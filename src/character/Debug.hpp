#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include "Object.hpp"

class Context;

namespace character
{

class Debug : public Object
{
public:
    Debug(Context& context, int type);

    virtual void draw() override;
    virtual void simulate(std::vector<Object*> gameObjects) override;

protected:
    bool isObjectAt(std::vector<Object*> gameObjects, float x, float y);
    void bouceOfCeiling(Object* ceilingBlock);
    int r_{};
    int g_{};
    int b_{};
    bool jumped_{false};
    int simCount_{};
    Context& context_;
};

}  // namespace character

#endif  // DEBUG_HPP_
