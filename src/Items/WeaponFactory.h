#ifndef WEAPONFACTORY_H
#define WEAPONFACTORY_H
#include "WeaponType.h"
#include "Weapons/Fist.h"
#include "Weapons/Rifle.h"
#include "Weapons/Sniper.h"
#include "Weapons/Knife.h"
#include "Weapons/Ball.h"

inline Weapon* createWeaponByType(WeaponType type) {
    switch (type) {
    case WeaponType::Fist: return new Fist();
    case WeaponType::Rifle: return new Rifle();
    case WeaponType::Sniper: return new Sniper();
    case WeaponType::Knife: return new Knife();
    case WeaponType::Ball: return new Ball();
    default: return new Fist(); // fallback
    }
}
#endif // WEAPONFACTORY_H
