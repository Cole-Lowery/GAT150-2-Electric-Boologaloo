#include "../GamePCH.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "../GameData.h"



bool SpaceGame::Initialize() {

	OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);
    

    m_scene = std::make_unique<viper::Scene>(this);

    m_scene->Load("scene.json");
    
    //it only loads the first font size
    m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "Prisma.ttf", 128.0f));
    m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Prisma.ttf", 48.0f));
    m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Prisma.ttf", 48.0f));

    
	


    return true;
}

void SpaceGame::Update(float dt) {
    switch (m_gameState) {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        if (!m_backgroundMusicStarted) {
            //viper::GetEngine().GetAudio().PlaySound("main_menu");
            //m_backgroundMusicStarted = true;
        }
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			//m_backgroundMusicStarted = false;
            m_gameState = GameState::StartGame;
        }
        break;
    case SpaceGame::GameState::StartGame:
		//viper::GetEngine().GetAudio().StopSound();
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound: {
        m_scene->RemoveAllActors();

        //auto player = viper::Factory::Instance().Create<viper::Actor>("player");
        auto player = viper::Instantiate("player");
        m_scene->AddActor(std::move(player));


        if (!m_backgroundMusicStarted) {
            //viper::GetEngine().GetAudio().PlaySound("tetris");
            //m_backgroundMusicStarted = true;
        }

        /*
        //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::points, viper::vec3{ 0.0f, 0.4f, 1.0f });
        viper::Transform transform{ viper::vec2{viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 3 };
        auto player = std::make_unique<Player>(transform); // , viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));

        player->speed = 500.0f;
        player->rotationRate = 200.0f;
        //player->damping = 1.5f;
        player->tag = "player";
        player->name = "player";

        // components
        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureName = "textures/player.png";
        player->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<viper::RigidBody>();
        rb->damping = 1.5f;
        player->AddComponent(std::move(rb));

        auto collider = std::make_unique<viper::CircleCollider2D>();
        collider->radius = 60;
		player->AddComponent(std::move(collider));

        m_scene->AddActor(std::move(player));
        */

        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:
        
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 1;
            SpawnEnemy();
        

        }

        break;
    case SpaceGame::GameState::PlayerDead:
        
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
        m_lives--;
        if (m_lives == 0) { 
            m_scene->RemoveAllActors();
        //viper::GetEngine().GetAudio().StopSound();
        //m_backgroundMusicStarted = false;
		//viper::GetEngine().GetAudio().PlaySound("game_over");
            m_gameState = GameState::GameOver; 
			m_stateTimer = 3;
        }
        else m_gameState = GameState::StartRound;
        }
        break;
    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
			//viper::GetEngine().GetAudio().StopSound();
        m_gameState = GameState::Title;
        m_stateTimer = 3;
        }
        break;
    default:
        break;
    }

    //if (viper::GetEngine().GetInput())

    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Shutdown() {
    //
}

void SpaceGame::Draw(viper::Renderer& renderer) {
    m_scene->Draw(renderer);
    
    if (m_gameState == GameState::Title) {
    
	m_titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1, 0, 0 }); //exception thrown when this line of code trys to create
    m_titleText->Draw(renderer, 200, 400);
    }

    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 150, 400);
    }

    m_scoreText->Create(renderer, std::to_string(m_score), { 1, 1, 1 });
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES: " + std::to_string(m_lives), {1, 1, 1});
    m_livesText->Draw(renderer, renderer.GetWidth() - 250, 20);
    

    viper::GetEngine().GetParticleSystem().Draw(renderer);
    
    

}

void SpaceGame::OnPlayerDeath() {
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void SpaceGame::SpawnEnemy() {
    viper::Actor* player = m_scene->GetactorByName<viper::Actor>("player");
        if (player) {

        viper::vec2 position = player->m_transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
        viper::Transform transform{ position, 0, 5 };
    auto enemy = viper::Instantiate("enemy", transform);
    m_scene->AddActor(std::move(enemy));

        }

}

void SpaceGame::OnNotify(const viper::Event& event) {
    if (viper::equalsIgnoreCase(event.id, "player_dead")) {
        OnPlayerDeath();
    } else if (viper::equalsIgnoreCase(event.id, "add_points")) {
        AddPoints(std::get<int>(event.data));
	}
    //std::cout << event.id << std::endl;


}

