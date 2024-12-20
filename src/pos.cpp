#include "pos.h"
#include <proj.h>
#include <iostream>
#include "proj_class.cpp"
using namespace std;

// Initialisation des membres statiques
PJ *Proj::pj_wgs84 = nullptr;
PJ *Proj::pj_lambert93 = nullptr;
PJ_CONTEXT *Proj::ctx = nullptr;

Pos::Pos() : _lat(0), _lon(0), _alt(0), _x(0), _y(0), _z(0) {
    transform_glob_loc(0, 0, 0);
}

Pos::Pos(long double lat, long double lon, long double alt) 
    : _lat(lat), _lon(lon), _alt(alt), _x(0), _y(0), _z(0) {
    transform_glob_loc(lat, lon, alt);
}

Pos::~Pos() {
}

void Pos::transform_glob_loc(long double lat, long double lon, long double alt) {
    if (!Proj::pj_lambert93) {
        std::cerr << "Erreur : Lambert93 non initialisé." << std::endl;
        return;
    }

    PJ_COORD coord_in = proj_coord(static_cast<double>(lon), static_cast<double>(lat), 
                                   static_cast<double>(alt), 0);
    PJ_COORD coord_out = proj_trans(Proj::pj_lambert93, PJ_FWD, coord_in);

    if (proj_errno(Proj::pj_lambert93) != 0) {
        std::cerr << "Erreur de transformation des coordonnées." << std::endl;
        return;
    }

    _x = static_cast<long double>(coord_out.xy.x);
    _y = static_cast<long double>(coord_out.xy.y);
    _z = alt;
}

std::ostream& operator<<(std::ostream& stream, const Pos& p) {
    stream << p._x << " " << p._y << " " << p._z;
    return stream;
}

std::istream& operator>>(std::istream& stream, Pos& p) {
    std::string lat, lon, alt;

    std::getline(stream, lat, ' ');
    std::getline(stream, lon, ' ');
    std::getline(stream, alt);

    if (lat.empty() || lon.empty() || alt.empty()) {
        return stream;
    } else {
        p._lat = std::stold(lat); // Conversion vers long double
        p._lon = std::stold(lon);
        p._alt = std::stold(alt);
        p.transform_glob_loc(p._lat, p._lon, p._alt);
    }

    return stream;
}
