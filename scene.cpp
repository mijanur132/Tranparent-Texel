#include "stdafx.h"

#include "scene.h"

#include "V3.h"
#include "M33.h"
#include "ppc.h"
#include "TMesh.h"

Scene* scene;

using namespace std;

#include <iostream>


Scene::Scene() {


	gui = new GUI();
	gui->show();

#if 0
	prepare frame buffers
#endif 

		int u0 = 20;
	int v0 = 100;
	int h = 600;
	int w = 700;

	fb0 = new FrameBuffer(u0, v0, w, h, 0);
	fb0->label("camera 0");
	fb0->show();
	fb0->redraw();

	fb1 = new FrameBuffer(u0 + w + 30, v0, w, h, 0);
	fb1->label("camera 1");
	fb1->show();
	fb1->redraw();

	gui->uiw->position(u0, v0 + h + 50);

	V3 col = V3(0, 0, 1.0f);
	V3 col1 = V3(1.0f, 0, 0);


#if 0
	prepare the tmesh objects of the scene
#endif 

		tmeshesN = 3;
	tmeshes = new TMesh[tmeshesN];

	V3 cc0(0.0f, 0.0f, 0.0f);

	tmeshes[0].LoadBin("geometry/auditorium.bin");
	//tmeshes[0].DrawPlanerRect(cc0, 100, col1.GetColor());	
	tmeshes[0].Rotate(tmeshes[0].GetCenter(), V3(1, 0, 0), -90.0f);
	tmeshes[0].Rotate(tmeshes[0].GetCenter(), V3(0, 1, 0), 180.0f);
	tmeshes[0].SetCenter(cc0);
	tmeshes[0].onFlag = 1;


	tmeshes[1].LoadBin("geometry/teapot1K.bin");
	//tmeshes[1].LoadBin("geometry/teapot57K.bin");
	tmeshes[1].SetCenter(V3(0.0f, 0.0f, 0.0f));  //***************************center of 1
	tmeshes[1].onFlag = 0;
	tmeshes[1].Rotate(tmeshes[1].GetCenter(), V3(1, 0, 0), -90);



#if 0
	prepare cameras
#endif 

		float hfov = 90.0f;
	ppc0 = new PPC(hfov, fb0->w, fb0->h);
	ppc1 = new PPC(hfov, fb1->w, fb1->h);

	ppc0->SetPose(V3(0, 0, -5), V3(0, 0, -100), V3(0, 1, 0));
	float roll = -45.0f;
	ppc0->Roll(roll);
	ppc1->PanLeftRight(0.0f);

#if 0
	our lightsource.
#endif

		L = V3(0.0f, 0.0f, 0.0f);  //*********************************************center of light camera
	float hfov1 = 90.0f;
	LightSrcPPC = new PPC(hfov1, fb1->w, fb1->h);
	//LightSrcPPC->SetPose(L, tmeshes[1].GetCenter(), V3(0, 1, 0));
	ka = 0.2f;


#if 0
	our drawing or other rendering operation
#endif

		fb0->redraw();
	fb1->redraw();

	for (int i = 0; i < 3600; i++)
	{
		cout << i << endl;
		RenderProjector(fb0, fb1, ppc0, ppc1);
		ppc0->Roll(roll * -1.0f);
		ppc0->PanLeftRight(-0.30f);
		ppc0->Roll(roll);
		//ppc1->PanLeftRight(-0.20f);
	}



	//Render(fb1, ppc1);
	//Render(fb, ppc,  &tmeshes[1]);
	//Render();

}

void Scene::Render() {
	for (int i = 0; i < 1; i++)
	{
		//tmeshes[1].Rotate(tmeshes[1].GetCenter(), V3(1, 0, 0), 2);
		cout << i << endl;
		Render(fb1, ppc1);
		ppc->PanLeftRight(0.5);
		Render(fb, ppc);

		fb0->redraw();
		fb1->redraw();
		Fl::check();
	}

}

