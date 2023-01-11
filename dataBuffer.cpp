#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    // declaring the variables by assigning a value to the following integers  
    numElement = 0; 
    numSample = 0; 
    scanline = 0;
    dataMatrix = NULL; // assigning a value of NULL to the dataMatrix double pointer
    next = NULL; // assigning a value of NULL to the next pointer 
}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    numElement = inputNumElement; 
    numSample = inputNumSample; 
    scanline = inputScanline; 
    dataMatrix = createDataMatrix ();  
    loadRFData(dataMatrix, imagFile, realFile); // this function fills the dataMatrix with the ultrasound data stored in the file for data reading 
} 

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // function calls on deleteDataMatrix to release RFData
}

complex **dataBuffer::createDataMatrix()
{
    complex **dataMatrix; 
    dataMatrix = new complex*[numElement]; 
    for (int x = 0; x < numElement; x++){ // dynamically allocates the dataMatrix 2D array and assign it to dataMatrix 
        dataMatrix[x] = new complex [numSample]; 
    }
    return dataMatrix; 
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    const int MAX_SIZE = 15; 
    char line [MAX_SIZE]; // character array with a maximum length of 15 5o store the imput data from the files
    int count = 0; 
    for (int x = 0; x < numElement; x++){ // for loops to get the data lines from the text files 
        for (int y = 0; y < numSample; y++){
            count = count + 1; 
            imagFile -> getline(line,MAX_SIZE); 
            RFData[x][y].imag = atof(line); 
            realFile -> getline(line,MAX_SIZE); 
            RFData[x][y].real = atof(line); 
            
        }
    }
    return 0; 
}

float dataBuffer::getRealRFData(int element,int sample)
{
    return dataMatrix[element][sample].real; // returns the real part of the data of dataMatrix at a specific locatiom
}
float dataBuffer::getImagRFData(int element,int sample)
{
    return dataMatrix[element][sample].imag; // returns the imaginary part of the data of dataMatrix at a specific location 
}

void dataBuffer::deleteDataMatrix()
{
    // for loop to release the dynamically allocated memory of each element in dataMatrix
    for (int x = 0; x < numElement; x++){
        delete dataMatrix[x]; 
    } // for loop ends 
}




