#include "SimpleCharacter.h"
#include "../Platform.h"
#include <QTransform>
#include <QPixmap>
#include <QBrush>
#include <QPen>
#include <qtimer.h>
#include <QTimer>
#include <QObject>
SimpleCharacter::SimpleCharacter(const QString& standPath,
                                 const QString& crouchPath,
                                 QGraphicsItem* parent)
    : Item(parent),
    standPixmap(standPath),
    crouchPixmap(crouchPath) {
    pixmapItem = new QGraphicsPixmapItem(standPixmap, this);
    pixmapItem->setOffset(-standPixmap.width() / 2, -standPixmap.height());

    // 创建血槽背景（底色）
    healthBarBackground = new QGraphicsRectItem(-40, -160, 100, 10, this);  // 假设初始血槽长度为100
    healthBarBackground->setBrush(QBrush(Qt::gray));  // 设置底色为灰色

    // 创建血条（显示实际生命值）
    healthBar = new QGraphicsRectItem(-40, -160, 100, 10, this);  // 初始血条长度为100
    healthBar->setBrush(QBrush(Qt::green));  // 设置血条的初始颜色为绿色
    healthBar->setPos(healthBarBackground->pos());  // 跟着背景走
    healthBar->setZValue(1);  // 确保血条在角色之上

    // 设置定时器，用于恢复血条颜色
    colorChangeTimer = new QTimer(this);
    connect(colorChangeTimer, &QTimer::timeout, this, &SimpleCharacter::resetHealthBarColor);

    // 创建半透明遮罩图层
    overlayEffect = new QGraphicsRectItem(this);
    overlayEffect->setRect(pixmapItem->boundingRect());  // 大小跟角色图像一样
    overlayEffect->setBrush(QBrush(QColor(255, 0, 0, 100)));  // 默认红色、半透明
    overlayEffect->setPen(Qt::NoPen);  // 没有边框
    overlayEffect->setZValue(10);  // 层级高于贴图
    overlayEffect->setVisible(false);  // 初始隐藏

    // 创建定时器用于恢复透明
    overlayTimer = new QTimer(this);
    overlayTimer->setSingleShot(true);  // 一次性的
    connect(overlayTimer, &QTimer::timeout, this, [this]() {
        if (overlayEffect) overlayEffect->setVisible(false);
    });
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

    if (down && !lastPickDown) {
        picking = true;  // 激活拾取逻辑
        emit requestPickUp(this);  // 发出拾取请求信号
    }

    lastPickDown = down;  // 更新下蹲键状态
}

void SimpleCharacter::updatePixmap() {
    // 每次更新角色位置时，应用地形效果
    applyTerrainEffect();  // 处理根据角色高度设置的地形效果
    if (isInvisible) {
        pixmapItem->setOpacity(0.0);  // 隐身时设置透明度为0
        healthBarBackground->setOpacity(0.0);
        healthBar->setOpacity(0.0);
    } else {
        pixmapItem->setOpacity(1.0);  // 恢复可见
        healthBarBackground->setOpacity(1.0);
        healthBar->setOpacity(1.0);
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
    // 打印角色当前的 Y 坐标
    qDebug() << "Character Height (Y): " << pos().y();
    verticalVelocity += gravity * deltaTime;  // 应用重力加速度
    qreal newY = pos().y() + verticalVelocity * deltaTime;  // 计算新的 Y 坐标
    // 每次更新角色位置时，应用地形效果
    applyTerrainEffect();  // 处理根据角色高度设置的地形效果

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
void SimpleCharacter::applyTerrainEffect() {
    qreal currentY = pos().y();  // 获取角色的当前 Y 坐标

    if (currentY >360) {
        // 角色站在冰面上，增加移动速度
        moveSpeed = 600;  // 假设冰面上的速度是普通速度的两倍
    } else if (currentY <= 360 && currentY > 160) {
        // 角色站在草地上，只有下蹲时才隐身
        moveSpeed = 300;
        if (isCrouching()) {
            isInvisible = true;  // 下蹲时隐身
        } else {
            isInvisible = false;  // 站立时不隐身
        }
    } else if (currentY <= 160) {
        // 角色站在地面上，没有特殊效果
        moveSpeed = 300;  // 恢复正常速度
        isInvisible = false;  // 恢复可见
    }
}


void SimpleCharacter::takeDamage(int damage) {
    int previousHealth = health;  // 记录受伤前的生命值
    health -= damage;
    if (health < 0) health = 0;

    // 如果生命值减少，显示红色
    if (health < previousHealth) {
        showOverlayEffect(Qt::red);  // 红色表示受伤
    }

    updateHealthBar();
    lastHealth = health;  // 更新 lastHealth
    qDebug() << "Current Health: " << health;  // 打印当前生命值，方便调试
}

void SimpleCharacter::heal(int amount) {
    int previousHealth = health;  // 记录回血前的生命值
    health += amount;
    if (health > maxHealth) health = maxHealth;

    // 如果生命值增加，显示蓝色
    if (health > previousHealth) {
        showOverlayEffect(Qt::blue);  // 蓝色表示回血
    }

    updateHealthBar();
    lastHealth = health;  // 更新 lastHealth
    qDebug() << "Current Health: " << health;  // 打印当前生命值，方便调试
}

void SimpleCharacter::updateHealthBar() {
    if (healthBar) {
        // 计算血条的长度，比例为当前生命值/最大生命值
        qreal healthRatio = static_cast<qreal>(health) / static_cast<qreal>(maxHealth);
        qreal newWidth = 100 * healthRatio;  // 假设血槽背景长度为100
        healthBar->setRect(0, 0, newWidth, 10);  // 更新血条的宽度

        // 根据生命值变化，更新血条的颜色
        // 如果生命值减少，血条变红
        if (health < lastHealth) {
            healthBar->setBrush(QBrush(Qt::red));  // 血条变红
            if (!colorChangeTimer->isActive()) {
                colorChangeTimer->start(500);  // 启动定时器，500ms后恢复为绿色
            }
        }
        // 如果生命值增加，血条变蓝
        else if (health > lastHealth) {
            healthBar->setBrush(QBrush(Qt::blue));  // 血条变蓝
            if (!colorChangeTimer->isActive()) {
                colorChangeTimer->start(500);  // 启动定时器，500ms后恢复为绿色
            }
        }
        // 如果生命值未变化，恢复为绿色
        else {
            healthBar->setBrush(QBrush(Qt::green));  // 血条保持绿色
        }

        // 更新 lastHealth，用于下一次比较
        lastHealth = health;

    }

}

void SimpleCharacter::resetHealthBarColor() {
    healthBar->setBrush(QBrush(Qt::green));  // 恢复为绿色
    colorChangeTimer->stop();  // 停止定时器
}


void SimpleCharacter::showOverlayEffect(const QColor& color) {
    if (!overlayEffect) return;

    overlayEffect->setBrush(QBrush(QColor(color.red(), color.green(), color.blue(), 100)));  // 半透明色
    overlayEffect->setVisible(true);
    overlayTimer->start(300);  // 显示300ms
}



