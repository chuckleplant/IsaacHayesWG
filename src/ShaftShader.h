#pragma once
#include "ofShader.h"
#include <string>

class ShaftShader : public ofShader
{
public:
    ShaftShader();
    ~ShaftShader();
    bool loadShaders();
private:
    std::string fragShader;
    std::string vertShader;
};