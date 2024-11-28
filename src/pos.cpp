#include "pos.h"
#include <proj.h>
#include <iostream>
//#include "Proj.h"

using namespace std;

class Proj {
public:
    static PJ *pj_wgs84;
    static PJ *pj_lambert93;
    static PJ_CONTEXT *ctx;
};



PJ_CONTEXT *Proj::ctx = proj_context_create();
PJ *Proj::pj_wgs84 = proj_create(Proj::ctx, "EPSG:4326");
PJ *Proj::pj_lambert93 = proj_create(Proj::ctx, "+proj=lcc +lat_1=49 +lat_2=44 +lat_0=46.5 +lon_0=3 +x_0=700000 +y_0=6600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs");



Pos::Pos() : _lat(0), _lon(0), _alt(0), _x(0), _y(0), _z(0) {
    transform_glob_loc(0, 0, 0);
}


Pos::Pos(double lat, double lon, double alt) {
    _lat = lat;
    _lon = lon;
    _alt = alt;
    transform_glob_loc(lat, lon, alt);
}

Pos::~Pos() {
}


void Pos::transform_glob_loc(double lat, double lon, double alt){
    if (!Proj::pj_wgs84 || !Proj::pj_lambert93) {
        std::cerr << "Erreur d'initialisation des systèmes de coordonnées." << std::endl;
    }

    // Créer une transformation entre les deux CRS
    PJ *transform = proj_create_crs_to_crs(Proj::ctx, "EPSG:4326",
                                           "+proj=lcc +lat_1=49 +lat_2=44 +lat_0=46.5 +lon_0=3 +x_0=700000 +y_0=6600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs",
                                           nullptr);
    if (!transform) {
        std::cerr << "Erreur de création de la transformation." << std::endl;
    }

    PJ_COORD coord_in = proj_coord(lon, lat, alt, 0); // Longitude, Latitude
    PJ_COORD coord_out = proj_trans(transform, PJ_FWD, coord_in);

    _x = coord_out.xy.x;
    _y = coord_out.xy.y;
    _z = alt;
    
    // Nettoyage
    proj_destroy(transform);
    proj_destroy(Proj::pj_wgs84);
    proj_destroy(Proj::pj_lambert93);
    proj_context_destroy(Proj::ctx);

}

std::ostream& operator<<(std::ostream& stream, const Pos& p) {
    stream << p._x << " " << p._y << " " << p._z << std::endl; 
    return stream;
}

std::istream& operator>>(std::istream& stream, Pos& p) {
    std::string lat, lon, alt;

    std::getline(stream, lat, ' ');
    std::getline(stream, lon, ' '); 
    std::getline(stream, alt); 
    cout << "lat = " << lat << "\n lon = " << lon << "\n alt = " << alt << endl;    

    p._lat = std::stod(lat);
    p._lon = std::stod(lon);
    p._alt = std::stod(alt);

    p.transform_glob_loc(p._lat, p._lon, p._alt);

    return stream;
}