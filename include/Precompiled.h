#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#endif

#include <cstdlib>
#include <cstdio>

#include <fstream>
#include <string>
#include <vector>

#define GLFW_USE_DWM_SWAP_INTERVAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
