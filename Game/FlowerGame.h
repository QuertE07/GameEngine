#pragma once
#include "Game.h"
#include "Text.h"
#include "Texture.h"
#include "Resource.h"

class FlowerGame : public gl::Game
{
public:
	enum class GameState
	{
		Title,
		StartGame,
		Game,
		GameOver
	};

public:
	FlowerGame() = default;
	FlowerGame(gl::Scene* scene) : Game{ scene } {}

	bool Initialize() override;

	void Update(float dt) override;
	void Draw(class gl::Renderer& renderer) override;

	void LifeLost();
	void AddPoints(int points) { m_score += points; }

private:
	void SpawnPlayer();
	void SpawnFlower(float decayRate);

private:
	GameState m_gamestate = GameState::Title;
	int m_score = 0;
	int m_lives = 0;

	float m_stateTimer = 0.0f;

	float m_spawnTimer = 0.0f;
	float m_spawnTime = 6.0f;
	int m_spawnCount = 0;
	int m_lostFlowers = 0;

	gl::res_t<gl::Texture> m_playerTexture{ nullptr };
	gl::res_t<gl::Texture> m_flowerTexture{ nullptr };
	gl::res_t<gl::Texture> m_bgTexture{ nullptr };

	gl::Text* m_titleText{ nullptr };

	gl::Text* m_gameOverText{ nullptr };

	gl::Text* m_scoreText{ nullptr };
	gl::Text* m_livesText{ nullptr };
};