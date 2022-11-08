#pragma once
#include "GameObject.h"
#include "Key.h"
#include "ControllerInput.h"
#include "Mouse.h"

class InputDevice :
	public GameObject {

private:
	bool mUseController = false;

	Key* mKey;
	Controller* mController;
	Mouse* mMouse;

public:
	InputDevice(class Game* game);
	~InputDevice() {}

	void SetState();

	const class Key* getKey() const { return mKey; }
	const class Controller* getController() const { return mController; }
	class Controller* getController() { return mController; }
	const class Mouse* getMouse() const { return mMouse; }

	bool isUseController() const { return mUseController; }
};