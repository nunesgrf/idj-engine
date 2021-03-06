#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.hpp"
#include "TileSet.hpp"
#include <string>
#include <vector>

#define PARALLAX 1

class TileMap : public Component {
    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
        
    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);
        void Start();
        void Load(std::string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();
        bool Is(std::string type);
        void Update(float dt);
};
#endif 