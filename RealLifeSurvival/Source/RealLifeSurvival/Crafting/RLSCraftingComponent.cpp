#include "Crafting/RLSCraftingComponent.h"
#include "Crafting/RLSRecipeTypes.h"
#include "Inventory/RLSInventoryComponent.h"
#include "GameFramework/Actor.h"

URLSCraftingComponent::URLSCraftingComponent() { SetIsReplicatedByDefault(true); }
bool URLSCraftingComponent::Craft(FName RecipeId)
{
    if (!GetOwner() || !GetOwner()->HasAuthority()) return false;
    const FRLSRecipeDefinition* Recipe = Recipes ? Recipes->FindRow<FRLSRecipeDefinition>(RecipeId, TEXT("Craft"), false) : nullptr;
    FRLSRecipeDefinition Fallback;
    if (!Recipe && RecipeId == TEXT("Plank")) { Fallback.RecipeId=RecipeId; Fallback.Ingredients.Add({TEXT("Wood"), 2}); Fallback.Output={TEXT("Plank"), 1}; Recipe=&Fallback; }
    if (!Recipe && RecipeId == TEXT("Wall")) { Fallback.RecipeId=RecipeId; Fallback.Ingredients.Add({TEXT("Plank"), 4}); Fallback.Output={TEXT("Wall"), 1}; Recipe=&Fallback; }
    URLSInventoryComponent* Inventory = GetOwner()->FindComponentByClass<URLSInventoryComponent>();
    return Recipe && Inventory && Recipe->Output.IsValid() && Inventory->HasItems(Recipe->Ingredients) && Inventory->ConsumeItems(Recipe->Ingredients) && Inventory->AddItem(Recipe->Output.ItemId, Recipe->Output.Quantity);
}
