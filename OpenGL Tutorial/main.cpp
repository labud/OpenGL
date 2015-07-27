#include <windows.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

//������Ⱦ����
static void RenderSceneCB()
{
	//��ÿ֡��Ⱦǰ����ָ������ɫ���color buffer �������ɫΪglClearColorָ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);

	//����ǰ�󻺳壬����Ⱦ��������Ļ����ʾ����
	glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
}


int main(int argc, char** argv)
{

	//glut��ʼ���������ú����Ĳ���ʹ��Ӧ�ó���������в��������õ������в����� - sync, �Cgldebug�ȣ���ϸ������Ϣ�뿴��http://www.opengl.org/documentation/specs/glut/spec3/node10.html
	glutInit(&argc, argv);

	//GLUT_DOUBLEָ��ϵͳʹ��˫���壬������2��color buffer��һ������ǰ���壬һ�������󻺳壬��Ⱦ��������ݶ��ȷ��ں󻺳��У���ͨ��swapbuffer������ǰ�󻺳壬�����������Է�ֹһ֡ͼ����Ⱦ��ȫ�����⡣ GLUT_RGBAָ��color buffer�ĸ�ʽ��
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	//���ڴ�С��λ��
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	//���ڱ���
	glutCreateWindow("Tutorial 01");

	//���ûص���������Ҫ��ָ�������ڵĻص���������������main��������loop�����Ǳ����ͨ���ص������ʹ��ڽ�������������windows���¼����ơ�
	InitializeGlutCallbacks();

	//����Ĵ��������õ���Ⱦ���ڵľ������opencl��opengl�����ĳ����У������õ���Ⱦ���ھ����ע�⣺glutCreateWindow������glutGetWindow���صĲ����Ǵ��ھ��������һ����������ʾ����id��ţ�����Ҫ�õ���Ⱦ���ھ�������ǿ���ͨ�������win32����ʵ�֣�Ҳ�����޸�freeglut��Դ���룬ʹglutGetWindow�������ش��ھ����
	const char *windowTitle = "This is my title";
	glutSetWindowTitle(windowTitle);
	HWND windowHandle = FindWindow(NULL, L"This is my title");
	HDC deviceContext = GetDC(windowHandle);
	HGLRC renderingContext = wglGetCurrentContext();
	cout << "render window handle:" << windowHandle << endl;

	//����֪��opengl��״̬���ú��Ժ󣬳����ٴ������µ�״̬�������һֱ���ֵ�ǰ״̬���ã��������ñ�����Ⱦ��ɫΪ��ɫ�󣬳��������ٴε���glClearColor�����µ���ɫ������ÿ֡��Ⱦǰ������glClear���������color buffer����Ϊ��ɫ��

	//�������������ɫΪ��ɫ�����ظ�ʽRGBA ���ú���ָ���������color buffer�ı�����ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//���������������glut��ʼ�ڲ�ѭ������ѭ���Ĺ����У����᲻�ϼ���һЩ��Ϣ���¼�����������Щ��Ϣ�¼�����Ӧ��ͬ�Ļص�������
	glutMainLoop();

	return 0;
}