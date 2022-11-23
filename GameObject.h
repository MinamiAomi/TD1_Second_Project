#pragma once

#ifndef ACCESS_PTR
#define ACCESS_PTR

#define CONTAINER getGame()->getContainer()
#define INPUT_DEV getGame()->getInput()
#define KEY getGame()->getInput()->getKey()
#define CONTROLLER getGame()->getInput()->getController()
#define MOUSE getGame()->getInput()->getMouse()
#define DELTA_TIME getGame()->getDeltaTime()
#define CAMERA getGame()->getCamera()
#define MAP getGame()->getMap()
#define PLAYER getGame()->getPlayer()
#define PLAYER_DATA getGame()->getContainer()->getPlayerData()

#define BOSS getGame()->getBoss()
#define BOSS_DATA getGame()->getContainer()->getBossData()

#endif // !ACCESS_PTR



class GameObject {

private:
	class Game* mGame;

public:
	GameObject(class Game* game) : mGame(game) {}
	virtual ~GameObject() = 0 { mGame = nullptr; }

	class Game* getGame() { return mGame; }
	const class Game* getGame() const { return mGame; }
	void setGame(class Game* game) { mGame = game; }
};

