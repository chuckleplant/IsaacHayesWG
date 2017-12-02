#include "ShaftShader.h"
using namespace std;

#define STRINGIFY(x) #x

ShaftShader::ShaftShader()
{
    vertShader = STRINGIFY(
        attribute vec4 position;
        attribute vec2 texcoord;
        uniform mat4 modelViewProjectionMatrix;
        varying vec2 texCoordVar;
        void main(){
            texCoordVar = texcoord;
            gl_Position = modelViewProjectionMatrix * position;
        }
    );

    fragShader = STRINGIFY(
        precision highp float;
        uniform sampler2D image;
        varying vec2 texCoordVar;
        void main()
        {
            // gl_FragCoord contains the window relative coordinate for the fragment.
            // we use gl_FragCoord.x position to control the red color value.
            // we use gl_FragCoord.y position to control the green color value.
            // please note that all r, g, b, a values are between 0 and 1.
            gl_FragColor = texture2D(image, texCoordVar);
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