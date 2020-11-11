#include "network.h"
#include "profile.h"
#include <cctype>
#include <string>

Network::Network() {
    // Constructor: 
    //   makes an empty network (numUsers = 0) 
    //   sets all elements of the matrix following to false, so no one is following anyone.
    //   sets number of posts to 0
    numUsers = 0;

    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < MAX_USERS; j++) {
            following[i][j] = false;
        }
    }

    numPosts = 0;
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

bool Network::follow(std::string usrn1, std::string usrn2) {
    // Make 'usrn1' follow 'usrn2' (if both usernames are in the network).
    // return true if success (if both usernames exist), otherwise return false
    int id1 = findID(usrn1);
    int id2 = findID(usrn2);
    if (id1 != -1 && id2 != -1) {
        following[id1][id2] = true;
        return true;
    } else {
        return false;
    }
}

void Network::printDot() {
    // Print Dot file (graphical representation of the network)

    std::cout << "digraph {" << std::endl;

    for (int i = 0; i < numUsers; i++) {
        std::cout << "\t" << usrnFormat(profiles[i].getUsername()) << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0; i < numUsers; i++){
        for (int j = 0; j < numUsers; j++) {
            if (following[i][j] == true) {
                std::cout << "\t" << usrnFormat(profiles[i].getUsername()) << " -> " << usrnFormat(profiles[j].getUsername()) << std::endl;
            }
        }
    }

    std::cout << "}" << std::endl;
}

std::string usrnFormat(std::string usrn) {
    return "\"@" + usrn + "\"";
}

bool Network::writePost(std::string usrn, std::string msg) {
    // Adds a new post to the posts array. 
    // It performs successfully if the username is found in the network 
    // and the posts array is not full (returns true). 
    // Otherwise, nothing is added and the function returns false.

    if ((findID(usrn) != -1) && (numPosts < MAX_POSTS)) {
        Post post = {usrn, msg};
        posts[numPosts] = post;
        numPosts += 1;
        return true;
    } else {
        return false;
    }
}

bool Network::printTimeline(std::string usrn) {
    // Prints out the timeline of the user usrn. 
    // The timeline of a user is the list of all posts by the user and by the people they follow, 
    // presented in reverse-chronological order. 
    if (findID(usrn) == -1) {
        return false;
    }

    for (int i = (numPosts - 1); i >= 0; i--) {
        if ((posts[i].username == usrn) || (following[findID(usrn)][findID(posts[i].username)] == true)) {
            std::cout << profiles[findID(usrn)].getFullName() << ": " << posts[i].message << std::endl;
        }
    }

    return true;
}