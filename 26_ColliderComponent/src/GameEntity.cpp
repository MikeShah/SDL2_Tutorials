#include "GameEntity.hpp"
#include "Collider2D.hpp"

GameEntity::GameEntity(){
    m_sprite = nullptr;
}

GameEntity::GameEntity(SDL_Renderer* renderer){
    m_renderer = renderer;
    m_sprite = nullptr;
}


GameEntity::~GameEntity(){
    if(nullptr != m_sprite){
        delete m_sprite; 
    }
    
    for(int i=0; i<m_colliders.size(); i++){
        delete m_colliders[i];
    }

}

void GameEntity::Update(){
    // Update the position of our collider,
    // to be the same as the position of our Sprite component
    //if(nullptr != m_sprite){
    //    int x = m_sprite->GetPositionX();
    //    int y = m_sprite->GetPositionY();
    //    int w = m_sprite->GetWidth();
    //    int h = m_sprite->GetHeight();
    //}
    
}

void GameEntity::Render(){
    if(nullptr != m_sprite){
        m_sprite->Render(m_renderer);
    }

    for(int i=0; i < m_colliders.size();i++){
        if(nullptr != m_colliders[i]){
           SDL_SetRenderDrawColor(m_renderer,255,0,255,SDL_ALPHA_OPAQUE);
           SDL_RenderDrawRect(m_renderer,&m_colliders[i]->GetColliderBoundingBox()); 
        }

    }
}

void GameEntity::AddTexturedRectangleComponent(std::string spritepath){
    m_sprite = new TexturedRectangle(m_renderer,spritepath);
}

void GameEntity::AddTexturedRectangleComponent(std::string spritepath, int redcolorkey, int greencolorkey, int bluecolorkey){
    m_sprite = new TexturedRectangle(m_renderer,spritepath, redcolorkey, greencolorkey, bluecolorkey);
}

void GameEntity::AddCollider2D(){
    m_colliders.push_back(new Collider2D());
}


TexturedRectangle& GameEntity::GetTexturedRectangle(){
    return *m_sprite;
}

Collider2D& GameEntity::GetCollider2D(size_t index){
    return *m_colliders[index];
}


