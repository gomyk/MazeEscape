// UserModel.cpp: implementation of the CUserModel class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "UserModel.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



/*====================================== CScene Class  ============================================
- Model a user and display it at the predefined position and orientation

==========================================================================================================*/

/*==================================================================================
Function: constructor
====================================================================================*/
CUserModel::CUserModel()
{
	curTireAngle = 0.f;	// 현재 바퀴의 회전 위치
	curRotSpeed = 5.f;

	// vertices
	m_vertices[0][0] = -1; m_vertices[0][1] = -1; m_vertices[0][2] = 1; // vertex 1
	m_vertices[1][0] = -1; m_vertices[1][1] = 1; m_vertices[1][2] = 1; // vertex 2
	m_vertices[2][0] = 1; m_vertices[2][1] = 1; m_vertices[2][2] = 1; // vertex 3
	m_vertices[3][0] = 1; m_vertices[3][1] = -1; m_vertices[3][2] = 1; // vertex 4
	m_vertices[4][0] = -1; m_vertices[4][1] = -1; m_vertices[4][2] = -1; // vertex 5
	m_vertices[5][0] = -1; m_vertices[5][1] = 1; m_vertices[5][2] = -1; // vertex 6
	m_vertices[6][0] = 1; m_vertices[6][1] = 1; m_vertices[6][2] = -1; // vertex 7
	m_vertices[7][0] = 1; m_vertices[7][1] = -1; m_vertices[7][2] = -1; // vertex 8

																		// normals
	m_normals[0][0] = 0; m_normals[0][1] = 0; m_normals[0][2] = 1; // (0, 3, 2, 1)
	m_normals[1][0] = 0; m_normals[1][1] = 1; m_normals[1][2] = 0; // (1, 2, 6, 5)
	m_normals[2][0] = 1; m_normals[2][1] = 0; m_normals[2][2] = 0; // (2, 3, 7, 6)
	m_normals[3][0] = 0; m_normals[3][1] = -1; m_normals[3][2] = 0; // (3, 0, 4, 7)
	m_normals[4][0] = 0; m_normals[4][1] = 0; m_normals[4][2] = -1; // (4, 5, 6, 7)
	m_normals[5][0] = -1; m_normals[5][1] = 0; m_normals[5][2] = 0; // (5, 4, 0, 1)

	InitializeDrawing(); // initialize all the variables necessary for this program.
}


/*==================================================================================
Function: destructor
====================================================================================*/
CUserModel::~CUserModel()
{
}

/* -----------------------------------------------------------------------
Function: perform the followings
- set the quadric object for the head drawing.
- Initialize the animation variables
-----------------------------------------------------------------------*/
void CUserModel::OnTimer()
{
	if (m_bAnimating) // check whether the animation is activated.
	{
		//check the end of the key frames 
		if (m_nSubFrameIdx > FRAMES_PER_INTV)
		{
			int nextKeyFrame = m_nKeyFrameIdx + 1; // set the next key frame index


												   // for the ball throw operation. Release the ball at the last key frame.
			if (nextKeyFrame == 7)
			{
			}

			// If the current index reach the end of the key frame, start from the begining.
			if (nextKeyFrame > 7)
			{
				nextKeyFrame = 0;
				
			}

			// Compute the variation between two intermediate frames.
			CalcDeltas(&keyStances[m_nKeyFrameIdx], &keyStances[nextKeyFrame], FRAMES_PER_INTV);

			// initialize the subframe number and key frame index
			m_nSubFrameIdx = 1;
			m_nKeyFrameIdx = nextKeyFrame;

		
			//?? update the current stance to generate the current intermediate frame.
		}

	}

}
void CUserModel::InitializeDrawing()  // 그리기에 필효한 변수를 초기화 한다. 
{

	//quadric object 생성
	p = gluNewQuadric();
	//set attributes of the quadric object. 속성 설정(GLU_POINT, GLU_LINE, GLU_FILL, GLU_SILHOUETTE)
	gluQuadricDrawStyle(p, GLU_LINE);

	//첫번째 키 프레임 부터.
	m_pitcherStance = keyStances[0];

	m_bAnimating = false;	// robot in stop position.

	m_nKeyFrameIdx = 0;     // current key frame index
	m_nSubFrameIdx = 31;	// next key frame. Generate intermediate frames(IF) between current and next key frame

	m_deltas;				// initialize variations between IFs

	m_deltas = keyStances[8];
}

