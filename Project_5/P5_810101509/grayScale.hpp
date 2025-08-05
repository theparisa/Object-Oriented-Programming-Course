#ifndef GRAYSCALE_INCLUDE
#define GRAYSCALE_INCLUDE
#include "changeColorFilter.hpp"

class grayScale : public changeColorFilter
{
public:
    grayScale() : changeColorFilter()
    {
    }
    void applyFilter(Bmp *bmp);
};
void grayScale::applyFilter(Bmp *bmp)
{
    int pixelAvg;
    for (int i = 0; i < bmp->infoHdr.height; i++)
    {
        for (int j = 0; j < bmp->infoHdr.width; j++)
        {
            pixelAvg = (bmp->data[i][j].blu + bmp->data[i][j].grn + bmp->data[i][j].red) / 3;
            bmp->data[i][j].blu = pixelAvg;
            bmp->data[i][j].grn = pixelAvg;
            bmp->data[i][j].red = pixelAvg;
        }
    }
}
#endif