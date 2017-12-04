#include "LightShaft.h"
#include "ofMain.h"
#include "ofFileUtils.h"
#include "emscripten.h"
#include <emscripten/val.h>
#include "Base64.h"
#include "ofEvents.h"
using namespace glm;
using namespace std;
using namespace emscripten;


LightShaft::LightShaft() : 
    imageDimension(10,10),
    saveFlag(false)
{
}


LightShaft::~LightShaft()
{
}

void LightShaft::saveImage()
{
    saveFlag = true;
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

    // Listen to saveImage button
    gui->getSaveButton().addListener(this, &LightShaft::saveImage);
    ofAddListener(ofEvents().update, this, &LightShaft::update);
}

void LightShaft::allocateBuffers(ofImage const & loadedImage)
{
    imageDimension.x = loadedImage.getWidth();
    imageDimension.y = loadedImage.getHeight();
    blackness.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    sceneBuffer.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    shaftComposite.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    sceneImage = ofImage(loadedImage);
    resizeLayout();
}



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


bool LightShaft::encodeFrameBase64(const ofFbo & fbo, std::string & output)
{
    ofPixels renderPix;
    fbo.readToPixels(renderPix);
    ofBuffer pngBuffer;
    ofSaveImage(renderPix, pngBuffer);
    if(pngBuffer.size() > 0)
    {
        auto numBytes = pngBuffer.size();
        auto encodedLength = Base64::EncodedLength(numBytes);
        output.resize(encodedLength);
        const char * input = reinterpret_cast<const char *>(pngBuffer.getData());
        return Base64::Encode(input, numBytes, &output[0], output.size());
    }
    return false;
}


void LightShaft::submitFrameToBrowser(std::string const & frame64)
{
    val CppBridge = val::global("CppBridge");
    if(!CppBridge.as<bool>())
    {
        ofLogError()<< "No CppBridge exists";        
    }
    else
    {
        val cppBridge = val::global("CppBridge").new_();
        if(cppBridge.call<bool>("saveFramePNG", frame64))
        {
            ofLog() << "Submission to browser succeeded.";
        }
    }
}

void LightShaft::saveFBOAsPNG(const ofFbo & fbo)
{
    string encodedFrame;
    if(encodeFrameBase64(fbo, encodedFrame))
    {
        submitFrameToBrowser(encodedFrame);
    } 
    else
    {
        ofLogError() << "Failed to encode frame";
    }
}

void LightShaft::update(ofEventArgs&)
{
    if(saveFlag)
    {
        saveFBOAsPNG(shaftComposite);
        saveFlag = false;
    }
}

void LightShaft::draw()
{
    if(gui->isCursorMoving())
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
            sceneImage.draw(0,0);
        shader.end();
    shaftComposite.end();

    ofSetColor(ofColor::white);
    shaftComposite.draw(renderLayout);
}
