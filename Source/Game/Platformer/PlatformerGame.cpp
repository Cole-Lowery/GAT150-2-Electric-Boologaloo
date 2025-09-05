#include "PlatformerGame.h"
#include "../GamePCH.h"



	bool PlatformerGame::Initialize() {


		OBSERVER_ADD(player_dead);
		OBSERVER_ADD(add_points);
		OBSERVER_ADD(touch_enemy);
		OBSERVER_ADD(fent);

		m_scene = std::make_unique<viper::Scene>(this);


		m_scene->Load("scenes/prototypes.json");
		m_scene->Load("scenes/level.json");

		m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "../Prisma.ttf", 48.0f));
		m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "../Prisma.ttf", 48.0f));
		m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "../Prisma.ttf", 48.0f));

		

		return true;
	}

	void PlatformerGame::Update(float dt) {
		switch (m_gameState)
		{
		case PlatformerGame::GameState::Initialize:
			m_gameState = GameState::Title;
			break;
		case PlatformerGame::GameState::Title:
			
			//if (!m_backgroundMusicStarted) {
			//viper::GetEngine().GetAudio().PlaySound("main_menu");
			//m_backgroundMusicStarted = true;
			//}
			if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
				//m_backgroundMusicStarted = false;
				m_gameState = GameState::StartGame;
			}
			break;
		case PlatformerGame::GameState::StartGame:
			//viper::GetEngine().GetAudio().StopSound();
			m_enemySpawnTimer = 0;
			m_coinSpawnTimer = 0;

			m_gameState = GameState::StartRound;
			break;
		case PlatformerGame::GameState::StartRound:

			//if (!m_backgroundMusicStarted) {
			//	viper::GetEngine().GetAudio().PlaySound("tetris");
			//	m_backgroundMusicStarted = true;
			//}

			SpawnPlayer();
			m_gameState = GameState::Game;

			break;
		case PlatformerGame::GameState::Game:
			m_enemySpawnTimer -= dt;
			m_coinSpawnTimer -= dt;
			if (m_enemySpawnTimer <= 0) {
				m_enemySpawnTimer = 10;
				SpawnBat();
			}
			if (m_coinSpawnTimer <= 0) {
				m_coinSpawnTimer = 2;
				SpawnCoin();
			}
			

			break;
		case PlatformerGame::GameState::PlayerDead:


			break;
		case PlatformerGame::GameState::GameOver:
			
			//if (!m_backgroundMusicStarted) {
		//viper::GetEngine().GetAudio().PlaySound("game_over");
		//m_backgroundMusicStarted = true;
		//	}
			m_scene->RemoveAllActors();
			if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
				//viper::GetEngine().GetAudio().StopSound();
				//m_backgroundMusicStarted = false;
				m_gameState = GameState::Title;
			}
			break;
		default:

			break;
		}

		m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
	}

	void PlatformerGame::Shutdown() {
		//
	}

	void PlatformerGame::Draw(class viper::Renderer& renderer) {
		m_scene->Draw(renderer);


		if (m_gameState == GameState::Title) {

			m_titleText->Create(renderer, "Final", viper::vec3{ 1, 0, 1 });
			m_titleText->Draw(renderer, 325, 500);
		}

		if (m_gameState == GameState::Game) {

		m_scoreText->Create(renderer, std::to_string(m_score), { 1, 1, 1 });
		m_scoreText->Draw(renderer, 20, 20);

		}

		if (m_gameState == GameState::GameOver) {

			m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0, 0 });
			m_titleText->Draw(renderer, 450, 500);
		}

		viper::GetEngine().GetPS().Draw(renderer);

	}


	void PlatformerGame::OnNotify(const viper::Event& event) {
		if (viper::equalsIgnoreCase(event.id, "add_points")) {
			AddPoints(std::get<int>(event.data));

			int i = viper::random::getReal(0.0f, 100.0f);
			if (i < 10) {
				SpawnPowerup();
			}
		}
		else if (viper::equalsIgnoreCase(event.id, "touch_enemy")) {
			//SpawnCoin();
		}
		else if (viper::equalsIgnoreCase(event.id, "player_dead")) {
			viper::GetEngine().GetAudio().StopSound();
			m_backgroundMusicStarted = false;
			m_gameState = GameState::GameOver;
		}
		else if (viper::equalsIgnoreCase(event.id, "fent")) {
			fent_count++;
			if (fent_count >= 1) { 
				EVENT_NOTIFY_DATA(player_dead, true);
			}
		}
	}

	void PlatformerGame::OnPlayerDeath() {

	}

	void PlatformerGame::SpawnEnemy() {
		auto enemy = viper::Instantiate("platformenemy");
		enemy->transform.position = viper::vec2{ 1080.0f, 0.0f };
		m_scene->AddActor(std::move(enemy));
	}

	void PlatformerGame::SpawnPlayer() {
		auto player = viper::Instantiate("platformplayer");
		player->transform.position = viper::vec2{ 440.0f, 520.0f };
		m_scene->AddActor(std::move(player));
	}

	void PlatformerGame::SpawnBat() {
		auto enemy = viper::Instantiate("bat");
		enemy->transform.position = viper::vec2{ 1000, 0 };
		m_scene->AddActor(std::move(enemy));
	}

	void PlatformerGame::SpawnPowerup() {
		auto powerup = viper::Instantiate("powerup_pickup");
		powerup->transform.position = viper::vec2{ viper::random::getReal(200.0f, 700.0f), 0};
		m_scene->AddActor(std::move(powerup));
	}

	void PlatformerGame::SpawnCoin() {
		auto pickup = viper::Instantiate("coin_pickup");
		pickup->transform.position = viper::vec2{ viper::random::getReal(200.0f, 700.0f), viper::random::getReal(0.0f, 300.0f)};
		m_scene->AddActor(std::move(pickup));
	}
