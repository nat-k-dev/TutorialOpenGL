#include "extern.h"
#include "init_gl.h"
#include "draw_gl.h"

int main()
{
	InitGLFW();

	GLFWwindow* window = CreateGLWindow();
	if (window == nullptr)
		return -1;

	if (!InitGLEW())
		return -1;

	Draw(window);

	ReleaseGLFW();

	return 0;
}
