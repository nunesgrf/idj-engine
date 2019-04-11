#ifndef TEXT_H
#define TEXT_H

#define INCLUDE_SDL_TTF 
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>

class Text : public Component {
    public:
        enum TextStyle{SOLID, SHADED, BLENDED};
        Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
        ~Text();

        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void SetText(std::string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontSize(int fontSize);
        void SetFontfile(std::string fontFile);

    private:
        std::shared_ptr<TTF_Font> font;
        std::shared_ptr<SDL_Texture> texture;

        std::string text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color;

        void RemakeTexture();
};
#endif