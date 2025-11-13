#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>

long double EPS = 1e-5;
std::mt19937_64 rnd(57); // random generator

struct Point2D {
    Point2D() = default;
    Point2D(long double _x, long double _y) : x(_x), y(_y) {}
    long double x;
    long double y;
};

struct Circle2D {
    Circle2D() = default;

    Circle2D(long double x, long double y, long double radius) {
        this->radius = radius;
        center = Point2D(x, y);
    }

    Point2D center;
    long double radius;
};

std::istream& operator>>(std::istream &is, Point2D &point) {
    is >> point.x;
    is >> point.y;
    return is;
}

std::istream& operator>>(std::istream &is, Circle2D &circle) {
    is >> circle.center;
    is >> circle.radius;
    return is;
}

long double p2(long double val) {
    return val * val;
}

long double dist(Point2D a, Point2D b) {
    return sqrtl(p2(a.x - b.x) + p2(a.y - b.y));
}

bool eqs(long double a, long double b) {
    return abs(a - b) < EPS;
}

bool lwr(long double a, long double b) {
    return a + EPS < b;
}

bool isPointInCircle(Point2D point, Circle2D circle) {
    return lwr(dist(point, circle.center), circle.radius);
}

int main() {
#ifdef LOCAL
    freopen("./../input.txt", "r", stdin);
    freopen("./../output.txt", "w", stdout);
#endif

    uint tries = 100;
    Circle2D a;
    Circle2D b;
    Circle2D c;

#ifdef EXP
    // A1 exp
    std::cin >> tries;
    a = {1.0, 1.0, 1.0};
    b = {1.5, 2.0, sqrtl(5) / 2.0};
    c = {2.0, 1.5, sqrtl(5) / 2.0};
#else
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
#endif
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    
}