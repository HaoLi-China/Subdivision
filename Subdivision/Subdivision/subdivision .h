#ifndef _SUBDIVISION_H
#define _SUBDIVISION_H

#include "half_edge.h"
#include <iostream>
#include<math.h>

#define PI 3.1415926

using namespace std;

//the Loop subdivision
void loopSubdivision(HalfEdgeMesh &halfEdgeMesh,HalfEdgeMesh &new_halfEdgeMesh);

//the modified Butterfly subdivision
void mButterflySubdivision(HalfEdgeMesh &halfEdgeMesh,HalfEdgeMesh &new_halfEdgeMesh);

#endif;