#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

struct Patient
{
    string name;
    string problem;
    string visit_time;
    string speciality_needed;
    string doctor_needed;
    double money_needed;
    string visit_information;
};

struct VisitInfo
{
    int arrival_time;
    int free_time;
    int weekday;
    string weekday_str;
    int count = 0;
};

struct Doctor
{
    string name;
    string specialty;
    double cost_of_visit;
    double avg_waiting_time;
    double visit_duration;
    vector<string> days_of_presence;
    vector<int> free_times;
    vector<VisitInfo> visit_infos;
    long int firstVisitTime;
};

struct Disease
{
    string specialty;
    vector<string> diseases;
    vector<Doctor> doctors;
};

vector<Patient> read_csv_patients(const string &filename)
{
    vector<Patient> patients;
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string name, problem, visit_time;

            getline(ss, name, ',');
            getline(ss, problem, ',');
            getline(ss, visit_time, ',');

            patients.push_back({name, problem, visit_time});

        }

        file.close();
    }

    return patients;
}

vector<Doctor> read_csv_doctors(const string &filename)
{
    vector<Doctor> doctors;
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string name, specialty, cost_of_visit_str, avg_waiting_time_str, visit_duration_str, days_of_presence_str;

            getline(ss, name, ',');
            getline(ss, specialty, ',');
            getline(ss, cost_of_visit_str, ',');
            getline(ss, visit_duration_str, ',');
            getline(ss, avg_waiting_time_str, ',');
            getline(ss, days_of_presence_str);

            double cost_of_visit = stod(cost_of_visit_str);
            double avg_waiting_time = stod(avg_waiting_time_str);
            double visit_duration = stod(visit_duration_str);

            vector<string> days_of_presence;
            stringstream ss_days(days_of_presence_str);
            string day;
            while (getline(ss_days, day, '$'))
            {
                days_of_presence.push_back(day);
            }

            doctors.push_back({name, specialty, cost_of_visit, avg_waiting_time, visit_duration, days_of_presence});
        }

        file.close();
    }

    return doctors;
}

vector<Disease> read_csv_diseases(const string &filename)
{
    vector<Disease> diseases;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        istringstream ss(line);
        Disease disease;

        if (getline(ss, disease.specialty, ','))
        {
            string diseases_str;
            if (getline(ss, diseases_str, ','))
            {
                istringstream ss_diseases(diseases_str);
                string disease_name;
                while (getline(ss_diseases, disease_name, '$'))
                {
                    disease.diseases.push_back(disease_name);
                }
            }
        }

        diseases.push_back(disease);
    }

    return diseases;
}

vector<int> processStrings(vector<string> input)
{
    vector<string> weekdays = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};
    vector<int> result(7, 0);

    for (const auto &str : input)
    {
        stringstream ss(str);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '-'))
        {
            tokens.push_back(token);
        }

        int arrival = stoi(tokens[1]);
        int departure = stoi(tokens[2]);
        int diff = departure - arrival;

        auto it = find(weekdays.begin(), weekdays.end(), tokens[0]);
        if (it != weekdays.end())
        {
            int index = distance(weekdays.begin(), it);
            result[index] = diff;
        }
    }

    return result;
}

void processStructs(vector<Doctor> &doctors)
{
    for (auto &d : doctors)
    {
        d.free_times = processStrings(d.days_of_presence);
    }
}

void addDoctorsToDiseases(vector<Disease> &diseases, const vector<Doctor> &Doctors)
{
    for (Disease &disease : diseases)
    {
        for (const Doctor &doctor : Doctors)
        {
            if (disease.specialty == doctor.specialty)
            {
                disease.doctors.push_back(doctor);
            }
        }
    }
}

void addSpecialtyToPatients(vector<Patient> &patients, const vector<Disease> &diseases)
{
    for (int i = 0; i < patients.size(); i++)
    {
        for (int j = 0; j < diseases.size(); j++)
        {
            for (int k = 0; k < diseases[j].diseases.size(); k++)
            {
                if (diseases[j].diseases[k] == patients[i].problem)
                {
                    patients[i].speciality_needed = diseases[j].specialty;
                }
            }
        }
    }
}

vector<string> weekdays = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};

