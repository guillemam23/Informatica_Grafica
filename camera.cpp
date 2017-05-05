#include "camera.h"


camera::camera(vec3 position, vec3 direction, GLfloat sensitivity, GLfloat fov)
{
}

void camera::DoMovement(GLFWwindow * window)
{
}

void camera::MouseMove(GLFWwindow * window, double xpos, double ypos)
{
}

void camera::MouseScroll(GLFWwindow * window, double xScroll, double yScroll)
{
	if (FOV >= 1.0f && FOV <= 45.0f)
		FOV -= yScroll;
	if (FOV <= 1.0f)
		FOV = 1.0f;
	if (FOV >= 45.0f)
		FOV = 45.0f;
}

mat4 camera::LookAt()
{
	return mat4();
}

GLfloat camera::GetFOV()
{
	return FOV;
}

camera::~camera()
{
}
