#ifndef LIGHTARMOR_H
#define LIGHTARMOR_H


#include "../Armor.h"

class LightArmor : public Armor {
public:
    QString getName() const override { return "Light Armor"; }
    int getDurability() const override { return 100; }  // 假设轻甲耐久为100
    void applyEffect() override {
        // 装备轻甲时减少一定比例的伤害
    }
    ArmorType getType() const override { return ArmorType::Light; }
};
#endif // LIGHTARMOR_H
