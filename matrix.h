#ifndef ___matrixn3_
#define ___matrixn3_

#include <iostream>
#include "Vector.h"

using namespace std;

class matrixn3
{
private:
	double m[9];


public:

	inline matrixn3(); //initialized to the identity

	inline matrixn3(const matrixn3&); //copy constructor

	inline matrixn3(const double*); //traverse row first
	inline matrixn3(const double, const double, const double, 
						  const double, const double, const double,
						  const double, const double, const double); //traverse row first
	inline matrixn3(const Vector, const Vector, const Vector); //Vectors are columns

	inline void set(const Vector, const Vector, const Vector); //Vectors are columns

	inline void set(const double *m); //traverse row first
	inline void set(const double, const double, const double, 
						  const double, const double, const double,
						  const double, const double, const double); //traverse row first

	inline void reset(); //set to identity
	inline void loadIdentity(); //set to identity 

	inline double& c(const int i, const int j) { return m[(i-1)*3+(j-1)]; } //cell access method LHS (row, column)
	inline double c(const int i, const int j) const {return m[(i-1)*3+(j-1)]; }; //cell access method RHS (row, column)
	
	inline double c1(const int r) const { return m[r]; }; //Low level cell access method RHS. Param is array index
	inline double& c1(const int r) { return m[r]; }; //Low Level cell access method LHS. Param is array index

	inline friend matrixn3 operator* (const matrixn3&, const matrixn3&);
	inline friend Vector operator* (const matrixn3&, const Vector&);

	inline friend matrixn3 operator+ (const matrixn3&, const matrixn3&);

	inline friend matrixn3 operator* (const double, const matrixn3&);
	inline friend matrixn3 operator* (const matrixn3&, const double);

	inline matrixn3& operator*= (const matrixn3&);
	inline matrixn3& operator*= (const double);

	inline matrixn3& operator+= (const matrixn3&);
	
	inline friend matrixn3 operator/ (const matrixn3&, const double);

	inline matrixn3& operator= (const matrixn3&);

	inline double operator() (const int i, const int j)  const { return m[(i-1)*3+(j-1)]; } ; //cell access operator RHS (row, column)
	inline double& operator() (const int i, const int j) { return m[(i-1)*3+(j-1)]; }; //cell access operator LHS (row, column)

	friend ostream& operator<< (ostream&, const matrixn3&);

	inline double det() const; //return determinant
	inline matrixn3 Inverse() const; //return inverse
	inline matrixn3 Transpose() const; //return transpose

	inline void roundoff(const double); //Utility. Approximate values close to zero as being zero

	inline Vector rowv(int i) const; //Utility return ith row vector
	inline Vector colv(int i) const; //Utility return ith column vector
	
};

inline matrixn3::matrixn3()
{
	/*
	for (int i=0; i<9; i++)
		m[i] = 0;
	*/
	
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	
	m[3] = 0;
	m[4] = 1;
	m[5] = 0;

	m[6] = 0;
	m[7] = 0;
	m[8] = 1;
	
}

inline matrixn3::matrixn3(const matrixn3& mat) //copy constructor
{
	m[0] = mat.m[0];
	m[1] = mat.m[1];
	m[2] = mat.m[2];
	
	m[3] = mat.m[3];
	m[4] = mat.m[4];
	m[5] = mat.m[5];

	m[6] = mat.m[6];
	m[7] = mat.m[7];
	m[8] = mat.m[8];
	
}


inline matrixn3::matrixn3( const double *mm)
{
	/*
	for (int i=0; i<9; i++)
		m[i] = mm[i];
	*/

	m[0] = mm[0];
	m[1] = mm[1];
	m[2] = mm[2];
	
	m[3] = mm[3];
	m[4] = mm[4];
	m[5] = mm[5];

	m[6] = mm[6];
	m[7] = mm[7];
	m[8] = mm[8];
	
}

inline matrixn3::matrixn3(const double a11, const double a12, const double a13, 
						  const double a21, const double a22, const double a23,
						  const double a31, const double a32, const double a33)
{						  
	m[0] = a11;
	m[1] = a12;
	m[2] = a13;
	
	m[3] = a21;
	m[4] = a22;
	m[5] = a23;

	m[6] = a31;
	m[7] = a32;
	m[8] = a33;
	
}

inline matrixn3::matrixn3(const Vector v1, const Vector v2, const Vector v3)
{
	m[0] = v1.x;
	m[1] = v2.x;
	m[2] = v3.x;

	m[3] = v1.y;
	m[4] = v2.y;
	m[5] = v3.y;

	m[6] = v1.z;
	m[7] = v2.z;
	m[8] = v3.z;
}


