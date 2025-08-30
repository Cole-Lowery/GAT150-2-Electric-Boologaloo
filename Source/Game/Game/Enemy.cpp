#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "../Rocket.h"
#include "../GameData.h"

FACTORY_REGISTER(Enemy)


void Enemy::Start() {
	OBSERVER_ADD(player_dead);

    m_rigidBody = owner->GetComponent<viper::RigidBody>();

    fireTimer = fireTime;
}

void Enemy::Update(float dt) {
    bool playerSeen = false;

    auto player = owner->m_scene->GetactorByName<viper::Actor>("player");
    if (player) {
        viper::vec2 direction{ 0, 0 };
        direction = player->m_transform.position - owner->m_transform.position;

        direction = direction.Normalized();
        viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->m_transform.rotation));

        float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 180;

        if (playerSeen) {
        float angle = viper::vec2::SignedAngleBetween(forward, direction);
        angle = viper::math::sign(angle);
        owner->m_transform.rotation += viper::math::radToDeg(angle * 5 * dt);
        
        }



    }


    viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(owner->m_transform.rotation)) * speed;
    //velocity += force * dt;
	//GetComponent<viper::RigidBody>()->velocity += force * dt;
    if (m_rigidBody) {
		m_rigidBody->velocity += force * dt;
    }

    owner->m_transform.position.x = viper::math::wrap(owner->m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->m_transform.position.y = viper::math::wrap(owner->m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());


    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::enemyDesign, viper::vec3{ 1.0f, 1.0f, 1.0f });
        //spawn rocket at player position and rotation
        viper::Transform transform{ owner->m_transform.position, owner->m_transform.rotation, 2.0f };
        //auto rocket = std::make_unique<viper::Actor>(transform);// , viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));
		auto rocket = viper::Instantiate("rocket", transform);

        //rocket->speed = 500.0f;
        //rocket->lifespan = 1.5f;
        rocket->tag = "enemy";
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

        owner->m_scene->AddActor(std::move(rocket));
    }
    /*
    viper::Actor::Update(dt);
    */
}


void Enemy::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;

        /*
    if (owner->tag != other->tag && other->tag != "powerup") {
        owner->scene->GetGame()->AddPoints(100);
        
        int randNum = viper::random::getInt(0, 100);
        if (randNum < 5) {
            //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::boost, viper::vec3{ 1.0f, 1.0f, 1.0f });
            FireratePowerup* powerup = new FireratePowerup(viper::Transform{ owner->transform.position, 0.0f, 15.0f }); //, viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));
            // components
            auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
            spriteRenderer->textureName = "textures/powerup.png";
            powerup->AddComponent(std::move(spriteRenderer));

            auto rb = std::make_unique<viper::RigidBody>();
            powerup->AddComponent(std::move(rb));

            auto collider = std::make_unique<viper::CircleCollider2D>();
            collider->radius = 60;
            powerup->AddComponent(std::move(collider));

            owner->scene->AddActor(std::unique_ptr<viper::Actor>(powerup));
            
        }
        */

		EVENT_NOTIFY_DATA("add_points", 100);

        for (int i = 0; i < 100; i++) {
            viper::Particle particle;
            particle.position = owner->m_transform.position;
            particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
            particle.color = { 1, 1, 1 };
            particle.lifespan = 2;
            viper::GetEngine().GetParticleSystem().AddParticle(particle);
        
    }
    }
}

void Enemy::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, fireTime);
}

void Enemy::OnNotify(const viper::Event& event) {
    if (viper::equalsIgnoreCase(event.id, "player_dead")) {
        owner->destroyed = true;
	}
}
