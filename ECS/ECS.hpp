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
class Manager;

using component_id = std::size_t;
using Group = std::size_t;


inline component_id get_new_component_type_id() {
    static component_id last_id = 0u;
    return ++last_id;
}

template <typename T> inline component_id get_component_type_id() noexcept {
    static_assert (std::is_base_of<Component, T>::value, "");
    static component_id type_id = get_new_component_type_id();
    return type_id;
}

constexpr std::size_t max_components = 32;
constexpr std::size_t max_groups = 32;

using component_bitset = std::bitset<max_components>;
using group_bitset = std::bitset<max_groups>;

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
    Manager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    component_array comp_array;
    component_bitset comp_bitset;
    group_bitset grp_bitset;

public:
    Entity(Manager& m_manager): manager(m_manager) {

    }
    void update() {
        for(auto& comp: components) comp->update();
    }

    void draw() {
        for (auto &comp : components)comp->draw();
     }
    bool is_active() const { return active; }
    void destroy() { active = false; }

    bool has_group(Group m_group) {
        return grp_bitset[m_group];
    }

    void add_group(Group m_group);

    void del_group(Group m_group) {
        grp_bitset[m_group] = false;
    }

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
    std::array<std::vector<Entity*>, max_groups> grouped_entities;


public:
    void update() {
        for(auto& entity: entities) entity->update();
    }

    void draw() {
        for(auto& entity: entities) entity->draw();
    }

    void refresh() {
        for(auto i(0u); i< max_groups; ++i) {
            auto & vecs(grouped_entities[i]);
            vecs.erase(
                std::remove_if(std::begin(vecs), std::end(vecs),
                [i](Entity* m_entity) {
                    return !m_entity->is_active() || !m_entity->has_group(i);
                }),
                std::end(vecs));
        }
            
        entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
            [](const std::unique_ptr<Entity> &m_entity) {
                return !m_entity->is_active();
            }),
            std::end(entities));
    }

    void add_to_group(Entity* m_entity, Group m_group) {
        grouped_entities[m_group].emplace_back(m_entity);
    }

    std::vector<Entity*>& get_group(Group m_group) {
        return grouped_entities[m_group];
    }

    Entity& add_entity() {
        Entity* entity = new Entity(*this);
        std::unique_ptr<Entity> u_ptr { entity };
        entities.emplace_back(std::move(u_ptr));

        return *entity;
    }

};

#endif