#pragma once

#include <Core/DataTypes.h>
#include <Internal/Asserts/SpawnerAsserts.h>
#include <cstddef>
#include <type_traits>

// TODO add the concept to the all templated classes

namespace TGL
{
    class ReferenceCounter final
    {
    private:
        template <typename T>
        friend class SharedPtr;

    private:
        u32 m_Counter = 1;
    };

    // TODO can the spawner var be moved to the AssetManager?
    class SharedPtrSpawnerUtil final
    {
    private:
        template <typename T>
        friend class SharedPtr;

        friend class Audio;
        friend class Material;
        friend class Texture;
        friend class TextureSlice;

    private:
        DECLARE_SPAWNER_ASSERT_VAR(Asset);

    public:
        SharedPtrSpawnerUtil() = delete;
        ~SharedPtrSpawnerUtil() = delete;

    public:
        SharedPtrSpawnerUtil(const SharedPtrSpawnerUtil&) = delete;
        SharedPtrSpawnerUtil& operator=(const SharedPtrSpawnerUtil&) = delete;
        SharedPtrSpawnerUtil(SharedPtrSpawnerUtil&&) = delete;
        SharedPtrSpawnerUtil& operator=(SharedPtrSpawnerUtil&&) = delete;
    };

    template <typename T>
    class SharedPtr final
    {
    private:
        friend class AssetManager;

        template <typename U>
        friend class SharedPtr;

        template <typename U>
        friend class SharedFromThis;

        template <typename To, typename From>
        friend SharedPtr<To> CastTo(const SharedPtr<From>& object);

    private:
        T* m_Pointer;
        ReferenceCounter* m_ReferenceCounter;

    public:
        SharedPtr()
            : m_Pointer(nullptr), m_ReferenceCounter(nullptr)
        {}

        SharedPtr(std::nullptr_t)
            : m_Pointer(nullptr), m_ReferenceCounter(nullptr)
        {}

    private:
        SharedPtr(T* ptr)
            : m_Pointer(ptr), m_ReferenceCounter(ptr != nullptr ? new ReferenceCounter() : nullptr)
        {
            if constexpr (std::is_base_of_v<SharedFromThis<T>, T>)
            {
                if (ptr != nullptr)
                {
                    ptr->m_Pointer = ptr;
                    ptr->m_ReferenceCounter = m_ReferenceCounter;
                }
            }
        }

        SharedPtr(T* ptr, ReferenceCounter* referenceCounter)
            : m_Pointer(ptr), m_ReferenceCounter(referenceCounter)
        {
            Increment();
        }

    public:
        ~SharedPtr()
        {
            Decrement();
        }

    public:
        SharedPtr(const SharedPtr& other)
            : m_Pointer(other.m_Pointer), m_ReferenceCounter(other.m_ReferenceCounter)
        {
            Increment();
        }

        SharedPtr(SharedPtr&& other) noexcept
            : m_Pointer(other.m_Pointer), m_ReferenceCounter(other.m_ReferenceCounter)
        {
            other.m_Pointer = nullptr;
            other.m_ReferenceCounter = nullptr;
        }

        SharedPtr& operator=(const SharedPtr& other)  // NOLINT(bugprone-unhandled-self-assignment)
        {
            if (this != &other)
            {
                Decrement();
                m_Pointer = other.m_Pointer;
                m_ReferenceCounter = other.m_ReferenceCounter;
                Increment();
            }

            return *this;
        }

        SharedPtr& operator=(SharedPtr&& other) noexcept
        {
            if (this != &other)
            {
                Decrement();
                m_Pointer = other.m_Pointer;
                m_ReferenceCounter = other.m_ReferenceCounter;
                other.m_Pointer = nullptr;
                other.m_ReferenceCounter = nullptr;
            }

            return *this;
        }

        SharedPtr& operator=(std::nullptr_t)
        {
            Decrement();
            m_Pointer = nullptr;
            m_ReferenceCounter = nullptr;
            return *this;
        }

        template <typename U>
        operator SharedPtr<U>() const // NOLINT(CppNonExplicitConversionOperator)
        {
            static_assert(std::is_base_of_v<U, T>, "U must be a base class of T");
            return SharedPtr<U>(m_Pointer, m_ReferenceCounter);
        }

    public:
        friend bool operator==(const SharedPtr& left, const SharedPtr& right)
        {
            return left.m_ReferenceCounter == right.m_ReferenceCounter;
        }

        friend bool operator!=(const SharedPtr& left, const SharedPtr& right)
        {
            return left.m_ReferenceCounter != right.m_ReferenceCounter;
        }

        friend bool operator==(const SharedPtr& left, std::nullptr_t)
        {
            return left.Get() == nullptr;
        }

        friend bool operator!=(const SharedPtr& left, std::nullptr_t)
        {
            return left.Get() != nullptr;
        }

    public:
        T* operator->() const
        {
            return Get();
        }

        T* operator*() const
        {
            return Get();
        }

    public:
        T* Get() const
        {
            return m_Pointer;
        }

        bool IsValid() const
        {
            return Get() != nullptr;
        }

    private:
        void Increment() const
        {
            if (m_ReferenceCounter == nullptr) return;

            m_ReferenceCounter->m_Counter++;
        }

        void Decrement() const
        {
            if (m_ReferenceCounter == nullptr) return;

            m_ReferenceCounter->m_Counter--;

            if (m_ReferenceCounter->m_Counter == 0)
            {
                PREPARE_SPAWNER_ASSERT_EXT(SharedPtrSpawnerUtil, Asset);

                delete m_ReferenceCounter;
                delete m_Pointer;
            }
        }
    };

    template <typename T>
    class SharedFromThis
    {
    private:
        friend class AssetManager;

        template <typename U>
        friend class SharedPtr;

    private:
        T* m_Pointer = nullptr;
        ReferenceCounter* m_ReferenceCounter = nullptr;

    protected:
        SharedPtr<T> ToSharedPtr()
        {
            return SharedPtr<T>(m_Pointer, m_ReferenceCounter);
        }
    };

    template <typename To, typename From>
    SharedPtr<To> CastTo(const SharedPtr<From>& object)
    {
        if (object == nullptr) return nullptr;

        if constexpr (std::is_base_of_v<To, From>)
        {
            return SharedPtr(static_cast<To*>(object.Get()), object.m_ReferenceCounter);
        }
        else if constexpr (std::is_base_of_v<From, To>)
        {
            return SharedPtr(dynamic_cast<To*>(object.Get()), object.m_ReferenceCounter);
        }
        else
        {
            return nullptr;
        }
    }
}
