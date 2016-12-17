/* GLInterface.cpp: implementation of the CGLInterface class.
function: application.
It perfroms the following operations;
- Initialize the parameters necessary for the user simulation
- Intialized the parameters necessary for this appications
- Handles the messages such as OnKeyDown
- Release the variables allocated this applications
It make use of the following class objects
- CSeneModel : class for the scene modeling
- CUserModel	 :  class for the user modeling
/////////////////////////////////////////////////////////////////////*/

#include "stdafx.h"
#include "GLInterface.h"

float BLUE[3] = { 0.0,0.0,1.0 };  // Blue
float YELLOW[3] = { 1.0,1.0,0.0 };
float GREEN[3] = { 0.0,1.0,0.0 };
float RED[3] = { 1.0,0.0,0.0 };
float WHITE[3] = { 1.0,1.0,1.0 };  // Blue
float GRAY[3] = { 0.5,0.5,0.5 };  // Blue


								  //////////////////////////////////////////////////////////////////////
								  // Construction/Destruction
								  //////////////////////////////////////////////////////////////////////

CGLInterface::CGLInterface()
{
	m_hRC = NULL;
	m_pDC = NULL;

	InitializeDrawing(); // initialize all the variables necessary for this program.

}

CGLInterface::~CGLInterface()
{
	if (m_hRC || m_pDC)
		Release();    // release the allocated variables and handlers
}


// initialize handlers and variables.
int CGLInterface::Initialize(CDC *pDC)
{
	if (m_pDC || m_hRC) {
		::AfxMessageBox(L"Already initialized");
		return -1;
	}
	if (!(m_pDC = pDC)) {
		::AfxMessageBox(L"Fail to get device context");
		return -1;
	}

	if (!SetPixelFormat(NULL)) {	// Pixel format 설정
		::AfxMessageBox(L"SetupPixelFormat failed");
		return -1;
	}
	if (!(m_hRC = wglCreateContext(m_pDC->GetSafeHdc()))) {	// RC 획득
		::AfxMessageBox(L"wglCreateContext failed");
		return -1;
	}
	if (!wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC)) {// Current RC 설정
		::AfxMessageBox(L"wglMakeCurrent failed");
		return -1;
	}

	return 0;	// -1: Fail | 0: Well done
}


// release allocated variables and handlers
void CGLInterface::Release()
{
	if (!wglMakeCurrent(0, 0))
		::AfxMessageBox(L"wglMakeCurrent failed");

	if (m_hRC && !wglDeleteContext(m_hRC))
		::AfxMessageBox(L"wglDeleteContext filed");

	if (m_pDC)
		delete m_pDC;

	m_hRC = NULL;	// Must be NULL
	m_pDC = NULL;	// Must be NULL
}



BOOL CGLInterface::SetPixelFormat(PIXELFORMATDESCRIPTOR * pPFD)
{
	if (!pPFD) {
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
			PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
			PFD_MAIN_PLANE,	0, 0, 0, 0 };
		pPFD = &pfd;
	}

	int nPF = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), pPFD);
	if (!nPF) {
		::AfxMessageBox(L"ChoosePixelFormat failed");
		return FALSE;
	}

	if (!::SetPixelFormat(m_pDC->GetSafeHdc(), nPF, pPFD)) {
		::AfxMessageBox(L"SetPixelFormat failed");
		return FALSE;
	}

	return TRUE;


}

/*-----------------------------------------------------------------

Function: Set the followings
- the projection mode, Viewing Volume, viewport
-----------------------------------------------------------------*/

void CGLInterface::SetProjectView(int cx, int cy)
{
	// cx와 cy는 클라이언트 영역의 x축, y축 크기

	// TODO: Add your message handler code here
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*if( cx <= cy )
	glOrtho(-2.0, 2.0, -2.0*(GLfloat)cy/(GLfloat)cx,
	2.0*(GLfloat)cy/(GLfloat)cx, -10.0, 10.0);
	else
	glOrtho(-2.0*(GLfloat)cx/(GLfloat)cy,
	2.0*(GLfloat)cx/(GLfloat)cy, -2.0, 2.0, -10.0, 10.0);*/

	gluPerspective(65.0, (GLfloat)cx / (GLsizei)cy, 1.0, 10000.0);

	glViewport(0, 0, cx, cy);

	glEnable(GL_TEXTURE_2D);
	UserModel.LoadImgTexture();
	MazeModel.LoadImgTexture();
}


