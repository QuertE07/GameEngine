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

    //{
    //    std::ifstream file("data/text.txt");
    //    if (file.is_open())
    //    {
    //        std::string str;
    //        while (std::getline(file, str))
    //        {
    //            std::cout << str << std::endl;
    //        }
    //    }
    //    else
    //    {
    //        std::cout << "Could not load file." << std::endl;
    //    }
    //    file.close();
    //}

    //{
    //    std::ofstream file("data/text.txt", std::ios::app);
    //    if (file.is_open())
    //    {
    //        file << "Have a good day.\n";
    //    }
    //    file.close();
    //}

    //{
    //    std::fstream file("data/text.txt", std::ios::in | std::ios::out | std::ios::app);
    //    if (file.is_open())
    //    {
    //        // input
    //        file << "Add a line.\n";
    //        file.seekg(0);
    //        // output
    //        std::string str;
    //        while (std::getline(file, str))
    //        {
    //            std::cout << str << std::endl;
    //        }
    //    }
    //    file.close();
    //}

    //{
    //    std::string name;
    //    int score;
    //    bool isAlive;

    //    bool save = false;
    //    if (save)
    //    {
    //        name = "Luigi";
    //        score = 4;
    //        isAlive = true;

    //        std::ofstream file("data/game.txt", std::ios::trunc);
    //        if (file.is_open())
    //        {
    //            file << name << "\n";
    //            file << score << "\n";
    //            file << isAlive << "\n";
    //        }
    //    }

    //    bool load = true;
    //    if (load)
    //    {
    //        std::ifstream file("data/game.txt");
    //        if (file.is_open())
    //        {
    //            std::getline(file, name);

    //            std::string str;
    //            std::getline(file, str);

    //            score = std::stoi(str);

    //            file >> isAlive;
    //        }
    //    }

    //    std::cout << name << std::endl;
    //    std::cout << score << std::endl;
    //    std::cout << isAlive << std::endl;

    //}

    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("data/data.json", document))
        {
            // read/show the data from the json file
            std::string name;
            int age;
            float speed;
            bool isAwake;
            Vector2 position;
            Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }
    }

    //Document document;
    //document.Parse(json);

    //return 0;

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