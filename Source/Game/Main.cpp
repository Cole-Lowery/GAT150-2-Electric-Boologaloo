
#include "Game/SpaceGame.h"


int main(int argc, char* argv[]) {

    viper::file::SetCurrentDirectory("Assets");

    // load the json data from a file
    std::string buffer;
    viper::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    viper::json::Load("json.txt", document);

    // read the age data from the json
    int age;
    viper::json::Read(document, "age", age);
    // show the age data
    std::cout << age << std::endl;

    // read/show the data from the json file
    std::string name;
    float speed;
    bool isAwake;
    viper::vec2 position;
    viper::vec3 color;

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

    //initialize engine
    viper::GetEngine().Initialize();

    viper::Logger::Info("Initialize engine...");

    //Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    //create objects


    viper::Font* font = new viper::Font();
    font->Load("Archeologicaps.ttf", 20);

    FMOD::Sound* sound = nullptr;

    std::vector<FMOD::Sound*> sounds;

    //Texture
 
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