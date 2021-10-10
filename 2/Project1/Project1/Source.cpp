#include <GL/freeglut.h>
#include<GL/gl.h>
#include<GL/GLU.h>
#include "GraphicObject.h"
#include <stdio.h>
#include <windows.h>
bool count_c = false;
double X1 = 0, Y1 = 0, Z1=0;
struct RGB{
	double R;
	double G;
	double B;
};
int count_t = 0;
RGB Colors[4] = { {0.0,0.0,0.0},{1,1,1},{0,0,1},{1,0,0} };
double c1=0, c2=0, c3 =0 ;
int i = 0;

double teapod_s = 1.0;
GLfloat M0[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 4,0,0,1 };
GLfloat M1[16] = { 1,0,0,0, 0,1,0,0, 0,0, 1,0, -4,0,0,1 };


const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];
// функция вызывается каждые 20 мс
void Simulation(int value)
{
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	
	if (count_c == true)
	{
		count_t += 20;
		if (count_t == 1000)
		{
			count_t = 0;
			i++;
			c1 = Colors[i].R;
			c2 = Colors[i].G;
			c3 = Colors[i].B;
			if (i == 4)
				i = 0;
		}
	}

	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, Simulation, 0);
	
};



// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 7.5, 0, 0, 0, 0, 1, 0);
	// выводим объект ‐ красный (1,0,0) чайник
	glColor3f(c1, c2, c3);
//	glutWireTeapot(teapod_s);

	graphicObjects[0].draw();
	graphicObjects[1].draw();
	graphicObjects[2].draw();
	graphicObjects[3].draw();
	//glColor3f(0, 0, 1);
 // glutWireTeacup(1.0);
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);

	switch (key)
	{
	case 'p':
		exit(0);
		break;
	case 'b':
		i++;
		c1 = Colors[i].R;
		c2 = Colors[i].G;
		c3 = Colors[i].B;
		glutPostRedisplay();
		if (i == 4)
			i = 0;
		break;
	case 'n':
		count_c = true;
		break;
	case 'm':
		count_c = false;
		count_t = 0;
		break;
	case 'h':
		teapod_s += 1.0;
		break;
	case 'j':
		teapod_s -= 1.0;
		break;
	}
};


void main(int argc,char **argv)
{
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(600, 600);
	// 3. создаем окно
	glutCreateWindow("laba1");

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutTimerFunc(20, Simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);
	
	graphicObjects[0].setPosition(-2.5f, 0.0f, 0.0f);
	graphicObjects[0].setAngle(0);
	graphicObjects[0].setСolor(1.0, 1.0, 1.0);
	
	graphicObjects[1].setPosition(0.0f, 0.0f, 2.5f);
	graphicObjects[1].setAngle(90);
	graphicObjects[1].setСolor(0.0, 0.0, 0.0);

	graphicObjects[2].setPosition(0.0f, 0.0f, -2.5f);
	graphicObjects[2].setAngle(-90);
	graphicObjects[2].setСolor(0.0, 0.0, 1.0);

	graphicObjects[3].setPosition(2.5f, 0.0f, 0.0f);
	graphicObjects[3].setAngle(180);
	graphicObjects[3].setСolor(1.0, 0.0, 0.0);
	// основной цикл обработки сообщений ОС
	glutMainLoop();
}