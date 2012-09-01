#ifndef PI
#define PI 3.14159265
#endif

#ifndef NULL
#define NULL 0
#endif

#include "Vector.h"
#include <vector>


class AABB
{

private:

public:

	Vector min, max;
	Vector position;


	AABB();

	AABB(Vector location, std::vector<Vector> vertices);

	void findMinMax(std::vector<Vector> vertices);

	void draw(Vector color);

};
