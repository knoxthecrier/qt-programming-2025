#include "BattleScene.h"
#include <QKeyEvent>
#include "../Items/Maps/Battlefield.h"

BattleScene::BattleScene(QObject* parent) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);

    map = new Battlefield();
    addItem(map);
    map->scaleToFitScene(this);

    player1 = new SimpleCharacter(":/Characters/Items/Characters/c1stand.png",
                                  ":/Characters/Items/Characters/c1crouch.png");
    addItem(player1);
    player1->setPos(map->getSpawnPos());

    player1->setWeapon(WeaponType::Fist);
}

void BattleScene::processInput() {
    if (player1) player1->processInput();
}

void BattleScene::keyPressEvent(QKeyEvent* event) {
    if (!player1) return;

    switch (event->key()) {
    case Qt::Key_A: player1->setLeftDown(true); break;
    case Qt::Key_D: player1->setRightDown(true); break;
    case Qt::Key_S: player1->setCrouching(true); break;
    case Qt::Key_W: player1->startJump(); break;
    case Qt::Key_J: player1->setPickDown(true); break;
    default: Scene::keyPressEvent(event);
    }
}

void BattleScene::keyReleaseEvent(QKeyEvent* event) {
    if (!player1) return;

    switch (event->key()) {
    case Qt::Key_A: player1->setLeftDown(false); break;
    case Qt::Key_D: player1->setRightDown(false); break;
    case Qt::Key_S: player1->setCrouching(false); break;
    case Qt::Key_J: player1->setPickDown(false); break;
    default: Scene::keyReleaseEvent(event);
    }
}

void BattleScene::update() {
    Scene::update();
}

void BattleScene::processMovement() {
    if (player1 && !player1->isCrouching()) {
        QPointF pos = player1->pos();
        QPointF velocity = player1->getVelocity();

        pos.rx() += velocity.x() * deltaTime;
        player1->applyVerticalMovement(deltaTime, map->getFloorHeight());
        player1->setX(pos.x());
    }
}

void BattleScene::processPicking() {
    // TODO: 实现拾取逻辑（下一步可加武器掉落物）
}
