#include "Game/SpaceGame.h"

class Animal {
public:
    virtual void Spreak() = 0;
};

class Cat : public Animal {
public:
    void Spreak() override { std::cout << "Meow!\n"; }
};

class Dog : public Animal {
public:
    void Spreak() override { std::cout << "Woof!\n"; }
};

class Bird : public Animal {
public:
    void Spreak() override { std::cout << "Cherp!\n"; }
};

Animal* CreateAnimal(int id) {
    Animal* animal = nullptr;
    switch (id) {
    case 1:
        animal = new Cat;  break;
    case 2:
        animal = new Dog;  break;
    case 3:
        animal = new Bird; break;
    }
    return animal;
};

int main(int argc, char* argv[]) {

    viper::file::SetCurrentDirectory("Assets");
    viper::Logger::Info("current directory: {}", viper::file::GetCurrentDirectory());

    auto spriteRenderer = viper::Factory::Instance().Create("SpriteRenderer");
    spriteRenderer->name = "Steve";


    return 0;

    //Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    //create objects


    viper::Font* font = new viper::Font();
    font->Load("Prisma.ttf", 20);

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