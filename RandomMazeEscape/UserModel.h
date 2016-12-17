#pragma once
#pragma once

#pragma comment (lib, "opengl/lib/glut32.lib")
#pragma comment (lib, "opengl/lib/glaux.lib")
#pragma comment (lib, "opengl32.lib")

#include "opengl/include/glut.h"
#include "opengl/include/GLAUX.H"
#include <gl/GL.h>
#include <gl/GLU.h>

#define	PI  3.14159265359f
#define RIGHT 1
#define LEFT 2
#define STRAIGHT 0
extern GLfloat BLUE[3];  // Blue
extern GLfloat YELLOW[3];
extern GLfloat GREEN[3];
extern GLfloat RED[3];
extern GLfloat WHITE[3];  // Blue
extern GLfloat GRAY[3];  // Blue

						 // Robot parameters
typedef struct {
	GLfloat body_x, body_y, body_z;		// Facing direction of body
	GLfloat neck_x, neck_y, neck_z;		// Facing direction of neck
	GLfloat armL_x, armL_y, armL_z;		// Orientation of left arm with respect to (WRT) body
	GLfloat armR_x, armR_y, armR_z;		// orientation of right arm WRT body
	GLfloat elbowL_x, elbowL_y, elbowL_z;	// orientation of lower left arm WRT upper left arm
	GLfloat elbowR_x, elbowR_y, elbowR_z;	// orientation of lower right arm WRT upper right arm
	GLfloat waist_x, waist_y, waist_z;	// orientation of waist
	GLfloat legL_x, legL_y, legL_z;		// orientation of left leg WRT body
	GLfloat legR_x, legR_y, legR_z;		// orientation of right leg WRT body
	GLfloat kneeL_x, kneeL_y, kneeL_z;	// orientation of lower left leg WRP upper left leg
	GLfloat kneeR_x, kneeR_y, kneeR_z;	// orientation of lower right leg WRP upper Right leg
	GLfloat ankleL_x, ankleL_y, ankleL_z;	// orientation of left ankle(발목)
	GLfloat ankleR_x, ankleR_y, ankleR_z;	// orientation of right ankle
} Stance;

// variables necessary for animation
const int FRAMES_PER_INTV = 30;				// number of frames between two key frames(두 키 프레임 사이의 프레임 수)

											// Definition of Key frames. array keyStances[] holds information for 7 key frames
											// 배열 keyStances[]에 7개의 키프레임 정보가 저장된다. 
