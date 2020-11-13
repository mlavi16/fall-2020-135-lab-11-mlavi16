#pragma once
#include <iostream>
#include "profile.h"
#include "post.h"

class Network {
private:
    static const int MAX_USERS = 20;
    int numUsers;
    Profile profiles[MAX_USERS]; 
    int findID (std::string usrn);

    bool following[MAX_USERS][MAX_USERS];

    static const int MAX_POSTS = 100;
    int numPosts;
    Post posts[MAX_POSTS]; 
public:
    Network();

    bool addUser(std::string usrn, std::string dspn);

    bool follow(std::string usrn1, std::string usrn2);
    void printDot();

    bool writePost(std::string usrn, std::string msg);
    bool printTimeline(std::string usrn);

    //functions for tests.cpp
    int testFindID(std::string usrn);
    Profile testNetwork(std::string usrn);
    bool testFollow(std::string usrn1, std::string usrn2);
    int testNumPosts();
    std::string returnTimeline(std::string usrn);
};

std::string usrnFormat(std::string usrn);