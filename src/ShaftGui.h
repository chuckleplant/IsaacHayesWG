#pragma once
#include "ofxGui.h"

class ShaftGui
{
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

    public:
		void setup();
        void draw();
        void loadImageButtonPressed();
        void sunResolutionChanged(int& circleResolution);
	    void saveSnapshot();

		ofColor const & getBaseColor() const;
		ofColor const & getAccentColor() const;
		ofColor const & getSunColor() const;
        float const & getSunRadius() const;
        float const & getDecay() const;
        float const & getExposure() const;
        float const & getDensity() const;
        float const & getWeight() const;
        int const & getNumSamples() const;
        int const & getSunResolution() const;
        bool const & isSunMoving() const;

        
};