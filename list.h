#ifndef LIST_H
#define LIST_H

#include <string>
#include "vehicle.h"

using namespace std;

struct Node {
    Vehicle* vehicle;
    Node* next;

    Node(){
        vehicle = nullptr;
        next = nullptr;
    }
    Node(Vehicle* v) {
        vehicle = v;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;
    double allbill;

public:
    LinkedList() {
        head = nullptr;
        allbill = 0.0;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp->vehicle; // Xóa vehicle thủ công
            delete temp;
        }
    }

    void append(Vehicle* vehicle) {
        Node* newNode = new Node(vehicle);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    int find(const string& plate) {
        Node* temp = head;
        int index = 0;
        while (temp) {
            if (temp->vehicle->getPlate() == plate) {
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }

    Vehicle* remove(const string& plate) {
        Node* temp = head;
        Node* prev = nullptr;
        while (temp != nullptr && temp->vehicle->getPlate() != plate) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr) { // Tìm thấy vehicle
            if (prev != nullptr) { // Không phải node đầu tiên
                prev->next = temp->next;
            } else { // Node đầu tiên
                head = temp->next;
            }
            Vehicle* vehicle = temp->vehicle;
            temp->vehicle = nullptr; // Ngăn Node destructor xóa vehicle
            delete temp;
            return vehicle;
        }
        return nullptr;
    }

    void listPlates(string& output) {
        Node* temp = head;
        while (temp) {
            output += temp->vehicle->getPlate() + "\n";
            temp = temp->next;
        }
    }

    int cnt_moto() {
        int count = 0;
        Node* temp = head;
        while (temp) {
            if (temp->vehicle->isMotorbike()) {
                count++;
            }
            temp = temp->next;
        }
        return count;
    }

    double bill(const string& currentTime, const string& plate) {
        Node* temp = head;
        while (temp) {
            if (temp->vehicle->getPlate() == plate) {
                return temp->vehicle->calculatePrice(currentTime);
            }
            temp = temp->next;
        }
        return -1;
    }

    double billAll() const {
        return allbill;
    }

    int in(const string& intime, Vehicle* vehicle) {
        if (find(vehicle->getPlate()) != -1) {
            return 0; // Vehicle đã có trong bãi
        }
        append(vehicle);
        return 1; // Thành công
    }

    int out(const string& outtime, const string& plate) {
        Vehicle* vehicle = remove(plate);
        if (vehicle) {
            allbill += vehicle->calculatePrice(outtime);
            delete vehicle;
            return 1; // Thành công
        }
        return 0; // Không tìm thấy vehicle trong bãi
    }
};

#endif
