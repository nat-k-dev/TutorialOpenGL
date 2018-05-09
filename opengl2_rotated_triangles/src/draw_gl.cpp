#include "extern.h"
#include "draw_gl.h"
#include "common.h"
#include "shaders.h"

namespace {
	struct TColor {
		GLclampf red;
		GLclampf green;
		GLclampf blue;
		GLclampf alpha;
	};

	const TColor violet{0.8f, 0.1f, 0.9f, 1.0f};
	const TColor pink{0.8f, 0.1f, 0.1f, 1.0f};
	TColor CurrentColor = violet;

	inline bool operator==(const TColor& lhs, const TColor& rhs) {
		return lhs.red == rhs.red &&
				lhs.green == rhs.green &&
				lhs.blue == rhs.blue &&
				lhs.alpha == rhs.alpha;
	}
	GLuint CurrentVAO; // vertex arrays object
	GLfloat vertices[] = {
			-0.9f, -0.5f, 0.0f,
			-0.0f, -0.5f, 0.0f,
			-0.45f, 0.5f, 0.0f,
			0.0f, -0.5f, 0.0f,
			0.9f, -0.5f, 0.0f,
			0.45f, 0.5f, 0.0f
	};

}

void prepareTriangle(GLuint& VAO) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO; // vertex buffer objects
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// close window if ESC key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	// switch color and rotate triangles
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		print_text("Switch color");
		CurrentColor == violet ? CurrentColor = pink : CurrentColor = violet;

		print_text("Rotate");
		for (size_t i = 0; i < sizeof(vertices)/sizeof(GLfloat); ++i) {
			if ((i + 1) % 3 == 0)
				continue;
			GLfloat newValue1 = vertices[i] * 0 + vertices[i+1] * -1;
			GLfloat newValue2 = vertices[i] * 1 + vertices[i+1]*0;
			vertices[i] = newValue1;
			vertices[i+1] = newValue2;
			++i;
		}
		prepareTriangle(CurrentVAO);
	}
}

void Draw(GLFWwindow* window)
{
	print_text("Draw color window;");
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	ShaderProgram shaderProgram;

	prepareTriangle(CurrentVAO);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwSetKeyCallback(window, keyCallback);

		glClearColor(CurrentColor.red, CurrentColor.green, CurrentColor.blue, CurrentColor.alpha);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram.GetShaderProgram());
		glBindVertexArray(CurrentVAO);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(GLfloat)/3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &CurrentVAO);
}
