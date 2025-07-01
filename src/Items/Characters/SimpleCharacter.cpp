#include "SimpleCharacter.h"
#include <QTransform>
#include <QPixmap>

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

void SimpleCharacter::setPickDown(bool down) {
    pickDown = down;
}

void SimpleCharacter::setCrouching(bool down) {
    if (isJumping) {
        // 如果正在跳跃，不允许下蹲
        return;
    }

    if (crouching != down) {
        crouching = down;
        updatePixmap();
    }
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
    verticalVelocity += gravity * deltaTime;
    qreal newY = pos().y() + verticalVelocity * deltaTime;

    if (newY >= floorY) {
        newY = floorY;
        verticalVelocity = 0.0;
        isOnGround = true;
        isJumping = false;
    }

    setPos(pos().x(), newY);
}

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

void SimpleCharacter::setWeapon(WeaponType type, const QString& pixmapPath) {
    currentWeapon = type;

    if (type == WeaponType::Fist) {
        removeWeapon();
        return;
    }

    QPixmap pix(pixmapPath);
    if (!weaponItem) {
        weaponItem = new QGraphicsPixmapItem(pix, this);
        weaponItem->setOffset(10, -20); // 可微调位置
    } else {
        weaponItem->setPixmap(pix);
    }
}

void SimpleCharacter::removeWeapon() {
    if (weaponItem) {
        delete weaponItem;
        weaponItem = nullptr;
    }
    currentWeapon = WeaponType::Fist;
}

WeaponType SimpleCharacter::getWeapon() const {
    return currentWeapon;
}
