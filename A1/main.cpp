// created by aaiakovlev(can4k)

#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>

constexpr long double EPS = 1e-5;
std::mt19937_64 rnd(57); // random generator

struct Point2D
{
    Point2D() = default;
    Point2D(long double _x, long double _y) : x(_x), y(_y) {}
    long double x;
    long double y;
};

struct Circle2D
{
    Circle2D() = default;

    Circle2D(long double x, long double y, long double radius)
    {
        this->radius = radius;
        center = Point2D(x, y);
    }

    Point2D center;
    long double radius;
};

struct Rectangle2D
{
    Point2D LD; // left & down
    Point2D RT; // right & top

    long double square() const
    {
        return (RT.x - LD.x) * (RT.y - LD.y);
    }
};

std::istream &operator>>(std::istream &is, Point2D &point)
{
    is >> point.x;
    is >> point.y;
    return is;
}

std::istream &operator>>(std::istream &is, Circle2D &circle)
{
    is >> circle.center;
    is >> circle.radius;
    return is;
}

long double p2(long double val)
{
    return val * val;
}

long double dist(const Point2D& a, const Point2D& b)
{
    return sqrtl(p2(a.x - b.x) + p2(a.y - b.y));
}

bool leq(long double a, long double b)
{
    return a + EPS <= b;
}

bool isPointInCircle(const Point2D& point, const Circle2D& circle)
{
    return leq(dist(point, circle.center), circle.radius);
}

long double generateRandom(std::uniform_real_distribution<long double>& dist)
{
    return dist(rnd);
}

Point2D generateRandomPointInRectangle(
    Rectangle2D& rect,
    std::uniform_real_distribution<long double>& dist_x,
    std::uniform_real_distribution<long double>& dist_y)
{
    long double x = generateRandom(dist_x);
    long double y = generateRandom(dist_y);
    return {x, y};
}

bool isPointSuccess(Point2D& tmp, const Circle2D& a, const Circle2D& b, const Circle2D& c)
{
    return (
        isPointInCircle(tmp, a) &&
        isPointInCircle(tmp, b) &&
        isPointInCircle(tmp, c));
}

long double experiment(const Circle2D& a, const Circle2D& b, const Circle2D& c, uint32_t tries, Rectangle2D& rect)
{
    std::uniform_real_distribution<long double> dist_x(rect.LD.x, rect.RT.x);
    std::uniform_real_distribution<long double> dist_y(rect.LD.y, rect.RT.y);

    uint32_t success = 0;

    for (uint32_t i = 0; i < tries; i++)
    {
        Point2D tmp = generateRandomPointInRectangle(rect, dist_x, dist_y);
        if (isPointSuccess(tmp, a, b, c))
        {
            success++;
        }
    }

    return static_cast<long double>(success) / tries;
}

void setupDefaultRectangle(Rectangle2D &rect, const Circle2D& a, const Circle2D& b, const Circle2D& c)
{
    // default rectangle
    long double max_radius = std::max(std::max(a.radius, b.radius), c.radius);
    rect = {
        {
            -max_radius,
            -max_radius,
        },
        {
            max_radius + 1,
            max_radius + 1,
        }};
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#ifdef LOCAL
    freopen("./../input.txt", "r", stdin);
    freopen("./../output.txt", "w", stdout);
#endif

    uint32_t tries = 100000;
    Circle2D a;
    Circle2D b;
    Circle2D c;
    Rectangle2D rect;

#ifdef EXP
    // A1 exp
    std::cin >> tries;
    a = {1.0, 1.0, 1.0};
    b = {1.5, 2.0, sqrtl(5) / 2.0};
    c = {2.0, 1.5, sqrtl(5) / 2.0};

    #ifdef BIG
    rect = {
        {0, 0},
        {3.15, 3.15}};
    #endif

    #ifdef SMALL
    rect = {
        {0.85, 0.85},
        {2.1, 2.1}};
    #endif

#else
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    setupDefaultRectangle(rect, a, b, c);
#endif
    std::cout << std::fixed << std::setprecision(16);

    long double exp_result = experiment(a, b, c, tries, rect);
    std::cout << exp_result * rect.square();
    return 0;
}