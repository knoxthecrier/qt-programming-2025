#ifndef BALL_H
#define BALL_H

#include "../Weapon.h"

class Ball : public Weapon {
public:
    QString getName() const override { return "Ball"; }
    int getDamage() const override { return 15; }  // 实心球伤害 15
    void attack() const override {
        // 实心球的攻击行为（例如投掷，造成伤害）
    }
    WeaponType getType() const override { return WeaponType::Ball; }
    QPixmap getPixmap() const override {
        return QPixmap(":/Items/Weapons/ball.png");
    }
};
#endif // BALL_H
