#include "LevelLoader.hpp"

#include <string>
#include <fstream>
#include <vector> 

#include "character/goomba/Goomba.hpp"
#include "environment/BrickBlock.hpp"
#include "environment/CoinBlock.hpp"
#include "environment/GroundBlock.hpp"
#include "environment/Background.hpp"
#include "environment/Mushroom.hpp"
#include "math/Vector2.hpp"

class Object;

// This is a very simple and messy level loader

Level LevelLoader::load(std::string filename)
{
    std::vector<Object*> objects;
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
                case '0' : object = new environment::GroundBlock(); break;
                case '1' : object = new environment::BrickBlock(); break;
                case '2' : object = new environment::CoinBlock(position); break;
                case 'q' : object = new environment::Background(BitmapType::BUSH_LEFT); break;
                case 'w' : object = new environment::Background(BitmapType::BUSH_MIDDLE); break;
                case 'e' : object = new environment::Background(BitmapType::BUSH_RIGHT); break;
                case 'a' : object = new environment::Background(BitmapType::HILL_LEFT); break;
                case 's' : object = new environment::Background(BitmapType::HILL_MIDDLE); break;
                case 'd' : object = new environment::Background(BitmapType::HILL_MIDDLE_2); break;
                case 'f' : object = new environment::Background(BitmapType::HILL_MIDDLE); break;
                case 'g' : object = new environment::Background(BitmapType::HILL_RIGHT); break;
                case 'h' : object = new environment::Background(BitmapType::HILL_TOP); break;
                case 'p' : object = new character::goomba::Goomba(); break;
                case 'm' : object = new environment::Mushroom(); break;

                /** background but collidable - nasty hack for now **/
                case 'z' : object = new environment::Background(BitmapType::PIPE_TOP_LEFT); object->collidable = true; break;
                case 'x' : object = new environment::Background(BitmapType::PIPE_TOP_RIGHT); object->collidable = true; break;
                case 'c' : object = new environment::Background(BitmapType::PIPE_BOTTOM_LEFT); object->collidable = true; break;
                case 'v' : object = new environment::Background(BitmapType::PIPE_BOTTOM_RIGHT); object->collidable = true; break;
            }

            object->position = position;
            objects.push_back(object);
            
            columnIndex++;
        }
        lineIndex++;
    }
    return Level {objects, {}};
}