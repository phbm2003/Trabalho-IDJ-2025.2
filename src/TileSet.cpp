#include "TileSet.h"
#include <iostream>

TileSet::TileSet (int tileWidth, int tileHeight, std::string file) : tileSet(file, 1, 1){
    if (tileSet.IsOpen()){
        std::cout << "TileSet carregado com sucesso: " << file << std::endl;
        std::cout << "tileWidth: " << tileWidth << std::endl;
        std::cout << "tileHeight: " << tileHeight << std::endl;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        int largura = tileSet.GetWidth();
        int altura = tileSet.GetHeight();

        std::cout << "Largura: " << largura << "\n" << std::endl;
        std::cout << "Largura: " << altura << "\n" << std::endl;

        int frameCountW = largura / tileWidth;
        int frameCountH = altura / tileHeight;

        tileSet.SetFrameCount(frameCountW, frameCountH);
        this->tileCount = frameCountW * frameCountH;
    } else {
        std::cout << "tileSet não foi aberto" << std::endl;
    }
}
void TileSet::RenderTile (unsigned index, float x, float y){
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
