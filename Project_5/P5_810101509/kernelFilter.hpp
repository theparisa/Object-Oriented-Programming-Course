#ifndef KERNELFILTER_INCLUDE
#define KERNELFILTER_INCLUDE

#include "filterApp.hpp"

class kernelFilter : public filterApp
{
public:
    kernelFilter() : filterApp() {}
    void applyFilterwithKernel(Bmp *bmp, vector<vector<double>> kernelMatrix);
    Pixel applyMatrixtoOnePixel(const vector<vector<Pixel>> &copyData, int rowPixel, int colPixel, vector<vector<double>> kernelMatrix);

private:
    vector<vector<int>> baseMatrix = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};
};

#endif
