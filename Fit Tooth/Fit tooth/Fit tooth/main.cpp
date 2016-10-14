#include <iostream>
#include "CreateWnd.h"

using namespace std;
CreateWnd *wnd = new CreateWnd( 500, 500, "HelloGLVideo" );

void OnClose()
{
	delete wnd;
}
void OnSize( int x, int y )
{
	if (x < 0 || y < 0)
	{
		x = 20;
		y = 20;
	}
	wnd->OnSize( x, y );
	
	//glViewport( 0, 0, x, y );
}
void OnRender()
{
	wnd->Render();
}

struct VV
{
	glm::vec3  pos;
	glm::vec3 color;
};
int main( int argc, char**argv )
{

	//VV a[3];
	//cout << sizeof( VV ) << endl;

	wnd->Initdata();
	glutCloseFunc( OnClose);
	glutDisplayFunc(OnRender );
	glutReshapeFunc( OnSize);
	glutMainLoop();
	return 0;
}
