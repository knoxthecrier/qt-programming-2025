#include "Scene.h"
#include <QDateTime>

Scene::Scene(QObject* parent) : QGraphicsScene(parent), timer(new QTimer(this)) {
    connect(timer, &QTimer::timeout, this, &Scene::update);
}

void Scene::startLoop() {
    timer->start(1000 / 90); // 90 FPS
}

void Scene::update() {
    auto currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

    if (lastTime == -1) {
        deltaTime = 0;
    } else {
        deltaTime = (currentTime - lastTime) / 1000.0;
    }

    lastTime = currentTime;

    processInput();
    processMovement();
    processPicking();
}

void Scene::processInput() {}
void Scene::processMovement() {}
void Scene::processPicking() {}