void sortPatients(std::vector<Patient> &patients)
{
    auto comparePatients = [](const Patient &a, const Patient &b)
    {
        string weekday_a = a.visit_time.substr(0, a.visit_time.find('-'));
        string weekday_b = b.visit_time.substr(0, b.visit_time.find('-'));
        int hour_a = stoi(a.visit_time.substr(a.visit_time.find('-') + 1));
        int hour_b = stoi(b.visit_time.substr(b.visit_time.find('-') + 1));

        auto it_a = find(weekdays.begin(), weekdays.end(), weekday_a);
        auto it_b = find(weekdays.begin(), weekdays.end(), weekday_b);
        if (it_a != weekdays.end() && it_b != weekdays.end())
        {
            if (it_a - weekdays.begin() < it_b - weekdays.begin())
                return true;
            if (it_a - weekdays.begin() > it_b - weekdays.begin())
                return false;
        }

        if (hour_a < hour_b)
            return true;
        if (hour_a > hour_b)
            return false;

        return a.name < b.name;
    };

    sort(patients.begin(), patients.end(), comparePatients);
}

int calculate_arrival_time(string input)
{
    vector<string> tokens;
    stringstream check1(input);
    string intermediate;

    while (getline(check1, intermediate, '-'))
    {
        tokens.push_back(intermediate);
    }

    string arrivalTime = tokens[1];
    string departureTime = tokens[2];

    int arrivalHour, arrivalMinute, departureHour, departureMinute;

    if (arrivalTime.find(":") != string::npos)
    {
        sscanf(arrivalTime.c_str(), "%d:%d", &arrivalHour, &arrivalMinute);
    }
    else
    {
        arrivalHour = stoi(arrivalTime);
        arrivalMinute = 0;
    }

    if (departureTime.find(":") != string::npos)
    {
        sscanf(departureTime.c_str(), "%d:%d", &departureHour, &departureMinute);
    }
    else
    {
        departureHour = stoi(departureTime);
        departureMinute = 0;
    }

    int arrivalTimeInMinutes = arrivalHour * 60 + arrivalMinute;
    return arrivalTimeInMinutes;
}

int timeDifference(string input)
{
    vector<string> tokens;
    stringstream check1(input);
    string intermediate;

    while (getline(check1, intermediate, '-'))
    {
        tokens.push_back(intermediate);
    }

    string arrivalTime = tokens[1];
    string departureTime = tokens[2];

    int arrivalHour, arrivalMinute, departureHour, departureMinute;

    if (arrivalTime.find(":") != string::npos)
    {
        sscanf(arrivalTime.c_str(), "%d:%d", &arrivalHour, &arrivalMinute);
    }
    else
    {
        arrivalHour = stoi(arrivalTime);
        arrivalMinute = 0;
    }

    if (departureTime.find(":") != string::npos)
    {
        sscanf(departureTime.c_str(), "%d:%d", &departureHour, &departureMinute);
    }
    else
    {
        departureHour = stoi(departureTime);
        departureMinute = 0;
    }

    int arrivalTimeInMinutes = arrivalHour * 60 + arrivalMinute;
    int departureTimeInMinutes = departureHour * 60 + departureMinute;

    return departureTimeInMinutes - arrivalTimeInMinutes;
}

int find_position(const vector<string> vec, string item)
{
    auto it = find(vec.begin(), vec.end(), item);
    if (it != vec.end())
    {
        return distance(vec.begin(), it) + 1;
    }
    else
    {
        return -1;
    }
}

void sortVisitInfoByWeekday(vector<VisitInfo> &visitInfos)
{
    vector<string> weekdays = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};

    sort(visitInfos.begin(), visitInfos.end(), [&weekdays](const VisitInfo &v1, const VisitInfo &v2)
         {
        auto it1 = find(weekdays.begin(), weekdays.end(), v1.weekday_str);
        auto it2 = find(weekdays.begin(), weekdays.end(), v2.weekday_str);
        return distance(weekdays.begin(), it1) < distance(weekdays.begin(), it2); });
}

void processDoctors(vector<Doctor> &doctors)
{
    vector<string> weekdays = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};

    for (auto &doctor : doctors)
    {
        vector<VisitInfo> temp_infos(7);
        for (const auto &str : doctor.days_of_presence)
        {
            stringstream ss(str);
            string token;
            vector<string> tokens;

            while (getline(ss, token, '-'))
            {
                tokens.push_back(token);
            }

            VisitInfo info;
            info.weekday_str = tokens[0];
            info.weekday = find_position(weekdays, tokens[0]);
            info.arrival_time = calculate_arrival_time(str);
            info.free_time = timeDifference(str);

            auto it = find(weekdays.begin(), weekdays.end(), tokens[0]);
            if (it != weekdays.end())
            {
                int index = distance(weekdays.begin(), it);
                temp_infos[index] = info;
                doctor.free_times[index] = info.free_time;
            }
        }
        doctor.visit_infos = temp_infos;

        sortVisitInfoByWeekday(doctor.visit_infos);
    }
}

