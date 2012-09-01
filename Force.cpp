#include <stdlib.h>
#include <glut.h>// GLUT
#include "Force.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


	Force::Force(Vector dir, Vector POA)
	{
		direction = dir;
		point = POA;
		positional = true;
	}

	Force::Force(Vector dir)
	{
		direction = dir;
		positional = false;
	}

	float Force::magnitude()
	{
		return direction.length();
	}

	Vector Force::POA()
	{
		return point;
	}

	void Force::draw()
	{
		glDisable(GL_LIGHTING);
			glLineWidth(6);
			positional?glColor3f(0.3f,0.15f,0.15f):glColor3f(0.2,0.5,0.2);
			glBegin(GL_LINES);
				glVertex3f(point.x,point.y,point.z);
				direction.length()>0.2?glVertex3f(point.x-direction.x, point.y-direction.y, point.z-direction.z):glVertex3f(point.x-(100*direction.x), point.y-(100*direction.y), point.z-(100*direction.z));
			glEnd();
			glLineWidth(1);
		glEnable(GL_LIGHTING);
	}
