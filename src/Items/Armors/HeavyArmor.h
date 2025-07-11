#ifndef HEAVYARMOR_H
#define HEAVYARMOR_H

#include "../Armor.h"

class HeavyArmor : public Armor {
public:
    QString getName() const override { return "Heavy Armor"; }
    int getDurability() const override { return 200; }  // 假设防弹衣耐久为200
    void applyEffect() override {
        // 装备防弹衣时吸收部分伤害
    }
    ArmorType getType() const override { return ArmorType::Heavy; }
};
#endif // HEAVYARMOR_H
