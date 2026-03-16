#include "GameMapParser.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <raylib.h>

#include "DefaultGameEntities.hpp"
#include "DefaultGameTiles.hpp"
#include "Logger.hpp"

namespace GameMapParser {

namespace {

bool ReadRowsFromFile(const std::string& filePath, std::vector<std::string>& outRows)
{
    char* fileText = LoadFileText(filePath.c_str());
    if (!fileText) {
        LOG_ERR("Failed to open map file: %s", filePath.c_str());
        return false;
    }

    outRows.clear();
    std::string text(fileText);
    UnloadFileText(fileText);

    std::istringstream file(text);
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        outRows.push_back(line);
    }

    if (outRows.empty()) {
        LOG_ERR("Map file is empty: %s", filePath.c_str());
        return false;
    }

    return true;
}

bool ValidateRows(const std::vector<std::string>& rows, const std::string& filePath, size_t& outExpectedWidth)
{
    outExpectedWidth = rows.front().size();
    if (outExpectedWidth == 0) {
        LOG_ERR("Map has zero-width rows: %s", filePath.c_str());
        return false;
    }

    for (size_t y = 0; y < rows.size(); ++y) {
        if (rows[y].size() != outExpectedWidth) {
            LOG_ERR(
                "Map row width mismatch at row %zu in %s (expected %zu, got %zu)",
                y,
                filePath.c_str(),
                outExpectedWidth,
                rows[y].size()
            );
            return false;
        }
    }

    return true;
}

void ResizeOutputGrid(int width, int height, std::vector<std::vector<GameMapCell>>& outGrid)
{
    outGrid.clear();
    outGrid.resize(static_cast<size_t>(height));
    for (auto& row : outGrid) {
        row.resize(static_cast<size_t>(width));
    }
}

bool ParseEntitySymbol(char symbol, GameMapCell& outCell)
{
    switch (symbol) {
        case '.':
        case ' ':
            return true;
        case 'P':
            outCell.entity = std::make_unique<PlayerEntity>();
            return true;
        case 'B':
            outCell.entity = std::make_unique<BoulderEntity>();
            return true;
        case 'G':
            outCell.entity = std::make_unique<GemEntity>();
            return true;
        case 'S':
            outCell.entity = std::make_unique<StoneWallEntity>();
            return true;
        case 'R':
            outCell.entity = std::make_unique<GrassEntity>();
            return true;
        default:
            return false;
    }
}

bool ParseTileSymbol(char symbol, int x, int y, GameMapCell& outCell)
{
    switch (symbol) {
        case '.':
        case ' ':
            return true;
        case '#':
        case 'M':
            outCell.tile = std::make_unique<MetalWallTile>(x, y);
            return true;
        case 'H':
            outCell.tile = std::make_unique<MetalGrillTile>(x, y);
            return true;
        case 'D':
            outCell.tile = std::make_unique<MudWallTile>(x, y);
            return true;
        case 'V':
            outCell.tile = std::make_unique<VinesWallTile>(x, y);
            return true;
        default:
            return false;
    }
}

bool ParseLayersIntoGrid(
    const std::vector<std::string>& entityRows,
    const std::vector<std::string>& tileRows,
    const std::string& entitiesFilePath,
    const std::string& tilesFilePath,
    std::vector<std::vector<GameMapCell>>& outGrid
)
{
    for (size_t y = 0; y < entityRows.size(); ++y) {
        for (size_t x = 0; x < entityRows[y].size(); ++x) {
            GameMapCell parsedCell{};

            if (!ParseTileSymbol(tileRows[y][x], static_cast<int>(x), static_cast<int>(y), parsedCell)) {
                LOG_ERR(
                    "Unknown tile symbol '%c' at (%zu, %zu) in %s",
                    tileRows[y][x],
                    x,
                    y,
                    tilesFilePath.c_str()
                );
                return false;
            }

            if (!ParseEntitySymbol(entityRows[y][x], parsedCell)) {
                LOG_ERR(
                    "Unknown entity symbol '%c' at (%zu, %zu) in %s",
                    entityRows[y][x],
                    x,
                    y,
                    entitiesFilePath.c_str()
                );
                return false;
            }

            if (parsedCell.entity) {
                parsedCell.entity->SetPosition(
                    GameEntity::GetWorldPosFromGridPos(static_cast<int>(x), static_cast<int>(y))
                );
                parsedCell.entity->SetGridPosition(static_cast<int>(x), static_cast<int>(y));
            }

            outGrid[y][x] = std::move(parsedCell);
        }
    }

    return true;
}

}  // namespace

bool LoadMapFromFiles(
    const std::string& entitiesFilePath,
    const std::string& tilesFilePath,
    std::vector<std::vector<GameMapCell>>& outGrid,
    int& outWidth,
    int& outHeight
)
{
    std::vector<std::string> entityRows;
    if (!ReadRowsFromFile(entitiesFilePath, entityRows)) {
        return false;
    }

    std::vector<std::string> tileRows;
    if (!ReadRowsFromFile(tilesFilePath, tileRows)) {
        return false;
    }

    size_t entityWidth = 0;
    if (!ValidateRows(entityRows, entitiesFilePath, entityWidth)) {
        return false;
    }

    size_t tileWidth = 0;
    if (!ValidateRows(tileRows, tilesFilePath, tileWidth)) {
        return false;
    }

    if (entityRows.size() != tileRows.size() || entityWidth != tileWidth) {
        LOG_ERR(
            "Map layer size mismatch: entities=%s (%zux%zu), tiles=%s (%zux%zu)",
            entitiesFilePath.c_str(),
            entityWidth,
            entityRows.size(),
            tilesFilePath.c_str(),
            tileWidth,
            tileRows.size()
        );
        return false;
    }

    outWidth = static_cast<int>(entityWidth);
    outHeight = static_cast<int>(entityRows.size());
    ResizeOutputGrid(outWidth, outHeight, outGrid);

    if (!ParseLayersIntoGrid(entityRows, tileRows, entitiesFilePath, tilesFilePath, outGrid)) {
        return false;
    }

    LOG_INFO(
        "Loaded layered map: entities=%s tiles=%s (%dx%d)",
        entitiesFilePath.c_str(),
        tilesFilePath.c_str(),
        outWidth,
        outHeight
    );
    return true;
}

}  // namespace GameMapParser
