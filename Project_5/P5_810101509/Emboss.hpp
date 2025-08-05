#ifndef EMBOSS_INCLUDE
#define EMBOSS_INCLUDE
#include "kernelFilter.hpp"
class Emboss : public kernelFilter
{
public:
    Emboss() : kernelFilter()
    {
    }
    void applyFilter(Bmp *bmp);

private:
    vector<vector<double>> kernelMatrix = {
        {-2, -1, 0},
        {-1, 1, 1},
        {0, 1, 2}};
};
void Emboss::applyFilter(Bmp *bmp)
{
    kernelFilter::applyFilterwithKernel(bmp, kernelMatrix);
}
#endif