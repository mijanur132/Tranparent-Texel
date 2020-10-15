#include "stdafx.h"

#include <fstream>
#include <iostream>

#include "M33.h"
#include "TMesh.h"
#include "AABB.h"

using namespace std;


void TMesh::Allocate(int _vertsN, int _trisN) {

	vertsN = _vertsN;
	trisN = _trisN;
	verts = new V3[vertsN];
	textureSTpair = new V3[vertsN];
	colors = new V3[vertsN];
	normals = new V3[vertsN];
	tris = new unsigned int[trisN * 3];
	tileM = 1;
	tileN = 1;
}

void TMesh::InitTexture()
{
	for (int i = 0; i < vertsN; i++)
	{
		textureSTpair[i] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}


}

void TMesh::info() {

	for (int i = 0; i < trisN; i++)
	{
		cout << "vertices of triangle: " << i << " are: " << endl;
		cout<<"vertice ID: "<<tris[3 * i] << ", vertice:" << verts[tris[3 * i]] << ", textureRSpair:" << textureSTpair[tris[3 * i]] << endl;
		cout << "vertice ID: " << tris[3 * i+1] << ", vertice:" << verts[tris[3 * i+1]] << ", textureRSpair:" << textureSTpair[tris[3 * i+1]] << endl;
		cout << "vertice ID: " << tris[3 * i+2] << ", vertice:" << verts[tris[3 * i+2]] << ", textureRSpair:" << textureSTpair[tris[3 * i+2]] << endl;
	}

}

