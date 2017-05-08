
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
#include "shader.h"

class Object {

public:
	enum FigureType {
		cube = 0,
	};

	Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef);
	~Object();

	void Draw();
	void Move(vec3 translation, GLFWwindow * window);
	void Rotate(vec3 rota);
	/*void Scale(vec3 scal);
	void Delete();
	mat4 GetModelMatrix();
	vec3 GetPosition();*/

private:
	GLuint VBO, VAO, EBO;
	vec3 position;
	vec3 scale;
	vec3 rotation;
};
