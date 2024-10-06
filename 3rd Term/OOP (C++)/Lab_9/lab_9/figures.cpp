#include "figures.h"

std::list<std::unique_ptr<figure>> figures;

int Point::distance(Point &other)
{
    return std::sqrt( std::pow(this->x - other.x, 2) + std::pow(this->y - other.y, 2));
}

QColor invertColor(const QColor& color)
{
    return QColor(255 - color.red(), 255 - color.green(), 255 - color.blue());
}

//////////////////////////////////////////////////

void figure::setColor(QString color)
{
    if (color == "Random")
        this->originalColor = QColor(128 + rand() % 128,
                                     128 + rand() % 128,
                                     128 + rand() % 128);
//        this->originalColor = QColor(rand() % 256, rand() % 256, rand() % 256);
    else
        this->originalColor = QColor(color);

    this->invertedColor = invertColor(this->originalColor);
    this->draggedColor = QColor("#ffffff");
    this->currentColor = this->originalColor;
}

void figure::setPos(Point point)
{
    Point offset = point - this->points[0]; // Calculating one point shift/offset
    for (int i = 0; i < static_cast<int>(points.size()); i++)
    {
        //this->points[i] = this->points[i] + offset;
        this->points[i] += offset;
    }
}

//////////////////////////////////////////////////

triangle::triangle(QString color)
{
    this->setColor(color);
    this->points.push_back(Point(rand()%800, rand()%700));
    this->points.push_back(Point(this->points[this->points.size()-1].x + rand()%100 - 50,
                                 this->points[this->points.size()-1].y + rand()%100 - 50));
    this->points.push_back(Point(this->points[this->points.size()-1].x + rand()%100 - 50,
                                 this->points[this->points.size()-1].y + rand()%100 - 50));
}

void triangle::paint(QPainter *painter)
{
    painter->setPen(this->getColor());
    int amountOfPoints = static_cast<int>(this->points.size());
    for (int i = 0; i < amountOfPoints; i++)
    {
        painter->drawLine(this->points[i].x,     this->points[i].y,
                          this->points[(i + 1) % amountOfPoints].x,
                          this->points[(i + 1) % amountOfPoints].y);
    }
}

void triangle::paintInverted(QPainter *painter)
{
    painter->setPen(invertColor(this->getColor()));
    int amountOfPoints = static_cast<int>(this->points.size());
    for (int i = 0; i < amountOfPoints; i++)
    {
        painter->drawLine(this->points[i].x,     this->points[i].y,
                          this->points[(i + 1) % amountOfPoints].x,
                          this->points[(i + 1) % amountOfPoints].y);
    }
}

bool triangle::isInside(Point point)
{
    QPolygon polygon; // Using polygon to mark the area boundaries
    for (const auto& p: this->points)
    {
        polygon << QPoint(p.x, p.y);
    }
    QRegion region(polygon); // Complete region (full area) within the boundaries
    return region.contains(QPoint(point.x, point.y));
}

//////////////////////////////////////////////////

circle::circle(QString color)
{
    this->setColor(color);
    this->points.push_back(Point(rand() % 800, rand() % 700));
    this->points.push_back(Point(this->points[0].x + rand() % 75,
                                 this->points[0].y + rand() % 75));
}

void circle::paint(QPainter *painter)
{
    painter->setPen(this->getColor());
    QPoint center (points[0].x, points[0].y);
    int radius = points[0].distance(points[1]);
    painter->drawEllipse(center, radius, radius);
}

void circle::paintInverted(QPainter *painter)
{
    painter->setPen(invertColor(this->getColor()));
    QPoint center (points[0].x, points[0].y);
    int radius = points[0].distance(points[1]);
    painter->drawEllipse(center, radius, radius);
}

bool circle::isInside(Point point)
{
    if (this->points[0].distance(point) <= this->points[0].distance(this->points[1]))
        return true;
    return false;
}

//////////////////////////////////////////////////

rectangle::rectangle(QString color)
{
    this->setColor(color);
    this->points.push_back(Point(rand()%800, rand()%700));
    this->points.push_back(Point(this->points[this->points.size()-1].x + rand()%100 - 50,
                                 this->points[this->points.size()-1].y));
    this->points.push_back(Point(this->points[this->points.size()-1].x,
                                 this->points[this->points.size()-1].y + rand()%100 - 50));
    this->points.push_back(Point(this->points[0].x,
                                 this->points[this->points.size() - 1].y));
}

void rectangle::paint(QPainter *painter)
{
    painter->setPen(this->getColor());
    int amountOfPoints = static_cast<int>(this->points.size());
    for (int i = 0; i < amountOfPoints; i++)
    {
        painter->drawLine(this->points[i].x,     this->points[i].y,
                          this->points[(i + 1) % amountOfPoints].x,
                          this->points[(i + 1) % amountOfPoints].y);
    }
}

void rectangle::paintInverted(QPainter *painter)
{
    painter->setPen(invertColor(this->getColor()));
    int amountOfPoints = static_cast<int>(this->points.size());
    for (int i = 0; i < amountOfPoints; i++)
    {
        painter->drawLine(this->points[i].x,     this->points[i].y,
                          this->points[(i + 1) % amountOfPoints].x,
                          this->points[(i + 1) % amountOfPoints].y);
    }
}

bool rectangle::isInside(Point point)
{
    int x = point.x, y = point.y;
        if ((points[0].x <= x && x <= points[1].x && points[0].y <= y && y <= points[2].y)||
            (points[0].x >= x && x >= points[1].x && points[0].y <= y && y <= points[2].y)||
            (points[0].x <= x && x <= points[1].x && points[0].y >= y && y >= points[2].y)||
            (points[0].x >= x && x >= points[1].x && points[0].y >= y && y >= points[2].y))
            return true;
        return false;
}
