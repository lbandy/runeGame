#include "stdafx.h"


bool Core::OnInit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	mainWindow = SDL_CreateWindow("Core Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	return true;
}

void Core::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_QUIT) {
		running = false;
	}

	else if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "Current event type: MOUSE_BUTTON_DOWN	\n";
	}

	else if(event->type == SDL_MOUSEBUTTONUP)
	{
		std::cout << "Current event type: MOUSE_BUTTON_UP	\n";
	}

	else if(event->type == SDL_MOUSEMOTION)
	{
		std::cout << "Current event type: MOUSE_MOTION	\n";
	}
}

void Core::OnLoop()
{
}

void Core::OnRender()
{
	SDL_RenderPresent(mainRenderer);
}

void Core::OnCleanup()
{
	/*
		set all surface and other pointers to NULL
	*/
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}

Core::Core()
{
	running = true;
}

int Core::OnExecute() {
	if(OnInit() == false) {
		return -1;
	}

	float frameRate = 60;
	float ticksToSkip = 1000 / frameRate;
	int lastTick = SDL_GetTicks();
	int tickCount = 0;

	SDL_Event Event;

	while(running) {
		while(SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}

		// frame-rate control
		tickCount = SDL_GetTicks();
		if (tickCount - lastTick < ticksToSkip) continue;
		lastTick = tickCount;

		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;
}