#pragma once

#include <Internal/Macros/EventMacros.h>
#include <glm/vec2.hpp>

namespace TGL
{
    DECLARE_EVENT_WITH_ARG(Window, WindowMovedEvent, OnWindowMoved, glm::uvec2, newPosition);

    DECLARE_EVENT_WITH_ARG(Window, WindowResizedEvent, OnWindowResized, glm::uvec2, newResolution);

    DECLARE_EVENT_WITH_ARG(Window, WindowFullscreenEvent, OnWindowFullscreen, bool, fullscreen);

    DECLARE_EVENT_NO_ARGS(Window, WindowMaximizedEvent, OnWindowMaximized);

    DECLARE_EVENT_NO_ARGS(Window, WindowMinimizedEvent, OnWindowMinimized);

    DECLARE_EVENT_NO_ARGS(Window, WindowRestoredEvent, OnWindowRestored);
}
