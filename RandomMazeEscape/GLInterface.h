// GLInterface.h: interface for the CGLInterface class.
/* function: application.
It perfroms the following operations;
- Initialize the parameters necessary for the user simulation
- Intialized the parameters necessary for this appications
- Handles the messages such as OnKeyDown
- Release the variables allocated this applications
It make use of the following class objects
- CSeneModel : class for the scene modeling
- CUserModel	 :  class for the user modeling
/////////////////////////////////////////////////////////////////////*/

#pragma once

#include "MazeModel.h"
#include "UserModel.h"

#include <math.h>
#include <time.h>

class CGLInterface
{
public:
	CGLInterface();
	virtual ~CGLInterface();
	int Initialize(CDC *pDC);
	void Release();				// release memory allocated for this application

	BOOL SetPixelFormat(PIXELFORMATDESCRIPTOR *pPFD = NULL);
	void SetProjectView(int cx, int cy);		// set the current viewport, Viewing volume, projection mode

	void Display(void * pData = NULL);			// display the application. This will be the interface between 
												// MFC and the application.


												// Function Definition Start: SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSs
public:
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void InitializeDrawing();  // variable initialization. 그리기에 필요한 변수를 초기화 한다. 
	void OnTimer(UINT nIDEvent);
	void DrawScene();  // Set the camera WRT WC and display the scene(카메라를 설정하고 scene 전체를 그린다) 
	void SetUserMovement(); // Update the parameters necessary for the user simulation 

							// Function Definition End: EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEe


private:
	HGLRC m_hRC;
	CDC * m_pDC;

	GLdouble g_Viewer[3];	// Camera position
	GLdouble g_Center[3];	// the point where the camera is looking at
	GLdouble g_Up[3];
	// data structures that holds the boundary information of streets and sidewalks
	bool next = false;
	CMazeModel MazeModel;		// create a maze model
	CUserModel UserModel; // user model
	int cameraPosition; // 1: at the pixed position, 2: 운전석, 3: 자동차 상단. 
	bool cameraJump;
	bool JumpSuccess;
	float v, g;
	GLfloat userYPos;	// Jump시 필요한 자동차의 위치
	GLfloat userXPos, userZPos; // 자동차의 현재 위치
	GLfloat saveUserX, saveUserZ;// 자동차의 직전 위치
	GLfloat userAngleSpeed; // 자동차의 각속도, 
	GLfloat userOrientation;  // 자동차 orientation
	GLfloat userDirection, turnAngle; // 핸들의 방향 
	GLfloat userSize; //determine the size of the user. 1: standard, 3: 3 times lager
	GLfloat userMovingSpeed;


	// Variable Definition Start: SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSs
	int mazeLevel;	// Level
	time_t tStart;
	time_t tEnd;
	time_t tNow;
	int successTime;	// 기록(시간)
	int limitTime;		// 제한 시간
	bool isFinish;		// 게임 끝 여부

	int jumpChance;		// 점프 가능 횟수
};