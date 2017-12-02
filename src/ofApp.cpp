#include "ofApp.h"
#include "ofxAppEmscriptenWindow.h"
#include <emscripten/val.h>
#include "Base64.h"

using namespace emscripten;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofShader", OF_LOG_VERBOSE);
    sceneImage.allocate(10, 10, OF_IMAGE_COLOR);
    shaftGui.setup();
    shaft.setWindowSize(ofGetWindowWidth(), ofGetWindowHeight());
    shaft.setGui(&shaftGui);
    //shaft.allocateBuffers(sceneImage);
    ofLog() << " DATA PATH " << ofToDataPath("file");
    ////
    // Scene params
    //ofBackground(0, 0, 0);
    //ofSetVerticalSync(true);
    //ofDisableDepthTest();
    ofDisableArbTex();
    ofEnableAlphaBlending();
}



bool ofApp::imageLoaded()
{
    val CppBridge = val::global("CppBridge");
    if(!CppBridge.as<bool>())
    {
        ofLogError()<< "No CppBridge exists";
        return false;
    }

    val cppBridge = val::global("CppBridge").new_();
    bool gotFile = cppBridge.call<bool>("gotFile");
    if(gotFile)
    {
        ofLogNotice() << "File received from JavaScript";
        string fileStream = cppBridge.call<string>("getFileStream");
        ofLog() << "File base64 length : " <<fileStream.size();
        
        int decLen = Base64::DecodedLength(fileStream.c_str(), fileStream.size());
        char * outBuf = new char[decLen];
        bool decodeSucces = Base64::Decode(fileStream.c_str(), fileStream.size(), outBuf, decLen);
        bool loadSuccess = false;
        if(decodeSucces)
        {
            ofBuffer imageBuffer(outBuf, decLen); 
            ofLog() << "ofBuffer size : " << imageBuffer.size();
            loadSuccess = ofLoadImage(sceneImage.getPixels(), imageBuffer);   
            ofLog() << "Pixels w,h : "<< sceneImage.getWidth() << ", " << sceneImage.getHeight();
            sceneImage.update();

        }
        else
        {
            ofLog()<< "Failed to decode base64 file";
        }
        delete[] outBuf;
        return loadSuccess;
    }
    return false;
}


//--------------------------------------------------------------
void ofApp::update(){
    if(imageLoaded())
    {
        shaft.allocateBuffers(sceneImage);   
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::black);
    //Draw background
    //ofVec2f sunPos(mouseX, mouseY);
    //shaft.render(sunPos, sceneImage);
    shaft.draw();
    shaftGui.draw();
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
    if(button == 2)
    {
        shaft.toggleLock();
    }
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
