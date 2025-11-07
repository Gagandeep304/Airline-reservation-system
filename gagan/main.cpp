#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

// Utility functions
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sleepMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// ===================== Airline Class =====================
class Airline {
private:
    string Flight, Des, Dep;
    int Seats;

public:
    Airline(string flight, string des, string dep, int seats) {
        Flight = flight;
        Des = des;
        Dep = dep;
        Seats = seats;
    }

    string getFlight() { return Flight; }
    string getDes() { return Des; }
    string getDep() { return Dep; }
    int getSeat() { return Seats; }

    void update(const string &flight) {
        ifstream in("Flight.txt");
        ofstream out("Flight_Temp.txt");

        if (!in || !out) {
            cout << "Error: File can't open!" << endl;
            return;
        }

        string line;
        while (getline(in, line)) {
            int pos = line.find(flight);
            if (pos != string::npos) {
                int current = Seats - 1;
                Seats = current;

                stringstream ss;
                ss << current;
                string strCurrent = ss.str();

                int seatPos = line.find_last_of(':');
                if (seatPos != string::npos) {
                    line.replace(seatPos + 2, string::npos, strCurrent);
                }
            }
            out << line << endl;
        }

        out.close();
        in.close();

        remove("Flight.txt");
        rename("Flight_Temp.txt", "Flight.txt");

        cout << "Seat Reserved Successfully!" << endl;
    }
};

// ===================== Display Function =====================
void display() {
    ifstream in("Flight.txt");
    if (!in) {
        cout << "Error: File Can't Open!" << endl;
        return;
    }

    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
}

// ===================== Main Function =====================
int main() {
    Airline flight1("F101", "UAE", "England", 50);
    Airline flight2("F202", "UAE", "USA", 40);
    Airline flight3("F303", "UAE", "Canada", 2);

    ofstream out("Flight.txt");
    if (!out) {
        cout << "Error: File can't open!" << endl;
        return 1;
    }

    out << "\t " << flight1.getFlight() << " : " << flight1.getDes() << " : " << flight1.getDep()
        << " : " << flight1.getSeat() << endl
        << endl;

    out << "\t " << flight2.getFlight() << " : " << flight2.getDes() << " : " << flight2.getDep()
        << " : " << flight2.getSeat() << endl
        << endl;

    out << "\t " << flight3.getFlight() << " : " << flight3.getDes() << " : " << flight3.getDep()
        << " : " << flight3.getSeat() << endl
        << endl;

    cout << "Data Saved Successfully!" << endl;
    out.close();

    bool exitProgram = false;
    while (!exitProgram) {
        clearScreen();
        cout << "\t Welcome To Airline Management System" << endl;
        cout << "\t ************************************" << endl;
        cout << "\t 1. Reserve A Seat." << endl;
        cout << "\t 2. Exit." << endl;
        cout << "\t Enter Your Choice: ";
        int val;
        cin >> val;

        if (val == 1) {
            clearScreen();
            display();
            string flight;
            cout << "Enter Flight No: ";
            cin >> flight;

            if (flight == flight1.getFlight() && flight1.getSeat() > 0) {
                flight1.update(flight);
            } else if (flight == flight1.getFlight()) {
                cout << "Sorry, Seats Not Available!" << endl;
            }

            if (flight == flight2.getFlight() && flight2.getSeat() > 0) {
                flight2.update(flight);
            } else if (flight == flight2.getFlight()) {
                cout << "Sorry, Seats Not Available!" << endl;
            }

            if (flight == flight3.getFlight() && flight3.getSeat() > 0) {
                flight3.update(flight);
            } else if (flight == flight3.getFlight()) {
                cout << "Sorry, Seats Not Available!" << endl;
            }

            sleepMs(3000);
        } else if (val == 2) {
            clearScreen();
            cout << "Good Luck!" << endl;
            sleepMs(2000);
            exitProgram = true;
        } else {
            cout << "Invalid Option!" << endl;
            sleepMs(2000);
        }
    }

    return 0;
}
