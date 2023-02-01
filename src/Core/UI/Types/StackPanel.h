#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <vector>

#include "../UICoreTypes.h"
#include "Core/Math/VectorMethods.h"

namespace CoreUI
{


enum class StackpanelAlignment
{
    eHorizontal,
    eVertical
};


class StackPanel : public UIBase
{
public:
    StackPanel();
    ~StackPanel();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void SetPosition(int x, int y);
    void RefreshUI();

    void SetDisplayType(DisplayType displayType);

    void AddChild(UIBase* child);
    void SetChildAlignment(StackpanelAlignment alignment);
    void SetPadding(int padding);

    void ClearChildren();

    const std::vector<UIBase*> GetChilren() { return m_Children; };
    uint32_t GetChildrenCount() { return static_cast<uint32_t>(m_Children.size()); }


public:

    std::vector<UIBase*> m_Children;


private:

    int m_iPadding;

    StackpanelAlignment m_Alignment;

};

}