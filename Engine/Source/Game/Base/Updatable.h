#pragma once

namespace TGL
{
    class Updatable
    {
    private:
        friend class EntityManager;

    private:
        bool m_ShouldUpdate;

    public:
        Updatable(bool shouldUpdate);
        virtual ~Updatable() = default;

    protected:
        virtual int GetOrderOfExecution() const;

    protected:
        virtual void OnStart();
        virtual void OnUpdate(float deltaTime);
    };
}
