#ifndef PLATFORM_H
#define PLATFORM_H
#include <QGraphicsRectItem>

class Platform : public QGraphicsRectItem {
public:
    // 构造函数，设置平台的x, y位置，宽度和高度
    Platform(qreal x, qreal y, qreal width, qreal height);

    // 可选：为平台设置不同的样式，颜色等
    void setPlatformColor(const QColor& color);

private:
    qreal width;
    qreal height;
};
#endif // PLATFORM_H
