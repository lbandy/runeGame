#ifndef CORE_H
#define CORE_H

class Core
{
private:
	bool running;
	SDL_Surface* loadingSurface;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

public:

	bool OnInit();

	void OnEvent(SDL_Event* Event);

	void OnLoop();

	void OnRender();

	void OnCleanup();

	int OnExecute();

	Core();
};
#endif