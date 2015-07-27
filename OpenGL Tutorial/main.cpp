#include <windows.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

//场景渲染函数
static void RenderSceneCB()
{
	//在每帧渲染前，用指定的颜色清除color buffer ，清除颜色为glClearColor指定的颜色
	glClear(GL_COLOR_BUFFER_BIT);

	//交换前后缓冲，把渲染内容在屏幕上显示出来
	glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
}


int main(int argc, char** argv)
{

	//glut初始化函数，该函数的参数使用应用程序的命令行参数。常用的命令行参数有 - sync, –gldebug等，详细参数信息请看：http://www.opengl.org/documentation/specs/glut/spec3/node10.html
	glutInit(&argc, argv);

	//GLUT_DOUBLE指定系统使用双缓冲，就是有2个color buffer，一个称作前缓冲，一个称作后缓冲，渲染输出的内容都先放在后缓冲中，再通过swapbuffer，交换前后缓冲，这样做，可以防止一帧图像渲染不全的问题。 GLUT_RGBA指定color buffer的格式。
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	//窗口大小及位置
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	//窗口标题
	glutCreateWindow("Tutorial 01");

	//设置回调函数，主要是指定主窗口的回调函数。这样，当main函数进入loop后，我们便可以通过回调函数和窗口交互，这类似于windows的事件机制。
	InitializeGlutCallbacks();

	//下面的代码用来得到渲染窗口的句柄，在opencl和opengl交互的程序中，可能用到渲染窗口句柄。注意：glutCreateWindow函数和glutGetWindow返回的并不是窗口句柄，而是一个整数，表示窗口id编号，所以要得到渲染窗口句柄，我们可以通过下面的win32函数实现，也可以修改freeglut的源代码，使glutGetWindow函数返回窗口句柄。
	const char *windowTitle = "This is my title";
	glutSetWindowTitle(windowTitle);
	HWND windowHandle = FindWindow(NULL, L"This is my title");
	HDC deviceContext = GetDC(windowHandle);
	HGLRC renderingContext = wglGetCurrentContext();
	cout << "render window handle:" << windowHandle << endl;

	//我们知道opengl的状态设置好以后，除非再次设置新的状态，否则会一直保持当前状态设置，比如设置背景渲染颜色为黑色后，除非我们再次调用glClearColor设置新的颜色，否则每帧渲染前，调用glClear函数都会把color buffer设置为黑色。

	//设置清除背景颜色为黑色，像素格式RGBA ，该函数指定用来清除color buffer的背景颜色
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//下面这个函数告诉glut开始内部循环，在循环的过程中，它会不断监听一些消息、事件，并根据这些消息事件来响应不同的回调函数。
	glutMainLoop();

	return 0;
}