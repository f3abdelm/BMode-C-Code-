#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    // declares pointers and variables with set values 
    line = 0; 
    imparams = NULL; 
    RFData = NULL; 
    next = NULL; 
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    // declares pointers and variables with set values 
    imparams = params; 
    RFData = data; 
    line = numline; 
    scanline = createScanline(imparams -> getNumPixel()); //invokes createScanline to allocate memory for scanline 
    beamform(); // invokes beamform to beamform the scanline 
}

BmodeClass::~BmodeClass()
{
    deleteScanline(); // releases the arrays dynamically allocated for scanline 
}

float *BmodeClass::createScanline(int numPixel)
{
    float *mem; 
    mem = new float[numPixel]; // dynamically allocates a 1D float of size numPixel 
    return mem; 
}

void BmodeClass::beamform()
{
    // delcares the variables and sets values for each variable (floats and integers) 
    float pReal = 0; 
    float pImag = 0; 
    int s = 0; 
    float time = 0; 

    for (int f = 0; f < imparams -> getNumPixel(); f++){ // for loops for calcuations 
        pReal = 0; 
        pImag = 0; 

        for (int a = 0; a < imparams -> getNumElement(); a++){ // for loop to calculate time and get the values of the variables in the class 
            time = (imparams -> getYPosition(line, f) + sqrt(pow(imparams -> getYPosition(line,f),2) + pow(imparams -> getXPosition(line, f) - imparams -> getElementPosition(a), 2)))/imparams -> SOS;
            s = floor(time*imparams -> FS); 
            if (s < imparams -> getNumSample()){
                pReal += RFData -> getRealRFData (a, s); 
                pImag += RFData -> getImagRFData (a, s); 
            }
            scanline[f] = sqrt(pow(pReal, 2) + pow(pImag, 2)); 
        }
    }
}

void BmodeClass::getScanline(float *data)
{
    for (int a = 0; a < imparams -> getNumPixel(); a++){ // for loop to copy the content inside each element of scanline to data 
        data[a] = scanline[a]; 
    }
}

void BmodeClass::deleteScanline()
{
    delete scanline; // releases the memory allocated for scanline 
}