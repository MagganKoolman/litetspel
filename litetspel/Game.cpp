#include "Game.h"

Game::Game() {
	pDeferredProgram = new DeferredProgram("deferred.vertex","deferred.pixel","deferred.geometry");
}

Game::~Game() {
	delete pDeferredProgram;
}

bool Game::update() {
	return true;
}