// ***************************************** Interface function   ******************************
void CGLInterface::Display(void * pData)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	// buffer clear color 설정
	glClear(GL_COLOR_BUFFER_BIT);	// 설정된 color로 버퍼를 clear
	DrawScene();
	glFlush();
}


// Function Implementation Start: SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS

/* -----------------------------------------------------------------------
Function: perform the followings
- set the quadric object for the head drawing.
- Initialize the animation variables
-----------------------------------------------------------------------*/

void CGLInterface::InitializeDrawing()  // 그리기에 필효한 변수를 초기화 한다. 
{
	g_Viewer[0] = 50.0f;
	g_Viewer[1] = 80.0f;
	g_Viewer[2] = 130.0f;

	g_Center[0] = 0.0f;
	g_Center[1] = 0.0f;
	g_Center[2] = 0.0f;	// 카메라의 초기 초점

	mazeLevel = 2;
	MazeModel.AllocMaze(mazeLevel);
	MazeModel.MakeItem();

	CString strText;
	strText.Format(_T("Level %d"), mazeLevel - 1);
	MessageBox(NULL, strText, _T("Random Maze Escape!"), MB_OK);

	isFinish = false;
	jumpChance = 0;
	limitTime = 60 * (mazeLevel - 1);

	cameraPosition = 1; // 1: at the pixed position, 2: 운전석, 3: 자동차 상단.
	cameraJump = false;
	JumpSuccess = false;
	v = 0.0, g = 9.8;
	userYPos = 0.0;

	float Unit = MazeModel.GetUnit();
	userXPos = -(2 * mazeLevel + 2)*6.0*Unit;
	userZPos = -(mazeLevel - 0.5)*6.0*Unit;			// 자동차의 현재 위치

	userAngleSpeed = 1;	// 자동차의 각속도, 
	userOrientation = 0;	// 자동차 orientation
	userDirection = STRAIGHT;
	turnAngle = 1;		// 핸들의 방향 
	userSize = 1;
	userMovingSpeed = 0.0;
}


void CGLInterface::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case VK_UP:
		//userDirection = STRAIGHT;
		next = true;
	
		userMovingSpeed = 1.5;
	
		break;
	case VK_DOWN:
		//userDirection = STRAIGHT;
		userMovingSpeed = -1;
		next = true;
		break;
	case VK_CONTROL:
		cameraPosition++;
		if (cameraPosition > 3)
			cameraPosition = 1;
		break;
	case VK_SPACE:
		if (!cameraJump && jumpChance > 0)
		{
			cameraJump = true;
			JumpSuccess = false;
		}
		break;
	case 'P': {
		mazeLevel++;
		MazeModel.delete_maze();	// 이전 Maze 메모리 할당 해제			

		MazeModel.AllocMaze(mazeLevel);
		MazeModel.MakeItem();

		isFinish = false;
		jumpChance = 0;
		limitTime = 60 * (mazeLevel - 1);

		cameraPosition = 1; // 1: at the pixed position, 2: 운전석, 3: 자동차 상단.
		cameraJump = false;
		JumpSuccess = false;
		v = 0.0, g = 9.8;
		userYPos = 0.0;

		float Unit = MazeModel.GetUnit();
		userXPos = -(2 * mazeLevel + 2)*6.0*Unit;
		userZPos = -(mazeLevel - 0.5)*6.0*Unit;			// 자동차의 현재 위치

		userAngleSpeed = 1;	// 자동차의 각속도, 
		userOrientation = 0;	// 자동차 orientation
		userDirection = STRAIGHT;
		turnAngle = 1;		// 핸들의 방향 
		userSize = 1;
		userMovingSpeed = 0.0;
		break;
	}
	case 'Z':
		CString strText;
		strText.Format(_T("Jump Change : %d회"), jumpChance);
		MessageBox(NULL, strText, _T("Jump Change"), MB_OK);
		break;
	
	

	}
}


