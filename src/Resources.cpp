#include "../include/Resources.hpp"

#include "../include/Game.hpp"
#include <iostream>

std::unordered_map<std::string,Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string,Mix_Music*> Resources::musicTable;
std::unordered_map<std::string,SDL_Texture*> Resources::imageTable;

Mix_Chunk* Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);
    
    if(it == soundTable.end()) {
        Mix_Chunk* aux_chunk;
        try {
            aux_chunk = Mix_LoadWAV(file.c_str());
        } 
        catch(...) { 
            std::cout << "MixLoadWAV_ERROR: " << SDL_GetError() << std::endl;
            exit(-4);
        }
        std::pair<std::string,Mix_Chunk*> toInsert(file,aux_chunk);
        soundTable.insert(toInsert);
        return aux_chunk;
    }
    return it->second;
}

void Resources::ClearSounds() {
    for(auto a : soundTable) {
        if(a.second != nullptr) Mix_FreeChunk(a.second);
    }
    soundTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);
    if(it == musicTable.end()) {
        Mix_Music* aux_music;
        try {
            aux_music = Mix_LoadMUS(file.c_str());
        }
        catch(...) {
            std::cout << "MixLoadMUS_ERROR: " << SDL_GetError() << std::endl;
            exit(-4);
        }
        return aux_music;
    }
    return it->second;
}

void Resources::ClearMusics() {
    for(auto a: musicTable) {
        if(a.second != nullptr) Mix_FreeMusic(a.second);
    }
    musicTable.clear();
}

SDL_Texture* Resources::GetImage(std::string file) {

    auto it = imageTable.find(file);
    if(it == imageTable.end()) {
        SDL_Texture* aux_texture;
        try {
            aux_texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(),file.c_str());
        }
        catch(...) {
            std::cout << "IMG_LoadTexture_ERROR: " << SDL_GetError() << std::endl;
            exit(-4);
        }
        return aux_texture;
    }
    return it->second;
}

void Resources::ClearImages() {
    for(auto a : imageTable) {
        if(a.second != nullptr) SDL_DestroyTexture(a.second);
    }
    imageTable.clear();
}