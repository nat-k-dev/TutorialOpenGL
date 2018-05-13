#pragma once

enum class TShaderColor {
	SC_GREEN,
	SC_YELLOW
};


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
	ShaderProgram(TShaderColor shaderColor);

	GLuint GetShaderProgram() const
		{ return shaderProgram; }

private:
	void checkProgram(GLuint shaderProgram);
	GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
	const GLchar* getShaderColor(TShaderColor shaderColor) const;

private:
	GLuint shaderProgram;
};

