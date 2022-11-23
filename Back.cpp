#include "Back.h"
#include "Game.h"
#include "Camera.h"
#include "Container.h"
void Back::Draw()
{
	static Quad quad = ToQuad({ { 0,(float)CONTAINER->getMapData().mapHeight },2560,2240 });
	CAMERA->DrawQuad(quad, CONTAINER->getBackData().image,0xAAAAAAFF);

}
