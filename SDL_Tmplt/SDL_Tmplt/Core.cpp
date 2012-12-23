#include "stdafx.h"


bool Core::OnInit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	moving = false;
	lastMoved = false;

	mainWindow = SDL_CreateWindow("Core Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1136, 640, SDL_WINDOW_SHOWN);
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	srand((unsigned)time(NULL));

	cDAT assets;
	char* buffer;

	assets.Read("assets.dat");

	/*	
	std::ifstream infile("assets.txt");
	std::string a;
	while (infile >> a)
	{
		buffer = assets.GetFile(a);
	}
	*/

	buffer = assets.GetFile("background.png");
	SDL_RWops *rw = SDL_RWFromMem(buffer, assets.GetFileSize("background.png"));
	loadingSurface = IMG_Load_RW(rw, 1);
	
	background = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);
	
	buffer = assets.GetFile("grid.png");
	rw = SDL_RWFromMem(buffer, assets.GetFileSize("grid.png"));
	loadingSurface = IMG_Load_RW(rw, 1);

	tableD.x = 15;
	tableD.y = 20;
	tableD.h = loadingSurface->h;
	tableD.w = loadingSurface->w;

	tableSizeX = loadingSurface->w;
	tableSizeY = loadingSurface->h;

	table = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);

	buffer = assets.GetFile("pont.png");
	rw = SDL_RWFromMem(buffer, assets.GetFileSize("pont.png"));
	loadingSurface = IMG_Load_RW(rw, 1);

	pointsD.x = 15;
	pointsD.y = 580;
	pointsD.h = loadingSurface->h;
	pointsD.w = loadingSurface->w;

	points = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);

	buffer = assets.GetFile("timer.png");
	rw = SDL_RWFromMem(buffer, assets.GetFileSize("timer.png"));
	loadingSurface = IMG_Load_RW(rw, 1);

	timerD.x = 820;
	timerD.y = 21;
	timerD.h = loadingSurface->h;
	timerD.w = loadingSurface->w;

	timer = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);

	buffer = assets.GetFile("cs01.png");
	rw = SDL_RWFromMem(buffer, assets.GetFileSize("cs01.png"));
	loadingSurface = IMG_Load_RW(rw, 1);

	girlD.x = 800;
	girlD.y = 10;
	girlD.h = loadingSurface->h;
	girlD.w = loadingSurface->w;

	girl = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);

	std::stringstream buff;

	for (int i = 0; i < 10; i++)
	{

		buff << "i" << (i+1) << ".png";
		buffer = assets.GetFile(buff.str());

		buffer = assets.GetFile(buff.str());
		rw = SDL_RWFromMem(buffer, assets.GetFileSize(buff.str()));
		loadingSurface = IMG_Load_RW(rw, 1);

		buff.str(std::string());

		runeTex[i] = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);
	}

	runeSizeX = loadingSurface->w;
	runeSizeY = loadingSurface->h;

	for (int i = 0; i < 45; i++)
	{
		runes[i] = rand() % 10;

		runePos[i].x = 15 + 10 + ((i % 9) * (runeSizeX - 25)); // table start position + 10
		runePos[i].y = 20 + 10 + ((i / 9) * (runeSizeY + 2));
		runePos[i].w = runeSizeX;
		runePos[i].h = runeSizeY;

		movingRunePos[i].x = 0;
		movingRunePos[i].y = 0;
		movingRunePos[i].w = runeSizeX;
		movingRunePos[i].h = runeSizeY;

		if (i % 2 == ((i / 9) % 2 == 0 ? 1 : 0)) // cserélgetjük soronként, hogy melyik oszlopot kell süllyeszteni
		{
			runePos[i].y += runeSizeY / 2;
		}
	}

	/* mezõk:
	120 széles
	100 magas
	25-25 két oldalt az átfedés
	10 px fentrõl a szünet
	10 px balról a szünet
	itt kezdõdik az elsõ mezõ
	minden következõ szélesség-15 ben kezd
	minden páros egy magasságban
	minden páratlan magasság/2-ben
	9x5 = 45

	0. item: 0. sor 0. oszlop
	i % 9 = oszlop
	i / 9 = sor

	x:
	minden sor elso tagja 0+10px
	a tobbi (i-1)->width - 12.5

	y:
	elso sor: 10px
	tobbi: sor*(i->height)
	if i % 2 = 1 then height/2

	i = 13, mit tudunk?
	13 / 9 = 1. sor
	13 % 9 = 5. oszlop (4-1)

	*/

	

	return true;
}

