#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "profile.h"
#include "network.h"
#include "post.h"

TEST_CASE("profile- task A") {
    Profile p;
    CHECK(p.getUsername() == "");
    CHECK(p.getFullName() == " (@)");
    p.setDisplayName("Yoshi");
    CHECK(p.getFullName() == "Yoshi (@)");

    Profile p2("Maya", "maya lavi");
    CHECK(p2.getUsername() == "Maya");
    CHECK(p2.getFullName() == "maya lavi (@Maya)");
    p2.setDisplayName("11");
    CHECK(p2.getFullName() == "11 (@Maya)");

    Profile p3("", "");
    CHECK(p3.getUsername() == "");
    CHECK(p3.getFullName() == " (@)");
    p3.setDisplayName("");
    CHECK(p3.getFullName() == " (@)");

    Profile p4("11111", "HELLO!");
    CHECK(p4.getUsername() == "11111");
    CHECK(p4.getFullName() == "HELLO! (@11111)");
    p4.setDisplayName("HELLO!");
    CHECK(p4.getFullName() == "HELLO! (@11111)");
}

TEST_CASE("Network.addUser()- task B") {
    Network net;
    net.addUser("Maya2020", "maya 5:)!");
    CHECK(net.testFindID("Maya2020") == 0);
    CHECK(net.testFindID("maya2020") == -1);
    Profile p = net.testNetwork("Maya2020");
    CHECK(p.getFullName() == "maya 5:)! (@Maya2020)");

    net.addUser("coolio", "coolio");
    CHECK(net.testFindID("coolio") == 1);
    p = net.testNetwork("coolio");
    CHECK(p.getFullName() == "coolio (@coolio)");

    net.addUser("Maya2020", "maya"); // repeat usernames should not be added
    CHECK(net.testFindID("Maya2020") != 2); 
    p = net.testNetwork("Maya2020");
    CHECK(p.getFullName() == "maya 5:)! (@Maya2020)");

    //usernames should be non-empty alphanumeric strings
    net.addUser("sherlock holmes", "Lock123");
    net.addUser("hey!", "hey!");
    net.addUser("", "hi");
    CHECK(net.testFindID("sherlock") == -1);
    CHECK(net.testFindID("hey!") == -1);
    CHECK(net.testFindID("") == -1);

    for (int i = 2; i < 20; i++) {
        net.addUser("name" + std::to_string(i), "wow" + std::to_string(i));
    }
    CHECK(net.testFindID("name4") == 4);
    CHECK(net.testFindID("name19") == 19);
    CHECK(net.testFindID("name 19") == -1);
    CHECK(net.testFindID("name20") == -1);

    // network is full, more usernames should not be added
    net.addUser("Steve", "steve00");
    CHECK(net.testFindID("Steve") == -1);
}

TEST_CASE("Network.follow()- task C") {
    Network n;
    n.addUser("bob", "bobby1");
    n.addUser("mario", "marmar");
    n.addUser("paul", "paulie!!");
    n.addUser("ted", "talks");

    CHECK(n.follow("bob", "ted") == true);
    CHECK(n.follow("ted", "paul") == true);
    CHECK(n.follow("paul", "ted") == true);
    CHECK(n.follow("paul", "mario") == true);

    CHECK(n.follow("bob", "marmar") == false);
    CHECK(n.follow("", "") == false);
    CHECK(n.follow("bob", "ted") == true);
    CHECK(n.follow("maya", "bob") == false);
    CHECK(n.follow("bob", "maya") == false);


    CHECK(n.testFollow("bob", "ted") == true);
    CHECK(n.testFollow("bob", "mario") == false);
    CHECK(n.testFollow("bob", "paul") == false);
\
    CHECK(n.testFollow("ted", "paul") == true);
    CHECK(n.testFollow("ted", "mario") == false);
    CHECK(n.testFollow("ted", "bob") == false);

    CHECK(n.testFollow("paul", "ted") == true);
    CHECK(n.testFollow("paul", "mario") == true);
    CHECK(n.testFollow("paul", "bob") == false);
\
    CHECK(n.testFollow("mario", "paul") == false);
    CHECK(n.testFollow("mario", "bob") == false);
    CHECK(n.testFollow("mario", "ted") == false);

    CHECK(n.testFollow("bob", "bob") == false);
    CHECK(n.testFollow("Mario", "Bob") == false);
    CHECK(n.testFollow("bob", "marmar") == false);
    CHECK(n.testFollow("bobby1", "mario") == false);
    CHECK(n.testFollow("", "") == false);
    CHECK(n.testFollow("mario", "maya") == false);
    CHECK(n.testFollow("maya", "ted") == false);
}

