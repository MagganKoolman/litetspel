#pragma once
#include "GameState.h"

class Game {
public:
	Game();
	~Game();

	bool update();
private:
	GameState* actionState;
};
