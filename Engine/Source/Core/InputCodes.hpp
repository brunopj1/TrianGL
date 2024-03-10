#pragma once

// @formatter:off

namespace Engine
{

enum class KeyCode
{
        /* Error key */
        Unkown             = -1, // GLFW_KEY_UNKNOWN

        /* Printable keys */
        Space              = 32, // GLFW_KEY_SPACE
        Apostrophe         = 39, // GLFW_KEY_APOSTROPHE
        Comma              = 44, // GLFW_KEY_COMMA
        Minus              = 45, // GLFW_KEY_MINUS
        Period             = 46, // GLFW_KEY_PERIOD
        Slash              = 47, // GLFW_KEY_SLASH
        Num0               = 48, // GLFW_KEY_0
        Num1               = 49, // GLFW_KEY_1
        Num2               = 50, // GLFW_KEY_2
        Num3               = 51, // GLFW_KEY_3
        Num4               = 52, // GLFW_KEY_4
        Num5               = 53, // GLFW_KEY_5
        Num6               = 54, // GLFW_KEY_6
        Num7               = 55, // GLFW_KEY_7
        Num8               = 56, // GLFW_KEY_8
        Num9               = 57, // GLFW_KEY_9
        Semicolon          = 59, // GLFW_KEY_SEMICOLON
        Equal              = 61, // GLFW_KEY_EQUAL
        A                  = 65, // GLFW_KEY_A
        B                  = 66, // GLFW_KEY_B
        C                  = 67, // GLFW_KEY_C
        D                  = 68, // GLFW_KEY_D
        E                  = 69, // GLFW_KEY_E
        F                  = 70, // GLFW_KEY_F
        G                  = 71, // GLFW_KEY_G
        H                  = 72, // GLFW_KEY_H
        I                  = 73, // GLFW_KEY_I
        J                  = 74, // GLFW_KEY_J
        K                  = 75, // GLFW_KEY_K
        L                  = 76, // GLFW_KEY_L
        M                  = 77, // GLFW_KEY_M
        N                  = 78, // GLFW_KEY_N
        O                  = 79, // GLFW_KEY_O
        P                  = 80, // GLFW_KEY_P
        Q                  = 81, // GLFW_KEY_Q
        R                  = 82, // GLFW_KEY_R
        S                  = 83, // GLFW_KEY_S
        T                  = 84, // GLFW_KEY_T
        U                  = 85, // GLFW_KEY_U
        V                  = 86, // GLFW_KEY_V
        W                  = 87, // GLFW_KEY_W
        X                  = 88, // GLFW_KEY_X
        Y                  = 89, // GLFW_KEY_Y
        Z                  = 90, // GLFW_KEY_Z
        LeftBracket        = 91, // GLFW_KEY_LEFT_BRACKET
        Backslash          = 92, // GLFW_KEY_BACKSLASH
        RightBracket       = 93, // GLFW_KEY_RIGHT_BRACKET
        GraveAccent        = 96, // GLFW_KEY_GRAVE_ACCENT
        World1             = 161, // GLFW_KEY_WORLD_1
        World2             = 162, // GLFW_KEY_WORLD_2

