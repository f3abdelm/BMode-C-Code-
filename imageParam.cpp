#include "imageParam.h"

imageParam::imageParam()
{
    // declaring variables with set values 
    numScanline = 127;
    numElement = 128; 
    numSample = 3338; 
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); 
    elementPosition = genElementPosition(); 
}

imageParam::~imageParam()
{
    deletePositionArray(); // calls on this function to releases the arrays dynamically allocated for different variables 
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    float *eleLocation; // declare eleLocation float 
    eleLocation = new float[numElement]; // defines eleLocation float array based on numElement 

    for (int x = 0; x < numElement; x++){ // uses equation to assign every element of eleLocation 
        eleLocation[x] = (x-((float)numElement-1.0)/2.0)*PITCH;
    }

    return eleLocation; // returns the element position array 

}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    std::cout << "Enter your desired scanline depth: "; // prompts user for desired scanline depth 
    std::cin >> desiredDepth; // stores user's input for scanline depth
    std:: cout << "Enter the number of pixels you would like: "; // prompts user for desired number of pixels 
    std::cin >> numPixel; // stores user's input for number of pixels 

    float2 **scanlinePosition; 
    scanlinePosition = new float2*[numScanline]; 
    for (int a = 0; a < numScanline; a++){ // for loop to derive the position of each scanline 
        scanlinePosition[a] = new float2[numPixel];
        for (int f = 0; f < numPixel; f++){
            scanlinePosition[a][f].x = ((a - (((float)numScanline-1.0)/2.0))*PITCH); 
            scanlinePosition[a][f].y = (f*(desiredDepth/(numPixel-1))); 
        }
    }
    return scanlinePosition; 
}

float imageParam::getXPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].x; // returns the x-coordinate of a pixel 
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y; // returns the y-coordinate of a pixel 

}

float imageParam::getElementPosition(int element)
{
    return elementPosition[element]; // returns the position of an element
}

int imageParam::getNumElement()
{
    return numElement; // returns the private data component of the class 
}

int imageParam::getNumSample()
{   
    return numSample; // returns the private data component of the class 
}

int imageParam::getNumScanline() 
{
    return numScanline; // returns the private data component of the class 
}

int imageParam::getNumPixel() 
{
    return numPixel; // returns the private data component of the class 
}

void imageParam::deletePositionArray()
{   
    delete elementPosition; // releases the memory allocated for elementPosition 
    for (int x = 0; x < numScanline; x++){ // for loop to release the memory allocated in each element of the scanlinePosition 
        delete scanlinePosition[x]; 
    }
}









