// 당구공 예제
#include <stdio.h>
#include "WIndows.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


int WindowXsize;//실행되는 윈도우의 사이즈
int WindowYsize;

float radius ; //공의 반지름

float C1xDelta; //초기 1번공(빨강)의 x좌표
float C1yDelta;//초기 1번공(빨강)의 y좌표
float C1CurXSpeed; //초기 1번공(빨강)의 x축 이동 속도
float C1CurYSpeed; //초기 1번공(빨강)의 y축 이동 속도

float C2xDelta; //초기 2번공(파랑)의 x좌표
float C2yDelta; //초기 2번공(파랑)의 y좌표
float C2CurXSpeed; //초기 2번공(파랑)의 x축 이동 속도
float C2CurYSpeed; //초기 2번공(파랑)의 y축 이동 속도

int CircleCollisionCount; //두 공이 충돌한 상황을 기록하는 count
int CirCollisionflag; //두 공이 충돌하는 순간 handler가 동작했는지 기록하는 변수

int C1WallCollision; // 1번 공이 벽에 부딫친 횟수를 카운트
int C1ColFlag; // 0은 부딫치지 않을 상태 1은 왼쪽벽에 충동, 2는 오른쪽벽에 충동, 3은 위쪽벽에 충동, 4는 아랫쪽 벽에 충돌.
float C1SpeedReducer; // 점점 줄어드는 속도를 기록하기 위한 변수

int C2WallCollision;
int C2ColFlag;
float C2SpeedReducer;

int WallCounter1Turnner; //1번공이 벽에 부딫치는 최대 횟수를 정의
int WallCounter2Turnner; //2번공이 벽에 부딫치는 최대 횟수를 정의

void SystemInitializer(float cir1speed) {//전역변수값을 초기화하며, 코드 재시작시 기본 값으로 돌리는 함수
	WindowXsize = 600;
	WindowYsize = 600;

	radius = 0.2; 

	C1xDelta = 0.0; 
	C1yDelta = -0.5;
	C1CurXSpeed = 0; 
	
	if (cir1speed == 0)
		C1CurYSpeed = 0;
	else
		C1CurYSpeed = cir1speed;

	C2xDelta = 0.0; 
	C2yDelta = 0.5; 
	C2CurXSpeed = 0; 
	C2CurYSpeed = 0; 

	CircleCollisionCount = 0;
	CirCollisionflag = 0; 

	C1WallCollision = 0; 
	C1ColFlag = 0; 
	C1SpeedReducer = 20; 

	C2WallCollision = 0;
	C2ColFlag = 0;
	C2SpeedReducer = 20;

	WallCounter1Turnner = 2;
	WallCounter2Turnner = 3;
}


void DrawCircle1(float cx, float cy, float r) //1번 빨간색 공을 그리는 함수
{
	float x1, y1, x2, y2;
	float angle;
	double radius = r;


	x1 = cx, y1 = cy;
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 0.01f; angle <= 2 * 3.14f + 0.2; angle += 0.2)
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

	for (angle = 0.01f; angle <= 2 * 3.14f + 0.2; angle += 0.2)
	{
		x2 = x1 - sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}

void MyDisplay() { //공 2개를 그리는 함수
	glClear(GL_COLOR_BUFFER_BIT);
	DrawCircle1(0 + C1xDelta, 0 + C1yDelta, radius);
	DrawCircle2(0 + C2xDelta, 0 + C2yDelta, radius);

	glutSwapBuffers();
}

void CircleIsCollide() //2공이 서로 충돌하는지 검사하는 함수
{

	float disX = C1xDelta - C2xDelta;
	float disY = C1yDelta - C2yDelta;
	float pointDis = sqrt(pow(disX, 2) + pow(disY, 2));

	if (pointDis <= 0.39)
	{
		CircleCollisionCount++;
		CirCollisionflag = 1;
	}
}


