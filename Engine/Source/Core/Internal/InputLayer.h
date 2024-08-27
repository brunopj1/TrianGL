#pragma once

#include "Core/DataTypes.h"
#include "Core/InputCodes.h"
#include "glm/vec2.hpp"

// Forward declarations
// ReSharper disable once CppInconsistentNaming, IdentifierTypo
struct GLFWwindow;

namespace TGL
{
    class InputLayer final
    {
    private:
        friend class InputSystem;
        
    public:
        InputLayer() = delete;
        ~InputLayer() = delete;

    private:
        static void BindKeyboardCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32, i32, i32, i32));
        static void BindMouseButtonCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32, i32, i32));
        static void BindMousePositionCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, f64, f64));
        static void BindMouseScrollCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, f64, f64));
        
    private:
        static void SetMouseInputMode(GLFWwindow* windowPtr, MouseMode mode);
        
        static void SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position);
        static glm::ivec2 GetMousePosition(GLFWwindow* windowPtr);
    };
}


