#include "data.hpp"
#include "Emboss.hpp"
#include "Sharpen.hpp"
#include "gaussianBlur.hpp"
#include "Invert.hpp"
#include "grayScale.hpp"

void processCommands(int argc, char *argv[]);
vector<pair<string, string>> readFileNames();

int main(int argc, char *argv[])
{

    processCommands(argc, argv);
    return 0;
}

vector<pair<string, string>> readFileNames()
{
    vector<pair<string, string>> files;
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        string inputFileName, outputFileName;
        if (iss >> inputFileName >> outputFileName)
        {
            files.push_back(make_pair(inputFileName, outputFileName));
        }
    }

    return files;
}

void processCommands(int argc, char *argv[])
{
    vector<pair<string, string>> files;
    vector<filterApp *> filters;
    map<filterApp *, vector<int>> viewFilters;

    for (int i = 1; i < argc; ++i)
    {
        string token = argv[i];
        if (token == "-B")
        {
            filters.push_back(new gaussianBlur);
        }
        else if (token == "-S")
        {
            filters.push_back(new Sharpen);
        }
        else if (token == "-E")
        {
            filters.push_back(new Emboss);
        }
        else if (token == "-I")
        {
            filters.push_back(new Invert);
        }
        else if (token == "-G")
        {
            filters.push_back(new grayScale);
        }
        else if (token.find(':') != string::npos)
        {
            istringstream iss2(token);
            vector<int> values(4);
            int j = 0;
            string value;
            while (getline(iss2, value, ':') && j < 4)
            {
                values[j++] = stoi(value);
            }
            if (!filters.empty())
            {
                viewFilters[filters.back()] = values;
            }
        }
        else
        {
            string inputFileName = token;
            if (i + 1 < argc)
            {
                string outputFileName = argv[++i];
                files.push_back(make_pair(inputFileName, outputFileName));
            }
            else
            {
                cerr << "Each input file name should be followed by an output file name." << endl;
                return;
            }
        }
    }
    cout.flush();

    files = readFileNames();

    for (const pair<string, string> &file : files)
    {
        Bmp bmp;
        read(bmp, file.first);

        for (filterApp *filter : filters)
        {
            if (viewFilters.count(filter) > 0)
            {
                auto values = viewFilters[filter];
                filter->applyFilterwithView(&bmp, values[0], values[1], values[2], values[3]);
            }
            else
            {
                filter->applyFilter(&bmp);
            }
        }
        write(bmp, file.second);
    }
    for (filterApp *filter : filters)
    {
        delete filter;
    }
}