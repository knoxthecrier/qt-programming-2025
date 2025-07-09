#include "Platform.h"
#include <QBrush>
#include <QPen>

Platform::Platform(qreal x, qreal y, qreal width, qreal height)
    : width(width), height(height) {
    // 设置平台的矩形区域，直接设置大小
    setRect(0, 0, width, height);  // 设置平台的尺寸（从0, 0开始）

    // 设置平台的位置，调整平台位置
    setPos(x, y);  // 设置平台的位置（x, y）

    // 默认平台颜色为灰色
    /*setBrush(QBrush(Qt::gray));
    setPen(QPen(Qt::black)); // 设置平台的边框为黑色*/
    setPen(QPen(Qt::transparent));  // 设置平台的边框为透明
}


// 可选：设置平台的颜色
void Platform::setPlatformColor(const QColor& color) {
    setBrush(QBrush(color));  // 改变平台的颜色
}
