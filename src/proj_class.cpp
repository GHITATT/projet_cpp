#include <proj.h>
#include <iostream>

class Proj {
public:
    static PJ *pj_wgs84;
    static PJ *pj_lambert93;
    static PJ_CONTEXT *ctx;

    Proj() = delete; // Empêche l'instanciation de cette classe

    ~Proj() {
        if (pj_wgs84) proj_destroy(pj_wgs84);
        if (pj_lambert93) proj_destroy(pj_lambert93);
        if (ctx) proj_context_destroy(ctx);
    }

    static void initialize() {
        ctx = proj_context_create();
        if (!ctx) throw std::runtime_error("Erreur de création du contexte PROJ.");

        pj_wgs84 = proj_create_crs_to_crs(ctx, "EPSG:4326", "EPSG:4326", nullptr);
        pj_lambert93 = proj_create_crs_to_crs(
            ctx, "EPSG:4326",
            "+proj=lcc +lat_1=49 +lat_2=44 +lat_0=46.5 +lon_0=3 +x_0=700000 +y_0=6600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs",
            nullptr
        );

        if (!pj_wgs84 || !pj_lambert93)
            throw std::runtime_error("Erreur d'initialisation des projections.");    
    }

    static void cleanup() {
        if (pj_wgs84) proj_destroy(pj_wgs84);
        if (pj_lambert93) proj_destroy(pj_lambert93);
        if (ctx) proj_context_destroy(ctx);
        pj_wgs84 = nullptr;
        pj_lambert93 = nullptr;
        ctx = nullptr;
    }
};