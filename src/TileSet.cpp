#include "TileSet.h"
#include <iostream>

TileSet::TileSet (int tileWidth, int tileHeight, std::string file) : tileSet(file, 1, 1){
    if (tileSet.IsOpen()){
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        int largura = tileSet.GetWidth();
        int altura = tileSet.GetHeight();

        int frameCountW = largura / tileWidth;
        int frameCountH = altura / tileHeight;

        tileSet.SetFrameCount(frameCountW, frameCountH);
        this->tileCount = frameCountW * frameCountH;
    } else {
        std::cout << "tileSet não foi aberto" << std::endl;
    }
}
void TileSet::RenderTile (unsigned index, float x, float y){
    if (index < 0 || index >= tileCount) {
        std::cout << "Tile inválido: " << index << std::endl;
        return;
    }
    if ((index >= 0) && (index <= tileCount-1)) {
        tileSet.SetFrame(index);
        tileSet.Render(x, y, tileWidth, tileHeight);
    }
}
int TileSet::GetTileWidth (){
    return tileWidth;
}
int TileSet::GetTileHeight(){
    return tileHeight;
}

int TileSet::GetTileCount() const {
    return tileCount;
}
