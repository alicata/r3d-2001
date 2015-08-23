// /////////////////////////////////////////////////
// math.h
//
// author:			Aaron Licata
// creation date:	20/08/00
// last modified:	17/09/00
//
// Header file for all general math data structures
// and procedures

#ifndef MATH_MODULE_H
#define MATH_MODULE_H

#include <math.h>

// constants
#define MACHINE_TOLLERANCE 0.0
#define INFINITY 999999.0

// macros

// find the square distance of two points
#define SQUARE_DISTANCE3(point, centre) (point.x-centre.x)*(point.x-centre.x)+(point.y-centre.y)*(point.y-centre.y)+(point.z-centre.z)*(point.z-centre.z)
// find the square distance of two pointers to point objects
#define SQUARE_DISTANCE3P(point, centre) (point->x-centre->x)*(point->x-centre->x)+(point->y-centre->y)*(point->y-centre->y)+(point->z-centre->z)*(point->z-centre->z)

// ///////////////////////////////////////////////////////////
// class Vector3
//
// creation date:	20/08/00
// last modified:	17/02/01
//
// purpose: class reprensenting a vector in 3-d space
// ///////////////////////////////////////////////////////////
class Vector3
{
public:
	Vector3() { x=y=z=0.0;}
	Vector3(double vx, double vy, double vz) { x=vx; y=vy; z=vz; }
	void Set(double vx, double vy, double vz) { x=vx; y=vy; z=vz; }
	void Set(Vector3& v) { x=v.x; y=v.y; z=v.z; }
	double Magnitude() { return sqrt(x*x + y*y + z*z); }
	void Normalize() { double m = Magnitude(); x /= m; y /= m; z /= m; }
public:
	double x, y, z;
};

// scalar product between two vectors in 3-d space
double DotProduct3(Vector3 *v1, Vector3 *v2);

// cross product between two vectors in 3-d space
void CrossProduct3(Vector3& v1, Vector3& v2, Vector3& result);

#endif