/*==================================================================================
Function: Initialize the parameters
====================================================================================*/
void CUserModel::SetMovementParameters()
{
	curTireAngle = 0.f;
	curRotSpeed = 0.01f;

}



/*==================================================================================
Function: Display a user
Parameters:
handleTurn: steering angle defined by steering wheel
wheelTurn : amount of turn of the wheel.
====================================================================================*/
void CUserModel::Display(float handleTurn, float wheelTurn)
{
	if (handleTurn > 30)
		handleTurn = 30.0f;
	else if (handleTurn < -30)
		handleTurn = -30.0f;

	glPushMatrix();	// 행렬 스택에 현재의 행렬을 push
	DrawPitcher();

	// curTireAngle은 바퀴의 현재 회전각을 나타낸다.
	curTireAngle += wheelTurn;
	if (curTireAngle > 360.0)
		curTireAngle = 0.0;

	glPopMatrix();	// 현재 행렬을 그 행렬 스택에서 밖으로 꺼낸다
}


/* -------------------------------------------------------------------------------------------------------------
Function: Draw a body.
- Bend the upper body WRT the waist. The location of the waist in the body coordinate is (0, -4, 0)
- Face the front of the body.
- Draw the parts of the robot WRT the body.
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::StartAnimation() {
	m_bAnimating = true;
}
void CUserModel::StopAnimation() {
	m_bAnimating = false;
	m_pitcherStance = keyStances[0];

	m_bAnimating = false;	// robot in stop position.

	m_nKeyFrameIdx = 0;     // current key frame index
	m_nSubFrameIdx = 31;	// next key frame. Generate intermediate frames(IF) between current and next key frame

	m_deltas;				// initialize variations between IFs

	m_deltas = keyStances[8];
}
void CUserModel::Torso()
{
	GLfloat mat_ambient1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess1 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess1);

	glPushMatrix();
	// Define orientation of body in WC. WC에 대한 몸통의 방향을 결정한다. 
	glRotatef(m_pitcherStance.body_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.body_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.body_z, 0.0, 0.0, 1.0);

	// Rotate the body WRT the waist. 
	// The posision of the waist in the body coordinate is (0.0, -4.0, 0.0)
	// 허리를 중심으로 몸통의 굽혀진 정도를 결정한다.
	// 여기서 허리의 위치는 몸통 좌표계상에서(0.0, -4.0, 0.0)에 있다.
	glTranslatef(0.0, -4.0, 0.0);
	glRotatef(m_pitcherStance.waist_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.waist_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.waist_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 4.0, 0.0);

	glPushMatrix();
	//크기 (6.0, 8.0, 2.3) 의 cube를 그린다.
	glScalef(3.0, 4.0, 1.2);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(0);
	glPopMatrix();

	// draw each part of the robot. 각 신체 부위
	Head();
	LeftUpperArm();
	RightUpperArm();
	LeftUpperLeg();
	RightUpperLeg();
	glPopMatrix();
}

/* -------------------------------------------------------------------------------------------------------------
Function: Draw the head.
- Let the head face the direction defined by m_pithcherStand.neck
- The location of the head coordinate in the Body coordinate is (0. 7. 0)
- The location of the neck in the head coordinate is (0.0, -3, 0)
- The location of the left eye in the head coordinate is (-1.0, 1.0, -2.5)
- The location of the right eye in the head coordinate is (1.0, 1.0, -2.5)
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::Head()
{
	// The location of the head coordinate in the Body coordinate is (0. 7. 0)
	GLfloat mat_ambient2[4] = { 1.0f, 1.4f, 2.0f, 1.0f };
	GLfloat mat_diffuse2[4] = { 1.0f, 1.4f, 2.0f, 1.0f };
	GLfloat mat_specular2[4] = { 2.0f, 2.0f, 2.0f, 1.0f };
	GLfloat mat_shininess2 = 200.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess2);

	glPushMatrix();
	glTranslatef(0.0, 7.0, 0.0);
	// roate the head WRT the neck.
	// The location of the neck in the head coordinate is (0.0, -3, 0)
	glTranslatef(0.0, -3.0, 0.0);
	glRotatef(m_pitcherStance.neck_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.neck_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.neck_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 3.0, 0.0);

	// draw head
	glColor3f(1.0, 0.5, 0.5);
	glutSolidSphere(3.0, 10, 10);

	GLfloat mat_ambient3[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse3[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_specular3[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_shininess3 = 1.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess3);

	// left eye. The location of the left eye in the head coordinate is (-1.0, 1.0, -2.5)
	glPushMatrix();
	glTranslatef(-1.0, 1.0, -2.5);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();

	// right eye. The location of the right eye in the head coordinate is (1.0, 1.0, -2.5)
	glPushMatrix();
	glTranslatef(1.0, 1.0, -2.5);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();

	glPopMatrix();
}


/* -------------------------------------------------------------------------------------------------------------
Function: // draw left upper arm.
- The location of the left arm in the body coordinate is (-4.0, 2.0, 0.0)
- The location of the left upper arm joint in the upper arm joint coordinate is (1.0 2.0 0.0)
- Draw the left lower arm WRT the left upper arm.
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::LeftUpperArm()
{
	GLfloat mat_ambient4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess4 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);

	glPushMatrix();
	glTranslatef(-4.0, 2.0, 0.0);  // position the left upper arm in the body coordinate

								   // rotate left shoulder
	glTranslatef(1.0, 2.0, 0.0);
	glRotatef(m_pitcherStance.armL_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.armL_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.armL_z, 0.0, 0.0, 1.0);
	glTranslatef(-1.0, -2.0, 0.0);

	// Draw the upper arm by scaling a cube by (2, 4, 1.75). Use glutWireCube(). 
	glPushMatrix();
	glScalef(1.0, 2.0, 0.9);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(1);
	glPopMatrix();

	// Draw left lower arm 
	LeftLowerArm();
	glPopMatrix();
}


/* -------------------------------------------------------------------------------------------------------------
Function:  draw left lowr arm.
- The location of the left lower arm in the left upper arm coordinate is (0.0, -4.5, 0.0)
- The location of the left elbow in the left upper arm coordinate is (0.0 2.5 0.0)
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::LeftLowerArm()
{
	// position the lower left arm in the left upper arm coorindate. 
	GLfloat mat_ambient5[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse5[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular5[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess5 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse5);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular5);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess5);

	glTranslatef(0.0, -4.5, 0.0);

	// rotate left elbow
	glTranslatef(0.0, 2.5, 0.0);
	glRotatef(m_pitcherStance.elbowL_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.elbowL_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.elbowL_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -2.5, 0.0);

	// draw left lower arm by scaling a cube by (2, 5, 1.75). Use glutWireCube().
	glPushMatrix();
	glScalef(1.0, 2.5, 0.9);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(2);
	glPopMatrix();
}

/* -------------------------------------------------------------------------------------------------------------
Function: // draw right upper arm.
- The location of the right arm in the body coordinate is (4.0, 2.0, 0.0)
- The location of the riht upper arm joint in the upper arm joint coordinate is (-1.0 2.0 0.0)
- Draw the right lower arm WRT the right upper arm.
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::RightUpperArm()
{
	GLfloat mat_ambient4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess4 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);

	glPushMatrix();
	// position the right upper arm in the body coordinate
	glTranslatef(4.0, 2.0, 0.0);

	// rotate right shoulder
	glTranslatef(-1.0, 2.0, 0.0);
	glRotatef(m_pitcherStance.armR_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.armR_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.armR_z, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -2.0, 0.0);

	// Draw the upper arm by scaling a cube by (2, 4, 1.75). Use glutWireCube(). 
	glPushMatrix();
	glScalef(1.0, 2.0, 0.9);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(1);
	glPopMatrix();

	// draw right lower arm
	RightLowerArm();
	glPopMatrix();
}

/* -------------------------------------------------------------------------------------------------------------
Function:  draw right lower arm.
- The location of the right lower arm in the right upper arm coordinate is (0.0, -4.5, 0.0)
- The location of the right elbow in the right upper arm coordinate is (0.0 2.5 0.0)
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::RightLowerArm()
{
	// position the lower right arm in the right upper arm coorindate. 
	GLfloat mat_ambient5[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse5[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular5[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess5 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse5);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular5);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess5);

	glTranslatef(0.0, -4.5, 0.0);

	// rotate right elbow
	glTranslatef(0.0, 2.5, 0.0);
	glRotatef(m_pitcherStance.elbowR_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.elbowR_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.elbowR_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -2.5, 0.0);

	// Draw the lower arm by scaling a cube by (2, 5, 1.75). Use glutWireCube().
	glPushMatrix();
	glScalef(1.0, 2.5, 0.9);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(2);
	glPopMatrix();
}


/* -------------------------------------------------------------------------------------------------------------
Function:  draw left upper leg(LUL).
- The location of LUL in the body coordinate is (-2.0, -7.0, 0.0)
- The location of the upper joint of LUL in LUL coordinate is 0.0, 3.0, 0.0)
- Draw the left lower leg.
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::LeftUpperLeg()
{
	GLfloat mat_ambient6[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse6[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular6[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess6 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient6);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse6);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular6);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess6);

	glPushMatrix();
	// potision the LUL in the body coordinate. The location is (-2.0, -7.0, 0.0)
	glTranslatef(-2.0, -7.0, 0.0);

	// rotate the LUL WRT the body. the location of the joint is (0.0, 3.0, 0.0)
	glTranslatef(0.0, 3.0, 0.0);
	glRotatef(m_pitcherStance.legL_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.legL_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.legL_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -3.0, 0.0);

	// draw LUL by scaling a cube by (2, 6, 2). Use glutWireCube()
	glPushMatrix();
	glScalef(1.0, 3.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(3);
	glPopMatrix();

	// draw left lower leg
	LeftLowerLeg();
	glPopMatrix();
}



/* -------------------------------------------------------------------------------------------------------------
Function:  draw left lower leg(LLL).
- The location of LLL in the LUL coordinate is (0.0, -5.5, 0.0)
- The location of the upper joint of LLL in LLL coordinate is (0.0, 2.5, 0.0)
- Draw the left lower leg.
- Draw a left foot(LF) and ankle (발과 발목)
- location of the foot in the LLL coordinate is (0.0, -3.0, 0.0)
- location of the foot joint (ankle) in the LF coordinate is (0.0, 0.5, 0.0)
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::LeftLowerLeg()
{
	// position the LLL in the LUL coordinate. the position is (0.0, -5.5, 0.0)
	GLfloat mat_ambient7[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse7[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular7[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess7 = 10.0;

	// 폴리곤의 앞면의 재질을 설정
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient7);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse7);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular7);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess7);

	glTranslatef(0.0, -5.5, 0.0);

	// rotate left knee. the joint is located at (0.0, 2.5, 0.0) in the LLL coordinate 
	glTranslatef(0.0, 2.5, 0.0);
	glRotatef(m_pitcherStance.kneeL_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.kneeL_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.kneeL_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -2.5, 0.0);

	//draw left lower leg by scaling a cube by (2, 5, 2). Use glutWireCube()
	glPushMatrix();
	glScalef(1.0, 2.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(4);
	glPopMatrix();

	// position the LF in the LLL coordinate
	GLfloat mat_ambient8[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse8[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular8[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess8 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient8);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse8);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular8);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess8);

	glTranslatef(0.0, -3.0, 0.0);

	// rotate left ankle. The ankle position in LF coordinate is (0.0, 0.5, 0.0)
	glTranslatef(0.0, 0.5, 0.0);
	glRotatef(m_pitcherStance.ankleL_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.ankleL_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.ankleL_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.5, 0.0);

	// draw a LF scaling a cube by (2, 1, 4). Use glutWireCube()
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1.0);
	glScalef(1.0, 0.5, 2.0);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(5);
	glPopMatrix();
}

/* -------------------------------------------------------------------------------------------------------------
Function:  draw right upper leg(RUL).
- The location of RUL in the body coordinate is (2.0, -7.0, 0.0)
- The location of the upper joint of RUL in RUL coordinate is 0.0, 3.0, 0.0)
- Draw the right lower leg.
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::RightUpperLeg()
{
	GLfloat mat_ambient6[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse6[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular6[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess6 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient6);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse6);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular6);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess6);

	glPushMatrix();
	// potision the RUL in the body coordinate. The location is (2.0, -7.0, 0.0)
	glTranslatef(2.0, -7.0, 0.0);

	// rotate the RUL WRT the body. the location of the joint is (0.0, 3.0, 0.0)
	glTranslatef(0.0, 3.0, 0.0);
	glRotatef(m_pitcherStance.legR_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.legR_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.legR_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -3.0, 0.0);

	// draw RUL by scaling a cube by (2, 6, 2). Use glutWireCube()
	glPushMatrix();
	glScalef(1.0, 3.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(3);
	glPopMatrix();

	RightLowerLeg();
	glPopMatrix();
}

/* -------------------------------------------------------------------------------------------------------------
Function:  draw right lower leg(RLL).
- The location of RLL in the RUL coordinate is (0.0, -5.5, 0.0)
- The location of the upper joint of RLL in RLL coordinate is (0.0, 2.5, 0.0)
- Draw the right lower leg.
- Draw a right foot(RF) and ankle (발과 발목)
- location of the foot in the RLL coordinate is (0.0, -3.0, 0.0)
- location of the foot joint (ankle) in the RF coordinate is (0.0, 0.5, 0.0)
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::RightLowerLeg()
{
	// position the RLL in the RUL coordinate. the position is (0.0, -5.5, 0.0)
	GLfloat mat_ambient7[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse7[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular7[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess7 = 10.0;

	// 폴리곤의 앞면의 재질을 설정
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient7);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse7);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular7);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess7);

	glTranslatef(0.0, -5.5, 0.0);

	// rotate right knee. the joint is located at (0.0, 2.5, 0.0) in the LLL coordinate 
	glTranslatef(0.0, 2.5, 0.0);
	glRotatef(m_pitcherStance.kneeR_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.kneeR_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.kneeR_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -2.5, 0.0);

	//draw right lower leg by scaling a cube by (2, 5, 2). Use glutWireCube()
	glPushMatrix();
	glScalef(1.0, 2.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(4);
	glPopMatrix();

	// position the RF in the RLL coordinate
	GLfloat mat_ambient8[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse8[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular8[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess8 = 10.0;
	// 폴리곤의 앞면의 재질을 설정 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient8);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse8);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular8);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess8);

	glTranslatef(0.0, -3.0, 0.0);
	// rotate right ankle. The ankle position in RF coordinate is (0.0, 0.5, 0.0)
	glTranslatef(0.0, 0.5, 0.0);
	glRotatef(m_pitcherStance.ankleR_x, 1.0, 0.0, 0.0);
	glRotatef(m_pitcherStance.ankleR_y, 0.0, 1.0, 0.0);
	glRotatef(m_pitcherStance.ankleR_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.5, 0.0);

	// draw a RF scaling a cube by (2, 1, 4). Use glutWireCube()
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1.0);
	glScalef(1.0, 0.5, 2.0);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(5);
	glPopMatrix();
}

/* -------------------------------------------------------------------------------------------------------------
Function:  Compute the variation between two intermediate frames
- stance 1 : current key frame
- stance 2 : next key frame
- n : the number of intermediate frames between those two key frames
- m_deltas : the structure variables holding the variance.
-------------------------------------------------------------------------------------------------------------*/
void CUserModel::CalcDeltas(const Stance *stance1, const Stance *stance2, int n)
{
	// Divide the difference between two key frames by the number of intermediate frames.
	//?? 중간 프레임 간 변화량을 계산하라.
	m_deltas.body_x = (stance2->body_x - stance1->body_x) / n;
	m_deltas.body_y = (stance2->body_y - stance1->body_y) / n;
	m_deltas.body_z = (stance2->body_z - stance1->body_z) / n;

	m_deltas.neck_x = (stance2->neck_x - stance1->neck_x) / n;
	m_deltas.neck_y = (stance2->neck_y - stance1->neck_y) / n;
	m_deltas.neck_z = (stance2->neck_z - stance1->neck_z) / n;

	m_deltas.armL_x = (stance2->armL_x - stance1->armL_x) / n;
	m_deltas.armL_y = (stance2->armL_y - stance1->armL_y) / n;
	m_deltas.armL_z = (stance2->armL_z - stance1->armL_z) / n;

	m_deltas.armR_x = (stance2->armR_x - stance1->armR_x) / n;
	m_deltas.armR_y = (stance2->armR_y - stance1->armR_y) / n;
	m_deltas.armR_z = (stance2->armR_z - stance1->armR_z) / n;

	m_deltas.elbowL_x = (stance2->elbowL_x - stance1->elbowL_x) / n;
	m_deltas.elbowL_y = (stance2->elbowL_y - stance1->elbowL_y) / n;
	m_deltas.elbowL_z = (stance2->elbowL_z - stance1->elbowL_z) / n;

	m_deltas.elbowR_x = (stance2->elbowR_x - stance1->elbowR_x) / n;
	m_deltas.elbowR_y = (stance2->elbowR_y - stance1->elbowR_y) / n;
	m_deltas.elbowR_z = (stance2->elbowR_z - stance1->elbowR_z) / n;

	m_deltas.waist_x = (stance2->waist_x - stance1->waist_x) / n;
	m_deltas.waist_y = (stance2->waist_y - stance1->waist_y) / n;
	m_deltas.waist_z = (stance2->waist_z - stance1->waist_z) / n;

	m_deltas.legL_x = (stance2->legL_x - stance1->legL_x) / n;
	m_deltas.legL_y = (stance2->legL_y - stance1->legL_y) / n;
	m_deltas.legL_z = (stance2->legL_z - stance1->legL_z) / n;

	m_deltas.legR_x = (stance2->legR_x - stance1->legR_x) / n;
	m_deltas.legR_y = (stance2->legR_y - stance1->legR_y) / n;
	m_deltas.legR_z = (stance2->legR_z - stance1->legR_z) / n;

	m_deltas.kneeL_x = (stance2->kneeL_x - stance1->kneeL_x) / n;
	m_deltas.kneeL_y = (stance2->kneeL_y - stance1->kneeL_y) / n;
	m_deltas.kneeL_z = (stance2->kneeL_z - stance1->kneeL_z) / n;

	m_deltas.kneeR_x = (stance2->kneeR_x - stance1->kneeR_x) / n;
	m_deltas.kneeR_y = (stance2->kneeR_y - stance1->kneeR_y) / n;
	m_deltas.kneeR_z = (stance2->kneeR_z - stance1->kneeR_z) / n;

	m_deltas.ankleL_x = (stance2->ankleL_x - stance1->ankleL_x) / n;
	m_deltas.ankleL_y = (stance2->ankleL_y - stance1->ankleL_y) / n;
	m_deltas.ankleL_z = (stance2->ankleL_z - stance1->ankleL_z) / n;

	m_deltas.ankleR_x = (stance2->ankleR_x - stance1->ankleR_x) / n;
	m_deltas.ankleR_y = (stance2->ankleR_y - stance1->ankleR_y) / n;
	m_deltas.ankleR_z = (stance2->ankleR_z - stance1->ankleR_z) / n;

}

