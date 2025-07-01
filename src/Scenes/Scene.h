#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Scene(QObject* parent = nullptr);

    void startLoop();

    virtual void processInput();
    virtual void processMovement();
    virtual void processPicking();

protected slots:
    virtual void update();

protected:
    qreal deltaTime = 0.0; // 单位：秒

private:
    QTimer* timer;
    qint64 lastTime = -1;
};

#endif // SCENE_H
