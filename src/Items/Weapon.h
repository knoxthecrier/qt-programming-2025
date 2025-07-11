#ifndef WEAPON_H
#define WEAPON_H


#include "Item.h"
#include "WeaponType.h"
#include <QString>

class Weapon : public Item {
public:

    virtual ~Weapon() = default;

    virtual QString getName() const = 0;  // 获取武器名称
    virtual int getDamage() const = 0;    // 获取武器伤害
    virtual void attack() const = 0;      // 攻击行为
    virtual WeaponType getType() const = 0;  // 加入类型识别接口

    virtual QPixmap getPixmap() const = 0;
};
#endif // WEAPON_H
