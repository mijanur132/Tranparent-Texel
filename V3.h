
#pragma once

#include <ostream>
#include<istream>
#include<iostream>

using namespace std;

class V3 {
public:
	V3() {};
	V3(float x, float y, float z) { xyz[0] = x; xyz[1] = y; xyz[2] = z; };  //a
	float xyz[3];                                                          //b-read
	float& operator[](int i);                                             //b-wr
	V3 operator+(V3 v1);							//c
	V3 operator-(V3 v1);							//d

	V3 operator^(V3 v2);							//f
	float operator*(V3 v1);							//e		

	V3 operator*(float scf);						//g
	V3 operator/(float scf);						//h

	
	V3 Normalized();									//i
	float Length();										//j

	//V3 UnitVector();
//	V3 RotateThisPointAboutArbitraryAxis(V3 O, V3 a, float angled);     //i
	V3 RotateThisVectorAboutDirection(V3 a, float angled);				//k
	

	// cerr << v;
	friend ostream& operator<<(ostream& ostr, V3 v);					//m
	//friend istream& operator>>(istream& istr, V3 v);					//m

	void SetFromColor(unsigned int color);
	unsigned int GetColor();
	V3 RotateVector(V3 adir, float theta);
	V3 RotatePoint(V3 aO, V3 adir, float theta);
	V3 Light(V3 lv, V3 nv, float ka);

};
