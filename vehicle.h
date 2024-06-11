#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
using namespace std;

class Vehicle {
private:
    string plate;
    string intime;

public:
    Vehicle(string plate, string intime) : plate(plate), intime(intime) {}

    virtual ~Vehicle() {}

    virtual double calculatePrice(const string& outtime) = 0;

    string getPlate() const {
        return plate;
    }

    string getIntime() const {
        return intime;
    }

    void parseTime(const string& timeStr, int& h, int& m, int& s) {
        h = m = s = 0;
        int pos1 = timeStr.find(':');
        int pos2 = timeStr.find(':', pos1 + 1);
        if (pos1 != -1 && pos2 != -1) {
            h = stoi(timeStr.substr(0, pos1));
            m = stoi(timeStr.substr(pos1 + 1, pos2 - pos1 - 1));
            s = stoi(timeStr.substr(pos2 + 1));
        }
    }

    int timeToSeconds(const string& timeStr) {
        int h, m, s;
        parseTime(timeStr, h, m, s);
        return h * 3600 + m * 60 + s;
    }

    bool isDayTime(const string& timeStr) {
        int seconds = timeToSeconds(timeStr);
        int dayStart = timeToSeconds("06:00:00");
        int dayEnd = timeToSeconds("18:00:00");
        return seconds >= dayStart && seconds < dayEnd;
    }

    virtual bool isMotorbike() { return false; }
};

class Bike : public Vehicle {
public:
    Bike(string plate, string intime) : Vehicle(plate, intime) {}

    double calculatePrice(const string& outtime) override {
        int inTime = timeToSeconds(getIntime());
        int outTime = timeToSeconds(outtime);

        if (outTime <= inTime) return -1;

        bool inDay = isDayTime(getIntime());
        bool outDay = isDayTime(outtime);

        if (!inDay && !outDay) return 2000; // Night - Night
        if (inDay && outDay) return 1000; // Day - Day
        if (!inDay && outDay) return 3000; // Night - Day
        return 5000; // Night - Day - Night
    }
};

class Motorbike : public Vehicle {
public:
    Motorbike(string plate, string intime) : Vehicle(plate, intime) {}

    double calculatePrice(const string& outtime) override {
        int inTime = timeToSeconds(getIntime());
        int outTime = timeToSeconds(outtime);

        if (outTime <= inTime) return -1;

        bool inDay = isDayTime(getIntime());
        bool outDay = isDayTime(outtime);

        if (!inDay && !outDay) return 5000; // Night - Night
        if (inDay && outDay) return 3000; // Day - Day
        if (!inDay && outDay) return 8000; // Night - Day
        return 13000; // Night - Day - Night
    }

    bool isMotorbike() override { return true; }
};

#endif
