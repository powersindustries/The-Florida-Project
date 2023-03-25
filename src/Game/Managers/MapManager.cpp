#include "MapManager.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

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
    m_sMapManifestPath.append("/src/Data/MapsManifest.xml");

    m_sMapDirectoryPath.append(__PROJECT_DIRECTORY__);
    m_sMapDirectoryPath.append("/src/Data/Maps/");

    m_BackgroundRectangle.x = 0;
    m_BackgroundRectangle.y = 0;
    m_BackgroundRectangle.w = CoreManagers::g_SettingsManager.GetScreenWidth();
    m_BackgroundRectangle.h = CoreManagers::g_SettingsManager.GetScreenHeight();
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
    rapidxml::file<> xmlFile(m_sMapManifestPath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* mapsNode = doc.first_node("Maps");
    for (rapidxml::xml_node<>* child = mapsNode->first_node(); child; child = child->next_sibling())
    {
        std::string sMapID = m_sMapDirectoryPath;
        sMapID.append(child->first_attribute("Path")->value());
        LoadMapData(sMapID);
    }

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Map data Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapData(std::string sMapPath)
{
    rapidxml::file<> xmlFile(sMapPath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* mapNode = doc.first_node("Map");

    MapData newMapData;
    newMapData.m_sID = mapNode->first_attribute("ID")->value();
    newMapData.m_uiIDHash = CoreSystems::StringToHash32(newMapData.m_sID);

    newMapData.m_BackgroundColor.r = std::stoi(mapNode->first_attribute("BackgroundR")->value());
    newMapData.m_BackgroundColor.g = std::stoi(mapNode->first_attribute("BackgroundG")->value());
    newMapData.m_BackgroundColor.b = std::stoi(mapNode->first_attribute("BackgroundB")->value());
    newMapData.m_BackgroundColor.a = std::stoi(mapNode->first_attribute("BackgroundA")->value());

    newMapData.m_BackgroundRectangle.x = 0;
    newMapData.m_BackgroundRectangle.y = 0;
    newMapData.m_BackgroundRectangle.w = CoreManagers::g_SettingsManager.GetScreenWidth();
    newMapData.m_BackgroundRectangle.h = CoreManagers::g_SettingsManager.GetScreenHeight();

    newMapData.m_vPlayerStartPosition.m_X = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(mapNode->first_attribute("PlayerX")->value()));
    newMapData.m_vPlayerStartPosition.m_Y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(mapNode->first_attribute("PlayerY")->value()));

    std::string sNightTextureID = mapNode->first_attribute("BackgroundTextureNight")->value();
    uint32_t uiNightTextureIDHash = CoreSystems::StringToHash32(sNightTextureID);

    std::string sDayTextureID = mapNode->first_attribute("BackgroundTextureDay")->value();
    uint32_t uiDayTextureIDHash = CoreSystems::StringToHash32(sDayTextureID);

    newMapData.m_BackgroundTextureDay = g_AssetManager.m_TextureAssets[uiDayTextureIDHash].m_Texture;
    newMapData.m_BackgroundTextureNight = g_AssetManager.m_TextureAssets[uiNightTextureIDHash].m_Texture;

    // Load Navigations
    rapidxml::xml_node<>* navigationsNode = doc.first_node()->first_node("Navigations");
    for (rapidxml::xml_node<>* child = navigationsNode->first_node(); child; child = child->next_sibling())
    {
        NavigationData newNavigation;
        newNavigation.m_Rectangle.x = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("x")->value()));
        newNavigation.m_Rectangle.y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("y")->value()));

        newNavigation.m_Rectangle.w = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("w")->value()));
        newNavigation.m_Rectangle.h = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("h")->value()));

        newNavigation.m_uiPadding = std::stoi(child->first_attribute("Padding")->value());

        newNavigation.m_vUpPosition.m_X = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("UpX")->value()));
        newNavigation.m_vUpPosition.m_Y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("UpY")->value()));

        newNavigation.m_vDownPosition.m_X = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("DownX")->value()));
        newNavigation.m_vDownPosition.m_Y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("DownY")->value()));

        newMapData.m_Navigations.push_back(newNavigation);
    }

    // Load Collisions
    rapidxml::xml_node<>* collisionsNode = doc.first_node()->first_node("Collisions");
    for (rapidxml::xml_node<>* child = collisionsNode->first_node(); child; child = child->next_sibling())
    {

        CollisionData newCollision;
        newCollision.m_Rectangle.x = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("x")->value()));
        newCollision.m_Rectangle.y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("y")->value()));

        newCollision.m_Rectangle.w = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("w")->value()));
        newCollision.m_Rectangle.h = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("h")->value()));

        newCollision.m_uiPadding = std::stoi(child->first_attribute("Padding")->value());

        newMapData.m_Collisions.push_back(newCollision);
    }

    // Load Enemies
    rapidxml::xml_node<>* enemiesNode = doc.first_node()->first_node("EnemySpawners");
    for (rapidxml::xml_node<>* child = enemiesNode->first_node(); child; child = child->next_sibling())
    {
        EnemySpawnerData newEnemy;
        newEnemy.m_uiMapIDHash = newMapData.m_uiIDHash;

        newEnemy.m_Rectangle.x = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("x")->value()));
        newEnemy.m_Rectangle.y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("y")->value()));
        newEnemy.m_Rectangle.w = 25;
        newEnemy.m_Rectangle.h = 50;

        g_EnemyManager.m_EnemySpawnerVector.push_back(newEnemy);

        const uint32_t uiEnemiesVectorSize = static_cast<uint32_t>(g_EnemyManager.m_EnemySpawnerVector.size()) - 1;
        g_EnemyManager.m_EnemySpawnerMap.insert({ newEnemy.m_uiMapIDHash, uiEnemiesVectorSize });

        newMapData.m_EnemySpawners.push_back(uiEnemiesVectorSize);
    }

    // Load Interactions
    rapidxml::xml_node<>* interactionsNode = doc.first_node()->first_node("Interactions");
    for (rapidxml::xml_node<>* child = interactionsNode->first_node(); child; child = child->next_sibling())
    {
        const InteractionType currInteractionType = StringToInteractionType(child->first_attribute("Type")->value());
        if (currInteractionType != InteractionType::eNONE)
        {
            switch (currInteractionType)
            {
            case InteractionType::ePickup:
            {
                PickupData* newPickupInteraction = new PickupData;
                newPickupInteraction->m_Type = currInteractionType;

                newPickupInteraction->m_Rectangle.x = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("x")->value()));
                newPickupInteraction->m_Rectangle.y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("y")->value()));
                newPickupInteraction->m_Rectangle.w = std::stoi(child->first_attribute("w")->value());
                newPickupInteraction->m_Rectangle.h = std::stoi(child->first_attribute("h")->value());
                newPickupInteraction->m_uiPadding = std::stoi(child->first_attribute("Padding")->value());

                newPickupInteraction->m_uiPickupTime = std::stoi(child->first_attribute("PickupTime")->value());

                newPickupInteraction->m_uiItem = CoreSystems::StringToHash32(std::string(child->first_attribute("Item")->value()));
                newPickupInteraction->m_uiAmount = std::stoi(child->first_attribute("Amount")->value());

                newPickupInteraction->m_Sprite = new Sprite(CoreSystems::StringToHash32(std::string(child->first_attribute("Texture")->value())), g_GameGlobals.ITEM_ANIMATION_SPEED);

                newMapData.m_PickupVector.push_back(newPickupInteraction);

                break;
            }
            case InteractionType::eRefresh:
            {
                RefreshData* newRefreshInteraction = new RefreshData;
                newRefreshInteraction->m_Type = currInteractionType;
                newRefreshInteraction->m_uiMapIDHash = newMapData.m_uiIDHash;

                newRefreshInteraction->m_Rectangle.x = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("x")->value()));
                newRefreshInteraction->m_Rectangle.y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("y")->value()));
                newRefreshInteraction->m_Rectangle.w = std::stoi(child->first_attribute("w")->value());
                newRefreshInteraction->m_Rectangle.h = std::stoi(child->first_attribute("h")->value());
                newRefreshInteraction->m_uiPadding = std::stoi(child->first_attribute("Padding")->value());

                newRefreshInteraction->m_uiPickupTime = std::stoi(child->first_attribute("PickupTime")->value());
                newRefreshInteraction->m_uiRefreshTime = std::stoi(child->first_attribute("RefreshTime")->value());

                newRefreshInteraction->m_uiItem = CoreSystems::StringToHash32(std::string(child->first_attribute("Item")->value()));
                newRefreshInteraction->m_uiAmount = std::stoi(child->first_attribute("Amount")->value());

                newRefreshInteraction->m_Sprite = new Sprite(CoreSystems::StringToHash32(std::string(child->first_attribute("Texture")->value())), g_GameGlobals.ITEM_ANIMATION_SPEED);
                
                newMapData.m_RefreshVector.push_back(newRefreshInteraction);

                g_UIManager.AddNewRefreshUI(newMapData.m_uiIDHash, newRefreshInteraction->m_Rectangle.x, newRefreshInteraction->m_Rectangle.y);

                break;
            }
            case InteractionType::eStory:
            {
                StoryData* newStoryInteraction = new StoryData;
                newStoryInteraction->m_Type = currInteractionType;

                newStoryInteraction->m_Rectangle.y = CoreManagers::g_SettingsManager.GetRelativeScreenY(std::stoi(child->first_attribute("y")->value()));
                newStoryInteraction->m_Rectangle.x = CoreManagers::g_SettingsManager.GetRelativeScreenX(std::stoi(child->first_attribute("x")->value()));
                newStoryInteraction->m_Rectangle.w = std::stoi(child->first_attribute("w")->value());
                newStoryInteraction->m_Rectangle.h = std::stoi(child->first_attribute("h")->value());
                newStoryInteraction->m_uiPadding = std::stoi(child->first_attribute("Padding")->value());

                newMapData.m_StoryVector.push_back(newStoryInteraction);

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }

    m_MapDataVector.push_back(newMapData);

    const uint32_t uiMapDataVectorSize = static_cast<uint32_t>(m_MapDataVector.size()) - 1;
    m_MapDataMap.insert({ newMapData.m_uiIDHash, uiMapDataVectorSize });
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

        if (CoreUtility::Utility::CollisionBetweenTwoRectanglesWithPadding(currNavigation.m_Rectangle, g_Player.GetPlayerRectangle(), currNavigation.m_uiPadding) &&
            (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eUp) || CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eDown)))
        {
            SDL_Rect& playerRect = g_Player.GetPlayerRectangle();
            int yOffsetTop = currNavigation.m_Rectangle.y - playerRect.y;
            int yOffsetBottom = (currNavigation.m_Rectangle.y + currNavigation.m_Rectangle.h) - playerRect.y;

            if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eUp) && yOffsetBottom > 0 && yOffsetBottom < 50)
            {
                g_Player.SetPlayerPosition(currNavigation.m_vUpPosition.m_X, currNavigation.m_vUpPosition.m_Y);
            }
            else if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eDown) && yOffsetTop > 0 && yOffsetTop < 50)
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
            CoreUtility::Utility::CollisionBetweenTwoRectanglesWithPadding(currPickup->m_Rectangle, g_Player.GetPlayerRectangle(), currPickup->m_uiPadding) &&
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


        if (currRefresh->m_bActive && CoreUtility::Utility::CollisionBetweenTwoRectanglesWithPadding(currRefresh->m_Rectangle, g_Player.GetPlayerRectangle(), currRefresh->m_uiPadding))
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
        if (currStory->m_bActive && CoreUtility::Utility::CollisionBetweenTwoRectanglesWithPadding(currStory->m_Rectangle, g_Player.GetPlayerRectangle(), currStory->m_uiPadding))
        {
            CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Story interaction!");
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