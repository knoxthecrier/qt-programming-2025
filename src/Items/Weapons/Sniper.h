#ifndef SNIPER_H
#define SNIPER_H


#include "../Weapon.h"

class Sniper : public Weapon {
public:
    QString getName() const override { return "Sniper"; }
    int getDamage() const override { return 50; }  // 狙击枪伤害 50
    void attack() const override {
        // 狙击枪的攻击行为（例如瞄准后发射）
    }
    WeaponType getType() const override { return WeaponType::Sniper; }
    QPixmap getPixmap() const override {
        return QPixmap(":/Items/Weapons/sniper.png");
    }

};
#endif // SNIPER_H
