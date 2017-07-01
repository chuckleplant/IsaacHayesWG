#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    decay.setMin(0.8);
    decay.setMax(1.0);
    exposure.setMin(0.0);
    exposure.setMax(2.0);
    weight.setMin(0.0);
    weight.setMax(2.0);
    density.setMin(0.0);
    density.setMax(2.0);
    numSamples.setMin(1);
    numSamples.setMax(300);
    sunRadius.setMin(10);
    sunRadius.setMax(500);
    sunResolution.setMin(3);
    sunResolution.setMax(90);
    sunResolution.addListener(this, &ofApp::sunResolutionChanged);
    
    parameters.setName("settings");
    parameters.add(moveSun.set("Move sun ([spacebar])", true));
    parameters.add(decay.set("Decay", 0.96815));
    parameters.add(exposure.set("Exposure", 0.2));
    parameters.add(weight.set("Weight", 0.58767));
    parameters.add(density.set("Density", 0.926));
    parameters.add(numSamples.set("Samples", 100));
    parameters.add(sunRadius.set("Sun radius", 50.0));
    parameters.add(sunResolution.set("Sun resolution", 20));
    
    parameters.add(baseColor.set("Base color", ofColor(255,235,197)));
    parameters.add(accentColor.set("Accent color", ofColor(235,215,167)));
    parameters.add(sunColor.set("Sun color", ofColor::orangeRed));
    
    loadImageButton.addListener(this, &ofApp::loadImageButtonPressed);
    saveSnapshotButton.addListener(this, &ofApp::saveSnapshot);
    
    gui.setup(parameters);
    gui.add(loadImageButton.setup("Load image"));
    gui.add(saveSnapshotButton.setup("Save image"));
    
    gui.setPosition(100, 100);

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
    ofBackgroundGradient(accentColor, baseColor);
    ofPopMatrix();
    gui.draw();

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
