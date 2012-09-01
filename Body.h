#ifndef PI
#define PI 3.14159265
#endif

#ifndef NULL
#define NULL 0
#endif

//#ifndef spline
//#define spline 
//#include "Spline.h"
//#endif

#include "Vector.h" //NOTE: no forward declaration, but not even guards... (suggestion from mathieu after forward declaration by chris)
#include "matrix.h"
//class Vector;

#include <vector>
#include "AABB.h"
#include "Force.h"


class Body
{
private:
	

public:

	float massR; //RECIPROCAL

	/*Phase vectors*/
	Vector position;
	Vector velocity;

	matrixn3 rotation;
	Vector angularVelocity;
	Vector angularAcceleration;

	matrixn3 inertialTensor; //RECIPROCAL, remains fixed
	matrixn3 worldInertialTensor; //RECIPROCAL
	Vector torque;
	

	Vector L,P;

	Vector appliedForce; //vector containing the cumulative force applied on the particle

	std::vector<Vector> worldVertices; //the ones who change
	std::vector<Vector> vertices; //the ones who remain fixed
	
	std::vector<Vector> indices;

	std::vector<Vector> normals;
	std::vector<Vector> worldNormals; //unused

	AABB box;

	bool isColliding;
	bool drawAABB;


	Body(Vector pos, int verticesNumber=8) ;

	//~Body() ;	

	float getSize();

	void stop();
	void reset();

	void setPosition(Vector location); //useless

	Vector getPosition(); //useless

	void draw(Vector color);

	void forceAccumulate(std::vector<Force> forces); 

	//void coolCollDet(Vector planeNormal) ;

	void update(std::vector<Force> forces);

	void handleTorque();

	void orthogonalize();

	Vector findNormal(Vector index);

	Vector getAABBMin();

	Vector getAABBMax();

	void setCollision(bool value);





	void test();

	void cleanInertia();

};