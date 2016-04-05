#pragma once

class GameState {
public:
	GameState();
	~GameState();
private:
	virtual const bool update() = 0;
};