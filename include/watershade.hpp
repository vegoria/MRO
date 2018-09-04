#pragma once

class Watershade
{
public:
    Watershade(int width, int heigth);
    ~Watershade();

    void setStartingPoint(int x, int y);
    void setImage(unsigned char** image);
    double performWatershade();
    void setTreshold(int treshold);


private:
    bool hasFloodedNeighbour(int x, int y);
    void floodVertical(int x, int y);
    void floodHorizontal(int x, int y);
    void floodImage();
    void markFloodedPixels();

    const int imageWidth;
    const int imageHeight;
    bool **floodedImage;
    unsigned char** image;
    int startX;
    int startY;
    int treshold;
};