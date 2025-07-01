#ifndef MAP_H
#define MAP_H

#include "../Item.h"
#include <QGraphicsScene>

class Map : public Item {
public:
    explicit Map(QGraphicsItem* parent = nullptr, const QString& pixmapPath = "");

    // 适配场景大小（缩放地图贴图）
    void scaleToFitScene(QGraphicsScene* scene);

    // 获取地面 Y 坐标（默认值可被重写）
    virtual qreal getFloorHeight();

    // 获取出生位置（默认地图中下方中间）
    virtual QPointF getSpawnPos();
};

#endif // MAP_H