inline void matrixn3::set(const double a11, const double a12, const double a13, 
						  const double a21, const double a22, const double a23,
						  const double a31, const double a32, const double a33)
{						  
	m[0] = a11;
	m[1] = a12;
	m[2] = a13;
	
	m[3] = a21;
	m[4] = a22;
	m[5] = a23;

	m[6] = a31;
	m[7] = a32;
	m[8] = a33;
	
}

inline void matrixn3::set(const Vector v1, const Vector v2, const Vector v3)
{
	m[0] = v1.x;
	m[1] = v2.x;
	m[2] = v3.x;

	m[3] = v1.y;
	m[4] = v2.y;
	m[5] = v3.y;

	m[6] = v1.z;
	m[7] = v2.z;
	m[8] = v3.z;
}

inline void matrixn3::set( const double *mm)
{
/*
	for (int i=0; i<9; i++)
	{
		m[i] = mm[i];
	}
*/
	m[0] = mm[0];
	m[1] = mm[1];
	m[2] = mm[2];
	
	m[3] = mm[3];
	m[4] = mm[4];
	m[5] = mm[5];

	m[6] = mm[6];
	m[7] = mm[7];
	m[8] = mm[8];
	
}

inline void matrixn3::reset()
{

	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	
	m[3] = 0;
	m[4] = 1;
	m[5] = 0;

	m[6] = 0;
	m[7] = 0;
	m[8] = 1;

}

inline void matrixn3::loadIdentity()
{

	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	
	m[3] = 0;
	m[4] = 1;
	m[5] = 0;

	m[6] = 0;
	m[7] = 0;
	m[8] = 1;


}

inline matrixn3 operator+ (const matrixn3& m1, const matrixn3& m2)
{
	matrixn3 m3(0,0,0,0,0,0,0,0,0);

	for (int i=1; i<=3; i++)
	{
		for (int j=1; j<=3; j++)
		{
			//for(int k=1; k<=3; k++)
			m3.c(i,j) += m1.c(i,j) + m2.c(i,j);
		}
	}

	return m3;

};

inline matrixn3 operator* (const matrixn3& m1, const matrixn3& m2)
{
	matrixn3 m3;
	for (int i=1; i<=3; i++)
	{
		for (int j=1; j<=3; j++)
		{
			m3.c(i,j) = 0.00;
			for(int k=1; k<=3; k++)
			m3.c(i,j) += m1.c(i,k)*m2.c(k,j);
		}
	}

	return m3;
}

inline matrixn3 operator* (const double d, const matrixn3& m1)
{
	matrixn3 m3;

	for (int i=1; i<=3; i++)
	{
		for (int j=1; j<=3; j++)
		{
			m3.c(i,j) = d*m1.c(i,j);
		}
	}

	return m3;
}

inline matrixn3 operator* (const matrixn3& m1, const double d)
{
	matrixn3 m3;
	m3 = d * m1;
	return m3;
}

inline Vector operator* (const matrixn3& m, const Vector& v)
{
	Vector res;

	res.x = m.c(1,1) * v.x + m.c(1,2) * v.y + m.c(1,3) * v.z;
	res.y = m.c(2,1) * v.x + m.c(2,2) * v.y + m.c(2,3) * v.z;
	res.z = m.c(3,1) * v.x + m.c(3,2) * v.y + m.c(3,3) * v.z;

	return res;
}

inline matrixn3& matrixn3::operator *= (const matrixn3& m)
{//to avoid complications of multiplying by self
	matrixn3 mm;

	mm = (*this) * m;
	(*this) = mm;

	return *this;
}

inline matrixn3& matrixn3::operator += (const matrixn3& m)
{//to avoid complications of summing by self
	matrixn3 mm;
	
	mm = (*this) + m;
	(*this) = mm;

	return *this;
}

inline matrixn3& matrixn3::operator *= (const double d)
{
	(*this) = (*this) * d;
	return *this;
}



inline matrixn3& matrixn3::operator= (const matrixn3& mm)
{
	if ( this == &mm ) return ( *this ) ;

	for (int i=0; i<9; i++)
	{
		m[i] = mm.m[i];
	}

	return (*this);
}

inline matrixn3 operator/ (const matrixn3& m1, const double d)
{
	matrixn3 m3;

	for (int i=1; i<=3; i++)
	{
		for (int j=1; j<=3; j++)
		{
			m3.c(i,j) = m1.c(i,j)/d;
		}
	}

	return m3;
}

inline double d2(double a, double b, double c, double d)
{
	return a*d - b*c;

}

