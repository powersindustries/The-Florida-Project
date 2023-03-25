#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <vector>

#include "../UICoreTypes.h"

namespace CoreUI
{

class VerticalStack : public UIBase
{
public:
    VerticalStack();
    ~VerticalStack();

    void Draw(SDL_Renderer* renderer);
    void SetStyle(uint32_t uiStyleID);
    void SetOffset(int xOffset, int yOffset);

    void RefreshUI();

    void AddChild(UIBase* child);
    void ClearChildren();

    void SetVisibility(UIVisibility visibility);
    void SetPadding(int padding);

private:

    void SetPositionNoRefresh(const int x, const int y);


public:

	std::vector<UIBase*> m_Children;

	int m_iPadding;

};
}