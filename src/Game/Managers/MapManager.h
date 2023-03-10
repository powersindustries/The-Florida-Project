#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>
#include <unordered_map>

#include "Core/Types/Sprite.h"
#include "GameGlobals.h"
#include "Core/Utility/VectorMethods.h"


namespace Florida
{


enum class InteractionType
{
    ePickup,
    eRefresh,
    eStory,
    eNONE
};


struct PickupData
{
    bool m_bActive = true;
    
    SDL_Rect m_Rectangle;
    uint8_t m_uiPadding = 5;

    InteractionType m_Type;

    uint8_t m_uiPickupTime;

    uint32_t m_uiItem;
    uint32_t m_uiAmount;

    CoreTypes::Sprite* m_Sprite = nullptr;

};


struct RefreshData
{
    bool m_bActive = true;
   
    uint32_t m_uiMapIDHash;

    SDL_Rect m_Rectangle;
    uint8_t m_uiPadding = 5;

    InteractionType m_Type;

    uint8_t m_uiPickupTime; // Time for player to hold button
    uint8_t m_uiRefreshTime; // Time it takes for resource to refresh

    float m_fGatheredTimestamp; // Game Timestamp when the resource was collected

    uint32_t m_uiItem;
    uint32_t m_uiAmount;

    CoreTypes::Sprite* m_Sprite = nullptr;
};


struct StoryData
{
    bool m_bActive = true;
    
    SDL_Rect m_Rectangle;
    uint8_t m_uiPadding = 5;

    InteractionType m_Type;
};


struct CollisionData
{
    SDL_Rect m_Rectangle;
    uint8_t m_uiPadding = 5;
};


struct NavigationData
{
    SDL_Rect m_Rectangle;
    uint8_t m_uiPadding = 5;
    CoreUtility::Vec2i m_vUpPosition;
    CoreUtility::Vec2i m_vDownPosition;
};


struct MapData
{
    std::string m_sID;
    uint32_t m_uiIDHash;

    CoreUtility::Vec2i m_vPlayerStartPosition;

    // Background
    SDL_Color m_BackgroundColor;
    SDL_Rect m_BackgroundRectangle;

    SDL_Texture* m_BackgroundTextureDay = nullptr;
    SDL_Texture* m_BackgroundTextureNight = nullptr;

    // Navigations
    std::vector<NavigationData> m_Navigations;

    // Enemy Spawners
    std::vector<uint32_t> m_EnemySpawners;

    // Interactions
    std::vector<PickupData*> m_PickupVector;
    std::vector<RefreshData*> m_RefreshVector;
    std::vector<StoryData*> m_StoryVector;

    // Collisions
    std::vector<CollisionData> m_Collisions;

};


class MapManager
{
public:
    MapManager();
    ~MapManager();

    void InitialLoad();
    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    void LoadMapByID(uint32_t uiMapIDHash);
    bool CollisionStoppingMovement(SDL_Rect& inRect, Direction& inDirection);
    void ResetMapManager();


private:

   void LoadMapData(std::string sMapPath);

   InteractionType StringToInteractionType(const std::string& string);


public:

    MapData* m_ActiveMap;


private:

    SDL_Rect m_BackgroundRectangle;

    std::vector<MapData> m_MapDataVector;
    std::unordered_map<uint32_t, uint32_t> m_MapDataMap; // ID has, index to m_MapDataVector

    std::string m_sMapManifestPath;
    std::string m_sMapDirectoryPath;

};

extern MapManager g_MapManager;
}