inline double matrixn3::det() const
{
	double d;
	
/*
	d = c(1,1) *( c(2,2)*c(3,3) - c(2,3)*c(3,2)) 
		- c(1,2) *(c(2,1)*c(3,3) - c(2,3)*c(3,1))
		+ c(1,3) *( c(2,1)*c(3,2) - c(2,2)*c(3,1)) ;

*//*
		d = c(1,1) * d2( c(2,2),c(2,3),c(3,2),c(3,3) ) 
			- c(1,2) * d2( c(2,1),c(2,3), c(3,1),c(3,3) )
		+ c(1,3) *d2( c(2,1),c(2,2),c(3,1),c(3,2)) ;


*//*
	d = m[0] *( m[4]*m[8] - m[5]*m[7]) 
		- m[1] *( m[3]*m[8] - m[5]*m[6]) 
		+ m[6] *( m[3]*m[7] - m[4]*m[6]) ;
*/

	
	//d  =  a11(a33a22-a32a23)-a21(a33a12-a32a13)+a31(a23a12-a22a13)
	d  =  c(1,1)*(c(3,3)*c(2,2)-c(3,2)*c(2,3))
		-c(2,1)*(c(3,3)*c(1,2)-c(3,2)*c(1,3))
		+c(3,1)*(c(2,3)*c(1,2)-c(2,2)*c(1,3));                                                          
	

	return d;
}



inline matrixn3 matrixn3::Inverse() const
{
	double d = det();
	matrixn3 ib,Inv;
/*
	ib.c(1,1) = d2(c(2,2), c(2,3), c(3,2),c(3,3));
	ib.c(1,2) = d2(c(1,3), c(1,2), c(3,3),c(3,2));
	ib.c(1,3) = d2(c(1,2), c(1,3), c(2,2),c(2,3));

	ib.c(2,1) = d2(c(2,3), c(2,1), c(3,3),c(3,1));
	ib.c(2,2) = d2(c(1,1), c(1,3), c(3,1),c(3,3));
	ib.c(2,3) = d2(c(1,3), c(1,1), c(2,3),c(2,1));

	ib.c(3,1) = d2(c(2,1), c(2,1), c(3,1),c(3,2));
	ib.c(3,2) = d2(c(1,2), c(1,1), c(3,2),c(3,1));
	ib.c(3,3) = d2(c(1,1), c(1,2), c(2,1),c(2,2));
*/
	ib.c(1,1) = c(3,3)*c(2,2)-c(3,2)*c(2,3);
	ib.c(1,2) = -(c(3,3)*c(1,2)-c(3,2)*c(1,3));   
	ib.c(1,3) = c(2,3)*c(1,2)-c(2,2)*c(1,3);                                                          

	ib.c(2,1) = -(c(3,3)*c(2,1)-c(3,1)*c(2,3));   
	ib.c(2,2) = c(3,3)*c(1,1)-c(3,1)*c(1,3);  
	ib.c(2,3) = -(c(2,3)*c(1,1)-c(2,1)*c(1,3));

	ib.c(3,1) = c(3,2)*c(2,1)-c(3,1)*c(2,2);  
	ib.c(3,2) = -(c(3,2)*c(1,1)-c(3,1)*c(1,2));   
	ib.c(3,3) = c(2,2)*c(1,1)-c(2,1)*c(1,2);                                                   

	Inv = ib / d;

	return Inv;

}

inline matrixn3 matrixn3::Transpose() const
{
	matrixn3 transp;

	for(int i=1; i<=3; i++)
		for(int j=1; j<=3; j++)
			transp.c(i,j) = c(j,i);
	
	return transp;
}


inline void matrixn3::roundoff(const double prec=0.000000001)
{
	for (int i=0; i<9; i++)
	{
		if (m[i]<prec && m[i]>(-prec))
			m[i] = 0;
	}
}


inline matrixn3 starv(const Vector v)
{
	double dm[] = {		0, -v.z, v.y,
							v.z, 0, -v.x,
							-v.y, v.x, 0};

	matrixn3 mm (dm);

	return mm;

}


inline Vector matrixn3::colv(int i) const
//return a vector representing column i
{
	Vector v;

	v.x = m[i];
	v.y = m[3+i];
	v.z = m[6+i];

	return v;
};

inline Vector matrixn3::rowv(int i) const
//return a vector representing row i
{
	Vector v;

	v.x = m[i*3];
	v.y = m[i*3+1];
	v.z = m[i*3+2];

	return v;
};


inline ostream& operator<< (ostream& os, const matrixn3& m1) 
{
	os << "[" << m1.m[0] << " " << m1.m[1] << " " << m1.m[2] << "]" << endl;
	os << "[" << m1.m[3] << " " << m1.m[4] << " " << m1.m[5] << "]" << endl;
	os << "[" << m1.m[6] <<" " <<  m1.m[7] <<" " <<  m1.m[8] << "]" << endl;

	return os;
};

#endif