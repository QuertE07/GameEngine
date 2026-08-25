#pragma once
#include "Framework/Object.h"
#include "Singleton.h"
#include "StringUtils.h"

#include <iostream>
#include <memory>
#include <map>

#define FACTORY_REGISTER(classname)                                     \
    class Register##classname                                           \
    {                                                                   \
    public:                                                             \
        Register##classname()                                           \
        {                                                               \
            gl::Factory::Instance().Register<classname>(#classname);    \
        }                                                               \
    };                                                                  \
    static Register##classname registerInstance;

namespace gl
{
    class ICreator
    {
    public:
        virtual ~ICreator() = default;
        virtual std::unique_ptr<Object> Create() = 0;
    };

    // Requires passed-in class to be object or any of its subclasses
    template <typename T>
        requires std::derived_from<T, Object>
    class Creator : public ICreator
    {
    public:
        ~Creator() = default;
        std::unique_ptr<Object> Create() override
        {
            return std::make_unique<T>();
        }
    };

    template <typename T>
        requires std::derived_from<T, Object>
    class PrototypeCreator : public ICreator
    {
    public:
        PrototypeCreator(std::unique_ptr<Object> prototype) : m_prototype{ std::move(prototype) } { }
        std::unique_ptr<class Object> Create() override
        {
            return m_prototype->Clone();
        }

    private:
        std::unique_ptr<Object> m_prototype;
    };

    // Factory is a singleton because there should only ever be one at any given point
    class Factory : public Singleton<Factory>
    {
    public:
        template <typename T>
            requires std::derived_from<T, Object>
        void Register(const std::string& name);

        template <typename T>
            requires std::derived_from<T, Object>
        void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);

        template <typename T = class Object>
            requires std::derived_from<T, Object>
        std::unique_ptr<T> Create(const std::string& name);

    private:
        // This is the registry. It holds things 🔥
        std::map<std::string, std::unique_ptr<ICreator>> m_registry;
    };

    template <typename T>
        requires std::derived_from<T, Object>
    inline void Factory::Register(const std::string& name)
    {
        std::string lowerName = ToLower(name);

        if (m_registry.contains(lowerName))
        {
            // Cancel adding a name to registry that already has an object in it
            std::cerr << "Object already registered: " << lowerName << std::endl;
            return;
        }

        // Store object to registry under name
        m_registry[lowerName] = std::make_unique<Creator<T>>();
    }

    template <typename T>
        requires std::derived_from<T, Object>
    inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype)
    {
        std::string lowerName = ToLower(name);

        if (m_registry.contains(lowerName))
        {
            // Cancel adding a name to registry that already has an object in it
            std::cerr << "Object already registered: " << lowerName << std::endl;
            return;
        }

        // Store object to registry under name
        m_registry[lowerName] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
    }

    template <typename T>
        requires std::derived_from<T, Object>
    inline std::unique_ptr<T> Factory::Create(const std::string& name)
    {
        std::string lowerName = ToLower(name);

        if (!m_registry.contains(lowerName))
        {
            // Print out error if trying to create unregistered object derivative
            std::cerr << "Object not registered: " << lowerName << std::endl;
            return std::unique_ptr<T>();
        }

        // If object *is* registered, create it
        auto iter = m_registry.find(lowerName);
        auto object = iter->second->Create();

        // Check if object created is the same or derived from type T
        T* derived = dynamic_cast<T*>(object.get());
        if (derived)
        {
            // Release and return unique pointer to object
            object.release();
            return std::unique_ptr<T>(derived);
        }
        else {
            // Print out error if not derived
            std::cerr << "Object not derived: " << lowerName << std::endl;
        }

        return std::unique_ptr<T>();
    }
}