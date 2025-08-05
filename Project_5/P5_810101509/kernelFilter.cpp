#include "kernelFilter.hpp"

Pixel kernelFilter::applyMatrixtoOnePixel(const vector<vector<Pixel>> &copyData, int rowPixel, int colPixel, vector<vector<double>> kernelMatrix)
{
    double blue = 0.0;
    double green = 0.0;
    double red = 0.0;
    int newRow = rowPixel - 1;
    int newCol = colPixel - 1;
    for (int i = 0; i < 3; i++)
    {
        if (newRow + i < 0 || newRow + i >= copyData.size())
        {
            continue;
        }

        for (int j = 0; j < 3; j++)
        {
            if (newCol + j < 0 || newCol + j >= copyData[0].size())
            {
                continue;
            }

            blue += kernelMatrix[i][j] * copyData[newRow + i][newCol + j].blu;
            green += kernelMatrix[i][j] * copyData[newRow + i][newCol + j].grn;
            red += kernelMatrix[i][j] * copyData[newRow + i][newCol + j].red;
        }
    }
    blue = min(max(round(blue), 0.0), 255.0);
    green = min(max(round(green), 0.0), 255.0);
    red = min(max(round(red), 0.0), 255.0);

    return Pixel(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
}

void kernelFilter::applyFilterwithKernel(Bmp *bmp, vector<vector<double>> kernelMatrix)
{
    vector<vector<Pixel>> copyData = bmp->data;
    for (int i = 0; i < bmp->infoHdr.height; i++)
    {
        for (int j = 0; j < bmp->infoHdr.width; j++)
        {
            bmp->data[i][j] = applyMatrixtoOnePixel(copyData, i, j, kernelMatrix);
        }
    }
};
