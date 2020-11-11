#pragma once
#include <iostream>
#include "profile.h"

class Network {
private:
    static const int MAX_USERS = 20;
    int numUsers;
    Profile profiles[MAX_USERS];
    bool following[MAX_USERS][MAX_USERS]; 
    int findID (std::string usrn);
public:
    Network();
    bool addUser(std::string usrn, std::string dspn);
    bool follow(std::string usrn1, std::string usrn2);
    void printDot();
};

std::string usrnFormat(std::string usrn);