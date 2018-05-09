#include "extern.h"
#include "init_gl.h"
#include "common.h"

void InitGLFW()
{
	print_text("Init GLFW");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

bool InitGLEW()
{
	print_text("Init GLEW");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		print_text("Failed to initialize GLEW");
		return false;
	}
	return true;
}

GLFWwindow* CreateGLWindow(int width, int height)
{
	print_text("Create GLFW window");
	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		print_text("Failed to create GLFW window");
		ReleaseGLFW();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	return window;
}

void ReleaseGLFW()
{
	print_text("Release resources");
	glfwTerminate();
}
