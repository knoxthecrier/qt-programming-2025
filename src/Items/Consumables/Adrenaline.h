#ifndef ADRENALINE_H
#define ADRENALINE_H


#include "../Consumable.h"

class Adrenaline : public Consumable {
public:
    QString getName() const override { return "Adrenaline"; }
    void applyEffect() override {
        // 增加移动速度并缓慢恢复血量
        // 提高速度*/
        // 还可以添加缓慢回血的效果
    }
    ConsumableType getType() const override { return ConsumableType::Adrenaline; }
};
#endif // ADRENALINE_H
