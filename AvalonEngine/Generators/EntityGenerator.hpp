#pragma once

#include <SFML/Graphics.hpp>
#include "../States/GameState.hpp"
#include <iostream>

namespace av
{
    namespace generators
    {

        class EntityGenerator {

        public:

            template <class T>
            static void Generate(std::vector<T> l_entities, sf::Uint32 l_count, state::GameState l_state);
        };

    }
}