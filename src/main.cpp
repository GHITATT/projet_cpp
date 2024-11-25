#include <cassert>
#include <cmath>   // for HUGE_VAL
#include <iomanip> // for std::setprecision()

#include <iostream>

#include "proj/coordinateoperation.hpp"
#include "proj/crs.hpp"
#include "proj/io.hpp"
#include "proj/util.hpp" // for nn_dynamic_pointer_cast

using namespace NS_PROJ::crs;
using namespace NS_PROJ::io;
using namespace NS_PROJ::operation;
using namespace NS_PROJ::util;



int main() {
    auto dbContext = DatabaseContext::create();
    auto authFactory = AuthorityFactory::create(dbContext, std::string());
    auto coord_op_ctxt =
    CoordinateOperationContext::create(authFactory, nullptr, 0.0);
    auto authFactoryEPSG = AuthorityFactory::create(dbContext, "EPSG");
    auto sourceCRS = authFactoryEPSG->createCoordinateReferenceSystem("4326");
    auto targetCRS =
    NN_CHECK_THROW(nn_dynamic_pointer_cast<CRS>(createFromUserInput(
        "+proj=utm +zone=31 +datum=WGS84 +type=crs", dbContext)));
    auto list = CoordinateOperationFactory::create()->createOperations(
    sourceCRS, targetCRS, coord_op_ctxt);
    assert(!list.empty());
    PJ_CONTEXT *ctx = proj_context_create();
    auto transformer = list[0]->coordinateTransformer(ctx);
    PJ_COORD c = {{
        49.0,    // latitude in degree
        2.0,     // longitude in degree
        0.0,     // z ordinate. unused
        HUGE_VAL // time ordinate. unused
    }};
    c = transformer->transform(c);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Easting: " << c.v[0] << std::endl;  // should be 426857.988
    std::cout << "Northing: " << c.v[1] << std::endl; // should be 5427937.523
    proj_context_destroy(ctx);
    return 0;
}

