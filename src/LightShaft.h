#pragma once
#include "ofFbo.h"
#include "ofVec2f.h"
#include "ofImage.h"
#include "ShaftGui.h"
#include "ShaftShader.h"

class LightShaft
{
public:
    LightShaft();
    ~LightShaft();
    void setWindowSize(int w, int h);
    void setGui(ShaftGui * shaftGui);
    void allocateBuffers(ofImage const & loadedImage);
    void render(ofVec2f const & sunPosition, ofImage const & sceneImage);
    void toggleLock();
    void update(ofEventArgs&);
    void draw();
    void saveImage();
    
private:
    glm::vec2 imageDimension;
    glm::vec2 windowDimension;
    glm::vec2 cursorPosition;

    ofFbo blackness;
    ofFbo sceneBuffer;
    ofFbo shaftComposite;

    ofImage sceneImage;
    ofRectangle renderLayout;
    ShaftGui * gui;
    ShaftShader shader;
    bool saveFlag;

    void resizeLayout();
};