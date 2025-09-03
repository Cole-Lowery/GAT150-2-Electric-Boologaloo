#include "Player.h"
#include "GameData.h"
#include "Rocket.h"
#include "SpaceGame.h"
#include "Laser.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Player)

void Player::Start() {
    m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void Player::Update(float dt) {
  

    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) { 
        CreateParticle();
        rotate -= 1;
    }
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) { 
        CreateParticle();
        rotate += 1; }

    //owner->transform.rotation += (rotate * rotationRate) * dt;
    m_rigidBody->ApplyTorque((rotate * rotationRate) * dt);

    //thrust
    float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) { 
        CreateParticle();
        thrust = 1;
    }
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) { 
        CreateParticle();
        thrust = -1; }
    
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {
        this->speed = 3000;
    }
    else { this->speed = 500;  }



    viper::vec2 direction{ 1, 0 };
    viper::vec2 force = direction.Rotate(viper::math::degToRad(owner->transform.rotation)) * thrust * speed;
	//velocity += force * dt;
    //auto* rb = owner->GetComponent<viper::RigidBody>();
    if (m_rigidBody) {
        m_rigidBody->ApplyForce(force);
    }

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    //check fire key pressed
    laserTimer -= dt;
    fireTimer -= dt;

    if (fireRateBoostActive) {
        boostCountDown -= dt;
        if (boostCountDown <= 0) {
            fireRateBoostActive = false;
            boostCountDown = boostTime; // reset for next powerup
        }
    }

    
    

    if (fireRateBoostActive) {
        canFire = viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE);
    }
    else {
        canFire = viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0;
    }

    if (canFire) {
        fireTimer = fireTime;

        /*
        auto sound = viper::GetEngine().GetAudio().PlaySound(*viper::Resources().Get<viper::AudioClip>("laser.wav", viper::GetEngine().GetAudio()).get());
        if (sound) {

        //viper::GetEngine().GetAudio().PlaySound(*sound);
        }
        */
        
        //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::points, viper::vec3{ 1.0f, 1.0f, 1.0f });
        //spawn rocket at player position and rotation
        viper::Transform transform{ this->owner->transform.position, this->owner->transform.rotation, 2.0f };
        //auto rocket = std::make_unique<viper::Actor>(transform); // , viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));
		auto rocket = viper::Instantiate("rocket", transform);

        //rocket->speed = 500.0f;
        //rocket->lifespan = 1.5f;
        rocket->tag = "player";
        //rocket->name = "rocket";

        // components
        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureName = "textures/rocket.png";
        rocket->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<viper::RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<viper::CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        //viper::GetEngine().GetAudio().PlaySound("laser");

        

        owner->scene->AddActor(std::move(rocket));
    }

    /*
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E) && laserTimer <= 0) {
        laserTimer = laserTime;
       
            
            //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::laser, viper::vec3{ 1.0f, 1.0f, 1.0f });
            //spawn rocket at player position and rotation
            viper::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
            auto laser = std::make_unique<Laser>(transform); // , viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));

            laser->speed = 5000.0f;
            laser->lifespan = 10.0f;
            laser->tag = "player";
            laser->name = "laser";

            // components
            auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
            spriteRenderer->textureName = "textures/laser.png";
            laser->AddComponent(std::move(spriteRenderer));

            auto rb = std::make_unique<viper::RigidBody>();
            laser->AddComponent(std::move(rb));

            auto collider = std::make_unique<viper::CircleCollider2D>();
            collider->radius = 10;
            laser->AddComponent(std::move(collider));


            viper::GetEngine().GetAudio().PlaySound("laser");



            scene->AddActor(std::move(laser));
    }
    
    Actor::Update(dt);
    */

   
}
    

void Player::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag && other->tag != "powerup") {
        owner->destroyed = true;

		EVENT_NOTIFY("player_dead", true);
        

        //dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
    }
}

void Player::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, rotationRate);
    JSON_READ(value, fireTime);

}

void Player::CreateParticle() {
    viper::Particle particle;
    particle.position = owner->transform.position;
    particle.velocity = viper::vec2{ viper::random::getReal(-200.0f , 200.0f), viper::random::getReal(-200.0f , 200.0f) };
    particle.color = { 1, 1, 1 };
    particle.lifespan = 2;
    viper::GetEngine().GetPS().AddParticle(particle);
}


