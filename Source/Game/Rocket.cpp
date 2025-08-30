#include "Rocket.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"
#include "GamePCH.h"

FACTORY_REGISTER(Rocket)

void Rocket::Start() {
    m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void Rocket::Update(float dt) {

    owner->m_transform.position.x = viper::math::wrap(owner->m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->m_transform.position.y = viper::math::wrap(owner->m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    float angle = owner->m_transform.rotation + viper::random::getReal(-60.0f, 60.0f);
    //velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(angle)) * speed;
    //  viper::vec2{ viper::random::getReal(-200.0f , 200.0f), viper::random::getReal(-200.0f , 200.0f) };
    viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(owner->m_transform.rotation)) * speed;
    
    if (m_rigidBody) {
        m_rigidBody->velocity = force;
    }
   

    viper::Particle particle;
    particle.position = owner->m_transform.position;
    particle.velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(angle)) * speed;
    particle.color = (owner->tag == "enemy") ? viper::vec3{ 0, 1, 1 } : viper::vec3{ 1, 1, 0 };
    particle.lifespan = viper::random::getReal(0.15f, 0.3f);
    viper::GetEngine().GetParticleSystem().AddParticle(particle);
}

void Rocket::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;
    }
}

void Rocket::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);


}
