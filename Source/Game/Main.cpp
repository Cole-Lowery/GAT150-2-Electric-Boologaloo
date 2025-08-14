
#include "Game/SpaceGame.h"


int main(int argc, char* argv[]) {

    std::filesystem::current_path("Assets");

	//Command Line Arguments
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
		viper::Logger::Debug("Arg {}: {}", i, argv[i]);
	}

    //Streams
	/*std::cout << "Hello World!" << std::endl;
	int age{ 0 };
	std::cout << "Enter your age: ";
    if (!(std::cin >> age)) {
		std::cerr << "Invalid input. Please enter a number." << std::endl;
    }
    std::cout << "You are " << age << " years old." << std::endl;*/

    std::fstream stream("test.txt");
    if (!stream) {
        std::cout << "Failed to open file." << std::endl;
    }
	std::string line;
    while (std::getline(stream, line)) {
        std::cout << line << std::endl;
	}

	viper::vec2 v{ 34.5f, 65.5f };
	std::cout  << v << std::endl;

	viper::vec3 v3{ 1.0f, 0.5f, 0.25f };
	std::cout << v3 << std::endl;

	std::string vstr = "{1.0, 2.0}";
	std::stringstream sstream(vstr);

	viper::vec2 v2;
	sstream >> v2;

	std::cout << v2 << std::endl;

    //initialize engine
    viper::GetEngine().Initialize();

    viper::Logger::Info("Initialize engine...");

    //Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
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