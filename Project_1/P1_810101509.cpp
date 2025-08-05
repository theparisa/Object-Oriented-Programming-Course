#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<int> getTime(string time)
{
    vector<int> result;
    string delimiter = ":";

    size_t pos = 0;
    string token;
    while ((pos = time.find(delimiter)) != string::npos)
    {
        token = time.substr(0, pos);
        result.push_back(stoi(token));
        time.erase(0, pos + delimiter.length());
    }
    result.push_back(stoi(time));

    return result;
}

int arrival_time_of_train(int waiting_minutes, vector<int> current_time)
{
    int current_time_in_minutes = (current_time[0] - 6) * 60 + current_time[1];
    if ((current_time_in_minutes % waiting_minutes) == 0)
    {
        return current_time_in_minutes;
    }
    int result_in_minutes = current_time_in_minutes + (waiting_minutes - (current_time_in_minutes % waiting_minutes));
    int result_hour = result_in_minutes / 60;
    int result_minutes = result_in_minutes % 60;

    return result_in_minutes;
}

double calculate_cost_of_trip(int num_stations)
{
    return ceil(1000 * log10(10 * num_stations));
}

int main()
{
    int num_lines;
    int hour, minute;
    string name_of_line;
    int num_all_stations;
    int wait_period;
    int num_towards_start_stations;
    int num_towards_end_stations;
    int ridetime_between_stations;
    string name_of_station;

    vector<string> vec_names_of_lines;
    vector<int> vec_wait_periods;
    vector<int> vec_num_towards_start_stations;
    vector<int> vec_num_towards_end_stations;
    vector<vector<int>> vec_ridetime_of_diffrent_lines;
    vector<vector<string>> vec_names_of_stations_of_diffrent_lines;

    string time_str;

    cin >> num_lines >> time_str;

    for (int i = 0; i < num_lines; i++)
    {
        vector<int> vec_ridetime_between_stations;
        vector<string> vec_names_of_stations;

        cin >> name_of_line >> wait_period;
        vec_names_of_lines.push_back(name_of_line);
        vec_wait_periods.push_back(wait_period);

        cin >> num_towards_start_stations;
        vec_num_towards_start_stations.push_back(num_towards_start_stations);

        for (int s = 0; s < num_towards_start_stations; s++)
        {
            cin >> ridetime_between_stations >> name_of_station;
            vec_ridetime_between_stations.push_back(ridetime_between_stations);
            vec_names_of_stations.push_back(name_of_station);
        }

        cin >> num_towards_end_stations;
        vec_num_towards_end_stations.push_back(num_towards_end_stations);

        for (int s = 0; s < num_towards_end_stations; s++)
        {
            cin >> ridetime_between_stations >> name_of_station;
            vec_ridetime_between_stations.push_back(ridetime_between_stations);
            vec_names_of_stations.push_back(name_of_station);
        }
        vec_names_of_stations_of_diffrent_lines.push_back(vec_names_of_stations);
        vec_ridetime_of_diffrent_lines.push_back(vec_ridetime_between_stations);
    }

    string name_of_the_destination;
    cin >> name_of_the_destination;

    int num_passed_stations;
    int ridetime = 0;
    string start_or_end_str;
    string name_of_the_destination_line;
    int destination_time_in_minutes;

    for (int i = 0; i < num_lines; i++)
    {
        for (int j = 0; j < vec_num_towards_end_stations[i] + vec_num_towards_start_stations[i]; j++)
        {
            if (vec_names_of_stations_of_diffrent_lines[i][j] == name_of_the_destination)
            {
                int num_start_stations_of_this_line = vec_num_towards_start_stations[i];
                name_of_the_destination_line = vec_names_of_lines[i];
                if (j < num_start_stations_of_this_line)
                {
                    num_passed_stations = j + 1;
                    for (int t = 0; t < (num_passed_stations); t++)
                    {
                        ridetime += vec_ridetime_of_diffrent_lines[i][t];
                    }
                    start_or_end_str = "start";
                }
                else
                {
                    num_passed_stations = (j - num_start_stations_of_this_line) + 1;
                    for (int t = 0; t < num_passed_stations; t++)
                    {
                        ridetime += vec_ridetime_of_diffrent_lines[i][t + num_start_stations_of_this_line];
                    }
                    start_or_end_str = "end";
                }
                destination_time_in_minutes = ridetime + arrival_time_of_train(vec_wait_periods[i], getTime(time_str));
            }
        }
    }

    int hour_arrival_time = 6 + (destination_time_in_minutes / 60);
    int minutes_arrival_time = destination_time_in_minutes % 60;

    double cost_of_trip = calculate_cost_of_trip(num_passed_stations);

    cout << "Towards " << start_or_end_str << " of " << name_of_the_destination_line << " in " << num_passed_stations << " station(s)" << endl;
    cout << hour_arrival_time << ":" << minutes_arrival_time << endl;
    cout << cost_of_trip << endl;

    return 0;
}