#ifndef TILESET_H
#define TILESET_H

#include <string>

class TileSet {
    private:
        //Sprite tileSet 
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;
    
    public:
        TileSet(int tileWidth, int tileHeight, std::string file);
        void RenderTile(unsigned index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();
};
#endif 