        /* Function keys */
        Escape             = 256, // GLFW_KEY_ESCAPE
        Enter              = 257, // GLFW_KEY_ENTER
        Tab                = 258, // GLFW_KEY_TAB
        Backspace          = 259, // GLFW_KEY_BACKSPACE
        Insert             = 260, // GLFW_KEY_INSERT
        Delete             = 261, // GLFW_KEY_DELETE
        Right              = 262, // GLFW_KEY_RIGHT
        Left               = 263, // GLFW_KEY_LEFT
        Down               = 264, // GLFW_KEY_DOWN
        Up                 = 265, // GLFW_KEY_UP
        PageUp             = 266, // GLFW_KEY_PAGE_UP
        PageDown           = 267, // GLFW_KEY_PAGE_DOWN
        Home               = 268, // GLFW_KEY_HOME
        End                = 269, // GLFW_KEY_END
        CapsLock           = 280, // GLFW_KEY_CAPS_LOCK
        ScrollLock         = 281, // GLFW_KEY_SCROLL_LOCK
        NumLock            = 282, // GLFW_KEY_NUM_LOCK
        PrintScreen        = 283, // GLFW_KEY_PRINT_SCREEN
        Pause              = 284, // GLFW_KEY_PAUSE
        F1                 = 290, // GLFW_KEY_F1
        F2                 = 291, // GLFW_KEY_F2
        F3                 = 292, // GLFW_KEY_F3
        F4                 = 293, // GLFW_KEY_F4
        F5                 = 294, // GLFW_KEY_F5
        F6                 = 295, // GLFW_KEY_F6
        F7                 = 296, // GLFW_KEY_F7
        F8                 = 297, // GLFW_KEY_F8
        F9                 = 298, // GLFW_KEY_F9
        F10                = 299, // GLFW_KEY_F10
        F11                = 300, // GLFW_KEY_F11
        F12                = 301, // GLFW_KEY_F12
        F13                = 302, // GLFW_KEY_F13
        F14                = 303, // GLFW_KEY_F14
        F15                = 304, // GLFW_KEY_F15
        F16                = 305, // GLFW_KEY_F16
        F17                = 306, // GLFW_KEY_F17
        F18                = 307, // GLFW_KEY_F18
        F19                = 308, // GLFW_KEY_F19
        F20                = 309, // GLFW_KEY_F20
        F21                = 310, // GLFW_KEY_F21
        F22                = 311, // GLFW_KEY_F22
        F23                = 312, // GLFW_KEY_F23
        F24                = 313, // GLFW_KEY_F24
        F25                = 314, // GLFW_KEY_F25
        Keypad0            = 320, // GLFW_KEY_KP_0
        Keypad1            = 321, // GLFW_KEY_KP_1
        Keypad2            = 322, // GLFW_KEY_KP_2
        Keypad3            = 323, // GLFW_KEY_KP_3
        Keypad4            = 324, // GLFW_KEY_KP_4
        Keypad5            = 325, // GLFW_KEY_KP_5
        Keypad6            = 326, // GLFW_KEY_KP_6
        Keypad7            = 327, // GLFW_KEY_KP_7
        Keypad8            = 328, // GLFW_KEY_KP_8
        Keypad9            = 329, // GLFW_KEY_KP_9
        KeypadDecimal      = 330, // GLFW_KEY_KP_DECIMAL
        KeypadDivide       = 331, // GLFW_KEY_KP_DIVIDE
        KeypadMultiply     = 332, // GLFW_KEY_KP_MULTIPLY
        KeypadSubtract     = 333, // GLFW_KEY_KP_SUBTRACT
        KeypadAdd          = 334, // GLFW_KEY_KP_ADD
        KeypadEnter        = 335, // GLFW_KEY_KP_ENTER
        KeypadEqual        = 336, // GLFW_KEY_KP_EQUAL
        LeftShift          = 340, // GLFW_KEY_LEFT_SHIFT
        LeftControl        = 341, // GLFW_KEY_LEFT_CONTROL
        LeftAlt            = 342, // GLFW_KEY_LEFT_ALT
        LeftSuper          = 343, // GLFW_KEY_LEFT_SUPER
        RightShift         = 344, // GLFW_KEY_RIGHT_SHIFT
        RightControl       = 345, // GLFW_KEY_RIGHT_CONTROL
        RightAlt           = 346, // GLFW_KEY_RIGHT_ALT
        RightSuper         = 347, // GLFW_KEY_RIGHT_SUPER
        Menu               = 348  // GLFW_KEY_MENU
    };

    enum class MouseButton
    {
        Left               = 0, // GLFW_MOUSE_BUTTON_LEFT
        Right              = 1, // GLFW_MOUSE_BUTTON_RIGHT
        Middle             = 2, // GLFW_MOUSE_BUTTON_MIDDLE
        Button4            = 3, // GLFW_MOUSE_BUTTON_4
        Button5            = 4, // GLFW_MOUSE_BUTTON_5
        Button6            = 5, // GLFW_MOUSE_BUTTON_6
        Button7            = 6, // GLFW_MOUSE_BUTTON_7
        Button8            = 7  // GLFW_MOUSE_BUTTON_8
    };

    enum class MouseMode
    {
        Normal             = 0x00034001, // GLFW_CURSOR_NORMAL
        Hidden             = 0x00034002, // GLFW_CURSOR_HIDDEN
        Disabled           = 0x00034003, // GLFW_CURSOR_DISABLED
        Captured           = 0x00034004  // GLFW_CURSOR_CAPTURED
    };
}

// @formatter:on
