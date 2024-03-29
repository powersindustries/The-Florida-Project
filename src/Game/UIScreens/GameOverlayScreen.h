#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <unordered_map>
#include <vector>

#include "Core/UI/UIScreenBase.h"
#include "Core/UI/Types/TextBlockRaw.h"

using namespace UI;

namespace Florida
{

struct RefreshUI
{
    uint32_t m_uiMapIDHash;
    TextBlockRaw m_RefreshText;
    bool m_bActive;
};

class GameOverlayScreen : public UIScreenBase
{
public:
    GameOverlayScreen();
    ~GameOverlayScreen();

    void Initialize() override;

    void Update() override;
    void Draw(SDL_Renderer* renderer) override;

    void OnShow() override;
    void RemoveSelf() override;


public:

    TextBlockRaw m_PickupCooldownText;

    bool m_bShowCooldownUI;

    std::unordered_map<uint32_t, std::vector<RefreshUI>> m_RefreshTextMap;

};
}