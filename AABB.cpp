#include "stdafx.h"

#include "AABB.h"

AABB::AABB(V3 firstPoint) {

	corners[0] = corners[1] = firstPoint;

}

void AABB::AddPoint(V3 P) {

	for (int i = 0; i < 3; i++) {
		if (corners[0][i] > P[i])
			corners[0][i] = P[i];
		if (corners[1][i] < P[i])
			corners[1][i] = P[i];
	}

}

int AABB:: clipwithframe(int w, int h)
{
	int u = corners[0][0];
	int v = corners[1][1];
	if (u < 0 || u > w - 1 || v < 0 || v > h - 1)
		return 0;
	return 1;
}