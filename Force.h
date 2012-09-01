#ifndef PI
#define PI 3.14159265
#endif

#ifndef NULL
#define NULL 0
#endif

#include "Vector.h" //NOTE: no forward declaration, but not even guards... (suggestion from mathieu after forward declaration by chris)
#include "matrix.h"

#include <vector>

class Force
{
private:
	

public:

	Vector direction;

	Vector point;

	bool positional;


	Force(Vector dir, Vector POA) ;
	//Force(Vector dir = Vector(0,0,0) , Vector POA(0,0,0), float magn) ;// how to???
	Force(Vector dir);
	//~Force() ;

	void draw();

	float magnitude();
	Vector POA();

};