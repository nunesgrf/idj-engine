#include "../include/TileSet.hpp"

TileSet::TileSet(GameObject& go, int tileWidth, int tileHeight, std::string file): tileSet(go,file), tileWidth(tileWidth), tileHeight(tileHeight) {
    if(this->tileSet.IsOpen()) {
        this->rows    = this->tileSet.GetHeight() / this->tileHeight;
        this->columns = this->tileSet.GetWidth() / this->tileWidth;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index < rows*columns) {
        int a = this->tileWidth*(index%this->columns);
        int b = this->tileHeight*(index/this->columns);
        this->tileSet.SetClip(a,b,this->tileWidth,this->tileHeight);
        tileSet.Render(x,y);
    }
}

int TileSet::GetTileWidth() {
    return this->tileWidth;
}

int TileSet::GetTileHeight() {
    return this->tileHeight;
}