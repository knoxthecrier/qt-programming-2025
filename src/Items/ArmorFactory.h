#ifndef ARMORFACTORY_H
#define ARMORFACTORY_H

#include "ArmorType.h"
#include "Armors/LightArmor.h"
#include "Armors/HeavyArmor.h"

inline Armor* createArmorByType(ArmorType type) {
    switch (type) {
    case ArmorType::Light: return new LightArmor();
    case ArmorType::Heavy: return new HeavyArmor();
    default: return nullptr;  // 如果没有对应类型，返回 nullptr
    }
}
#endif // ARMORFACTORY_H
