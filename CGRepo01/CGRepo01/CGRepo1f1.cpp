// new 5.4
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include<stdio.h>

int WindowXsize = 600;//실행되는 윈도우의 사이즈
int WindowYsize = 600;

float radius = 0.2; //공의 반지름

float C1xDelta = 0.0; //초기 1번공(빨강)의 x좌표
float C1yDelta = -0.5;//초기 1번공(빨강)의 y좌표
float C1CurXSpeed = 0; //초기 1번공(빨강)의 x축 이동 속도
float C1CurYSpeed = 0.01; //초기 1번공(빨강)의 y축 이동 속도

float C2xDelta = 0.0; //초기 2번공(파랑)의 x좌표
float C2yDelta = 0.5; //초기 2번공(파랑)의 y좌표
float C2CurXSpeed = 0; //초기 2번공(파랑)의 x축 이동 속도
float C2CurYSpeed = 0; //초기 2번공(파랑)의 y축 이동 속도

int CircleCollisionCount = 0; //두 공이 충돌한 상황을 기록하는 count
int CirCollisionflag = 0; //두 공이 충돌하는 순간 handler가 동작했는지 기록하는 변수

int C1WallCollision = 0; // 1번 공이 벽에 부딫친 횟수를 카운트
int C1ColFlag = 0; // 0은 부딫치지 않을 상태 1은 왼쪽벽에 충동, 2는 오른쪽벽에 충동, 3은 위쪽벽에 충동, 4는 아랫쪽 벽에 충돌.
float C1SpeedReducer = 20; // 점점 줄어드는 속도를 기록하기 위한 변수

int C2WallCollision = 0;
int C2ColFlag = 0;
float C2SpeedReducer = 20;


void DrawCircle1(float cx, float cy, float r) //1번 빨간색 공을 그리는 함수
{
	float x1, y1, x2, y2;
	float angle;
	double radius = r;


	x1 = cx, y1 = cy;
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 0.01f; angle <= 2*3.14f + 0.2; angle += 0.2)
	{
		x2 = x1 - sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}

void DrawCircle2(float cx, float cy, float r)//2번 빨간색 공을 그리는 함수
{
	float x1, y1, x2, y2;
	float angle;
	double radius = r;


	x1 = cx, y1 = cy;
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 0.01f; angle <= 2*3.14f + 0.2; angle += 0.2)
	{
		x2 = x1 - sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	DrawCircle1(0 + C1xDelta, 0 + C1yDelta, radius);
	DrawCircle2(0 + C2xDelta, 0 + C2yDelta, radius);

	//glClear(GL_COLOR_BUFFER_BIT);
	//glBegin(GL_POLYGON);
	//glColor3f(0.0, 0.5, 0.8);
	//glVertex3f(-1.0 + Delta, -0.5, 0.0);
	//glVertex3f(0.0 + Delta, -0.5, 0.0);
	//glVertex3f(0.0 + Delta, 0.5, 0.0);
	//glVertex3f(-1.0 + Delta, 0.5, 0.0);
	//glEnd();


	glutSwapBuffers();
}

void CircleIsCollide()
{
	
	float disX = C1xDelta - C2xDelta;
	float disY = C1yDelta - C2yDelta;
	float pointDis = sqrt(pow(disX,2)+pow(disY,2));
	
	if(pointDis <= 0.39)
	{
		CircleCollisionCount++;
     	CirCollisionflag = 1;
	}
	//printf("disX : %f // disY : %f // pointDIs : %f\n", disX, disY, pointDis);
}

void printall()
{
	//printf("C1poX : %f // C1poY : %f \n", C1xDelta, C1yDelta);
	//printf("C1spdX : %f // C1spdY : %f \n", C1CurXSpeed, C1CurYSpeed);
	//printf("C1Colflag : %d\n", C1ColFlag);
	//printf("C1WallCollision : %d\n", C1WallCollision);

	printf("C2Colflag : %d\n", C2ColFlag);
	printf("C2WallCollision : %d\n", C2WallCollision);
	printf("C2poX : %f // C2poY : %f \n", C2xDelta, C2yDelta);
	printf("C2spdX : %f // C2spdY : %f \n", C2CurXSpeed, C2CurYSpeed);
	//printf("The Val of SpeedReducer : %f\n", ((C2SpeedReducer - 1) / C2SpeedReducer));
	printf("CirColCount : %d \n\n", CircleCollisionCount);

}

void Circle1IsCollideWall(){
	
	if(C1xDelta<=(-1.0)+ radius)
	{
		C1WallCollision++;
		C1ColFlag = 1;
	}

	if(C1xDelta>=1.0 - radius)
	{
		C1WallCollision++;
		C1ColFlag = 2;
	}

	if(C1yDelta >= (1.0 - radius))
	{	
		C1WallCollision++;
		C1ColFlag = 3;
	}

	if(C1yDelta<=(-1.0) + radius)
	{	
		C1WallCollision++;
		C1ColFlag = 4;
	}
}
	
