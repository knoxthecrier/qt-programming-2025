#include "Platform.h"
#include <QBrush>
#include <QPen>

// 构造函数：根据提供的参数设置平台的位置和大小
Platform::Platform(qreal x, qreal y, qreal width, qreal height)
    : width(width), height(height) {
    // 设置平台的矩形区域
    setRect(x, y, width, height);
    // 默认平台颜色为灰色
    setBrush(QBrush(Qt::gray));
    setPen(QPen(Qt::black));  // 设置平台的边框为黑色
}

// 可选：设置平台的颜色
void Platform::setPlatformColor(const QColor& color) {
    setBrush(QBrush(color));  // 改变平台的颜色
}
