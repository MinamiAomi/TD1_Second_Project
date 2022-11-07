#pragma once

#ifndef ACCESS_PTR
#define ACCESS_PTR

#define CONTAINER getGame()->getContainer()
#define KEY getGame()->getKey()
#define CONTROLLER getGame()->getController()
#define DELTA_TIME getGame()->getDeltaTime()
#define CAMERA getGame()->getCamera()
#define MAP getGame()->getMap()

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

