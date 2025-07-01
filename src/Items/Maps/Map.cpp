#include "Map.h"

Map::Map(QGraphicsItem* parent, const QString& pixmapPath)
    : Item(parent, pixmapPath) {}

void Map::scaleToFitScene(QGraphicsScene* scene) {
    QRectF sceneRect = scene->sceneRect();
    QRectF itemRect = boundingRect();

    qreal scaleX = sceneRect.width() / itemRect.width();
    qreal scaleY = sceneRect.height() / itemRect.height();
    qreal scaleFactor = qMin(scaleX, scaleY);

    setTransform(QTransform::fromScale(scaleFactor, scaleFactor), true);

    // 居中地图（可选）
    setPos((sceneRect.width() - boundingRect().width() * scaleFactor) / 2,
           (sceneRect.height() - boundingRect().height() * scaleFactor) / 2);
}

qreal Map::getFloorHeight() {
    auto sceneRect = sceneBoundingRect();
    return sceneRect.top() + (sceneRect.height() * 0.5);  // 默认中线
}

QPointF Map::getSpawnPos() {
    auto rect = sceneBoundingRect();
    return QPointF((rect.left() + rect.right()) / 2, getFloorHeight());
}
