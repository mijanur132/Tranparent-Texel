#pragma once

#include "V3.h"

using namespace std;


class M33 {
public:
	V3 rows[3];
	M33() {};
	V3& operator[](int i);
	V3 operator*(V3 v);
	
	V3 GetColumn(int i);
	void SetColumn(int i, V3 c);	
	void SetRotationAboutY(float angled);

	M33 Inverted();  //g
	M33 Transposed();  //h
};

