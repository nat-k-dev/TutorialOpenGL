#include "extern.h"
#include "draw_gl.h"
#include "common.h"
#include "shaders.h"
#include <vector>

namespace {
	struct ColorEnum {
		GLclampf red;
		GLclampf green;
		GLclampf blue;
		GLclampf alpha;
	};

	const ColorEnum violet{0.8f, 0.1f, 0.9f, 1.0f};
	const ColorEnum pink{0.8f, 0.1f, 0.1f, 1.0f};
	ColorEnum CurrentColor = violet;

	inline bool operator==(const ColorEnum& lhs, const ColorEnum& rhs) {
		return lhs.red == rhs.red && lhs.green == rhs.green &&
				lhs.blue == rhs.blue && lhs.alpha == rhs.alpha;
	}

	GLuint CurrentVAO; // vertex arrays object
	GLuint CurrentEBO;

	std::vector<GLfloat> vertices = {
		     0.5f,  0.5f, 0.0f,  // Верхний правый угол
		     0.5f, -0.5f, 0.0f,  // Нижний правый угол
		    -0.5f, -0.5f, 0.0f,  // Нижний левый угол
		    -0.5f,  0.5f, 0.0f   // Верхний левый угол
		};
	std::vector<GLuint> indices = {
	    0, 1, 3,   // Первый треугольник
	    1, 2, 3    // Второй треугольник
	};

}

void prepareTriangle(GLuint& VAO) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &CurrentEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CurrentEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	GLuint VBO; // vertex buffer objects
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
		for (size_t i = 0; i < vertices.size(); ++i) {
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

	ShaderProgram shaderProgram(TShaderColor::SC_GREEN);
	//ShaderProgram shaderProgram(TShaderColor::SC_YELLOW);

	prepareTriangle(CurrentVAO);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwSetKeyCallback(window, keyCallback);

		glClearColor(CurrentColor.red, CurrentColor.green, CurrentColor.blue, CurrentColor.alpha);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram.GetShaderProgram());
		glBindVertexArray(CurrentVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &CurrentVAO);
}