const Stance keyStances[9] =
{
	// KEY FRAME 1
	{ 0.0, -90.0, 0.0, // body
	0.0, 0.0, 0.0, // neck
	0.0, 0.0, 0.0, // left shoulder
	0.0, 0.0, 0.0, // right shoulder
	0.0, 0.0, 0.0, // left elbow
	0.0, 0.0, 0.0, // right elbow
	0.0, 0.0, 0.0, // waist
	0.0, 0.0, 0.0, // left hip
	0.0, 0.0, 0.0, // right hip
	0.0, 0.0, 0.0, // left knee
	0.0, 0.0, 0.0, // right knee
	0.0, 0.0, 0.0, // left ankle
	0.0, 0.0, 0.0 },// right ankle

					// KEY FRAME 2
	{ 0.0, -90.0, 0.0, // body
	0.0, 0.0, 0.0, // neck
	50.0, 0.0, 0.0, // left shoulder
	-50.0, 0.0, 0.0, // right shoulder
	0.0, 0.0, 0.0, // left elbow
	0.0, 0.0, 0.0, // right elbow
	0.0, 0.0, 0.0, // waist
	-50.0, 0.0, 0.0, // left hip
	50.0, 0.0, 0.0, // right hip
	0.0, 0.0, 0.0, // left knee
	0.0, 0.0, 0.0, // right knee
	0.0, 0.0, 0.0, // left ankle
	0.0, 0.0, 0.0 },// right ankle

					// KEY FRAME 3
	{ 0.0, -90.0, 0.0, // body
	0.0, 0.0, 0.0, // neck
	0.0, 0.0, 0.0, // left shoulder
	0.0, 0.0, 0.0, // right shoulder
	0.0, 0.0, 0.0, // left elbow
	0.0, 0.0, 0.0, // right elbow
	0.0, 0.0, 0.0, // waist
	0.0, 0.0, 0.0, // left hip
	0.0, 0.0, 0.0, // right hip
	0.0, 0.0, 0.0, // left knee
	0.0, 0.0, 0.0, // right knee
	0.0, 0.0, 0.0, // left ankle
	0.0, 0.0, 0.0 },// right ankle

					// KEY FRAME 4
	{ 0.0,-90.0, 0.0, // body
	0.0, 0.0, 0.0, // neck
	-50.0, 0.0, 0.0, // left shoulder
	50.0, 0.0, 0.0, // right shoulder
	0.0, 0.0, 0.0, // left elbow
	0.0, 0.0, 0.0, // right elbow
	0.0, 0.0, 0.0, // waist
	50.0, 0.0, 0.0, // left hip
	-50.0, 0.0, 0.0, // right hip
	0.0, 0.0, 0.0, // left knee
	0.0, 0.0, 0.0, // right knee
	0.0, 0.0, 0.0, // left ankle
	0.0, 0.0, 0.0 },// right ankle

					// KEY FRAME 5
	{ 0.0, -90.0, 0.0, // body
	0.0, 0.0, 0.0, // neck
	0.0, 0.0, 0.0, // left shoulder
	0.0, 0.0,0.0, // right shoulder
	0.0, 0.0, 0.0, // left elbow
	0.0, 0.0, 0.0, // right elbow
	0.0, 0.0, 0.0, // waist
	0.0, 0.0, 0.0, // left hip
	0.0, 0.0, 0.0, // right hip
	0.0, 0.0, 0.0, // left knee
	0.0, 0.0, 0.0, // right knee
	0.0, 0.0, 0.0, // left ankle
	0.0, 0.0, 0.0 },// right ankle

					// KEY FRAME 6
	{ 0.0, -90.0, 0.0, // body
	0.0, 0.0, 0.0, // neck
	50.0, 0.0, 0.0, // left shoulder
	-50.0, 0.0, 0.0, // right shoulder
	0.0, 0.0, 0.0, // left elbow
	0.0, 0.0, 0.0, // right elbow
	0.0, 0.0, 0.0, // waist
	-50.0, 0.0, 0.0, // left hip
	50.0, 0.0, 0.0, // right hip
	0.0, 0.0, 0.0, // left knee
	0.0, 0.0, 0.0, // right knee
	0.0, 0.0, 0.0, // left ankle
	0.0, 0.0, 0.0 },// right ankle

					// KEY FRAME 7
	{ 0.0, -90.0, 0.0, // body
	0.0, 0.0, 0.0, // neck
	0.0, 0.0, 0.0, // left shoulder
	0.0, 0.0, 0.0, // right shoulder
	0.0, 0.0, 0.0, // left elbow
	0.0, 0.0, 0.0, // right elbow
	0.0, 0.0, 0.0, // waist
	0.0, 0.0, 0.0, // left hip
	0.0, 0.0, 0.0, // right hip
	0.0, 0.0, 0.0, // left knee
	0.0, 0.0, 0.0, // right knee
	0.0, 0.0, 0.0, // left ankle
	0.0, 0.0, 0.0 }, // right ankle
					 // KEY FRAME 8
	{ 0.0, -90.0, 0.0, // body
		0.0, 0.0, 0.0, // neck
		-50.0, 0.0, 0.0, // left shoulder
		50.0, 0.0, 0.0, // right shoulder
		0.0, 0.0, 0.0, // left elbow
		0.0, 0.0, 0.0, // right elbow
		0.0, 0.0, 0.0, // waist
		50.0, 0.0, 0.0, // left hip
		-50.0, 0.0, 0.0, // right hip
		0.0, 0.0, 0.0, // left knee
		0.0, 0.0, 0.0, // right knee
		0.0, 0.0, 0.0, // left ankle
		0.0, 0.0, 0.0 }, // right ankle
					 // Initial 
	{
		0.0, 0.0, 0.0, // body
		0.0, 0.0, 0.0, // neck
		0.0, 0.0, 0.0, // left shoulder
		0.0, 0.0, 0.0, // right shoulder
		0.0, 0.0, 0.0, // left elbow
		0.0, 0.0, 0.0, // right elbow
		0.0, 0.0, 0.0, // waist
		0.0, 0.0, 0.0, // left hip
		0.0, 0.0, 0.0, // right hip
		0.0, 0.0, 0.0, // left knee
		0.0, 0.0, 0.0, // right knee
		0.0, 0.0, 0.0, // left ankle
		0.0, 0.0, 0.0
	}
}; // right ankle



   // Local Variable End : EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEe


   /*====================================== CUserModel  Class  ============================================
   - Model a user and display it at the predefined position and orientation

   ==========================================================================================================*/
