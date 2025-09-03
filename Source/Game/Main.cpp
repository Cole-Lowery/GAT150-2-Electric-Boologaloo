
//#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"



int main(int argc, char* argv[]) {



    //return 0;

    viper::file::SetCurrentDirectory("Assets/Platformer");

   //initialize engine
    viper::GetEngine().Initialize();

    viper::Logger::Info("Initialize engine...");

    //Initialize Game
    std::unique_ptr<viper::Game> game = std::make_unique<PlatformerGame>();
    game->Initialize();

    //create objects


    viper::Font* font = new viper::Font();
    font->Load("Archeologicaps.ttf", 20);

    //viper::GetEngine().GetAudio().AddSound("laser_shoot.wav", "laser");
    /*
    viper::GetEngine().GetAudio().Inititalize();
    viper::GetEngine().GetAudio().AddBackGroundMusic("tetris.wav", "tetris");
    viper::GetEngine().GetAudio().AddBackGroundMusic("main_menu.wav", "main_menu");
    viper::GetEngine().GetAudio().AddBackGroundMusic("game_over.wav", "game_over");
    */

    FMOD::Sound* sound = nullptr;
    
    std::vector<FMOD::Sound*> sounds;
   
   //Texture
    //auto texture = viper::Resources().Get<viper::Texture>("Textures/creature.png", viper::GetEngine().GetRenderer());


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


        //Draw Texture ---------
        //rotate += 90 * viper::GetEngine().GetTime().GetDeltaTime();
        //viper::GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30, rotate , 4);

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
