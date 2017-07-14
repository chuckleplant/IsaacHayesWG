#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    shaftGui.setup();

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
    ofDrawBitmapStringHighlight(ofToString(ofGetWindowWidth()), ofGetMouseX(), ofGetMouseY());
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
