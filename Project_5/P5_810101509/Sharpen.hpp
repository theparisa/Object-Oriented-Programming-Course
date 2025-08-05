#ifndef SHARPEN_INCLUDE
#define SHARPEN_INCLUDE
#include "kernelFilter.hpp"
class Sharpen : public kernelFilter
{
public:
    Sharpen() : kernelFilter()
    {
    }
    void applyFilter(Bmp *bmp);

private:
    vector<vector<double>> kernelMatrix = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}};
};
void Sharpen::applyFilter(Bmp *bmp)
{
    kernelFilter::applyFilterwithKernel(bmp, kernelMatrix);
}
#endif