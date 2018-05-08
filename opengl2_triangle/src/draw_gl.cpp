#include "extern.h"
#include "draw_gl.h"
#include "common.h"

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
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// close window if ESC key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	// switch color
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		print_text("Switch color");
		CurrentColor == violet ? CurrentColor = pink : CurrentColor = violet;
	}
}

namespace shaders {
	const GLchar vertexShaderSource[] = "#version 330 core\n"
			"layout (location = 0) in vec3 position;\n"
			"void main() {\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"}\0";
	const GLchar* fragmentShaderSourceYellow = "#version 330 core\n"
			"out vec4 color;\n"
			"void main() {\n"
			"color = vec4(1.0f, 1.0f, 0.1f, 1.0f);\n"
			"}\0";
	const GLchar* fragmentShaderSourceGreen = "#version 330 core\n"
			"out vec4 color;\n"
			"void main() {\n"
			"color = vec4(0.1f, 1.0f, 0.1f, 1.0f);\n"
			"}\0";
}

bool checkShader(GLuint shader)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		print_text("ERROR::SHADER::COMPILATION_FAILED");
		print_text(infoLog);
		return false;
	}
	return true;
}

GLuint createShaders(GLenum shaderType, const GLchar* shaderSource)
{
	GLuint shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	checkShader(shader);
	return shader;
}

bool checkProgram(GLuint shaderProgram)
{
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		print_text("ERROR::SHADER_PROGRAM::COMPILATION_FAILED");
		print_text(infoLog);
		return false;
	}
	return true;
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	return shaderProgram;
}

GLuint prepareShaderProgram()
{
	GLuint vertexShader = createShaders(GL_VERTEX_SHADER, shaders::vertexShaderSource);
	GLuint fragmentShader = createShaders(GL_FRAGMENT_SHADER, shaders::fragmentShaderSourceYellow);

	GLuint shaderProgram = createProgram(vertexShader, fragmentShader);
	checkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

GLuint prepareTriangle()
{
	GLfloat vertices[] = {
			-0.9f, -0.5f, 0.0f,
			-0.0f, -0.5f, 0.0f,
			-0.45f, 0.5f, 0.0f,
			0.0f, -0.5f, 0.0f,
			0.9f, -0.5f, 0.0f,
			0.45f, 0.5f, 0.0f
	};

	GLuint VAO; // vertex arrays object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO; // vertex buffer objects
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return VAO;
}

void Draw(GLFWwindow* window)
{
	print_text("Draw color window;");
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLuint shaderProgram = prepareShaderProgram();
	GLuint VAO = prepareTriangle();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwSetKeyCallback(window, keyCallback);

		glClearColor(CurrentColor.red, CurrentColor.green, CurrentColor.blue, CurrentColor.alpha);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
}