void TMesh::SetToCube(V3 cc, float sideLength, unsigned int color0, unsigned int color1) {

	vertsN = 8;
	trisN = 6 * 2;
	Allocate(vertsN, trisN);



	for (int vi = 0; vi < 4; vi++) {
		colors[vi].SetFromColor(color0);
		colors[vi+4].SetFromColor(color1);
	}

	int vi = 0;
	verts[vi] = cc + V3(-sideLength / 2.0f, +sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(-sideLength / 2.0f, -sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength / 2.0f, -sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength / 2.0f, +sideLength / 2.0f, +sideLength / 2.0f);
	vi++;

	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;

	int tri = 0;
	tris[3 * tri + 0] = 0;
	tris[3 * tri + 1] = 1;
	tris[3 * tri + 2] = 2;
	tri++;
	tris[3 * tri + 0] = 2;
	tris[3 * tri + 1] = 3;
	tris[3 * tri + 2] = 0;
	tri++;
	tris[3 * tri + 0] = 3;
	tris[3 * tri + 1] = 2;
	tris[3 * tri + 2] = 6;
	tri++;
	tris[3 * tri + 0] = 6;
	tris[3 * tri + 1] = 7;
	tris[3 * tri + 2] = 3;
	tri++;
	tris[3 * tri + 0] = 7;
	tris[3 * tri + 1] = 6;
	tris[3 * tri + 2] = 5;
	tri++;
	tris[3 * tri + 0] = 5;
	tris[3 * tri + 1] = 4;
	tris[3 * tri + 2] = 7;
	tri++;
	tris[3 * tri + 0] = 4;
	tris[3 * tri + 1] = 5;
	tris[3 * tri + 2] = 1;
	tri++;
	tris[3 * tri + 0] = 1;
	tris[3 * tri + 1] = 0;
	tris[3 * tri + 2] = 4;
	tri++;
	tris[3 * tri + 0] = 4;
	tris[3 * tri + 1] = 0;
	tris[3 * tri + 2] = 3;
	tri++;
	tris[3 * tri + 0] = 3;
	tris[3 * tri + 1] = 7;
	tris[3 * tri + 2] = 4;
	tri++;
	tris[3 * tri + 0] = 1;
	tris[3 * tri + 1] = 5;
	tris[3 * tri + 2] = 6;
	tri++;
	tris[3 * tri + 0] = 6;
	tris[3 * tri + 1] = 2;
	tris[3 * tri + 2] = 1;
	tri++;

}

void TMesh::DrawCubeQuadFaces(FrameBuffer *fb, PPC *ppc, unsigned int color) {

	V3 c0;
	c0.SetFromColor(color);
	for (int si = 0; si < 4; si++) {
		fb->Draw3DSegment(verts[si], verts[(si + 1) % 4], ppc, c0, c0);
		fb->Draw3DSegment(verts[4+si], verts[4 + (si + 1) % 4], ppc, c0, c0);
		fb->Draw3DSegment(verts[si], verts[si + 4], ppc, c0, c0);
	}

}

void TMesh::DrawPlanerRect(V3 cc, float sideLength, unsigned int color) {

	vertsN = 4;
	trisN = 2;
	Allocate(vertsN, trisN);


	int vi = 0;
	verts[vi] = cc + V3(-sideLength / 2.0f, +sideLength / 2.0f, 0);
	vi++;
	verts[vi] = cc + V3(-sideLength / 2.0f, -sideLength / 2.0f,0);
	vi++;
	verts[vi] = cc + V3(+sideLength / 2.0f, -sideLength / 2.0f, 0);
	vi++;
	verts[vi] = cc + V3(+sideLength / 2.0f, +sideLength / 2.0f,0);
	vi++;


	int tri = 0;
	tris[3 * tri + 0] = 0;
	tris[3 * tri + 1] = 1;
	tris[3 * tri + 2] = 2;
	tri++;
	tris[3 * tri + 0] = 2;
	tris[3 * tri + 1] = 3;
	tris[3 * tri + 2] = 0;
	tri++;

	for (int vi = 0; vi < 4; vi++) {
		colors[vi].SetFromColor(color);		
	}

	V3 v01 = verts[0] - verts[1];
	V3 v03 = verts[0] - verts[2];

	V3 normal = v01 ^ v03.Normalized();

	normal=normal.Normalized();
	for (int vi = 0; vi < 4; vi++) {
		normals[vi]=normal;
	}

}

void TMesh::DrawPlanerRectUpdateNormal() {

	V3 v01 = verts[0] - verts[1];
	V3 v03 = verts[0] - verts[2];

	V3 normal = v01 ^ v03.Normalized();

	normal = normal.Normalized();
	for (int vi = 0; vi < 4; vi++) {
		normals[vi] = normal;
	}
}

void TMesh::DrawWireFrame(FrameBuffer *fb, PPC *ppc, unsigned int color) {
	//trisN = 2; //temp just to check one face of the cube for hw3 other wise delte this line.
	for (int tri = 0; tri < trisN; tri++) {
		V3 V0 = verts[tris[3 * tri + 0]];
		V3 V1 = verts[tris[3 * tri + 1]];
		V3 V2 = verts[tris[3 * tri + 2]];
		V3 c0 = colors[tris[3 * tri + 0]];
		V3 c1 = colors[tris[3 * tri + 1]];
		V3 c2 = colors[tris[3 * tri + 2]];
		fb->Draw3DSegment(V0, V1, ppc, c0, c1);
		fb->Draw3DSegment(V1, V2, ppc, c1, c2);
		fb->Draw3DSegment(V2, V0, ppc, c2, c0);
	}

}

void TMesh::LoadBin(char *fname) {

	ifstream ifs(fname, ios::binary);
	if (ifs.fail()) {
		cerr << "INFO: cannot open file: " << fname << endl;
		return;
	}

	ifs.read((char*)&vertsN, sizeof(int));
	char yn;
	ifs.read(&yn, 1); // always xyz
	if (yn != 'y') {
		cerr << "INTERNAL ERROR: there should always be vertex xyz data" << endl;
		return;
	}
	if (verts)
		delete verts;
	verts = new V3[vertsN];

	ifs.read(&yn, 1); // cols 3 floats
	if (colors)
		delete colors;
	colors = 0;
	if (yn == 'y') {
		colors = new V3[vertsN];
	}

	ifs.read(&yn, 1); // normals 3 floats
	if (normals)
		delete normals;
	normals = 0;
	if (yn == 'y') {
		normals = new V3[vertsN];
	}

	ifs.read(&yn, 1); // texture coordinates 2 floats
	float *tcs = 0; // don't have texture coordinates for now
	if (tcs)
		delete tcs;
	tcs = 0;
	if (yn == 'y') {
		tcs = new float[vertsN * 2];
	}

	ifs.read((char*)verts, vertsN * 3 * sizeof(float)); // load verts

	if (colors) {
		ifs.read((char*)colors, vertsN * 3 * sizeof(float)); // load cols
	}

	if (normals)
		ifs.read((char*)normals, vertsN * 3 * sizeof(float)); // load normals

	if (tcs)
		ifs.read((char*)tcs, vertsN * 2 * sizeof(float)); // load texture coordinates

	ifs.read((char*)&trisN, sizeof(int));
	if (tris)
		delete tris;
	tris = new unsigned int[trisN * 3];
	ifs.read((char*)tris, trisN * 3 * sizeof(unsigned int)); // read tiangles

	ifs.close();

	cerr << "INFO: loaded " << vertsN << " verts, " << trisN << " tris from " << endl << "      " << fname << endl;
	cerr << "      xyz " << ((colors) ? "rgb " : "") << ((normals) ? "nxnynz " : "") << ((tcs) ? "tcstct " : "") << endl;

}

V3 TMesh::GetCenter() {

	V3 ret(0.0f, 0.0f, 0.0f);
	for (int vi = 0; vi < vertsN; vi++) {
		ret = ret + verts[vi];
	}
	ret = ret / (float)vertsN;
	return ret;

}

void TMesh::Translate(V3 tv) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] + tv;
	}

}

