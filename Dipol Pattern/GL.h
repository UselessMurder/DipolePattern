#pragma once
#include <Windows.h>
#include "glut.h"
#include <vector>
#include <cmath>
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"Gdi32.lib")
#pragma comment (lib,"glut.lib")
#pragma comment (lib,"glut32.lib")



struct Vertex
{
	double x;
	double y;
	double z;
};

struct Ñamera_position
{
	GLdouble x;
	GLdouble y;
	GLdouble z;
};

struct Red_Green_Blue
{
	double red;
	double green;
	double blue;
};

struct Camera_turn
{
	GLdouble x_increment;
	GLdouble x_decrement;
	GLdouble y_increment;
	GLdouble y_decrement;
	GLdouble z_increment;
	GLdouble z_decrement;
};



class  GL {
private: 
	HWND output;
	GLboolean output_true;

	HGLRC  hRC;
	HDC  hDC;

	GLuint  PixelFormat;

	Ñamera_position head;
	Camera_turn view_angle;

	GLdouble scale;

	GLuint base;
	GLYPHMETRICSFLOAT gmf[256];

	GLvoid Build_Font(GLvoid);

	GLvoid Print_Text(const char *fmt, ...);


	GLvoid Alter_x_Angle(GLboolean add, GLint old_position, GLint new_position);
	GLvoid Alter_y_Angle(GLboolean add, GLint old_position, GLint new_position);
	GLvoid Alter_z_Angle(GLboolean add, GLint old_position, GLint new_position);
public:
	GL();
	~GL();

	GLint Init_GL(GLvoid);
	GLboolean Start_GL(HWND input_output, GLsizei width, GLsizei height);
	GLvoid Resize_GL_Scene(GLsizei width, GLsizei height);
	GLint Draw_GL_Scene(std::vector<Vertex> &electric_field_line, std::vector<Vertex> &magnetic_field_line, std::pair<Vertex, Vertex> Etheta, std::pair<Vertex, Vertex> Hphi);

	GLvoid Draw_Vector(Vertex begin, Vertex end, Red_Green_Blue color, GLdouble width, const char *txt);

	GLvoid Set_x_Location(GLdouble input_x_location);
	GLvoid Set_y_Location(GLdouble input_y_location);
	GLvoid Set_z_Location(GLdouble input_z_location);

	GLdouble Get_x_Location(GLvoid);
	GLdouble Get_y_Location(GLvoid);
	GLdouble Get_z_Location(GLvoid);

	GLvoid Set_Scale(GLdouble input_scale);
	GLdouble Get_Scale(GLvoid);

	GLvoid Alter_Angle(std::pair<GLint,GLint> position_x, std::pair<GLint,GLint> position_y);
};
