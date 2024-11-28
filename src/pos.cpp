#include "pos.h"
#include <proj.h>
#include <iostream>

using namespace std;

class Proj {
public:
    static PJ *pj_wgs84;
    static PJ *pj_lambert93;
    static PJ_CONTEXT *ctx;
};

PJ_CONTEXT *Proj::ctx = proj_context_create();
PJ *Proj::pj_wgs84 = proj_create_crs_to_crs(Proj::ctx, "EPSG:4326", "EPSG:4326", nullptr);
PJ *Proj::pj_lambert93 = proj_create_crs_to_crs(Proj::ctx, "EPSG:4326", "+proj=lcc +lat_1=49 +lat_2=44 +lat_0=46.5 +lon_0=3 +x_0=700000 +y_0=6600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs", nullptr);

Pos::Pos() : _lat(0), _lon(0), _alt(0), _x(0), _y(0), _z(0) {
    transform_glob_loc(0, 0, 0);
}

Pos::Pos(double lat, double lon, double alt) : _lat(lat), _lon(lon), _alt(alt), _x(0), _y(0), _z(0) {
    transform_glob_loc(lat, lon, alt);
}

Pos::~Pos() {
}

void Pos::transform_glob_loc(double lat, double lon, double alt) {
    if (!Proj::pj_wgs84 || !Proj::pj_lambert93) {
        std::cerr << "Erreur d'initialisation des systèmes de coordonnées." << std::endl;
        return;
    }

    // Créer une transformation entre les deux CRS
    PJ *transform = proj_create_crs_to_crs(Proj::ctx, "EPSG:4326",
                                           "+proj=lcc +lat_1=49 +lat_2=44 +lat_0=46.5 +lon_0=3 +x_0=700000 +y_0=6600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs",
                                           nullptr);
    if (!transform) {
        std::cerr << "Erreur de création de la transformation." << std::endl;
        return;
    }

    PJ_COORD coord_in = proj_coord(lon, lat, alt, 0);
    PJ_COORD coord_out = proj_trans(transform, PJ_FWD, coord_in);

    _x = coord_out.xy.x;
    _y = coord_out.xy.y;
    _z = alt;

    proj_destroy(transform);
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
    }
    else{
        p._lat = std::stod(lat);
        p._lon = std::stod(lon);
        p._alt = std::stod(alt);
        p.transform_glob_loc(p._lat, p._lon, p._alt);
    }
   
    return stream;
}