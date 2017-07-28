#include "ShaftGui.h"
#include "ofxAppEmscriptenWindow.h"

#define STRINGIFY(s) #s 



extern "C"
{
    int int_sqrt(int x)
    {
        return sqrt(x);
    }
}

void ShaftGui::setup(std::function<void(string const &)> loadImage)
{

    debugy = "initial"; 
    loadImageFunction = loadImage;

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
    
    loadImageButton.addListener(this, &ShaftGui::loadImageButtonPressed);
    saveSnapshotButton.addListener(this, &ShaftGui::saveSnapshot);
    
    gui.setup(parameters);
    gui.add(loadImageButton.setup("Load image"));
    gui.add(saveSnapshotButton.setup("Save image"));
    
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

extern "C"{
    void testJSCall(int x)
    {
        printf("Size %d", x);
    }
}



extern "C" 
{
    int receive_base_64(int ptr)
    {
        printf("pointer at %d", ptr);
    }    
}


void ShaftGui::loadImageButtonPressed()
{
/*         int test_int = emscripten_run_script_int(STRINGIFY(
            function loadDialog()
            {
                var input = document.createElement('input');
                input.type = 'file';
                input.click();
                return input.data.length;
                //var reader = new FileReader();
                //var stringfile = reader.reasAsBinaryString(input.data);
                //return stringfile.length;
            }
            loadDialog();
        ));
        ofLogNotice() << "int : " << test_int; */



 
        char * somestring = emscripten_run_script_string(STRINGIFY(
            function loadDialog()
            {
                var input = document.createElement('input');
                input.type = 'file';
                input.click();
                return "Whot";
                //return input.value;

               // var reader = new FileReader();
                //reader.reasAsBinaryString(input.data);
                
            }
            loadDialog();
        )
        );

        ofLogNotice() << "File as string? : " << somestring; 

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

