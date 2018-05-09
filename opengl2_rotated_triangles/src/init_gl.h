#pragma once

void InitGLFW();

bool InitGLEW();

GLFWwindow* CreateGLWindow(int width = 800, int height = 600);

void ReleaseGLFW();
