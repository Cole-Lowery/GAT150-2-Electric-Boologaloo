#pragma once
#include "Framework/Actor.h"
#include "Renderer/Texture.h"

class Laser : public viper::Component {
public:
	float speed = 20.0f;

public:
	Laser() = default;

	void Update(float dt) override;

	void OnCollision(class viper::Actor* other);
private:

};

