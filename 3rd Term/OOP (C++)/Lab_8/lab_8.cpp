//cmd -> g++ lab_8.cpp -o lab.exe && lab.exe

#include <iostream>
#include <vector>
#include <numeric>

template <typename T>
class Point
{
public: 
    T x{0}, y{0};
    Point() = default; // Leads to the default initialization for member variables
    Point(T x, T y) : x(x), y(y) {}
    Point operator+ (const Point &first)
    {
        return Point (x + first.x, y + first.y);
    }
    Point operator- (const Point &first)
    {
        return Point (x - first.x, y - first.y);
    }
    const Point& operator+= (const Point &second)
    {
        this->x += second.x;
        this->y += second.y;
        return *this;
    }
    Point operator* (int num)
    {
        return Point (x * num,  y * num);
    }
    Point operator/ (int num)
    {
        return Point (x / num,  y / num);
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};


template <typename T>
T CalcVectorAVG(std::vector<T> &vec) 
{
    T AVG{}; // Also leads to default initialization value, i.e int, float. double = 0
    for (const auto& v: vec)
    {
        AVG += v;
    }
    return AVG / static_cast<int>(vec.size()); // static_cast force converts datatype to <int>
};

int main()
{
    std::vector<int> intVector = {1, 2, 3, 4, -5, -6};
    std::cout << "Average of int vector: " << CalcVectorAVG(intVector) << std::endl; 

    std::vector<float> floatVector = {1.1, 2.2, 3.3, 4.4, 5.9};
    std::cout << "Average of float vector: " << CalcVectorAVG(floatVector) << std::endl;

    std::vector<Point<int>> pointVector = {{1, 2}, {3, 4}, {5, 6}, {7, 77}};
    Point<int> averagePoint = CalcVectorAVG(pointVector);
    std::cout << "Average of point vector: "<< averagePoint << std::endl;

    return 0;
}