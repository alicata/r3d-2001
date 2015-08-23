// file name: math.cpp
//
// author:			Aaron Licata
// creation date:	14/02/01
// last modified:	17/02/01
// version number:	2
//
// description: math function module
//
// //////////////////////////////////////////////////////////

#include "config.h"
#include "math.h"		// DotProduct3
#include <stdlib.h>		// assert


// ////////////////////////////////////////////////////////////
// function: DotProduct() and CrossProduct()
//
// creation date:	29/12/00
// last modified:	29/12/00
// purpose: dot and cross products
//
// arguments: vectors
//
// return value: none
// ////////////////////////////////////////////////////////////

#if (ENABLE_EXACT_ARITHMETIC == 1)
	// use J.Shewchuck exact arithmetics rountine 
	double DotProduct3(Vector3 *v1, Vector3 *v2)
	{
		// TODO
		assert(0);
	}

    void CrossProduct3(Vector3& v1, Vector3& v2, Vector3& result)
	{
		assert(0);
	}

#else
// ///////////////////////////////////////////////////////////
// function: DotProduct3()
//
// creation date:	12/02/01
// last modified:	17/02/01
// purpose: scalar product between two vectors in 3-d space
//
// arguments: first and second vectors 
// ///////////////////////////////////////////////////////////

double DotProduct3(Vector3 *v1, Vector3 *v2) 
{
	return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z; 
}



// ///////////////////////////////////////////////////////////
// function: CrossProduct3()
//
// creation date:	17/02/01
// last modified:	17/02/01
// purpose: vector product between two vectors in 3-d space
//
// arguments: first, second vectors and uknown normal vector 
// ///////////////////////////////////////////////////////////

void CrossProduct3(Vector3& v1, Vector3& v2, Vector3& result)
{
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
}

#endif // end of non-exact version


