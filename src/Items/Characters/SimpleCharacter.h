#ifndef SIMPLECHARACTER_H
#define SIMPLECHARACTER_H
#include "../Item.h"
#include "../Weapon.h"
#include "../Armor.h"
#include "../Consumable.h"
#include "../Platform.h"
#include "../Weapons/Fist.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

class SimpleCharacter : public Item {
public:
    explicit SimpleCharacter(const QString& standPath,
                             const QString& crouchPath,
                             QGraphicsItem* parent = nullptr);

    // 角色行为
    void setLeftDown(bool down);
    void setRightDown(bool down);
    void setCrouchAndPick(bool down);
    void startJump();
    void applyTerrainEffect();
    // 运动状态
    void processInput();
    void applyVerticalMovement(qreal deltaTime, qreal floorY);

    // 装备系统
    void setWeapon(Weapon* weapon);  // 设置武器（通过 Weapon 类）
    Weapon* getWeapon() const;       // 获取当前武器
    void equipArmor(Armor* armor);
    Armor* getArmor()const;
    void useConsumable(Consumable* consumable);

    // 状态查询
    [[nodiscard]] bool isCrouching() const;
    [[nodiscard]] bool isPicking() const;
    [[nodiscard]] QPointF getVelocity() const;

private:
    // 图像状态
    QPixmap standPixmap;
    QPixmap crouchPixmap;
    QGraphicsPixmapItem* weaponItem = nullptr;
    bool crouching = false;

    // 控制状态
    bool leftDown = false, rightDown = false, pickDown = false, lastPickDown = false;
    bool picking = false;

    // 跳跃/重力
    QPointF velocity;
    bool isJumping = false;
    bool isOnGround = true;
    qreal verticalVelocity = 0.0;
    const qreal gravity = 2000.0;
    const qreal jumpVelocity = -1000.0;
    int moveSpeed=600;
    bool isInvisible=false;

    // 武器类型
    Weapon* currentWeapon = new Fist();  // 默认设置为拳头
    Armor* currentArmor =nullptr;

    void updatePixmap();
};
#endif // SIMPLECHARACTER_H
