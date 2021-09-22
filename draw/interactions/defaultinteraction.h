#ifndef DEFAULTINTERACTION_H
#define DEFAULTINTERACTION_H
#include "draw/drawnschemainteraction.h"

class DefaultInteraction : public DrawnSchemaInteraction
{
public:
    DefaultInteraction(DrawnSchema *schema);
    ~DefaultInteraction() {}
    void mousePressEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) override;
};

#endif // DEFAULTINTERACTION_H
