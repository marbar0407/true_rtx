#pragma GCC optimize("unroll-loops,O3,Ofast")
#pragma once

#include <bits/stdc++.h>
#include "geom.h"
using namespace std;

const int WIDE = 1024;
const int BRIGHT = 255;
const int HEIGHT = 1024;

class pixel {
public:
    double r, g, b;
    pixel(double rr = 0, double gg = 0, double bb = 0) : r(rr), g(gg), b(bb) {}
};

ostream& operator<<(ostream &out, pixel a) {
    out << (int)(a.r * BRIGHT) << " " << (int)(a.g * BRIGHT) << " " << (int)(a.b * BRIGHT);
    return out;
}

void baza(ofstream &fout, vector<pixel> &output) {
    fout << "P3\n";
    fout << WIDE << " " << HEIGHT << "\n";
    fout << BRIGHT << "\n";
    for (int i = 0; i < HEIGHT * WIDE; i++) {
        fout << output[i] << "\n";
    }
}

void trugol(vector<pixel> &screen, Point a, Point b, Point c) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDE; ++j) {
            Point p = {(double)i, (double)j};
            if (within(a, b, c, p) && within(a, c, b, p)) {
                screen[i * WIDE + j] = {0, 0, 0};
            }
        }
    }
}

void grad(vector<pixel> &screen) {
    double h = HEIGHT,
            w = WIDE;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDE; ++j) {
            screen[i * WIDE + j].r = (i / h);
            screen[i * WIDE + j].g = (j / w);
            screen[i * WIDE + j].b = (((i + j) % WIDE) / w);
        }
    }
}

int main() {
    ofstream fout;
    fout.open("image.ppm");

    vector<pixel> screen(WIDE * HEIGHT);
    grad(screen);
    trugol(screen, {1000, 1000}, {1, 5}, {300, 700});
    baza(fout, screen);
}