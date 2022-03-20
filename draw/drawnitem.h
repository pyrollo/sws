/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DRAWNITEM_H
#define DRAWNITEM_H
#include "drawninteractive.h"

class DrawnSchema;
class DrawnIcon;
class CoreModule;

class DrawnItem : public DrawnInteractive
{
    Q_OBJECT
public:
    virtual ~DrawnItem();

    std::string getType() const { return mType; }
    DrawnSchema *schema() { return mSchema; }
    virtual CoreModule *core() { return nullptr; }


    void setIcon(const QString &filename);
    void alignToGrid(bool align) { mAlignToGrid = align; }

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

signals:
    void positionChanged();

protected:
    std::string mType;
    DrawnSchema *mSchema;
    DrawnIcon *mIcon;
    bool mAlignToGrid;

    DrawnItem(std::string type, DrawnSchema *schema);

    void repositionIcon();
};

#endif // DRAWNITEM_H
