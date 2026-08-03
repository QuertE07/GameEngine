#include "FlowerGame.h"
#include "Engine.h"
#include "Player.h"
#include "Flower.h"
#include "Assets.h"

#include <string>

using namespace gl;

bool FlowerGame::Initialize()
{
    Game::Initialize();

    m_scene = new Scene();
    m_scene->SetGame(this);

    m_titleFont = new Font();
    m_titleFont->Load("fonts/Hyacinth.ttf", 120);

    m_titleText = new Text(m_titleFont);
    m_titleText->Create(Engine::Get().GetRenderer(), "Butterfly Pollinator", Color{ 1.0f, 1.0f, 1.0f });

    m_gameOverFont = new Font();
    m_gameOverFont->Load("fonts/Hyacinth.ttf", 140);

    m_gameOverText = new Text(m_gameOverFont);
    m_gameOverText->Create(Engine::Get().GetRenderer(), "Game Over", Color{ 1.0f, 0.4f, 0.6f });

    m_gameFont = new Font();
    m_gameFont->Load("fonts/Hyacinth.ttf", 60);

    m_scoreText = new Text(m_gameFont);
    m_livesText = new Text(m_gameFont);



    return false;
}

void FlowerGame::Update(float dt)
{
    switch (m_gamestate)
    {
    case GameState::Title:
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
        {
            m_gamestate = GameState::StartGame;
            Engine::Get().GetAudio().PlaySound("bgm");
        }
        break;
    case GameState::StartGame:
        SpawnPlayer();

        m_score = 0;
        m_lives = 3;
        m_gamestate = GameState::Game;
        break;
    case GameState::Game:
        
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0)
        {
            m_spawnTimer = m_spawnTime;
            SpawnFlower(1.0f);
            m_spawnCount++;
            if (m_spawnCount > 1)
            {
                m_spawnCount = 0;
                m_spawnTime *= 0.95f;
            }
        }

        break;
    case GameState::GameOver:

        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_scene->RemoveAllActors();
            m_gamestate = GameState::Title;
        }
        break;
    }
    Game::Update(dt);
}

void FlowerGame::Draw(const Renderer& renderer)
{
    switch (m_gamestate)
    {
    case GameState::Title:
        m_titleText->Draw(renderer, 650, 500);
        break;
    case GameState::StartGame:
    case GameState::Game:
        m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
        m_scoreText->Draw(renderer, 30, 30);

        m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
        m_livesText->Draw(renderer, 30, 150);

        break;
    case GameState::GameOver:
        m_gameOverText->Draw(renderer, 750, 450);
        break;
    }
    Game::Draw(renderer);
}

void FlowerGame::LifeLost()
{
    m_lives--;

    if (m_lives == 0)
    {
        m_scene->GetActorByName<Player>("Player")->SetDestroyed();
        m_gamestate = GameState::GameOver;
        m_stateTimer = 2.0f;
    }
}

void FlowerGame::SpawnPlayer()
{
    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.tag = "Player";
    playerDesc.transform = Transform{ Vector2{ 960.0f, 540.0f }, 0, 10 };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.model = Assets::playerModel;
    playerDesc.speed = 100.0f;

    std::unique_ptr<Player> player = std::make_unique<Player>( playerDesc );
    m_scene->AddActor(std::move(player));
}

void FlowerGame::SpawnFlower(float decayRate)
{
    FlowerDesc flowerDesc;
    flowerDesc.name = "Flower";
    flowerDesc.tag = "Flower";
    flowerDesc.transform = Transform{ Vector2{ RandomFloat(100.0f, 1820.0f), RandomFloat(100.0f, 980.0f) }, 0, 10};
    flowerDesc.velocity = Vector2{ 0.0f, 0.0f };
    flowerDesc.model = Assets::flowerModel;
    flowerDesc.decayRate = decayRate;

    std::unique_ptr<Flower> flower = std::make_unique<Flower>( flowerDesc );
    m_scene->AddActor(std::move(flower));
}
