#ifndef FILTERAPP_INCLUDE
#define FILTERAPP_INCLUDE
#include "data.hpp"

class filterApp
{
private:
    Bmp tempBmp;
    string command;

public:
    filterApp(){};
    virtual void applyFilter(Bmp *bmp) = 0;
    void applyFilterwithView(Bmp *bmp, int x, int y, int w, int h);
    void setView(Bmp *bmp, int x, int y, int w, int h);
    void removeView(Bmp *bmp, int x, int y);
    void processCommands(int argc, char *argv[]);
    vector<pair<string, string>> readFileNames();
};

#endif