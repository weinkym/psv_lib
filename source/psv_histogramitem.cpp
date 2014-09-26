#include <QBrush>
#include <QPen>
#include <math.h>
#include "psv_histogramitem.h"

PSV_HistogramItem::PSV_HistogramItem(const QMap<PSV::ATTRIBUTE_ROLE, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_obliqueAngle(60)
    , m_cosLength(cos(m_obliqueAngle) * m_rect.width() / 3)
    , m_dimension(3)
    , m_isCuboid(true)
    , m_color(QColor(Qt::darkCyan))
{
    initVariables();
    updateItem();
}

PSV_HistogramItem::~PSV_HistogramItem()
{
    //
}

void PSV_HistogramItem::initVariables()
{
    if(m_param.contains(PSV::boundingRect))
    {
        m_rect = m_param.value(PSV::boundingRect).toRectF();
    }
    if(m_param.contains(PSV::toolTip))
    {
        setToolTip(m_param.value(PSV::toolTip).toString());
    }
    if(m_param.contains(PSV::obliqueAngle))
    {
        m_obliqueAngle = m_param.value(PSV::obliqueAngle).toDouble();
    }
    if(m_param.contains(PSV::cosLength))
    {
        m_cosLength = m_param.value(PSV::cosLength).toDouble();
    }
    if(m_param.contains(PSV::isCuboid))
    {
        m_isCuboid = m_param.value(PSV::isCuboid).toBool();
    }
    if(m_param.contains(PSV::dimension))
    {
        int tempValue = m_param.value(PSV::dimension).toInt();
        if(tempValue == 2 || tempValue == 3)
        {
            m_dimension = tempValue;
        }
    }

    if(m_param.contains(PSV::color))
    {
        m_color = m_param.value(PSV::color).value<QColor>();
    }

    if(m_param.contains(PSV::upPhaseBrush))
    {
        m_upPhaseBrush = m_param.value(PSV::upPhaseBrush).value<QBrush>();
    }
    else
    {
        m_upPhaseBrush = QBrush(QBrush(m_color.lighter(150)));
    }

    if(m_param.contains(PSV::frontPhaseBrush))
    {
        m_frontPhaseBrush = m_param.value(PSV::frontPhaseBrush).value<QBrush>();
    }
    else
    {
        m_frontPhaseBrush = QBrush(QBrush(m_color.darker(100)));
    }
    if(m_param.contains(PSV::sidePhaseBrush))
    {
        m_sidePhaseBrush = m_param.value(PSV::sidePhaseBrush).value<QBrush>();
    }
    else
    {
        m_sidePhaseBrush = QBrush(m_color.darker(200));
    }
}

int PSV_HistogramItem::type() const
{
    return PSV::cuboidItem;
}

void PSV_HistogramItem::updateItem()
{
    {
        QPolygonF polygonF_front;
        polygonF_front.append(m_rect.topLeft());
        polygonF_front.append(m_rect.topRight());
        polygonF_front.append(m_rect.bottomRight());
        polygonF_front.append(m_rect.bottomLeft());
        QGraphicsPolygonItem* item = new QGraphicsPolygonItem(this);
        item->setBrush(m_frontPhaseBrush);
        item->setPen(QPen(m_frontPhaseBrush.color()));
        item->setPolygon(polygonF_front);
    }
    double dy = tan(m_obliqueAngle / 180 * PSV_PI) * m_cosLength;
    if(m_dimension == 2)
    {
        dy = 0.0;
    }
    if(m_isCuboid)
    {
        {
            QPolygonF polygonF_side;
            polygonF_side.append(m_rect.bottomRight());
            polygonF_side.append(m_rect.topRight());
            polygonF_side.append(QPointF(m_rect.right() + m_cosLength, m_rect.top() - dy));
            polygonF_side.append(QPointF(m_rect.right() + m_cosLength, m_rect.bottom() - dy));

            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(this);
            item->setBrush(m_sidePhaseBrush);
            item->setPen(QPen(m_frontPhaseBrush.color()));
            item->setPolygon(polygonF_side);
        }
        {
            QPolygonF polygonF_up;
            polygonF_up.append(m_rect.topRight());
            polygonF_up.append(m_rect.topLeft());
            polygonF_up.append(QPointF(m_rect.left()+ m_cosLength, m_rect.top() - dy));
            polygonF_up.append(QPointF(m_rect.right()+ m_cosLength, m_rect.top() - dy));

            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(this);
            item->setBrush(m_upPhaseBrush);
            item->setPen(QPen(m_frontPhaseBrush.color()));
            item->setPolygon(polygonF_up);
        }
    }
    else
    {
        QRectF rectF(m_rect.x(),m_rect.y() - dy,m_rect.width(),2 * dy);
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rectF,this);
        item->setBrush(m_upPhaseBrush);
        item->setPen(QPen(m_frontPhaseBrush.color()));
        item->setZValue(2);
    }
}

void PSV_HistogramItem::setItemNull()
{
    return;
}
