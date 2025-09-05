#pragma once

#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class PlatformerGame : public viper::Game, public viper::IObserver {
public:
	

	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver
	};

public:

	PlatformerGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;
	void Draw(class viper::Renderer& renderer) override;

	void OnNotify(const viper::Event& event) override;
	void OnPlayerDeath();
	void SpawnCoin();

	

private:
	void SpawnEnemy();
	void SpawnPlayer();
	void SpawnBat();
	void SpawnPowerup();

private:
	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer{ 0 };
	float m_stateTimer{ 0 };
	float m_coinSpawnTimer{ 0 };
	float fent_count{ 0 };

	std::shared_ptr< class viper::Font> m_titleFont;
	std::shared_ptr< class viper::Font> m_uiFont;

	std::unique_ptr< class viper::Text> m_titleText;
	std::unique_ptr< class viper::Text> m_scoreText;
	std::unique_ptr< class viper::Text> m_livesText;

	bool m_backgroundMusicStarted = false;


};

