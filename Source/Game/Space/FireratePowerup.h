#pragma once
#include "Framework/Actor.h"


class FireratePowerup : public viper::Component {
public:
	/*FireratePowerup(const viper::Transform& transform)
		: Actor{ transform } {
		tag = "powerup";
		name = "fireRatePowerUp";
	}*/

	void Update(float dt) override;
	void OnCollision(viper::Actor* other);

private:

};

