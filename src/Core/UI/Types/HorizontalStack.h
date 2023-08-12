#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <vector>

#include "../UICore.h"

namespace UI
{

class HorizontalStack : public UIBase
{
public:
    HorizontalStack();
    ~HorizontalStack();

    void Draw(SDL_Renderer* renderer) override;
    void SetStyle(uint32_t uiStyleID) override;
    void SetOffset(int xOffset, int yOffset) override;

    void RefreshUI() override;

    void AddChild(UIBase* child);
    void ClearChildren();

    void SetVisibility(UIVisibility visibility) override;
    void SetPadding(int padding);


private:

    void SetPositionNoRefresh(const int x, const int y) override;


public:

	std::vector<UIBase*> m_Children;

	int m_iPadding;

};
}