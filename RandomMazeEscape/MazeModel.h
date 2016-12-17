#pragma once
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "opengl/lib/glut32.lib")
#pragma comment (lib, "opengl/lib/glaux.lib")

#include <gl/GL.h>
#include <gl/GLU.h>
#include "opengl/include/glut.h"
#include "opengl/include/GLAUX.H"
#include <math.h>

#define	PI  3.14159265359f
extern GLfloat BLUE[3];  // Blue
extern GLfloat YELLOW[3];
extern GLfloat GREEN[3];
extern GLfloat RED[3];
extern GLfloat WHITE[3];  // Blue
extern GLfloat GRAY[3];  // Blue

#define STREETWIDTH 80

#define GROUND_LIMIT 10000
#define GROUND_LIMITF 10000.0f

						 /* =========================================   CMazeModel Class    =========================================
						 The scene construction procedures:
						 - Draw the checkerboard textures on the XZ plane of SC
						 - Generate a small straight street block
						 - Generate a small street corner block
						 - Generate a small maze block by connecting the street blocks
						 - Generate the scene by using connecting the maze blocks
						 =======================================================================================================*/
class CMazeModel
{
public:
	CMazeModel();
	virtual ~CMazeModel();

	void DrawCrossBlock(GLfloat xpos, GLfloat zpos, GLfloat yRotate);
	void DrawMiddleBlock(GLfloat xpos, GLfloat zpos, GLfloat yRotate);
	void DrawHorizontalBlock(GLfloat xpos, GLfloat zpos, GLfloat yRotate);
	void DrawCornerBlock(GLfloat xpos, GLfloat zpos, GLfloat yRotate);
	void DrawItem(GLfloat xpos, GLfloat zpos, GLfloat yRotate);
	void MakeItem();
	void DrawMaze();
	void DrawBackGround();

	bool IsCollision(GLfloat xpos, GLfloat zpos);
	bool IsStart(GLfloat xpos, GLfloat zpos);
	bool IsEnd(GLfloat xpos, GLfloat zpos);
	bool IsItem(GLfloat xpos, GLfloat zpos);

	void DrawGround();		// Draw checkerboard textures on the ground. Assume that the ground is XZ plane
	void DefinePrimitiveListforScene(); // register primitives for scene modeling
	void DisplayQuad(GLfloat arr[][3], int a, int b, int c, int d);	// display a quad defined by the four points: a,b,c,d

																	/*==================================================================================
																	Function: Place a cube defined by the function "RegCube()" at the position (posX,posY,posY)
																	after scaling the cube by using the parameter (scaleX, scaleY, scaleZ)
																	====================================================================================*/
	void PlaceObject(float scaleX, float scaleY, float scaleZ,
		float rotateY,
		float posX, float posY, float posZ);

	/*==================================================================================
	Function: Display the quad deinfed by the "RegQuad()" at (xPos,zPos)
	after scaling it by using the paramter (xScale, zScale)
	and rotating it with respect to y axis by yRoate
	====================================================================================*/
	void DrawPlane(float xScale, float zScale,
		float yRotate,
		float xPos, float zPos);
	/* ==================================================================================================
	Function : Draw a line
	=====================================================================================================*/
	void DrawLine(float xStart, float yStart, float zStart, float xEnd, float yEnd, float zEnd);

	GLfloat GetUnit() { return Unit; };

	// Texture Mapping
	void DrawQuad(int a, int b, int c, int d);
	void TextureCube(int texID);	// draw cube with textures in the bit maps read in
	void LoadImgTexture();

	// Maze
	void AllocMaze(int matrix_dim);
	void push(int row, int col);
	void pop(int *row, int *col);
	void show_stack();
	char **create_empty_maze();
	void generate_maze(int **maze, int start_row, int start_col, int **visited, int matrix_dim);
	void delete_maze();

private:
	GLfloat Unit;
	GLint   QUADLIST;   // OpenGL List pointer for the quad defined by "RegQuad()"
	GLint   CUBLIST;	// OpenGL List pointer for the Cube defined by "RegCube()"

						// Maze
	int **stack;
	int stackIndex;

	int **neighbors_matrix;

	int step_debug;
	int maze_number_debug;
	int maze_plan_debug;
	int maze_dim;
	int mazeLevel;	// matrix_dim과 동일 (+2하기 전)

	int **maze;
	int **visited;
	char **maze_plan;

	GLfloat mazeHeight;
	GLfloat crossBlockSize;		// = 6U
	GLfloat middleBlockSize;	// = 6U
	GLfloat horizontalBlockSize;// = 6U x 18U

	GLfloat m_vertices[8][3];	// for drawing a quad
	GLfloat m_normals[6][3];	// normal

								// Texture Mapping을 위한 멤버 추가
	GLubyte m_image[64][64][3];
	AUX_RGBImageRec * m_texRec[5];
	GLuint			  m_texID[5];	// test id
};
