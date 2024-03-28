#pragma once

#include <vector>

// ReSharper disable CppClangTidyBugproneMacroParentheses

#define DECLARE_EVENT_NO_ARGS(callerClass, className, methodName) \
    class className                                               \
    {                                                             \
    private:                                                      \
        friend class callerClass;                                 \
                                                                  \
    private:                                                      \
        static inline std::vector<className*> s_Listeners;        \
                                                                  \
    public:                                                       \
        className() { s_Listeners.push_back(this); }              \
        virtual ~className() { std::erase(s_Listeners, this); }   \
                                                                  \
    protected:                                                    \
        virtual void methodName() = 0;                            \
    }

#define DECLARE_EVENT_WITH_ARG(callerClass, className, methodName, argType, argName) \
    class className                                                                  \
    {                                                                                \
    private:                                                                         \
        friend class callerClass;                                                    \
                                                                                     \
    private:                                                                         \
        static inline std::vector<className*> s_Listeners;                           \
                                                                                     \
    public:                                                                          \
        className() { s_Listeners.push_back(this); }                                 \
        virtual ~className() { std::erase(s_Listeners, this); }                      \
                                                                                     \
    protected:                                                                       \
        virtual void methodName(argType argName) = 0;                                \
    }
