#include "FireratePowerup.h"
#include "Player.h"




void FireratePowerup::Update(float dt) {
	//Actor::Update(dt);
}

void FireratePowerup::OnCollision(viper::Actor* other) {
    if (Player* player = dynamic_cast<Player*>(other)) {
        player->fireRateBoostActive = true;
        owner->destroyed = true; 
    }
}