void Circle2IsCollideWall(){

	if(C2xDelta <= ((-1.0) + radius))
	{
		C2WallCollision++;
		C2ColFlag = 1;
	}

	if(C2xDelta >= ((1.0) - radius))
	{
		C2WallCollision++;
		C2ColFlag = 2;
	}

	if(C2yDelta >= (1.0 - radius))
	{
		C2WallCollision++;
		C2ColFlag = 3;
	}

	if(C2yDelta <= ((-1.0) + radius))
	{
		C2WallCollision++;
		C2ColFlag = 4;
	}
}



void MyTimer(int Value) {
	CircleIsCollide();
	Circle1IsCollideWall();
	Circle2IsCollideWall();

	
	if (CircleCollisionCount > 4)
	{
		C1CurXSpeed = 0;
		C1CurYSpeed = 0;
		C2CurXSpeed = 0;
		C2CurYSpeed = 0;
	}


	
	if ((CircleCollisionCount == 1)&&(CirCollisionflag == 1))
	{
		float magC1 = sqrt(pow(C1CurXSpeed, 2) + pow(C1CurYSpeed, 2));

		C1CurXSpeed = magC1*sqrt(3)/2;
		C1CurYSpeed = magC1*1/2;
		C2CurXSpeed = magC1 *1/2*(-1);
		C2CurYSpeed = magC1 * sqrt(3)/2;
		
		CirCollisionflag = 0;
	}
	
	if(C1ColFlag != 0)//Circle1의 벽과 충돌시 이동 경로를 변경
	{
		if(C1ColFlag == 1)
		{
			C1xDelta = -0.79;
			C1CurXSpeed = C1CurXSpeed*(-0.8);
			C1ColFlag = 0;
		}
		else if(C1ColFlag == 2)
		{
			C1xDelta = 0.79;
			C1CurXSpeed = C1CurXSpeed*(-0.8);
			C1ColFlag = 0;
		}
		else if(C1ColFlag == 3)
		{
			C1yDelta = 0.79;
			C1CurYSpeed = C1CurYSpeed*(-0.8);
			C1ColFlag = 0;
		}
		else if(C1ColFlag == 4)
		{
			C1yDelta = -0.79;
			C1CurYSpeed = C1CurYSpeed * (-0.8);
			C1ColFlag = 0;
		}
	}
	
	
	if(C2ColFlag != 0)//Circle2의 벽과 충돌시 이동 경로를 변경	
	{
		if(C2ColFlag == 1)
		{
			C2xDelta = -0.79;
			C2CurXSpeed = C2CurXSpeed*(-0.8);	
			C2ColFlag = 0;
		}
		else if(C2ColFlag == 2)
		{
			C2xDelta = 0.79;
			C2CurXSpeed = C2CurXSpeed*(-0.8);	
			C2ColFlag = 0;
		}
		else if(C2ColFlag == 3)
		{
			C2yDelta = 0.79;
			C2CurYSpeed = C2CurYSpeed*(-0.8);
			C2ColFlag = 0;
		}
		else if(C2ColFlag == 4)
		{
			C2yDelta = -0.79;
			C2CurYSpeed = C2CurYSpeed*(-0.8);
			C2ColFlag = 0;	
		}
	}
		
	if(C1WallCollision == 10)
	{
		if (C1SpeedReducer != 0) {
			C1CurXSpeed = C1CurXSpeed * ((C1SpeedReducer - 1) / C1SpeedReducer);
			C1CurYSpeed = C1CurYSpeed * ((C1SpeedReducer - 1) / C1SpeedReducer);
			C1SpeedReducer--;
		}
		else {
			C1CurXSpeed = 0;
			C1CurYSpeed = 0;
		}
	}
	
	if(C2WallCollision == 10)
	{
		if (C2SpeedReducer != 0) {
			C2CurXSpeed = C2CurXSpeed * ((C2SpeedReducer - 1) / C2SpeedReducer);
			C2CurYSpeed = C2CurYSpeed * ((C2SpeedReducer - 1) / C2SpeedReducer);
			C2SpeedReducer--;
		}
		else {
			C2CurXSpeed = 0;
			C2CurYSpeed = 0;
		}
	}
	
	
	
	C1xDelta = C1xDelta + C1CurXSpeed;
	C1yDelta = C1yDelta + C1CurYSpeed;
	C2xDelta = C2xDelta + C2CurXSpeed;
	C2yDelta = C2yDelta + C2CurYSpeed;

	//printall();
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1); //msec
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WindowXsize, WindowYsize);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(0.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(40, MyTimer, 1);
	glutMainLoop();
	return 0;
}
