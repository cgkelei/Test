#include <iostream>
#include "CreateWnd.h"
#include <opencv2/opencv.hpp>
using namespace std;
CreateWnd *wnd = new CreateWnd( 800, 600, "HelloGLVideo" );

void OnClose()
{
	wnd->OnClose();
	delete wnd;
}
void OnSize( int x, int y )
{
	wnd->OnSize(x, y);
	
}
void OnRender()
{
	wnd->Render();
}
void OnKey(unsigned char key, int x, int y)
{
	wnd->OnKeyDown(key, x, y);
}
void OnMouseDown(int button, int s, int x, int y)
{
	wnd->OnMouseDown(button, s, x, y);
}
void OnMouseMove(int x,int y)
{
	wnd->OnMouseMove(x, y);
}
struct VV
{
	glm::vec3  pos;
	glm::vec3 color;
};
void OnIdle()
{
	wnd->OnIdle();
}
int main( int argc, char**argv )
{
	wnd->Initdata();
	wnd->SetColor(120, 0, 0);
	glutCloseFunc(OnClose);
	glutReshapeFunc(OnSize);
	glutKeyboardFunc(OnKey);
	glutMouseFunc(OnMouseDown);
	glutMotionFunc(OnMouseMove);
	glutDisplayFunc(OnRender );
	glutIdleFunc(OnIdle);

	cv::Mat  img = cv::imread("image/Lenna.png");
	cv::imshow("LoadImage", img);
	


	glutMainLoop();
	cv::waitKey(59999);
	return 0;
}
