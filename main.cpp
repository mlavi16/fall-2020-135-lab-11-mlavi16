#include <iostream>
#include "profile.h"
#include "network.h"

int main() {
    // Profile p1("marco", "Marco");    
    // std::cout << p1.getUsername() << std::endl; // marco
    // std::cout << p1.getFullName() << std::endl; // Marco (@marco)

    // p1.setDisplayName("Marco Rossi"); 
    // std::cout << p1.getUsername() << std::endl; // marco
    // std::cout << p1.getFullName() << std::endl; // Marco Rossi (@marco)
    
    // Profile p2("tarma1", "Tarma Roving");    
    // std::cout << p2.getUsername() << std::endl; // tarma1
    // std::cout << p2.getFullName() << std::endl; // Tarma Roving (@tarma1)


    Network nw;
    std::cout << nw.addUser("mario", "Mario") << std::endl;     // true (1)
    std::cout << nw.addUser("luigi", "Luigi") << std::endl;     // true (1)

    std::cout << nw.addUser("mario", "Mario2") << std::endl;    // false (0)
    std::cout << nw.addUser("mario 2", "Mario2") << std::endl;  // false (0)
    std::cout << nw.addUser("mario-2", "Mario2") << std::endl;  // false (0)

    for(int i = 2; i < 20; i++) {
        std::cout << nw.addUser("mario" + std::to_string(i), "Mario" + std::to_string(i)) << std::endl;   // true (1)
    }

    std::cout << nw.addUser("yoshi", "Yoshi") << std::endl;     // false (0)
    
    return 0;
}