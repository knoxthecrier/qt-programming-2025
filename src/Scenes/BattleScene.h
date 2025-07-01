#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/SimpleCharacter.h"

class BattleScene : public Scene {
    Q_OBJECT

public:
    explicit BattleScene(QObject* parent = nullptr);

    void processInput() override;
    void processMovement() override;
    void processPicking() override;

protected slots:
    void update() override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    Map* map;
    SimpleCharacter* player1;
};

#endif // BATTLESCENE_H
