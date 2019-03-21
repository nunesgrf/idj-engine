#define INCLUDE_SDL

#define PI 3.14159265359

#include "SDL_include.h"
#include "TileMap.hpp"
#include "TileSet.hpp"
#include "Face.hpp"
#include "Vec2.hpp"
#include "State.hpp"
#include "Sprite.hpp"
#include "Sound.hpp"
#include <iostream>

State::State() : quitRequested(false), music("assets/audio/stageState.ogg") {
	std::string background_file = "assets/img/ocean.jpg";
	
	GameObject* go = new GameObject();
	Sprite* sprite = new Sprite(*go,background_file);
    
	go->box.x = 0;
	go->box.y = 0;

	go->AddComponent(sprite);
	
	this->objectArray.emplace_back(go);

	std::string tile_file = "assets/img/tileset.png";
	std::string map_file = "assets/map/tileMap.txt";
	GameObject * tile_go = new GameObject();
	TileSet * tileset = new TileSet(*go,64,64,tile_file);
	TileMap * tilemap = new TileMap(*go,map_file,tileset);

	tile_go->AddComponent(tilemap);
	
	this->objectArray.emplace_back(tile_go);

	music.Play();

}

State::~State() {
    this->objectArray.clear();
}

void State::LoadAssets() {
}

void State::Render() {
	for(auto &a : this->objectArray) {
		a->Render();
	}
}

void State::Update(float dt) {
    //this->quitRequested = SDL_QuitRequested();
	this->Input();
	for(int i = 0; i < this->objectArray.size(); i++) {
		this->objectArray[i]->Update(dt);
	}
	for(int i = 0; i < this->objectArray.size(); i++) {
		if(this->objectArray[i]->IsDead()) {
			this->objectArray.erase(this->objectArray.begin()+i);
		}
	}
}

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::AddObject(int mouseX, int mouseY) {
    std::string img = "assets/img/penguinface.png";
	std::string snd = "assets/audio/boom.wav";

    GameObject* go = new GameObject();
	Sprite* sprite = new Sprite(*go,img);
	Sound* sound = new Sound(*go,snd);
	Face* face = new Face(*go);

	go->box.x = mouseX;
	go->box.y = mouseY;
	go->box.w = sprite->GetWidth();
	go->box.h = sprite->GetHeight();

	go->AddComponent(sprite);
	go->AddComponent(sound);
	go->AddComponent(face);

    this->objectArray.emplace_back(go);
}

void State::Input() {

	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}
