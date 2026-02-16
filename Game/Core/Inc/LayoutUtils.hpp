#pragma once
#include <raylib.h>
#include "GameConstants.hpp"

struct LayoutMetrics {
    float scale;
    float offsetX;
    float offsetY;
    float destWidth;
    float destHeight;
};

class LayoutUtils {
public:
    static LayoutUtils& GetInstance();

    void UpdateLayout();

    const LayoutMetrics& GetLayoutMetrics() const;

    Rectangle ScaleRect(const Rectangle& rect) const;

private:
    LayoutUtils();
    ~LayoutUtils() = default;
    LayoutUtils(const LayoutUtils&) = delete;
    LayoutUtils& operator=(const LayoutUtils&) = delete;

    int lastScreenWidth;
    int lastScreenHeight;
    LayoutMetrics cachedMetrics;
}; 