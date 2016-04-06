#include <GL\glew.h>
#include <iostream>
#include <chrono>
#include <Windows.h>
#include <SDL\SDL.h>
#include "Game.h"
#include "Input.h"

using namespace std;

int screen_width = 1080;
int screen_height = 720;

void initWindow(SDL_Window* window) {
	window = SDL_CreateWindow("Try hard!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
		std::cout << "SDLFEL";
	GLenum error = glewInit();
	if (error != GLEW_OK)
		std::cout << "GlewFel!";
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.7f, 0.7f, 1.0f, 1.0);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = nullptr;
	initWindow(window);
	chrono::milliseconds timeStamp = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	chrono::milliseconds timeStamp2;
	long long dt = timeStamp.count();
	bool running = true;

	Input input;

	Game game;

	while (running)
	{
		timeStamp2 = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
		dt = timeStamp2.count() - timeStamp.count();
		timeStamp = timeStamp2;

		running = input.update();

		if( input.keyPressed( SDLK_ESCAPE ) )
			running = false;
	}
	return 0;
}