TEST_CASE("posts- task D") {
    Network n;
    n.addUser("Maya", "mayay");
    n.addUser("Tim", "tom");
    n.addUser("Lucy", "lucky");
    n.addUser("natalie", "nat");
    n.addUser("Tal", "tal10");

    //maya
    n.follow("Maya", "Lucy");
    n.follow("Maya", "Tim");
    n.follow("Maya", "Tal");
    //lucy
    n.follow("Lucy", "Maya");
    n.follow("Lucy", "natalie");
    n.follow("Lucy", "Tim");
    n.follow("Lucy", "Tal");
    //natalie
    n.follow("natalie", "Lucy");
    //tim
    n.follow("Tim", "Lucy");

    CHECK(n.writePost("Maya", "hey y'all") == true);
    CHECK(n.writePost("Tim", "what is up???") == true);
    CHECK(n.writePost("natalie", "hiyo") == true);
    CHECK(n.writePost("Maya", "balloons") == true);
    CHECK(n.writePost("Tal", "explosions") == true);
    CHECK(n.writePost("Lucy", "bingo") == true);
    CHECK(n.writePost("natalie", "partayy") == true);
    CHECK(n.writePost("Tim", "Go Wildcats") == true);
    CHECK(n.writePost("Lucy", "yay!!") == true);
    CHECK(n.writePost("natalie", "") == true);

    CHECK(n.writePost("ted", "hello") == false);
    CHECK(n.writePost("", "yippie") == false);

    CHECK(n.testNumPosts() == 10);
    std::string maya = "lucky (@Lucy): yay!!\ntom (@Tim): Go Wildcats\nlucky (@Lucy): bingo\ntal10 (@Tal): explosions\nmayay (@Maya): balloons\ntom (@Tim): what is up???\nmayay (@Maya): hey y'all\n";
    CHECK(n.returnTimeline("Maya") == maya);
    std::string lucy = "nat (@natalie): \nlucky (@Lucy): yay!!\ntom (@Tim): Go Wildcats\nnat (@natalie): partayy\nlucky (@Lucy): bingo\ntal10 (@Tal): explosions\nmayay (@Maya): balloons\nnat (@natalie): hiyo\ntom (@Tim): what is up???\nmayay (@Maya): hey y'all\n";
    CHECK(n.returnTimeline("Lucy") == lucy); //should return every post bc lucy follows everyone
    std::string tim = "lucky (@Lucy): yay!!\ntom (@Tim): Go Wildcats\nlucky (@Lucy): bingo\ntom (@Tim): what is up???\n";
    CHECK(n.returnTimeline("Tim") == tim);
    std::string natalie = "nat (@natalie): \nlucky (@Lucy): yay!!\nnat (@natalie): partayy\nlucky (@Lucy): bingo\nnat (@natalie): hiyo\n";
    CHECK(n.returnTimeline("natalie") == natalie);
    std::string tal = "tal10 (@Tal): explosions\n";
    CHECK(n.returnTimeline("Tal") == tal);

    CHECK(n.returnTimeline("ted") == "");

    //cannot exceed 100 messages in a network
    n.addUser("p", "p");
    for (int i = 10; i < 100; i++) {
        n.writePost("p", "msg" + std::to_string(i));
    }
    CHECK(n.testNumPosts() == 100);
    CHECK(n.writePost("p", "no more messages :(") == false);

}