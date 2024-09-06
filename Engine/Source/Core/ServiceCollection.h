#pragma once

#include "Internal/Concepts/ServiceCollection.h"
#include "Services/Clock.h"
#include "Services/InputSystem.h"
#include "Services/Internal/AssetManager.h"
#include "Services/Internal/EntityManager.h"
#include "Services/Window.h"
#include <memory>

namespace TGL
{
	class ServiceCollection final
	{
	public:
		// Public services
		std::unique_ptr<Clock, ServiceDeleter<Clock>> ClockImpl = nullptr;
		std::unique_ptr<Window, ServiceDeleter<Window>> WindowImpl = nullptr;
		std::unique_ptr<InputSystem, ServiceDeleter<InputSystem>> InputSystemImpl = nullptr;

		// Private services
		std::unique_ptr<EntityManager, ServiceDeleter<EntityManager>> EntityManagerImpl = nullptr;
		std::unique_ptr<AssetManager, ServiceDeleter<AssetManager>> AssetManagerImpl = nullptr;

	public:
		ServiceCollection() = default;
		~ServiceCollection() = default;

	public:
		template <typename T>
		void CreateService()
			requires IsValidService<T>
		{
			if constexpr (IsValidServiceOfType<Clock, T>)
			{
				if (ClockImpl == nullptr)
				{
					ClockImpl = std::unique_ptr<T, ServiceDeleter<Clock>>(new T());
				}
			}
			else if constexpr (IsValidServiceOfType<Window, T>)
			{
				if (WindowImpl == nullptr)
				{
					WindowImpl = std::unique_ptr<T, ServiceDeleter<Window>>(new T());
				}
			}
			else if constexpr (IsValidServiceOfType<InputSystem, T>)
			{
				if (InputSystemImpl == nullptr)
				{
					InputSystemImpl = std::unique_ptr<T, ServiceDeleter<InputSystem>>(new T());
				}
			}
			else if constexpr (IsValidServiceOfType<EntityManager, T>)
			{
				if (EntityManagerImpl == nullptr)
				{
					EntityManagerImpl = std::unique_ptr<T, ServiceDeleter<EntityManager>>(new T());
				}
			}
			else if constexpr (IsValidServiceOfType<AssetManager, T>)
			{
				if (AssetManagerImpl == nullptr)
				{
					AssetManagerImpl = std::unique_ptr<T, ServiceDeleter<AssetManager>>(new T());
				}
			}
			else
			{
				static_assert(false, "Invalid service type");
			}
		}
	};
}
