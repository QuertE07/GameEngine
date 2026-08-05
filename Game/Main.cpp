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

int main()
{
    std::cout << "====================-object-=====================\n";
    {
        Object objectA;
        Object objectB = objectA;
        Object objectC;
        objectC = objectA;
    }

    std::cout << "\n====================-raw pointers-=====================\n";
    {
        Object* objectA = new Object;
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;
        Object* objectC = nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;
        
        delete objectA;
        delete objectB;
    }

    std::cout << "\n====================-smart pointers-=====================\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << std::endl;
    }

    //return 0;

    SetWorkingDirectory("Assets");
    if (Engine::Get().Initialize() == false) return 0;

    FlowerGame game;
    game.Initialize();

    // SFX init
    Engine::Get().GetAudio().AddSound("bgm", "audio/bgm.mp3");
    Engine::Get().GetAudio().AddSound("CompleteCharge", "audio/sparkle.mp3");
    Engine::Get().GetAudio().AddSound("FlowerWilt", "audio/wilt.mp3");

    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("textures/fiddlebothert.jpg", Engine::Get().GetRenderer());

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


        Engine::Get().GetRenderer().DrawTexture(texture.get(), 30, 30);


        Engine::Get().GetRenderer().Present();
    }

    Engine::Get().Shutdown();

    return 0;
}