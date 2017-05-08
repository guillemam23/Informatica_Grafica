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
#include "camera.h"
#include "Object.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "SOIL.h"

using namespace std;
using namespace glm;

bool WIREFRAME = false;
int screenWithd, screenHeight;

bool TeclaUp = false;
bool TeclaDown = false;
bool TeclaRight = false;

bool Tecla2 = false;
bool Tecla4 = false;
bool Tecla6 = false;
bool Tecla8 = false;

bool TeclaLeft = false;
bool Key1 = false;
bool Key2 = false;

GLfloat lastX = 400, lastY = 400;
GLfloat fov = 45.0f;

vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
GLfloat sensitivity = 0.05f;
vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);

vec3 lightPos(1.2f, 0.0f, 2.0f);


void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void DoMovement(GLFWwindow* window);

//Variables para el movimiento de la camara

camera Camara(cameraPos, cameraTarget, sensitivity, fov);

//vec3 escalado = vec3(0.0f, 0.0f, 0.0f);
//vec3 rotado = vec3(0.0f, 0.0f, 0.0f);
//vec3 posicion = vec3(0.0f, 0.0f, 0.0f);
//
//Object cubo (escalado, rotado, posicion, Object::cube);

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

	glfwSetScrollCallback(window, scroll_callback);

	//que funcion se llama cuando se detecta una pulsaci�n de tecla en la ventana x
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	DoMovement(window);
	//cargamos los shader

	shader shaderLamp("./src/LightVertex.vertexshader", "./src/LightFragment.fragmentshader");
	shader shader("./src/LightVertex.vertexshader", "./src/LightFragment.fragmentshader");


	// Definir el buffer de vertices (shader modificado)

	GLfloat VertexBufferObject[] = {
		//front
		1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		1.0f , -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		//back
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		1.0f , -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		1.0f ,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		1.0f ,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		//left
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		//right
		1.0f , -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		1.0f ,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		1.0f ,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		1.0f ,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		1.0f , -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		1.0f , -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		//down
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		1.0f , -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		1.0f , -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		1.0f , -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		//up
		1.0f ,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		1.0f ,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		1.0f ,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f

	};

	vec3 CubesPositionBuffer[] = {
		vec3(0.0f ,  0.0f,  0.0f),
		/*vec3(1.0f ,  5.0f, -1.0f),
		/*vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f , -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f , -2.0f, -2.5f),
		vec3(1.5f ,  2.0f, -2.5f),
		vec3(1.5f ,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)*/
	};

	glfwGetTime();

	// Crear los VBO, VAO y EBO

	GLuint VBO;
	GLuint VAO;

	//reservar memoria para el VAO, VBO y EBO

	glGenBuffers(1, &VBO);
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

	//Declarar el VBO y el EBO

	//Enlazar el buffer con openGL
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Alocamos memoria suficiente para almacenar 4 grupos de 3 floats (segundo parámetro) (VBO)
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

	//Alocamos ahora el EBO()

	//Buffer de posicion

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//// Buffer de textura

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	//Activar el z-buffer

	glEnable(GL_DEPTH_TEST);

	//liberar el buffer de vertices
	glBindVertexArray(0);

	//CAMARA

	//Posicion de la camara
	//Dirección de la camara

	//Vector RIGHT

	//Vector UP
	//vec3 cameraUp = cross(cameraDirection, cameraRight);

	//Matriz look at

	mat4 view;

	GLfloat camX = 0.0f;
	GLfloat camZ = 3.0f;

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO, the container's VBO's data already contains the correct data.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for our lamp)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	//Bucle de dibujado 
	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		DoMovement(window);
		glfwSetCursorPosCallback(window, mouse_callback);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*	if (WIREFRAME == true) {

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
*/
		//Activar textura
		projection = perspective(Camara.GetFOV(), (GLfloat)screenWithd / (GLfloat)screenHeight, 0.1f, 1000.f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shader.Program, "Texture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "Texture2"), 1);

		glUniform1f(glGetUniformLocation(shader.Program, "Opacidad"), Opacidad);

		GLfloat angleX;
		GLfloat angleY;

		mat4 model;
		mat4 view;
		
		view = translate(view, vec3(0.0f, 0.0f, -3.0f));

		//MOVIMIENTO MEDIANTE FLECHAS

		if (TeclaUp) {
			y += 0.1f;
			TeclaUp = false;
		}
		if (TeclaDown) {
			y -= 0.1f;
			TeclaDown = false;
		}

		if (TeclaLeft) {
			x -= 0.1f;
			TeclaLeft = false;
		}
		if (TeclaRight) {
			x += 0.1f;
			TeclaRight = false;
		}


		//ROTACION

		if (Tecla2) {
			angleX += 5.0f;
			Tecla2 = false;
		}
		if (Tecla4) {
			angleY -= 5.0f;
			Tecla4 = false;
		}

		if (Tecla6) {
			angleY += 5.0f;
			Tecla6 = false;
		}
		if (Tecla8) {
			angleX -= 5.0f;
			Tecla8 = false;
		}

		vec3 move = vec3(x, y, z);
		model = translate(model, move);
	
		model = rotate(model, angleX, vec3(1.0f, 0.0f, 0.0f));
		model = rotate(model, angleY, vec3(0.0f, 1.0f, 0.0f));


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

		//Camara

		GLfloat radius = 10.0f;
		/*GLfloat camX = sin(glfwGetTime()*3) * radius;
		GLfloat camZ = cos(glfwGetTime()*3) * radius;*/

		cameraPos = vec3(camX, 0.f, camZ);

		GLint objectColorLoc = glGetUniformLocation(shader.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(shader.Program, "lightColor");
		glUniform3f(objectColorLoc, 0.8f, 0.4f, 1.0f);
		glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f);

		view = Camara.LookAt();

		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");;
		GLint projLoc = glGetUniformLocation(shader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

		glBindVertexArray(VAO);
		//glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		shaderLamp.Use();

		modelLoc = glGetUniformLocation(shaderLamp.Program, "model");
		viewLoc = glGetUniformLocation(shaderLamp.Program, "view");
		projLoc = glGetUniformLocation(shaderLamp.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		//Carga de 10 cubos

		/*for (int i = 1; i < 10; i++) {

			mat4 model;

			model = translate(model, CubesPositionBuffer[i]);
			model = rotate(model, (GLfloat)glfwGetTime()*5.0f, vec3(0.5f, 1.0f, 0.0f));

			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(model));

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawArrays(GL_TRIANGLES, 0, 36);


		}*/

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

	glfwDestroyWindow(window);
	glfwTerminate();
	std::exit(EXIT_SUCCESS);
}


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void DoMovement(GLFWwindow* window) {
	Camara.DoMovement(window);

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

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) Key1 = true;

	//if (key == GLFW_KEY_2 && action == GLFW_PRESS) Key2 = true;


	if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS) Tecla2 = true;

	if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS) Tecla4 = true;

	if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS) Tecla6 = true;

	if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS) Tecla8 = true;
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	Camara.MouseMove(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	Camara.MouseScroll(window, xoffset, yoffset);

}