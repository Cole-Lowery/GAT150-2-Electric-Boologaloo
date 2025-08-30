#pragma once

#include "Framework/Component.h"


class Player : public viper::Component, public viper::ICollidable {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.5f;
	float fireTimer = 0.0f;
	float laserTime = 30.0f;
	float laserTimer = 0.0f;

	bool fireRateBoostActive = false;
	float boostTime = 5.0f;
	float boostTimer = 0.0f;
	float boostCountDown = 5.0f;
	float canFire = false;

public:
	Player() = default;
		
	void Update(float dt) override;

	CLASS_PROTOTYPE(Player)

	void OnCollision(class viper::Actor* other) override;

	void Read(const viper::json::value_t& value)override;

private:
	void CreateParticle();

};
