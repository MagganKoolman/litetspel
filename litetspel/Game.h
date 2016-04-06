#pragma once
#include "GameState.h"
#include "DeferredProgram.h"

class Game {
public:
	bool update();

	Game();
	~Game();
private:
	GameState* pActionState;
	ShaderProgram* pDeferredProgram;
};
