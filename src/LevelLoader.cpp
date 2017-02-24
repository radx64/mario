#include "LevelLoader.hpp"

#include <string>
#include <fstream>
#include <vector> 

#include "environment/BrickBlock.hpp"
#include "environment/CoinBlock.hpp"
#include "environment/GroundBlock.hpp"
#include "environment/Background.hpp"
#include "math/Vector2.hpp"

class Object;

// This is a very simple and messy level loader

Level LevelLoader::load(std::string filename)
{
    std::vector<Object*> gameObjects;
    std::vector<Object*> backgroundObjects;
    std::ifstream levelFile(filename);
    if (!levelFile.is_open())
    {
        throw std::runtime_error("Error opening " + filename);
    }
    std::string line;
    uint8_t lineIndex = 0;
    while (std::getline(levelFile, line))
    {
        uint16_t columnIndex = 0;
        for (auto const& c : line)
        {   
            Object* object = nullptr;
            math::Vector2f position = {columnIndex * 16.0f, lineIndex * 16.0f};
            switch(c)
            {   
                case ' ' : columnIndex++; continue;
                case '0' : object = new environment::GroundBlock(columnIndex*lineIndex); break;
                case '1' : object = new environment::BrickBlock(columnIndex*lineIndex); break;
                case '2' : object = new environment::CoinBlock(columnIndex*lineIndex, position); break;
                case 'q' : object = new environment::Background(BitmapType::BUSH_LEFT); break;
                case 'w' : object = new environment::Background(BitmapType::BUSH_MIDDLE); break;
                case 'e' : object = new environment::Background(BitmapType::BUSH_RIGHT); break;
                case 'a' : object = new environment::Background(BitmapType::HILL_LEFT); break;
                case 's' : object = new environment::Background(BitmapType::HILL_MIDDLE); break;
                case 'd' : object = new environment::Background(BitmapType::HILL_MIDDLE_2); break;
                case 'f' : object = new environment::Background(BitmapType::HILL_MIDDLE); break;
                case 'g' : object = new environment::Background(BitmapType::HILL_RIGHT); break;
                case 'h' : object = new environment::Background(BitmapType::HILL_TOP); break;

                /** background but collidable - nasty hack for now **/
                case 'z' : object = new environment::Background(BitmapType::PIPE_TOP_LEFT); break;
                case 'x' : object = new environment::Background(BitmapType::PIPE_TOP_RIGHT); break;
                case 'c' : object = new environment::Background(BitmapType::PIPE_BOTTOM_LEFT); break;
                case 'v' : object = new environment::Background(BitmapType::PIPE_BOTTOM_RIGHT); break;
            }

            object->position = position;

            switch(c)
            {
                case '0':
                case '1':
                case '2': 
                case 'z':
                case 'x':
                case 'c': 
                case 'v': gameObjects.push_back(object); break;

                case 'q': 
                case 'w': 
                case 'e': 
                case 'a': 
                case 's': 
                case 'd': 
                case 'f': 
                case 'g': 
                case 'h': backgroundObjects.push_back(object); break;
            }
            columnIndex++;
        }
        lineIndex++;
    }
    return Level {backgroundObjects, gameObjects, {}};
}