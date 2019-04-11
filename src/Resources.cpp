#include "Resources.hpp"

#include "Game.hpp"
#include <iostream>

std::unordered_map<std::string,std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string,std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string,std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string,std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {    
    if(soundTable.find(file) == soundTable.end()) {
        try {
            Mix_Chunk* loaded = Mix_LoadWAV(file.c_str());
            void (*destructor)(Mix_Chunk*) = [](Mix_Chunk* loaded)->void {
                Mix_FreeChunk(loaded);
            };
            std::shared_ptr<Mix_Chunk> smart_ptr = std::shared_ptr<Mix_Chunk>(loaded, destructor);
            soundTable.emplace(file,smart_ptr);
        } 
        catch(...) { 
            std::cout << "MixLoadWAV_ERROR: " << SDL_GetError() << std::endl;
            exit(-4);
        }       
    }
    return (*soundTable.find(file)).second;
}

void Resources::ClearSounds() {
    for(auto a : soundTable) {
        if(a.second.unique()) {
            soundTable.erase(a.first);
        }
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    if(musicTable.find(file) == musicTable.end()) {
        try {
            Mix_Music* loaded = Mix_LoadMUS(file.c_str());
            void (*destructor)(Mix_Music*) = [](Mix_Music* loaded)->void {
                Mix_FreeMusic(loaded);
            };
            std::shared_ptr<Mix_Music> smart_ptr = std::shared_ptr<Mix_Music>(loaded,destructor);
            musicTable.emplace(file,smart_ptr);
        }
        catch(...) {
            std::cout << "MixLoadMUS_ERROR: " << SDL_GetError() << std::endl;
            exit(-4);
        }
    }
    return (*musicTable.find(file)).second;
}

void Resources::ClearMusics() {
    for(auto a: musicTable) {
        if(a.second.unique()) {
            musicTable.erase(a.first);
        }
    }
}

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    if(imageTable.find(file) == imageTable.end()) {
        try {
            SDL_Texture* loaded = IMG_LoadTexture(Game::GetInstance().GetRenderer(),file.c_str());
            void (*destructor)(SDL_Texture*) = [](SDL_Texture* loaded)->void {
                SDL_DestroyTexture(loaded);
            };
            std::shared_ptr<SDL_Texture> smart_ptr = std::shared_ptr<SDL_Texture>(loaded,destructor);
            imageTable.emplace(file,smart_ptr);
        }
        catch(...) {
            std::cout << "IMG_LoadTexture_ERROR: " << SDL_GetError() << std::endl;
            exit(-4);
        }
    }
    return (*imageTable.find(file)).second;
}

void Resources::ClearImages() {
    for(auto a : imageTable) {
       if(a.second.unique()) {
           imageTable.erase(a.first);
       }
    }
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int ptsize) {
    if(fontTable.find(file) == fontTable.end()) {
        try {
            TTF_Font* loaded = TTF_OpenFont(file.c_str(),ptsize);
            void (*destructor)(TTF_Font*) = [](TTF_Font* loaded)->void {
                std::cout << "Olá" << std::endl;
                TTF_CloseFont(loaded);
            };
            std::shared_ptr<TTF_Font> smart_ptr = std::shared_ptr<TTF_Font>(loaded,destructor);
            fontTable.emplace(file + std::to_string(ptsize), smart_ptr);
        }
        catch(...) {
            std::cout << "TTF_LoadFont_ERROR: " << SDL_GetError() << std::endl;
            exit(-4);
        }
    }
    return (*fontTable.find(file + std::to_string(ptsize))).second;
}

void Resources::ClearFonts() {
    for(auto a : fontTable) {
        if(a.second.unique()) {
            fontTable.erase(a.first);
        }
    }
}



