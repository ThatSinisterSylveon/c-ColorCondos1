#include "Engine.h"
#include <iostream>
#include "IO/mouse.h"
using namespace std;

int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow* Engine::window = NULL; 
Engine::Engine(){
    
}
Engine::~Engine(){
    
}

bool Engine::Initialize(char* windowTitle){
    if(!glfwInit()){
	cout << "error initializing glfw" << endl;
	return false;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);
    if (window == NULL){
	cout << "Error creating window" << endl;
	return false;
    }

    //GLFW setup
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSwapInterval(1);

    glfwSetCursorPosCallback(window, Mouse::MousePosCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (mode->width - SCREEN_WIDTH) / 2;
    int yPos = (mode->height - SCREEN_HEIGHT) / 2;
    glfwSetWindowPos(window, xPos, yPos);

    //OpenGL setup
    //Viewport
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();glOrtho(0, width, 0, height, -10, 10);
    glDepthRange(-10, 10);
    glMatrixMode(GL_MODELVIEW);

    //Aplha Blending
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true; 
}

void Engine::Update(){
    glfwPollEvents();
}

void Engine::BeginRender(){
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndRender(){
    glfwSwapBuffers(window);
}

