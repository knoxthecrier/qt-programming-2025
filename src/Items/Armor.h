#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"
#include "ArmorType.h"
#include <QString>

class Armor : public Item {
public:
    virtual ~Armor() = default;

    virtual QString getName() const = 0;  // 获取护甲名称
    virtual int getDurability() const = 0;  // 获取护甲耐久
    virtual void applyEffect() = 0;  // 应用护甲效果（如减少伤害）
    virtual ArmorType getType() const = 0;  // 加入类型识别接口
};

#endif // ARMOR_H
