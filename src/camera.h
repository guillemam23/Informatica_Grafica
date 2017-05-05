#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;
const GLint WIDTH = 800, HEIGHT = 800;

class camera
{
private:
		vec3 cameraPos;
		vec3 cameraFront;
		vec3 cameraUp;
		GLfloat Deltatime = glfwGetTime();
		GLfloat Lastframe;
		GLfloat LastMx = WIDTH /2.0f;
		GLfloat LastMy = HEIGHT / 2.0f;
		GLfloat Sensitivity;
		GLboolean firstMouse;
		GLfloat YAW = -90.0f;
		GLfloat PITCH = 0.0f;
		GLfloat FOV;

public:
	camera(vec3 position, vec3 direction, GLfloat sensitivity, GLfloat fov);
	void DoMovement(GLFWwindow * window);
	void MouseMove(GLFWwindow* window, double xpos, double ypos);
	void MouseScroll(GLFWwindow* window, double xScroll, double yScroll);
	mat4 LookAt();
	GLfloat GetFOV();
	~camera();
};

