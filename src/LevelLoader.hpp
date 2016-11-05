#include <string>
#include <fstream>
#include <vector> 

#include "environment/BrickBlock.hpp"
#include "environment/CoinBlock.hpp"
#include "environment/GroundBlock.hpp"
#include "environment/Background.hpp"

// This is a very simple level loader.

class LevelLoader
{
public:
    static std::vector<Object*> load(std::string filename)
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
                switch(c)
                {   
                    case ' ' : columnIndex++; continue;
                    case '0' : object = new environment::GroundBlock(columnIndex*lineIndex); break;
                    case '1' : object = new environment::BrickBlock(columnIndex*lineIndex); break;
                    case '2' : object = new environment::CoinBlock(columnIndex*lineIndex); break;

                    case 'q' : object = new environment::Background(BitmapType::BUSH_LEFT); break;
                    case 'w' : object = new environment::Background(BitmapType::BUSH_MIDDLE); break;
                    case 'e' : object = new environment::Background(BitmapType::BUSH_RIGHT); break;

                    case 'a' : object = new environment::Background(BitmapType::HILL_LEFT); break;
                    case 's' : object = new environment::Background(BitmapType::HILL_MIDDLE); break;
                    case 'd' : object = new environment::Background(BitmapType::HILL_MIDDLE_2); break;
                    case 'f' : object = new environment::Background(BitmapType::HILL_MIDDLE_3); break;
                    case 'g' : object = new environment::Background(BitmapType::HILL_RIGHT); break;
                    case 'h' : object = new environment::Background(BitmapType::HILL_TOP); break;


                }
                object->x = columnIndex * 32;
                object->y = lineIndex * 32;
                object->w = 32;
                object->h = 32;
                objects.push_back(object);
                columnIndex++;
            }
            lineIndex++;
        }

        return objects;
    }
};