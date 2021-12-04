#include "ResourceManager.hpp"

ResourceManager::ResourceManager(){

}

ResourceManager::ResourceManager(ResourceManager const&){

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs){
    // TODO: Although we do not need this for a singleton
    return *this;
}

// Is instantiate, exactly 1 instance of our class
ResourceManager& ResourceManager::GetInstance(){
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath){
    // We will, look through, our m_surfaces
    // which is a 'unordered_map' and see if
    // a file exists.
    // And if the file does exist, then return the
    // associated surface.
    auto search = m_surfaces.find(filepath);
    if(search != m_surfaces.end()){
        return m_surfaces[filepath];
    }else{
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        m_surfaces.insert(std::make_pair(filepath,surface));
        return m_surfaces[filepath];
    }
    
    return nullptr;

}








