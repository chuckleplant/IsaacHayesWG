#include "LightShaft.h"
#include "ofMain.h"
#include "ofFileUtils.h"
using namespace glm;
using namespace std;

LightShaft::LightShaft() : 
    imageDimension(10,10),
    bLocked(false)
{
}


LightShaft::~LightShaft()
{
}

void LightShaft::setGui(ShaftGui * shaftGui)
{
    gui = shaftGui;

    ofLog() << "Load shaders : "<< shader.loadShaders();

    ofBuffer buf = ofBufferFromFile(ofToDataPath("RDR2.png"));
    ofPixels wut;
    if(ofLoadImage(wut, buf))
    {
       ofLog() << "Loaded image, wxh = "<< wut.getWidth() <<","<< wut.getHeight();
       sceneImage.setFromPixels(wut.getData(), wut.getWidth(), wut.getHeight(), OF_IMAGE_COLOR_ALPHA);
       sceneImage.update();
       allocateBuffers(sceneImage);
    }
    
}

void LightShaft::allocateBuffers(ofImage const & loadedImage)
{
    imageDimension.x = loadedImage.getWidth();
    imageDimension.y = loadedImage.getHeight();
    ofLog() << "Allocating buffers : (" << imageDimension.x <<", "<<imageDimension.y <<")";
    blackness.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    sceneBuffer.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    shaftComposite.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    sceneImage = ofImage(loadedImage);
    resizeLayout();
}

/*
void ofApp::renderBackground(ofFbo const & targetBuffer)
{
    ofPushMatrix();
    ofVec2f fboScale = ofVec2f(targetBuffer.getWidth() / ofGetWindowWidth(), targetBuffer.getHeight() / ofGetWindowHeight());
    ofScale(fboScale);
    ofBackgroundGradient(accentColor, baseColor);
    ofPopMatrix();
}
*/

void LightShaft::render(ofVec2f const & sunPosition, ofImage const & sceneImage)
{
    // Black buffer, only the sun is rendered
    blackness.begin();
        ofClear(0, 0);
        ofSetColor(gui->getSunColor());
        ofDrawCircle(sunPosition.x, sunPosition.y, gui->getSunRadius());
        ofSetColor(ofColor::black);
        sceneImage.draw(0,0);
    blackness.end();


    // Draw the scene without shafts
    sceneBuffer.begin();
        ofClear(0, 1);
        ofSetColor(255);

        // Draw background
        ofPushMatrix();
            ofVec2f fboScale = ofVec2f(sceneBuffer.getWidth() / ofGetWindowWidth(), sceneBuffer.getHeight() / ofGetWindowHeight());
            ofScale(fboScale.x, fboScale.y);
            ofBackgroundGradient(gui->getAccentColor(), gui->getBaseColor());
        ofPopMatrix();

        // Draw sun (not strictly necessary)
        ofDrawCircle(sunPosition.x, sunPosition.y, gui->getSunRadius());
        sceneImage.draw(0,0);
    sceneBuffer.end();
    
}

void LightShaft::setWindowSize(int windowWidth, int windowHeight)
{
    windowDimension.x = windowWidth;
    windowDimension.y = windowHeight;
}

void LightShaft::resizeLayout()
{
    float imageAspect = imageDimension.x/(float)imageDimension.y;
    float windowAspect = windowDimension.x/(float)windowDimension.y;
    if(imageAspect > windowAspect){
        renderLayout.x = 0;
        renderLayout.width = windowDimension.x;
        renderLayout.height = windowDimension.x / imageAspect;
        renderLayout.y = (windowDimension.y - renderLayout.height)/2;
    }
    else{
        renderLayout.y = 0;
        renderLayout.height = windowDimension.y;
        renderLayout.width = windowDimension.y * imageAspect;
        renderLayout.x = (windowDimension.x - renderLayout.width)/2;
    }
}

void LightShaft::toggleLock()
{
    bLocked = !bLocked;
}

void LightShaft::draw()
{
    if(!bLocked)
    {
        unsigned int originMouseX = ofGetMouseX() - renderLayout.x;
        unsigned int originMouseY = ofGetMouseY() - renderLayout.y;
        ofVec2f normalizedMousePos = ofVec2f(originMouseX / renderLayout.width, originMouseY / renderLayout.height);
        cursorPosition.x = normalizedMousePos.x * (imageDimension.x);
        cursorPosition.y = normalizedMousePos.y * (imageDimension.y);
    }

    // Draw shaft mask
    //
    //
    blackness.begin();
    ofClear(0,0);
    ofSetColor(gui->getSunColor());
    ofDrawCircle(cursorPosition.x, cursorPosition.y, gui->getSunRadius());
    ofSetColor(ofColor::black);
    sceneImage.draw(0,0);
    blackness.end();

    // Draw scene
    //
    //
    sceneBuffer.begin();
        ofClear(0, 1);
        ofSetColor(255);
        ofBackgroundGradient(gui->getAccentColor(), gui->getBaseColor());
        ofDrawCircle(cursorPosition.x, cursorPosition.y, gui->getSunRadius());
        sceneImage.draw(0,0);
    sceneBuffer.end();


    // Draw shaft composite 
    //
    //
    shaftComposite.begin();
        ofClear(0, 0);
        glm::vec2 normalizedLightPos = glm::vec2(cursorPosition.x / (float)imageDimension.x, cursorPosition.y / (float)imageDimension.y);
        shader.begin();
            shader.setUniformTexture("scene", sceneBuffer.getTexture(), 1);
            shader.setUniformTexture("lightMap", blackness.getTexture(), 2);
            shader.setUniform2f("lightPosition", normalizedLightPos);
            shader.setUniform1f("decay", gui->getDecay());
            shader.setUniform1f("density", gui->getDensity());
            shader.setUniform1f("weight", gui->getWeight());
            shader.setUniform1i("numSamples", gui->getNumSamples());
            ofFill();
            sceneImage.draw(0,0,windowDimension.x,windowDimension.y);
        shader.end();
    shaftComposite.end();














    ofSetColor(ofColor::white);
    shaftComposite.draw(0,0);




    
    /*
    shader.begin();
        shader.setUniformTexture("image", sceneImage.getTexture(),1);
        sceneImage.draw(renderLayout);
    shader.end();


    ofSetColor(gui->getSunColor());
    ofDrawCircle(cursorPosition.x, cursorPosition.y, gui->getSunRadius());
    //sceneBuffer.draw(0,0);
    */
}
