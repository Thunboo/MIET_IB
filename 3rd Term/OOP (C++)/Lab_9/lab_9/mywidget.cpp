#include "mywidget.h"

myWidget::myWidget(QWidget *parent) : QWidget{parent}
{
    setMouseTracking(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

void myWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);    // Prevents "unused variable warning"
    QPainter painter(this); // Takes paint device as an input, i.e.: QWidget
    painter.setRenderHint(QPainter::Antialiasing); // Enables antialiasing, which can improve the appearance of lines and curves.

    for (auto &f : figures)
    {
            f->paint(&painter);
    }
}

void myWidget::mouseMoveEvent(QMouseEvent* event)
{
    Point mousePos(event->pos());

    for (auto& f: figures)
    {
        if (f->isInside(mousePos))
        {
            f->setInvColor();
        }
        else
            f->setOrigColor();
    }
    if (draggedFigure != nullptr)
    {
        draggedFigure->setPos(mousePos + draggedFigure->getOffset());
        draggedFigure->setDraggedColor();
    }
    this->update();
}

void myWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) // If LMB is clicked
    {
        Point mousePos(event->pos());
        for (auto& f: figures)
        {
            if (f->isInside(mousePos))
            {
                draggedFigure = &*f;
                // f - is a reference to a pointer
                // so *f - is dereference of the pointer
                // so that we receive an actual pointer value - actual figure
                // then we take an address of that particular figure

                //The &*f syntax ensures that the correct pointer is assigned
                //          without creating unnecessary copies or references
                draggedFigure->setDraggedColor();
                draggedFigure->setOffset(draggedFigure->getPointsCoords()[0] - mousePos);
                break;
            }
        }
        this->update();
    }
    if (event->button() == Qt::RightButton)
    {
        Point mousePos(event->pos());
        for (auto fig = figures.begin(); fig != figures.end(); ++fig)
        {
            if ((*fig)->isInside(mousePos))
            {
                QMenu menu(this); // Constructing a menu within QWidget - param
                QAction *deleteAction = menu.addAction("Delete");
                // Connecting "deleteAction" to an actual code
                connect(deleteAction, &QAction::triggered, this, [this, fig](){
                    figures.erase(fig);
                    update(); // QWidget update method
                });
                menu.exec(event->globalPosition().toPoint());
                break;
            }
        }

    }
}

void myWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (draggedFigure != nullptr)
        {
            draggedFigure->setInvColor();
        }
        draggedFigure = nullptr;
        this->update();
    }
}
