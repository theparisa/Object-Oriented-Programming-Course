#ifndef INVERT_INCLUDE
#define INVERT_INCLUDE
#include "changeColorFilter.hpp"

class Invert : public changeColorFilter
{
public:
    Invert() : changeColorFilter()
    {
    }
    void applyFilter(Bmp *bmp);
};
void Invert::applyFilter(Bmp *bmp)
{
    for (int i = 0; i < bmp->infoHdr.height; i++)
    {
        for (int j = 0; j < bmp->infoHdr.width; j++)
        {
            bmp->data[i][j].blu = 255 - bmp->data[i][j].blu;
            bmp->data[i][j].grn = 255 - bmp->data[i][j].grn;
            bmp->data[i][j].red = 255 - bmp->data[i][j].red;
        }
    }
};
#endif