/*==================================================================================
Function: Update the parameters necessary for the user simulation
Pre : userAngeSpeed and userDirection should be defined
Post: new user position, turnAngle, and user orientation are defined
====================================================================================*/
void CGLInterface::SetUserMovement()
{
	float Unit = MazeModel.GetUnit();
	//#define WHEELSIZE 0.2
#define TURNSPEED 1.3
#define MAZE_LIMIT (2*mazeLevel + 2)*6.0*Unit

	float theta;
	//float wheelSize = WHEELSIZE*userSize;

	// 이동 거리를 계산: 바퀴의 속도에 비례 
	// Calculate moving distance: Proportional to the speed of the wheel
	//if (userDirection != STRAIGHT)
	//	userMovingSpeed = 2.0f * PI * userAngleSpeed / 360.0f;

	// 바퀴의 좌우 회전 방향(각도)를 계산
	// Calculate side of the wheel rotation direction (angle)
	if (userDirection == RIGHT) {
		turnAngle -= TURNSPEED;
		if (turnAngle < -1.3) {
			turnAngle = -TURNSPEED;
		}
	}

	else if (userDirection == LEFT) {
		turnAngle += TURNSPEED;
		if (turnAngle > 1.3) {
			turnAngle = TURNSPEED;
		}
	}

	else {
		turnAngle = 0.0;
	}
	

	// 현재 자동차의 축적된 orientation 계산
	// Calculate the current orientation of the user accumulated
	userOrientation += turnAngle;
	if (userOrientation > 360.0f)
		userOrientation = 0.0f;
	else if (userOrientation < 0.0f)
		userOrientation = 360.0f;

	// 축적된 자동차의 위치 계산	
	// Calculate the accumulated position of user
	saveUserX = userXPos;
	saveUserZ = userZPos;
	if (userDirection != STRAIGHT)
	{

	}
	theta = -userOrientation*PI / 180.0;
	userXPos += userMovingSpeed * cos(theta);
	userZPos += userMovingSpeed * sin(theta);
	if (userMovingSpeed != 0) {
		UserModel.StartAnimation();
	}
	else {
		UserModel.StopAnimation();
	}
	// 점프
	float JumpHeight = 40.0;
	if (cameraJump)
	{
		if (!JumpSuccess)
		{
			if (userYPos < JumpHeight)
			{
				v += g * 0.1;
				userYPos += v * 0.1 + 0.5 * g * 0.1 * 0.1;
			}
			else
			{
				JumpSuccess = true;
				userYPos = JumpHeight;
			}
		}
		else
		{
			if (userYPos > 0.0)
			{
				v += -g * 0.1;
				userYPos += v * 0.1 - 0.5 * g * 0.1 * 0.1;
			}
			else
			{
				userYPos = 0.0;
				v = 0.0;
				cameraJump = false;
				jumpChance--;
			}
		}
	}

	if (userXPos > MAZE_LIMIT)
		userXPos = MAZE_LIMIT;
	else if (userXPos < -MAZE_LIMIT)
		userXPos = -MAZE_LIMIT;

	if (userZPos > MAZE_LIMIT)
		userZPos = MAZE_LIMIT;
	else if (userZPos < -MAZE_LIMIT)
		userZPos = -MAZE_LIMIT;

	if (MazeModel.IsCollision(userXPos, userZPos))	// 벽과 충돌할 경우
	{
		userXPos = saveUserX;
		userZPos = saveUserZ;
		next = false;
		UserModel.StopAnimation();
	}
	else											// 도로에 있는 경우
	{
		if (MazeModel.IsItem(userXPos, userZPos))		// Item 획득
		{
			jumpChance++;
			userDirection = STRAIGHT;
			userMovingSpeed = 0.0;
			UserModel.StopAnimation();
			next = false;
			MessageBox(NULL, _T("Jump Chance + 1 !!"), _T("WOW! Item!!"), MB_OK);
		}
		// 아무 처리 안함
	}

}


