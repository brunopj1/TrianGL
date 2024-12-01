#pragma once

#include "Internal/Concepts/ServiceCollection.h"
#include "Services/Backends/AudioBackend.h"
#include "Services/Backends/InputBackend.h"
#include "Services/Backends/RenderBackend.h"
#include "Services/Private/AssetManager.h"
#include "Services/Private/EntityManager.h"
#include "Services/Public/Clock.h"
#include "Services/Public/InputSystem.h"
#include "Services/Public/Window.h"
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

		// Backend services
		std::unique_ptr<RenderBackend, ServiceDeleter<RenderBackend>> RenderBackendImpl = nullptr;
		std::unique_ptr<InputBackend, ServiceDeleter<InputBackend>> InputBackendImpl = nullptr;
		std::unique_ptr<AudioBackend, ServiceDeleter<AudioBackend>> AudioBackendImpl = nullptr;

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
			else if constexpr (IsValidServiceOfType<RenderBackend, T>)
			{
				if (RenderBackendImpl == nullptr)
				{
					RenderBackendImpl = std::unique_ptr<T, ServiceDeleter<RenderBackend>>(new T());
				}
			}
			else if constexpr (IsValidServiceOfType<InputBackend, T>)
			{
				if (InputBackendImpl == nullptr)
				{
					InputBackendImpl = std::unique_ptr<T, ServiceDeleter<InputBackend>>(new T());
				}
			}
			else if constexpr (IsValidServiceOfType<AudioBackend, T>)
			{
				if (AudioBackendImpl == nullptr)
				{
					AudioBackendImpl = std::unique_ptr<T, ServiceDeleter<AudioBackend>>(new T());
				}
			}
			else
			{
				// TODO this static assert is generating compile errors after updating Visual Studio
				//static_assert(false, "Invalid service type");
			}
		}
	};
}
