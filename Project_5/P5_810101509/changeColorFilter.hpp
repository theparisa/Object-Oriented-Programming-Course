#ifndef CHANGECOLORFILTER_INCLUDE
#define CHANGECOLORFILTER_INCLUDE

#include "filterApp.hpp"
class changeColorFilter : public filterApp
{
public:
    changeColorFilter() : filterApp()
    {
    }
    void applyFilter(Bmp *) {}
};
#endif