void CUserModel::DrawPitcher()
{
	m_pitcherStance.body_x += m_deltas.body_x;
	m_pitcherStance.body_y += m_deltas.body_y;
	m_pitcherStance.body_z += m_deltas.body_z;

	m_pitcherStance.neck_x += m_deltas.neck_x;
	m_pitcherStance.neck_y += m_deltas.neck_y;
	m_pitcherStance.neck_z += m_deltas.neck_z;

	m_pitcherStance.armL_x += m_deltas.armL_x;
	m_pitcherStance.armL_y += m_deltas.armL_y;
	m_pitcherStance.armL_z += m_deltas.armL_z;

	m_pitcherStance.armR_x += m_deltas.armR_x;
	m_pitcherStance.armR_y += m_deltas.armR_y;
	m_pitcherStance.armR_z += m_deltas.armR_z;

	m_pitcherStance.elbowL_x += m_deltas.elbowL_x;
	m_pitcherStance.elbowL_y += m_deltas.elbowL_y;
	m_pitcherStance.elbowL_z += m_deltas.elbowL_z;

	m_pitcherStance.elbowR_x += m_deltas.elbowR_x;
	m_pitcherStance.elbowR_y += m_deltas.elbowR_y;
	m_pitcherStance.elbowR_z += m_deltas.elbowR_z;

	m_pitcherStance.waist_x += m_deltas.waist_x;
	m_pitcherStance.waist_y += m_deltas.waist_y;
	m_pitcherStance.waist_z += m_deltas.waist_z;

	m_pitcherStance.legL_x += m_deltas.legL_x;
	m_pitcherStance.legL_y += m_deltas.legL_y;
	m_pitcherStance.legL_z += m_deltas.legL_z;

	m_pitcherStance.legR_x += m_deltas.legR_x;
	m_pitcherStance.legR_y += m_deltas.legR_y;
	m_pitcherStance.legR_z += m_deltas.legR_z;

	m_pitcherStance.kneeL_x += m_deltas.kneeL_x;
	m_pitcherStance.kneeL_y += m_deltas.kneeL_y;
	m_pitcherStance.kneeL_z += m_deltas.kneeL_z;

	m_pitcherStance.kneeR_x += m_deltas.kneeR_x;
	m_pitcherStance.kneeR_y += m_deltas.kneeR_y;
	m_pitcherStance.kneeR_z += m_deltas.kneeR_z;

	m_pitcherStance.ankleL_x += m_deltas.ankleL_x;
	m_pitcherStance.ankleL_y += m_deltas.ankleL_y;
	m_pitcherStance.ankleL_z += m_deltas.ankleL_z;

	m_pitcherStance.ankleR_x += m_deltas.ankleR_x;
	m_pitcherStance.ankleR_y += m_deltas.ankleR_y;
	m_pitcherStance.ankleR_z += m_deltas.ankleR_z;

	m_nSubFrameIdx++;
	glPushMatrix();
	Torso();
	glPopMatrix();

}

