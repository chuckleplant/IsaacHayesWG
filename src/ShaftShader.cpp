#include "ShaftShader.h"
using namespace std;

#define STRINGIFY(x) #x

ShaftShader::ShaftShader()
{
    vertShader = STRINGIFY(
        attribute vec4 position;
        uniform mat4 modelViewProjectionMatrix;
        void main(){
            gl_Position = modelViewProjectionMatrix * position;
        }
    );

    fragShader = STRINGIFY(
        precision highp float;
        void main()
        {
            // gl_FragCoord contains the window relative coordinate for the fragment.
            // we use gl_FragCoord.x position to control the red color value.
            // we use gl_FragCoord.y position to control the green color value.
            // please note that all r, g, b, a values are between 0 and 1.
            float windowWidth = 1024.0;
            float windowHeight = 768.0;
            float r = gl_FragCoord.x / windowWidth;
            float g = gl_FragCoord.y / windowHeight;
            float b = 1.0;
            float a = 1.0;
            gl_FragColor = vec4(r, g, b, a);
        }
    );
}


ShaftShader::~ShaftShader()
{

}


bool ShaftShader::loadShaders()
{
    ofLog() << "frag: " << ofShader::setupShaderFromSource(GL_FRAGMENT_SHADER, fragShader);
    ofLog() << "vert: " << ofShader::setupShaderFromSource(GL_VERTEX_SHADER, vertShader);
    ofLog() << "binddef: " << ofShader::bindDefaults();
    ofLog() << "link: " << ofShader::linkProgram();
    return false;

}