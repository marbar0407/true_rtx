#include <bits/stdc++.h>


using namespace std;


const double eps = 1e-9;

bool equal(double x, double y) {
    if(abs(x - y) < eps) return true;
    return false;
}

bool more(double x, double y) {
    if(x > y + eps) return true;
    return false;
}

bool more_and_more(double x, double y) {
    if(x > y - eps) return true;
    return false;
}


class color {
public:
    double r, g, b;

    explicit color(double rr = 0, double gg = 0, double bb = 0) : r(rr), g(gg), b(bb) {}

    [[nodiscard]] color ColorRev() const {
        return color(1 - r, 1 - g, 1 - b);
    }

    color operator*(double k) const {
        return color(min(r * k, 1.0), min(g * k, 1.0), min(b * k, 1.0));
    }
};

class point {
public:
    double x;
    double y;
    double z;

    point() {}

    point(double x, double y, double z) :
            x(x),
            y(y),
            z(z) {}
};

class vec {
public:
    double x{}, y{}, z{};

    vec() = default;

    vec(point a, point b) {
        x = b.x - a.x;
        y = b.y - a.y;
        z = b.z - a.z;
    }

    vec(point a) {
        x = a.x;
        y = a.y;
        z = a.z;
    }

    [[nodiscard]] double len() const {
        return sqrt(x * x + y * y + z * z);
    }

    vec operator+(double a) const { return {point(x + a, y + a, z + a)}; }
    vec operator+(vec a) const { return {point(x + a.x, y + a.y, z + a.z)}; }
    vec operator+(point a) const { return {point(x + a.x, y + a.y, z + a.z)}; }

    vec operator-(double a) const { return {point(x - a, y - a, z - a)}; }
    vec operator-(vec a) const { return {point(x - a.x, y - a.y, z - a.z)}; }
    vec operator-(point a) const { return {point(x - a.x, y - a.y, z - a.z)}; }


    [[nodiscard]] vec m(double k) const {
        return vec(point(x * k, y * k, z * k));
    }

    double operator%(vec a) const {
        return x * a.x + y * a.y + z * a.z;
    }

    vec norm() const { return {point(x / len(), y / len(), z / len())}; }

};

point shift(point nw, vec a) {
    return {nw.x + a.x, nw.y + a.y, nw.z + a.z};
}

class sphere {
public:
    point center;
    double r{};
    color col;

    sphere() = default;

    sphere(point centre, double r, color cl) : center(centre), r(r), col(cl) {}

    [[nodiscard]] shared_ptr<pair<double, double>> intersect(vec v, point a) const {
        vec u = vec(center, a);
        double discriminant = ((v % u) * 2) * ((v % u) * 2) - 4 * (v % v) * (u % u - r * r);
        if (discriminant < 0) {
            return nullptr;
        }
        double t1 = (-2 * (u % v) + sqrt(discriminant)) / (2 * (v % v));
        double t2 = (-2 * (u % v) - sqrt(discriminant)) / (2 * (v % v));
        return make_shared<pair<double, double>>(t1, t2);
    }
};

class light {
public:
    point center;
    double intense{};

    light() = default;

    light(point c, double i) : center(c), intense(i) {}
};
