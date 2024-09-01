#pragma once

#include "Internal/Macros/ClassMacros.h"
#include <assert.h>

template <typename T>
class Service
{
private:
    static inline T* s_Instance = nullptr;
    
protected:
    Service()
    {
        assert(s_Instance == nullptr && "Trying to create multiple instances of the same service");
        
        s_Instance = static_cast<T*>(this);
    }

    ~Service()
    {
        s_Instance = nullptr;
    }

public:
    DELETE_COPY_AND_MOVE_CONSTRUCTORS(Service);

public:
    static T& Get()
    {
        assert(s_Instance != nullptr && "Trying to access a service that has not been created. Doing so will result in a nullptr dereference");
            
        return *s_Instance;
    }
};

