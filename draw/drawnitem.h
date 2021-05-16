#ifndef DRAWNITEM_H
#define DRAWNITEM_H
#include <QGraphicsItem>

const float baseSize = 1.0f;

class DrawnSchema;

class DrawnItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    DrawnItem(DrawnItem *parent, float posGridSize = 0.0f);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    void deleteAll();
    void deleteSelected();

signals:
    void positionChanged();

protected:
    bool mIsHovered;
    float mPosGridSize;
    QPointF mPosGridAnchor;
};

#endif // DRAWNITEM_H
