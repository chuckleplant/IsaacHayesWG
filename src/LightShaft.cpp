#include "LightShaft.h"
#include "ofMain.h"
LightShaft::LightShaft() 
{
    blackness.allocate(20,20,GL_RGBA);
    sceneBuffer.allocate(20,20,GL_RGBA);
    shaftComposite.allocate(20,20,GL_RGBA);
}


LightShaft::~LightShaft()
{
}

void LightShaft::setGui(ShaftGui * shaftGui)
{
    gui = shaftGui;
}

void LightShaft::allocateBuffers(ofImage const & loadedImage)
{
    blackness.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    sceneBuffer.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    shaftComposite.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
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


void LightShaft::draw()
{
    sceneBuffer.draw(0,0);
}
