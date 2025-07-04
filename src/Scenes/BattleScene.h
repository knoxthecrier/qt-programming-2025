#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "../Items/Platform.h"
#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/SimpleCharacter.h"
#include <QGraphicsScene>
class BattleScene : public Scene {
    Q_OBJECT

public:
    explicit BattleScene(QObject* parent = nullptr);

    void processInput() override;
    void processMovement() override;
    void processPicking() override;

    void createPlatforms();  // 用于创建平台
protected slots:
    void update() override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    Map* map;
    SimpleCharacter* player1;
    Platform* platform1;
    Platform* platform2;
    Platform* platform3;
};

#endif // BATTLESCENE_H
