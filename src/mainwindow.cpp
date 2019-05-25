#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trianglepopupwidget.h"
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QPoint pt = this->mapFromGlobal(event->globalPos());


        if(NULL != w)
        {
            w->hide();
            w->setParent(NULL);
            delete w;
            w=NULL;
        }

        w = new TrianglePopupWidget(
                    pt
                    ,QSize(400,100)
                    ,QRect(0,0,800,600)
                    ,this);

        QLabel* textLabel = new QLabel;
        textLabel->setAlignment(Qt::AlignCenter);
        textLabel->setText("ArrowWidget");
        textLabel->setStyleSheet("background-color:red");
        w->addCenterWidget(textLabel);

        QLabel* textLabel2 = new QLabel;
        textLabel2->setAlignment(Qt::AlignCenter);
        textLabel2->setText("DDDDA");
        textLabel2->setStyleSheet("background-color:green");
        w->addCenterWidget(textLabel2);

        QLabel* textLabel3 = new QLabel;
        textLabel3->setAlignment(Qt::AlignCenter);
        textLabel3->setText("bbbb");
        textLabel3->setStyleSheet("background-color:yellow");
        w->addCenterWidget(textLabel3);

        QColor clr(0,0,255);
        w->setBackgroundColor(clr);
        w->show();
    }

}
