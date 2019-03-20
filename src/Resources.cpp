#include "../include/Resources.hpp"

#include <iostream>

std::unordered_map<std::string,Mix_Chunk*> Resources::soundTable;

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