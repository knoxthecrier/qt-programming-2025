#include "BattleScene.h"
#include <QKeyEvent>
#include "../Items/Maps/Battlefield.h"
#include "../Items/Platform.h"
#include "../Items/DropItem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRandomGenerator>
BattleScene::BattleScene(QObject* parent) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);

    map = new Battlefield();
    addItem(map);
    map->scaleToFitScene(this);

    player1 = new SimpleCharacter(":/Characters/Items/Characters/c1stand.png",
                                  ":/Characters/Items/Characters/c1crouch.png");
    addItem(player1);
    player2 = new SimpleCharacter(":/Characters/Items/Characters/c2stand.png",
                                  ":/Characters/Items/Characters/c2crouch.png");
    addItem(player2);

    player1->setPos(map->getSpawnPos());
    player2->setPos(map->getSpawnPos() + QPointF(200, 0));  // 右边一点出生

    player1->setWeapon(new Fist());  // 给 player1 设置拳头
    player2->setWeapon(new Fist());  // 给 player2 设置拳头


    qreal centerX = 640;  // 场景中心X坐标
    qreal platformWidth = 410;
    qreal platformHeight = 20;  // 平台高度

    // 创建平台1 (左侧)
    platform1 = new Platform(centerX - 360 - platformWidth / 2, 360, platformWidth, platformHeight);
    addItem(platform1);

    // 创建平台2 (右侧)
    platform2 = new Platform(centerX + 360 - platformWidth / 2, 360, platformWidth, platformHeight);
    addItem(platform2);

    // 创建平台3 (在平台1和平台2之上)
    platform3 = new Platform(centerX - platformWidth / 2, 160, platformWidth, platformHeight);
    addItem(platform3);

    // 定时器定期调用 spawnRandomDrop()
    QTimer* dropTimer = new QTimer(this);
    connect(dropTimer, &QTimer::timeout, this, &BattleScene::spawnRandomDrop);
    dropTimer->start(6000);  // 每 6 秒生成一个掉落物
}

void BattleScene::processInput() {
    if (player1) player1->processInput();
    if (player2) player2->processInput();
}

void BattleScene::keyPressEvent(QKeyEvent* event) {
    if (player1 && player2) {
        switch (event->key()) {
        // Player1
        case Qt::Key_A: player1->setLeftDown(true); break;
        case Qt::Key_D: player1->setRightDown(true); break;
        case Qt::Key_W: player1->startJump(); break;
        case Qt::Key_S: player1->setCrouchAndPick(true); break; // ← 合并按键
        case Qt::Key_Q: /* 攻击逻辑 */ break;

        // Player2
        case Qt::Key_Left: player2->setLeftDown(true); break;
        case Qt::Key_Right: player2->setRightDown(true); break;
        case Qt::Key_Up: player2->startJump(); break;
        case Qt::Key_Down: player2->setCrouchAndPick(true); break; // ← 合并按键
        case Qt::Key_Slash: /* 攻击逻辑 */ break;

        default: Scene::keyPressEvent(event);
        }
    }
}

void BattleScene::keyReleaseEvent(QKeyEvent* event) {
    if (player1 && player2) {
        switch (event->key()) {
        // Player1
        case Qt::Key_A: player1->setLeftDown(false); break;
        case Qt::Key_D: player1->setRightDown(false); break;
        case Qt::Key_S: player1->setCrouchAndPick(false); break;

            // Player2
        case Qt::Key_Left: player2->setLeftDown(false); break;
        case Qt::Key_Right: player2->setRightDown(false); break;
        case Qt::Key_Down: player2->setCrouchAndPick(false); break;

        default: Scene::keyReleaseEvent(event);
        }
    }
}

void BattleScene::update() {

    Scene::update();

    // 让所有掉落物下落
    for (DropItem* drop : drops) {
        drop->fall(deltaTime);  // 调用掉落物下落
    }
}

void BattleScene::processMovement() {
    if (player1 && !player1->isCrouching()) {
        QPointF pos = player1->pos();  // 获取角色的位置
        QPointF velocity = player1->getVelocity();  // 获取角色的速度

        // 更新角色的水平位置
        pos.rx() += velocity.x() * deltaTime;

        // 检测与三个平台的碰撞
        player1->applyVerticalMovement(deltaTime, map->getFloorHeight());

        // 更新角色的 X 坐标
        player1->setPos(pos.x(), player1->pos().y());  // 更新 X 和 Y 坐标
    }

    if (player2 && !player2->isCrouching()) {
        QPointF pos = player2->pos();// 获取角色的位置
        QPointF velocity = player2->getVelocity();// 获取角色的速度

        // 更新角色的水平位置
        pos.rx() += velocity.x() * deltaTime;

        // 检测与三个平台的碰撞
        player2->applyVerticalMovement(deltaTime, map->getFloorHeight());

        // 更新角色的 X 坐标
        player2->setPos(pos.x(), player2->pos().y());  // 更新 X 和 Y 坐标
    }
}


void BattleScene::processPicking() {
    for (int i = 0; i < drops.size(); ++i) {  // 使用下标访问
        DropItem* drop = drops[i];
        for (SimpleCharacter* player : {player1, player2}) {
            if (player->isPicking() && player->collidesWithItem(drop)) {
                drop->applyTo(player);  // 应用掉落物效果
                removeItem(drop);
                delete drop;
                drops.removeAt(i);  // 使用 removeAt 删除元素
                break;
            }
        }
    }
}




void BattleScene::spawnRandomDrop() {
    int randType = QRandomGenerator::global()->bounded(7); // 0~6
    DropType type = static_cast<DropType>(randType);
    QString img = ":/Items/box.png"; // 临时用默认图
    DropItem* drop = new DropItem(type, img);
    drop->setPos(QPointF(100 + rand() % 1000, 0)); // 随机 x 轴顶部掉落
    addItem(drop);
    drops.push_back(drop);
}

