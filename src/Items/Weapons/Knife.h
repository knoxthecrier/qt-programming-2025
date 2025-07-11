#ifndef KNIFE_H
#define KNIFE_H


#include "../Weapon.h"

class Knife : public Weapon {
public:
    QString getName() const override { return "Knife"; }
    int getDamage() const override { return 5; }  // 小刀伤害 5
    void attack() const override {
        // 小刀近战攻击行为
    }
    WeaponType getType() const override { return WeaponType::Knife; }
    QPixmap getPixmap() const override {
        return QPixmap(":/Items/Weapons/knife.png");
    }
};

#endif // KNIFE_H
