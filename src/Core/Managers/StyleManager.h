#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>
#include <map>

namespace CoreManagers
{


struct TextBlockStyle
{
    uint32_t m_uiID;
    uint32_t m_uiFont;
    
    SDL_Color m_Color;
    std::string m_sDefaultText;
};


struct ButtonStyle
{
    uint32_t m_uiID;
    uint32_t m_uiFont;
    
    SDL_Color m_HoverColor;
    SDL_Color m_PressedColor;
    SDL_Color m_TextColor;
    SDL_Color m_BaseColor;
    
    
    
    std::string m_sDefaultText;
};



class StyleManager
{
public:
    StyleManager();
    ~StyleManager();

    void InitializeStyleManager();

    inline const TextBlockStyle& GetTextBlockStyle(uint32_t uiStyleID) { return m_TextBlockStyles[uiStyleID]; }
    inline const ButtonStyle& GetButtonStyle(uint32_t uiStyleID) { return m_ButtonStyles[uiStyleID]; }

private:

    SDL_Color ColorStringToSDLColor(const char* string );


private:

    std::string m_sStyleFilepath;

    std::map<uint32_t, TextBlockStyle> m_TextBlockStyles; // ID as hash, TextBlockStyle Data
    std::map<uint32_t, ButtonStyle> m_ButtonStyles; // ID as hash, ButtonStyle Data


};

extern StyleManager g_StyleManager;

}