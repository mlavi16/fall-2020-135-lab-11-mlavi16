#include "network.h"
#include "profile.h"
#include <cctype>
#include <string>

Network::Network() {
    // Constructor, makes an empty network (numUsers = 0)
    numUsers = 0;
}

bool Network::addUser(std::string usrn, std::string dspn) {
    // Attempts to sign up a new user with specified username and displayname
    // return true if the operation was successful, otherwise return false

    // the new username usrn must be a non-empty alphanumeric string,
    if (usrn.length() == 0){
        return false;
    } else {
        for (int i = 0; i < usrn.length(); i++) { 
            if (!isalnum(usrn[i])) {
                return false;
            }
        }
    }

    //the array profiles cannot be full.
    if (numUsers >= MAX_USERS) {
        return false;
    }

    //there cannot be other users in the network with the same username,
    for (int i = 0; i < numUsers; i++) {
        if (usrn == profiles[i].getUsername()) {
            return false;
        }
    }

    Profile p(usrn, dspn);
    profiles[numUsers] = p;
    numUsers += 1;
    return true;
}

int Network::findID (std::string usrn) {
    // Returns user ID (index in the 'profiles' array) by their username
    // (or -1 if username is not found)

    for (int i = 0; i < numUsers; i++) {
        if (profiles[i].getUsername() == usrn) {
            return i;
        }
    }
    return -1;
}