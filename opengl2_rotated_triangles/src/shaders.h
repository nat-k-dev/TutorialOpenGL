#pragma once


class Shader {
public:
	Shader(GLenum shaderType, const GLchar* shaderSource);
	~Shader();

	const GLuint& GetShader() const
		{ return shader; }
private:
	void checkShader(GLuint shader);

private:
	GLuint shader;
};

class ShaderProgram {
public:
	ShaderProgram();

	GLuint GetShaderProgram() const
		{ return shaderProgram; }

private:
	void checkProgram(GLuint shaderProgram);
	GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

private:
	GLuint shaderProgram;
};

