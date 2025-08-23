#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) {

    viper::file::SetCurrentDirectory("Assets");
    viper::Logger::Info("current directory: {}", viper::file::GetCurrentDirectory());

    // Intialize engine
    viper::Logger::Warning("Viper Engine is initializing...");
    viper::GetEngine().Initialize();

    //Initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    auto texture = viper::Resources().Get<viper::Texture>("textures/player.png", viper::GetEngine().GetRenderer());

    SDL_Event e;
    bool quit = false;
    float rotate = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) { quit = true; }

        // Update input system
        viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        // Clear the renderer
        viper::vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        game->Draw(viper::GetEngine().GetRenderer());

        viper::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}