#include "FlowerGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <fmod.hpp>
#include <map>
#include <memory>
#include <fstream>

using namespace gl;

int main()
{
    SetWorkingDirectory("Assets");
    if (Engine::Get().Initialize() == false) return 0;

    //return 0;

    FlowerGame game;
    game.Initialize();

    // SFX init
    Engine::Get().GetAudio().AddSound("bgm", "audio/bgm.mp3");
    Engine::Get().GetAudio().AddSound("CompleteCharge", "audio/ELPELT.mp3");
    Engine::Get().GetAudio().AddSound("FlowerWilt", "audio/COUNTER.mp3");

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