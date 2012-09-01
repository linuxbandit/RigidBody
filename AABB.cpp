#include <stdlib.h>
#include <glut.h>// GLUT
#include "AABB.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


	AABB::AABB()
	{
	}


	AABB::AABB(Vector location, std::vector<Vector> vertices)
	{
		position = location;
		findMinMax(vertices);
	}

	void AABB::findMinMax(std::vector<Vector> vertices)
	{
		
		Vector localMin = Vector( INT_MAX - 0.01, INT_MAX - 0.01, INT_MAX - 0.01) ;
		Vector localMax = Vector( INT_MIN + 0.01, INT_MIN + 0.01, INT_MIN + 0.01) ;
		

		for ( int i = 0; i < 3; i++)
			for(int j = 0; j < vertices.size(); j++){
				if(localMin[i] > vertices.at(j)[i])
					localMin[i] = vertices.at(j)[i];
				if(localMax[i] < vertices.at(j)[i])
					localMax[i] = vertices.at(j)[i];
			}
			
		min = Vector ( localMin ) ;
		max = Vector ( localMax ) ;

	}

	void AABB::draw(Vector color) 
	{
		
		glDisable(GL_LIGHTING);

		glLineWidth(2);

		glColor3f(color[0],color[1],color[2]);
			glBegin(GL_LINE_LOOP);
			glNormal3f( 0, -1, 0);
			glVertex3f(min[0],min[1],min[2]); //V0
			glVertex3f(max[0],min[1],min[2]); //V3
			glVertex3f(max[0],min[1],max[2]); //V2
			glVertex3f(min[0],min[1],max[2]); //V1
			glVertex3f(min[0],max[1],max[2]); //V5
			glVertex3f(max[0],max[1],max[2]); //V6
			glVertex3f(max[0],max[1],min[2]); //V7
			glVertex3f(min[0],max[1],min[2]); //V4
			glEnd();

			glBegin(GL_LINES);
			glNormal3f( 0, -1, 0);
			glVertex3f(min[0],max[1],min[2]); //V4
			glVertex3f(min[0],max[1],max[2]); //V5

			glVertex3f(min[0],min[1],min[2]); //V0
			glVertex3f(min[0],min[1],max[2]); //V1

			glVertex3f(max[0],max[1],max[2]); //V6
			glVertex3f(max[0],min[1],max[2]); //V2

			glVertex3f(max[0],max[1],min[2]); //V7
			glVertex3f(max[0],min[1],min[2]); //V3
			glEnd();

			

			glLineWidth(1);

			glEnable(GL_LIGHTING);
		
			//debug: see min and max
		/*std::cout << min << " " << max << std::endl;
		std::cout << min.distance(max) << std::endl << std::endl;*/

		/*
		glPushMatrix();
			glTranslatef(min.x,min.y,min.z);
			glutSolidSphere(0.01,20,20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(max.x,max.y,max.z);
			glutSolidSphere(0.01,20,20);
		glPopMatrix();

		glBegin(GL_LINES); //diagonal min-max (testing)
			glVertex3f(min[0],min[1],min[2]); 
			glVertex3f(max[0],max[1],max[2]); 
		glEnd();
		*/
		
	}