void CUserModel::LoadImgTexture()
{
	m_texRec[0] = auxDIBImageLoad(L"Torso.bmp");	// 몸
	m_texRec[1] = auxDIBImageLoad(L"UpperArm.bmp"); // 팔 위쪽
	m_texRec[2] = auxDIBImageLoad(L"LowerArm.bmp"); // 팔 아래쪽
	m_texRec[3] = auxDIBImageLoad(L"UpperLeg.bmp"); // 다리 위쪽
	m_texRec[4] = auxDIBImageLoad(L"LowerLeg.bmp"); // 다리 아래쪽
	m_texRec[5] = auxDIBImageLoad(L"Ankle.bmp");	// 신발

	glGenTextures(6, &m_texID[0]); // Generates texture names

	for (register int i = 0; i<6; i++) {
		// The creation of a named texture that is bound to a texture target
		glBindTexture(GL_TEXTURE_2D, m_texID[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			m_texRec[i]->sizeX, m_texRec[i]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, m_texRec[i]->data);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// 다음을 처리하지 않을 경우 memory leak 발생
		delete[] m_texRec[i]->data;
		delete m_texRec[i];
	}

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// Step 3: Texture mapping을 위한 텍스쳐 좌표 설정
void CUserModel::DrawQuad(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);
	glNormal3fv(m_normals[a]);

	//glColor3fv(m_colors[a]);
	// set the current texture coordinates
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(m_vertices[a]);

	//glColor3fv(m_colors[b]);
	// set the current texture coordinates
	glTexCoord2f(1.0, 0.0);
	glVertex3fv(m_vertices[b]);

	//glColor3fv(m_colors[c]);
	// set the current texture coordinates
	glTexCoord2f(1.0, 1.0);
	glVertex3fv(m_vertices[c]);

	//glColor3fv(m_colors[d]);
	// set the current texture coordinates
	glTexCoord2f(0.0, 1.0);
	glVertex3fv(m_vertices[d]);
	glEnd();
}

void CUserModel::TextureCube(int texID)
{
	//LoadImgTexture();	
	// 각면에 각기 다른 texture를 mapping 한다.

	// 뒤
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(3, 2, 1, 0);
	// 위
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(1, 2, 6, 5);
	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(7, 6, 2, 3);
	// 아래
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(3, 0, 4, 7);
	// 앞
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(4, 5, 6, 7);
	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(0, 1, 5, 4);
}
