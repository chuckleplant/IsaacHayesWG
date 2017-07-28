#include "ofApp.h"
#include "ofxAppEmscriptenWindow.h"
#include <emscripten/val.h>
#include "ofxBase64.h"

using namespace emscripten;


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
    val Objecto = val::global("Objecto");

    if(!Objecto.as<bool>())
    {
        ofLog()<< "No objecto exists";
    }
    else
    {
        //ofLog() << "Magic";
    }

    val julipendio = val::global("Objecto").new_();
    bool gotFile = julipendio.call<bool>("gotFile");
    if(gotFile)
    {
        ofLogNotice() << "YOO";
        string fileStream = julipendio.call<string>("getFileStream");
        ofLog() << "file length" <<fileStream.size();

        ofBuffer imageBuffer; 
        ofxBase64Decode(fileStream, imageBuffer);
        ofLog() << "Loaded : " << ofLoadImage(sceneImage.getPixels(), imageBuffer);   
    }

    //julipendio.call<void>("methodInteger", 123);
   // Objecto.call<void>("methodInteger", 123);

   //double now = val::global("Date").call<double>("now");
    //ofLog() << "Now : " << now;


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

    sceneImage.draw(mouseX, mouseY);
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
