// DropItem.cpp
#include "DropItem.h"
#include "ConsumableFactory.h"
#include "ArmorFactory.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "WeaponFactory.h"
#include "Characters/SimpleCharacter.h"

DropItem::DropItem(DropType type, const QString& imagePath, QGraphicsItem* parent)
    : Item(parent, imagePath), dropType(type) {}

// DropItem.cpp
void DropItem::applyTo(SimpleCharacter* character) {
    switch (dropType) {
    case DropType::Weapon:
        // 生成并应用武器
        character->setWeapon(createWeaponByType(weaponType));
        break;
    case DropType::Armor:
        // 生成并应用护甲
        character->equipArmor(createArmorByType(armorType));
        break;
    case DropType::Consumable:
        // 生成并使用消耗品
        character->useConsumable(createConsumableByType(consumableType));
        break;
    default:
        break;
    }
}

void DropItem::fall(qreal deltaTime) {
    // 模拟简单的重力下落
    setPos(pos().x(), pos().y() + fallSpeed * deltaTime);
    fallSpeed += 20 * deltaTime;  // 加速度
}