void Core::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_QUIT) {
		running = false;
	}

	else if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		//std::cout << "Current event type: MOUSE_BUTTON_DOWN	\n";
//		std::cout << event->button.x << ", " << event->button.y <<	"\n";
	//	std::cout << GetClickedRune(event->button.x, event->button.y) <<	"\n";
		StartDrag(GetClickedRune(event->button.x, event->button.y));
	}

	else if(event->type == SDL_MOUSEBUTTONUP)
	{
		//std::cout << "Current event type: MOUSE_BUTTON_UP	\n";
		EndDrag(GetClickedRune(event->button.x, event->button.y));
	}

	else if(event->type == SDL_MOUSEMOTION)
	{
	//	std::cout << "Current event type: MOUSE_MOTION	\n";
	}
}

void Core::OnLoop()
{
}

void Core::OnRender()
{
	SDL_RenderCopy(mainRenderer, background, NULL, NULL);
	SDL_RenderCopy(mainRenderer, table, NULL, &tableD);
	SDL_RenderCopy(mainRenderer, points, NULL, &pointsD);
	SDL_RenderCopy(mainRenderer, timer, NULL, &timerD);
	SDL_RenderCopy(mainRenderer, girl, NULL, &girlD);

	for (int i = 0; i < 45; i++)
	{
		if (runes[i] == -1) continue;

		if (runeTargetSteps[i] >= 0)
		{
			moving = true;
			lastMoved = true;
			//std::cout << "Moving " << i << " at " << movingRunePos[i].x << " and " << movingRunePos[i].y << " from " << runePos[i].x << " and " << runePos[i].y << "\n";
			movingRunePos[i].x += runeTargetX[i];
			movingRunePos[i].y += runeTargetY[i];
			runeTargetSteps[i] -= 1;
			
			SDL_RenderCopy(mainRenderer, runeTex[runes[i]], NULL, &movingRunePos[i]);
		}
		else
		{
			SDL_RenderCopy(mainRenderer, runeTex[runes[i]], NULL, &runePos[i]);
		}
	}

	if (moving != lastMoved) AnimationReady();
	lastMoved = moving;
	moving = false;
	
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

		SDL_Delay(1);
	}

	OnCleanup();

	return 0;
}

