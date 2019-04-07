#include "Collider.hpp"

#ifdef DEBUG
#include "Game.hpp"
#include <SDL2/SDL.h>
#include "Camera.hpp"
#endif

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset): Component(associated), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
    Rect copy;
    Rect &aux = associated.box;

    copy.w = aux.w * scale.x;
    copy.h = aux.h * scale.y;

    copy.x = aux.Center().x - copy.w/2;
    copy.y = aux.Center().y - copy.h/2;

    box = aux + offset.RotateDeg(associated.angleDeg);
}	

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}

bool Collider::Is(std::string type) {
    return type == std::string("Collider");
}

void Collider::Render() {
    #ifdef DEBUG
	Vec2 center( box.Center() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
	#endif // DEBUG
}