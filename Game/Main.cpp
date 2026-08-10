#include "FlowerGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <fmod.hpp>
#include <map>
#include <memory>

using namespace gl;

class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

uint32_t seed = 1234;

uint32_t RNG()
{
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main()
{
    //for (size_t i = 0; i < 10; i++) std::cout << RNG() << " ";
    //std::cout << std::endl;
    //
    //for (size_t i = 0; i < 10; i++) std::cout << RNG() << " ";
    //std::cout << std::endl;
    //
    ////srand((unsigned int)time(NULL));
    //SeedRandom((unsigned int)time(NULL));
    //for (size_t i = 0; i < 10; i++) std::cout << rand() << " ";
    //std::cout << std::endl;

    //return 0;

    //std::cout << "====================-object-=====================\n";
    //{

    //    Object objectA;
    //    Object objectB = objectA;
    //    Object objectC;
    //    objectC = objectA;
    //}

    //std::cout << "\n====================-raw pointers-=====================\n";
    //{
    //    Object* objectA = new Object;
    //    std::cout << objectA << std::endl;
    //    Object* objectB = new Object(*objectA);
    //    std::cout << objectB << std::endl;
    //    Object* objectC = nullptr;
    //    objectC = objectA;
    //    std::cout << objectC << std::endl;
    //    
    //    delete objectA;
    //    delete objectB;
    //}

    //std::cout << "\n====================-smart pointers-=====================\n";
    //{
    //    std::unique_ptr<Object> objectA = std::make_unique<Object>();
    //    std::cout << objectA.get() << std::endl;
    //    std::unique_ptr<Object> objectB;
    //    objectB = std::move(objectA);
    //    std::cout << objectB.get() << std::endl;
    //}

    //return 0;

    SetWorkingDirectory("Assets");
    if (Engine::Get().Initialize() == false) return 0;

    FlowerGame game;
    game.Initialize();

    // SFX init
    Engine::Get().GetAudio().AddSound("bgm", "audio/bgm.mp3");
    Engine::Get().GetAudio().AddSound("CompleteCharge", "audio/sparkle.mp3");
    Engine::Get().GetAudio().AddSound("FlowerWilt", "audio/wilt.mp3");

    bool quit = false;

    while (!quit) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // ENGINE
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();

        // GAME
        game.Update(dt);

        // RENDERING
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        // character
        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());


        Engine::Get().GetRenderer().Present();
    }

    Engine::Get().Shutdown();

    return 0;
}