#include "list.h"
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int main() {
    LinkedList* parking = new LinkedList();
    string input;
    string output; // Chuỗi lưu trữ kết quả đầu ra tạm thời
    while (true) {
        getline(cin, input);
        if (input == "*") {
            break;
        } else {
            int spacePos = input.find(' ');
            string intime = input.substr(0, spacePos);
            string plate = input.substr(spacePos + 1);

            Vehicle* vehicle;
            if (plate.substr(0, 4) == "xxxx") {
                vehicle = new Bike(plate, intime);
            } else {
                vehicle = new Motorbike(plate, intime);
            }
            parking->append(vehicle);
        }
    }

    while (true) {
        getline(cin, input);
        if (input == "***") {
            break;
        }
        int spacePos = input.find(' ');
        string command = input.substr(0, spacePos);
        string rest = input.substr(spacePos + 1);

        if (command == "list") {
            parking->listPlates(output);
        } else if (command == "find") {
            output += to_string(parking->find(rest)) + "\n";
        } else if (command == "in") {
            int spacePos1 = rest.find(' ');
            string intime = rest.substr(0, spacePos1);
            string plate = rest.substr(spacePos1 + 1);
            Vehicle* vehicle;
            if (plate.substr(0, 4) == "xxxx") {
                vehicle = new Bike(plate, intime);
            } else {
                vehicle = new Motorbike(plate, intime);
            }
            output += to_string(parking->in(intime, vehicle)) + "\n";
        } else if (command == "out") {
            int spacePos1 = rest.find(' ');
            string outtime = rest.substr(0, spacePos1);
            string plate = rest.substr(spacePos1 + 1);
            output += to_string(parking->out(outtime, plate)) + "\n";
        } else if (command == "cnt-moto") {
            output += to_string(parking->cnt_moto()) + "\n";
        } else if (command == "bill") {
            int spacePos1 = rest.find(' ');
            string currentTime = rest.substr(0, spacePos1);
            string plate = rest.substr(spacePos1 + 1);
            output += to_string(parking->bill(currentTime, plate)) + "\n";
        } else if (command == "billall") {
            output += to_string(parking->billAll()) + "\n";
        }
    }
    // In ra toàn bộ kết quả sau khi nhận được ***
    cout << output;
    delete parking;
    getch();
    return 0;
}
