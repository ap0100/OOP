#include <cmath>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

const int size=1024;

struct Pixel {
    uint8_t R, G, B;
};

struct imageRGB {
    Pixel image[size][size];
};

void imageWriter(imageRGB img) {
    ofstream outFile("example.ppm");
    outFile << "P3" << '\n' << size << " " << size <<  '\n' << "255" << '\n';
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            outFile << static_cast<int>(img.image[i][j].R)
            << " " << static_cast<int>(img.image[i][j].G)
            << " " << static_cast<int>(img.image[i][j].B) << "\n";
        }
    }

    outFile.close();
}

int main() {
    imageRGB img;
    float distance=0,  maxDistance=sqrt(2*pow((size/2), 2)), diff=0;
    int center=size/2;

    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            distance=static_cast<float>(sqrt(pow(center-i,2) + pow(center-j, 2)));
            diff=distance/maxDistance;
            diff=pow(diff,0.38);

            img.image[i][j].R=size-static_cast<uint8_t>((-diff)*60 + (diff)*200)-1;//static_cast<uint8_t>((-diff)*245)-1;
            img.image[i][j].G=55;//static_cast<uint8_t>((-diff)*255)-1;
            img.image[i][j].B=static_cast<uint8_t>((diff)*250 + (-diff)*175);//static_cast<uint8_t>((-diff)*240)-1;
        }
    }

    imageWriter(img);

    return 0;
}