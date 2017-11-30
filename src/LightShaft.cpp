#include "LightShaft.h"
#include "ofMain.h"
LightShaft::LightShaft() : bLocked(false)
{
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
    ofLog() << "alloc buffers wh - "<< loadedImage.getWidth() << ", " << loadedImage.getHeight();
    blackness.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    sceneBuffer.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    shaftComposite.allocate(loadedImage.getWidth(), loadedImage.getHeight(), GL_RGBA);
    sceneImage = ofImage(loadedImage);
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

void LightShaft::toggleLock()
{
    bLocked = !bLocked;
}

void LightShaft::draw()
{
    if(!bLocked)
    {
        cursorPosition.x = ofGetMouseX();
        cursorPosition.y = ofGetMouseY();
    }
    sceneImage.draw(cursorPosition.x, cursorPosition.y);
    //sceneBuffer.draw(0,0);
}
