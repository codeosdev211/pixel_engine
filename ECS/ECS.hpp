#ifndef ECS_hpp
#define ECS_hpp

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;

using component_id = std::size_t;

inline component_id get_component_type_id() {
    static component_id last_id = 0;
    return ++last_id;
}

template <typename T> inline component_id get_component_type_id() noexcept {
    static component_id type_id = get_component_type_id();
    return type_id;
}

constexpr std::size_t max_components = 32;

using component_bitset = std::bitset<max_components>;
using component_array = std::array<Component*, max_components>;

class Component {

public:
    Entity* entity;

    virtual void init() { }
    virtual void update() { }
    virtual void draw() {}

    virtual ~Component() { }

};

class Entity {

private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    component_array comp_array;
    component_bitset comp_bitset;

public:
    void update() {
        for(auto& comp: components) comp->update();
    }

    void draw() {
        for (auto &comp : components)comp->draw();
     }
    bool is_active() const { return active; }
    void destroy() { active = false; }

    template <typename T> bool has_component() const {
        return comp_bitset[get_component_type_id<T>()];
    }

    template <typename T, typename... TArgs>
    T& add_component(TArgs&&... m_args) {
        T* comp(new T(std::forward<TArgs>(m_args)...));
        comp->entity = this;
        std::unique_ptr<Component> u_ptr { comp };
        components.emplace_back(std::move(u_ptr));

        comp_array[get_component_type_id<T>()] = comp;
        comp_bitset[get_component_type_id<T>()] = true;

        comp->init();
        return *comp;
    }

    template<typename T> T& get_component() const {
        auto ptr(comp_array[get_component_type_id<T>()]);
        return *static_cast<T*>(ptr);
    }
  
};

class Manager {

private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void update() {
        for(auto& entity: entities) entity->update();
    }

    void draw() {
        for(auto& entity: entities) entity->draw();
    }

    void refresh() {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
            [](const std::unique_ptr<Entity> &m_entity) {
                return !m_entity->is_active();
            }),
            std::end(entities));
    }

    Entity& add_entity() {
        Entity* entity = new Entity();
        std::unique_ptr<Entity> u_ptr { entity };
        entities.emplace_back(std::move(u_ptr));

        return *entity;
    }

};

#endif