void CGLInterface::OnTimer(UINT nIDEvent)
{
	if (nIDEvent != 100)
		return;
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)) 
	{

	}
	else {
			  userMovingSpeed = 0.0;
	}

	int		gameStart = IDNO;
	if (GetAsyncKeyState(VK_RIGHT)) {
		userDirection = RIGHT;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		userDirection = LEFT;
	}
	else {
		userDirection = STRAIGHT;
	}
	// 시간 측정
	
	
	if (MazeModel.IsStart(userXPos, userZPos))
		tStart = time(NULL);        // 현재 시간 가져오기
	else if (MazeModel.IsEnd(userXPos, userZPos))
	{
		if (!isFinish)
		{
			tEnd = time(NULL);        // 현재 시간 가져오기
			successTime = difftime(tEnd, tStart);

			isFinish = true;
			userDirection = STRAIGHT;
			userMovingSpeed = 0.0;

			CString strText;
			UserModel.StopAnimation();
			next = false;
			strText.Format(_T("Records : %d분 %d초"), successTime / 60, successTime % 60);
			MessageBox(NULL, strText, _T("Escape Success!!"), MB_OK);


			CString strText2;
			strText2.Format(_T("Level %d Start"), mazeLevel);	// -1하지 않아서 다음 레벨 표시
			gameStart = MessageBox(NULL, strText2, _T("Next Stage"), MB_YESNO);
			if (gameStart == IDNO)
				exit(0);
			else
				mazeLevel++;
		}
	}

	tNow = time(NULL);        // 현재 시간 가져오기
	if (difftime(tNow, tStart) > limitTime && !isFinish)
	{
		isFinish = true;
		userDirection = STRAIGHT;
		userMovingSpeed = 0.0;

		CString strText;
		next = false;
		strText.Format(_T("Level %d Time limited : %d분 %d초"), mazeLevel - 1, limitTime / 60, limitTime % 60);
		MessageBox(NULL, strText, _T("Escape Fail!!"), MB_OK);

		CString strText2;
		strText2.Format(_T("Level %d Restart"), mazeLevel - 1);
		gameStart = MessageBox(NULL, strText2, _T("Current Stage Restart"), MB_YESNO);
		if (gameStart == IDNO)
			exit(0);
		else;
	}

	// Restart & Next Stage
	if (isFinish && gameStart == IDYES)
	{
		MazeModel.delete_maze();	// 이전 Maze 메모리 할당 해제			

		MazeModel.AllocMaze(mazeLevel);
		MazeModel.MakeItem();

		isFinish = false;
		jumpChance = 0;
		limitTime = 60 * (mazeLevel - 1);

		cameraPosition = 1; // 1: at the pixed position, 2: 운전석, 3: 자동차 상단.
		cameraJump = false;
		JumpSuccess = false;
		v = 0.0, g = 9.8;
		userYPos = 0.0;

		float Unit = MazeModel.GetUnit();
		userXPos = -(2 * mazeLevel + 2)*6.0*Unit;
		userZPos = -(mazeLevel - 0.5)*6.0*Unit;			// 자동차의 현재 위치

		userAngleSpeed = 1;	// 자동차의 각속도, 
		userOrientation = 0;	// 자동차 orientation
		userDirection = STRAIGHT;
		turnAngle = 1;		// 핸들의 방향 
		userSize = 1;
		userMovingSpeed = 0.0;
	}
	if (next) {
		UserModel.OnTimer();
	}
	SetUserMovement();
}


