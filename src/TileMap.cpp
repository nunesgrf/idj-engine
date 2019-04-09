#include "TileMap.hpp"

#include <fstream>
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet): Component(associated), tileSet(tileSet) {
    Load(file);
}

void TileMap::Load(std::string file) {
    FILE * filepointer = fopen(file.c_str(), "r");
    int toPush;

    if(filepointer == nullptr) {
        std::cout << "Open_File_Error: " << file << std::endl;
        exit(-5);
    }
    if(fscanf(filepointer,"%d,%d,%d", &mapWidth, &mapHeight, &mapDepth) != 3) {
        exit(-5);
    }
    fseek(filepointer,1,SEEK_CUR);
    while(!feof(filepointer)) {
        fscanf(filepointer," %d,", &toPush);
        tileMatrix.push_back(toPush-1);
    }
    fclose(filepointer);
}

void TileMap::SetTileSet(TileSet* tileSet) {
    tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
    return tileMatrix[index];
}

void TileMap::Render() {

    for(int i = 0; i < mapDepth; i++) {
        RenderLayer(i, associated.box.x,associated.box.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for(int i = 0; i < mapWidth; i++) {
        for(int j = 0; j < mapHeight; j++) {
            tileSet->RenderTile((unsigned)At(i,j,layer),i*tileSet->GetTileWidth(), j*tileSet->GetTileHeight());
        }
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

bool TileMap::Is(std::string type) {
    return type == std::string("TileMap");
}

void TileMap::Update(float dt) {
}