bool Core::CheckMatches(int index)
{
	std::cout <<"Checking for matchis at " << index << ", value: " << runes[index] << "\n";
	for (int i = 0; i < 45; i++)
	{
		std::cout << i << ": " << runes[i] << ", ";
	}
	std::cout << "\n";
	bool result = false;
	int matches = 0;

	// függõleges csekk felfelé
	if (index >= 9 && runes[index] == runes[index - 9])	// nem a legfelsõ sorban van
	{
		std::cout << "Match found in kulso " << index << " and index - 9\n";
		matches++;
		clearRunes.push_back(index - 9);

		if (index >= 9 * 2 && runes[index] == runes[index - (9 * 2)]) // nem is az elsõben
		{
			std::cout << "Match found in belso " << index << " and index - 9 * 2\n";
			matches++;
			clearRunes.push_back(index - 9 * 2);
		}
		
	}
	
	// függõleges csekk lefelé
	if (index < 9 * 4 && runes[index] == runes[index + 9])
	{
		std::cout << "Match found in kulso " << index << " and index + 9\n";
		matches++;
		clearRunes.push_back(index + 9);

		if (index < 9 * 3 && runes[index] == runes[index + (9 * 2)])
		{
			std::cout << "Match found in belso " << index << " and index + 9 * 2\n";
				matches++;
				clearRunes.push_back(index + 9 * 2);
		}
	}

	// csekk found ! 
	if (matches >= 2)
	{
		// collapse animation clearRunes összes elemét eltüntetjük és score-ozunk
		clearRunes.push_back(index);
		ClearMatchedRunes();
		result = true;
	}
	
	if (startIndex % 2 == ((startIndex / 9) % 2 == 0 ? 1 : 0))
	{
		// ha letolt kis runát csekkolunk
		matches = 0;
		clearRunes.clear();

		// nem a jobb szélén van
		if ((index % 9 < 8) && runes[index] == runes[index + 1])
		{
		std::cout << "Match found in kulso " << index << " and index + 1\n";
		matches++;
		clearRunes.push_back(index + 1);

			// és nem is eggyel a széle elõtt
			if ((index % 9 < 7) && index >= 9 && runes[index] == runes[index - 9 + 2])
			{
				std::cout << "Match found in belso " << index << " and index - 9 + 2\n";
				matches++;
				clearRunes.push_back(index - 9 + 2);
			}
		}

		// nem a bal szélén van
		if (index < 9 * 4 && (index % 9 > 0) && runes[index] == runes[index + 9 - 1])
		{
			std::cout << "Match found in kulso " << index << " and index + 9 - 1\n";
			matches++;
			clearRunes.push_back(index + 9 - 1);

			// és nem is eggyel a széle elõtt
			if ((index % 9 > 1) && runes[index] == runes[index + 9 - 2])
			{
				std::cout << "Match found in belso " << index << " and index + 9 - 2\n";
				matches++;
				clearRunes.push_back(index + 9 - 2);
			}
		}
	
		// csekk found ! 
		if (matches >= 2)
		{
			// collapse animation clearRunes összes elemét eltüntetjük és score-ozunk
			clearRunes.push_back(index);
			ClearMatchedRunes();
			result = true;
		}

		// masik atlot is megnezzuk
		matches = 0;
		clearRunes.clear();

		// nem a jobb szélén van
		if (index < 9 * 4 && (index % 9 < 8) && runes[index] == runes[index + 9 + 1])
		{
			std::cout << "Match found in kulso " << index << " and index + 9 + 1\n";
			matches++;
			clearRunes.push_back(index + 9 + 1);

			// és nem is eggyel a széle elõtt
			if ((index % 9 < 7) && runes[index] == runes[index + 9 + 2])
			{
				std::cout << "Match found in belso " << index << " and index + 9 + 2\n";
				matches++;
				clearRunes.push_back(index + 9 + 2);
			}
		}

		// nem a bal szélén van
		if ((index % 9 > 0) && runes[index] == runes[index - 1])
		{
			std::cout << "Match found in kulso " << index << " and index - 1\n";
			matches++;
			clearRunes.push_back(index - 1);

			// és nem is eggyel a széle elõtt
			if ((index % 9 > 1) && index >= 9 && runes[index] == runes[index - 9 - 2])
			{
				std::cout << "Match found in belso " << index << " and index - 9 - 2\n";
				matches++;
				clearRunes.push_back(index - 9 - 2);
			}
		}

		// csekk found ! 
		if (matches >= 2)
		{
			// collapse animation clearRunes összes elemét eltüntetjük és score-ozunk
			clearRunes.push_back(index);
			ClearMatchedRunes();
			result = true;
		}

	}
	else
	{
		// ha letolt kis runát csekkolunk
		matches = 0;
		clearRunes.clear();

		// nem a jobb szélén van
		if (index >= 9 && (index % 9 < 8) && runes[index] == runes[index - 9 + 1])
		{
			std::cout << "Match found in kulso " << index << " and index - 9 + 1\n";
			matches++;
			clearRunes.push_back(index - 9 + 1);

			// és nem is eggyel a széle elõtt
			if ((index % 9 < 7) && runes[index] == runes[index - 9 + 2])
			{
				std::cout << "Match found in belso " << index << " and index - 9 + 2\n";
				matches++;
				clearRunes.push_back(index - 9 + 2);
			}
		}

		// nem a bal szélén van
		if ((index % 9 > 0) && runes[index] == runes[index - 1])
		{
			std::cout << "Match found in kulso " << index << " and index - 1\n";
			matches++;
			clearRunes.push_back(index - 1);

			// és nem is eggyel a széle elõtt
			if ((index % 9 > 1) && index < 9 * 4 && runes[index] == runes[index + 9 - 2])
			{
				std::cout << "Match found in belso " << index << " and index + 9 - 2\n";
				matches++;
				clearRunes.push_back(index + 9 - 2);
			}
		}

		// csekk found ! 
		if (matches >= 2)
		{
			// collapse animation clearRunes összes elemét eltüntetjük és score-ozunk
			clearRunes.push_back(index);
			ClearMatchedRunes();
			result = true;
		}

		// masik atlo
		matches = 0;
		clearRunes.clear();

		// nem a jobb szélén van
		if (index >= 9 && (index % 9 > 0) && runes[index] == runes[index - 9 - 1])
		{
			std::cout << "Match found in kulso " << index << " and index - 9 - 1\n";
			matches++;
			clearRunes.push_back(index - 9 - 1);

			// és nem is eggyel a széle elõtt
			if ((index % 9 > 1) && runes[index] == runes[index - 9 - 2])
			{
				std::cout << "Match found in belso " << index << " and index - 9 - 2\n";
				matches++;
				clearRunes.push_back(index - 9 - 2);
			}
		}

		// nem a bal szélén van
		if ((index % 9 < 8) && runes[index] == runes[index + 1])
		{
			std::cout << "Match found in kulso " << index << " and index + 1\n";
			matches++;
			clearRunes.push_back(index + 1);

			// és nem is eggyel a széle elõtt
			if ((index % 9 < 7) && index < 9 * 4 && runes[index] == runes[index + 9 + 2])
			{
				std::cout << "Match found in belso " << index << " and index + 9 + 2\n";
				matches++;
				clearRunes.push_back(index + 9 + 2);
			}
		}

		// csekk found ! 
		if (matches >= 2)
		{
			// collapse animation clearRunes összes elemét eltüntetjük és score-ozunk
			//clearRunes.clear();
			clearRunes.push_back(index);
			ClearMatchedRunes();
			result = true;
		}

	}
	
	std::cout << "Match found: " << result << "\n";
	return result;
}

