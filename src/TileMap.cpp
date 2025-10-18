#include "TileMap.h"
#include <fstream>
#include <iostream>
#include <sstream> // biblioteca que contém tipo std::stringstream

TileMap::TileMap (GameObject& associated, std::string file, TileSet* tileSet) : Component(associated) {
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load (std::string file){
    std::ifstream input(file); // abre arquivo

    if (!input.is_open()) {
        std::cout << "Arquivo não foi aberto" << std::endl;
        return;
    }
    std::string linha;
    std::getline(input, linha); // pega linha do arquivo

    std::stringstream fluxo(linha); // transforma linha em um fluxo (stream)

    // pegar 3 valores iniciais
    std::string value;

    std::getline(fluxo, value, ','); // atribui a value valor até antes de uma vírgula a partir de um fluxo
    mapWidth = std::stoi(value);

    std::getline(fluxo, value, ',');
    mapHeight = std::stoi(value);

    std::getline(fluxo, value, ',');
    mapDepth = std::stoi(value);

    tileMatrix.clear(); // limpa matriz

    while (std::getline(input, linha)) { // percorre restante das linhas
        fluxo.clear();  // limpa flags
        fluxo.str(linha); // pega fluxo da nova linha

        while (std::getline(fluxo, value, ',')){ // percorre o fluxo da linha
            tileMatrix.push_back(std::stoi(value)); // adiciona value a matriz
        }
    }

    input.close(); // fecha arquivo
}

void TileMap::SetTileSet (TileSet* tileSet){
    this->tileSet = std::unique_ptr<TileSet>(tileSet); // cria objeto unique_ptr<TileSet> que guarda tileSet
    // atualiza unique_ptr<TileSet> do objeto TileMap com o novo obj criado
}

int& TileMap::At (int x, int y, int z){
    int indice = x + (y * mapWidth) + (z * mapWidth * mapHeight); // transforma vetor 3D em 1D
    return tileMatrix[indice];
}

void TileMap::Render (){
    for (int index = 0; index < mapDepth; index++) {
        RenderLayer(index);
    }
}

void TileMap::RenderLayer (int layer){
    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapHeight; y++) {
            // posição do tile no mapa
            int tilex = x * tileSet->GetTileWidth();
            int tiley = y * tileSet->GetTileHeight();

            // posição do tile no mapa adicionado a posição relativa da box
            tileSet->RenderTile(At(x, y, layer), tilex + associated.box.x, tiley + associated.box.y);
        }
    }
}

int TileMap::GetWidth (){
    return mapWidth;
}

int TileMap::GetHeight (){
    return mapHeight;
}

int TileMap::GetDepth (){
    return mapDepth;
}

void TileMap::Update (float dt){}
