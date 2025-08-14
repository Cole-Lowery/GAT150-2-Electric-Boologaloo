#include "Rocket.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"
#include "../GamePCH.h"

void Rocket::Update(float dt) {

    transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    float angle = transform.rotation + viper::random::getReal(-60.0f, 60.0f);
    //velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(angle)) * speed;
    //  viper::vec2{ viper::random::getReal(-200.0f , 200.0f), viper::random::getReal(-200.0f , 200.0f) };
    viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(transform.rotation)) * speed;
    auto* rb = GetComponent<viper::RigidBody>();
    if (rb) {
        rb->velocity = force;
    }
<<<<<<< Updated upstream
   
=======

>>>>>>> Stashed changes

    viper::Particle particle;
    particle.position = transform.position;
    particle.velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(angle)) * speed;
    particle.color = (tag == "enemy") ? viper::vec3{ 0, 1, 1 } : viper::vec3{ 1, 1, 0 };
    particle.lifespan = viper::random::getReal(0.15f, 0.3f);
    viper::GetEngine().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other) {
    if (tag != other->tag) {
        destroyed = true;
    }
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
