#pragma once
#include "Framework/Actor.h"


class FireratePowerup : public viper::Actor {
public:
	FireratePowerup(const viper::Transform& transform)
		: Actor{ transform } {
		tag = "powerup";
		name = "fireRatePowerUp";
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

};

