#ifndef CORE_H
#define CORE_H

class Core
{
private:
	bool running;
	SDL_Surface* loadingSurface;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture *background, *table, *points, *timer, *girl;
	SDL_Rect tableS, pointsS, timerS, girlS, tableD, pointsD, timerD, girlD;

	SDL_Texture* runeTex[10];
	SDL_Rect runePos[45];
	SDL_Rect movingRunePos[45];
	int runes[45];
	int tableSizeX, tableSizeY, runeSizeX, runeSizeY, startIndex, endIndex;

	std::vector<int> clearRunes;

	int runeTargetX[45];
	int runeTargetY[45];
	int runeTargetSteps[45];

	int animationState;
	bool matchMade, match1, match2, moving, lastMoved;

	int initialDistance;

public:

	bool OnInit();

	void OnEvent(SDL_Event* Event);

	void OnLoop();

	void OnRender();

	void OnCleanup();

	int OnExecute();

	bool CheckMatches(int index);

	void MoveRune(int source, int dest);

	int GetClickedRune(int mouseX, int mouseY);

	void StartDrag(int index);

	void EndDrag(int index);

	void ClearMatchedRunes();

	void MoveRunes();

	int FindNextRune(int index);

	void SpawnRunes(int index, int count);

	void SetRuneTarget(int index, int startX, int startY, int targetX, int targetY, int speed);
	
	void AnimationReady();

	void MatchResults();

	void FlipRunes(int index1, int index2, int speed);

	Core();
};
#endif