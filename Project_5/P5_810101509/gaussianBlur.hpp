#ifndef GAUSSIANBLUR_INCLUDE
#define GAUSSIANBLUR_INCLUDE
#include "kernelFilter.hpp"

class gaussianBlur : public kernelFilter
{
public:
    gaussianBlur() : kernelFilter() {}
    void applyFilter(Bmp *bmp);

private:
    double scaleFactor = 1.0 / 16.0;
    vector<vector<double>> kernelMatrix = {
        {1 * scaleFactor, 2 * scaleFactor, 1 * scaleFactor},
        {2 * scaleFactor, 4 * scaleFactor, 2 * scaleFactor},
        {1 * scaleFactor, 2 * scaleFactor, 1 * scaleFactor}};
};
void gaussianBlur::applyFilter(Bmp *bmp)
{
    kernelFilter::applyFilterwithKernel(bmp, kernelMatrix);
}
#endif