#ifndef LEVELLOADER_HPP_
#define LEVELLOADER_HPP_

#include <string>

#include "World.hpp"

// This is a very simple level loader.

class LevelLoader
{
public:
    static Level load(std::string filename);
};

#endif  // LEVELLOADER_HPP_