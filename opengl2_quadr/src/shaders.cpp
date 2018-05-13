#include "extern.h"
#include "shaders.h"
#include "common.h"

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
	const GLchar* fragmentShaderSourceDefault = "#version 330 core\n"
			"out vec4 color;\n"
			"void main() {\n"
			"color = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
			"}\0";
}

Shader::Shader(GLenum shaderType, const GLchar* shaderSource) {
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	checkShader(shader);
	std::cout << shader << std::endl;
}

Shader::~Shader() {
	glDeleteShader(shader);
}

void Shader::checkShader(GLuint shader) {
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		print_text("ERROR::SHADER::COMPILATION_FAILED");
		print_text(infoLog);
	}
}


ShaderProgram::ShaderProgram(TShaderColor shaderColor) {
	Shader vertexSh(GL_VERTEX_SHADER, shaders::vertexShaderSource);
	Shader fragmentSh(GL_FRAGMENT_SHADER, getShaderColor(shaderColor));

	shaderProgram = createProgram(vertexSh.GetShader(), fragmentSh.GetShader());
	checkProgram(shaderProgram);
}

const GLchar* ShaderProgram::getShaderColor(TShaderColor shaderColor) const {
	switch (shaderColor) {
	case TShaderColor::SC_GREEN:
		return shaders::fragmentShaderSourceGreen;
		break;
	case TShaderColor::SC_YELLOW:
		return shaders::fragmentShaderSourceYellow;
		break;
	default:
		;
	}
	return shaders::fragmentShaderSourceDefault;
}

GLuint ShaderProgram::createProgram(GLuint vertexShader, GLuint fragmentShader) {
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	return shaderProgram;
}

void ShaderProgram::checkProgram(GLuint shaderProgram) {
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		print_text("ERROR::SHADER_PROGRAM::COMPILATION_FAILED");
		print_text(infoLog);
	}
}
