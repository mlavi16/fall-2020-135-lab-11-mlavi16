#include <iostream>
#include "profile.h"

Profile::Profile(std::string usrn, std::string dspn) {
    // Profile constructor for a user (initializing private variables username=usrn, displayname=dspn)
    username = usrn;
    displayname = dspn;
}

Profile::Profile() {
    // Default Profile constructor (username="", displayname="")
    username = "";
    displayname = "";
}

std::string Profile::getUsername() {
    //returns the username
    return username;
}

std::string Profile::getFullName() {
    //returns the string in the format “displayname (@username)”.
    return displayname + " (@" + username + ")";
}

void Profile::setDisplayName(std::string dspn) {
    //allows to change the displayname property.
    displayname = dspn;
}