void TMesh::SetCenter(V3 center) {

	V3 currCenter = GetCenter();
	Translate(center - currCenter);

}



void TMesh::Rotate(V3 aO, V3 aDir, float theta) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi].RotatePoint(aO, aDir, theta);
	}

}


void TMesh::RenderFilled(FrameBuffer *fb, PPC *ppc) {

	V3 *pverts = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	//trisN = 2; //temp just to check one face of the cube for hw3 other wise delte this line.

	for (int tri = 0; tri < trisN; tri++) {
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2]};
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		 if (!aabb.clipwithframe(fb->w, fb->h))
			continue;
		
		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;
		M33 cm;
		cm.SetColumn(0, colors[vinds[0]]);
		cm.SetColumn(1, colors[vinds[1]]);
		cm.SetColumn(2, colors[vinds[2]]);
		M33 cLEm;
		cLEm[0] = ssim * cm[0];
		cLEm[1] = ssim * cm[1];
		cLEm[2] = ssim * cm[2];
		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				float currz = zLE * currPix;
				if (fb->Farther(u, v, currz))
					continue; // hidden
				V3 currColor = cLEm*currPix;
				fb->Set(u, v, currColor.GetColor());
			}
		}

	}

	delete []pverts;

}



void TMesh::RenderFilled(FrameBuffer* fb, PPC* ppc, V3 C, V3 L, float ka) {

	//int trisN = 1;

	V3* pverts = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	for (int tri = 0; tri < trisN; tri++) {
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		 if (!aabb.clipwithframe(fb->w, fb->h))
			continue;

		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;
		M33 cm;
		cm.SetColumn(0, colors[vinds[0]]);
		cm.SetColumn(1, colors[vinds[1]]);
		cm.SetColumn(2, colors[vinds[2]]);
		M33 cLEm;
		cLEm[0] = ssim * cm[0];
		cLEm[1] = ssim * cm[1];
		cLEm[2] = ssim * cm[2];

		M33 nm;
		nm.SetColumn(0, normals[vinds[0]]);
		nm.SetColumn(1, normals[vinds[1]]);
		nm.SetColumn(2, normals[vinds[2]]);
		M33 nLEm;
		nLEm[0] = ssim * nm[0];
		nLEm[1] = ssim * nm[1];
		nLEm[2] = ssim * nm[2];


		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				float currz = zLE * currPix;
				if (fb->Farther(u, v, currz))
				{
					cout << "further z" << endl;
					continue; // hidden
				}
				V3 currColor = cLEm * currPix;

				// normal at current pixel
				V3 currNormal = nLEm * currPix;
				V3 nv = currNormal.Normalized();

				// 3D surface point at current pixel
				V3 currP = ppc->UnProject(V3(currPix[0], currPix[1], currz));

				// light vector
				V3 lv = (L - currP).Normalized();
				currColor = C.Light(lv, nv, ka);
				//fb->Set(u, v, currColor.GetColor());
			}
		}

	}

	delete[]pverts;

}


