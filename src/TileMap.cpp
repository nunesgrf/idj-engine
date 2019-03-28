#include "../include/TileMap.hpp"

#include "Camera.hpp"
#include <fstream>
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet): Component(associated), tileSet(tileSet) {
    this->Load(file);
}

void TileMap::Load(std::string file) {
    FILE * filepointer = fopen(file.c_str(), "r");
    int toPush;

    if(filepointer == nullptr) {
        std::cout << "Open_File_Error: " << file << std::endl;
        exit(-5);
    }
    if(fscanf(filepointer,"%d,%d,%d", &this->mapWidth, &this->mapHeight, &this->mapDepth) != 3) {
        exit(-5);
    }
    fseek(filepointer,1,SEEK_CUR);
    while(!feof(filepointer)) {
        fscanf(filepointer," %d,", &toPush);
        this->tileMatrix.push_back(toPush-1);
    }
    fclose(filepointer);
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    int index = x + (y * this->mapWidth) + (z * this->mapWidth * this->mapHeight);
    return this->tileMatrix[index];
}

void TileMap::Render() {
    associated.box.x = Camera::pos.x;
	associated.box.y = Camera::pos.y;
    for(int i = 0; i < this->mapDepth; i++) {
        this->RenderLayer(i, this->associated.box.x,this->associated.box.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for(int i = 0; i < this->mapWidth; i++) {
        for(int j = 0; j < this->mapHeight; j++) {
            auto y = j*this->tileSet->GetTileHeight()-cameraY-Camera::pos.y*layer*PARALLAX;
            auto x = i*this->tileSet->GetTileWidth()-cameraX-Camera::pos.x*layer*PARALLAX;
            this->tileSet->RenderTile((unsigned)this->At(i,j,layer),x,y);
        }
    }
}

int TileMap::GetWidth() {
    return this->mapWidth;
}

int TileMap::GetHeight() {
    return this->mapHeight;
}

int TileMap::GetDepth() {
    return this->mapDepth;
}

bool TileMap::Is(std::string type) {
    return type == std::string("TileMap");
}

void TileMap::Update(float dt) {
}

void TileMap::Start() {}