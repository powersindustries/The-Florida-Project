#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image


namespace UI
{

enum class UIScreenID
{
    eDEFAULT,

	eHud,
	eInventory,
	ePause,
	eGameOver,
	eIntro,
	eControls
};

class UIScreenBase
{
public:

    virtual void Initialize() = 0;

    virtual void Update() = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;

    virtual void OnShow() = 0;
    virtual void RemoveSelf() = 0;


public:

    UIScreenID m_ScreenID;

};

}