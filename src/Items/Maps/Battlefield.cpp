#include "Battlefield.h"

Battlefield::Battlefield(QGraphicsItem* parent)
    : Map(parent, ":/Background/Items/Background/newBackground.png") {}

qreal Battlefield::getFloorHeight() {
    auto sceneRect = sceneBoundingRect();
    return (sceneRect.bottom()-150) ;
}
