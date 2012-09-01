#ifndef PI
#define PI 3.14159265
#endif

#ifndef NULL
#define NULL 0
#endif

#include "Vector.h" 
#include "matrix.h"

#include <vector>


class Plane
{
private:
	

public:

	Vector V1,V2,V3,V4;
	Vector normal;
	Vector origin;


	Plane(Vector v1,Vector v2, Vector v3, Vector v4) ;

	//~Plane() ;	

	void draw(Vector color);

	Vector findNormal(Vector v1,Vector v2, Vector v3);

	Vector getNormal();

	bool onPlane(Vector point);

	float getDistance(Vector point);

	Vector getClosestPoint(Vector point);
	
};