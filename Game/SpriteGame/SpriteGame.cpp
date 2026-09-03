#include "SpriteGame.h"
#include "Engine.h"

#include <string>

using namespace gl;

bool SpriteGame::Initialize()
{
    Game::Initialize();

    SetWorkingDirectory("SpriteGame");

    m_scene = std::make_unique<Scene>();
    m_scene->SetGame(this);
    m_scene->Load("scenes/scene.json");
    
    m_bgTexture = Resources().Get<Texture>("textures/oldtimes.png", Engine::Get().GetRenderer());

    m_titleText = new Text(Resources().GetWithID<Font>("title_font", "fonts/Hyacinth.ttf", 120.0f));
    m_titleText->Create(Engine::Get().GetRenderer(), "Elphelt Simulator", Color{ 1.0f, 1.0f, 1.0f });

    m_gameOverText = new Text(Resources().GetWithID<Font>("gameOver_font", "fonts/Hyacinth.ttf", 140.0f));
    m_gameOverText->Create(Engine::Get().GetRenderer(), "Died </3", Color{ 1.0f, 0.4f, 0.6f });

    m_scoreText = new Text(Resources().GetWithID<Font>("score_font", "fonts/Hyacinth.ttf", 60.0f));
    m_livesText = new Text(Resources().GetWithID<Font>("lives_font", "fonts/Hyacinth.ttf", 60.0f));

    return false;
}

void SpriteGame::Update(float dt)
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
        m_gamestate = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            //m_scene->RemoveAllActors();
            m_scene->Load("scenes/level.json");

            m_gamestate = GameState::Game;
        }
        break;
    case GameState::Game:
        
        m_spawnTimer -= dt;

        if (m_spawnTimer < 0)
        {
            SpawnEnemy();
            m_spawnTimer = 3.0f;
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

void SpriteGame::Draw(Renderer& renderer)
{
    renderer.DrawTexture(*m_bgTexture.get(), renderer.GetWidth() / 2.0f, renderer.GetHeight() / 2.0f);

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

void SpriteGame::LifeLost()
{
    m_lives--;

    if (m_lives == 0)
    {
        //m_scene->GetActorByName<Player>("PlayerPrototype")->SetDestroyed();
        m_gamestate = GameState::GameOver;
        m_stateTimer = 2.0f;
    }
}

void SpriteGame::SpawnPlayer()
{
    auto player = Factory::Instance().Create<Actor>("PlayerPrototype");
    m_scene->AddActor(std::move(player));
}

void SpriteGame::SpawnEnemy()
{
    int enemyIndex = RandomInt(2);

    if (enemyIndex == 0)
    {
        auto enemy = Factory::Instance().Create<Actor>("EnemyPrototype");
        enemy->SetPosition({ RandomFloat(0.0f, 1920.0f), RandomFloat(0, 1080) });
        m_scene->AddActor(std::move(enemy));
    }
    else
    {
        auto enemy = Factory::Instance().Create<Actor>("FlyingEnemyPrototype");
        enemy->SetPosition({ RandomFloat(0.0f, 1920.0f), RandomFloat(0, 1080) });
        m_scene->AddActor(std::move(enemy));
    }
}