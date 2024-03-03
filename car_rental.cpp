#include <bits/stdc++.h>

using namespace std;

int fine_per_day = 100;

int damage_per_day = 1;

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year)
{
    if (month == 2)
    {
        return isLeapYear(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}

void addDaysToDate(int &day, int &month, int &year, int daysToAdd)
{
    while (daysToAdd > 0)
    {
        int daysInCurrentMonth = daysInMonth(month, year);
        int daysLeftInMonth = daysInCurrentMonth - day + 1;

        if (daysToAdd >= daysLeftInMonth)
        {
            daysToAdd -= daysLeftInMonth;
            day = 1;
            if (month == 12)
            {
                month = 1;
                year++;
            }
            else
            {
                month++;
            }
        }
        else
        {
            day += daysToAdd;
            daysToAdd = 0;
        }
    }
}

int daysBetweenDates(string d1, string m1, string y1, string d2, string m2, string y2)
{
    int day1 = stoi(d1);
    int month1 = stoi(m1);
    int year1 = stoi(y1);
    int day2 = stoi(d2);
    int month2 = stoi(m2);
    int year2 = stoi(y2);

    if ((year1 > year2) || ((year1 == year2) && (month1 > month2)) || ((year1 == year2) && (month1 == month2) && day1 >= day2))
    {
        int totalDays1 = year1 * 365 + (year1 / 4 - year1 / 100 + year1 / 400);
        int totalDays2 = year2 * 365 + (year2 / 4 - year2 / 100 + year2 / 400);

        for (int month = 1; month < month1; ++month)
        {
            totalDays1 += daysInMonth(month, year1);
        }
        totalDays1 += day1;

        for (int month = 1; month < month2; ++month)
        {
            totalDays2 += daysInMonth(month, year2);
        }
        totalDays2 += day2;

        return (totalDays1 - totalDays2);
    }
    return 0;
}

class car;
class user;
class customer;
class employee;
class manager;

class car
{
public:
    string model;
    bool available; // true if available to rent
    int req_record;
    int price;
    int car_health;
    int owner; // 1 for customer, 2 for employee
    string id;
    string name;
    string return_date_dd;
    string return_date_mm;
    string return_date_yyyy;
    car(string &m, int p, int rr)
    {
        model = m;
        price = p;
        req_record = rr;
        available = 1;
        owner = 0;
        car_health = 500;
        id = "0";
        name = "0";
        return_date_dd = "00";
        return_date_mm = "00";
        return_date_yyyy = "0000";
    }
};

class user
{
public:
    string name;
    string id;
    string password;
};

class customer : public user
{
private:
    int cust_record;
    // int fine_due;
public:
    customer(string &i, string &n, string &p, int cr = 50)
    {
        id = i;
        name = n;
        password = p;
        this->cust_record = cr;
        // fine_due = 0;
    }
    int get_cust_record()
    {
        return cust_record;
    }
    void show_available_cars();
    void show_rented_cars();
    void rent_car();
    void check_fine();
    void clear_dues();
};

class employee : public user
{
private:
    int emp_record;
    // int fine_due;

public:
    employee(string &i, string &n, string &p, int er = 50)
    {
        id = i;
        name = n;
        password = p;
        this->emp_record = er;
        // fine_due = 0;
    }
    int get_emp_record()
    {
        return emp_record;
    }
    void show_available_cars();
    void show_rented_cars();
    void rent_car();
    void check_fine();
    void clear_dues();
};

class manager : public user
{
private:
public:
    manager(string &i, string &n, string &p)
    {
        id = i;
        name = n;
        password = p;
    }
    void check_all_cars();
    void add_customer(customer *cust);
    void update_customer(customer *cust);
    void delete_customer(string id);

    void add_employee(employee *emp);
    void update_employee(employee *emp);
    void delete_employee(string id);

    void add_car(car *new_car);
    void update_car(string m);
    void delete_car(string m);
};

// Customer Class Functions
void customer::show_available_cars()
{
    ifstream car_database("cars.csv");
    if (car_database.is_open() == false)
        cerr << "Error : Unable to fetch data from database" << endl;
    else
    {
        string header = "";
        getline(car_database, header);

        string line = "";
        while (getline(car_database, line))
        {
            stringstream input_string(line);
            string model, available, req_record, price, car_health;

            getline(input_string, model, ',');
            getline(input_string, available, ',');
            getline(input_string, req_record, ',');
            getline(input_string, price, ',');
            getline(input_string, car_health, ',');
            int temp1 = stoi(available);
            int temp2 = stoi(req_record);
            int temp3 = stoi(price);
            int temp4 = stoi(car_health);
            // cout << available << " " << req_record << " " << this->get_cust_record() << endl;
            if (temp1 == 1 && temp2 <= this->get_cust_record() && temp4>0)
                cout << "Model : " << model << " --> Price : " << price << " --> Car Health : " << car_health << endl;
        }
        car_database.close();
    }
}

void customer::show_rented_cars()
{
    ifstream car_database("cars.csv");
    if (!car_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header;
    getline(car_database, header); // Skip the header

    string line;
    while (getline(car_database, line))
    {
        stringstream input_string(line);
        string model, available, req_record, price, car_health, owner, id, name, return_date_dd, return_date_mm, return_date_yyyy;

        getline(input_string, model, ',');
        getline(input_string, available, ',');
        getline(input_string, req_record, ',');
        getline(input_string, price, ',');
        getline(input_string, car_health, ',');
        getline(input_string, owner, ',');
        getline(input_string, id, ',');
        getline(input_string, name, ',');
        getline(input_string, return_date_dd, ',');
        getline(input_string, return_date_mm, ',');
        getline(input_string, return_date_yyyy, ',');

        // cout << owner << id << " " << this->id << endl;
        if (owner == "1" && id == this->id && name == this->name)
        {
            cout << "Model: " << model << " --> Return Date: " << return_date_dd << "-" << return_date_mm << "-" << return_date_yyyy << endl;
        }
    }
    car_database.close();
}

void customer::rent_car()
{
    cout << "Available cars are : " << endl;
    this->show_available_cars();
    cout << "Enter model you want to rent : ";
    string req_model;
    cin >> req_model;
    int no_of_days;
    cout << "Enter number of days you want to rent : ";
    cin >> no_of_days;

    time_t now = time(0);
    tm *localTime = localtime(&now);
    string yearStr = to_string(1900 + localTime->tm_year);
    string monthStr = to_string(1 + localTime->tm_mon);
    string dayStr = to_string(localTime->tm_mday);

    int day, month, year;
    stringstream(dayStr) >> day;
    stringstream(monthStr) >> month;
    stringstream(yearStr) >> year;

    addDaysToDate(day, month, year, no_of_days);

    string d, m, y;
    d = to_string(day);
    m = to_string(month);
    y = to_string(year);

    ifstream car_database("cars.csv");
    if (car_database.is_open() == false)
        cerr << "Error : Unable to fetch data from database" << endl;

    vector<string> header;
    string header_line = "";
    getline(car_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }
    bool rent = false;
    vector<vector<string>> data;
    string line = "";
    while (getline(car_database, line))
    {
        stringstream input_string(line);
        string mm, a, rr, pr, ch, owner, id, n, rd, rm, ry;
        vector<string> row;
        getline(input_string, mm, ',');
        getline(input_string, a, ',');
        getline(input_string, rr, ',');
        getline(input_string, pr, ',');
        getline(input_string, ch, ',');
        getline(input_string, owner, ',');
        getline(input_string, id, ',');
        getline(input_string, n, ',');
        getline(input_string, rd, ',');
        getline(input_string, rm, ',');
        getline(input_string, ry, ',');

        int curr_health = stoi(ch);
        if (req_model == mm && a == "1" && stoi(rr) <= this->get_cust_record() && stoi(ch)>0)
        {
            int new_health = max(0, curr_health - no_of_days*damage_per_day);
            rent = true;
            row.push_back(mm);
            row.push_back("0");
            row.push_back(rr);
            row.push_back(pr);
            row.push_back(to_string(new_health));
            row.push_back("1");
            row.push_back(this->id);
            row.push_back(this->name);
            row.push_back(d);
            row.push_back(m);
            row.push_back(y);
        }
        else
        {
            row.push_back(mm);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(pr);
            row.push_back(ch);
            row.push_back(owner);
            row.push_back(id);
            row.push_back(n);
            row.push_back(rd);
            row.push_back(rm);
            row.push_back(ry);
        }
        if (!row[0].empty())
            data.push_back(row);
    }
    car_database.close();

    if (rent == false)
        cout << "No such model is available to rent" << endl;
    else
        cout << "Model : " << req_model << " rented successfully" << endl;

    ofstream outfile("cars.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }
}

void customer::check_fine()
{
    time_t now = time(0);
    tm *localTime = localtime(&now);
    string ty = to_string(1900 + localTime->tm_year);
    string tm = to_string(1 + localTime->tm_mon);
    string td = to_string(localTime->tm_mday);

    int your_fine = 0;

    ifstream car_database("cars.csv");
    if (car_database.is_open() == false)
        cerr << "Error : Unable to fetch data from database" << endl;
    else
    {
        string header = "";
        getline(car_database, header);

        string line = "";
        while (getline(car_database, line))
        {
            stringstream input_string(line);
            string owner, id, rd, rm, ry;
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, id, ',');
            getline(input_string, rd, ',');
            getline(input_string, rd, ',');
            getline(input_string, rm, ',');
            getline(input_string, ry, ',');

            if (owner == "1" && id == this->id)
                your_fine += daysBetweenDates(td, tm, ty, rd, rm, ry) * fine_per_day;
        }
        car_database.close();
    }
    cout << "Your fine : " << your_fine << endl;
}

void customer::clear_dues()
{
    int new_cr = this->get_cust_record();

    time_t now = time(0);
    tm *localTime = localtime(&now);
    string ty = to_string(1900 + localTime->tm_year);
    string tm = to_string(1 + localTime->tm_mon);
    string td = to_string(localTime->tm_mday);

    int your_fine = 0;

    ifstream car_database("cars.csv");
    if (car_database.is_open() == false)
        cerr << "Error : Unable to fetch data from database" << endl;

    vector<string> header;
    string header_line = "";
    getline(car_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }

    vector<vector<string>> data;
    string line = "";
    while (getline(car_database, line))
    {
        stringstream input_string(line);
        string m, a, rr, pr, ch, owner, id, n, rd, rm, ry;
        vector<string> row;
        getline(input_string, m, ',');
        getline(input_string, a, ',');
        getline(input_string, rr, ',');
        getline(input_string, pr, ',');
        getline(input_string, ch, ',');
        getline(input_string, owner, ',');
        getline(input_string, id, ',');
        getline(input_string, n, ',');
        getline(input_string, rd, ',');
        getline(input_string, rm, ',');
        getline(input_string, ry, ',');


        int curr_health = stoi(ch);
        if (owner == "1" && id == this->id)
        {
            your_fine += daysBetweenDates(td, tm, ty, rd, rm, ry) * fine_per_day;
            int new_health = max(0, curr_health - damage_per_day*daysBetweenDates(td,tm,ty,rd,rm,ry));
            new_cr = max(0, new_cr - daysBetweenDates(td, tm, ty, rd, rm, ry));
            row.push_back(m);
            row.push_back("1");
            row.push_back(rr);
            row.push_back(pr);
            row.push_back(to_string(new_health));
            row.push_back("0");
            row.push_back("0");
            row.push_back("0");
            row.push_back("00");
            row.push_back("00");
            row.push_back("0000");
        }
        else
        {
            row.push_back(m);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(pr);
            row.push_back(ch);
            row.push_back(owner);
            row.push_back(id);
            row.push_back(n);
            row.push_back(rd);
            row.push_back(rm);
            row.push_back(ry);
        }
        if (!row[0].empty())
            data.push_back(row);
    }
    car_database.close();

    cout << "Pay fine : " << your_fine << endl;

    ofstream outfile("cars.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }

    // we need to update customer record
    vector<string> header_2;
    ifstream customer_database("customers.csv");
    if (!customer_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    customer* cust = new customer(this->id, this->name, this->password, new_cr);
    string header_line_2;
    getline(customer_database, header_line_2);
    stringstream header_stream_2(header_line_2);
    string token_2;
    while (getline(header_stream_2, token_2, ','))
    {
        header_2.push_back(token_2);
    }

    vector<vector<string>> data_2;

    string line_2;
    while (getline(customer_database, line_2))
    {
        stringstream ss(line_2);
        string i, n, p, cr;
        vector<string> row;
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, p, ',');
        getline(ss, cr, ',');
        if (i == cust->id)
        {
            row.push_back(i);
            row.push_back(cust->name);
            row.push_back(cust->password);
            row.push_back(to_string(cust->get_cust_record()));
        }
        else
        {
            row.push_back(i);
            row.push_back(n);
            row.push_back(p);
            row.push_back(cr);
        }
        if (!row[0].empty())
            data_2.push_back(row);
    }
    customer_database.close();

    ofstream outfile_2("customers.csv", ios::trunc);
    if (!outfile_2.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header_2.size(); i++)
        {
            outfile_2 << header_2[i];
            if (i != header_2.size() - 1)
                outfile_2 << ",";
        }
        outfile_2 << endl;

        for (int i = 0; i < data_2.size(); i++)
        {
            for (int j = 0; j < data_2[i].size(); j++)
            {
                outfile_2 << data_2[i][j];
                if (j != data_2[i].size() - 1)
                    outfile_2 << ",";
            }
            outfile_2 << endl;
        }
    }
}

// Employee Class Functions
void employee::show_available_cars()
{
    ifstream car_database("cars.csv");
    if (car_database.is_open() == false)
        cerr << "Error : Unable to fetch data from database" << endl;
    else
    {
        string header = "";
        getline(car_database, header);

        string line = "";
        while (getline(car_database, line))
        {
            stringstream input_string(line);
            string model, available, req_record, price, car_health;

            getline(input_string, model, ',');
            getline(input_string, available, ',');
            getline(input_string, req_record, ',');
            getline(input_string, price, ',');
            getline(input_string, car_health, ',');
            int temp1 = stoi(available);
            int temp2 = stoi(req_record);
            int temp3 = stoi(price);
            int temp4 = stoi(car_health);
            if (temp1 == 1 && temp2 <= this->get_emp_record() && temp4>0)
                cout << "Model : " << model << " --> Price : " << price << " --> Car Health : " << car_health << endl;
        }
        car_database.close();
    }
}

void employee::show_rented_cars()
{
    ifstream car_database("cars.csv");
    if (!car_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header;
    getline(car_database, header); // Skip the header

    string line;
    while (getline(car_database, line))
    {
        stringstream input_string(line);
        string model, available, req_record, price, car_health, owner, id, name, return_date_dd, return_date_mm, return_date_yyyy;

        getline(input_string, model, ',');
        getline(input_string, available, ',');
        getline(input_string, req_record, ',');
        getline(input_string, price, ',');
        getline(input_string, car_health, ',');
        getline(input_string, owner, ',');
        getline(input_string, id, ',');
        getline(input_string, name, ',');
        getline(input_string, return_date_dd, ',');
        getline(input_string, return_date_mm, ',');
        getline(input_string, return_date_yyyy, ',');

        // cout << id << " " << this->id << endl;
        if (owner == "2" && id == this->id && name == this->name)
        {
            cout << "Model: " << model << " --> Return Date: " << return_date_dd << "-" << return_date_mm << "-" << return_date_yyyy << endl;
        }
    }
    car_database.close();
}

void employee::rent_car()
{
    cout << "Available cars are : " << endl;
    this->show_available_cars();
    cout << "Enter model you want to rent : ";
    string req_model;
    cin >> req_model;
    int no_of_days;
    cout << "Enter number of days you want to rent : ";
    cin >> no_of_days;

    time_t now = time(0);
    tm *localTime = localtime(&now);
    string yearStr = to_string(1900 + localTime->tm_year);
    string monthStr = to_string(1 + localTime->tm_mon);
    string dayStr = to_string(localTime->tm_mday);

    int day, month, year;
    stringstream(dayStr) >> day;
    stringstream(monthStr) >> month;
    stringstream(yearStr) >> year;

    addDaysToDate(day, month, year, no_of_days);

    string d, m, y;
    d = to_string(day);
    m = to_string(month);
    y = to_string(year);

    ifstream car_database("cars.csv");
    if (car_database.is_open() == false)
        cerr << "Error : Unable to fetch data from database" << endl;

    vector<string> header;
    string header_line = "";
    getline(car_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }
    bool rent = false;
    vector<vector<string>> data;
    string line = "";
    while (getline(car_database, line))
    {
        stringstream input_string(line);
        string mm, a, rr, pr, ch, owner, id, n, rd, rm, ry;
        vector<string> row;
        getline(input_string, mm, ',');
        getline(input_string, a, ',');
        getline(input_string, rr, ',');
        getline(input_string, pr, ',');
        getline(input_string, ch, ',');
        getline(input_string, owner, ',');
        getline(input_string, id, ',');
        getline(input_string, n, ',');
        getline(input_string, rd, ',');
        getline(input_string, rm, ',');
        getline(input_string, ry, ',');

        int curr_health = stoi(ch);
        if (req_model == mm && a == "1" && stoi(rr) <= this->get_emp_record() && stoi(ch)>0)
        {
            int new_health = max(0, curr_health - no_of_days*damage_per_day);
            rent = true;
            row.push_back(mm);
            row.push_back("0");
            row.push_back(rr);
            row.push_back(pr);
            row.push_back(to_string(new_health));
            row.push_back("2");
            row.push_back(this->id);
            row.push_back(this->name);
            row.push_back(d);
            row.push_back(m);
            row.push_back(y);
        }
        else
        {
            row.push_back(mm);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(pr);
            row.push_back(ch);
            row.push_back(owner);
            row.push_back(id);
            row.push_back(n);
            row.push_back(rd);
            row.push_back(rm);
            row.push_back(ry);
        }
        if (!row[0].empty())
            data.push_back(row);
    }
    car_database.close();

    if (rent == false)
        cout << "No such model is available to rent" << endl;
    else
        cout << "Model : " << req_model << " rented successfully" << endl;

    ofstream outfile("cars.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }
}

void employee::check_fine()
{
    time_t now = time(0);
    tm *localTime = localtime(&now);
    string ty = to_string(1900 + localTime->tm_year);
    string tm = to_string(1 + localTime->tm_mon);
    string td = to_string(localTime->tm_mday);

    int your_fine = 0;

    ifstream car_database("cars.csv");
    if (car_database.is_open() == false)
        cerr << "Error : Unable to fetch data from database" << endl;
    else
    {
        string header = "";
        getline(car_database, header);

        string line = "";
        while (getline(car_database, line))
        {
            stringstream input_string(line);
            string owner, id, rd, rm, ry;
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, owner, ',');
            getline(input_string, id, ',');
            getline(input_string, rd, ',');
            getline(input_string, rd, ',');
            getline(input_string, rm, ',');
            getline(input_string, ry, ',');

            if (owner == "2" && id == this->id)
                your_fine += daysBetweenDates(td, tm, ty, rd, rm, ry) * fine_per_day;
        }
        car_database.close();
    }
    cout << "Your fine : " << your_fine << endl;
}

void employee::clear_dues()
{
    int new_er = this->get_emp_record();

    time_t now = time(0);
    tm *localTime = localtime(&now);
    string ty = to_string(1900 + localTime->tm_year);
    string tm = to_string(1 + localTime->tm_mon);
    string td = to_string(localTime->tm_mday);

    int your_fine = 0;

    ifstream car_database("cars.csv");
    if (car_database.is_open() == false)
        cerr << "Error : Unable to fetch data from database" << endl;

    vector<string> header;
    string header_line = "";
    getline(car_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }

    vector<vector<string>> data;
    string line = "";
    while (getline(car_database, line))
    {
        stringstream input_string(line);
        string m, a, rr, pr, ch, owner, id, n, rd, rm, ry;
        vector<string> row;
        getline(input_string, m, ',');
        getline(input_string, a, ',');
        getline(input_string, rr, ',');
        getline(input_string, pr, ',');
        getline(input_string, ch, ',');
        getline(input_string, owner, ',');
        getline(input_string, id, ',');
        getline(input_string, n, ',');
        getline(input_string, rd, ',');
        getline(input_string, rm, ',');
        getline(input_string, ry, ',');


        int curr_health = stoi(ch);
        if (owner == "2" && id == this->id)
        {
            your_fine += daysBetweenDates(td, tm, ty, rd, rm, ry) * fine_per_day;
            int new_health = max(0, curr_health - damage_per_day*daysBetweenDates(td,tm,ty,rd,rm,ry));
            new_er = max(0, new_er - daysBetweenDates(td, tm, ty, rd, rm, ry));
            row.push_back(m);
            row.push_back("1");
            row.push_back(rr);
            row.push_back(pr);
            row.push_back(to_string(new_health));
            row.push_back("0");
            row.push_back("0");
            row.push_back("0");
            row.push_back("00");
            row.push_back("00");
            row.push_back("0000");
        }
        else
        {
            row.push_back(m);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(pr);
            row.push_back(ch);
            row.push_back(owner);
            row.push_back(id);
            row.push_back(n);
            row.push_back(rd);
            row.push_back(rm);
            row.push_back(ry);
        }
        if (!row[0].empty())
            data.push_back(row);
    }
    car_database.close();

    cout << "Pay fine : " << your_fine << endl;

    ofstream outfile("cars.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }

    // we need to update employee record
    vector<string> header_2;
    ifstream employee_database("employee.csv");
    if (!employee_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    employee* emp = new employee(this->id, this->name, this->password, new_er);
    string header_line_2;
    getline(employee_database, header_line_2);
    stringstream header_stream_2(header_line_2);
    string token_2;
    while (getline(header_stream_2, token_2, ','))
    {
        header_2.push_back(token_2);
    }

    vector<vector<string>> data_2;

    string line_2;
    while (getline(employee_database, line_2))
    {
        stringstream ss(line_2);
        string i, n, p, er;
        vector<string> row;
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, p, ',');
        getline(ss, er, ',');
        if (i == emp->id)
        {
            row.push_back(i);
            row.push_back(emp->name);
            row.push_back(emp->password);
            row.push_back(to_string(emp->get_emp_record()));
        }
        else
        {
            row.push_back(i);
            row.push_back(n);
            row.push_back(p);
            row.push_back(er);
        }
        if (!row[0].empty())
            data_2.push_back(row);
    }
    employee_database.close();

    ofstream outfile_2("employee.csv", ios::trunc);
    if (!outfile_2.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header_2.size(); i++)
        {
            outfile_2 << header_2[i];
            if (i != header_2.size() - 1)
                outfile_2 << ",";
        }
        outfile_2 << endl;

        for (int i = 0; i < data_2.size(); i++)
        {
            for (int j = 0; j < data_2[i].size(); j++)
            {
                outfile_2 << data_2[i][j];
                if (j != data_2[i].size() - 1)
                    outfile_2 << ",";
            }
            outfile_2 << endl;
        }
    }
}

// Manager Class Functions
void manager::check_all_cars()
{
    ifstream car_database("cars.csv");
    if (!car_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header;
    getline(car_database, header); // Skip the header

    string line;
    while (getline(car_database, line))
    {
        stringstream input_string(line);
        string model, available, req_record, price, ch, owner, id, name, return_date_dd, return_date_mm, return_date_yyyy;

        getline(input_string, model, ',');
        getline(input_string, available, ',');
        getline(input_string, req_record, ',');
        getline(input_string, price, ',');
        getline(input_string, ch, ',');
        getline(input_string, owner, ',');
        getline(input_string, id, ',');
        getline(input_string, name, ',');
        getline(input_string, return_date_dd, ',');
        getline(input_string, return_date_mm, ',');
        getline(input_string, return_date_yyyy, ',');

        if (available == "1")
        {
            cout << "Model : " << model << "--> Not Rented" << " --> Car Health : " << ch << endl;
        }
        else
        {
            if (owner == "1") // Customer
            {
                cout << "Model : " << model << " --> Rented to Customer : " << name << " (" << id << ") --> "
                     << "Return Date : " << return_date_dd << "-" << return_date_mm << "-" << return_date_yyyy << " --> Car Health : " << ch << endl;
            }
            else // Employee
            {
                cout << "Model : " << model << " --> Rented to Employee : " << name << " (" << id << ") --> "
                     << "Return Date : " << return_date_dd << "-" << return_date_mm << "-" << return_date_yyyy << " --> Car Health : " << ch << endl;
            }
        }
    }
    car_database.close();
}

void manager::add_customer(customer *cust)
{
    ofstream outfile("customers.csv", ios::app);
    if (!outfile.is_open())
    {
        cerr << "Error: 1Unable to open file." << endl;
    }
    else
    {
        outfile << cust->id << "," << cust->name << "," << cust->password << "," << cust->get_cust_record() << endl;
        outfile.close();
        cout << "New-Customer " << cust->name << " added successfully" << endl;
    }
}

void manager::add_employee(employee *emp)
{
    ofstream outfile("employee.csv", ios::app);
    if (!outfile.is_open())
    {
        cerr << "Error: 1Unable to open file." << endl;
    }
    else
    {
        outfile << emp->id << "," << emp->name << "," << emp->password << "," << emp->get_emp_record() << endl;
        outfile.close();
        cout << "New-Employee " << emp->name << " added successfully" << endl;
    }
}

void manager::add_car(car *new_car)
{
    ofstream outfile("cars.csv", ios::app);
    if (!outfile.is_open())
    {
        cerr << "Error: 1Unable to open file." << endl;
    }
    else
    {
        outfile << new_car->model << "," << new_car->available << "," << new_car->req_record << "," << new_car->price << "," << new_car->car_health << "," << new_car->owner << "," << new_car->id << "," << new_car->name << "," << new_car->return_date_dd << "," << new_car->return_date_mm << "," << new_car->return_date_yyyy << endl;
        outfile.close();
        cout << "New-Car " << new_car->model << " added successfully" << endl;
    }
}

void manager::update_customer(customer *cust)
{
    vector<string> header;
    ifstream customer_database("customers.csv");
    if (!customer_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header_line;
    getline(customer_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }

    vector<vector<string>> data;

    string line;
    while (getline(customer_database, line))
    {
        stringstream ss(line);
        string i, n, p, cr;
        vector<string> row;
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, p, ',');
        getline(ss, cr, ',');
        if (i == cust->id)
        {
            row.push_back(i);
            row.push_back(cust->name);
            row.push_back(cust->password);
            row.push_back(to_string(cust->get_cust_record()));
        }
        else
        {
            row.push_back(i);
            row.push_back(n);
            row.push_back(p);
            row.push_back(cr);
        }
        if (!row[0].empty())
            data.push_back(row);
    }
    customer_database.close();

    ofstream outfile("customers.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }
}

void manager::update_employee(employee *emp)
{
    vector<string> header;
    ifstream employee_database("employee.csv");
    if (!employee_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header_line;
    getline(employee_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }

    vector<vector<string>> data;

    string line;
    while (getline(employee_database, line))
    {
        stringstream ss(line);
        string i, n, p, cr;
        vector<string> row;
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, p, ',');
        getline(ss, cr, ',');
        if (i == emp->id)
        {
            row.push_back(i);
            row.push_back(emp->name);
            row.push_back(emp->password);
            row.push_back(to_string(emp->get_emp_record()));
        }
        else
        {
            row.push_back(i);
            row.push_back(n);
            row.push_back(p);
            row.push_back(cr);
        }
        if (!row[0].empty())
            data.push_back(row);
    }
    employee_database.close();

    ofstream outfile("employee.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }
}

void manager::update_car(string model)
{
    bool change_date = false;
    string price, rrr, dd, mm, yyyy;
    cout << "Enter new price of car : ";
    cin >> price;
    cout << "Enter new minimum user record to rent the car : ";
    cin >> rrr;

    cout << "Enter 1 to change return date" << endl;
    cout << "Enter otherwise to proceed" << endl;
    int inp;
    cin >> inp;
    if(inp==1)
    {
        cout << "Enter new date of return(DD MM YYYY) : ";
        cin >> dd;
        cin >> mm;
        cin >> yyyy;
        change_date=true;
    }
    cout << "Enter new Car Health : ";
    string cch;
    cin >> cch;

    vector<string> header;
    ifstream car_database("cars.csv");
    if (!car_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header_line;
    getline(car_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }

    vector<vector<string>> data;

    string line;
    while (getline(car_database, line))
    {
        stringstream ss(line);
        string mo, a, rr, p, ch, o, i, n, d, m, y;
        vector<string> row;
        getline(ss, mo, ',');
        getline(ss, a, ',');
        getline(ss, rr, ',');
        getline(ss, p, ',');
        getline(ss, ch, ',');
        getline(ss, o, ',');
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, d, ',');
        getline(ss, m, ',');
        getline(ss, y, ',');

        if (mo == model)
        {
            row.push_back(mo);
            row.push_back(a);
            row.push_back(rrr);
            row.push_back(price);
            row.push_back(cch);
            row.push_back(o);
            row.push_back(i);
            row.push_back(n);
            if(change_date)
            {
                row.push_back(dd);
                row.push_back(mm);
                row.push_back(yyyy);
            }
            else
            {
                row.push_back(m);
                row.push_back(m);
                row.push_back(y);
            }
        }
        else
        {
            row.push_back(mo);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(p);
            row.push_back(ch);
            row.push_back(o);
            row.push_back(i);
            row.push_back(n);
            row.push_back(d);
            row.push_back(m);
            row.push_back(y);
        }
        if (!row[0].empty())
            data.push_back(row);
    }
    car_database.close();

    ofstream outfile("cars.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }
}

void manager::delete_customer(string id)
{
    vector<string> header;
    ifstream customer_database("customers.csv");
    if (!customer_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header_line;
    getline(customer_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }

    vector<vector<string>> data;

    string line;
    while (getline(customer_database, line))
    {
        stringstream ss(line);
        string i, n, p, cr;
        vector<string> row;
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, p, ',');
        getline(ss, cr, ',');
        if (i != id)
        {
            row.push_back(i);
            row.push_back(n);
            row.push_back(p);
            row.push_back(cr);
            if (!row[0].empty())
                data.push_back(row);
        }
    }
    customer_database.close();

    ofstream outfile("customers.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }

    // updating car owned by this customer to available
    vector<string> header_2;
    ifstream car_database_2("cars.csv");
    if (!car_database_2.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header_line_2;
    getline(car_database_2, header_line_2);
    stringstream header_stream_2(header_line_2);
    string token_2;
    while (getline(header_stream_2, token_2, ','))
    {
        header_2.push_back(token_2);
    }

    vector<vector<string>> data_2;

    string line_2;
    while (getline(car_database_2, line_2))
    {
        stringstream ss(line_2);
        string mo, a, rr, p, ch, o, i, n, d, m, y;
        vector<string> row;
        getline(ss, mo, ',');
        getline(ss, a, ',');
        getline(ss, rr, ',');
        getline(ss, p, ',');
        getline(ss, ch, ',');
        getline(ss, o, ',');
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, d, ',');
        getline(ss, m, ',');
        getline(ss, y, ',');

        if (o == "1" && i == id)
        {
            row.push_back(mo);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(p);
            row.push_back(ch);
            row.push_back("0");
            row.push_back("0");
            row.push_back("0");
            row.push_back("00");
            row.push_back("00");
            row.push_back("0000");
        }
        else
        {
            row.push_back(mo);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(p);
            row.push_back(ch);
            row.push_back(o);
            row.push_back(i);
            row.push_back(n);
            row.push_back(d);
            row.push_back(m);
            row.push_back(y);
        }
        if (!row[0].empty())
            data_2.push_back(row);
    }
    car_database_2.close();

    ofstream outfile_2("cars.csv", ios::trunc);
    if (!outfile_2.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header_2.size(); i++)
        {
            outfile_2 << header_2[i];
            if (i != header_2.size() - 1)
                outfile_2 << ",";
        }
        outfile_2 << endl;

        for (int i = 0; i < data_2.size(); i++)
        {
            for (int j = 0; j < data_2[i].size(); j++)
            {
                outfile_2 << data_2[i][j];
                if (j != data_2[i].size() - 1)
                    outfile_2 << ",";
            }
            outfile_2 << endl;
        }
    }

    cout << "Customer deleted!" << endl;
}

void manager::delete_employee(string id)
{
    vector<string> header;
    ifstream employee_database("employee.csv");
    if (!employee_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header_line;
    getline(employee_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }

    vector<vector<string>> data;

    string line;
    while (getline(employee_database, line))
    {
        stringstream ss(line);
        string i, n, p, cr;
        vector<string> row;
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, p, ',');
        getline(ss, cr, ',');
        if (i != id)
        {
            row.push_back(i);
            row.push_back(n);
            row.push_back(p);
            row.push_back(cr);
            if (!row[0].empty())
                data.push_back(row);
        }
    }
    employee_database.close();

    ofstream outfile("employee.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }

    vector<string> header_2;
    ifstream car_database_2("cars.csv");
    if (!car_database_2.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header_line_2;
    getline(car_database_2, header_line_2);
    stringstream header_stream_2(header_line_2);
    string token_2;
    while (getline(header_stream_2, token_2, ','))
    {
        header_2.push_back(token_2);
    }

    vector<vector<string>> data_2;

    string line_2;
    while (getline(car_database_2, line_2))
    {
        stringstream ss(line_2);
        string mo, a, rr, p, ch, o, i, n, d, m, y;
        vector<string> row;
        getline(ss, mo, ',');
        getline(ss, a, ',');
        getline(ss, rr, ',');
        getline(ss, p, ',');
        getline(ss, ch, ',');
        getline(ss, o, ',');
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, d, ',');
        getline(ss, m, ',');
        getline(ss, y, ',');

        if (o == "2" && i == id)
        {
            row.push_back(mo);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(p);
            row.push_back(ch);
            row.push_back("0");
            row.push_back("0");
            row.push_back("0");
            row.push_back("00");
            row.push_back("00");
            row.push_back("0000");
        }
        else
        {
            row.push_back(mo);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(p);
            row.push_back(ch);
            row.push_back(o);
            row.push_back(i);
            row.push_back(n);
            row.push_back(d);
            row.push_back(m);
            row.push_back(y);
        }
        if (!row[0].empty())
            data_2.push_back(row);
    }
    car_database_2.close();

    ofstream outfile_2("cars.csv", ios::trunc);
    if (!outfile_2.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header_2.size(); i++)
        {
            outfile_2 << header_2[i];
            if (i != header_2.size() - 1)
                outfile_2 << ",";
        }
        outfile_2 << endl;

        for (int i = 0; i < data_2.size(); i++)
        {
            for (int j = 0; j < data_2[i].size(); j++)
            {
                outfile_2 << data_2[i][j];
                if (j != data_2[i].size() - 1)
                    outfile_2 << ",";
            }
            outfile_2 << endl;
        }
    }

    cout << "Employee deleted" << endl;
}

void manager::delete_car(string model)
{
    vector<string> header;
    ifstream car_database("cars.csv");
    if (!car_database.is_open())
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return;
    }

    string header_line;
    getline(car_database, header_line);
    stringstream header_stream(header_line);
    string token;
    while (getline(header_stream, token, ','))
    {
        header.push_back(token);
    }

    vector<vector<string>> data;

    string line;
    while (getline(car_database, line))
    {
        stringstream ss(line);
        string mo, a, rr, p, o, i, n, d, m, y;
        vector<string> row;
        getline(ss, mo, ',');
        getline(ss, a, ',');
        getline(ss, rr, ',');
        getline(ss, p, ',');
        getline(ss, o, ',');
        getline(ss, i, ',');
        getline(ss, n, ',');
        getline(ss, d, ',');
        getline(ss, m, ',');
        getline(ss, y, ',');

        if (mo != model)
        {
            row.push_back(mo);
            row.push_back(a);
            row.push_back(rr);
            row.push_back(p);
            row.push_back(o);
            row.push_back(i);
            row.push_back(n);
            row.push_back(d);
            row.push_back(m);
            row.push_back(y);
            if (!row[0].empty())
                data.push_back(row);
        }
    }
    car_database.close();

    ofstream outfile("cars.csv", ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
    }
    else
    {
        for (int i = 0; i < header.size(); i++)
        {
            outfile << header[i];
            if (i != header.size() - 1)
                outfile << ",";
        }
        outfile << endl;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                outfile << data[i][j];
                if (j != data[i].size() - 1)
                    outfile << ",";
            }
            outfile << endl;
        }
    }
    cout << "Car deleted" << endl;
}

// Functions
int valid_user(string file, string &id, string &name, string &password);
void customer_login(customer *cust);
void employee_login(employee *emp);
void manager_login(manager *man);
bool check_distinct_user(string file, string &id);
void cust_registration(string file, customer *new_cust);
void emp_registration(string file, employee *new_emp);
void man_registration(string file, manager *new_man);
bool search_car(string &s);

int main()
{
    cout << "Welcome to CAR RENTAL SYSTEM" << endl;
    while (true)
    {
        cout << "Enter 1 to login" << endl;
        cout << "Enter 2 to register" << endl;
        cout << "Enter 3 to terminate" << endl;
        string main_inp;
        cin >> main_inp;
    

        if (main_inp == "1") // login
        {
            cout << "Enter 1 for customer login" << endl;
            cout << "Enter 2 for employee login" << endl;
            cout << "Enter 3 for manager login" << endl;
            cout << "Enter otherwise to go back" << endl;

            int login_inp;
            cin >> login_inp;
            if (login_inp == 1) // Customer login
            {
                string id_inp, name_inp, pass_inp;
                cout << "Enter name : ";
                cin >> name_inp;
                cout << "Enter user id : ";
                cin >> id_inp;
                cout << "Enter password : ";
                cin >> pass_inp;

                // need to check if this user exists
                int cust_rec = valid_user("customers.csv", id_inp, name_inp, pass_inp);
                if (cust_rec)
                {
                    customer *cust = new customer(id_inp, name_inp, pass_inp, cust_rec);
                    customer_login(cust);
                }
                else
                    cout << "No such Customer exists" << endl;
            }
            else if (login_inp == 2) // Employee Login
            {
                string id_inp, name_inp, pass_inp;
                cout << "Enter name : ";
                cin >> name_inp;
                cout << "Enter user id : ";
                cin >> id_inp;
                cout << "Enter password : ";
                cin >> pass_inp;

                // need to check if this user exists
                int emp_rec = valid_user("employee.csv", id_inp, name_inp, pass_inp);
                if (emp_rec)
                {
                    employee *emp = new employee(id_inp, name_inp, pass_inp, emp_rec);
                    employee_login(emp);
                }
                else
                    cout << "No such Employee exists" << endl;
            }
            else if (login_inp == 3) // Manager Login
            {
                string id_inp, name_inp, pass_inp;
                cout << "Enter name : ";
                cin >> name_inp;
                cout << "Enter user id : ";
                cin >> id_inp;
                cout << "Enter password : ";
                cin >> pass_inp;

                // need to check if this user exists
                int valid_login = valid_user("manager.csv", id_inp, name_inp, pass_inp);
                if (valid_login)
                {
                    manager *man = new manager(id_inp, name_inp, pass_inp);
                    manager_login(man);
                }
                else
                    cout << "No such Manager exists" << endl;
            }
            else
                cout << "Session expired" << endl;
            
        }
        else if (main_inp == "2") // register
        {
            cout << "Enter 1 for customer register" << endl;
            cout << "Enter 2 for employee register" << endl;
            cout << "Enter 3 for manager register" << endl;
            cout << "Enter otherwise to go back" << endl;

            int reg_inp;
            cin >> reg_inp;
            if (reg_inp == 1) // Customer register
            {
                string id_inp, name_inp, pass_inp;
                cout << "Enter name : ";
                cin >> name_inp;
                cout << "Enter user id : ";
                cin >> id_inp;
                // need to check if this customer user id exists in database
                bool valid_user_id = check_distinct_user("customers.csv", id_inp);
                if (valid_user_id)
                {
                    cout << "Enter password : ";
                    cin >> pass_inp;
                    customer *new_cust = new customer(id_inp, name_inp, pass_inp);
                    cust_registration("customers.csv", new_cust);
                }
                else
                    cout << "A customer already exists with such user id" << endl;
            }
            else if (reg_inp == 2) // Employee register
            {
                string id_inp, name_inp, pass_inp;
                cout << "Enter name : ";
                cin >> name_inp;
                cout << "Enter user id : ";
                cin >> id_inp;
                // need to check if this employee user id exists in database
                bool valid_user_id = check_distinct_user("employee.csv", id_inp);
                if (valid_user_id)
                {
                    cout << "Enter password : ";
                    cin >> pass_inp;
                    employee *new_emp = new employee(id_inp, name_inp, pass_inp);
                    emp_registration("employee.csv", new_emp);
                }
                else
                    cout << "A Employee already exists with such user id" << endl;
            }
            else if (reg_inp == 3) // Manager register
            {
                string id_inp, name_inp, pass_inp;
                cout << "Enter name : ";
                cin >> name_inp;
                cout << "Enter user id : ";
                cin >> id_inp;
                // need to check if this employee user id exists in database
                bool valid_user_id = check_distinct_user("manager.csv", id_inp);
                if (valid_user_id)
                {
                    cout << "Enter password : ";
                    cin >> pass_inp;
                    manager *new_man = new manager(id_inp, name_inp, pass_inp);
                    man_registration("manager.csv", new_man);
                }
                else
                    cout << "A Manager already exists with such user id" << endl;
            }
            
        }
        else if (main_inp == "3")
        {
            cout << "Session expired" << endl;
            break;
        }
        else
        {
            cout << "Invalid Input" << endl;
            cout << "Try Again" << endl;
        }
    }
}

bool check_distinct_user(string file, string &i)
{
    ifstream database(file);

    if (database.is_open() == false)
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return false;
    }
    else
    {
        string header;
        getline(database, header);

        string line = "";
        while (getline(database, line))
        {
            stringstream input_string(line);
            string id, name, password;
            getline(input_string, id, ',');
            getline(input_string, name, ',');
            getline(input_string, password, ',');
            if (id == i)
                return false;
            line = "";
        }
        database.close();
        return true;
    }
}

void cust_registration(string file, customer *cust)
{
    ofstream outfile(file, ios::app);
    if (!outfile.is_open())
    {
        cerr << "Error: 1Unable to open file." << endl;
    }
    else
    {
        outfile << cust->id << "," << cust->name << "," << cust->password << "," << cust->get_cust_record() << endl;
        outfile.close();
        cout << "New-Customer " << cust->name << " registered successfully" << endl;
    }
}

void emp_registration(string file, employee *emp)
{
    ofstream outfile(file, ios::app);
    if (!outfile.is_open())
    {
        cerr << "Error: 1Unable to open file." << endl;
    }
    else
    {
        outfile << emp->id << "," << emp->name << "," << emp->password << "," << emp->get_emp_record() << endl;
        outfile.close();
        cout << "New-Employee " << emp->name << " registered successfully" << endl;
    }
}

void man_registration(string file, manager *man)
{
    ofstream outfile(file, ios::app);
    if (!outfile.is_open())
    {
        cerr << "Error: 1Unable to open file." << endl;
    }
    else
    {
        outfile << man->id << "," << man->name << "," << man->password << endl;
        outfile.close();
        cout << "New-Manager " << man->name << " registered successfully" << endl;
    }
}

int valid_user(string file, string &i, string &n, string &p)
{
    // check for manager
    if (file == "manager.csv")
    {
        ifstream database(file);

        if (database.is_open() == false)
        {
            cerr << "Error : Unable to fetch data from database" << endl;
            return 0;
        }
        else
        {
            string header;
            getline(database, header);

            string line = "";
            while (getline(database, line))
            {
                stringstream input_string(line);
                string id, name, password, cr;
                getline(input_string, id, ',');
                getline(input_string, name, ',');
                getline(input_string, password, ',');
                // getline(input_string, cr, ',');
                if (id == i && name == n && password == p)
                    return 1;
                line = "";
            }
            database.close();
            return 0;
        }
    }
    // check for customer and database
    ifstream database(file);

    if (database.is_open() == false)
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return 0;
    }
    else
    {
        string header;
        getline(database, header);

        string line = "";
        while (getline(database, line))
        {
            stringstream input_string(line);
            string id, name, password, cr;
            getline(input_string, id, ',');
            getline(input_string, name, ',');
            getline(input_string, password, ',');
            getline(input_string, cr, ',');
            // cout << id << endl;
            // cout << name << endl;
            // cout << password << endl;
            // cout << cr << endl;
            if (id == i && name == n && password == p)
                return stoi(cr);
            line = "";
        }
        database.close();
        return 0;
    }
}

void customer_login(customer *cust)
{
    cout << "Welcome, " << cust->name << " to CAR RENTAL SYSTEM" << endl;

    bool terminate = false;
    while (!terminate)
    {
        cout << "Enter 1 to check all available cars" << endl;
        cout << "Enter 2 to check your rented cars" << endl;
        cout << "Enter 3 to rent a car" << endl;
        cout << "Enter 4 to check fine" << endl;
        cout << "Enter 5 to clear dues" << endl;
        cout << "Enter 6 to log out" << endl;

        int cust_inp;
        cin >> cust_inp;

        switch (cust_inp)
        {
        case 1: // check all available cars
            cust->show_available_cars();
            break;
        case 2: // check rented cars
            cust->show_rented_cars();
            break;
        case 3: // rent a car
            cust->rent_car();
            break;
        case 4: // check fine
            cust->check_fine();
            break;
        case 5: // clear dues
            cust->clear_dues();
            break;
        case 6: // terminate
            terminate = true;
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }
}

void employee_login(employee *emp)
{
    cout << "Welcome, " << emp->name << " to CAR RENTAL SYSTEM" << endl;

    bool terminate = false;
    while (!terminate)
    {
        cout << "Enter 1 to check all available cars" << endl;
        cout << "Enter 2 to check your rented cars" << endl;
        cout << "Enter 3 to rent a car" << endl;
        cout << "Enter 4 to check fine" << endl;
        cout << "Enter 5 to clear dues" << endl;
        cout << "Enter 6 to log out" << endl;

        int emp_inp;
        cin >> emp_inp;

        switch (emp_inp)
        {
        case 1: // check all available cars
            emp->show_available_cars();
            break;
        case 2: // check rented cars
            emp->show_rented_cars();
            break;
        case 3: // rent a car
            emp->rent_car();
            break;
        case 4: // check fine
            emp->check_fine();
            break;
        case 5: // clear dues
            emp->clear_dues();
            break;
        case 6: // terminate
            terminate = true;
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }
}

void manager_login(manager *man)
{
    cout << "Welcome, " << man->name << " to CAR RENTAL SYSTEM" << endl;

    bool terminate = false;
    while (!terminate)
    {
        cout << "Enter 1 to check all cars" << endl;
        cout << "Enter 2 to modify Car details" << endl;
        cout << "Enter 3 to modify Customer details" << endl;
        cout << "Enter 4 to modify Employee details" << endl;
        cout << "Enter 5 to log out" << endl;

        int man_inp;
        cin >> man_inp;

        switch (man_inp)
        {
        case 1: // check all  cars
            man->check_all_cars();
            break;
        case 2: // modify car details

            while (true)
            {
                cout << "Enter 1 to add Car" << endl;
                cout << "Enter 2 to update Car" << endl;
                cout << "Enter 3 to delete Car" << endl;
                cout << "Enter 4 to go back" << endl;

                int car_inp;
                cin >> car_inp;
                if (car_inp == 1) // Add car
                {
                    cout << "Enter model : ";
                    string model;
                    cin >> model;
                    if (search_car(model))
                        cout << "A car of this model already exists" << endl;
                    else
                    {
                        int req_record, price;
                        cout << "Enter the minimum user_record to rent this car : ";
                        cin >> req_record;
                        cout << "Enter the price of car : ";
                        cin >> price;
                        car *new_car = new car(model, price, req_record);
                        man->add_car(new_car);
                    }
                }
                else if (car_inp == 2) // Update car
                {
                    cout << "Enter the model of car you want to update : ";
                    string m;
                    cin >> m;
                    if (search_car(m))
                    {
                        man->update_car(m);
                        cout << "Car of model " << m << " updated" << endl;
                    }
                    else
                        cout << "No car exists of this model" << endl;
                }
                else if (car_inp == 3) // Delete car
                {
                    cout << "Enter the model of car you want to delete : ";
                    string m;
                    cin >> m;
                    if (search_car(m))
                    {
                        man->delete_car(m);
                        cout << "Car of model " << m << " deleted" << endl;
                    }
                    else
                        cout << "No car exists of this model" << endl;
                }
                else if (car_inp == 4)
                    break;
                else
                {
                    cout << "Invalid Input" << endl;
                    break;
                }
            }

            break;
        case 3: // modify customer details

            while (true)
            {
                cout << "Enter 1 to add Customer" << endl;
                cout << "Enter 2 to update Customer" << endl;
                cout << "Enter 3 to delete Customer" << endl;
                cout << "Enter 4 to go back" << endl;

                int cust_inp;
                cin >> cust_inp;
                if (cust_inp == 1) // Add Customer
                {
                    string i, n, p;
                    cout << "Enter user id : ";
                    cin >> i;
                    if (!check_distinct_user("customers.csv", i))
                        cout << "A Customer already exists with this user id" << endl;
                    else
                    {
                        cout << "Enter name : ";
                        cin >> n;
                        cout << "Enter password : ";
                        cin >> p;
                        customer *cust = new customer(i, n, p);
                        man->add_customer(cust);
                    }
                }
                else if (cust_inp == 2) // Update Customer
                {
                    cout << "Enter the id of customer you want to update : ";
                    string i;
                    cin >> i;
                    if (check_distinct_user("customers.csv", i))
                    {
                        cout << "No such customer exists" << endl;
                    }
                    else
                    {
                        string n, p, cr;
                        cout << "Enter new name : ";
                        cin >> n;
                        cout << "Enter new password : ";
                        cin >> p;
                        cout << "Enter new customer record : ";
                        cin >> cr;
                        customer *cust = new customer(i, n, p, stoi(cr));
                        man->update_customer(cust);
                        cout << "Customer with user id " << i << " updated" << endl;
                    }
                }
                else if (cust_inp == 3) // Delete Customer
                {
                    cout << "Enter the id of customer you want to delete : ";
                    string i;
                    cin >> i;
                    if (check_distinct_user("customers.csv", i))
                    {
                        cout << "No such customer exists" << endl;
                    }
                    else
                    {
                        man->delete_customer(i);
                    }
                }
                else if (cust_inp == 4)
                    break;
                else
                    cout << "Invalid Input" << endl;
            }

            break;
        case 4: // modify employee details

            while (true)
            {
                cout << "Enter 1 to add Employee" << endl;
                cout << "Enter 2 to update Employee" << endl;
                cout << "Enter 3 to delete Employee" << endl;
                cout << "Enter 4 to go back" << endl;

                int emp_inp;
                cin >> emp_inp;
                if (emp_inp == 1) // Add Employee
                {
                    string i, n, p;
                    cout << "Enter user id : ";
                    cin >> i;
                    if (!check_distinct_user("employee.csv", i))
                        cout << "A Employee already exists with this user id" << endl;
                    else
                    {
                        cout << "Enter name : ";
                        cin >> n;
                        cout << "Enter password : ";
                        cin >> p;
                        employee *emp = new employee(i, n, p);
                        man->add_employee(emp);
                    }
                }
                else if (emp_inp == 2) // Update Employee
                {
                    cout << "Enter the id of employee you want to update : ";
                    string i;
                    cin >> i;
                    if (check_distinct_user("employee.csv", i))
                    {
                        cout << "No such employee exists" << endl;
                    }
                    else
                    {
                        string n, p, cr;
                        cout << "Enter new name : ";
                        cin >> n;
                        cout << "Enter new password : ";
                        cin >> p;
                        cout << "Enter new employee record : ";
                        cin >> cr;
                        employee *emp = new employee(i, n, p, stoi(cr));
                        man->update_employee(emp);
                        cout << "Employee with user id " << i << " updated" << endl;
                    }
                }
                else if (emp_inp == 3) // Delete Employee
                {
                    cout << "Enter the id of employee you want to delete : ";
                    string i;
                    cin >> i;
                    if (check_distinct_user("employee.csv", i))
                    {
                        cout << "No such employee exists" << endl;
                    }
                    else
                    {
                        man->delete_employee(i);
                        cout << "Employee with user id " << i << " deleted" << endl;
                    }
                }
                else if (emp_inp == 4)
                    break;
                else
                    cout << "Invalid Input" << endl;
            }

            break;
        case 5: // terminate
            terminate = true;
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }
}

bool search_car(string &model)
{
    ifstream database("cars.csv");

    if (database.is_open() == false)
    {
        cerr << "Error : Unable to fetch data from database" << endl;
        return 0;
    }
    else
    {
        string header;
        getline(database, header);

        string line = "";
        while (getline(database, line))
        {
            stringstream input_string(line);
            string m;
            getline(input_string, m, ',');
            if (m == model)
                return 1;
        }
        database.close();
        return 0;
    }
}