void TMesh::RenderShadowZmap(FrameBuffer* fb, PPC* LightSrcAsPPC, float* zbx)
{
	//int trisN = 1;



	V3* pverts = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!LightSrcAsPPC->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	for (int tri = 0; tri < trisN; tri++) {
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		 if (!aabb.clipwithframe(fb->w, fb->h))
			continue;

		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;

		for (int v = top; v <= bottom; v++) 
		{
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				float currz = zLE * currPix;
				//cout << currz << endl;
				if (fb->FartherLightZ(zbx, u, v, currz))					
					continue; // hidden
				
				//float colz = abs(currz)/10;
				//V3 currColor = V3(colz, 0, 0);
				//fb->Set(u, v, currColor.GetColor());
				
			}
		}

	}

	delete[]pverts;

}



void TMesh::RenderFilledWithShadow(FrameBuffer* fb, PPC* ppc, float* zbx, PPC* LightPPC, V3 C, V3 L, float ka) {
	
#if 0
	project three vertices of the triangle camera plane
		check boundary
#endif

	V3* pverts = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	for (int tri = 0; tri < trisN; tri++) {
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		 if (!aabb.clipwithframe(fb->w, fb->h))
			continue;

		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;
		M33 cm;
		cm.SetColumn(0, colors[vinds[0]]);
		cm.SetColumn(1, colors[vinds[1]]);
		cm.SetColumn(2, colors[vinds[2]]);
		M33 cLEm;
		cLEm[0] = ssim * cm[0];
		cLEm[1] = ssim * cm[1];
		cLEm[2] = ssim * cm[2];

		M33 nm;
		nm.SetColumn(0, normals[vinds[0]]);
		nm.SetColumn(1, normals[vinds[1]]);
		nm.SetColumn(2, normals[vinds[2]]);
		M33 nLEm;
		nLEm[0] = ssim * nm[0];
		nLEm[1] = ssim * nm[1];
		nLEm[2] = ssim * nm[2];

		
		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				float currz = zLE * currPix;	

				V3 unprojectedP=LightPPC->UnProject(V3(u, v, currz));
				
				V3 lighFrameP(0, 0, 0);
				LightPPC->Project(unprojectedP, lighFrameP);
				
				
				if (fb->FartherLightZCompare(zbx,lighFrameP[0], lighFrameP[1],lighFrameP[2] ))
				{

					V3 currColor = cLEm * currPix;					
					
					currColor = C * ka;
					fb->Set(u, v, currColor.GetColor());
					
					continue; 
				}

				if (fb->Farther(u, v, currz))
				{
					continue; 
				}


				V3 currColor = cLEm * currPix;

				// normal at current pixel
				V3 currNormal = nLEm * currPix;
				V3 nv = currNormal.Normalized();
				
				// 3D surface point at current pixel
				V3 currP = ppc->UnProject(V3(currPix[0], currPix[1], currz));
			
				// light vector
				V3 lv = (L - currP).Normalized();
				//cout << "nv lv" << nv << " " << lv << endl;
				currColor = C.Light(lv, nv, ka);
				fb->Set(u, v, currColor.GetColor());
			}
		}

	}

	delete[]pverts;

}

