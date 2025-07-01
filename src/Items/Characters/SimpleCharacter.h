#ifndef SIMPLECHARACTER_H
#define SIMPLECHARACTER_H
#include "../Item.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

enum class WeaponType {
    Fist,
    Rifle,
    Sniper,
    Ball
};

class SimpleCharacter : public Item {
public:
    explicit SimpleCharacter(const QString& standPath,
                             const QString& crouchPath,
                             QGraphicsItem* parent = nullptr);

    // 角色行为
    void setLeftDown(bool down);
    void setRightDown(bool down);
    void setPickDown(bool down);
    void setCrouching(bool down);
    void startJump();

    // 运动状态
    void processInput();
    void applyVerticalMovement(qreal deltaTime, qreal floorY);

    // 武器系统
    void setWeapon(WeaponType type, const QString& pixmapPath = "");
    void removeWeapon();
    WeaponType getWeapon() const;

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

    // 武器类型
    WeaponType currentWeapon = WeaponType::Fist;

    void updatePixmap();
};
#endif // SIMPLECHARACTER_H
