#pragma once
#include "PlayerStateBase.h"
class PlayerStateWait :
    public PlayerStateBase
{

private:


public:
    PlayerStateWait(class Player* player) : PlayerStateBase(player) {}
    ~PlayerStateWait() {}

    void Update();
    void StateTransition();

};

