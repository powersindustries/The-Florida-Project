#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

namespace Core
{

enum class InputMappings
{
    // Mouse Actions.
    eMouse1,
    eMouse2,
    eMouse3,
    eMouseMotion,

    // Navigation Actions.
    eRight,
    eLeft,
    eUp,
    eDown,
    eRun,

    // Gameplay Actions.
    eInteract,
    eAction,
    eSwitchEquipment,
    eReload,

    // System Actions.
    eESCMenu,
    eTabMenu,

    // Debug Actions.
    eDebug1,
    eDebug2,
    eDebug3,
    eDebug4,

};

struct InputMappingsData
{
    // Debug Keys.
    bool m_F1 = false;
    bool m_F2 = false;
    bool m_F3 = false;
    bool m_F4 = false;
    
    // Mouse Actions.
    bool m_LeftClicked = false;
    bool m_RightClicked = false;
    bool m_MiddleClicked = false;
    bool m_MouseMotion = false;

    // System Keys.
    bool m_Escape = false;
    bool m_Tab = false;

    // Player Keys.
    bool m_UpArrow = false;
    bool m_DownArrow = false;
    bool m_LeftArrow = false;
    bool m_RightArrow = false;
    bool m_W = false;
    bool m_A = false;
    bool m_S = false;
    bool m_D = false;

    bool m_Space = false;

    // Gameplay Keys.
    bool m_E = false;
    bool m_J = false;
    bool m_Q = false;
    bool m_R = false;
};

struct HeldInputMappingsData
{
    InputMappingsData m_InputMappingData;

    // Debug Keys.
    int64_t m_F1Stamp = -1;
    int64_t m_F2Stamp = -1;
    int64_t m_F3Stamp = -1;
    int64_t m_F4Stamp = -1;
    
    // Mouse Actions.
    int64_t m_LeftClickedStamp = -1;
    int64_t m_RightClickedStamp = -1;
    int64_t m_MiddleClickedStamp = -1;

    // System Keys.
    int64_t m_EscapeStamp = -1;
    int64_t m_TabStamp = -1;

    // Player Keys.
    int64_t m_UpArrowStamp = -1;
    int64_t m_DownArrowStamp = -1;
    int64_t m_LeftArrowStamp = -1;
    int64_t m_RightArrowStamp = -1;
    int64_t m_WStamp = -1;
    int64_t m_AStamp = -1;
    int64_t m_SStamp = -1;
    int64_t m_DStamp = -1;

    int64_t m_SpaceStamp = -1;

    // Gameplay Keys.
    int64_t m_EStamp = -1;
    int64_t m_JStamp = -1;
    int64_t m_QStamp = -1;
    int64_t m_RStamp = -1;
};

struct MouseMotionData
{
    int8_t m_iMotionX = 0;
    int8_t m_iMotionY = 0;
};

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void ProcessInputs();

    bool GetActionPressed(const InputMappings Mapping);
    bool GetActionHeld(const InputMappings Mapping);
    int64_t GetActionHeldTimestamp(const InputMappings Mapping);

    const MouseMotionData& GetMouseMotionData() const { return m_MouseMotionData; }

    bool GetMouseClickAbsorbedByUI() const { return m_bMouseClickAbsorbedByUI; };
    void SetMouseClickAbsorbedByUI(bool bAbsorbed) { m_bMouseClickAbsorbedByUI = bAbsorbed; };


private:

    void ResetAllPressedData();

    void OnKeyUpEvent();
    void OnMouseEvent();
    void OnKeyDownEvent();


private:

    SDL_Event* m_SDLEvent;

    InputMappingsData m_InputMappingPressedData;
    HeldInputMappingsData m_InputMappingHeldData;

    MouseMotionData m_MouseMotionData;

    bool m_bMouseClickAbsorbedByUI;
};

extern InputManager g_InputManager;
}
