#include "Laser.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"

void Laser::Update(float dt) {
    /*
    transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    float angle = transform.rotation + viper::random::getReal(-60.0f, 60.0f);
    //velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(angle)) * speed;

    Actor::Update(dt);
    */
}

void Laser::OnCollision( class viper::Actor* other) {

}
