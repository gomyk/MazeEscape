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
	void InitializeDrawing();  // variable initialization. �׸��⿡ �ʿ��� ������ �ʱ�ȭ �Ѵ�. 
	void OnTimer(UINT nIDEvent);
	void DrawScene();  // Set the camera WRT WC and display the scene(ī�޶� �����ϰ� scene ��ü�� �׸���) 
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
	int cameraPosition; // 1: at the pixed position, 2: ������, 3: �ڵ��� ���. 
	bool cameraJump;
	bool JumpSuccess;
	float v, g;
	GLfloat userYPos;	// Jump�� �ʿ��� �ڵ����� ��ġ
	GLfloat userXPos, userZPos; // �ڵ����� ���� ��ġ
	GLfloat saveUserX, saveUserZ;// �ڵ����� ���� ��ġ
	GLfloat userAngleSpeed; // �ڵ����� ���ӵ�, 
	GLfloat userOrientation;  // �ڵ��� orientation
	GLfloat userDirection, turnAngle; // �ڵ��� ���� 
	GLfloat userSize; //determine the size of the user. 1: standard, 3: 3 times lager
	GLfloat userMovingSpeed;


	// Variable Definition Start: SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSs
	int mazeLevel;	// Level
	time_t tStart;
	time_t tEnd;
	time_t tNow;
	int successTime;	// ���(�ð�)
	int limitTime;		// ���� �ð�
	bool isFinish;		// ���� �� ����

	int jumpChance;		// ���� ���� Ƚ��
};