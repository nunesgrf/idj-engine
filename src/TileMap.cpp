#include "../include/TileMap.hpp"

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
    int index = x + (y * this->mapWidth) + (z * this->mapWidth * mapHeight);
    return this->tileMatrix[index];
}

void TileMap::Render() {

}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {

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
