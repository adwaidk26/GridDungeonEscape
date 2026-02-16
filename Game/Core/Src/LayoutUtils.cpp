#include "LayoutUtils.hpp"

LayoutUtils& LayoutUtils::GetInstance() {
    static LayoutUtils instance;
    return instance;
}

LayoutUtils::LayoutUtils() : lastScreenWidth(0), lastScreenHeight(0), cachedMetrics{0} {}

void LayoutUtils::UpdateLayout() {
    int currentWidth = GetScreenWidth();
    int currentHeight = GetScreenHeight();

    if (currentWidth != lastScreenWidth || currentHeight != lastScreenHeight) {
        lastScreenWidth = currentWidth;
        lastScreenHeight = currentHeight;

        float scaleX = (float)currentWidth / GameConstants::screenWidth;
        float scaleY = (float)currentHeight / GameConstants::screenHeight;
        float scale = (scaleX < scaleY) ? scaleX : scaleY;

        float destWidth = (float)GameConstants::screenWidth * scale;
        float destHeight = (float)GameConstants::screenHeight * scale;

        float offsetX = ((float)currentWidth - destWidth) * 0.5f;
        float offsetY = ((float)currentHeight - destHeight) * 0.5f;

        cachedMetrics = { scale, offsetX, offsetY, destWidth, destHeight };
    }
}

const LayoutMetrics& LayoutUtils::GetLayoutMetrics() const {
    return cachedMetrics;
}

Rectangle LayoutUtils::ScaleRect(const Rectangle& rect) const {
    return {
        cachedMetrics.offsetX + rect.x * cachedMetrics.scale,
        cachedMetrics.offsetY + rect.y * cachedMetrics.scale,
        rect.width * cachedMetrics.scale,
        rect.height * cachedMetrics.scale
    };
}