void Scene::RenderProjector(FrameBuffer* fb0, FrameBuffer* fb1, PPC* ppc0, PPC* ppc1) {
#if 0
	Prepare two cameraand framebuffer: ppc0, fb0 for the projectorand ppc1, fb1 for the output camera
#endif

		fb0->SetBGR(0xFFFFFFFF);
	fb0->ClearZB();
	fb0->ClearZB(fb0->zbL1);

	fb1->SetBGR(0xFFFFFFFF);
	fb1->ClearZB();
	fb1->ClearZB(fb1->zbL1);

#if 0
	upload the image "I" on the the projector frame buffer if not done yet
		Calculate the shadow map from the projector camera pc0 to the projector framebuffer fb0->zbl1 to check visiblity.
#endif

		//fb0->LoadTiff("orange.tiff");
		fb0->LoadTiff("purdue.tiff");

	for (int tmi = 0; tmi < tmeshesN; tmi++)
	{
		if (!tmeshes[tmi].onFlag)
			continue;
		tmeshes[tmi].RenderShadowZmap(fb0, ppc0, fb0->zbL1);

	}

	V3 col1 = V3(1, 0, 0);

	fb1->Draw3DPoint(ppc0->C, ppc1, col1.GetColor(), 10);
	fb1->Draw3DPoint(ppc0->c * 3 + ppc0->C, ppc1, col1.GetColor(), 10);
	//fb1->Draw3DSegment(ppc0->C, ppc0->GetVD() * 3+ppc0->C, ppc1, col1, col1);
	fb1->Draw3DSegment(ppc0->C, ppc0->c * 3 + ppc0->C, ppc1, col1, col1);
	fb1->Draw3DSegment(ppc0->C, ppc0->GetVD().Normalized() * ppc0->GetF() + ppc0->C, ppc1, col1, col1);

#if 0
	Now call the renderFilledProjector() function to update the camera.
#endif

		for (int tmi = 0; tmi < tmeshesN; tmi++) {
			if (!tmeshes[tmi].onFlag)
				continue;
			tmeshes[tmi].RenderFilled(fb1, ppc1);
			tmeshes[tmi].RenderFilledProjector(fb0, fb1, ppc0, ppc1);


		}
#if 0
	perform displaying operation
#endif

		fb0->redraw();
	fb1->redraw();
	Fl::check();

}


//not improtant right now.

void Scene::Render(FrameBuffer* rfb, PPC* rppc) {

	for (int i = 0; i < 1; i++)
	{
		cout << i << endl;


		rfb->SetBGR(0xFFFFFFFF);
		rfb->ClearZB();
		rfb->ClearZB(rfb->zbL1);

		for (int tmi = 0; tmi < tmeshesN; tmi++) {
			if (!tmeshes[tmi].onFlag)
				continue;
			tmeshes[tmi].RenderShadowZmap(rfb, LightSrcPPC, rfb->zbL1);

		}

		for (int tmi = 0; tmi < tmeshesN; tmi++) {
			if (!tmeshes[tmi].onFlag)
				continue;

			V3 C(1.0f, 0.0f, 0.0f);
			tmeshes[tmi].Light(C, L, ka);
			tmeshes[tmi].RenderFilledWithShadow(rfb, rppc, rfb->zbL1, LightSrcPPC, C, L, ka);
			//tmeshes[tmi].DrawWireFrame(rfb, rppc, C.GetColor());


		}


		V3 col1 = V3(1, 0, 0);
		rfb->Draw3DPoint(LightSrcPPC->C, rppc, col1.GetColor(), 10);

		rfb->redraw();
		Fl::check();





		//tmeshes[1].Rotate(tmeshes[1].GetCenter(),V3(0,1,0),0.20f);
		//L=L.RotatePoint((tmeshes[1].GetCenter()), V3(0, 1, 0), -0.30f);
		//L = L + (V3(0.100f, 00.0f, 0.0f));
		//L = V3(140.0f, 0.0f, -100.0f);
		//LightSrcPPC->SetPose(L, tmeshes[1].GetCenter(), V3(0, 1, 0));
		//rppc->PanLeftRight(-10.0f);	


	}


	//tmeshes[0].SetCenter(V3 (50.0f, -15.0f, -100.0f));

}

void Scene::DBG() {
	{

		Render(fb1, ppc);
		return;

	}

	{

		//V3 tcenter = tmeshes[1].GetCenter();
		//V3 newC = V3(20.0f, 50.0f, -30.0f);
		//ppc->SetPose(newC, tcenter, V3(0.0f, 1.0f, 0.0f));

		int fN = 10000;
		V3 L0 = L;
		V3 L1 = tmeshes[1].GetCenter();
		for (int fi = 0; fi < fN; fi++) {
			L = L0 + (L1 - L0) * (float)fi / (float)(fN - 1);
			//L = L.RotatePoint(L1, V3(0.0f, 1.0f, 0.0f), 360.0f * 3.0f / (float)fN);
			Render();
			Fl::check();
		}
		L = L0;
		return;
	}
}



