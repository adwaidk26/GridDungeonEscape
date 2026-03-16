#include "RenderUtils.hpp"

#include "GameConstants.hpp"

namespace RenderUtils {

void DrawTextureInTile(const Texture2D& texture, Vector2 tileCenter)
{
    const float tileSize = static_cast<float>(GameConstants::TILE_SIZE);
    const Rectangle destination = {
        tileCenter.x - tileSize / 2.0f,
        tileCenter.y - tileSize / 2.0f,
        tileSize,
        tileSize
    };

    if (texture.id == 0) {
        DrawRectangle(
            static_cast<int>(destination.x),
            static_cast<int>(destination.y),
            static_cast<int>(destination.width),
            static_cast<int>(destination.height),
            MAGENTA
        );
        return;
    }

    const Rectangle source = {
        0.0f,
        0.0f,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };
    DrawTexturePro(texture, source, destination, {0.0f, 0.0f}, 0.0f, WHITE);
}

}  // namespace RenderUtils
