#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

class short_term_deposit
{
private:
    float intitial_investment;
    float profit = 0;

public:
    short_term_deposit(float _initial_investment)
    {
        intitial_investment = _initial_investment;
    }
    float get_initial_investment() { return intitial_investment; }
    float *get_profit_ptr() { return &profit; }
    float get_profit() { return profit; }
    int Id;
};

class long_term_deposit
{
private:
    int Id;
    float intitial_investment;
    int short_term_deposit_id;
    int years;

public:
    long_term_deposit(float _initial_investment, int _short_term_deposit_id, int _years)
    {
        intitial_investment = _initial_investment;
        short_term_deposit_id = _short_term_deposit_id;
        years = _years;
    }
    float get_initial_investment() { return intitial_investment; }
    int get_years() { return years; }
    int get_short_term_deposit_id() { return short_term_deposit_id; }
};

class gharzolhasane_deposit
{
private:
    int Id;
    float intitial_investment;

public:
    gharzolhasane_deposit(float _initial_investment)
    {
        intitial_investment = _initial_investment;
    }
    float get_initial_investment() { return intitial_investment; }
};

class Bank_account
{
private:
    int Id;
    int Short_term_profit_margin;
    float Short_term_minimum_investment;

public:
    Bank_account(int _Id, int _Short_term_profit_margin, float _Short_term_minimum_investment)
    {
        Id = _Id;
        Short_term_profit_margin = _Short_term_profit_margin;
        Short_term_minimum_investment = _Short_term_minimum_investment;
    }
    int get_Id() { return Id; }
    int get_Short_term_profit_margin() { return Short_term_profit_margin; }
    float get_Short_term_minimum_investment() { return Short_term_minimum_investment; }

    short_term_deposit *find_short_deposit_by_id(int short_deposit_id);

    vector<gharzolhasane_deposit> gharz_deposits;
    vector<short_term_deposit> short_deposits;
    vector<long_term_deposit> long_deposits;
};

short_term_deposit *Bank_account::find_short_deposit_by_id(int short_deposit_id)
{
    for (short_term_deposit &short_deposit : short_deposits)
    {
        if (short_deposit.Id == short_deposit_id)
        {
            return &short_deposit;
        }
    }
    return NULL;
}

class User
{
private:
    int Id;
    float Wallet;
    vector<Bank_account> accounts;

public:
    User(int _Id, float _Wallet)
    {
        Id = _Id;
        Wallet = _Wallet;
    }
    int get_Id() { return Id; }
    Bank_account *find_bank_by_id(int the_Id);
    float *get_Wallet_ptr() { return &Wallet; }
    float get_wallet() { return Wallet; }
    vector<Bank_account> *get_bank_accounts() { return &accounts; }
};

Bank_account *User::find_bank_by_id(int the_Id)
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (the_Id == accounts[i].get_Id())
        {
            return &accounts[i];
        }
    }
}

class Manager
{
private:
    vector<User> users;
    vector<Bank_account> banks;
    vector<int> num_short_deposit_banks;

public:
    Manager(vector<Bank_account> _banks, vector<User> _users)
    {
        banks = _banks;
        users = _users;
        create_num_short_deposits_vector();
    }
    void create_num_short_deposits_vector();
    User *find_user_by_id(int the_Id);
    Bank_account find_bank_account_by_id(int the_Id);
    void create_short_term_deposit(int user_id, int bank_id, float initial_investment);
    void create_long_term_deposit(int user_id, int bank_id, int short_term_deposite_id, int years, float initial_investment);
    void create_gharzolhasane_deposit(int user_id, int bank_id, float initial_investment);
    int inc_num_short_deposits(int the_id);
    void past_time(int month);
    void print();
    void inventory_report(int user_id, int bank_id, int short_term_deposit_id);
    void calc_money_in_bank(int user_id, int bank_id);
    void calc_all_money(int user_id);
    void get_command(string command);
};

bool not_enogh_money_err(User user, Bank_account bank_account, float initial_investment)
{

    if (initial_investment > user.get_wallet() || initial_investment < bank_account.get_Short_term_minimum_investment())
    {
        cout << "Not enough money" << endl;
        return true;
    }
    return false;
}

User *Manager::find_user_by_id(int the_Id)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (the_Id == users[i].get_Id())
        {
            return &users[i];
        }
    }
}

Bank_account Manager::find_bank_account_by_id(int the_Id)
{
    for (int i = 0; i < banks.size(); i++)
    {
        if (banks[i].get_Id() == the_Id)
        {
            return banks[i];
        }
    }
}

int Manager::inc_num_short_deposits(int the_Id)
{
    for (int i = 0; i < banks.size(); i++)
    {
        if (banks[i].get_Id() == the_Id)
        {
            num_short_deposit_banks[i]++;
            return num_short_deposit_banks[i];
        }
    }
}

void Manager::create_num_short_deposits_vector()
{
    for (int i = 0; i < banks.size(); i++)
    {
        num_short_deposit_banks.push_back(0);
    }
}

