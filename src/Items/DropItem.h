#ifndef DROPITEM_H
#define DROPITEM_H

#include "Item.h"
#include "Characters/SimpleCharacter.h"
#include "Armor.h"
#include "Consumable.h"

enum class DropType {
    Weapon,       // 武器掉落
    Armor,        // 护甲掉落
    Consumable    // 消耗品掉落（如绷带、医疗箱等）
};

class DropItem : public Item {
public:
    DropItem(DropType type, const QString& imagePath, QGraphicsItem* parent = nullptr);

    // 获取类型（大类）
    DropType getDropType() const { return dropType; }

    // 获取具体类型
    WeaponType getWeaponType() const { return weaponType; }
    ArmorType getArmorType() const { return armorType; }
    ConsumableType getConsumableType() const { return consumableType; }

    void applyTo(SimpleCharacter* character);

    void fall(qreal deltaTime);

private:
    DropType dropType;
    WeaponType weaponType = WeaponType::Fist;  // 默认为拳头
    ArmorType armorType = ArmorType::None;    // 默认无护甲
    ConsumableType consumableType = ConsumableType::Bandage; // 默认为绷带

    qreal fallSpeed = 0.0;
};

#endif // DROPITEM_H

