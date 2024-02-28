#ifndef GEOMOCHKA_GEOM_H
#define GEOMOCHKA_GEOM_H

#include <bits/stdc++.h>

using namespace std;
#define double long double

class Point {
public:
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y){}
    Point operator +(Point a) {
        return {x + a.x, y + a.y};
    }
    Point operator -(Point a) {
        return {x - a.x, y - a.y};
    }
    Point turn (double alpha) {
        return {x * cosl(alpha) - y * sinl(alpha),
                y * sinl(alpha) - x * cosl(alpha)};
    }
    double operator /(Point a) {
        return (x * a.x + y * a.y);
    }
    double operator *(Point a) {
        return (x * a.y - y * a.x);
    }
    double len(Point a) {
        return sqrt(x * x + y * y);
    }
};

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool within(Point a, Point b, Point c, Point p) {
    return (((a - b) * (p - b)) * ((p - b) * (c - b)) >= 0 && ((a - b) * (c - b)) * ((a - b) * (p - b)) >= 0);
}

#endif //GEOMOCHKA_GEOM_H
