#include "drawnitem.h"
#include "../gui/guischemascene.h"
#include <QApplication>
#include <cmath>

DrawnItem::DrawnItem(DrawnItem *parent, float posGridSize):
    QObject(), QGraphicsItem(parent), mIsHovered(false), mPosGridSize(posGridSize),
    mPosGridAnchor(0.0f, 0.0f)
{
    if (mPosGridSize > 0.0f)
        setFlags(flags() | QGraphicsItem::ItemSendsGeometryChanges);
}

QVariant DrawnItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange)
        emit positionChanged();

    if (change == ItemPositionChange && mPosGridSize > 0.0f) {
        QPointF newPos = value.toPointF() + mPosGridAnchor;
        qreal xV = round(newPos.x()/mPosGridSize)*mPosGridSize;
        qreal yV = round(newPos.y()/mPosGridSize)*mPosGridSize;
        return QPointF(xV, yV) - mPosGridAnchor;
    }

    return QGraphicsItem::itemChange(change, value);
}

void DrawnItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void DrawnItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = false;
    QGraphicsItem::hoverLeaveEvent(event);
}

