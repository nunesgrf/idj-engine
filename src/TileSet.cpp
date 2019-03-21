#include "../include/TileSet.hpp"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file): tileWidth(tileWidth), tileHeight(tileHeight) {
    //to modify 
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    
}

int TileSet::GetTileWidth() {
    return this->tileWidth;
}

int TileSet::GetTileHeight() {
    return this->tileHeight;
}