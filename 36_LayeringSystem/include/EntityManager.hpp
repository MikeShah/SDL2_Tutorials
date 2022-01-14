#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "GameEntity.hpp"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

#include "Layer.hpp"

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

        bool CreateEntity(std::string name, SDL_Renderer* renderer, LAYER layer);
        // Retrieve the Entity from the key
        std::shared_ptr<GameEntity> GetEntityRef(std::string name);
        // Remove the entity
        void RemoveEntity(std::string name);
        // Update all the entities
        void UpdateAll();
        // Render all of the entities
        void RenderAllLayers();
		// Render all entities in a specific layer
		void RenderLayer(LAYER layer);
        // Delete all of the entities
        void DeleteAllEntities();
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
