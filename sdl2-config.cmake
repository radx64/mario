set(SDL2_INCLUDE_DIRS "${SDL2_PATH}/x86_64-w64-mingw32/include")
set(SDL2_LIBRARIES "${SDL2_PATH}/x86_64-w64-mingw32/lib/libSDL2.a;${SDL2_PATH}/x86_64-w64-mingw32/lib/libSDL2main.a")
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