void Manager::create_short_term_deposit(int user_id, int bank_id, float initial_investment)
{

    User *the_user = find_user_by_id(user_id);
    Bank_account *the_bank_account = the_user->find_bank_by_id(bank_id);
    short_term_deposit short_deposit(initial_investment);

    if (the_bank_account == NULL)
    {
        Bank_account the_account = find_bank_account_by_id(bank_id);

        if (not_enogh_money_err(*the_user, the_account, initial_investment))
        {
            return;
        }
        int short_dep_id = inc_num_short_deposits(bank_id);
        short_deposit.Id = short_dep_id;
        the_account.short_deposits.push_back(short_deposit);
        the_user->get_bank_accounts()->push_back(the_account);
    }
    else
    {
        if (not_enogh_money_err(*the_user, *the_bank_account, initial_investment))
        {
            return;
        }
        int short_dep_id = inc_num_short_deposits(bank_id);
        short_deposit.Id = short_dep_id;
        the_bank_account->short_deposits.push_back(short_deposit);
    }

    (*the_user->get_Wallet_ptr()) -= initial_investment;

    cout << short_deposit.Id << endl;
}

void Manager::create_long_term_deposit(int user_id, int bank_id, int short_term_deposite_id, int years, float initial_investment)
{
    User *the_user = find_user_by_id(user_id);

    Bank_account *the_bank_account = the_user->find_bank_by_id(bank_id);

    if (the_bank_account == NULL)
    {
        cout << "Invalid short-term deposit" << endl;
        return;
    }
    else
    {
        if (the_bank_account->find_short_deposit_by_id(short_term_deposite_id) == NULL)
        {
            cout << "Invalid short-term deposit" << endl;
            return;
        }
        if (not_enogh_money_err(*the_user, *the_bank_account, initial_investment))
        {
            return;
        }
        the_bank_account->long_deposits.push_back(long_term_deposit(initial_investment, short_term_deposite_id, years));
    }
    (*the_user->get_Wallet_ptr()) -= initial_investment;
}

void Manager::create_gharzolhasane_deposit(int user_id, int bank_id, float initial_investment)
{
    User *the_user = find_user_by_id(user_id);

    Bank_account *the_bank_account = the_user->find_bank_by_id(bank_id);

    if (the_bank_account == NULL)
    {

        Bank_account the_account = find_bank_account_by_id(bank_id);

        if (not_enogh_money_err(*the_user, the_account, initial_investment))
        {
            return;
        }

        the_account.gharz_deposits.push_back(gharzolhasane_deposit(initial_investment));
        the_user->get_bank_accounts()->push_back(the_account);
    }
    else
    {
        if (not_enogh_money_err(*the_user, *the_bank_account, initial_investment))
        {
            return;
        }

        the_bank_account->gharz_deposits.push_back(gharzolhasane_deposit(initial_investment));
    }
    (*the_user->get_Wallet_ptr()) -= initial_investment;
}

void Manager::past_time(int month)
{
    for (int i = 0; i < users.size(); i++)
    {
        for (int j = 0; j < users[i].get_bank_accounts()->size(); j++)
        {
        }
    }

    for (User &user : users)
    {
        for (Bank_account &bank_account : (*user.get_bank_accounts()))
        {
            for (short_term_deposit &short_deposit : bank_account.short_deposits)
            {
                (*short_deposit.get_profit_ptr()) += month * bank_account.get_Short_term_profit_margin() * short_deposit.get_initial_investment() / 100;
            }
            for (long_term_deposit &long_deposit : bank_account.long_deposits)
            {
                short_term_deposit *the_short_deposit = bank_account.find_short_deposit_by_id(long_deposit.get_short_term_deposit_id());
                (*the_short_deposit->get_profit_ptr()) += month * long_deposit.get_years() * bank_account.get_Short_term_profit_margin() * long_deposit.get_initial_investment() / 100;

            }
        }
    }

}

void Manager::print()
{
    for (User user : users)
    {
        for (Bank_account bank_account : (*user.get_bank_accounts()))
        {
            for (short_term_deposit short_deposit : bank_account.short_deposits)
            {
                cout << short_deposit.get_profit() << endl;
            }
        }
    }
}

void Manager::inventory_report(int user_id, int bank_id, int short_term_deposit_id)
{
    bool find_short_deposit_id = false;
    for (User user : users)
    {
        if (user.get_Id() == user_id)
        {
            for (Bank_account bank_account : (*user.get_bank_accounts()))
            {
                if (bank_account.get_Id() == bank_id)
                {
                    for (short_term_deposit short_deposit : bank_account.short_deposits)
                    {
                        if (short_deposit.Id == short_term_deposit_id)
                        {
                            find_short_deposit_id = true;
                            float result = short_deposit.get_initial_investment() + short_deposit.get_profit();
                            result = static_cast<float>(static_cast<int>(result * pow(10, 2))) / pow(10, 2);
                            cout << result << endl;
                        }
                    }
                }
            }
        }
    }
    if (!find_short_deposit_id)
    {
        cout << "Invalid short-term deposit" << endl;
    }
}

