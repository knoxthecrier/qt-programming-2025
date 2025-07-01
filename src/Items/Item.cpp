#include "Item.h"
#include <QPixmap>

Item::Item(QGraphicsItem* parent, const QString& pixmapPath)
    : QGraphicsItem(parent) {
    if (!pixmapPath.isEmpty()) {
        QPixmap pix(pixmapPath);
        if (!pix.isNull()) {
            pixmapItem = new QGraphicsPixmapItem(pix, this);
        }
    }
}

void Item::setPixmap(const QPixmap& pixmap) {
    if (!pixmapItem) {
        pixmapItem = new QGraphicsPixmapItem(pixmap, this);
    } else {
        pixmapItem->setPixmap(pixmap);
    }
}

QGraphicsPixmapItem* Item::getPixmapItem() const {
    return pixmapItem;
}

QRectF Item::boundingRect() const {
    if (pixmapItem) {
        return pixmapItem->boundingRect();
    }
    return {};
}