class CUserModel
{
public:

	CUserModel();   //constructor
					// set the parameters need for simulation
	void SetMovementParameters();  //Initialize the parameters
								   //draw a user with the followings: steering angle(handleTurn) and amount of turn of the wheel(wheelTurn)
	void Display(float handleTurn, float wheelTurn);  // handleTurn: 
	virtual ~CUserModel();

protected:

	GLfloat  curTireAngle;	// 현재 바퀴의 회전 위치
	GLfloat  curRotSpeed;   // 회전 속도: 
	GLint   QUADLIST;   // OpenGL List pointer for the quad defined by "RegQuad()"
	GLint   CUBLIST;	// OpenGL List pointer for the Cube defined by "RegCube()"

						// Function Definition Start: SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSs
public:
	void DrawPitcher(); // draw the robot pitching a ball. 투구하는 로봇을 그린다. 

						// Generate the intermediate frames. 각 키 프레임의 중간 애니메이션 생성
	void CalcDeltas(const Stance *stance1, const Stance *stance2, int n);

	// draw robot head, body, arm, and leg.
	void Torso();		// body
	void Head();
	void LeftUpperArm();
	void LeftLowerArm();
	void RightUpperArm();
	void RightLowerArm();
	void LeftUpperLeg();
	void LeftLowerLeg();
	void RightUpperLeg();
	void RightLowerLeg();
	void OnTimer();
	void StartAnimation();
	void StopAnimation();
	// control functions specific to this application.
	void InitializeDrawing();  // variable initialization. 그리기에 필요한 변수를 초기화 한다. 

	void DrawQuad(int a, int b, int c, int d);
	void TextureCube(int texID);
	void LoadImgTexture();
	// Function Definition End: EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEe


private:
	// Variable Definition Start: SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSs
	// Quadraric object needed for cylinder drawing. cylinder를 그리기 위한 quadric object
	GLUquadricObj *p;

	//current key frame. 현재 로봇의 키 프레임
	Stance m_pitcherStance;

	// variables for animation.  움직임을 위함 변수들
	bool m_bAnimating;		//animation flag
	int m_nKeyFrameIdx;		//current key frame index.   현재 키 프레임
	int m_nSubFrameIdx;		//next key frame index

	Stance m_deltas;		// variation between two intermediate frames. 두 중간 프레임 사이의 변화량

	GLfloat m_vertices[8][3];	// for drawing a quad
	GLfloat m_normals[6][3];	// normal

								// Texture Mapping을 위한 멤버 추가
	GLubyte m_image[64][64][3];
	AUX_RGBImageRec * m_texRec[6];
	GLuint			  m_texID[6];  // test id

								   // Variable Definition End : EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEe

};
