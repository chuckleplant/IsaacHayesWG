#pragma once
#include "ofFbo.h"
#include "ofVec2f.h"
#include "ofImage.h"
#include "ShaftGui.h"

class LightShaft
{
public:
    LightShaft();
    ~LightShaft();
    void setGui(ShaftGui * shaftGui);
    void allocateBuffers(ofImage const & loadedImage);
    void render(ofVec2f const & sunPosition, ofImage const & sceneImage);
    void toggleLock();
    void draw();
private:
    glm::vec2 cursorPosition;
    bool bLocked;
    ofFbo blackness;
    ofFbo sceneBuffer;
    ofFbo shaftComposite;
    ofImage sceneImage;
    ShaftGui * gui;
};