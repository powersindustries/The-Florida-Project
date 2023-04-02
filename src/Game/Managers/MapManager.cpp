#include "MapManager.h"

#include "GameManager.h"
#include "UIManager.h"
#include "EnemyManager.h"
#include "AssetManager.h"
#include "GameplayManager.h"
#include "../Player/Player.h"
#include "Core/Systems/Logging.h"
#include "Core/Systems/Hash.h"
#include "Core/Managers/SettingsManager.h"
#include "ItemManager.h"
#include "Core/Utility/Utility.h"
#include "Core/Types/LuaTableLoader.h"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
MapManager g_MapManager;


// -------------------------------------------------------
// -------------------------------------------------------
MapManager::MapManager()
    : m_ActiveMap(nullptr)
{
    m_sMapManifestPath.append(__PROJECT_DIRECTORY__);
    m_sMapManifestPath.append("/src/Data/MapsManifest.lua");

    m_sMapDirectoryPath.append(__PROJECT_DIRECTORY__);
    m_sMapDirectoryPath.append("/src/Data/Maps/");

    m_BackgroundRectangle.x = 0;
    m_BackgroundRectangle.y = 0;
    m_BackgroundRectangle.w = Core::g_SettingsManager.GetScreenWidth();
    m_BackgroundRectangle.h = Core::g_SettingsManager.GetScreenHeight();
}


