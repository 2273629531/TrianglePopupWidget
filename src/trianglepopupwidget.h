#ifndef TRIANGLEPOPUPWIDGET_H
#define TRIANGLEPOPUPWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QSize>

class TrianglePopupWidget: public QWidget
{
    Q_OBJECT
public:
    TrianglePopupWidget(QPoint triangleStartPosition
                        ,QSize rectSize,QRect windowGeometry=QRect(0,0,1920,1080),QWidget *parent = 0);
    ~TrianglePopupWidget();


    // 设置中间区域widget;
    void addCenterWidget(QWidget* widget);

    void setTriangleSize(const QSize &triangleSize);

    QRect windowGeometry() const;
    void setWindowGeometry(const QRect &windowGeometry);

    void setMargins(int left, int top, int right, int bottom);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &backgroundColor);

protected:
    void paintEvent(QPaintEvent *);
private:
    // 小三角起始位置;
    QPoint m_triangleStartPosition;
    // 小三角的size;
    QSize m_triangleSize;
    // 是否绘制阴影
    int m_isDrawShadowOrNot;
    // 内容矩形的长宽
    QSize m_rectSize;
    QColor m_backgroundColor;

    QLayout* m_layout;
    //qmaindow大小
    QRect m_windowGeometry;
    void calculateGeometry();

};

#endif // TRIANGLEPOPUPWIDGET_H
