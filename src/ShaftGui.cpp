#include "ShaftGui.h"
#include "ofxAppEmscriptenWindow.h"

void ShaftGui::setup()
{
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
    sunResolution.addListener(this, &ShaftGui::sunResolutionChanged);
    
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
    
    
    gui.setup(parameters);
    
    gui.setPosition(100, 100);
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

float const & ShaftGui::getExposure() const
{
    return exposure.get();
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

bool const & ShaftGui::isSunMoving() const
{
    return moveSun.get();
}

