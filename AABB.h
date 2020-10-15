#pragma once

#include "V3.h"

class AABB {
public:
	V3 corners[2];
	AABB(V3 firstPoint);
	void AddPoint(V3 P);
	int clipwithframe(int w, int h);
};