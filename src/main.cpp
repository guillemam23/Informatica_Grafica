
//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW

#include <GLFW\glfw3.h>
#include <iostream>

//Shader

#include <string>
#include <fstream>
#include <sstream>
#include  <iostream>
#include "shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "SOIL.h"

using namespace std;
using namespace glm;

const GLint WIDTH = 800, HEIGHT = 800;
bool WIREFRAME = false;
int screenWithd, screenHeight;

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool TeclaUp = false;
bool TeclaDown = false;
bool TeclaRight = false;
bool TeclaLeft = false;
bool Key1 = false;
bool Key2 = false;

int main() {

	//initGLFW
	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	//comprobar que GLFW esta activo
	if (!glfwInit())
		std::exit(EXIT_FAILURE);

	//crear la ventana
	window = glfwCreateWindow(WIDTH, HEIGHT, "Informatica grafica", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);


	//que funcion se llama cuando se detecta una pulsaci�n de tecla en la ventana x
	glfwSetKeyCallback(window, key_callback);


	//cargamos los shader
	shader shader("./src/cubos_Vertex.vertexshader", "./src/cubos_Fragment.fragmentshader");

	// Definir el buffer de vertices (shader modificado)

	GLfloat VertexBufferCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vec3 CubesPositionBuffer[] = {
		vec3(0.0f ,  0.0f,  0.0f),
		vec3(2.0f ,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f , -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f , -2.0f, -2.5f),
		vec3(1.5f ,  2.0f, -2.5f),
		vec3(1.5f ,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	glfwGetTime();

	// Crear los VBO, VAO y EBO

	GLuint VBO;
	//GLuint EBO;
	GLuint VAO;

	//reservar memoria para el VAO, VBO y EBO

	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	glGenBuffers(1, &VAO);

	//Textura 1

	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image("./src/caja_tnt.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Textura 2

	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width2, height2;
	unsigned char* image2 = SOIL_load_image("./src/caja_madera.png", &width2, &height2, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 1);

	GLfloat Opacidad = 0.5;

	mat4 projection;
	projection = perspective(45.0f,(GLfloat)screenWithd/ (GLfloat)screenHeight, 0.1f, 1000.f);

	//Declarar el VBO y el EBO

	//Enlazar el buffer con openGL
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	//Alocamos memoria suficiente para almacenar 4 grupos de 3 floats (segundo parámetro) (VBO)
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferCube), VertexBufferCube, GL_STATIC_DRAW);

	//Alocamos ahora el EBO()
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);

	//Buffer de posicion

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Buffer de textura

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//Activar el z-buffer

	glEnable(GL_DEPTH_TEST);

	//liberar el buffer de vertices
	glBindVertexArray(0);

	//Bucle de dibujado (VENTANA)

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		glClearColor(0.6f, 0.6f, 1.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glViewport(0, 0, screenWithd, screenHeight);

		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(-10, 10, -10.f, 10.f, -1.0f, 10.f);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		//Establecer el shader
		//Shader::USE(programID);

		//glUseProgram(programID);

		if (WIREFRAME == true) {

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/*transformacion = scale(transformacion, vec3(0.5f, -0.5f, 0.f));
		transformacion = translate(transformacion, vec3(0.5f, 0.5f, 0.0f));
		transformacion = rotate(transformacion, angle, vec3(0.0f, 0.0f, 1.0f));*/

	/*	GLint transformacionlocation = glGetUniformLocation(shader.Program, "transformacion");
		glUniformMatrix4fv(transformacionlocation, 1, GL_FALSE, value_ptr(transformacion));*/

		//Activar textura

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shader.Program, "Texture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "Texture2"), 1);

		glUniform1f(glGetUniformLocation(shader.Program, "Opacidad"), Opacidad);

		GLfloat angleX;
		GLfloat angleY;

		//Modificación de la opacidad mediante las felchas

		if (TeclaUp) {
			angleX = angleX - 5.0f;
			TeclaUp = false;
		}
		if (TeclaDown) {
			angleX = angleX + 5.0f;
			TeclaDown = false;
		}

		if (TeclaLeft) {
			angleY = angleY - 5.0f;
			TeclaLeft = false;
		}
		if (TeclaRight) {
			angleY = angleY + 5.0f;
			TeclaRight = false;
		}

		if (Key1) {
			Opacidad = 1.0f;

			glUniform1f(glGetUniformLocation(shader.Program, "Opacidad"), Opacidad);
			Key1 = false;
		}
		if (Key2) {
			Opacidad = 0.0f;

			glUniform1f(glGetUniformLocation(shader.Program, "Opacidad"), Opacidad);
			Key2 = false;
		}

		shader.Use();

		mat4 model;
		mat4 view;
		model = rotate(model, angleX, vec3(0.5f, 0.0f, 0.0f));
		model = rotate(model, angleY, vec3(0.0f, 0.5f, 0.0f));

		view = translate(view, vec3(0.0f, 0.0f, -3.0f));

		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");;
		GLint projLoc = glGetUniformLocation(shader.Program, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//Carga de 10 cubos


		for (int i = 1; i < 10; i++) {

			mat4 model;

			model = translate(model, CubesPositionBuffer[i]);
			model = rotate(model, (GLfloat)glfwGetTime()*10.0f, vec3(0.5f, 1.0f, 0.0f));

			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(model));

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawArrays(GL_TRIANGLES, 0, 36);


		}




		// bind index buffer if you want to render indexed data
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// indexed draw call

		// Swap the screen buffers
		glfwSwapBuffers(window);
		//Event poll

	}

	// liberar la memoria de los VAO, EBO y VBO

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Terminate GLFW, clearing any resources allocated by GLFW.

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);
	glfwTerminate();
	std::exit(EXIT_SUCCESS);
}


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Cuando pulsamos la tecla ESC se cierra la aplicacion
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);


	if (key == GLFW_KEY_UP && action == GLFW_PRESS) TeclaUp = true;

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) TeclaDown = true;

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) TeclaRight = true;

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) TeclaLeft = true;

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		Key1 = true;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		Key2 = true;
	}
}