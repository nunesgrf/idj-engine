#include "TileSet.hpp"

TileSet::TileSet(GameObject& go, int tileWidth, int tileHeight, std::string file): tileSet(go,file), tileWidth(tileWidth), tileHeight(tileHeight) {
    if(tileSet.IsOpen()) {
        rows    = tileSet.GetHeight() / tileHeight;
        columns = tileSet.GetWidth() / tileWidth;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index < rows*columns) {
        int a = tileWidth*(index%columns);
        int b = tileHeight*(index/columns);
        tileSet.SetClip(a,b,tileWidth,tileHeight);
        tileSet.Render(x,y);
    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}