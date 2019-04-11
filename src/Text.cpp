#include "Text.hpp"

#include "Game.hpp"
#include "Camera.hpp"
#include "Resources.hpp"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color):
    Component(associated),
    fontFile(fontFile),
    fontSize(fontSize),
    style(style),  
    text(text),
    color(color),
    texture(texture) { RemakeTexture(); }

void Text::Render() {
    Game &aux = Game::GetInstance();
    SDL_Rect clipRect = {0,0,(int)associated.box.w,(int)associated.box.h};
    SDL_Rect dstrect = clipRect;
    dstrect.x = (int)(associated.box + Camera::pos).x;
    dstrect.y = (int)(associated.box + Camera::pos).y;
    
    SDL_RenderCopyEx(aux.GetRenderer(),texture.get(),&clipRect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
}

void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize= fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if(texture.get() != nullptr) {
        texture = nullptr;
        Resources::ClearFonts();
    }

    SDL_Surface* surf;
    font = Resources::GetFont(fontFile,fontSize);

    switch(style) {
        case TextStyle::SOLID:
            surf = TTF_RenderText_Solid(font.get(),text.c_str(),color);
            break;  
        case TextStyle::SHADED:
            surf = TTF_RenderText_Shaded(font.get(),text.c_str(),color, {0,0,0,255});
            break;
        case TextStyle::BLENDED:
            surf = TTF_RenderText_Blended(font.get(),text.c_str(),color);
            break;
    }

    SDL_Texture* loaded = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surf);
    void (*destructor)(SDL_Texture*) = [](SDL_Texture* loaded)->void {
                SDL_DestroyTexture(loaded);
    };
    texture = std::shared_ptr<SDL_Texture>(loaded,destructor);
    if(surf) {
        associated.box.w = surf->w;
        associated.box.h = surf->h;
        SDL_FreeSurface(surf);
    }
}

bool Text::Is(std::string type) {
    return type == std::string("Text");
}

void Text::Update(float dt) {

}
Text::~Text() {}