/*
Scene::Scene() {


	gui = new GUI();
	gui->show();

	int u0 = 10;
	int v0 = 10;
	int h = 400;
	int w = 500;

	fb = new FrameBuffer(u0, v0, w, h, 0);
	fb->label("SW 0");
	fb->show();

	//fb->redraw();
	fb1 = new FrameBuffer(u0+w+20, v0, w, h, 0);
	fb1->label("SW 2");
	fb1->show();


	fb2 = new FrameBuffer(u0 + 2*w + 40, 3*v0, w, h, 0);
	fb2->label("SW 3");
	fb2->show();

	fb3 = new FrameBuffer(u0, v0+h+20, w, h, 0);
	fb3->label("SW 4");
	fb3->show();

	fb4 = new FrameBuffer(u0+w+20, v0+h+20, w, h, 0);
	fb4->label("SW 5");
	fb4->show();



#if 1



	fb->SetBGR(0xFFFFFFFF);
	fb->ClearZB();

	fb1->SetBGR(0xFFFFFFFF);
	fb1->ClearZB();

	fb2->SetBGR(0xFFFFFFFF);
	fb2->ClearZB();

	fb3->SetBGR(0xFFFFFFFF);
	fb3->ClearZB();

	fb4->SetBGR(0xFFFFFFFF);
	fb4->ClearZB();


	gui->uiw->position(u0, v0 + h + 50);

	float hfov = 55.0f;
	ppc = new PPC(hfov, fb->w, fb->h);
	ppc3 = new PPC(hfov, fb3->w, fb3->h);

	tmeshesN = 5;
	tmeshes = new TMesh[tmeshesN];

	V3 cc(0.0f, 0.0f, -110.0f);
	float sideLength = 60.0f;
	tmeshes[0].SetToCube(cc, sideLength, 0xFF0000FF, 0xFF000000);
	tmeshes[1].SetToCube(cc, sideLength, 0xFF0000FF, 0xFF000000);
	tmeshes[2].SetToCube(cc, sideLength, 0xFF0000FF, 0xFF000000);
	tmeshes[3].SetToCube(cc, sideLength, 0xFF0000FF, 0xFF000000);
	tmeshes[4].SetToCube(cc, sideLength, 0xFF0000FF, 0xFF000000);

	//tmeshes[0].Rotate(tmeshes[0].GetCenter(),V3(0,1,0), 50.0f);
	tmeshes[0].onFlag = 1;
	//tmeshes[0].DrawWireFrame(fb, ppc, 0xFFFF00FF);

	t1=new texture();
	t1->LoadTiff("orange.tiff");

	t2 = new texture();
	t2->LoadTiff("complex.tiff");

	t3 = new texture();
	t3->LoadTiff("brick.tiff");

	t4 = new texture();
	t4->LoadTiff("reflection2.tiff");

	t5 = new texture();
	t5->LoadTiff("self.tiff");

	tmeshes[0].setXYtileN(3.0f, 3.0f);
	//tmeshes[0].setXYtileN(3.0f, 3.0f);
	for (int i = 0; i < 3600; i++)
	{
		Render(fb, ppc, t1, &tmeshes[0]);
		Render(fb1, ppc, t2, &tmeshes[1]);
		Render(fb2, ppc, t3, &tmeshes[2]);
		Render(fb3, ppc, t4, &tmeshes[3]);
		Render(fb4, ppc, t5, &tmeshes[4]);
		tmeshes[0].Rotate(tmeshes[0].GetCenter(), V3(0, 1, 0), 1.0f);
		tmeshes[1].Rotate(tmeshes[0].GetCenter(), V3(0, 1, 0), 1.0f);
		tmeshes[2].Rotate(tmeshes[0].GetCenter(), V3(0, 1, 0), 1.0f);
		tmeshes[3].Rotate(tmeshes[0].GetCenter(), V3(0, 1, 0), 1.0f);
		tmeshes[4].Rotate(tmeshes[0].GetCenter(), V3(0, 1, 0), 1.0f);
	}


#endif

}

void Scene::Render() {

	//Render(fb, ppc,t1);
	//return;

}


void Scene::Render(FrameBuffer *rfb, PPC *rppc,texture* t1, TMesh* tmesh) {

	rfb->SetBGR(0xFFFFFFFF);
	rfb->ClearZB();

	tmesh->InitTexture();
	tmesh->MapTextureCorners2TriangleVerts(0, 0);
	tmesh->MapTextureCorners2TriangleVerts(1, 1);

#if 0

	for (int tmi = 0; tmi < tmeshesN; tmi++) {
		if (!tmeshes[tmi].onFlag)
			continue;
		tmeshes[tmi].DrawWireFrame(rfb, rppc, 0xFF000000);
		tmesh->RenderTexture(rfb, rppc,t1);

	}
#endif
	tmesh->RenderTexture(rfb, rppc, t1);
	rfb->redraw();
	Fl::check();
	return;

}


void Scene::DBG() {

	{
		for (int i = 0; i < 36000; i++)
		{

			fb->SetBGR(0xFFFFFFFF);
			fb->ClearZB();
			tmeshes[0].Rotate(tmeshes[0].GetCenter(), V3(0, 1, 0), 1.0f);
			tmeshes[0].MapTextureCorners2TriangleVerts(0, 0);
			tmeshes[0].MapTextureCorners2TriangleVerts(1, 1);
			tmeshes[0].RenderTexture(fb, ppc, t1);
			fb->redraw();
			Fl::check();

		}
		return;

	}
}
*/

void Scene::NewButton() {
	cerr << "INFO: pressed New Button" << endl;
}