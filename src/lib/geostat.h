#ifndef GEOSTAT_H
#define GEOSTAT_H

#include "geom.h"

#define TETRALIST_STATS		1
#define TETRA_STATS			2

void ShowTetraListStatistics(TetraList& tetraList, int mode);
void ShowTetraStatistics(Tetrahedron* tetra);

#endif