void Core::MoveRune(int source, int dest)
{
	runes[dest] = runes[source];
}

int Core::GetClickedRune(int mouseX, int mouseY)
{
	int clicked;

	int column = (mouseX - 15 - 10) / (runeSizeX - 25);

	int row = ((mouseY - 20 - 10) - (column % 2 == 0 ? 0 : runeSizeY / 2)) / (runeSizeY);

	//std::cout << row << " and " << column << "\n";

	clicked = (row * 9) + (column);

	return clicked;
}

void Core::StartDrag(int index)
{
	if (index < 45 || index >= 0)
	{
		startIndex = index;
	}
}

void Core::EndDrag(int index)
{
	if (startIndex == -1) return;

	if (index < 45 || index >= 0)
	{
		endIndex = index;
	}

	//std::cout << "Start: " << startIndex << ", end: "  << endIndex << "\n";

	if (startIndex + 9 == endIndex || startIndex - 9 == endIndex || startIndex + 1 == endIndex || startIndex - 1 == endIndex 
		|| ((startIndex % 2 == ((startIndex / 9) % 2 == 0 ? 1 : 0)) && (startIndex + 9 + 1 == endIndex || startIndex + 9 - 1 == endIndex))
		|| ((startIndex % 2 == ((startIndex / 9) % 2 == 0 ? 0 : 1)) && (startIndex - 9 + 1 == endIndex || startIndex - 9 - 1 == endIndex))
		)
	{
			animationState = 1;
			//SetRuneTarget(endIndex, runePos[startIndex].x, runePos[startIndex].y, runePos[endIndex].x, runePos[endIndex].y, 10);
			//SetRuneTarget(startIndex, runePos[endIndex].x, runePos[endIndex].y, runePos[startIndex].x, runePos[startIndex].y, 10);
			//std::cout << "Changing " << startIndex << " (" << runes[startIndex] << ") to " << endIndex << " (" << runes[endIndex] << ")\n";
			int tempVal = runes[startIndex];
			runes[startIndex] = runes[endIndex];
			runes[endIndex] = tempVal;
			FlipRunes(endIndex, startIndex, 60);
			//std::cout << "After Changing " << startIndex << " (" << runes[startIndex] << ") to " << endIndex << " (" << runes[endIndex] << ")\n";

			match1 = CheckMatches(startIndex);
			match2 = CheckMatches(endIndex);

	}

}

