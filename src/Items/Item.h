#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QString>

class Item : public QGraphicsItem {
public:
    explicit Item(QGraphicsItem* parent = nullptr, const QString& pixmapPath = "");

    // 设置贴图
    void setPixmap(const QPixmap& pixmap);

    // 获取内部图像项（例如用于判断尺寸、位置等）
    QGraphicsPixmapItem* getPixmapItem() const;

    // 基础碰撞范围（由 pixmap 决定）
    [[nodiscard]] QRectF boundingRect() const override;

    // 我们不自己绘图，靠 QGraphicsPixmapItem 显示图像
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override {}

protected:
    QGraphicsPixmapItem* pixmapItem = nullptr;
};

#endif // ITEM_H
