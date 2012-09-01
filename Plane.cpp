#include <stdlib.h>
#include <glut.h>// GLUT
#include "Plane.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


	Plane::Plane(Vector v1, Vector v2, Vector v3, Vector v4)//IMPROVE: pass normal and origin, deduce 4 vertices with the parametric form
	{
		V1 = v1;
		V2 = v2;
		V3 = v3;
		V4 = v4;
		normal = findNormal(V1, V2, V3);
		origin.x = (V2.x+V4.x)/2;
		origin.y = (V2.y+V4.y)/2;
		origin.z = (V2.z+V4.z)/2;
	}

	Vector Plane::findNormal(Vector v1, Vector v2, Vector v3) //FIX
	{
		Vector p1 = V1;
		Vector p2 = V2;
		Vector p3 = V3;

		// normal = p2-p1 cross p3-p1
		Vector U = (p2-p1);
		Vector V = (p3-p1);
		Vector normal = U.crossProduct(V);
		normal.normalize();
		return normal;
	}

	Vector Plane::getNormal() 
	{
		return normal;
	}

	void Plane::draw(Vector color)
	{
		glPushMatrix(); //position in the world

			//global transformations
			//glTranslatef(position[0],position[1],position[2]); //the aim is NOT to use gl translations!
		
			glColor3f(color[0],color[1],color[2]);

			glBegin(GL_QUADS);
			glNormal3f( normal.x, normal.y, normal.z);
				glVertex3f( V1[0], V1[1], V1[2] );//V1
				glVertex3f( V2[0], V2[1], V2[2] );//V2
				glVertex3f( V3[0], V3[1], V3[2] );//V3
				glVertex3f( V4[0], V4[1], V4[2] );//V4
			glEnd();

		glPopMatrix(); //position in the world
	}

	bool Plane::onPlane(Vector point) //IMPROVE
	{
		//add control whether the point is on the drawn plane (i.e. (point-origin).x must be within (v?-v?).x max)
		float dp = normal.dotProduct(point-origin);
		return dp <= 0.00001 && dp >= -0.00001; //finite memory: approximation error
	}

	float Plane::getDistance(Vector point)
	{
		return (point-origin).dotProduct(normal);
	}

	Vector Plane::getClosestPoint(Vector point)
	{
		return point - normal*getDistance(point);
	}

	
