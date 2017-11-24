#include "EntityGenerator.hpp"

template <class T>
void av::generators::EntityGenerator::Generate(std::vector<T> l_entities, sf::Uint32 l_count, state::GameState l_state)
{
    auto missing_entities = l_count - l_entities.size();

    if(missing_entities != 0)
    {
        std::cout << "Missing Entities -> " << missing_entities << std::endl;
        
        //Generate the remaining entities
        T entity;

        l_entities.push_back(entity);
    }
}