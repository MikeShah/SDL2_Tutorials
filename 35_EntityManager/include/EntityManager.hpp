#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "GameEntity.hpp"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

/*
// Example shortcut function to save us typing so much
// when actually using the Entity Manager
// TODO: You can remove this whenver you like
std::shared_ptr<GameEntity> GetEntityRef(std::string name){
    return  EntityManager::GetInstance().GetEntityRef(name);
}
*/

// Singleton class
class EntityManager{
    public:
        static EntityManager& GetInstance(){
            static EntityManager* instance = new EntityManager;
            return *instance;
        }

        bool CreateEntity(std::string name, SDL_Renderer* renderer){
            std::shared_ptr<GameEntity> newEntity = std::make_shared<GameEntity>(name, renderer); 
            m_entities.insert(std::make_pair(name,newEntity));
            // Increment our count
            m_entityCount++;
            // Return if the operation was successful
            return (m_entities[name] != nullptr);
        }

        // Retrieve the Entity from the key
        std::shared_ptr<GameEntity> GetEntityRef(std::string name){
            return (m_entities[name]);
        }

        // Remove the entity
        void RemoveEntity(std::string name){
            // TODO: Some error handling, check if entity
            //       was actually found.
            auto it = m_entities.find(name);
            m_entities.erase(it);
            m_entityCount--;
        }

        // Update all the entities
        void UpdateAll(){
            size_t index=0;
            for(auto it = m_entities.begin() ; it!= m_entities.end(); it++){
                if(m_entities[it->first]!=nullptr){
                    m_entities[it->first]->Update();
                }else{
                    std::cout << "Unknown entity update: " << index << std::endl;
                }
                index++;
            }
        }

        // Render all of the entities
        void RenderAll(){
            size_t index=0;
            for(auto it = m_entities.begin() ; it!= m_entities.end(); it++){
                if(m_entities[it->first]!=nullptr){
                    m_entities[it->first]->Render();
                }else{
                    std::cout << "Unknown entity render: " << index << std::endl;
                }
                index++;
            }
        }

        // Delete all of the entities
        void DeleteAllEntities(){
            m_entities.erase(m_entities.begin(),m_entities.end());
            m_entityCount=0;
        }

    private:
        // Private Constructor
        EntityManager(){}
        // Private Destructor
        ~EntityManager() {}
    private:
        long long m_entityCount = 0;
        // Hold a mapping of entities names to an object 
        std::unordered_map<std::string, std::shared_ptr<GameEntity>> m_entities;
};


#endif
