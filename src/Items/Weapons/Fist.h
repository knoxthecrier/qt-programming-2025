#ifndef FIST_H
#define FIST_H


#include "../Weapon.h"

class Fist : public Weapon {
public:
    QString getName() const override { return "Fist"; }
    int getDamage() const override { return 5; }  // 默认拳头伤害为 5
    void attack() const override {
        // 拳头攻击行为
        // 可以加些逻辑：近战攻击等
    }
    WeaponType getType() const override { return WeaponType::Fist; }
    QPixmap getPixmap() const override {
        return QPixmap();
    }
};
#endif // FIST_H