void TMesh::RenderFilledProjector(FrameBuffer* fb0, FrameBuffer* fb1, PPC* ppc0, PPC* ppc1) {

#if 0
	first determine ppc1 projections from tmesh points
#endif

	V3* pverts = new V3[vertsN];
	V3* pverts2 = new V3[vertsN];

	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc1->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);

		if (!ppc0->Project(verts[vi], pverts2[vi]))
			pverts2[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	for (int tri = 0; tri < trisN; tri++) {
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		if (!aabb.clipwithframe(fb1->w, fb1->h))
			continue;

		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;

		M33 cm;
		cm.SetColumn(0, colors[vinds[0]]);
		cm.SetColumn(1, colors[vinds[1]]);
		cm.SetColumn(2, colors[vinds[2]]);
		M33 cLEm;
		cLEm[0] = ssim * cm[0];
		cLEm[1] = ssim * cm[1];
		cLEm[2] = ssim * cm[2];

#if 0
		run through ppc1 frame on each triangle AABB
#endif

		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				float currz = zLE * currPix;
				
#if 1
				if (fb1->Farther(u, v, currz))
				{
					continue;
				}
#endif

#if 0
				we found the outputImage point. Now project it back to the object to get the scene point. 
					Once we get the scene point, and compare with the z buffer to check whether it is visible from the output frame at ppc1.
					Then, project it to the projector ppc0 and compare with z buffer to check visiblity from the projector. 
					if not visible take the value from scenePoint and update the color at fb1 at u,v- scene color here is done by taking ssim of there vertex color of the triangle
						if they are beyond the frame w and h (ref pverts2) take the value from scenePointand update the color at fb1 at u, v - scene color here is done by taking ssim of there vertex color of the triangle
						if visible get the color at projector pix at fb0->pix at cordinate projectorFramePoint[0] and projectorFramePoint[1]. 
#endif
				V3 outputImagePoint = V3(u, v, currz);
				V3 scenePoint = ppc1->UnProject(outputImagePoint);

				if (
					pverts2[vinds[0]][0] == FLT_MAX ||
					pverts2[vinds[1]][0] == FLT_MAX ||
					pverts2[vinds[2]][0] == FLT_MAX
					) 
				{
					V3 currColor = cLEm * currPix;
					//fb1->Set(u, v, currColor.GetColor());

					continue;
				}

				V3 projectorFramePoint(0, 0, 0);
				ppc0->Project(scenePoint, projectorFramePoint);		

			
#if 1
				if (fb0->FartherLightZCompare(fb0->zbL1, projectorFramePoint[0], projectorFramePoint[1], projectorFramePoint[2]))
				{

					V3 currColor = cLEm * currPix;					
					//fb1->Set(u, v, currColor.GetColor());
					continue;
				}		
#endif



				unsigned int projectorColor = fb0->Get((int)projectorFramePoint[0], (int)projectorFramePoint[1]);	
#if 1
				//implement transplant pixel 
				V3 color;
				color.SetFromColor(projectorColor);
				if (color[0] < 0.5)
				{
					continue;
				}
								
#endif	

				fb1->Set(u, v, projectorColor);
			}
		}

	}

	delete[]pverts;

}



void TMesh::RenderFilledLight(FrameBuffer* fb, PPC* ppc, V3 C, V3 L, float ka) {

	V3* pverts = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	//trisN = 2; //temp just to check one face of the cube for hw3 other wise delte this line.

	for (int tri = 0; tri < trisN; tri++) {
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		 if (!aabb.clipwithframe(fb->w, fb->h))
			continue;

		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;
		M33 cm;
		cm.SetColumn(0, colors[vinds[0]]);
		cm.SetColumn(1, colors[vinds[1]]);
		cm.SetColumn(2, colors[vinds[2]]);
		M33 cLEm;
		cLEm[0] = ssim * cm[0];
		cLEm[1] = ssim * cm[1];
		cLEm[2] = ssim * cm[2];


		M33 nm;
		nm.SetColumn(0, normals[vinds[0]]);
		nm.SetColumn(1, normals[vinds[1]]);
		nm.SetColumn(2, normals[vinds[2]]);
		M33 nLEm;
		nLEm[0] = ssim * nm[0];
		nLEm[1] = ssim * nm[1];
		nLEm[2] = ssim * nm[2];



		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				float currz = zLE * currPix;
				if (fb->Farther(u, v, currz))
					continue; // hidden
				V3 currColor = cLEm * currPix;



				// normal at current pixel
				V3 currNormal = nLEm * currPix;
				V3 nv = currNormal.Normalized();

				// 3D surface point at current pixel
				V3 currP = ppc->UnProject(V3(currPix[0], currPix[1], currz));

				// light vector
				V3 lv = (L - currP).Normalized();
				currColor = C.Light(lv, nv, ka);			

				fb->Set(u, v, currColor.GetColor());
			}
		}

	}

	delete[]pverts;

}


