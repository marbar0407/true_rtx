#pragma GCC optimize("unroll-loops,O3,Ofast")
#pragma once

#include <bits/stdc++.h>
#include "geom.h"

using namespace std;


const int WIDE = 1024,
        HEIGHT = 1024,
        BRIGHT = 255,
        inf = 1e9;


ostream &operator<<(ostream &out, color a) {
    out << (int) (a.r * BRIGHT) << ' ' << (int) (a.g * BRIGHT) << ' ' << (int) (a.b * BRIGHT);
    return out;
}


void siuuuout(ofstream &fout, vector<color> &screen) {
    fout << "P3\n";
    fout << WIDE << " " << HEIGHT << "\n";
    fout << 255 << "\n";
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDE; ++j) {
            fout << screen[i * WIDE + j] << "\n";
        }
    }
}


void grad(vector<color> &screen) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDE; j++) {
            screen[i * WIDE + j].g = ((double) i / HEIGHT);
            screen[i * WIDE + j].b = ((double) j / WIDE);
            screen[i * WIDE + j].r = ((double) ((i + j) % WIDE) / WIDE);
        }
    }
}

signed main() {
    ofstream fout;
    fout.open("image.ppm");
    vector<color> screen(WIDE * HEIGHT);

    grad(screen);

    double h = 1, w = 1, z = 1;

    point cam = point(0, 0, 0);

    vector<light> roollight = {light(point(0, 10, 0), 1),
                               light(point(2, 0, 16), 1.5),
                               light(point(0, 0, 16), 0.75)};
    vector<sphere> smeshariki = {sphere(point(2, 4, 16), 2, color(1, 0.35, 0)),
                                 sphere(point(-2, 4, 16), 0.15, color(0.2, 0.2, 1))};

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDE; ++j) {
            color c = screen[i * WIDE + j];
            double dist = inf,
                    in = 0;
            for (auto ssh: smeshariki) {
                point xy = point(((double) -w) / 2 + w * ((double) j / (WIDE - 1)),
                                 ((double) h) / 2 - h * ((double) i / (HEIGHT - 1)),
                                 z);
                vec v = vec(cam, xy);
                auto shin = ssh.intersect(v, cam);
                if (shin == nullptr) continue;

                double mn = min(shin->first, shin->second);
                point p = shift(cam, v.m(mn));
                vec onw = vec(cam, p);
                if (more_and_more(onw.len(), dist)) continue;

                c = ssh.col;
                dist = onw.len();

                for (auto rool: roollight) {
                    int f = 1;
                    vec tow = vec(rool.center, p);
                    for (auto sh: smeshariki) {
                        auto inter = sh.intersect(tow, rool.center);
                        if (inter == nullptr) continue;
                        if ((more_and_more(inter->first, 0) && more(1.0, inter->first + eps)) ||
                            (more_and_more(inter->second, 0) && more(1.0, inter->second + eps))) {
                            f = 0;
                            break;
                        }
                    }

                    if (!f) continue;

                    auto pp = ssh.intersect(tow, rool.center);
                    if (more_and_more(eps, abs(1 - min(pp->first, pp->second)))) {
                        vec base = vec(ssh.center, p);
                        in += rool.intense * (base.norm() % tow.m(-1).norm());
                    }
                }
            }
            if (!equal(dist, inf)) screen[i * WIDE + j] = c * in;
        }
    }

    siuuuout(fout, screen);
}
