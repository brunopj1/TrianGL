#pragma once

#include <type_traits>

namespace TGL
{
    // Forward declarations
    class GameObject;
    class GameMode;
    class Entity;
    class Component;

    // Castable concepts

    template <typename T>
    concept CastableGameObject =
        std::is_base_of_v<GameObject, T>;
    
    // Spawnable concepts

    template <typename T, typename... Args>
    concept SpawnableGameMode =
        !std::is_same_v<GameMode, T> &&
        std::is_base_of_v<GameMode, T> &&
        std::is_constructible_v<T, Args...>;

    template <typename T, typename... Args>
    concept SpawnableEntity =
        !std::is_same_v<Entity, T> &&
        std::is_base_of_v<Entity, T> &&
        std::is_constructible_v<T, Args...>;

    template <typename T, typename... Args>
    concept SpawnableComponent =
        !std::is_same_v<Component, T> &&
        std::is_base_of_v<Component, T> &&
        std::is_constructible_v<T, Args...>;

    // Searchable concepts

    template <typename T>
    concept SearchableEntity =
        !std::is_same_v<Entity, T> &&
        std::is_base_of_v<Entity, T>;

    template <typename T>
    concept SearchableComponent =
        !std::is_same_v<Component, T> &&
        std::is_base_of_v<Component, T>;
}
