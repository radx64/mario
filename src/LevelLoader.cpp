#include "LevelLoader.hpp"

#include <string>
#include <fstream>
#include <vector>

#include "character/goomba/Goomba.hpp"
#include "environment/block/Bricks.hpp"
#include "environment/block/Coins.hpp"
#include "environment/block/Mushroom.hpp"
#include "environment/block/Question.hpp"
#include "environment/block/Ground.hpp"
#include "environment/Background.hpp"
#include "math/Vector2.hpp"

class Object;

// This is a very simple and messy level loader to speedup development
// Yes it is baaaad, really really baaaad. But works like a charm.

Level LevelLoader::load(std::string filename)
{
    std::vector<Object*> backObjects;
    std::vector<Object*> foreObjects;

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
                case '0' : object = new environment::block::Ground(); break;
                case '1' : object = new environment::block::Bricks(position); break;
                case '2' : object = new environment::block::Coins(position, 3); break;
                case 'q' : object = new environment::Background(SpriteType::BUSH_LEFT); break;
                case 'w' : object = new environment::Background(SpriteType::BUSH_MIDDLE); break;
                case 'e' : object = new environment::Background(SpriteType::BUSH_RIGHT); break;
                case 'a' : object = new environment::Background(SpriteType::HILL_LEFT); break;
                case 's' : object = new environment::Background(SpriteType::HILL_MIDDLE); break;
                case 'd' : object = new environment::Background(SpriteType::HILL_MIDDLE_2); break;
                case 'f' : object = new environment::Background(SpriteType::HILL_MIDDLE); break;
                case 'g' : object = new environment::Background(SpriteType::HILL_RIGHT); break;
                case 'h' : object = new environment::Background(SpriteType::HILL_TOP); break;
                case 'p' : object = new character::goomba::Goomba(); break;
                case 'm' : object = new environment::block::Mushroom(position); break;

                /** background but collidable - nasty hack for now **/
                case 'z' : object = new environment::Background(SpriteType::PIPE_TOP_LEFT); object->collidable_ = true; break;
                case 'x' : object = new environment::Background(SpriteType::PIPE_TOP_RIGHT); object->collidable_ = true; break;
                case 'c' : object = new environment::Background(SpriteType::PIPE_BOTTOM_LEFT); object->collidable_ = true; break;
                case 'v' : object = new environment::Background(SpriteType::PIPE_BOTTOM_RIGHT); object->collidable_ = true; break;
            }

            object->position = position;
            switch(c)
            {

                case '0' : 
                case '1' : 
                case '2' : 
                case 'm' : 
                case 'p' : 
                case 'z' : 
                case 'x' : 
                case 'c' : 
                case 'v' :  foreObjects.push_back(object);
                            break;

                case 'q' : 
                case 'w' : 
                case 'e' : 
                case 'a' : 
                case 's' : 
                case 'd' : 
                case 'f' : 
                case 'g' : 
                case 'h' :  backObjects.push_back(object);
                            break;             
            }
            
            columnIndex++;
        }
        lineIndex++;
    }
    return Level {backObjects, foreObjects, {}, {} };
}
