#include "InputDevice.h"
#include "Game.h"
#include "Camera.h"

InputDevice::InputDevice(class Game* game) :
	GameObject(game)
{
	mKey = Key::GetInstance();
	mController = Controller::GetInstance();
	mMouse = Mouse::GetInstance();

}

void InputDevice::SetState(){
	mKey->SetState();
	mController->SetState();
	mMouse->SetState(CAMERA->getInverseMatrix());

	mUseController = mKey->isInput() ? false : mUseController;
	mUseController = mController->isInput() ? true : mUseController;
}