#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <string>
#include <list>
#include <cmath>

#include <QColor>
#include <QPainter>

struct Point {
    int x{0}, y{0};
    Point(int x, int y) : x{x}, y{y} {};
    Point(QPoint point) : x{point.x()}, y{point.y()} {};

    int distance(Point &other);

    Point operator+ (const Point &other){
        return Point(x + other.x, y + other.y);
    }
    Point operator- (const Point &other){
        return Point(x - other.x, y - other.y);
    }
    const Point& operator+= (const Point &other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
};

QColor invertColor(const QColor& color);

class figure
{
public:
    virtual void paint(QPainter* painter) = 0;
    virtual void paintInverted(QPainter* painter) = 0;
    virtual bool isInside(Point point) = 0;

    void setPos(Point point);
    std::vector<Point> getPointsCoords() {return this->points; }

    QColor getColor()        { return this-> currentColor; }
    QColor getOrigColor()    { return this-> originalColor; }
    QColor getInvColor()     { return this-> invertedColor; }
    QColor getDraggedColor() { return this-> draggedColor; }

    void setColor(QString color);
    void setCurColor(QColor color) { this->currentColor = color; }
    void setOrigColor()            { this->currentColor = this-> originalColor; }
    void setInvColor()             { this->currentColor = this-> invertedColor; }
    void setDraggedColor()         { this->currentColor = this-> draggedColor; }

    void setOffset(Point point) {this->offset = point; }
    Point getOffset() {return this->offset; }

protected:
    std::vector<Point> points;
    QColor currentColor;
    QColor originalColor;
    QColor invertedColor;
    QColor draggedColor;
    Point offset{0,0}; // mathematical vector from first [0] point to dragging mouse cursor position
};

extern std::list<std::unique_ptr<figure>> figures; // extern - no memory is allocated. we don't define this right now

class triangle : public figure
{
public:
    triangle(QString color);
    void paint(QPainter *painter) override;
    void paintInverted(QPainter *painter) override;
    bool isInside(Point point) override;
};

class circle : public figure
{
public:
    circle(QString color);
    void paint(QPainter *painter) override;
    void paintInverted(QPainter *painter) override;
    bool isInside(Point point) override;
};

class rectangle : public figure
{
public:
    rectangle(QString color);
    void paint(QPainter *painter) override;
    void paintInverted(QPainter *painter) override;
    bool isInside(Point point) override;
};

#endif // FIGURES_H
