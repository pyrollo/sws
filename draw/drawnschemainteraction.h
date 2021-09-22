#ifndef DRAWNSCHEMAINTERACTION_H
#define DRAWNSCHEMAINTERACTION_H

class QGraphicsSceneMouseEvent;
class DrawnSchema;
class DrawnItem;

class DrawnSchemaInteraction {
public:
    DrawnSchemaInteraction(DrawnSchema *schema) : mSchema(schema) {}
    virtual ~DrawnSchemaInteraction() {}

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) { (void)(e); (void)(item); }
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) { (void)(e); (void)(item); }
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) { (void)(e); (void)(item); }
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) { (void)(e); (void)(item); }
    virtual void init() {}
    virtual void terminate() {}

protected:
    DrawnSchema *mSchema;
};

#endif // DRAWNSCHEMAINTERACTION_H
