
//#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"



int main(int argc, char* argv[]) {

    viper::file::SetCurrentDirectory("Assets/Platformer");

    //initialize engine
    viper::GetEngine().Initialize();

    viper::Logger::Info("Initialize engine...");

    //Initialize Game
    std::unique_ptr<viper::Game> game = std::make_unique<PlatformerGame>();
    game->Initialize();

    //create objects
    viper::Font* font = new viper::Font();
    font->Load("Prisma.ttf", 20);
    FMOD::Sound* sound = nullptr;

    std::vector<FMOD::Sound*> sounds;

    SDL_Event e;
    bool quit = false;
    float rotate = 0;


    //Main Loop
    while (!quit) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        viper::GetEngine().Update();

        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //draw
        viper::vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor((float)color.r, (float)color.g, (float)color.b);
        viper::GetEngine().GetRenderer().Clear();

        viper::GetEngine().Draw();
        //Draw
        game->Draw(viper::GetEngine().GetRenderer());


        //present
        viper::GetEngine().GetRenderer().Present();

    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}