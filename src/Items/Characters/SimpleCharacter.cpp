#include "SimpleCharacter.h"
#include <QTransform>
#include <QPixmap>
#include "../Platform.h"
SimpleCharacter::SimpleCharacter(const QString& standPath,
                                 const QString& crouchPath,
                                 QGraphicsItem* parent)
    : Item(parent),
    standPixmap(standPath),
    crouchPixmap(crouchPath) {
    pixmapItem = new QGraphicsPixmapItem(standPixmap, this);
    pixmapItem->setOffset(-standPixmap.width() / 2, -standPixmap.height());
    pixmapItem->setScale(3.0);
}

void SimpleCharacter::setLeftDown(bool down) {
    leftDown = down;
}

void SimpleCharacter::setRightDown(bool down) {
    rightDown = down;
}



void SimpleCharacter::setCrouchAndPick(bool down) {
    if (isJumping) {
        // 如果正在跳跃，不允许下蹲
        return;
    }

    if (crouching != down) {
        crouching = down;
        updatePixmap();
    }
    // 拾取检测只在按下的“瞬间”触发
    picking = (!lastPickDown && down);
    lastPickDown = down;
}

void SimpleCharacter::updatePixmap() {
    if (pixmapItem) {
        pixmapItem->setPixmap(crouching ? crouchPixmap : standPixmap);
    }
}

bool SimpleCharacter::isCrouching() const {
    return crouching;
}

bool SimpleCharacter::isPicking() const {
    return picking;
}

QPointF SimpleCharacter::getVelocity() const {
    return velocity;
}

void SimpleCharacter::startJump() {
    if (isOnGround && !crouching) {
        isJumping = true;
        isOnGround = false;
        verticalVelocity = jumpVelocity;
    }
}
void SimpleCharacter::applyVerticalMovement(qreal deltaTime, qreal floorY) {
    verticalVelocity += gravity * deltaTime;  // 应用重力加速度
    qreal newY = pos().y() + verticalVelocity * deltaTime;  // 计算新的 Y 坐标

    bool collidedWithPlatform = false;  // 标记是否与平台发生碰撞

    // 遍历所有碰撞物体，检测是否是平台
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (auto* item : collidingItems) {
        if (auto* platform = dynamic_cast<Platform*>(item)) {
            qDebug() << "Collided with Platform at Y: " << platform->y();
            if ( newY > platform->y()-1){
            // 检查角色是否与平台接触（判断角色底部是否与平台顶部重叠）

                // 调整角色的 Y 坐标，使其站在平台上
                newY = platform->y() ;
                verticalVelocity = 0;  // 重置垂直速度
                isOnGround = true;     // 标记角色在地面上
                isJumping = false;     // 停止跳跃
                collidedWithPlatform = true;
                qDebug() << "Vertical Velocity: " << verticalVelocity;
                break;  // 如果已经碰到平台，跳出循环
            }
        }
    }
    // 如果没有与任何平台碰撞，继续下落
    if (!collidedWithPlatform && newY >= floorY) {
        newY = floorY;  // 角色到达地面
        verticalVelocity = 0.0;  // 重置垂直速度
        isOnGround = true;     // 标记角色在地面上
        isJumping = false;     // 停止跳跃
    }

    // 更新角色的 Y 坐标
    setPos(pos().x(), newY);  // 更新角色的位置
}

/*
void SimpleCharacter::applyVerticalMovement(qreal deltaTime, qreal floorY) {
    verticalVelocity += gravity * deltaTime;
    qreal newY = pos().y() + verticalVelocity * deltaTime;

    // 获取碰撞的物体
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    bool collidedWithPlatform = false;

    // 遍历碰撞物体
    // 每个平台有它的X位置和宽度



    // 检测与平台1的碰撞
    if (newY + boundingRect().height() <= 360 && newY + boundingRect().height() >= 0) {
        // 检查 X 坐标是否重叠
        if (pos().x() + boundingRect().width() > platform1X && pos().x() < platform1X + platformWidth) {
            newY = 360 - boundingRect().height();  // 角色站在平台1上
            verticalVelocity = 0;  // 重置垂直速度
            isOnGround = true;     // 标记角色在地面上
            isJumping = false;     // 停止跳跃
            collidedWithPlatform = true;
        }
    }

    // 检测与平台2的碰撞
    else if (newY + boundingRect().height() <= 360 && newY + boundingRect().height() >= 0) {
        // 检查 X 坐标是否重叠
        if (pos().x() + boundingRect().width() > platform2X && pos().x() < platform2X + platformWidth) {
            newY = 360 - boundingRect().height();  // 角色站在平台2上
            verticalVelocity = 0;  // 重置垂直速度
            isOnGround = true;     // 标记角色在地面上
            isJumping = false;     // 停止跳跃
            collidedWithPlatform = true;
        }
    }

    // 检测与平台3的碰撞
    else if (newY + boundingRect().height() <= 160 && newY + boundingRect().height() >= 0) {
        // 检查 X 坐标是否重叠
        if (pos().x() + boundingRect().width() > platform3X && pos().x() < platform3X + platformWidth) {
            newY = 160 - boundingRect().height();  // 角色站在平台3上
            verticalVelocity = 0;  // 重置垂直速度
            isOnGround = true;     // 标记角色在地面上
            isJumping = false;     // 停止跳跃
            collidedWithPlatform = true;
        }
    }


    // 如果没有碰撞到平台，继续下落
    if (!collidedWithPlatform && newY >= floorY) {
        newY = floorY;
        verticalVelocity = 0.0;
        isOnGround = true;
        isJumping = false;
    }

    setPos(pos().x(), newY);  // 更新角色的位置
}

*/
void SimpleCharacter::processInput() {
    velocity = QPointF(0, 0);
    const int moveSpeed = 300;

    if (leftDown && !crouching) {
        velocity.setX(-moveSpeed);
        setTransform(QTransform().scale(1, 1)); // 面向左
    }

    if (rightDown && !crouching) {
        velocity.setX(moveSpeed);
        setTransform(QTransform().scale(-1, 1)); // 面向右
    }

    // 检测拾取按键触发（只在按下瞬间有效）
    picking = (!lastPickDown && pickDown);
    lastPickDown = pickDown;
}

void SimpleCharacter::setWeapon(Weapon* weapon) {
    if (currentWeapon && currentWeapon != weapon) {
        delete currentWeapon;  // 删除之前的武器
    }

    currentWeapon = weapon;

    // 如果是拳头，不显示额外武器贴图
    if (!weapon || weapon->getType() == WeaponType::Fist) {
        if (weaponItem) {
            delete weaponItem;
            weaponItem = nullptr;  // 删除武器图像
        }
        return;
    }

    // 为其他武器更新贴图
    QPixmap pix = weapon->getPixmap();  // 通过武器类获取图像
    if (!weaponItem) {
        weaponItem = new QGraphicsPixmapItem(pix, this);
        weaponItem->setOffset(10, -20); // 可微调位置
    } else {
        weaponItem->setPixmap(pix);
    }

    // 根据角色朝向调整武器图像朝向（如果需要）
}

Weapon* SimpleCharacter::getWeapon() const {
    return currentWeapon;
}

void SimpleCharacter::equipArmor(Armor* armor) {
    // 处理护甲的应用逻辑（如减少伤害、显示护甲图标等）
}

Armor* SimpleCharacter::getArmor() const {
    return currentArmor;
}

void SimpleCharacter::useConsumable(Consumable* consumable) {
    consumable->applyEffect();  // 调用消耗品的效果（如加血）
}
