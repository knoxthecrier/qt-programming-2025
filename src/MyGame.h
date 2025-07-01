#ifndef MYGAME_H
#define MYGAME_H

#include <QMainWindow>
#include <QGraphicsView>
#include "Scenes/BattleScene.h"

class MyGame : public QMainWindow {
    Q_OBJECT

public:
    explicit MyGame(QWidget* parent = nullptr);

private:
    BattleScene* battleScene;
    QGraphicsView* view;
};

#endif // MYGAME_H
