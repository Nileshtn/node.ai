#ifndef IMGUI_VEC2_UTILS_HPP
#define IMGUI_VEC2_UTILS_HPP

#include "imgui.h"

// Add two ImVec2
inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

// Subtract two ImVec2
inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

// Multiply ImVec2 by scalar
inline ImVec2 operator*(const ImVec2& lhs, float scalar) {
    return ImVec2(lhs.x * scalar, lhs.y * scalar);
}

// Divide ImVec2 by scalar
inline ImVec2 operator/(const ImVec2& lhs, float scalar) {
    return ImVec2(lhs.x / scalar, lhs.y / scalar);
}

#endif // IMGUI_VEC2_UTILS_HPP
