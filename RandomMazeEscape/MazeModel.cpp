#include "StdAfx.h"
#include "MazeModel.h"
#include <cmath>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*=====================================  CMazeModel Class    =============================================
Function: distructor
=================================================================================================*/
CMazeModel::~CMazeModel()
{
}


/*=====================================  CMazeModel Class    =============================================
Function: Constructor
Pre :
Post:
=====================================================================================================*/
CMazeModel::CMazeModel()
{

	Unit = 10.0;	// maze model�� scale�� �����Ѵ�. 

	crossBlockSize = 6.0*Unit;
	middleBlockSize = 6.0*Unit;

	mazeHeight = 7.0*Unit;
	stackIndex = 0;
	step_debug = 0;
	maze_number_debug = 0;
	maze_plan_debug = 0;
	maze_dim = 0;

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

}

void CMazeModel::DrawCrossBlock(GLfloat xpos, GLfloat zpos, GLfloat yRotate)
{
	GLfloat mat_ambient1[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat mat_diffuse1[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat mat_specular1[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_shininess1 = 100.0;
	// �������� �ո��� ������ ���� 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess1);

	glPushMatrix();
	glTranslatef(xpos, 0.0, zpos);
	glRotatef(yRotate, 0.0, 1.0, 0.0);

	//?? Draw the building 1: 
	glPushMatrix();
	//ũ�� (6.0*Unit, mazeHeight, 2.0*Unit) �� cube�� �׸���.
	glTranslatef(0.0*Unit, mazeHeight / 2.0, 0.0*Unit);
	glScalef(1.0*Unit, 0.5*mazeHeight, 1.0*Unit);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(0);
	// glColor3fv(RED);
	// PlaceObject(6.0*Unit, mazeHeight, 2.0*Unit, 0.0, 0.0*Unit, mazeHeight / 2.0, 0.0*Unit);
	glPopMatrix();

	glPopMatrix();	// ���� ����� �� ��� ���ÿ��� ������ ������
}

void CMazeModel::DrawMiddleBlock(GLfloat xpos, GLfloat zpos, GLfloat yRotate)
{
	GLfloat mat_ambient4[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat mat_diffuse4[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat mat_specular4[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess4 = 100.0;
	// �������� �ո��� ������ ���� 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);

	glPushMatrix();
	glTranslatef(xpos, 0.0, zpos);
	glRotatef(yRotate, 0.0, 1.0, 0.0);

	//?? Draw the building 1: 
	glPushMatrix();
	//ũ�� (6.0*Unit, mazeHeight, 2.0*Unit) �� cube�� �׸���.
	glTranslatef(0.0*Unit, mazeHeight / 2.0, 0.0*Unit);
	glScalef(3.0*Unit, 0.5*mazeHeight, 1.0*Unit);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(1);
	// glColor3fv(BLUE);
	// PlaceObject(6.0*Unit, mazeHeight, 2.0*Unit, 0.0, 0.0*Unit, mazeHeight / 2.0, 0.0*Unit);
	glPopMatrix();
	glPopMatrix();	// ���� ����� �� ��� ���ÿ��� ������ ������
}

void CMazeModel::DrawHorizontalBlock(GLfloat xpos, GLfloat zpos, GLfloat yRotate)
{
	glPushMatrix();
	glTranslatef(xpos, 0.0, zpos);
	glRotatef(yRotate, 0.0, 1.0, 0.0);

	//?? Draw the building 1: 
	glPushMatrix();
	//DrawMiddleBlock(-6.0*Unit, 0.0, 0.0);
	DrawMiddleBlock(0.0, 0.0, 0.0);
	//DrawMiddleBlock(6.0*Unit, 0.0, 0.0);
	glPopMatrix();
	glPopMatrix();	// ���� ����� �� ��� ���ÿ��� ������ ������
}

void CMazeModel::DrawCornerBlock(GLfloat xpos, GLfloat zpos, GLfloat yRotate) // �����
{
	GLfloat mat_ambient1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse1[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat mat_specular1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess1 = 10.0;
	// �������� �ո��� ������ ���� 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess1);

	glPushMatrix();
	glTranslatef(xpos, 0.0, zpos);
	glRotatef(yRotate, 0.0, 1.0, 0.0);

	//?? Draw the building 1: 
	glPushMatrix();
	//ũ�� (4.0*Unit, mazeHeight, 2.0*Unit) �� cube�� �׸���.
	glTranslatef(-1.0*Unit, mazeHeight / 2.0, 0.0*Unit);
	glScalef(2.0*Unit, 0.5*mazeHeight, 1.0*Unit);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(0);
	// glColor3fv(RED);
	// PlaceObject(4.0*Unit, mazeHeight, 2.0*Unit, 0.0, 0.0*Unit, mazeHeight / 2.0, 0.0*Unit);
	glPopMatrix();

	//?? Draw the building 2: 
	glPushMatrix();
	//ũ�� (2.0*Unit, mazeHeight, 2.0*Unit) �� cube�� �׸���.
	glTranslatef(0.0*Unit, mazeHeight / 2.0, 2.0*Unit);
	glScalef(1.0*Unit, 0.5*mazeHeight, 1.0*Unit);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(0);
	// PlaceObject(2.0*Unit, mazeHeight, 2.0*Unit, 0.0, 0.0*Unit, mazeHeight / 2.0, 2.0*Unit);
	glPopMatrix();

	glPopMatrix();	// ���� ����� �� ��� ���ÿ��� ������ ������
}

void CMazeModel::DrawItem(GLfloat xpos, GLfloat zpos, GLfloat yRotate)
{
	GLfloat mat_ambient4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess4 = 200.0;
	// �������� �ո��� ������ ���� 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);

	glPushMatrix();
	glTranslatef(xpos, 3.0*Unit, zpos);
	glRotatef(yRotate, 0.0, 1.0, 0.0);

	glPushMatrix();
	glScalef(0.6*Unit, 0.6*Unit, 0.6*Unit);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(4);
	//glutSolidTorus(0.3*Unit, 0.6*Unit, 10, 20);
	glPopMatrix();
	glPopMatrix();	// ���� ����� �� ��� ���ÿ��� ������ ������
}

void CMazeModel::MakeItem()
{
	// �������� itemNum�� Item ��ġ
	srand(unsigned(time(NULL)));
	int itemNum = rand() % mazeLevel + 2;

	while (itemNum > 0)
	{
		int i = rand() % maze_dim, j = rand() % maze_dim;
		if (i == 1 && j == 0);
		else if (maze_plan[i][j] == ' ')	// ��ĭ�� ��
		{
			maze_plan[i][j] = '*';
			itemNum--;
		}
	}
}

void CMazeModel::DrawMaze()
{
	// Ground
	GLfloat mat_ambient[4] = { 1.2f, 1.4f, 1.0f, 1.0f };
	//GLfloat mat_ambient[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat mat_diffuse[4] = { 1.2f, 1.2f, 1.2f, 1.0f };
	GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess = 10.0;

	// �������� �ո��� ������ ���� 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glColor3fv(GRAY);
	//DrawGround();	  // DrawGround �Լ� ȣ��	

					  // World coordinate�� �׸�����.
	//glLineWidth(5.0);
	//glColor3fv(RED);
	//DrawLine(0.0, 0.0, 0.0, GROUND_LIMITF, 0.0, 0.0); // x �� 
	//(GREEN);
	//DrawLine(0.0, 0.0, 0.0, 0.0, GROUND_LIMITF, 0.0); // Y �� 
	//glColor3fv(BLUE);
	//DrawLine(0.0, 0.0, 0.0, 0.0, 0.0, GROUND_LIMITF); // Z �� 

	glPushMatrix();	// ��� ���ÿ� ������ ����� push
					/*---------------------------------------------
					Maze ũ�� :
					���� = 2 * maze_dim - 1
					���� = maze_dim
					Maze Level :
					Level(�Է°�) = (maze_dim - 1) / 2
					----------------------------------------------*/

	glTranslatef(-(maze_dim - 0.5)*6.0*Unit, 0.0, -0.5*maze_dim*6.0*Unit);	// �̷� �߾��� ������ ���� �̵�
	for (int i = 0; i < maze_dim; i++)
	{
		for (int j = 0; j < maze_dim; j++)
		{
			bool up = false;
			bool down = false;
			bool left = false;
			bool right = false;

			float xpos = 6 * 1 * j * Unit, zpos = 6 * i * Unit;



			if (maze_plan[i][j] == '+')
			{
				glPushMatrix();
				DrawCrossBlock(xpos, zpos, 0.0);
				glPopMatrix();

				if ((i != 0) && ((maze_plan[i - 1][j] != ' ') && (maze_plan[i - 1][j] != '*'))) {
					up = true;
					glPushMatrix();
					glTranslatef(0.0*Unit, 0, -2.0*Unit);
					DrawCrossBlock(xpos, zpos, 0.0);
					glPopMatrix();

				}
				if ((i != maze_dim - 1) && ((maze_plan[i + 1][j] != ' ') && (maze_plan[i + 1][j] != '*'))) {
					down = true;
					glPushMatrix();
					glTranslatef(0.0*Unit, 0, 2.0*Unit);
					DrawCrossBlock(xpos, zpos, 0.0);
					glPopMatrix();
				}
				if ((j != 0) && ((maze_plan[i][j - 1] != ' ') && (maze_plan[i][j - 1] != '*'))) {
					left = true;
					glPushMatrix();
					glTranslatef(-2.0*Unit, 0, 0.0*Unit);
					DrawCrossBlock(xpos, zpos, 0.0);
					glPopMatrix();
				}
				if ((j != maze_dim - 1) && ((maze_plan[i][j + 1] != ' ') && (maze_plan[i][j + 1] != '*'))) {
					right = true;
					glPushMatrix();
					glTranslatef(2.0*Unit, 0, 0.0*Unit);
					DrawCrossBlock(xpos, zpos, 0.0);
					glPopMatrix();
				}

				glPushMatrix();
				DrawCrossBlock(xpos, zpos, 0.0);
				glPopMatrix();
			}
			else if (maze_plan[i][j] == '-')
			{
				glPushMatrix();
				DrawHorizontalBlock(xpos, zpos, 0.0);
				glPopMatrix();
			}
			else if (maze_plan[i][j] == '|')
			{
				glPushMatrix();
				DrawMiddleBlock(xpos, zpos, 90.0);
				glPopMatrix();
			}
			else if (maze_plan[i][j] == '*')
			{
				glPushMatrix();
				DrawItem(xpos, zpos, 90.0);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
}

void CMazeModel::DrawBackGround()
{
	GLfloat mat_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess = 100.0;
	// �������� �ո��� ������ ���� 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	// �ٴ�
	glPushMatrix();
	glTranslatef(-(maze_dim - 0.5)*Unit, -5.0, -0.5*maze_dim*Unit);	// �̷� �߾��� ������ ���� �̵�
	glScalef(5 * maze_dim*5.0*Unit, 10, 5 * maze_dim*5.0*Unit);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(3);
	glPopMatrix();

	/*------------
	�ϴ�
	-------------*/
	// ����
	
	float g_ViewerHeight = 600.0f + 10.0 * (mazeLevel*(mazeLevel + 1) / 2 - 3 + 2 * mazeLevel - 4);
	glPushMatrix();
	glTranslatef(0.0, g_ViewerHeight + 10, 0.0);	// �̷� �߾��� ������ ���� �̵�
	glScalef(10000, 10, 10000);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(2);
	glPopMatrix();

	// ������
	glPushMatrix();
	glTranslatef(5000.0, 10.0, 0.0);	// �̷� �߾��� ������ ���� �̵�
	glScalef(10, g_ViewerHeight, 10000);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(2);
	glPopMatrix();

	// ����
	glPushMatrix();
	glTranslatef(-5000.0, 10.0, 0.0);	// �̷� �߾��� ������ ���� �̵�
	glScalef(10, g_ViewerHeight, 10000);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(2);
	glPopMatrix();

	// ����
	glPushMatrix();
	glTranslatef(0.0, 10.0, -5000.0);	// �̷� �߾��� ������ ���� �̵�
	glScalef(10000, g_ViewerHeight, 10);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(2);
	glPopMatrix();

	// ����
	glPushMatrix();
	glTranslatef(0.0, 10.0, 5000.0);	// �̷� �߾��� ������ ���� �̵�
	glScalef(10000, g_ViewerHeight, 10);
	glColor3f(1.0, 1.0, 1.0);
	TextureCube(2);
	glPopMatrix();
	
}

bool CMazeModel::IsCollision(GLfloat xpos, GLfloat zpos)
{
	// �̷� �߾��� ������ ���� �̵��ߴ� �۾� ���
	float saveX = xpos, saveZ = zpos;
	xpos += (maze_dim - 0.5)*6.0*Unit;
	zpos += 0.5*maze_dim*6.0*Unit;
	int i, j, tmpZ, tmpX;


	tmpZ = round(((zpos) / Unit) / 6.0);
	tmpX = round(((xpos) / Unit) / 6.0);


	if (tmpZ < 0) tmpZ = 0;
	if (tmpX < 0) tmpX = 0;

	if (abs(zpos / Unit / 6.0 - tmpZ) < 0.3) {
		if (abs(xpos / Unit / 6.0 - tmpX) < 0.3) {
			i = tmpZ;
			j = tmpX;

			// ���� �ƴ� ���
			if (maze_plan[i][j] == '*' || maze_plan[i][j] == 'X' || maze_plan[i][j] == ' ')
				return false;
			else
				return true;
		}
	}

	// �������� ���� ���
	return false;
}

bool CMazeModel::IsStart(GLfloat xpos, GLfloat zpos)
{
	// �̷� �߾��� ������ ���� �̵��ߴ� �۾� ���
	float saveX = xpos, saveZ = zpos;
	xpos += (maze_dim - 0.5)*6.0*Unit;
	zpos += 0.5*maze_dim*6.0*Unit;

	int i, j;
	i = round((zpos / 6.0) / Unit);
	j = round((xpos / 6.0) / Unit);
	if (i < 0) i = 0;
	if (j < 0) j = 0;

	// ������
	if (i == 1 && j == 0) return true;
	else return false;
}

bool CMazeModel::IsEnd(GLfloat xpos, GLfloat zpos)
{
	// �̷� �߾��� ������ ���� �̵��ߴ� �۾� ���
	float saveX = xpos, saveZ = zpos;
	xpos += (maze_dim - 0.5)*6.0*Unit;
	zpos += 0.5*maze_dim*6.0*Unit;

	int i, j;
	i = round((zpos / 6.0) / Unit);
	j = round((xpos / 6.0) / Unit);
	if (i < 0) i = 0;
	if (j < 0) j = 0;

	// ����
	if (i == maze_dim - 2 && j == maze_dim - 1) return true;
	else return false;
}

bool CMazeModel::IsItem(GLfloat xpos, GLfloat zpos)
{
	// �̷� �߾��� ������ ���� �̵��ߴ� �۾� ���
	float saveX = xpos, saveZ = zpos;
	xpos += (maze_dim - 0.5)*6.0*Unit;
	zpos += 0.5*maze_dim*6.0*Unit;

	int i, j;
	i = round((zpos / 6.0) / Unit);
	j = round((xpos / 6.0) / Unit);
	if (i < 0) i = 0;
	if (j < 0) j = 0;

	// item
	if (maze_plan[i][j] == '*') {
		maze_plan[i][j] = ' ';
		return true;
	}
	else return false;
}

/*=====================================  CMazeModel Class    =============================================
Function: Draw checkerboard textures on the ground.
Pre: the ground is defined on the XZ plane
=================================================================================================*/
void CMazeModel::DrawGround()
{
	int r, c;
	int nStep = 10;

	glBegin(GL_LINES); // Ŀ�ٶ� �鿡 ���� �ߴ´�
	for (r = -GROUND_LIMIT; r <= GROUND_LIMIT; r += nStep) // X������� line draw
	{
		glVertex3f((float)r, 0.0f, -GROUND_LIMITF);
		glVertex3f((float)r, 0.0f, GROUND_LIMITF);
	}
	for (c = -GROUND_LIMITF; c <= GROUND_LIMITF; c += nStep)	// Z������� line draw
	{
		glVertex3f(GROUND_LIMITF, 0.0f, (float)c);
		glVertex3f(-GROUND_LIMITF, 0.0f, (float)c);
	}
	glEnd();
}


/* ==================================================================================================
Function : Draw a line
====================================================================================================*/
void CMazeModel::DrawLine(float xStart, float yStart, float zStart, float xEnd, float yEnd, float zEnd)
{
	glBegin(GL_LINES);
	glVertex3f(xStart, yStart, zStart);
	glVertex3f(xEnd, yEnd, zEnd);
	glEnd();
}

/*==================================================================================
Function: Display the quad deinfed by the "RegQuad()" at (xPos,zPos)
after scaling it by using the paramter (xScale, zScale)
and rotating it with respect to y axis by yRoate
====================================================================================*/

void CMazeModel::DrawPlane(float xScale, float zScale, float yRotate, float xPos, float zPos)
{
	glPushMatrix();	// ��� ���ÿ� ������ ����� push
	glTranslatef(xPos, 0.0, zPos); // �ش� ��ġ�� �̵� 
	glRotatef(yRotate, 0.0, 1.0, 0.0); // Y�࿡ ���� ȸ��
	glScalef(xScale, 1.0, zScale);
	glCallList(QUADLIST);

	glPopMatrix();	// ���� ����� �� ��� ���ÿ��� ������ ������
}



/*==================================================================================
Function: Place a cube defined by the function "RegCube()" at the position (posX,posY,posY)
after scaling the cube by using the parameter (scaleX, scaleY, scaleZ)
====================================================================================*/
void CMazeModel::PlaceObject(float scaleX, float scaleY, float scaleZ,
	float rotateY, float posX, float posY, float posZ)
{
	glPushMatrix();	// ��� ���ÿ� ������ ����� push
	glTranslatef(posX, posY, posZ); // �ش� ��ġ�� �̵� 
	glRotatef(rotateY, 0.0, 1.0, 0.0); // Y�࿡ ���� ȸ��
	glScalef(scaleX, scaleY, scaleZ);
	glCallList(CUBLIST);
	glPopMatrix();	// ���� ����� �� ��� ���ÿ��� ������ ������
}

/*=================================================================================================
Function: Dispaly a quad
Pre: array cube should be defined.
=================================================================================================*/
void CMazeModel::DisplayQuad(GLfloat cube[][3], int a, int b, int c, int d)
{

	//	 glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);

	// set the current texture coordinates
	//glTexCoord2f(0.0, 0.0);
	glVertex3fv(cube[a]); // 0

						  // set the current texture coordinates
						  //glTexCoord2f(1.0, 0.0);
	glVertex3fv(cube[b]); // 1

						  // set the current texture coordinates
						  //glTexCoord2f(1.0, 1.0);
	glVertex3fv(cube[c]); // 2

						  // set the current texture coordinates
						  //glTexCoord2f(0.0, 1.0);
	glVertex3fv(cube[d]); // 3
	glEnd();
}


void CMazeModel::DefinePrimitiveListforScene()
{

	GLfloat unitSquare[][3] = { { 0.5, 0.0, 0.5 },{ 0.5, 0, -0.5 }
	,{ -0.5, 0.0, -0.5 },{ -0.5, 0.0, 0.5 } };

	/*		     Y
	7----|--------6
	/     |       /|
	/      |      / |
	4------|-----5| |
	|  2   /------|-/1------->x
	|     /       |/
	|3---/--------0
	/z					*/
	GLfloat unitCube[][3] = { { 0.5, -0.5, 0.5 },{ 0.5, -0.5, -0.5 }
		,{ -0.5, -0.5, -0.5 },{ -0.5, -0.5, 0.5 }
		,{ -0.5, 0.5, 0.5 },{ 0.5, 0.5, 0.5 }
	,{ 0.5, 0.5, -0.5 },{ -0.5, 0.5, -0.5 } };
	GLfloat surfaceNorm[][3] = {
		{ 0.0, 0.0, 1.0 }		 // �ո�		
		,{ 1.0, 0.0, 0.0 }	 //������ ��	
		,{ 0.0, 0.0, -1.0 }	 // �޸�
		,{ -1.0, 0.0, 0.0 }	 // ���ʸ�
		,{ 0.0, 1.0, 0.0 }	  // ����		
		,{ 0.0, -1.0, 0.0 }	 // �ظ�	
	};
	//Register a unit Square as a list. The cube is defined on xz plane with the center as (0,0,0)
	QUADLIST = glGenLists(1);
	glNewList(QUADLIST, GL_COMPILE);
	glNormal3fv(surfaceNorm[4]);
	DisplayQuad(unitSquare, 0, 1, 2, 3);
	glEndList();

	CUBLIST = glGenLists(2);
	glNewList(CUBLIST, GL_COMPILE);
	glNormal3fv(surfaceNorm[0]);
	DisplayQuad(unitCube, 0, 5, 4, 3); // �ո�
	glNormal3fv(surfaceNorm[1]);
	DisplayQuad(unitCube, 0, 1, 6, 5); //������ ��
	glNormal3fv(surfaceNorm[2]);
	DisplayQuad(unitCube, 1, 2, 7, 6); // �޸�
	glNormal3fv(surfaceNorm[3]);
	DisplayQuad(unitCube, 4, 7, 2, 3); // ���ʸ�
	glNormal3fv(surfaceNorm[4]);
	DisplayQuad(unitCube, 4, 5, 6, 7);  // ����
	glNormal3fv(surfaceNorm[5]);
	DisplayQuad(unitCube, 0, 1, 2, 3); // �ظ�
	glEndList();

}

// Maze
void CMazeModel::AllocMaze(int matrix_dim)
{
	mazeLevel = matrix_dim;
	stack = (int**)calloc(matrix_dim*matrix_dim * 100, sizeof(int*)); //Stack olusturma
	for (int i = 0; i < matrix_dim*matrix_dim * 100; i++)
		stack[i] = (int*)calloc(2, sizeof(int));

	neighbors_matrix = (int**)calloc(4, sizeof(int*));
	for (int i = 0; i < 4; i++)
		neighbors_matrix[i] = (int*)calloc(3, sizeof(int));

	neighbors_matrix[0][0] = -1;
	neighbors_matrix[0][1] = 0;

	neighbors_matrix[1][0] = 0;
	neighbors_matrix[1][1] = 1;

	neighbors_matrix[2][0] = 1;
	neighbors_matrix[2][1] = 0;

	neighbors_matrix[3][0] = 0;
	neighbors_matrix[3][1] = -1;

	matrix_dim += 2;
	maze_dim = 2 * (matrix_dim - 2) + 1;

	maze = (int**)calloc(matrix_dim, sizeof(int*));
	for (int i = 0; i < matrix_dim; i++)
		maze[i] = (int*)calloc(matrix_dim, sizeof(int));

	visited = (int**)calloc(matrix_dim, sizeof(int*));
	for (int i = 0; i < matrix_dim; i++)
		visited[i] = (int*)calloc(matrix_dim, sizeof(int));

	generate_maze(maze, 1, 1, visited, matrix_dim);
}

void CMazeModel::push(int row, int col)
{
	if (stackIndex >= 0)
	{
		stack[stackIndex][0] = row;
		stack[stackIndex][1] = col;
	}
	stackIndex++;

}

void CMazeModel::pop(int *row, int *col)
{
	stackIndex--;
	if (stackIndex >= 0)
	{
		*row = stack[stackIndex][0];
		*col = stack[stackIndex][1];
	}
}

void CMazeModel::show_stack()
{
	int temp_stack = stackIndex - 1;
	printf("???");
	while (temp_stack >= 0)
	{
		printf(" %d - %d ||", stack[temp_stack][0], stack[temp_stack][1]);
		temp_stack--;
	}
}

char** CMazeModel::create_empty_maze()
{
	char **maze_plan = (char**)calloc(maze_dim, sizeof(char*));
	int i, j;

	for (i = 0; i < maze_dim; i++)
	{
		maze_plan[i] = (char*)calloc(maze_dim, sizeof(char));

		for (j = 0; j < maze_dim; j++)
		{
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
					maze_plan[i][j] = '+';
				else
					maze_plan[i][j] = '-';
			}
			else
			{
				if (j % 2 == 0)
					maze_plan[i][j] = '|';
				else
					maze_plan[i][j] = ' ';
			}
		}
	}

	/*----------------------
	�̷��� �ܺ� �� ����
	-----------------------*/
	for (int i = 0; i < maze_dim; i++)
	{
		for (int j = 0; j < maze_dim; j++)
		{
			if (i == 0 || i == maze_dim - 1)
			{
				maze_plan[i][j] = '-';
			}
			else if (j == 0 || j == maze_dim - 1)
				maze_plan[i][j] = '|';
		}
	}
	for (int i = 0; i < maze_dim; i++)
	{
		for (int j = 0; j < maze_dim; j++)
		{
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					maze_plan[i][j] = '+';
				}
			}

		}
	}

	/*----------------------
	�̷��� �� �𼭸� ����
	(�ð��������� �����Ҵ�)
	�� : '1'
	�� : '2'
	�� : '3'
	�� : '4'
	-----------------------*/
	maze_plan[0][0] = '+';
	maze_plan[0][maze_dim - 1] = '+';
	maze_plan[maze_dim - 1][maze_dim - 1] = '+';
	maze_plan[maze_dim - 1][0] = '+';

	return maze_plan;
}

void CMazeModel::generate_maze(int **maze, int start_row, int start_col, int **visited, int matrix_dim)
{

	push(start_row, start_col);
	visited[start_row][start_col] = 1;

	maze_plan = create_empty_maze();
	int i, j;

	int counter0 = 0;
	int temp_row = start_row;
	int temp_col = start_col;
	int temp_row1 = start_row;
	int temp_col1 = start_col;

	maze_plan[start_row][start_col] = 'X';


	while (stackIndex != 0)
	{
		int row, col;
		int n_index;

		pop(&row, &col);
		start_row = row;
		start_col = col;
		visited[row][col] = 1;

		int k = 0;
		int counter = 0;
		n_index = 0;
		while (k == 0 && counter < 4)
		{
			n_index = rand() % (6343 - rand() % 2243);// (row * 29 + 1));
			n_index %= 4;
			// n_index = rand() % 4;
			row = start_row + neighbors_matrix[n_index][0];
			col = start_col + neighbors_matrix[n_index][1];
			neighbors_matrix[n_index][2] = 1;

			if (!(row < 0 || col < 0 || (row == 0 || col == 0 || row == matrix_dim - 1 || col == matrix_dim - 1)))
			{

				if (visited[row][col] == 0)
				{
					counter0 = 0;
					maze[start_row][start_col] = 10 * (row)+col;

					if (step_debug == 1)
						printf("%d-%d ->", row, col);

					if (start_row == row && start_col != col)
					{
						if (start_col > col)
						{
							temp_col1 = temp_col;
							temp_row1 = temp_row;

							maze_plan[temp_row][temp_col - 1] = ' ';
							maze_plan[temp_row][temp_col - 2] = ' ';
							temp_col -= 2;

						}
						else
						{
							temp_col1 = temp_col;
							temp_row1 = temp_row;

							maze_plan[temp_row][temp_col + 1] = ' ';
							maze_plan[temp_row][temp_col + 2] = ' ';
							temp_col += 2;
						}
					}
					else if (start_col == col && start_row != row)
					{
						if (start_row > row)
						{
							temp_col1 = temp_col;
							temp_row1 = temp_row;

							maze_plan[temp_row - 1][temp_col] = ' ';
							maze_plan[temp_row - 2][temp_col] = ' ';
							temp_row -= 2;
						}
						else
						{
							temp_col1 = temp_col;
							temp_row1 = temp_row;

							maze_plan[temp_row + 1][temp_col] = ' ';
							maze_plan[temp_row + 2][temp_col] = ' ';
							temp_row += 2;
						}
					}

					push(start_row, start_col);
					push(row, col);
					visited[row][col] = 1;
					k = 1;
				}
				else
					counter = neighbors_matrix[0][2] + neighbors_matrix[1][2] + neighbors_matrix[2][2] + neighbors_matrix[3][2];
			}
		}

		if (counter == 4)
		{
			pop(&row, &col);

			if (start_row == row && start_col != col)
			{
				if (start_col > col)
					temp_col -= 2;
				else
					temp_col += 2;
			}
			else if (start_col == col && start_row != row)
			{
				if (start_row > row)
					temp_row -= 2;
				else
					temp_row += 2;
			}
			push(row, col);
		}

		neighbors_matrix[0][2] = 0;
		neighbors_matrix[1][2] = 0;
		neighbors_matrix[2][2] = 0;
		neighbors_matrix[3][2] = 0;
	}

	//printf("\n");

	maze_plan[maze_dim - 2][maze_dim - 2] = 'X';

	// ���
	maze_plan[1][0] = ' ';
	maze_plan[maze_dim - 2][maze_dim - 1] = ' ';
	/*
	for (int i = 0; i < maze_dim; i++)
	{
	for (int j = 0; j < maze_dim; j++)
	printf(" %c ", maze_plan[i][j]);
	printf("\n");
	}
	*/
}

void CMazeModel::delete_maze()
{
	stackIndex = 0;
	step_debug = 0;
	maze_number_debug = 0;
	maze_plan_debug = 0;
	maze_dim = 0;

	// stack �Ҵ� ����
	for (int i = 0; i < mazeLevel*mazeLevel * 100; i++)
		free(stack[i]);
	free(stack);

	// neighbors_matrix �Ҵ� ����
	for (int i = 0; i < 4; i++)
		free(neighbors_matrix[i]);
	free(neighbors_matrix);

	// maze, visited �Ҵ� ����
	for (int i = 0; i < mazeLevel + 2; i++)
	{
		free(maze[i]);
		free(visited[i]);
	}
	free(maze);
	free(visited);

	// maze_plan �Ҵ� ����
	for (int i = 0; i < maze_dim; i++)
		free(maze_plan[i]);
	free(maze_plan);
}

void CMazeModel::LoadImgTexture()
{
	m_texRec[0] = auxDIBImageLoad(L"wall.bmp");	// Cross Block
	m_texRec[1] = auxDIBImageLoad(L"wall.bmp");// Middle Block
	m_texRec[2] = auxDIBImageLoad(L"Wine.bmp");  // �ϴ�
	m_texRec[3] = auxDIBImageLoad(L"Grass.bmp");// �ܵ�
	m_texRec[4] = auxDIBImageLoad(L"Item.bmp");// �ܵ�

	glGenTextures(5, &m_texID[0]); // Generates texture names

	for (register int i = 0; i < 5; i++) {
		// The creation of a named texture that is bound to a texture target
		glBindTexture(GL_TEXTURE_2D, m_texID[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			m_texRec[i]->sizeX, m_texRec[i]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, m_texRec[i]->data);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		// ������ ó������ ���� ��� memory leak �߻�
		delete[] m_texRec[i]->data;
		delete m_texRec[i];
	}
	glEnable(GL_TEXTURE_2D); //<11>
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //<
	
}

// Step 3: Texture mapping�� ���� �ؽ��� ��ǥ ����
void CMazeModel::DrawQuad(int a, int b, int c, int d)
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

void CMazeModel::TextureCube(int texID)
{
	//LoadImgTexture();	
	// ���鿡 ���� �ٸ� texture�� mapping �Ѵ�.

	// ��
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(3, 2, 1, 0);
	// ��
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(1, 2, 6, 5);
	// ������
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(7, 6, 2, 3);
	// �Ʒ�
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(3, 0, 4, 7);
	// ��
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(4, 5, 6, 7);
	// ����
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	DrawQuad(0, 1, 5, 4);
}