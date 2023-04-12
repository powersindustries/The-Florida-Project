#include "CraftingManager.h"
#include "../Player/Player.h"
#include "Core/Systems/Hash.h"
#include "Core/Systems/Logging.h"
#include "ItemManager.h"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
CraftingManager g_CraftingManager;


// -------------------------------------------------------
// -------------------------------------------------------
CraftingManager::CraftingManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
CraftingManager::~CraftingManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingManager::Initialize()
{
    IngredientData scrapData;
    scrapData.m_uiItemID = Core::StringToHash32(std::string("itm_Scrap"));
    scrapData.m_uiAmount = m_uiDefaultAmount;

    IngredientData waterData;
    waterData.m_uiItemID = Core::StringToHash32(std::string("itm_Water"));
    waterData.m_uiAmount = m_uiDefaultAmount;

    IngredientData woodData;
    woodData.m_uiItemID = Core::StringToHash32(std::string("itm_Wood"));
    woodData.m_uiAmount = m_uiDefaultAmount;

    IngredientData ammoData;
    ammoData.m_uiItemID = Core::StringToHash32(std::string("itm_Ammo"));
    ammoData.m_uiAmount = m_uiDefaultAmount;

    IngredientData staminaPotionData;
    staminaPotionData.m_uiItemID = Core::StringToHash32(std::string("itm_StaminaPotion"));
    staminaPotionData.m_uiAmount = m_uiDefaultAmount;

    // Ammo Recipe (1 Wood, 1 Scrap)
    RecipeData ammoRecipeData;
    ammoRecipeData.m_uiRecipeID = ammoData.m_uiItemID;
    ammoRecipeData.m_Reward = ammoData;
    ammoRecipeData.m_sIngredientText = "(Wood: 1, Scrap: 1)";
    ammoRecipeData.m_Ingredients.push_back(woodData);
    ammoRecipeData.m_Ingredients.push_back(scrapData);

    // StaminaPotion Recipe (1 Scrap, 1 Wood, 1 Water)
    RecipeData staminaPotionRecipeData;
    staminaPotionRecipeData.m_uiRecipeID = staminaPotionData.m_uiItemID;
    staminaPotionRecipeData.m_Reward = staminaPotionData;
    staminaPotionRecipeData.m_sIngredientText = "(Scrap: 1, Wood: 1, Water: 1)";
    staminaPotionRecipeData.m_Ingredients.push_back(scrapData);
    staminaPotionRecipeData.m_Ingredients.push_back(woodData);
    staminaPotionRecipeData.m_Ingredients.push_back(waterData);

    m_AllRecipes.push_back(ammoRecipeData);
    m_RecipesMap.insert({ ammoData.m_uiItemID, static_cast<uint32_t>(m_RecipesMap.size()) });

    m_AllRecipes.push_back(staminaPotionRecipeData);
    m_RecipesMap.insert({ staminaPotionData.m_uiItemID, static_cast<uint32_t>(m_RecipesMap.size()) });

}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingManager::CraftItemByIndex(uint32_t uiRecipeIndex)
{
    RecipeData& craftRecipe = m_AllRecipes[uiRecipeIndex];

    std::vector<IngredientData>& ingredientVector = craftRecipe.m_Ingredients;
    const uint8_t uiIngredientVectorSize = static_cast<uint8_t>(ingredientVector.size());
    for (uint8_t x=0; x< uiIngredientVectorSize; ++x)
    {
        IngredientData& currIngredient = ingredientVector[x];
        const ItemData& playerIventoryData = g_ItemManager.GetItemDataByID(currIngredient.m_uiItemID);

        if (playerIventoryData.m_uiAmount < currIngredient.m_uiAmount)
        {
            Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Not enough resources to craft current item.");
            return;
        }
    }

    for (uint8_t x = 0; x < uiIngredientVectorSize; ++x)
    {
        IngredientData& currIngredient = ingredientVector[x];
        g_ItemManager.RemoveItem(currIngredient.m_uiItemID, currIngredient.m_uiAmount);
    }

    g_ItemManager.AddItem(craftRecipe.m_Reward.m_uiItemID, craftRecipe.m_Reward.m_uiAmount);
}


// -------------------------------------------------------
// -------------------------------------------------------
bool CraftingManager::HasEnoughResourcesToCraft(uint32_t uiRecipeID)
{
    const uint32_t uiCraftRecipeIndex = m_RecipesMap[uiRecipeID];
    RecipeData& craftRecipe = m_AllRecipes[uiCraftRecipeIndex];

    std::vector<IngredientData>& ingredientVector = craftRecipe.m_Ingredients;
    const uint8_t uiIngredientVectorSize = static_cast<uint8_t>(ingredientVector.size());
    for (uint8_t x=0; x< uiIngredientVectorSize; ++x)
    {
        IngredientData& currIngredient = ingredientVector[x];
        const ItemData& playerIventoryData = g_ItemManager.GetItemDataByID(currIngredient.m_uiItemID);

        if (playerIventoryData.m_uiAmount < currIngredient.m_uiAmount)
        {
            return false;
        }
    }

    return true;
}


// -------------------------------------------------------
// -------------------------------------------------------
const Florida::RecipeData& CraftingManager::GetRecipeByID(uint32_t RecipeID)
{
    uint32_t uiRecipeIndex = m_RecipesMap[RecipeID];
    return m_AllRecipes[uiRecipeIndex];
}

}