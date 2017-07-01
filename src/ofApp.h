#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		ofVec2f getRenderDimensions();
		
		void loadImageButtonPressed(){}
    void sunResolutionChanged(int& circleResolution){}
	void saveSnapshot(){}

    	ofParameter<ofColor> baseColor;
    	ofParameter<ofColor> accentColor;
    	ofParameter<ofColor> sunColor;
    	ofParameter<float> sunRadius;
    	ofParameter<float> decay;
    	ofParameter<float> exposure;
    	ofParameter<float> density;
    	ofParameter<float> weight;
    	ofParameter<int> numSamples;
    	ofParameter<int> sunResolution;
    	ofParameter<bool> moveSun;
    	ofxButton loadImageButton;
    	ofxButton saveSnapshotButton;

		ofParameterGroup parameters;
		ofxPanel gui;
};
