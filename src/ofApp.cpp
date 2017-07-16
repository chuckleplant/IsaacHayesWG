#include "ofApp.h"
#include "ofxAppEmscriptenWindow.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
#ifdef TARGET_OSX
ofLogNotice() << "osx";
#endif
#ifdef TARGET_WIN32
ofLogNotice() << "win";
#endif
#if defined( TARGET_LINUX ) && defined (OF_USING_GTK)
ofLogNotice() << "lin";
#endif

    shaftGui.setup(std::bind(&ofApp::setupImageResourcesFromImage, this, std::placeholders::_1));

    ////
    // Scene params
    //ofBackground(0, 0, 0);
    //ofSetVerticalSync(true);
    //ofDisableDepthTest();
    ofEnableAlphaBlending();
}

ofVec2f ofApp::getRenderDimensions()
{
    return ofVec2f(500,500);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    //Draw background
    ofPushMatrix();
    ofVec2f size = getRenderDimensions();
    //ofScale(size.x, size.y);
    //ofBackgroundGradient(accentColor, baseColor);
    ofBackgroundGradient(shaftGui.getAccentColor(), shaftGui.getBaseColor());
    ofPopMatrix();
    shaftGui.draw();
    ofDrawBitmapStringHighlight(shaftGui.debugy, ofGetMouseX(), ofGetMouseY());
}

void ofApp::setupImageResourcesFromImage(string const & imageFilename)
{
    if(sceneImage.load(imageFilename))
    {
        ofLog() << "log?";
    }
    else
    {
        ofSystemAlertDialog("Could not load image file ("+ imageFilename +")");
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
