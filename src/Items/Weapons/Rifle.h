#ifndef RIFLE_H
#define RIFLE_H

#include "../Weapon.h"

class Rifle : public Weapon {
public:
    QString getName() const override { return "Rifle"; }
    int getDamage() const override { return 10; }  // 步枪伤害 10
    void attack() const override {
        // 步枪的攻击行为（例如射击）
    }
    WeaponType getType() const override { return WeaponType::Rifle; }
    QPixmap getPixmap() const override {
        return QPixmap(":/Items/Weapons/rifle.png");
    }

};
#endif // RIFLE_H
