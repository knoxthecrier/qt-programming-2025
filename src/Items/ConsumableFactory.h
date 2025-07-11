#ifndef CONSUMABLEFACTORY_H
#define CONSUMABLEFACTORY_H
#include "ConsumableType.h"
#include "Consumables/Bandage.h"
#include "Consumables/Medkit.h"
#include "Consumables/Adrenaline.h"

inline Consumable* createConsumableByType(ConsumableType type) {
    switch (type) {
    case ConsumableType::Bandage: return new Bandage();
    case ConsumableType::Medkit: return new Medkit();
    case ConsumableType::Adrenaline: return new Adrenaline();
    default: return nullptr;  // 如果没有对应类型，返回 nullptr
    }
}
#endif // CONSUMABLEFACTORY_H