V3 TMesh::SetEEQ(V3 v0, V3 v1, V3 v2) {

#if 0

	(x - x0) / (x1 - x0) = (y - y0) / (y1 - y0)
	(x - x0)*(y1 - y0) = (y - y0)*(x1 - x0);
	x*(y1 - y0) + y * (x0 - x1) + x0(y0 - y1) + y0(x1 - x0) = 0
	xA + yB + C = 0
#endif

	float x0, x1, y0, y1;
	x0 = v0[0];
	x1 = v1[0];
	y0 = v0[1];
	y1 = v1[1];
	V3 ret;
	ret[0] = y1 - y0;
	ret[1] = x0 - x1;
//	ret[2] = x0*(y0 - y1) + y0*(x1 - x0);
	ret[2] = -x0*y1 + y0*x1;
	V3 v2p(v2); v2p[2] = 1.0f;

	if (ret*v2p < 0.0f) // ret * v2p = Au+Bv+C
		ret = ret * -1.0f;

	return ret;

}

M33 TMesh::SetEEQs(V3 pv0, V3 pv1, V3 pv2) {

	M33 ret;
	V3 pvs[3];
	pvs[0] = pv0;
	pvs[1] = pv1;
	pvs[2] = pv2;
	for (int ei = 0; ei < 3; ei++) {
		ret[ei] = SetEEQ(pvs[ei], pvs[(ei + 1) % 3], pvs[(ei + 2) % 3]);
	}
	return ret;
}

// LE(u, v) = Au + Bv + c;

// LE(u + 1, v) = LE(u, v) + A;

M33 TMesh::SetSSIM(V3 pv0, V3 pv1, V3 pv2) {

	M33 ret;
	ret[0] = pv0;
	ret[1] = pv1;
	ret[2] = pv2;
	ret.SetColumn(2, V3(1.0f, 1.0f, 1.0f));
	return ret.Inverted();

}
#if 0
model space works with unprojected original vertices of the model
#endif

M33 TMesh::SetMSIM(V3 V1, V3 V2, V3 V3, PPC* ppc) {

	M33 ret;
	ret[0] = V1-  ppc->C;
	ret[1] = V2 - ppc->C;
	ret[2] = V3 - ppc->C;
	ret = ret.Transposed();
	return ret.Inverted();



}

