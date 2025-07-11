#ifndef MEDKIT_H
#define MEDKIT_H

#include "../Consumable.h"

class Medkit : public Consumable {
public:
    QString getName() const override { return "Medkit"; }
    void applyEffect() override {
        // 恢复全部血量
        // 假设恢复100血量*/
    }
    ConsumableType getType() const override { return ConsumableType::Medkit; }
};
#endif // MEDKIT_H