void Manager::calc_money_in_bank(int user_id, int bank_id)
{
    float sum = 0;
    for (User user : users)
    {
        if (user.get_Id() == user_id)
        {
            for (Bank_account bank_account : (*user.get_bank_accounts()))
            {
                if (bank_account.get_Id() == bank_id)
                {
                    for (short_term_deposit short_deposit : bank_account.short_deposits)
                    {
                        sum += short_deposit.get_initial_investment() + short_deposit.get_profit();
                    }
                    for (long_term_deposit long_deposit : bank_account.long_deposits)
                    {
                        sum += long_deposit.get_initial_investment();
                    }
                    for (gharzolhasane_deposit gharz_deposit : bank_account.gharz_deposits)
                    {
                        sum += gharz_deposit.get_initial_investment();
                    }
                }
            }
        }
    }
    sum = static_cast<float>(static_cast<int>(sum * pow(10, 2))) / pow(10, 2);
    cout << sum << endl;
}

void Manager::calc_all_money(int user_id)
{
    float sum = 0;
    for (User user : users)
    {
        if (user.get_Id() == user_id)
        {
            for (Bank_account bank_account : (*user.get_bank_accounts()))
            {
                for (short_term_deposit short_deposit : bank_account.short_deposits)
                {
                    sum += short_deposit.get_initial_investment() + short_deposit.get_profit();
                }
                for (long_term_deposit long_deposit : bank_account.long_deposits)
                {
                    sum += long_deposit.get_initial_investment();
                }
                for (gharzolhasane_deposit gharz_deposit : bank_account.gharz_deposits)
                {
                    sum += gharz_deposit.get_initial_investment();
                }
            }
        }
    }
    sum = static_cast<float>(static_cast<int>(sum * pow(10, 2))) / pow(10, 2);
    cout << sum << endl;
}

void readCSV_users(string user_file, vector<User> &users)
{
    ifstream file(user_file);

    if (file.is_open())
    {
        string line;

        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string value;

            getline(ss, value, ',');
            int id = stoi(value);

            getline(ss, value, ',');
            float wallet = stof(value);

            users.push_back(User(id, wallet));
        }
    }
}

void readCSV_banks(string bank_file, vector<Bank_account> &banks)
{
    ifstream file(bank_file);

    if (file.is_open())
    {
        string line;

        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string value;

            getline(ss, value, ',');
            int id = stoi(value);

            getline(ss, value, ',');
            int Short_term_profit_margin = stoi(value);

            getline(ss, value, ',');
            float Short_term_minimum_investment = stof(value);

            banks.push_back(Bank_account(id, Short_term_profit_margin, Short_term_minimum_investment));
        }
    }
}

void Manager::get_command(string command)
{
    int user_id;
    int bank_id;
    int short_term_deposit_id;
    int years;
    float initial_investment;
    int month;
    if (command == "create_short_term_deposit")
    {
        cin >> user_id >> bank_id >> initial_investment;
        create_short_term_deposit(user_id, bank_id, initial_investment);
    }
    else if (command == "create_long_term_deposit")
    {
        cin >> user_id >> bank_id >> short_term_deposit_id >> years >> initial_investment;
        create_long_term_deposit(user_id, bank_id, short_term_deposit_id, years, initial_investment);
        cout << "OK" << endl;
    }
    else if (command == "create_gharzolhasane_deposit")
    {
        cin >> user_id >> bank_id >> initial_investment;
        create_short_term_deposit(user_id, bank_id, initial_investment);
        cout << "OK" << endl;
    }
    else if (command == "past_time")
    {
        cin >> month;
        past_time(month);
        cout << "OK" << endl;
    }
    else if (command == "inventory_report")
    {
        cin >> user_id >> bank_id >> short_term_deposit_id;
        inventory_report(user_id, bank_id, short_term_deposit_id);
    }
    else if (command == "calc_money_in_bank")
    {
        cin >> user_id >> bank_id;
        calc_money_in_bank(user_id, bank_id);
    }
    else if (command == "calc_all_money")
    {
        cin >> user_id;
        calc_all_money(user_id);
    }
}

int main(int argc, char *argv[])
{
    string banksFile, usersFile;
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if (arg == "-b")
        {
            if (i + 1 < argc)
            {
                banksFile = argv[++i];
            }
            else
            {
                cerr << "-b option requires one argument." << std::endl;
                return 1;
            }
        }
        else if (arg == "-u")
        {
            if (i + 1 < argc)
            {
                usersFile = argv[++i];
            }
            else
            {
                cerr << "-u option requires one argument." << std::endl;
                return 1;
            }
        }
    }
    vector<Bank_account> banks;
    vector<User> users;
    readCSV_banks(banksFile, banks);
    readCSV_users(usersFile, users);
    Manager manager(banks, users);

    string command;
    while (cin >> command)
    {
        manager.get_command(command);
    }
    
    return 0;
}