void Core::MatchResults()
{

	if (match1 == match2 && match2 == false)
	{
			std::cout <<"MatchResults false\n";
		//SetRuneTarget(endIndex, runePos[startIndex].x, runePos[startIndex].y, runePos[endIndex].x, runePos[endIndex].y, 10);
		//SetRuneTarget(startIndex, runePos[endIndex].x, runePos[endIndex].y, runePos[startIndex].x, runePos[startIndex].y, 10);

		int tempVal = runes[startIndex];
		runes[startIndex] = runes[endIndex];
		runes[endIndex] = tempVal;

		FlipRunes(startIndex, endIndex, 60);
		
		animationState = 3;
	}
	else
	{
			std::cout <<"MatchResults true\n";
		animationState = 2;
		MoveRunes();
	}
	startIndex = -1;
	endIndex = -1;
};

void Core::ClearMatchedRunes()
{
	for (int i = clearRunes.size(); i > 0; i--)
	{
		runes[clearRunes.at(i-1)] = -1;
		clearRunes.pop_back();
	}
}

void Core::MoveRunes()
{
	for (int i = 44; i >= 0; i--)
	{
		if (runes[i] == -1)
		{
			int index = FindNextRune(i);

			if (index != -1)
			{
				runes[i] = runes[index];
				runes[index] = -1;
				SetRuneTarget(i, runePos[index].x, runePos[index].y, runePos[i].x, runePos[i].y, 50);//(i - index) / 9 * 1
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		if (runes[i] == -1)
		{
			int spawn = 1;
			for (int j = 4; j >= 0; j--)
			{
				if (runes[i + (j * 9)] == -1)
				{
					SpawnRunes(i + j * 9, spawn);
					spawn++;
					std::cout << "Spawning new block to column " << i % 9 << ", index: " << (i + j * 9) << "\n";
				}
			}
			//SpawnRunes(i, spawn);
			std::cout << "Spawning " << spawn << " new blocks to column " << i % 9 << "\n";
		}
	}
}

int Core::FindNextRune(int index)
{
	if (index >= 9)
	{
		if (runes[index - 9] == -1)
		{
			return FindNextRune(index - 9);
		}
		else
		{
			//index = FindNextRune(index - 9);
			return (index - 9);
		}
	}
	return -1;
}

void Core::SpawnRunes(int index, int count)
{
	runes[index] = rand() % 10;

	int dist = (runePos[index].y / runeSizeY) + 1;
	int startPos = 20 + 10 - runeSizeY * count;

	if (index % 2 == ((index / 9) % 2 == 0 ? 1 : 0))
	{
		startPos += runeSizeY / 2;
	}

	SetRuneTarget(index, runePos[index].x, startPos, runePos[index].x, runePos[index].y, 50 * count);
}

void Core::SetRuneTarget(int index, int startX, int startY, int targetX, int targetY, int speed)
{
	std::cout << "Moving " << index << " to " << targetX << ", " << targetY << " from " << startX << ", " << startY << "\n";

	//speed = 1 esetén azt tudom, hogy 60 frame alatt tesz meg 1 sizeY-t vagy sizeX-t => speed = 60
//		ha speed = 0.5 akkor => 30

		//(runeSizeY / 50) = 1;

	//runeTargetX[index] = (speed == 60 ? 0 : (targetX - startX) / speed);
	runeTargetX[index] = 0;
	//runeTargetY[index] = (speed == 60 ? 2 : (targetY - startY) / speed);
	runeTargetY[index] = 2;

	movingRunePos[index].x = startX;
	movingRunePos[index].y = startY;

	//runeTargetSteps[index] = (speed == 60 ? ((targetY - startY) / runeSizeY) * 50 : speed);
	runeTargetSteps[index] = speed;
}

void Core::FlipRunes(int index1, int index2, int speed)
{
	runeTargetX[index1] = (runePos[index2].x - runePos[index1].x) / speed;
	runeTargetY[index1] = (runePos[index2].y - runePos[index1].y) / speed;

	movingRunePos[index1].x = runePos[index1].x;
	movingRunePos[index1].y = runePos[index1].y;

	runeTargetSteps[index1] = speed;

	runeTargetX[index2] = (runePos[index1].x - runePos[index2].x) / speed;
	runeTargetY[index2] = (runePos[index1].y - runePos[index2].y) / speed;

	movingRunePos[index2].x = runePos[index2].x;
	movingRunePos[index2].y = runePos[index2].y;

	runeTargetSteps[index2] = speed;
}

void Core::AnimationReady()
{
	std::cout <<"Ready: " << animationState << "\n";
	switch (animationState)
	{
	case 1:
		MatchResults();
		break;
	}
}