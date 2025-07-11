#ifndef BANDAGE_H
#define BANDAGE_H

#include "../Consumable.h"

class Bandage : public Consumable {
public:
    QString getName() const override { return "Bandage"; }
    void applyEffect() override {
        // 恢复少量血量
        // 假设恢复10血量*/
    }
    ConsumableType getType() const override { return ConsumableType::Bandage; }
};
#endif // BANDAGE_H
