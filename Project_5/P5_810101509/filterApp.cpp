#include "filterApp.hpp"

void filterApp::setView(Bmp *bmp, int x, int y, int w, int h)
{
    create(tempBmp, w, h);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            tempBmp.data[i][j] = bmp->data[y + i][x + j];
        }
    }
}
void filterApp::removeView(Bmp *bmp, int x, int y)
{
    for (int i = 0; i < tempBmp.infoHdr.height; i++)
    {
        for (int j = 0; j < tempBmp.infoHdr.width; j++)
        {
            bmp->data[y + i][x + j] = tempBmp.data[i][j];
        }
    }
    delete tempBmp.fileData;
}
void filterApp::applyFilterwithView(Bmp *bmp, int x, int y, int w, int h)
{
    vector<vector<Pixel>> copyData = bmp->data;

    setView(bmp, x, y, w, h);
    applyFilter(&tempBmp);

    for (int i = 0; i < tempBmp.infoHdr.height; i++)
    {
        for (int j = 0; j < tempBmp.infoHdr.width; j++)
        {
            copyData[y + i][x + j] = tempBmp.data[i][j];
        }
    }
    bmp->data = copyData;
    // delete tempBmp.fileData;
}
