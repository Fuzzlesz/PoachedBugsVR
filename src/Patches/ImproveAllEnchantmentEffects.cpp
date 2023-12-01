#include "ImproveAllEnchantmentEffects.h"

namespace Patch
{
    void ImproveAllEnchantmentEffects::InstallPatch() {
        if(settings.improveAllEnchantmentEffects)
        {
            REL::Relocation<uintptr_t> enchantmentItemVtable{ RE::VTABLE_CraftingSubMenus__EnchantConstructMenu__CreateEffectFunctor[0] }; // index 1 of this vtable has the functor we are looking for
            originalAddEffect_ = enchantmentItemVtable.write_vfunc(0x1, ImproveAllEnchantmentEffects::AddEffect);
            logger::info("\"Improve multiple enchantment effects\" patch installed!");
        }
        else
        {
            logger::info("\"Improve multiple enchantment effects\" patch is NOT enabled... skipping.");
        }
    };
    
    RE::BSContainer::ForEachResult ImproveAllEnchantmentEffects::AddEffect(RE::CraftingSubMenus::EnchantConstructMenu::CreateEffectFunctor* createEffectFunctor, RE::Effect* effect){
        return originalAddEffect_(createEffectFunctor, effect);
    };

    REL::Relocation<decltype(ImproveAllEnchantmentEffects::AddEffect)> ImproveAllEnchantmentEffects::originalAddEffect_{};
} // namespace Patch