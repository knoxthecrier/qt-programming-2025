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

class SimpleCharacter : public QObject, public Item {
    Q_OBJECT
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

    // 生命值系统
    void takeDamage(int damage);  // 受到伤害，减少生命值
    void heal(int amount);        // 恢复生命，增加生命值


    // 状态查询
    [[nodiscard]] bool isCrouching() const;
    [[nodiscard]] bool isPicking() const;
    [[nodiscard]] QPointF getVelocity() const;
signals:
    // 当角色触发拾取时发出信号
    void requestPickUp(SimpleCharacter* character);

private:
    // 图像状态
    QPixmap standPixmap;
    QPixmap crouchPixmap;
    QGraphicsPixmapItem* weaponItem = nullptr;
    bool crouching = false;

    // 控制状态
    bool leftDown = false, rightDown = false, pickDown = false, lastPickDown = false;
    bool picking = false;

    // 攻击标志
    bool isAttacking = false;

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

    // 生命值系统
    QGraphicsRectItem* healthBarBackground = nullptr;  // 血槽背景（底色）
    QGraphicsRectItem* healthBar = nullptr;  // 血条（显示生命值）
    const int maxHealth = 100;  // 最大生命值，方便计算血条的长度
    int lastHealth = 100;  // 用于记录上一次的生命值
    int health=100;  //初始生命值默认100
    // 伤害及回复显示
    QTimer* colorChangeTimer = nullptr;  // 用于控制血条颜色变化的定时器
    QGraphicsRectItem* overlayEffect = nullptr;  // 半透明遮罩图层
    QTimer* overlayTimer = nullptr;              // 用于恢复透明的定时器

    void updatePixmap();
    void updateHealthBar();       // 更新血条
    void resetHealthBarColor();
    void showOverlayEffect(const QColor& color);



};
#endif // SIMPLECHARACTER_H