void TMesh::MapTextureCorners2TriangleVerts(int tri, int whichHalf) {
	//whichHalf 0-->left/up side  1 for right/down side triangle
	//Z VALUE DOES NOT MATTER
	unsigned int vin[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
	
	if (whichHalf == 0)
	{
		textureSTpair[vin[0]] = V3(0*tileM, 0*tileN, 1);
		textureSTpair[vin[1]] = V3(0*tileM, 1*tileN, 1);
		textureSTpair[vin[2]] = V3(1*tileM, 1*tileN, 1);
	}
	else {
	
		textureSTpair[vin[0]] = V3(1*tileM, 1*tileN, 1);
		textureSTpair[vin[1]] = V3(1*tileM, 0*tileN, 1);
		textureSTpair[vin[2]] = V3(0*tileM, 0*tileN, 1);
	
	}
}



void TMesh::RenderTexture(FrameBuffer* fb, PPC* ppc, texture* t1) {

	V3* pverts = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	trisN = 2; //temp just to check one face of the cube for hw3 other wise delte this line.

	for (int tri = 0; tri < trisN; tri++)
	{
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		if (!aabb.clipwithframe(fb->w, fb->h))
			continue;

		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);


		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;


		V3 texS(textureSTpair[vinds[0]][0], textureSTpair[vinds[1]][0], textureSTpair[vinds[2]][0]);
		V3 texT(textureSTpair[vinds[0]][1], textureSTpair[vinds[1]][1], textureSTpair[vinds[2]][1]);
		V3 sLE = ssim * texS;
		V3 tLE = ssim * texT;
#if 0
		cout << verts[vinds[0]] << verts[vinds[1]] << verts[vinds[2]] << endl;
		cout << "texS and texT:" << endl;
		cout << texS << texT << endl;
		cout << "sLE and tLE" << endl;
		cout << sLE << tLE << endl;
		cout << top << " " << bottom << " " << left << " " << right << endl;
#endif
		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				float currz = zLE * currPix;

#if 1
				currPix[2] = currz;
				V3 UcurrPix = ppc->UnProject(currPix);
				V3 uvw(0, 0, 0);
				GetBarryCentric(verts[vinds[0]], verts[vinds[1]], verts[vinds[2]], UcurrPix, uvw);
				float currS = (uvw.xyz[2] * textureSTpair[vinds[0]][0] + uvw.xyz[0] * textureSTpair[vinds[1]][0] + uvw.xyz[1] * textureSTpair[vinds[2]][0]) * t1->w;
				float currT = (uvw.xyz[2] * textureSTpair[vinds[0]][1] + uvw.xyz[0] * textureSTpair[vinds[1]][1] + uvw.xyz[1] * textureSTpair[vinds[2]][1]) * t1->h;

#endif

#if 0
				cout << "unprojected curr pix and barrycentric uvw:" << endl;
				cout << UcurrPix << endl;
				cout << uvw << endl;
				cout << verts[vinds[0]] << endl;
				cout << verts[vinds[1]] << endl;
				cout << verts[vinds[2]] << endl;
				cout << "texS" << textureSTpair[vinds[0]][0] << " " << textureSTpair[vinds[1]][0] << " " << textureSTpair[vinds[2]][0] << endl;
				cout << "texT" << textureSTpair[vinds[0]][1] << " " << textureSTpair[vinds[1]][1] << " " << textureSTpair[vinds[2]][1] << endl;
				cout << "j, i, T, s:" << v << "," << u << "," << currT << "," << currS << endl;
				cout << pixIJ << endl;
#endif

#if 0
				int currS = sLE * currPix * t1->w;
				int currT = tLE * currPix * t1->h;
				//cout << "j, i, T, s:" << v << "," << u << "," << currT << "," << currS << endl;
				int pixIJ = currS + currT * t1->w;
				//cout << pixIJ << endl;
#endif

#if 0
				//use this two lines to check weather interpolation works or not based on the colors of the vertices
				V3 color = V3(uvw[2], 0, 0);
				unsigned int color_uvw = color.GetColor();

#endif
				//unsigned int color_uvw = bilinearinterpolation(t1, currS, currT);
				//unsigned int color_uvw = NonBilinearReginterpolation(t1, currS, currT);
				if (fb->Farther(u, v, currz))
					continue; // hidden

				//fb->Set(u, v, color_uvw);
			}
		}

	}

	delete[]pverts;
}


float TMesh::CalcArea(V3 p1, V3 p2, V3 p3)
{
	float area = ((p1.xyz[0] * (p2.xyz[1] - p3.xyz[1]) + p2.xyz[0] * (p3.xyz[1] - p1.xyz[1]) + p3.xyz[0] * (p1.xyz[1] - p2.xyz[1])) / 2.0f);
	return area;
}

/*
c
 \
|		w	\
	\			\
  u	 D *		-	-	b
|				/
	/	v	/
|		/
a
 some point P=ua+vb+wc
*/

/*
Gives barrycentric co-ordinates of a point p with respect to a triangle with point a,b and c
Refer to the graph above for understanding u,v and w
calculates area of the whole triangle and sub triangles formed by the point and two triangle points and find ratios
returns
barycentric parameters u,b,w
0<u,v,w<1 for the point within the triangle. 0 means on the line.
*/

