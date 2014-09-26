#ifndef PSV_ITEM_H
#define PSV_ITEM_H
#include <QGraphicsItem>
#include "psv_public.h"
#include "psv_define.h"

class PSVLIB_API PSV_Item : public QGraphicsItem
{
public:
    PSV_Item(QGraphicsItem * parent = 0 );
    PSV_Item(const QMap<PSV::ATTRIBUTE_ROLE, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_Item();
    virtual int type ()  const = 0;
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void refreshItem();
    virtual void setData(PSV::ATTRIBUTE_ROLE role,const QVariant& value,bool isUpdate = false);
//    QVariant getData(PSV::ATTRIBUTE_ROLE);
    void beginSet();
    void endSet();

protected:
    virtual void updateItem() = 0;
    virtual void setItemNull() = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void advance(int phase);
    bool clearAll();

private:
    void adjustPointParam();
    void refreshRect();
    void initDefaultParam();

protected:
    bool m_isBeginSet;
    bool m_isAutoUpdate;
    bool m_isAdvancetable;
    QColor m_defaultColor;
    QRectF m_rect;
    QPainterPath m_painterPath;
    qreal m_margin;
    qreal m_titlePointSizeRatio;
    QMap<PSV::ATTRIBUTE_ROLE,QVariant> m_param;
    PSV_ItemPointParam m_itemPointParam;
};

#endif // PSV_ITEM_H
