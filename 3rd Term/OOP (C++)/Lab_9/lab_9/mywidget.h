#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "figures.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>

class myWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myWidget(QWidget *parent = nullptr);
//    myWidget(QWidget *parent = nullptr) : QWidget(parent)
//    {
//        setMouseTracking(true);
//    }
protected:
    figure *draggedFigure{nullptr};

    void paintEvent(QPaintEvent* P_event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // MYWIDGET_H
