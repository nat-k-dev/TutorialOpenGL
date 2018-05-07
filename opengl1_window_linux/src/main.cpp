#define GLEW_STATIC
#include <iostream>
#include <string>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct TColor {
	GLclampf red;
	GLclampf green;
	GLclampf blue;
	GLclampf alpha;
};

const TColor violet{0.8f, 0.1f, 0.9f, 1.0f};
const TColor pink{0.8f, 0.1f, 0.1f, 1.0f};
TColor CurrentColor = violet;

bool operator==(const TColor& lhs, const TColor& rhs) {
	return lhs.red == rhs.red &&
			lhs.green == rhs.green &&
			lhs.blue == rhs.blue &&
			lhs.alpha == rhs.alpha;
}

void print_text(const std::string& text) {
	std::cout << text << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// close window if ESC key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	// switch color
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		print_text("Switch color");
		CurrentColor == violet ? CurrentColor = pink : CurrentColor = violet;
	}
}

int main() {
	print_text("Init GLFW");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	print_text("Create GLFW window");
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		print_text("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	print_text("Init GLEW");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		print_text("Failed to initialize GLEW");
		return -1;
	}

	print_text("Draw color window;");
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwSetKeyCallback(window, key_callback);

		glClearColor(CurrentColor.red, CurrentColor.green, CurrentColor.blue, CurrentColor.alpha);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	print_text("Release resources");
	glfwTerminate();
	return 0;
}
