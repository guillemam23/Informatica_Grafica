
#include "camera.h"

camera::camera(vec3 position, vec3 direction, GLfloat sensitivity, GLfloat fov)
{
	cameraPos = position;
	cameraFront = direction;
	Sensitivity =	sensitivity;
	FOV = fov;

	vec3 cameraDirection = normalize(cameraPos - cameraFront);
	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	vec3 cameraRight = normalize(cross(up, cameraDirection));
	cameraUp = cross(cameraDirection, cameraRight);

}

void camera::DoMovement(GLFWwindow * window){
	bool TeclaW = false;
	bool TeclaS = false;
	bool TeclaA = false;
	bool TeclaD = false;

	if (glfwGetKey(window, GLFW_KEY_W)) {
		TeclaW = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		TeclaS = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		TeclaA = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		TeclaD = true;
	}

	if (TeclaW) {
		cameraPos.z = cameraPos.z - 0.1f;
		TeclaW = false;
	}
	if (TeclaS) {
		cameraPos.z = cameraPos.z + 0.1f;
		TeclaS = false;
	}
	if (TeclaA) {
		cameraPos.x = cameraPos.x - 0.1f;
		TeclaA = false;
	}
	if (TeclaD) {
		cameraPos.x = cameraPos.x + 0.1f;
		TeclaD = false;
	}
}

void camera::MouseMove(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		LastMx = xpos;
		LastMy = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - LastMx;
	GLfloat yoffset = LastMy - ypos;
	LastMx = xpos;
	LastMy = ypos;

	xoffset *= Sensitivity;
	yoffset *= Sensitivity;

	YAW += xoffset;
	PITCH += yoffset;

	if (PITCH > 89.0f)
		PITCH = 89.0f;
	if (PITCH < -89.0f)
		PITCH = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
	front.y = sin(glm::radians(PITCH));
	front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
	cameraFront = glm::normalize(front);
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
	return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);;
}

GLfloat camera::GetFOV()
{
	return FOV;
}

camera::~camera()
{
}
