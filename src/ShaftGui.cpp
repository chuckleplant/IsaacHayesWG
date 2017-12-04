#include "ShaftGui.h"
#include "ofxAppEmscriptenWindow.h"

void ShaftGui::setup()
{
    decay.setMin(0.8);
    decay.setMax(1.0);
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
    sunResolution.addListener(this, &ShaftGui::sunResolutionChanged);
    
    parameters.setName("settings");
    parameters.add(cursorMoves.set("Move sun ([Right click])", true));
    parameters.add(decay.set("Decay", 0.946));    
    parameters.add(weight.set("Weight", 0.74));
    parameters.add(density.set("Density", 0.9));
    parameters.add(numSamples.set("Samples", 100));
    parameters.add(sunRadius.set("Sun radius", 230.0));
    parameters.add(sunResolution.set("Sun resolution", 26));
    parameters.add(baseColor.set("Base color", ofColor(155,41,33)));
    parameters.add(accentColor.set("Accent color", ofColor(228,77,65)));
    parameters.add(sunColor.set("Sun color", ofColor::orangeRed));
    
    //saveImageButton.addListener(this, &ShaftGui::savePressed);
    gui.setup(parameters);
    gui.add(saveImageButton.setup("Save image"));
    
    gui.setPosition(100, 100);
}

ofxButton & ShaftGui::getSaveButton()
{
    return saveImageButton;
}

ofColor const & ShaftGui::getBaseColor() const
{
    return baseColor.get();
}

ofColor const & ShaftGui::getAccentColor() const
{
    return accentColor.get();
}

ofColor const & ShaftGui::getSunColor() const
{
    return sunColor.get();
}

void ShaftGui::draw()
{
    gui.draw();
}

void ShaftGui::sunResolutionChanged(int& circleResolution)
{
    ofSetCircleResolution(circleResolution);
}

void ShaftGui::saveSnapshot()
{
}

float const & ShaftGui::getSunRadius() const
{
    return sunRadius.get();
}

float const & ShaftGui::getDecay() const
{
    return decay.get();
}


float const & ShaftGui::getDensity() const
{
    return density.get();
}

float const & ShaftGui::getWeight() const
{
    return weight.get();
}

int const & ShaftGui::getNumSamples() const
{
    return numSamples.get();
}

int const & ShaftGui::getSunResolution() const
{
    return sunResolution.get();
}

bool const & ShaftGui::isCursorMoving() const
{
    return cursorMoves.get();
}

void ShaftGui::toggleCursor()
{
    cursorMoves = !cursorMoves;
}

