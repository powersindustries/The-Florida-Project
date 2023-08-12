#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdint.h>

namespace Florida
{


struct IngredientData
{
    uint32_t m_uiItemID;
    uint32_t m_uiAmount;
};


struct RecipeData
{
    uint32_t m_uiRecipeID;
    std::string m_sIngredientText;

    IngredientData m_Reward;

    std::vector<IngredientData> m_Ingredients;
};


class CraftingManager
{
public:
    CraftingManager();
    ~CraftingManager();

    void Initialize();

    void CraftItemByIndex(uint32_t uiRecipeIndex);

    bool HasEnoughResourcesToCraft(uint32_t uiRecipeID);

    const RecipeData& GetRecipeByID(uint32_t RecipeID);

    const inline std::vector<RecipeData>& GetAllRecipes() const { return m_AllRecipes; };


private:

    const uint32_t m_uiDefaultAmount = 1;

    std::vector<RecipeData> m_AllRecipes;
    std::map<uint32_t, uint32_t> m_RecipesMap; // Recipe ID, Index in m_AllRecipes.

};

extern CraftingManager g_CraftingManager;

}