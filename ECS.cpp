#include "ECS/ECS.hpp"
  
void Entity::add_group(Group m_group) {
    grp_bitset[m_group] = true;
    manager.add_to_group(this, m_group);
}