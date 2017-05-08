
#include "Object.h"

Object::Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef) {

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
}
//
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &VAO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//}
//
//
//Object::~Object() {}
//
//void Object::Draw() {
//
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//}
//void Object::Move(vec3 translation, GLFWwindow * window) {
//
//	bool TeclaW = false;
//	bool TeclaS = false;
//	bool TeclaA = false;
//	bool TeclaD = false;
//
//	if (glfwGetKey(window, GLFW_KEY_W)) {
//		TeclaW = true;
//	}
//	if (glfwGetKey(window, GLFW_KEY_S)) {
//		TeclaS = true;
//	}
//	if (glfwGetKey(window, GLFW_KEY_A)) {
//		TeclaA = true;
//	}
//	if (glfwGetKey(window, GLFW_KEY_D)) {
//		TeclaD = true;
//	}
//	if (TeclaW) {
//		translation.z = translation.z - 0.1f;
//		TeclaW = false;
//	}
//	if (TeclaS) {
//		translation.z = translation.z + 0.1f;
//		TeclaS = false;
//	}
//	if (TeclaA) {
//		translation.x = translation.x - 0.1f;
//		TeclaA = false;
//	}
//	if (TeclaD) {
//		translation.x = translation.x + 0.1f;
//		TeclaD = false;
//	}
//}
//void Object::Rotate(vec3 rota) {
//
//	bool Tecla2 = false;
//	bool Tecla4 = false;
//	bool Tecla6 = false;
//	bool Tecla8 = false;
//
//	if (Tecla2) {
//		rota.x = rota.x - 5.0f;
//		Tecla2 = false;
//	}
//	if (Tecla4) {
//		rota.x = rota.x + 5.0f;
//		Tecla4 = false;
//	}
//
//	if (Tecla6) {
//		rota.y = rota.y - 5.0f;
//		Tecla6 = false;
//	}
//	if (Tecla8) {
//		rota.y = rota.y + 5.0f;
//		Tecla8 = false;
//	}
//}
////void Object::Scale(vec3 scal) {
////}
////
////mat4 Object::GetModelMatrix() {
////
////}
////
////vec3 Object::GetPosition() {
////
////}
////
////void Object::Delete() {
////
////}