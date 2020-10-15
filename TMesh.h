#pragma once

#include "V3.h"
#include "M33.h"
#include "ppc.h"
#include "framebuffer.h"
#include"texture.h"

class TMesh {
public:
	int onFlag;
	V3 *verts;
	V3 *colors;
	V3 *normals;
	V3* textureSTpair;
	int vertsN;
	float tileM, tileN; //Number of texture tiles in each direction
	unsigned int *tris;
	int trisN;
	TMesh() : verts(0), vertsN(0), tris(0), trisN(0), colors(0), normals(0), onFlag(1) {};
	void SetToCube(V3 cc, float sideLength, unsigned int color0, unsigned int color1);
	void Allocate(int _vertsN, int _trisN);
	void DrawCubeQuadFaces(FrameBuffer *fb, PPC *ppc, unsigned int color);
	void DrawWireFrame(FrameBuffer *fb, PPC *ppc, unsigned int color);
	void DrawPlanerRect(V3 cc, float sideLength,  unsigned int color);
	void DrawPlanerRectUpdateNormal();
	void LoadBin(char *fname);
	V3 GetCenter();
	void SetCenter(V3 center);
	void Translate(V3 tv);
	void Rotate(V3 aO, V3 aDir, float theta);
	//void RenderFilled(FrameBuffer *fb, PPC *ppc);
	void RenderFilled(FrameBuffer* fb, PPC* ppc, V3 C, V3 L, float ka);
	void RenderFilled(FrameBuffer* fb, PPC* ppc);
	V3 SetEEQ(V3 v0, V3 v1, V3 v2);
	M33 SetEEQs(V3 pv0, V3 pv1, V3 pv2);
	M33 SetSSIM(V3 pv0, V3 pv1, V3 pv2);
	M33 SetMSIM(V3 V1, V3 V2, V3 V3, PPC* ppc);
	void InitTexture();
	void MapTextureCorners2TriangleVerts(int triangleID, int whichHalf);
	void info();
	void RenderTexture(FrameBuffer* rfb, PPC* rppc, texture* t1);
	void RenderTextureProjector(FrameBuffer* rfb, PPC* rppc, FrameBuffer* t1);
	void GetBarryCentric(V3 p1, V3 p2, V3 p3, V3 p, V3& uvw);
	float CalcArea(V3 p1, V3 p2, V3 p3);
	unsigned int bilinearinterpolation(FrameBuffer* t1, float uf, float vf);
	unsigned int NonBilinearReginterpolation(texture* t1, float uf, float vf);
	void setXYtileN(float m, float n);
	void Light(V3 C, V3 L, float ka);
	void RenderFilledLight(FrameBuffer* fb, PPC* ppc, V3 C, V3 L, float ka);
	void RenderShadowZmap(FrameBuffer* fb, PPC* Lppc, float *Zb);
	void RenderFilledWithShadow(FrameBuffer* fb, PPC* ppc, float* zb, PPC* LightPPC, V3 C, V3 L, float ka);
	void RenderFilledProjector(FrameBuffer* fb0, FrameBuffer* fb1, PPC* ppc0, PPC* ppc1);

};