#include <stdlib.h>
#include <glut.h>// GLUT
#include "Body.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


	Body::Body(Vector location, int verticesNumber)
	{
		massR = 1;
		position = location;
		velocity = Vector(0,0,0);
		appliedForce = torque = Vector(0,0,0); // nobody starts with gravity force		
		
		angularVelocity = Vector(((int)rand()%2 == 0 ? (float)rand() / RAND_MAX : -(float)rand() / RAND_MAX )/4,
								 ((int)rand()%2 == 0 ? (float)rand() / RAND_MAX : -(float)rand() / RAND_MAX )/4,
								 ((int)rand()%2 == 0 ? (float)rand() / RAND_MAX : -(float)rand() / RAND_MAX )/4 );

		angularAcceleration = Vector(0,0,0);
		 
		L = P = Vector(0,0,0); // this was for testing: indeed I don't need momenta if I use angularAcceleration and such

		//rotation = matrixn3(-0.63,0.71,-0.31,-0.55,-0.12,0.82,0.54,0.69,0.47);
		rotation = matrixn3(1,0,0,0,1,0,0,0,1);
		
		float u = 12*massR;
		worldInertialTensor = matrixn3( 2/u, 0, 0, 0, 2/u, 0, 0, 0, 2/u ).Inverse();
		inertialTensor = matrixn3(worldInertialTensor);

		vertices.resize(verticesNumber);
		worldVertices.resize(verticesNumber);

		for(int i=0;i<vertices.size();i++) {
			vertices.at(i) = Vector(0,0,0);
			worldVertices.at(i) = Vector(0,0,0);
		}
		for(int i=0;i<indices.size();i++)
			worldNormals.at(i) = Vector(0,0,0);
		

		vertices.at(0) = worldVertices.at(0) = Vector(-1.0,-1.0,-1.0);
		vertices.at(1) = worldVertices.at(1) = Vector(-1.0,-1.0, 1.0);
		vertices.at(2) = worldVertices.at(2) = Vector( 1.0,-1.0, 1.0);
		vertices.at(3) = worldVertices.at(3) = Vector( 1.0,-1.0,-1.0);
		vertices.at(4) = worldVertices.at(4) = Vector(-1.0, 1.0,-1.0);
		vertices.at(5) = worldVertices.at(5) = Vector(-1.0, 1.0, 1.0);
		vertices.at(6) = worldVertices.at(6) = Vector( 1.0, 1.0, 1.0);
		vertices.at(7) = worldVertices.at(7) = Vector( 1.0, 1.0,-1.0);

		for(int i=0 ; i< vertices.size(); i++)
			worldVertices.at(i) = rotation * vertices.at(i) + position;

		indices.push_back( Vector(0,2,1)  );    
        //normals.push_back( Vector(0,-1,0) );

		indices.push_back( Vector(0,3,2)  );
		//normals.push_back( Vector(0,-1,0) );

		indices.push_back( Vector(0,1,5)  );
		//normals.push_back( Vector(-1,0,0) );

		indices.push_back( Vector(0,5,4)  );
		//normals.push_back( Vector(-1,0,0) );
		
		indices.push_back( Vector(1,2,6)  );
		//normals.push_back( Vector(0,0,1) );
		
		indices.push_back( Vector(1,6,5) );
		//normals.push_back( Vector(0,0,1) );
		
		indices.push_back( Vector(2,3,7) );
		//normals.push_back( Vector(1,0,0) );
		
		indices.push_back( Vector(2,7,6) );
		//normals.push_back( Vector(1,0,0) );
		
		indices.push_back( Vector(3,0,4) );
		//normals.push_back( Vector(0,0,-1) );
	
		indices.push_back( Vector(3,4,7) );
		//normals.push_back( Vector(0,0,-1) );

		indices.push_back( Vector(5,6,7) );
		//normals.push_back( Vector(0,1,0) );

		indices.push_back( Vector(5,7,4) );    
		//normals.push_back( Vector(0,1,0) );

		normals.push_back( findNormal( indices.at(0) ) );
		normals.push_back( findNormal( indices.at(1) ) );
		normals.push_back( findNormal( indices.at(2) ) );
		normals.push_back( findNormal( indices.at(3) ) );
		normals.push_back( findNormal( indices.at(4) ) );
		normals.push_back( findNormal( indices.at(5) ) );
		normals.push_back( findNormal( indices.at(6) ) );
		normals.push_back( findNormal( indices.at(7) ) );
		normals.push_back( findNormal( indices.at(8) ) );
		normals.push_back( findNormal( indices.at(9) ) );
		normals.push_back( findNormal( indices.at(10)) );
		normals.push_back( findNormal( indices.at(11)) );

		worldNormals.resize(normals.size());

		box = AABB(location, worldVertices);
		isColliding = false;
		drawAABB = true;
	}

	Vector Body::findNormal(Vector index) //FIX
	{
		Vector p1 = worldVertices.at(index[0]);
		Vector p2 = worldVertices.at(index[1]);
		Vector p3 = worldVertices.at(index[2]);

		// normal = p2-p1 cross p3-p1
		Vector U = (p2-p1);
		Vector V = (p3-p1);
		Vector normal = U.crossProduct(V);
		normal.normalize();
		return normal;
	}

	void Body::test()
	{
		float u = 12*massR;
		float c=2/u;
		matrixn3 temp = rotation* matrixn3( c, 0, 0, 0, c, 0, 0, 0, c )  *rotation.Transpose();
		//std::cout << temp * worldInertialTensor << std::endl;
		std::cout << inertialTensor << " " << temp << " " << temp.Inverse()<< " " << temp*temp.Inverse() << std::endl;
		std::cout << 2/u << std::endl;
	}

	void Body::stop()
	{
		angularVelocity.zero();
		angularAcceleration.zero();
		//rotation = matrixn3(1,0,0,0,1,0,0,0,1);
		//rotation = matrixn3(0,rotation.c(1,2),rotation.c(1,3),rotation.c(2,1),0,rotation.c(2,3),rotation.c(3,1),rotation.c(3,2),0);
	}

	void Body::reset()
	{
		rotation = matrixn3(1,0,0,0,1,0,0,0,1);
	}

	void Body::draw(Vector color)
	{
		glPushMatrix(); //position in the world

			//global transformations
			//glTranslatef(position[0],position[1],position[2]); //the aim is NOT to use gl translations!

				/*if(color != NULL)*/ 
					glColor3f(color[0],color[1],color[2]);
					glBegin(GL_TRIANGLES);
						for (int i = 0; i < indices.size(); i ++) { //for each triangle represented by indices i set their vertices so opengl can draw them
							glNormal3f( worldNormals[i].x, worldNormals[i].y, worldNormals[i].z); //I first set the normal of each triangle

							//the vertex has a component x,y,z and it is represented by i-th indice(triangle)'s 1,2,3 component (not really useful to call them xyz in this case as they are not representation of axes)
							glVertex3f( worldVertices[indices[i].x].x , worldVertices[indices[i].x].y, worldVertices[indices[i].x].z);
							glVertex3f( worldVertices[indices[i].y].x , worldVertices[indices[i].y].y, worldVertices[indices[i].y].z);
							glVertex3f( worldVertices[indices[i].z].x , worldVertices[indices[i].z].y, worldVertices[indices[i].z].z);
						}    
					glEnd();

					if(drawAABB) box.draw((isColliding?Vector( 1.f, 0, 0 ):Vector( 0, 1.f, 0 )));

			//glLineWidth(2);

			//glColor3f(255,0,0); //RED: x
			//glBegin(GL_LINES);
			//glVertex3f(position[0],position[1],position[2]);
			//glVertex3f(position[0]+5,position[1],position[2]);
			//glEnd();

			//glColor3f(0,0,255); //BLUE: z
			//glBegin(GL_LINES);
			//glVertex3f(position[0],position[1],position[2]);
			//glVertex3f(position[0],position[1],position[2]+5);
			//glEnd();

			//glColor3f(0,255,0); //GREEN: y
			//glBegin(GL_LINES);
			//glVertex3f(position[0],position[1],position[2]);
			//glVertex3f(position[0],position[1]+5,position[2]);
			//glEnd();

			//glLineWidth(1);

		glPopMatrix(); //position in the world
	}


	void Body::setPosition(Vector location)
	{
		position = location;
	}


	Vector Body::getPosition()
	{
		return position;
	}

	void Body::cleanInertia()
	{
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++)
				if(worldInertialTensor.c(i,j) < 0.0001 && worldInertialTensor.c(i,j) > -0.0001)
					worldInertialTensor.c(i,j) = 0;
	}

	void Body::update(std::vector<Force> forces) 
	{
		
		forceAccumulate(forces);
		
		//update of linear position
		velocity += appliedForce * massR;
		velocity *= 0.9;
		if(velocity.length() < 0.0001 && velocity.length() > -0.0001) velocity.zero();
		position += velocity;//ok

		//update of angular position
		for(int i=0 ; i< vertices.size(); i++)
			worldVertices.at(i) = rotation * vertices.at(i) + position; 

		//update of inertial tensor (needed for update of angular velocity)
		worldInertialTensor = rotation * inertialTensor * rotation.Transpose();

		//the rotation makes it dirty
		cleanInertia();

		//update of rotation
		rotation += starv(angularVelocity)*rotation; 

		//orthogonalisation of rotation matrix
		orthogonalize();
		
		//update of torque (needed for update of angular velocity)
		//done on the forceAccumulate function. BUT what I have to update here is the POA of the force (transform it) --NECESSARY TO STORE A BODYSPACE INFORMATION OF THE POI (WHERE??)

		//update of the angular acceleration
		angularAcceleration = worldInertialTensor * torque ;
		
		//update of the angular velocity
		angularVelocity += angularAcceleration; 
		angularVelocity *= 0.987; //dampening
		if(angularVelocity.length() < 0.0001 && angularVelocity.length() > -0.0001) angularVelocity.zero();

		for (int i=0; i < indices.size(); i++)
			worldNormals.at(i) = findNormal(indices.at(i));

		if(drawAABB) box.findMinMax(worldVertices);

	}
	

	void Body::orthogonalize()
	{
		Vector x( rotation.colv(0) ) , y( rotation.colv(1) ) , z( rotation.colv(2) ) ;
		x.normalize();
		y=z.crossProduct(x);
		y.normalize();
		z=x.crossProduct(y);
		z.normalize();
		rotation.set(x,y,z);
	}

	void Body::forceAccumulate(std::vector<Force> forces)
	{
		appliedForce.zero() ;
		torque.zero() ;

		for(int k=0; k < forces.size(); k++)
			if(forces.at(k).positional)
				torque += (forces.at(k).point - position).crossProduct(forces.at(k).direction);
			else appliedForce += forces.at(k).direction;
	}


	Vector Body::getAABBMin()
	{
		return box.min;
	}

	Vector Body::getAABBMax()
	{
		return box.max;
	}


	void Body::setCollision(bool value)
	{
		isColliding = value;
	}

	
	//void Body::update(std::vector<Force> forces) 
	//{
	//	forceAccumulate(forces);
	//	
	//	//update of linear position
	//	P += appliedForce;
	//	velocity += P * massR;
	//	velocity *= 0.9;
	//	if(velocity.length() < 0.0001 && velocity.length() > -0.0001) velocity.zero();
	//	position += velocity;//ok

	//	//update of angular position
	//	for(int i=0 ; i< vertices.size(); i++)
	//		worldVertices.at(i) = rotation * vertices.at(i) + position; 

	//	//update of inertial tensor (needed for update of angular velocity)
	//	worldInertialTensor = rotation * inertialTensor * rotation.Transpose();

	//	//the rotation makes it dirty
	//	cleanInertia();

	//	//update of rotation
	//	rotation += starv(angularVelocity)*rotation; 

	//	//orthogonalize the rotation
	//	orthogonalize();
	//	
	//	//update of torque (needed for update of angular velocity)
	//	//done on the forceAccumulate function. BUT what I have to update here is the POA of the force (transform it) --NECESSARY TO STORE A BODYSPACE INFORMATION OF THE POI (WHERE??)

	//	//update of the angular acceleration
	//	L += torque;

	//	//update of the angular velocity
	//	angularVelocity += worldInertialTensor * L; 
	//	angularVelocity *= 0.979;

	//	for (int i=0; i < indices.size(); i++)
	//		worldNormals.at(i) = findNormal(indices.at(i));

	//	if(drawAABB) box.findMinMax(worldVertices);

	//}
