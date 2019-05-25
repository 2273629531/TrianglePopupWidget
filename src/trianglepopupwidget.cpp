#include "trianglepopupwidget.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#define SHADOW_WIDTH 0                 // 窗口阴影宽度;
#define TRIANGLE_WIDTH 15               // 小三角的宽度;
#define TRIANGLE_HEIGHT 10              // 小三角的高度;
#define BORDER_RADIUS 5                 // 窗口边角的弧度;


TrianglePopupWidget::TrianglePopupWidget(QPoint triangleStartPosition
                                         ,QSize rectSize
                                         ,QRect windowGeometry
                                         ,QWidget *parent)
    : QWidget(parent)
    , m_rectSize(rectSize)
    , m_triangleStartPosition(triangleStartPosition)
    , m_isDrawShadowOrNot(false)
    , m_windowGeometry(windowGeometry)
    , m_layout(NULL)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_triangleSize = QSize(TRIANGLE_WIDTH,TRIANGLE_HEIGHT);
    m_backgroundColor = QColor(255,255,255);
    // 设置阴影边框;
    if(m_isDrawShadowOrNot)
    {
        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(0, 0);
        shadowEffect->setColor(Qt::gray);
        shadowEffect->setBlurRadius(SHADOW_WIDTH);
        this->setGraphicsEffect(shadowEffect);
    }

    calculateGeometry();


}


TrianglePopupWidget::~TrianglePopupWidget()
{

}

//计算整个widget的Geometry
void TrianglePopupWidget::calculateGeometry()
{

    int x=0;
    int y=0;
    int width = m_rectSize.width();
    int height = m_rectSize.height()+m_triangleSize.height();

    int standard_startX = m_triangleStartPosition.x()-m_rectSize.width()/2;
    int standard_startY = m_triangleStartPosition.y()-m_triangleSize.height()-m_rectSize.height();
    int standard_endX = m_triangleStartPosition.x()-m_rectSize.width()/2+width;
    int standard_endY = m_triangleStartPosition.y()-m_triangleSize.height()-m_rectSize.height() + height;

    if(standard_startX<m_windowGeometry.x()+10)
    {
        standard_startX =  m_windowGeometry.x()+10;
    }
    if(standard_endX>m_windowGeometry.y()+m_windowGeometry.width()-10)
    {
        standard_startX =  standard_startX - (standard_endX-(m_windowGeometry.y()+m_windowGeometry.width()-10));
    }

    //微调
    if(m_triangleStartPosition.x()<standard_startX+m_triangleSize.width()/2+BORDER_RADIUS)
    {
        standard_startX = m_triangleStartPosition.x() - BORDER_RADIUS - m_triangleSize.width()/2;
    }
    //微调
    if(m_triangleStartPosition.x()>standard_startX+width-m_triangleSize.width()/2-BORDER_RADIUS )
    {
        standard_startX = standard_startX+m_triangleSize.width()/2+BORDER_RADIUS ;
    }

    x = standard_startX;
    y = standard_startY;

    this->setGeometry(x,y,width,height);
}

void TrianglePopupWidget::addCenterWidget(QWidget* widget)
{
    if(NULL == m_layout)
    {
        m_layout = new QHBoxLayout(this);
        m_layout->setSpacing(10);
        m_layout->setContentsMargins(10,10,10,10+TRIANGLE_HEIGHT);
    }
    m_layout->addWidget(widget);
}

void TrianglePopupWidget::setMargins(int left,int top,int right,int bottom)
{
    if(NULL != m_layout)
    {
        m_layout->setContentsMargins(left,top,right,bottom+TRIANGLE_HEIGHT);
    }
}

void TrianglePopupWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backgroundColor);

    // 小三角区域
    QPolygon trianglePolygon;
    QPoint pt_triStartPosRelaThis(m_triangleStartPosition.x()-geometry().x(),
                                   m_triangleStartPosition.y()-geometry().y());

//    int x1=m_triangleStartPosition.x()-geometry().x();
//    int y1=m_triangleStartPosition.y()-geometry().y();
//    int x2=pt_triStartPosRelaThis.x() + m_triangleSize.width() / 2;
//    int y2=pt_triStartPosRelaThis.y()-m_triangleSize.height();
//    int x3=pt_triStartPosRelaThis.x() - m_triangleSize.width() / 2;
//    int y3=pt_triStartPosRelaThis.y()-m_triangleSize.height();

    trianglePolygon << pt_triStartPosRelaThis;
    trianglePolygon << QPoint(pt_triStartPosRelaThis.x() + m_triangleSize.width() / 2
                              , pt_triStartPosRelaThis.y()-m_triangleSize.height());
    trianglePolygon << QPoint(pt_triStartPosRelaThis.x() - m_triangleSize.width() / 2
                              , pt_triStartPosRelaThis.y()-m_triangleSize.height());

    QPainterPath drawPath;
    //矩形区域
    drawPath.addRoundedRect(QRect(0,0,m_rectSize.width(),m_rectSize.height()),BORDER_RADIUS,BORDER_RADIUS);
    // Rect + Triangle;
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);

}
QColor TrianglePopupWidget::backgroundColor() const
{
    return m_backgroundColor;
}

void TrianglePopupWidget::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

QRect TrianglePopupWidget::windowGeometry() const
{
    return m_windowGeometry;
}

void TrianglePopupWidget::setWindowGeometry(const QRect &windowGeometry)
{
    m_windowGeometry = windowGeometry;
}


void TrianglePopupWidget::setTriangleSize(const QSize &triangleSize)
{
    m_triangleSize = triangleSize;
}



