#include "Engine.h"

#include <fmod.hpp>
#include <map>
#include <memory>
#include <fstream>

using namespace gl;

int main()
{
    SetWorkingDirectory("Assets");
    if (Engine::Get().Initialize() == false) return 0;

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

        // RENDERING
        Engine::Get().GetRenderer().BeginFrame();

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().EndFrame();
    }

    Engine::Get().Shutdown();

    return 0;
}