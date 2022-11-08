#pragma once
class PlayerStateBase
{

private:

	class Player* mPlayer;

public:
	PlayerStateBase(class Player* player) : mPlayer(player) {}
	virtual ~PlayerStateBase() {}

	class Player* getPlayer() { return mPlayer; }
	const class Player* getPlayer() const { return mPlayer; }
	void Proc() {
		Update();
		StateTransition();
	}

	virtual void Update() = 0;
	virtual void StateTransition() = 0;

};

