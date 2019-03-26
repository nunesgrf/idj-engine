#include "Resources.hpp"

#define RESOURCE_ERROR -444
#include <iostream>

std::unordered_map<std::string,MIX_CHUNK*> Resources::soundTable;

MIX_CHUNK* Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);
    
    if(it == soundTable.end()) {
        MIX_CHUNK* aux_chunk;
        try {
            aux_chunk = Mix_LoadWAV(file.c_str());
        } 
        catch(...) { 
            std::cout << "MixLoadWAV_ERROR: " << SDL_GetError() << std::endl;
            exit(RESOURCE_ERROR);
        }
        std::pair<std::string,MIX_CHUNK*> toInsert(file,aux_chunk);
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