
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

float rightangle = 0; //각각 오른쪽.왼쪽 lower arm의 각도를 조절
float leftangle = 0; 
float upperAngle = 30;// 양 팔의 upper arm의 각도를 조절
int lowerFlag = 0; // lower arm의 각도가 증가하는지 감소하는지 판단하는 flag
int upperFlag = 0; // upper arm의 각도가 증가하는지 감소하는지 판단하는 flag

void Draw_Body() {
	glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(5.0, 5.0, 0.0);
		glVertex3f(5.0, -5.0, 0.0);
		glVertex3f(-5.0, -5.0, 0.0);
		glVertex3f(-5.0, 5.0, 0.0);
		glEnd();
}

void Draw_UpperArm() {
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glVertex3f(7.0, 3.0, 0.0);
	glVertex3f(7.0, 0.0, 0.0);
	glEnd();
}


void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 2, 3.0, 0.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void InitVisibility() {
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

void drawCylinder() {// upper, lower arm을 구현하기 위한 일반적인 길이의 실린더
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.2f, 0.2f, 3.0f, 32, 32);

}

void drawLCylinder() { //목과 몸을 표현하기 위한 길이가 좀 더 긴 실린더
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.2f, 0.2f, 7.0f, 32, 32);
}

void MyDrawBody() {
//	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, -10.0);
	gluLookAt(0.0, 0.4, 0.5, 0.0, -0.5, -1.0, 0.0, 1.0, 0.0);
	
	
	glutSolidSphere(1.2, 100, 400);//머리부분

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.f, 0.0f, 0.5f);
	drawLCylinder();
	glPopMatrix();//목,몸통

	
	glPushMatrix();
	glTranslatef(0.f, -1.8f, 0.0f);
	glRotatef(upperAngle, 0, 1, 0);
	drawCylinder();//오른쪽 upper arm

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 3.0f);
	glRotatef(leftangle, 0, 1, 1);
	drawCylinder();//오른쪽 lower arm
	glTranslatef(0.0f, 0.0f, 3.0f);
	glutSolidSphere(0.5, 100, 400);
	glPopMatrix();
	glPopMatrix();// 2번의 pop으로 좌표계를 초기값과 같게 만든다. 


	glPushMatrix();
	glTranslatef(0.f, -1.8f, 0.0f);
	glRotatef(-upperAngle, 0, 1, 0);
	drawCylinder();//왼쪽 upper arm

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 3.0f);
	glRotatef(-rightangle, 1, 1, 0);
	drawCylinder();// 왼쪽 lower arm
	glTranslatef(0.0f, 0.0f, 3.0f);
	glutSolidSphere(0.5, 100, 400);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers(); //double 버퍼 형식에서 버퍼의 변경
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 2.0);
}

void MyTimer(int Value) {

	if (lowerFlag == 0) { //lower arm의 각도를 control 하는 부분으로 flag == 0 일 때 각이 증가
		rightangle += 30; //좌.우 표시되는 lower arm은 서로 다른 각도로 회전
		leftangle += 45;
	}
	else {// flag == 1일때 각이 감소
		rightangle -= 30;
		leftangle -= 45;
	}
	if (rightangle >= 120) {// 최대 각인 120도에 도달시 증가하는 flag변수로 변경
		lowerFlag = 1;
	}	
	if (leftangle == 0)// 최소 각인 0도에 도달시 감소하는 flag변수로 변경
		lowerFlag = 0;


	if (upperFlag == 0) // upper arm의 각도를 조절하는 부분 동작은 lower arm과 동일
		upperAngle += 10;
	else
		upperAngle -= 10;

	if (upperAngle >= 90)
		upperFlag = 1;
	if (upperAngle <= 30)
		upperFlag = 0;
	

	glutPostRedisplay();
	glutTimerFunc(100, MyTimer, 1); //msec
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //애니메이션 구현에 double buffer를 사용
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("사람 움직임 애니메이션 - 201500122 고 병 현");
	glClearColor(0.5, 0.5, 0.5, 0.0);
	InitLight();
	InitVisibility();
	glMatrixMode(GL_PROJECTION);
	glutDisplayFunc(MyDrawBody);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(1000, MyTimer, 1);
	glutMainLoop();
	return 0;
}
