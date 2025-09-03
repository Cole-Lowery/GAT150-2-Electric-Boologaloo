#include "GameData.h"

namespace GameData {

    std::vector<viper::vec2> points{
        {5, 0},
        {-4, -3},
        {-2, 0},
        {-4, 3},
        {5, 0},
    };

    std::vector<viper::vec2> enemyDesign{
        { -4, 3 },
        { 0, 0 },
        { -4, -3 },
        { 3, -3 },
        { 3, 3 },
        { -4, 3 },
        { -4, -3 }
    };

    std::vector<viper::vec2> laser{
        { -10, -2 },
        { 10, -2 },
        { 10, 0 },
        { -10, 0 },
        { -10, -2 }
    };

    std::vector<viper::vec2> boost{
        {-1, 1},
        {-1, -1},
        {1, -1},
        {1, 1},
    };
}