void Circle1IsCollideWall() { //1번공이 벽에 부딫치는지를 count하는 함수

	if (C1xDelta <= (-1.0) + radius)
	{
		C1WallCollision++;
		C1ColFlag = 1;
	}

	if (C1xDelta >= 1.0 - radius)
	{
		C1WallCollision++;
		C1ColFlag = 2;
	}

	if (C1yDelta >= (1.0 - radius))
	{
		C1WallCollision++;
		C1ColFlag = 3;
	}

	if (C1yDelta <= (-1.0) + radius)
	{
		C1WallCollision++;
		C1ColFlag = 4;
	}
}

void Circle2IsCollideWall() {//2번공이 벽에 부딫치는지를 count하는 함수

	if (C2xDelta <= ((-1.0) + radius))
	{
		C2WallCollision++;
		C2ColFlag = 1;
	}

	if (C2xDelta >= ((1.0) - radius))
	{
		C2WallCollision++;
		C2ColFlag = 2;
	}

	if (C2yDelta >= (1.0 - radius))
	{
		C2WallCollision++;
		C2ColFlag = 3;
	}

	if (C2yDelta <= ((-1.0) + radius))
	{
		C2WallCollision++;
		C2ColFlag = 4;
	}
}



void MyTimer(int Value) { //timer에 의해 call되는 함수로 대부분의 작업을 처리
	CircleIsCollide(); //각각의 공이 서로 또는 벽에 충동하는지를 check
	Circle1IsCollideWall();
	Circle2IsCollideWall();


	if (CircleCollisionCount == 4) //만일 서로 공이 2번 이상 충돌할 경우 stop
	{ //CircleCollisionCount거 2가 아닌 이유는 충돌시 공의 속도에 따라서 바로 방향을 바꾸더라도
	  // 공의 위치가 반지름의 영향을 받아서 충돌 후 이격이 1사이클의 timer로는 제대로 되지 않는 경우가 
      //있기에 4라는 값을 실험으로 얻어진 값으로, 최소 3번의 timer call이상 후 두 공이 지름 범위 이상으로 이격됨
		C1CurXSpeed = 0;
		C1CurYSpeed = 0;
		C2CurXSpeed = 0;
		C2CurYSpeed = 0;
	}

	if (CircleCollisionCount == 50)//두 공이 충돌 후 50틱 이후 재시작
	{
		SystemInitializer(0.01);
		WallCounter1Turnner = 10;
		WallCounter2Turnner = 10;
	}



	if ((CircleCollisionCount == 1) && (CirCollisionflag == 1))// 두 공이 처음으로 충돌한 경우
	{//각각의 공은 vector계산만으로 30,60도의 방향으로 진행
		float magC1 = sqrt(pow(C1CurXSpeed, 2) + pow(C1CurYSpeed, 2));//첫 충돌시 처음 공의 속도는 유지
		//공의 속도는 == 벡터의 크기
		C1CurXSpeed = magC1 * sqrt(3) / 2; //각각을 x,y방향의 vector성분으로 분리하여 속도를 결정
		C1CurYSpeed = magC1 * 1 / 2;
		C2CurXSpeed = magC1 * 1 / 2 * (-1);
		C2CurYSpeed = magC1 * sqrt(3) / 2; 

		CirCollisionflag = 0; 
	}

	if (C1ColFlag != 0)//Circle1의 벽과 충돌시 이동 경로를 변경
	{
		if (C1ColFlag == 1)
		{
			C1xDelta = -0.79; // 0.8이 아닌 0.79인 이유도 앞에서와 같이 속도에 따라 1틱(timer함수가 1번 call)으로는 
			// 충돌 코스에서 벗어나지 못하는 경우가 있기에, 확실히 벽과의 이격거리 확보를 위해 0,01의 마진을 둠
			C1CurXSpeed = C1CurXSpeed * (-0.8); //충돌시 마다 -값으로 방향을 반대하며, 0.8을 곱하여, 이전 속도의 0,8배씩으로 줄어듬
			C1ColFlag = 0;
		}
		else if (C1ColFlag == 2)
		{
			C1xDelta = 0.79;
			C1CurXSpeed = C1CurXSpeed * (-0.8);
			C1ColFlag = 0;
		}
		else if (C1ColFlag == 3)
		{
			C1yDelta = 0.79;
			C1CurYSpeed = C1CurYSpeed * (-0.8);
			C1ColFlag = 0;
		}
		else if (C1ColFlag == 4)
		{
			C1yDelta = -0.79;
			C1CurYSpeed = C1CurYSpeed * (-0.8);
			C1ColFlag = 0;
		}
	}


	if (C2ColFlag != 0)//Circle2의 벽과 충돌시 이동 경로를 변경	
	{
		if (C2ColFlag == 1)
		{
			C2xDelta = -0.79;
			C2CurXSpeed = C2CurXSpeed * (-0.8);
			C2ColFlag = 0;
		}
		else if (C2ColFlag == 2)
		{
			C2xDelta = 0.79;
			C2CurXSpeed = C2CurXSpeed * (-0.8);
			C2ColFlag = 0;
		}
		else if (C2ColFlag == 3)
		{
			C2yDelta = 0.79;
			C2CurYSpeed = C2CurYSpeed * (-0.8);
			C2ColFlag = 0;
		}
		else if (C2ColFlag == 4)
		{
			C2yDelta = -0.79;
			C2CurYSpeed = C2CurYSpeed * (-0.8);
			C2ColFlag = 0;
		}
	}

	if (C1WallCollision == WallCounter1Turnner) //1번 공이 허용된 수치 이상 벽에 부딫친 경우 stop
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

	if (C2WallCollision == WallCounter2Turnner)//2번 공이 허용된 수치 이상 벽에 부딫친 경우 stop 1초후 재시작
	{
		if (C2SpeedReducer != 0) {
			C2CurXSpeed = C2CurXSpeed * ((C2SpeedReducer - 1) / C2SpeedReducer);
			C2CurYSpeed = C2CurYSpeed * ((C2SpeedReducer - 1) / C2SpeedReducer);
			C2SpeedReducer--;
		}
		else {
			C2CurXSpeed = 0;
			C2CurYSpeed = 0;

			Sleep(1000);
			SystemInitializer(0.01);
		}
	}


		



	C1xDelta = C1xDelta + C1CurXSpeed;// 해당 공의 진행을 vector로 구현한 부분 
	C1yDelta = C1yDelta + C1CurYSpeed;// 속도는 vector로써 현재 공의 위치 + 다음 공과의 거리차 == 해당 공의 진행 속도 == vector 
	C2xDelta = C2xDelta + C2CurXSpeed;// 이 vector 형식의 속도변수만을 변경하며, 다음 공의 위치는 현재 위치에서 해당 틱(timer call)에서 결정된
	C2yDelta = C2yDelta + C2CurYSpeed;// 속도를 더해서 결정됨

	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1); //msec
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {// ketboard 인터럽트를 처리하는 부분 
	switch (KeyPressed) {
	case 'S'://대문자 S를 누르면, 2공이 2번 부딫처서 멈출때 까지 시뮬레이션을 진행
		C1CurYSpeed = 0.01;
		WallCounter1Turnner = 10;
		WallCounter2Turnner = 10;
		break;
	case 's': //소문자 s를 누르면 2공이 1번 충돌 후, 벽에 각각 2,3번 부딫치는 과정을 시뮬레이션
		C1CurYSpeed = 0.01; break;
	case 'R': //대문자 소문자 상관없이 R,r은 해당 시뮬레이션을 재실행
		SystemInitializer(0);
		break;
	case 'r':
		SystemInitializer(0);
		break;
	case 'Q'://Q,q,ESC는 실행종료
		quick_exit(0); break;
	case 'q':
		quick_exit(0); break;
	case 27:                //'esc' 키의 아스키 코드 값
		quick_exit(0); break;
	}
}

int main(int argc, char** argv) {
	SystemInitializer(0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WindowXsize, WindowYsize);//윈도우 크기값의 적용
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Computer Graphics 2019 Report 01 - 201500122");
	glClearColor(0.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay); //디스플레이 이벤트 핸들러 등록
	glutKeyboardFunc(MyKeyboard); //키보드 인터럽트 핸들러 등록
	glutTimerFunc(40, MyTimer, 1);//타이머 인터럽트 
	glutMainLoop();//해당과정을 loop
	return 0;
}
