#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include "ConsumableType.h"
#include "Item.h"
#include <QString>

class Consumable : public Item {
public:
    virtual ~Consumable() = default;

    virtual QString getName() const = 0;  // 获取消耗品名称
    virtual void applyEffect() = 0;  // 应用消耗品效果（如加血、加速）
    virtual ConsumableType getType() const = 0;  // 加入类型识别接口
};
#endif // CONSUMABLE_H
