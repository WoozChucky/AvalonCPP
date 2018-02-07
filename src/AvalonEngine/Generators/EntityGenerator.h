//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_ENTITYGENERATOR_H
#define AVALONENGINE_ENTITYGENERATOR_H

#include <SFML/Graphics.hpp>
#include <typeinfo>
#include "../Locator.h"
#include "../Entities/Enemy.h"

namespace av
{
    /**
     * NOTE: So this might be a really helpfull tip for beginners, like me!
     * In template classes and/or member functions, the definition and implementation has to be done in the same file!
     * ie: EntitityGenerator has a template method (Generate) defined and implemented in the same file (This one here! EntityGenerator.h).
     */

    class EntityGenerator {

    public:

        // This is somewhat not generic, in fact it is a bit hardcoded because of the lack of entitie's default constructor.
        // So I might create a default constructor, and have all entities implement some sort of Initialize() method that
        // has to take the same number and type of arguments. But in that case whenever I want to create some entities outside
        // the generators, I have to make sure that i have all the required arguments to Initialize(), if any.
        // Or I simply continue to check the 'typeof' of those entities and act accordingly >.< .
        template <class T>
        static void Generate(std::vector<T>& l_entities, const sf::Uint32 l_count /*, state::GameState l_state*/ )
        {
            auto missing_entities = l_count - l_entities.size();

            if (missing_entities > 0)
            {
                char buffer[80];
                sprintf(buffer, "Missing %s -> %d", typeid(T).name(), static_cast<int>(missing_entities));
                Locator::GetLogger().Log(__FUNCTION__, buffer);

                for(auto i = l_entities.size(); i < l_count; i++)
                {
                    if (typeid(T) == typeid(Enemy))
                    {
                        auto valid_position = false;

                        //TODO: This is a possible mem leak due to some control paths, please analyze!
                        T* entity = new Enemy(sf::Vector2f(50.f, 50.f));

                        if(i > 0)
                        {
                            while (!valid_position)
                            {
                                auto counter = 0;

                                // loop trough all the entities and break when they don't collide.
                                for (auto j = 0; j < l_entities.size(); j++)
                                {
                                    if (static_cast<Enemy>(l_entities[j]).Collide(static_cast<Enemy>(*entity)))
                                    {
                                        // Set a random position
                                        entity = new Enemy(sf::Vector2f(50.f, 50.f));
                                        break;
                                    }

                                    counter++;

                                    if(counter == l_entities.size())
                                    {
                                        // The new entity doesn't collide with any preivously crated entities
                                        valid_position = true;
                                        counter = 0;
                                        break;
                                    }
                                }

                            }
                            valid_position = false; //Reset
                        }

                        //Push then entity
                        l_entities.push_back(*entity);
                    }
                    else if(typeid(T) == typeid(Bullet))
                    {
                        //TODO
                    }
                }
            }
        }
    };
}

#endif //AVALONENGINE_ENTITYGENERATOR_H