// -------------------------------------------------------
// -------------------------------------------------------
MapManager::~MapManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::InitialLoad()
{
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(m_sMapManifestPath);

	// Load Textures table.
	luaLoader->LoadTableByID("Maps");

	const uint8_t uiMapsTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiMapsTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

        std::string sMapID = m_sMapDirectoryPath;
        sMapID.append(luaLoader->GetStringByID("Path"));
        LoadMapData(sMapID);

		luaLoader->PopTopTableElement();
    }

    delete luaLoader;


    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Map data Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapData(std::string sMapPath)
{
    LuaTableLoader* luaLoader = new LuaTableLoader(sMapPath);

    luaLoader->LoadTableByID("Settings");


    MapData newMapData;
    newMapData.m_uiID = Core::StringToHash32(luaLoader->GetStringByID("ID"));

    newMapData.m_BackgroundColor.r = luaLoader->GetIntByID("BackgroundR");
    newMapData.m_BackgroundColor.g = luaLoader->GetIntByID("BackgroundG");
    newMapData.m_BackgroundColor.b = luaLoader->GetIntByID("BackgroundB");
    newMapData.m_BackgroundColor.a = luaLoader->GetIntByID("BackgroundA");

    newMapData.m_BackgroundRectangle.x = 0;
    newMapData.m_BackgroundRectangle.y = 0;
    newMapData.m_BackgroundRectangle.w = Core::g_SettingsManager.GetScreenWidth();
    newMapData.m_BackgroundRectangle.h = Core::g_SettingsManager.GetScreenHeight();

    newMapData.m_vPlayerStartPosition.m_X = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("PlayerX"));
    newMapData.m_vPlayerStartPosition.m_Y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("PlayerY"));

    std::string sNightTextureID = luaLoader->GetStringByID("BackgroundTextureNight");
    uint32_t uiNightTextureIDHash = Core::StringToHash32(sNightTextureID);

    std::string sDayTextureID = luaLoader->GetStringByID("BackgroundTextureDay");
    uint32_t uiDayTextureIDHash = Core::StringToHash32(sDayTextureID);

    newMapData.m_BackgroundTextureDay = g_AssetManager.m_TextureAssets[uiDayTextureIDHash].m_Texture;
    newMapData.m_BackgroundTextureNight = g_AssetManager.m_TextureAssets[uiNightTextureIDHash].m_Texture;

    // Load Navigations
    luaLoader->LoadTableByID("Navigations");

    const uint8_t uiNavigationsSize = luaLoader->GetCurrentTableSize();
    for (uint8_t x=0; x < uiNavigationsSize; ++x)
    {
        int indexOffset = x + 1;

        if (luaLoader->PushIntegerAndGetTable(indexOffset))
        {
            break;
        }


        NavigationData newNavigation;
        newNavigation.m_Rectangle.x = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("x"));
        newNavigation.m_Rectangle.y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("y"));

        newNavigation.m_Rectangle.w = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("w"));
        newNavigation.m_Rectangle.h = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("h"));

        newNavigation.m_uiPadding = luaLoader->GetIntByID("Padding");

        newNavigation.m_vUpPosition.m_X = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("UpX"));
        newNavigation.m_vUpPosition.m_Y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("UpY"));

        newNavigation.m_vDownPosition.m_X = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("DownX"));
        newNavigation.m_vDownPosition.m_Y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("DownY"));

        newMapData.m_Navigations.push_back(newNavigation);

        luaLoader->PopTopTableElement();
    }

    // Load Collisions
	luaLoader->LoadTableByID("Collisions");

	const uint8_t uiCollisionsSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiCollisionsSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}


        CollisionData newCollision;
        newCollision.m_Rectangle.x = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("x"));
        newCollision.m_Rectangle.y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("y"));

        newCollision.m_Rectangle.w = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("w"));
        newCollision.m_Rectangle.h = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("h"));

        newCollision.m_uiPadding = luaLoader->GetIntByID("Padding");

        newMapData.m_Collisions.push_back(newCollision);

		luaLoader->PopTopTableElement();
    }

    // Load Enemies
	luaLoader->LoadTableByID("EnemySpawners");

	const uint8_t uiSpawnerSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiSpawnerSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}


        EnemySpawnerData newEnemy;
        newEnemy.m_uiMapIDHash = newMapData.m_uiID;

        newEnemy.m_Rectangle.x = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("x"));
        newEnemy.m_Rectangle.y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("y"));
        newEnemy.m_Rectangle.w = 25;
        newEnemy.m_Rectangle.h = 50;

        g_EnemyManager.m_EnemySpawnerVector.push_back(newEnemy);

        const uint32_t uiEnemiesVectorSize = static_cast<uint32_t>(g_EnemyManager.m_EnemySpawnerVector.size()) - 1;
        g_EnemyManager.m_EnemySpawnerMap.insert({ newEnemy.m_uiMapIDHash, uiEnemiesVectorSize });

        newMapData.m_EnemySpawners.push_back(uiEnemiesVectorSize);

		luaLoader->PopTopTableElement();
    }

    // Load Interactions
	luaLoader->LoadTableByID("Interactions");

	const uint8_t uiInteractionsSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiInteractionsSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}


        const InteractionType currInteractionType = StringToInteractionType(luaLoader->GetStringByID("Type"));
        if (currInteractionType != InteractionType::eNONE)
        {
            switch (currInteractionType)
            {
            case InteractionType::ePickup:
            {
                PickupData* newPickupInteraction = new PickupData;
                newPickupInteraction->m_Type = currInteractionType;

                newPickupInteraction->m_Rectangle.x = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("x"));
                newPickupInteraction->m_Rectangle.y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("y"));
                newPickupInteraction->m_Rectangle.w = luaLoader->GetIntByID("w");
                newPickupInteraction->m_Rectangle.h = luaLoader->GetIntByID("h");
                newPickupInteraction->m_uiPadding = luaLoader->GetIntByID("Padding");

                newPickupInteraction->m_uiPickupTime = luaLoader->GetIntByID("PickupTime");

                newPickupInteraction->m_uiItem = Core::StringToHash32(luaLoader->GetStringByID("Item"));
                newPickupInteraction->m_uiAmount = luaLoader->GetIntByID("Amount");

                newPickupInteraction->m_Sprite = new Sprite(Core::StringToHash32(luaLoader->GetStringByID("Texture")), g_GameGlobals.ITEM_ANIMATION_SPEED);

                newMapData.m_PickupVector.push_back(newPickupInteraction);

                break;
            }
            case InteractionType::eRefresh:
            {
                RefreshData* newRefreshInteraction = new RefreshData;
                newRefreshInteraction->m_Type = currInteractionType;
                newRefreshInteraction->m_uiMapIDHash = newMapData.m_uiID;

                newRefreshInteraction->m_Rectangle.x = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("x"));
                newRefreshInteraction->m_Rectangle.y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("y"));
                newRefreshInteraction->m_Rectangle.w = luaLoader->GetIntByID("w");
                newRefreshInteraction->m_Rectangle.h = luaLoader->GetIntByID("h");
                newRefreshInteraction->m_uiPadding = luaLoader->GetIntByID("Padding");

                newRefreshInteraction->m_uiPickupTime = luaLoader->GetIntByID("PickupTime");
                newRefreshInteraction->m_uiRefreshTime = luaLoader->GetIntByID("RefreshTime");

                newRefreshInteraction->m_uiItem = Core::StringToHash32(luaLoader->GetStringByID("Item"));
                newRefreshInteraction->m_uiAmount = luaLoader->GetIntByID("Amount");

                newRefreshInteraction->m_Sprite = new Sprite(Core::StringToHash32(luaLoader->GetStringByID("Texture")), g_GameGlobals.ITEM_ANIMATION_SPEED);
                
                newMapData.m_RefreshVector.push_back(newRefreshInteraction);

                g_UIManager.AddNewRefreshUI(newMapData.m_uiID, newRefreshInteraction->m_Rectangle.x, newRefreshInteraction->m_Rectangle.y);

                break;
            }
            case InteractionType::eStory:
            {
                StoryData* newStoryInteraction = new StoryData;
                newStoryInteraction->m_Type = currInteractionType;

                newStoryInteraction->m_Rectangle.y = Core::g_SettingsManager.GetRelativeScreenY(luaLoader->GetIntByID("y"));
                newStoryInteraction->m_Rectangle.x = Core::g_SettingsManager.GetRelativeScreenX(luaLoader->GetIntByID("x"));
                newStoryInteraction->m_Rectangle.w = luaLoader->GetIntByID("w");
                newStoryInteraction->m_Rectangle.h = luaLoader->GetIntByID("h");
                newStoryInteraction->m_uiPadding = luaLoader->GetIntByID("Padding");

                newMapData.m_StoryVector.push_back(newStoryInteraction);

                break;
            }
            default:
            {
                break;
            }
            }
        }

		luaLoader->PopTopTableElement();
    }

    delete luaLoader;

    m_MapDataVector.push_back(newMapData);

    const uint32_t uiMapDataVectorSize = static_cast<uint32_t>(m_MapDataVector.size()) - 1;
    m_MapDataMap.insert({ newMapData.m_uiID, uiMapDataVectorSize });
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::Update(float deltaTime)
{
    if (!m_ActiveMap)
    {
        return;
    }

    const uint32_t uiNavigationSize = static_cast<uint32_t>(m_ActiveMap->m_Navigations.size());
    for (uint32_t x = 0; x < uiNavigationSize; ++x)
    {
        NavigationData& currNavigation = m_ActiveMap->m_Navigations[x];

        if (Core::Utility::CollisionBetweenTwoRectanglesWithPadding(currNavigation.m_Rectangle, g_Player.GetPlayerRectangle(), currNavigation.m_uiPadding) &&
            (Core::g_InputManager.GetActionHeld(Core::InputMappings::eUp) || Core::g_InputManager.GetActionHeld(Core::InputMappings::eDown)))
        {
            SDL_Rect& playerRect = g_Player.GetPlayerRectangle();
            int yOffsetTop = currNavigation.m_Rectangle.y - playerRect.y;
            int yOffsetBottom = (currNavigation.m_Rectangle.y + currNavigation.m_Rectangle.h) - playerRect.y;

            if (Core::g_InputManager.GetActionHeld(Core::InputMappings::eUp) && yOffsetBottom > 0 && yOffsetBottom < 50)
            {
                g_Player.SetPlayerPosition(currNavigation.m_vUpPosition.m_X, currNavigation.m_vUpPosition.m_Y);
            }
            else if (Core::g_InputManager.GetActionHeld(Core::InputMappings::eDown) && yOffsetTop > 0 && yOffsetTop < 50)
            {
                g_Player.SetPlayerPosition(currNavigation.m_vDownPosition.m_X, currNavigation.m_vDownPosition.m_Y);
            }
        }
    }

    const uint32_t uiPickupsSize = static_cast<uint32_t>(m_ActiveMap->m_PickupVector.size());
    for (uint32_t x = 0; x < uiPickupsSize; ++x)
    {
        PickupData* currPickup = m_ActiveMap->m_PickupVector[x];
        if (currPickup->m_bActive)
        {
            currPickup->m_Sprite->Update(deltaTime, currPickup->m_Rectangle);
        }
    }

    for (uint32_t x = 0; x < uiPickupsSize; ++x)
    {
        PickupData* currPickup = m_ActiveMap->m_PickupVector[x];
        if (currPickup->m_bActive &&
            Core::Utility::CollisionBetweenTwoRectanglesWithPadding(currPickup->m_Rectangle, g_Player.GetPlayerRectangle(), currPickup->m_uiPadding) &&
            g_Player.GetInteractState().m_bHeld)
        {
            uint16_t uiCountdown = currPickup->m_uiPickupTime - static_cast<uint16_t>(deltaTime - g_Player.GetInteractState().m_fTime);

            g_UIManager.UpdatePickupUI(
                true,
                uiCountdown,
                currPickup->m_Rectangle.x + (currPickup->m_Rectangle.w / 2),
                currPickup->m_Rectangle.y - currPickup->m_Rectangle.h
            );

            if (deltaTime >= (g_Player.GetInteractState().m_fTime + currPickup->m_uiPickupTime))
            {
                g_ItemManager.AddItem(currPickup->m_uiItem, currPickup->m_uiAmount);
                m_ActiveMap->m_PickupVector[x]->m_bActive = false;
            }
        
            break;
        }
        else
        {
            g_UIManager.UpdatePickupUI(false, 0, 0, 0);
        }
    }

    const uint32_t uiRefreshSize = static_cast<uint32_t>(m_ActiveMap->m_RefreshVector.size());
    for (uint32_t x = 0; x < uiRefreshSize; ++x)
    {
        RefreshData* currRefresh = m_ActiveMap->m_RefreshVector[x];

        if (!currRefresh->m_bActive)
        {
            const uint8_t uiRefreshTime = static_cast<uint8_t>(currRefresh->m_fGatheredTimestamp) + currRefresh->m_uiRefreshTime;
            const uint8_t uiCooldownTime = static_cast<uint8_t>((currRefresh->m_fGatheredTimestamp + currRefresh->m_uiRefreshTime) - deltaTime);
            g_UIManager.UpdateRefreshUI(true, x, uiCooldownTime);

            if (deltaTime >= uiRefreshTime)
            {
                currRefresh->m_bActive = true;
                break;
            }
        }
        else
        {
            g_UIManager.UpdateRefreshUI(false, x, 0);

            currRefresh->m_Sprite->Update(deltaTime, currRefresh->m_Rectangle);
        }


        if (currRefresh->m_bActive && Core::Utility::CollisionBetweenTwoRectanglesWithPadding(currRefresh->m_Rectangle, g_Player.GetPlayerRectangle(), currRefresh->m_uiPadding))
        {
            g_ItemManager.AddItem(currRefresh->m_uiItem, currRefresh->m_uiAmount);
            m_ActiveMap->m_RefreshVector[x]->m_bActive = false;

            currRefresh->m_fGatheredTimestamp = deltaTime;
        }
    }

    const uint32_t uiStorySize = static_cast<uint32_t>(m_ActiveMap->m_StoryVector.size());
    for (uint32_t x = 0; x < uiStorySize; ++x)
    {
        StoryData* currStory = m_ActiveMap->m_StoryVector[x];
        if (currStory->m_bActive && Core::Utility::CollisionBetweenTwoRectanglesWithPadding(currStory->m_Rectangle, g_Player.GetPlayerRectangle(), currStory->m_uiPadding))
        {
            Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Story interaction!");
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::Draw(SDL_Renderer* renderer)
{
    if (m_ActiveMap)
    {
        SDL_SetRenderDrawColor(renderer, m_ActiveMap->m_BackgroundColor.r,
            m_ActiveMap->m_BackgroundColor.g,
            m_ActiveMap->m_BackgroundColor.b,
            g_GameplayManager.GetDayNightValue() == DayNightValues::eDay ? (m_ActiveMap->m_BackgroundColor.a / 2) : m_ActiveMap->m_BackgroundColor.a);

        SDL_RenderFillRect(renderer, &m_ActiveMap->m_BackgroundRectangle);

        if (g_GameplayManager.GetDayNightValue() == DayNightValues::eDay)
        {
            SDL_RenderCopyEx(renderer, m_ActiveMap->m_BackgroundTextureDay, NULL, &m_ActiveMap->m_BackgroundRectangle, 0.0, NULL, SDL_FLIP_NONE);
        }
        else
        {
            SDL_RenderCopyEx(renderer, m_ActiveMap->m_BackgroundTextureNight, NULL, &m_ActiveMap->m_BackgroundRectangle, 0.0, NULL, SDL_FLIP_NONE);
        }

        const uint16_t uiNavigationsSize = static_cast<uint16_t>(m_ActiveMap->m_Navigations.size());
        for (uint16_t x = 0; x < uiNavigationsSize; ++x)
        {
            SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_WHITE.r, g_GameGlobals.COLOR_WHITE.g, g_GameGlobals.COLOR_WHITE.b, g_GameGlobals.COLOR_WHITE.a);
            SDL_RenderFillRect(renderer, &m_ActiveMap->m_Navigations[x].m_Rectangle);
        }

        const uint32_t uiPickupVectorSize = static_cast<uint32_t>(m_ActiveMap->m_PickupVector.size());
        for (uint32_t x = 0; x < uiPickupVectorSize; ++x)
        {
            PickupData* currPickup = m_ActiveMap->m_PickupVector[x];
            if (currPickup->m_bActive)
            {
                currPickup->m_Sprite->Draw(renderer);
            }
        }

        const uint16_t uiRefreshVectorSize = static_cast<uint16_t>(m_ActiveMap->m_RefreshVector.size());
        for (uint16_t x = 0; x < uiRefreshVectorSize; ++x)
        {
            RefreshData* currRefresh = m_ActiveMap->m_RefreshVector[x];

            if (currRefresh->m_bActive)
            {
                currRefresh->m_Sprite->Draw(renderer);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_GRAY.r, g_GameGlobals.COLOR_GRAY.g, g_GameGlobals.COLOR_GRAY.b, static_cast<Uint8>(g_GameGlobals.COLOR_GRAY.a * 0.5));
                SDL_RenderFillRect(renderer, &currRefresh->m_Rectangle);
            }
        }

        const uint16_t uiStoryVectorSize = static_cast<uint16_t>(m_ActiveMap->m_StoryVector.size());
        for (uint16_t x = 0; x < uiStoryVectorSize; ++x)
        {
            StoryData* currRefresh = m_ActiveMap->m_StoryVector[x];
            SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_YELLOW.r, g_GameGlobals.COLOR_YELLOW.g, g_GameGlobals.COLOR_YELLOW.b, g_GameGlobals.COLOR_YELLOW.a);
            SDL_RenderFillRect(renderer, &currRefresh->m_Rectangle);
        }

        if (g_GameManager.GraphicsDebugModeOn())
        {
            const uint16_t uiCollisionSize = static_cast<uint16_t>(m_ActiveMap->m_Collisions.size());
            for (uint16_t x = 0; x < uiCollisionSize; ++x)
            {
                SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_BLACK.r, g_GameGlobals.COLOR_BLACK.g, g_GameGlobals.COLOR_BLACK.b, g_GameGlobals.COLOR_BLACK.a);
                SDL_RenderFillRect(renderer, &m_ActiveMap->m_Collisions[x].m_Rectangle);
            }
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapByID(uint32_t uiMapIDHash)
{
    uint32_t uiMapIndex = m_MapDataMap[uiMapIDHash];
    m_ActiveMap = &m_MapDataVector[uiMapIndex];

    if (m_ActiveMap)
    {
        g_Player.SetPlayerPosition(m_ActiveMap->m_vPlayerStartPosition.m_X, m_ActiveMap->m_vPlayerStartPosition.m_Y);

        g_EnemyManager.SetupEnemySpawning(m_ActiveMap->m_EnemySpawners);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
bool MapManager::CollisionStoppingMovement(SDL_Rect& inRect, Direction& inDirection)
{
    if (m_ActiveMap)
    {
        const uint32_t uiCollisionVectorSize = static_cast<uint32_t>(m_ActiveMap->m_Collisions.size());

        for (uint32_t x = 0; x < uiCollisionVectorSize; ++x)
        {
            CollisionData& currCollision = m_ActiveMap->m_Collisions[x];

            int16_t iCollisionLeft   = currCollision.m_Rectangle.x;
            int16_t iCollisionRight  = currCollision.m_Rectangle.x + currCollision.m_Rectangle.w;
            int16_t iCollisionTop    = currCollision.m_Rectangle.y;
            int16_t iCollisionBottom = currCollision.m_Rectangle.y + currCollision.m_Rectangle.h;

            int16_t iInLeft   = inRect.x;
            int16_t iInRight  = inRect.x + inRect.w;
            int16_t iInTop    = inRect.y;
            int16_t iInBottom = inRect.y + inRect.h;

            bool bIntersecting = false;
            if ((iCollisionLeft - currCollision.m_uiPadding) < iInRight &&
                (iCollisionRight + currCollision.m_uiPadding) > iInLeft &&
                (iCollisionTop - currCollision.m_uiPadding) < iInBottom &&
                (iCollisionBottom + currCollision.m_uiPadding) > iInTop)
            {

                bIntersecting = true;
            }

            if (!bIntersecting)
            {
                continue;
            }
            else
            {
                int16_t iRight  = abs(iInRight - iCollisionLeft);
                int16_t iLeft   = abs(iInLeft - iCollisionRight);
                int16_t iTop    = abs(iInTop - iCollisionBottom);
                int16_t iBottom = abs(iInBottom - iCollisionTop);

                Direction direction;
                int16_t iXMin = iLeft < iRight ? iLeft : iRight;
                int16_t iYMin = iTop < iBottom ? iTop : iBottom;

                if (iXMin < iYMin)
                {
                    direction = iLeft > iRight ? Direction::eLeft : Direction::eRight;
                }
                else
                {
                    direction = iBottom > iTop ? Direction::eDown : Direction::eUp;
                }

                if ((inDirection == Direction::eRight && direction == Direction::eLeft) ||
                    (inDirection == Direction::eLeft  && direction == Direction::eRight) ||
                    (inDirection == Direction::eUp    && direction == Direction::eDown) ||
                    (inDirection == Direction::eDown  && direction == Direction::eUp))
                {
                    // Collision in the way of movement direction.
                    return true;
                }
            }
        }
    }

    return false;
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::ResetMapManager()
{
    if (m_ActiveMap)
    {
        m_ActiveMap->m_PickupVector.clear();
   
        const uint8_t uiRefreshSize = static_cast<uint8_t>(m_ActiveMap->m_RefreshVector.size());
        for (uint8_t x=0; x < uiRefreshSize; ++x)
        {
            RefreshData* currRefreshData = m_ActiveMap->m_RefreshVector[x];
            currRefreshData->m_fGatheredTimestamp = 0;
        }
    }

    m_ActiveMap = nullptr;
}


// -------------------------------------------------------
// -------------------------------------------------------
Florida::InteractionType MapManager::StringToInteractionType(const std::string& string)
{
    if (string == "pickup")
    {
        return InteractionType::ePickup;
    }
    else if (string == "refresh")
    {
        return InteractionType::eRefresh;
    }
    else if (string == "story")
    {
        return InteractionType::eStory;
    }

    return InteractionType::eNONE;
}

}