void CGLInterface::DrawScene()
{
	glEnable(GL_DEPTH_TEST);	// Enable hidden surface removal
	glMatrixMode(GL_MODELVIEW); // Modelview 행렬 스택 선택
	glLoadIdentity();			// 현재 변환 행렬을 단위 행렬로 대치

	float theta = -userOrientation*PI / 180.0;
	switch (cameraPosition)
	{
	case 1:	// Mage 전체
			/*---------------------------------
			k = 3 ~ mazeLevel, 10*∑(k + 2)

			ex)
			mazeLevel 3 = 50
			mazeLevel 4 = 50 + 60
			mazeLevel 5 = 50 + 60 + 70
			----------------------------------*/
		g_Viewer[0] = 0.0f;
		g_Viewer[1] = 600.0f + 10.0 * (mazeLevel*(mazeLevel + 1) / 2 - 3 + 2 * mazeLevel - 4);
		g_Viewer[2] = 0.0f;

		g_Center[0] = 0.0f;
		g_Center[1] = 0.0f;
		g_Center[2] = 0.0f;	// 카메라의 초기 초점

		g_Up[0] = 0.0f;
		g_Up[1] = 0.0f;
		g_Up[2] = -1.0f;
		break;
	case 2:	// 1인칭 시점
		g_Viewer[0] = userXPos;
		g_Viewer[1] = userYPos + 32.0f;
		g_Viewer[2] = userZPos;

		// 전진
		if (userMovingSpeed > 0)
		{
			g_Center[0] = g_Viewer[0] + userMovingSpeed * cos(theta);
			g_Center[1] = userYPos + 32.0f;
			g_Center[2] = g_Viewer[2] + userMovingSpeed * sin(theta);	// 카메라의 초기 초점
		}
		// 후진
		else if (userMovingSpeed < 0)
		{
			g_Viewer[0] = g_Viewer[0] + userMovingSpeed * cos(theta);
			g_Viewer[1] = userYPos + 32.0f;
			g_Viewer[2] = g_Viewer[2] + userMovingSpeed * sin(theta);	// 카메라의 초기 초점

			g_Center[0] = userXPos;
			g_Center[1] = userYPos + 32.0f;
			g_Center[2] = userZPos;
		}
		// 정지
		else
		{
			g_Center[0] = g_Viewer[0] + 0.01 * cos(theta);
			g_Center[1] = userYPos + 32.0f;
			g_Center[2] = g_Viewer[2] + 0.01 * sin(theta);	// 카메라의 초기 초점
		}

		g_Up[0] = 0.0f;
		g_Up[1] = 1.0f;
		g_Up[2] = 0.0f;
		break;
	case 3:	// 자동차 상단		
		g_Viewer[0] = userXPos - 100.0 * 0.5 * cos(theta);
		g_Viewer[1] = userYPos + 50.0f;
		g_Viewer[2] = userZPos - 100.0 * 0.5 * sin(theta);

		g_Center[0] = userXPos;
		g_Center[1] = userYPos + 20.0f;
		g_Center[2] = userZPos;	// 카메라의 초기 초점

		g_Up[0] = 0.0f;
		g_Up[1] = 1.0f;
		g_Up[2] = 0.0f;
		break;
	}
	// viewing 변환 정의

	gluLookAt(g_Viewer[0], g_Viewer[1], g_Viewer[2],
		g_Center[0], g_Center[1], g_Center[2],
		g_Up[0], g_Up[1], g_Up[2]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // RGB color display
	
							// Define light source 0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_AMBIENT,GL_LIGHT0);
	// 광원 위치 
	GLfloat position0[4] = { 1000, 1000, 1000, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	// 주변광
	GLfloat ambient0[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);

	// 난반사광
	GLfloat diffuse0[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);

	// 전반사광
	GLfloat specular0[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	glShadeModel(GL_SMOOTH);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// MazeModeling
	MazeModel.DefinePrimitiveListforScene(); // define and register primitives for scene modeling
											 //MazeModel.RenderScene();	// RenderScene 함수 호출	
	MazeModel.DrawMaze();
	MazeModel.DrawBackGround();

	// User modeling
	glPushMatrix();		// push current matrix to matrix stack.
	glTranslatef(userXPos, userYPos + 21.0, userZPos);	// move the position
	glRotatef(userOrientation, 0.0, 1.0, 0.0);	// Rotation about the Y-axis
	glPushMatrix();
	glScalef(userSize, userSize, userSize); // magnify the user
	UserModel.Display(turnAngle, userAngleSpeed); //CUserModel::Display(float handleTurn, float wheelTrun)
	glPopMatrix();
	glPopMatrix();	// Pop current matrix from matrix stack.

}

