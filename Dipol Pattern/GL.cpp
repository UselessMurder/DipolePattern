#include "GL.h"
#include <chrono>

 


GL::GL()
{
	output = NULL;
	hRC = NULL;
	hDC = NULL;
	PixelFormat = 0;
	output_true = false;
	head.x = 0;
	head.y = 0;
	head.z = -1;
	view_angle.x_increment = 0;
	view_angle.x_decrement = 0;
	view_angle.y_increment = 0;
	view_angle.y_decrement = 0;
	view_angle.z_increment = 0;
	view_angle.z_decrement = 0;
	scale = 0;
}
GL::~GL()
{
	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
			MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		if (!wglDeleteContext(hRC))
			MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hRC = NULL;
	}
	if (hDC && !ReleaseDC(output, hDC))
	{
		MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}
	glDeleteLists(base, 96);
}

GLint GL::Init_GL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	Build_Font();
	glEnable(GL_COLOR_MATERIAL);
	return TRUE;
}

GLvoid GL::Build_Font(GLvoid)
{
	HFONT  font;
	base = glGenLists(256);
	font = CreateFont(-32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, L"Comic Sans MS");
	SelectObject(hDC, font);
	wglUseFontBitmaps(hDC, 32, 96, base);
}


GLvoid GL::Resize_GL_Scene(GLsizei width, GLsizei height)
{
	if (output_true)
	{
		if (height == 0)
			height = 1;
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

GLboolean GL::Start_GL(HWND input_output, GLsizei width, GLsizei height)
{
	output = input_output;
	static  PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1 , PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };
	if (!(hDC = GetDC(output)))
		return false;
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
		return false;
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
		return false;
	if (!(hRC = wglCreateContext(hDC)))
		return false;
	if (!wglMakeCurrent(hDC, hRC))
		return false;
	output_true = true;
	this->Resize_GL_Scene(width, height);
	if (!this->Init_GL())
		return false;
	return true;
}

GLvoid GL::Print_Text(const char *fmt, ...)
{
	char text[256];
	va_list ap;

	if (fmt == NULL)
		return;
	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
	glListBase(base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}



GLvoid GL::Draw_Vector(Vertex begin, Vertex end, Red_Green_Blue color, GLdouble width, const char *txt)
{
	begin.x *=  pow(10, scale); begin.y *= pow(10, scale); begin.z *= pow(10, scale);
	end.x *= pow(10, scale); end.y *= pow(10, scale); end.z *= pow(10, scale);

	Vertex base;
	
	base.x = end.x - (end.x - begin.x) * 0.2;
	base.y = end.y - (end.y - begin.y) * 0.2;
	base.z = end.z - (end.z - begin.z) * 0.2;

	GLdouble r = sqrt(pow(end.x - base.x, 2) + pow(end.y - base.y, 2) + pow(end.z - base.z, 2));

	
	glLineWidth(width);

	glBegin(2);
	glColor3d(color.red, color.green, color.blue);
	glVertex3d(begin.x, begin.y, begin.z);
	glVertex3d(end.x, end.y, end.z);
	glEnd();

	glLineWidth(1);

	glRasterPos3d(end.x + r, end.y + r, end.z + r);
	this->Print_Text(txt, 0);

	glColor3d(color.red, color.green, color.blue);


	GLdouble N = 16;
	GLdouble R = r / 2;
	for (GLdouble i = 0, j = N; i < N; i++, j--)
	{
		GLdouble x = end.x + (end.x - base.x) * i / N;
		GLdouble y = end.y + (end.y - base.y) * i / N;
		GLdouble z = end.z + (end.z - base.z) * i / N;
		glTranslated(x, y, z);
		glutSolidSphere(R * j / N, 5, 5);
		glTranslated(-x, -y, -z);
	}
}


GLint GL::Draw_GL_Scene(std::vector<Vertex> &electric_field_line, std::vector<Vertex> &magnetic_field_line, std::pair<Vertex, Vertex> Etheta,  std::pair<Vertex, Vertex> Hphi)
{
	if (output_true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluPerspective(45.0f, 0, 0, INFINITE);
		glTranslated(head.x, head.y, head.z);

		glRotated(view_angle.x_increment, 0, 1, 0);
		glRotated(view_angle.x_decrement, 0, -1, 0);
		glRotated(view_angle.y_increment, 1, 0, 0);
		glRotated(view_angle.y_decrement, -1, 0, 0);
		glRotated(view_angle.z_increment, 0, 0, 1);
		glRotated(view_angle.z_decrement, 0, 0, -1);

		Vertex begin_axis;
		Vertex end_axis;
		Red_Green_Blue color;
		color.red = 1; color.green = 1; color.blue = 0;
		begin_axis.x = 0; begin_axis.y = 0; begin_axis.z = 0;
		end_axis.x = 1.3; end_axis.y = 0; end_axis.z = 0;
		Draw_Vector(begin_axis, end_axis, color, 5 ,"X");
		end_axis.x = 0; end_axis.y = 1.3; end_axis.z = 0;
		Draw_Vector(begin_axis, end_axis, color, 5, "Y");
		end_axis.x = 0; end_axis.y = 0; end_axis.z = 1.3;
		Draw_Vector(begin_axis, end_axis, color, 5,"Z");

		glColor3d(0, 1, 0);
		for (unsigned int i = 0; i < electric_field_line.size();)
		{
			glBegin(2);
			for (unsigned int j = 0; j < 63 && i < electric_field_line.size(); j++ , i++)
				glVertex3d(electric_field_line[i].x * pow(10, scale), electric_field_line[i].y * pow(10, scale), electric_field_line[i].z * pow(10, scale));
			glEnd();
		}

		
		glColor3d(0, 1, 0);
		for (unsigned int i = 0; i < magnetic_field_line.size();)
		{
			glBegin(2);
			for (unsigned int j = 0; j < 63 && i < electric_field_line.size(); j++, i++)
				glVertex3d(magnetic_field_line[i].x * pow(10, scale), magnetic_field_line[i].y * pow(10, scale), magnetic_field_line[i].z * pow(10, scale));
			glEnd();
		}
		Red_Green_Blue rgb;
		rgb.red = 1; rgb.green = 0; rgb.blue = 0;
		this->Draw_Vector(Etheta.first, Etheta.second, rgb, 20, "E");
		rgb.red = 0; rgb.green = 0; rgb.blue = 1;
		this->Draw_Vector(Hphi.first, Hphi.second, rgb, 20, "H");
	}
	SwapBuffers(hDC);
	return TRUE;
}

GLvoid GL::Set_x_Location(GLdouble input_x_location)
{
	head.x = input_x_location;
}
GLvoid GL::Set_y_Location(GLdouble input_y_location)
{
	head.y = input_y_location;
}
GLvoid GL::Set_z_Location(GLdouble input_z_location)
{
	head.z = input_z_location;
}


GLdouble GL::Get_x_Location(GLvoid)
{
	return head.x;
}
GLdouble GL::Get_y_Location(GLvoid)
{
	return head.y;
}
GLdouble GL::Get_z_Location(GLvoid)
{
	return head.z;
}

GLvoid GL::Alter_x_Angle(GLboolean add, GLint old_position, GLint new_position)
{
	if (add)
		for (int i = 0; i < new_position - old_position; i++)
			view_angle.x_increment += 0.2;
	else
		for (int i = 0; i < old_position - new_position; i++)
			view_angle.x_decrement += 0.2;
}

GLvoid GL::Alter_y_Angle(GLboolean add, GLint old_position, GLint new_position)
{
	if (add)
		for (int i = 0; i < new_position - old_position; i++)
			view_angle.y_increment += 0.2;
	else
		for (int i = 0; i < old_position - new_position; i++)
			view_angle.y_decrement += 0.2;
}

GLvoid GL::Alter_z_Angle(GLboolean add, GLint old_position, GLint new_position)
{
	if (add)
		for (int i = 0; i < new_position - old_position; i++)
			view_angle.z_increment += 0.2;
	else
		for (int i = 0; i < old_position - new_position; i++)
			view_angle.z_decrement += 0.2;
}

GLvoid GL::Alter_Angle(std::pair<GLint, GLint> position_x, std::pair<GLint, GLint> position_y)
{
	int x_status = 0;
	int y_status = 0;
	if (position_x.first < position_x.second)
		x_status = 1;
	if (position_x.first > position_x.second)
		x_status = -1;
	if (position_y.first < position_y.second)
		y_status = 1;
	if (position_y.first > position_y.second)
		y_status = -1;
	/*if (x_status > 0 && y_status > 0)
		this->Alter_z_Angle(true, (position_x.first + position_y.first) , (position_x.second - position_y.second));*/
	/*if (x_status > 0 && y_status < 0)
		this->Alter_z_Angle(false, (position_x.second - position_x.first) + (position_y.first - position_y.second));
	if (x_status < 0 && y_status > 0)
		this->Alter_z_Angle(true, (position_x.first - position_x.second) + (position_y.first - position_y.second));
	if (x_status < 0 && y_status < 0)
		this->Alter_z_Angle(true, (position_x.first - position_x.second) + (position_y.first - position_y.second));*/
	if (x_status > 0)
		this->Alter_x_Angle(true, position_x.first, position_x.second);
	if (x_status < 0)
		this->Alter_x_Angle(false, position_x.first, position_x.second);
	if (y_status > 0)
		this->Alter_y_Angle(true, position_y.first, position_y.second);
	if (y_status < 0)
		this->Alter_y_Angle(false, position_y.first, position_y.second);
}

GLvoid GL::Set_Scale(GLdouble input_scale)
{
	scale = input_scale;
}

GLdouble GL::Get_Scale(GLvoid)
{
	return scale;
}