void TMesh::GetBarryCentric(V3 a, V3 b, V3 c, V3 p, V3& uvw)
{
	float area_abc = CalcArea(a, b, c) + 0.01f;
	float area_cap = CalcArea(c, a, p);
	float area_abp = CalcArea(a, b, p);
	float area_bcp = CalcArea(b, c, p);

	uvw.xyz[0] = area_cap / area_abc;
	uvw.xyz[1] = area_abp / area_abc;
	uvw.xyz[2] = area_bcp / area_abc;

}
unsigned int TMesh::NonBilinearReginterpolation(texture* t1, float uf, float vf)
{
	int pixIJ = t1->getPixelIndex(uf, vf);
	if (pixIJ >= t1->w * t1->w)
	{
		pixIJ = t1->w * t1->w - 1;
		cout << "****************Warning: pixel beyond texture******************" << endl;
	}
	if (pixIJ < 0)
	{
		pixIJ = 0;
		cout << "****************Warning: pixel beyond texture******************" << endl;
	}
	return t1->pix[pixIJ];
	

}

unsigned int TMesh::bilinearinterpolation(FrameBuffer* t1, float uf, float vf)
{
	V3 colorBilinear;

	if (vf < (t1->h - 1.5) && vf> 0.5 && uf > 0.5 && uf < (t1->w - 1.5))
	{
		float u0 = (uf - 0.5f);
		float v0 = (vf - 0.5f);
		int u0f = floor(u0);
		int v0f = floor(v0);

		float dx = u0 - u0f;
		float dy = v0 - v0f;

		V3 c0, c1, c2, c3;
		int i0, i1, i2, i3;
		float a0, a1, a2, a3;

		i0 = t1->getPixelIndex(u0f, v0f);
		i1 = t1->getPixelIndex(u0f + 1, v0f);
		i2 = t1->getPixelIndex(u0f + 1, v0f + 1);
		i3 = t1->getPixelIndex(u0f, v0f + 1);
		//cout << "u0f, v0f, i0, i1, i2, i3:" << u0f<<" " << v0f<<" " << i0 <<" "<< i1 <<" "<<i2<<" "<<i3<< endl;
		c0.SetFromColor(t1->pix[i0]);
		c1.SetFromColor(t1->pix[i1]);
		c2.SetFromColor(t1->pix[i2]);
		c3.SetFromColor(t1->pix[i3]);
		//cout << c0<<" " << c1<<" " << c2<<" " << c3 << endl;
		
		a0 = (1 - dx) * (1 - dy);
		a1 = dx * (1 - dy);
		a2 = dx * dy;
		a3 = (1 - dx) * dy;
		//a0 = a1 = a2 = a3 = 1;
		//cout << a0 << " " << a1<<"  "<<a2<<" "<<a3<<endl;
		for (int i = 0; i < 3; i++)
		{
			colorBilinear[i] = (a0 * c0[i] + a2 * c2[i] + a1 * c1[i] + a3 * c3[i]);

		}

		return colorBilinear.GetColor();

	}
	else 
	{
		int pixIJ = t1->getPixelIndex(uf, vf);
		if (pixIJ >= t1->w * t1->w)
		{
			pixIJ = t1->w * t1->w - 1;
			cout << "****************Warning: pixel beyond texture******************" <<uf<<" "<<vf <<endl;
		}
		if (pixIJ < 0)
		{
			pixIJ = 0;
			cout << "****************Warning: pixel beyond texture******************" << uf << " " << vf << endl;
		}
		return t1->pix[pixIJ];

	}
	
}

void TMesh::setXYtileN(float m, float n) {
	tileM = m;
	tileN = n;
}

void TMesh::Light(V3 C, V3 L, float ka) {

	for (int vi = 0; vi < vertsN; vi++) {
		V3 lv = (L - verts[vi]).Normalized();
		V3 nv = normals[vi].Normalized();
		colors[vi] = C.Light(lv, nv, ka);
	}

}