void find_first_free_time(Doctor &doctor)
{
    for (int i = 0; i < 7; i++)
    {
        if (doctor.visit_infos[i].free_time != 0)
        {
            doctor.firstVisitTime = doctor.visit_infos[i].weekday * 100000 + doctor.visit_infos[i].arrival_time + doctor.visit_infos[i].count * doctor.visit_duration;
            break;
        }
    }
}

string calculateTime(int minutes)
{
    int hours = minutes / 60;
    int remaining_minutes = minutes % 60;
    ostringstream timeStream;
    timeStream << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << remaining_minutes;
    return timeStream.str();
}

void assignDoctors(vector<Patient> &patients, vector<Disease> &diseases)
{
    for (Patient &patient : patients)
    {
        Doctor *bestDoctor = nullptr;
        VisitInfo *bestVisitInfo = nullptr;

        for (Disease &disease : diseases)
        {
            if (disease.specialty == patient.speciality_needed)
            {
                for (Doctor &doctor : disease.doctors)
                {
                    find_first_free_time(doctor);

                    for (VisitInfo &visitInfo : doctor.visit_infos)
                    {
                        if (visitInfo.free_time != 0 &&
                            (bestDoctor == nullptr ||
                             doctor.firstVisitTime < bestDoctor->firstVisitTime ||
                             (doctor.firstVisitTime == bestDoctor->firstVisitTime && doctor.cost_of_visit < bestDoctor->cost_of_visit) ||
                             (doctor.firstVisitTime == bestDoctor->firstVisitTime && doctor.cost_of_visit == bestDoctor->cost_of_visit && doctor.avg_waiting_time < bestDoctor->avg_waiting_time) ||
                             (doctor.firstVisitTime == bestDoctor->firstVisitTime && doctor.cost_of_visit == bestDoctor->cost_of_visit && doctor.avg_waiting_time == bestDoctor->avg_waiting_time && doctor.name < bestDoctor->name)))
                        {
                            bestDoctor = &doctor;
                            bestVisitInfo = &visitInfo;
                        }
                    }
                }
            }
        }

        if (bestDoctor != nullptr && bestVisitInfo != nullptr)
        {
            patient.doctor_needed = bestDoctor->name;
            patient.money_needed = bestDoctor->cost_of_visit;
            bestVisitInfo->free_time -= bestDoctor->visit_duration;
            bestVisitInfo->count += 1;
            patient.visit_information = bestVisitInfo->weekday_str + " " + to_string(bestVisitInfo->count) + " " + calculateTime(bestDoctor->firstVisitTime % 100000);
        }
        else
        {
            patient.visit_information = "No free time";
        }
    }
}

bool comparePatients(const Patient &p1, const Patient &p2)
{
    return p1.name < p2.name;
}

void sortPatientsByName(vector<Patient> &patients)
{
    sort(patients.begin(), patients.end(), comparePatients);
}

void printOutput(vector<Patient> &patients)
{
    sortPatientsByName(patients);
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].visit_information == "No free time")
        {
            cout << "Name: " << patients[i].name << endl;
            cout << patients[i].visit_information << endl;
        }
        else
        {
            cout << "Name: " << patients[i].name << endl;
            cout << "Doctor: " << patients[i].doctor_needed << endl;
            cout << "Visit: " << patients[i].visit_information << endl;
            cout << "Charge: " << patients[i].money_needed << endl;
        }
        if (i == patients.size() - 1)
        {
            continue;
        }
        cout << "----------" << endl;
    }
}

void assign_visit_time(vector<Patient> &patients, vector<Disease> &diseases, vector<Doctor> &doctors)
{
    processStructs(doctors);
    processDoctors(doctors);
    addDoctorsToDiseases(diseases, doctors);
    addSpecialtyToPatients(patients, diseases);
    sortPatients(patients);
    assignDoctors(patients, diseases);
}

int main()
{

    vector<Patient> patients = read_csv_patients("patients.csv");
    vector<Doctor> doctors = read_csv_doctors("doctors.csv");
    vector<Disease> diseases = read_csv_diseases("diseases.csv");

    assign_visit_time(patients, diseases, doctors);
    printOutput(patients);

    return 0;
}