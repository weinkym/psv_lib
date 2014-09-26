#include <QGraphicsScene>
#include "psv_item.h"

PSV_Item::PSV_Item(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_isBeginSet(false)
    , m_isAutoUpdate(true)
    , m_isAdvancetable(false)
    , m_defaultColor(Qt::black)
    , m_rect(QRectF(0,0,600,400))
    , m_margin(3)
{
//    initDefaultParam();
}


PSV_Item::PSV_Item(const QMap<PSV::ATTRIBUTE_ROLE, QVariant> &param, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_isBeginSet(false)
    , m_isAutoUpdate(true)
    , m_isAdvancetable(false)
    , m_defaultColor(Qt::black)
    , m_rect(QRectF(0,0,600,400))
    , m_margin(3)
    , m_param(param)
{
//    initDefaultParam();
//    QMapIterator<PSV::ATTRIBUTE_ROLE, QVariant> iter(param);
//    while(iter.hasNext())
//    {
//        iter.next();
//        m_param.insert(iter.key(),iter.value());
//    }
    if(param.contains(PSV::boundingRect))
    {
        m_rect = param.value(PSV::boundingRect).toRectF();
    }
    if(param.contains(PSV::dx))
    {
        m_itemPointParam.m_dx = param.value(PSV::dx).toDouble();
    }
    if(param.contains(PSV::dy))
    {
        m_itemPointParam.m_dy = param.value(PSV::dy).toDouble();
    }
    if(param.contains(PSV::dw))
    {
        m_itemPointParam.m_dw = param.value(PSV::dw).toDouble();
    }
    if(param.contains(PSV::dh))
    {
        m_itemPointParam.m_dh = param.value(PSV::dh).toDouble();
    }
}

PSV_Item::~PSV_Item()
{
    //
}

//int PSV_Item::type() const
//{
//    return PSV::psvItem;
//}

QRectF PSV_Item::boundingRect() const
{
    return m_rect;
}

QPainterPath PSV_Item::shape() const
{
    return m_painterPath;
}

void PSV_Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    PSV_NOUSED(painter);
    PSV_NOUSED(option);
    PSV_NOUSED(widget);
    return;
}

void PSV_Item::beginSet()
{
    m_isBeginSet = true;
    m_isAutoUpdate = false;
}

void PSV_Item::endSet()
{
    if(m_isBeginSet)
    {
        if(!m_isAutoUpdate)
        {
            m_isAutoUpdate = true;
            refreshItem();
        }
    }
    else
    {
        PSV_Public::printMes("请设置对应的起始设置标识PSV_Item::beginSet()","warning:警告");
    }
}

void PSV_Item::refreshItem()
{
    if(clearAll())
    {
        refreshRect();
        updateItem();
    }
}

void PSV_Item::setData(PSV::ATTRIBUTE_ROLE role, const QVariant &value, bool isUpdate)
{
    PSV_NOUSED(role);
    PSV_NOUSED(value);
    PSV_NOUSED(isUpdate);
}

bool PSV_Item::clearAll()
{
    QGraphicsScene *scene = this->scene();
    QList<QGraphicsItem*> chirldrenItem = this->childItems();
    if(scene != NULL)
    {
        for(int i = 0; i < chirldrenItem.count(); ++i)
        {
            scene->removeItem(chirldrenItem.at(i));
        }
        setItemNull();//设为NULL
        return true;
    }
    return false;
}

void PSV_Item::advance(int phase)
{
    if(phase != 0 && m_isAdvancetable)
    {
        refreshItem();
    }
}

void PSV_Item::refreshRect()
{
    QGraphicsScene *scene = this->scene();
    if(scene != NULL && m_isAdvancetable)
    {
        adjustPointParam();
        QRectF rect = scene->sceneRect();
        m_rect = QRectF(rect.x() + m_itemPointParam.m_dx * rect.width()
                        ,rect.y() + m_itemPointParam.m_dy * rect.height()
                        ,m_itemPointParam.m_dw * rect.width()
                        ,m_itemPointParam.m_dh * rect.height());
    }
}

void PSV_Item::initDefaultParam()
{
//    m_param.clear();
//    m_param.insert(PSV::defaultColor,QColor(Qt::black));
//    m_param.insert(PSV::margin,3.0);
//    m_isBeginSet = false;
//    m_isAutoUpdate = true;
//    m_isAdvancetable = false;
//    m_defaultColor = QColor(Qt::black);
//    m_rect = QRectF(0,0,600,400);
//    m_margin = 3;
}

void PSV_Item::adjustPointParam()
{
    if(m_itemPointParam.m_dx < 0 && m_itemPointParam.m_dx > 1)
    {
        m_itemPointParam.m_dx = 0;
    }
    if(m_itemPointParam.m_dy < 0 && m_itemPointParam.m_dy > 1)
    {
        m_itemPointParam.m_dy = 0;
    }
    if(m_itemPointParam.m_dw < 0 && m_itemPointParam.m_dw > 1)
    {
        m_itemPointParam.m_dw = 1;
    }
    if(m_itemPointParam.m_dh < 0 && m_itemPointParam.m_dh > 1)
    {
        m_itemPointParam.m_dh = 1;
    }
}
