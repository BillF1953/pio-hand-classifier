#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-container-size-empty"
//
// Created by tylerf on 6/21/19.
//

#include "catch.hpp"
#include "../src/HandClassifier.h"


using namespace std;



TEST_CASE("Quads", "[BoardType]") {


    vector<vector<string>> t = {{"Ks", "Kh", "Kd", "Kc"},
                                {"Ks", "Kh", "Kd", "Kh", "Qc"},
                                {"As", "Ks", "Kc", "Kh", "Kd"}};
    for (auto i : t) {
        CHECK(HandClassifier().getBoardType(i) == "Quads");
    }


}

TEST_CASE("Three-of-a-Kind", "[BoardType]") {


    vector<vector<string>> t = {{"As", "Kh", "Kd", "Kc"},
                                {"Ks", "Kh", "Kd", "Qh"},
                                {"As", "Ks", "Kc", "Kh", "Qd"},
                                {"As", "Ks", "Qc", "Qh", "Qd"},
                                {"As", "Ad", "Ac", "Kh", "Qh"},
                                {"As", "Kd", "Kc", "Kh", "Qh"}
    };
    for (auto i : t) {
        CHECK(HandClassifier().getBoardType(i) == "Three-of-a-Kind");
    }


}

TEST_CASE("Paired", "[BoardType]") {


    vector<vector<string>> t = {{"As", "Kh", "Kd", "Qc"},
                                {"Ks", "Kh", "Qd", "Jh"},
                                {"As", "Kh", "Qd", "Qh"},
                                {"As", "Ks", "Kc", "Qh", "Jd"},
                                {"As", "Ks", "Qc", "Qh", "Jd"},
                                {"As", "Ad", "Kc", "Qh", "Jh"},
                                {"As", "Kd", "Qc", "Jd", "Jh"}
    };
    for (auto i : t) {
        CHECK(HandClassifier().getBoardType(i) == "Paired");
    }


}


TEST_CASE("Full-House", "[BoardType]") {


    vector<vector<string>> t = {{"As", "Ad", "Kc", "Kh", "Kd"},
                                {"Ks", "Kd", "Qc", "Qh", "Qd"}};
    for (auto i : t) {
        CHECK(HandClassifier().getBoardType(i) == "Full-House");
    }


}


TEST_CASE("Double-Paired", "[BoardType]") {


    vector<vector<string>> t = {{"Ks", "Kh", "Qd", "Qh"},
                                {"As", "Ks", "Kc", "Qh", "Qd"},
                                {"As", "Ac", "Qc", "Qh", "Jd"},
                                {"As", "Ad", "Kc", "Jd", "Jh"}};
    for (auto i : t) {


        CHECK(HandClassifier().getBoardType(i) == "Double-Paired");
    }


}

TEST_CASE("Unpaired", "[BoardType]") {


    vector<vector<string>> t = {{"As", "Kh", "Qd", "Jh"},
                                {"As", "Ks", "Qc", "7h", "5d"}};
    for (auto i : t) {
        CHECK(HandClassifier().getBoardType(i) == "Unpaired");
    }


}


TEST_CASE("HandType", "[HandType]") {

    vector<vector<string>> t = {{"As", "Ah"},
                                {"As", "Ks"}};
    CHECK(HandClassifier().getHandType(t[0]) == "Paired");
    CHECK(HandClassifier().getHandType(t[1]) == "Unpaired");


}

TEST_CASE("PocketPairsUnPairedBoards", "[HandRank]") {

    vector<vector<string>> b = {{"Ks", "Jh", "9h", "7h", "5h"}, {"Ks", "Jh", "9h", "7h"}, {"Ks", "Jh", "9h"}};
    vector<vector<string>> h = {{"Kd", "Kh"},
                                {"Js", "Jc"},
                                {"7s", "7c"},
                                {"Ad", "Ah"},
                                {"Qs", "Qc"},
                                {"Ts", "Tc"},
                                {"8d", "8h"},
                                {"6s", "6c"},
                                {"4s", "4c"}};


    CHECK(HandClassifier().getUnpairedPr(b[0], h[0]) == "Set");

    CHECK(HandClassifier().getUnpairedPr(b[0], h[1]) == "Set");

    CHECK(HandClassifier().getUnpairedPr(b[0], h[2]) == "Set");

    CHECK(HandClassifier().getUnpairedPr(b[0], h[3]) == "Overpair");

    CHECK(HandClassifier().getUnpairedPr(b[0], h[4]) == "PPuTP");

    CHECK(HandClassifier().getUnpairedPr(b[0], h[5]) == "PPu2ndPr");

    CHECK(HandClassifier().getUnpairedPr(b[0], h[6]) == "PPu3rdPr");

    CHECK(HandClassifier().getUnpairedPr(b[0], h[7]) == "PPu4thPr");

    CHECK(HandClassifier().getUnpairedPr(b[0], h[8]) == "PPu5thPr");



    CHECK(HandClassifier().getUnpairedPr(b[1], h[0]) == "Set");

    CHECK(HandClassifier().getUnpairedPr(b[1], h[1]) == "Set");

    CHECK(HandClassifier().getUnpairedPr(b[1], h[2]) == "Set");

    CHECK(HandClassifier().getUnpairedPr(b[1], h[3]) == "Overpair");

    CHECK(HandClassifier().getUnpairedPr(b[1], h[4]) == "PPuTP");

    CHECK(HandClassifier().getUnpairedPr(b[1], h[5]) == "PPu2ndPr");

    CHECK(HandClassifier().getUnpairedPr(b[1], h[6]) == "PPu3rdPr");

    CHECK(HandClassifier().getUnpairedPr(b[1], h[7]) == "PPu4thPr");

    CHECK(HandClassifier().getUnpairedPr(b[1], h[8]) == "PPu4thPr");


    CHECK(HandClassifier().getUnpairedPr(b[2], h[0]) == "Set");

    CHECK(HandClassifier().getUnpairedPr(b[2], h[1]) == "Set");

    CHECK(HandClassifier().getUnpairedPr(b[2], h[2]) == "PPu3rdPr");

    CHECK(HandClassifier().getUnpairedPr(b[2], h[3]) == "Overpair");

    CHECK(HandClassifier().getUnpairedPr(b[2], h[4]) == "PPuTP");

    CHECK(HandClassifier().getUnpairedPr(b[2], h[5]) == "PPu2ndPr");

    CHECK(HandClassifier().getUnpairedPr(b[2], h[6]) == "PPu3rdPr");

    CHECK(HandClassifier().getUnpairedPr(b[2], h[7]) == "PPu3rdPr");

    CHECK(HandClassifier().getUnpairedPr(b[2], h[8]) == "PPu3rdPr");




}

TEST_CASE("UnpairedBoards", "[HandRank]") {

    vector<vector<string>> b = {{"Ks", "Jh", "9h", "7h", "5h"}};
    vector<vector<string>> h = {{"Kd", "Qh"},
                                {"As", "Jc"},
                                {"9s", "7c"},
                                {"Ad", "7h"},
                                {"5s", "4c"},
                                {"9s", "8c"},
                                {"Kd", "5s"},
                                {"Js", "5c"},
                                {"Ts", "9c"},
                                {"Ad", "4d"},
                                {"Qh", "4d"},
                                {"4h", "3d"}};

    CHECK(HandClassifier().getUnpaired(b[0], h[0]) == "Top-Pr");
    CHECK(HandClassifier().getUnpaired(b[0], h[1]) == "Second-Pr");
    CHECK(HandClassifier().getUnpaired(b[0], h[2]) == "Two-Pair");
    CHECK(HandClassifier().getUnpaired(b[0], h[3]) == "Fourth-Pr");
    CHECK(HandClassifier().getUnpaired(b[0], h[4]) == "Fifth-Pr");
    CHECK(HandClassifier().getUnpaired(b[0], h[5]) == "Third-Pr");
    CHECK(HandClassifier().getUnpaired(b[0], h[6]) == "Two-Pair");
    CHECK(HandClassifier().getUnpaired(b[0], h[7]) == "Two-Pair");
    CHECK(HandClassifier().getUnpaired(b[0], h[8]) == "Third-Pr");
    CHECK(HandClassifier().getUnpaired(b[0], h[9]) == "A-H");
    CHECK(HandClassifier().getUnpaired(b[0], h[10]) == "Q-H");
    CHECK(HandClassifier().getUnpaired(b[0], h[11]) == "Air");
}


TEST_CASE("5-Flush", "[FlushDraw]") {

    vector<vector<string>> b = {{"Ks", "Js", "9s", "7s", "5s"}};

    vector<vector<string>> h = {{"As", "8s"},
                                {"As", "Jc"},
                                {"7c", "4s"},
                                {"Tc", "8c"},
                                {"Td", "8d"},
                                {"Tc", "7h"}
    };


    CHECK(HandClassifier().flushDraw(b[0], h[0]) == "A-H 5Flush");
    CHECK(HandClassifier().flushDraw(b[0], h[1]) == "A-H 5Flush");
    CHECK(HandClassifier().flushDraw(b[0], h[2]) == "5Flush");
    CHECK(HandClassifier().flushDraw(b[0], h[3]) == "5Flush");


}


TEST_CASE("Four-Flush", "[FlushDraw]") {

    vector<vector<string>> b = {{"Ks", "Js", "9s", "7s", "5d"},
                                {"Ks", "Js", "9s", "7h", "5s"},
                                {"Ks", "Js", "9s", "7s"}};


    vector<vector<string>> h = {{"As", "8s"},
                                {"As", "Jc"},
                                {"7c", "4s"},
                                {"Tc", "8c"},
                                {"Td", "8d"},
                                {"Tc", "7h"}
    };
    for (auto i : b) {

        CHECK(HandClassifier().flushDraw(i, h[0]) == "A-H 4Flush");
        CHECK(HandClassifier().flushDraw(i, h[1]) == "A-H 4Flush");
        CHECK(HandClassifier().flushDraw(i, h[2]) == "4-H 4Flush");
        CHECK(HandClassifier().flushDraw(i, h[3]).empty());
    }


}


TEST_CASE("Three-Flush", "[FlushDraw]") {

    vector<vector<string>> b = {{"Ks", "Js", "9s", "7h", "5d"},
                                {"Ks", "Js", "9s", "7h"},
                                {"Ks", "Js", "9d", "7s", "5d"},
                                {"Ks", "Js", "9d", "7d", "5s"},
                                {"Ks", "Js", "9d", "7s"},
                                {"Ks", "Js", "9s"}};


    vector<vector<string>> h = {{"As", "8s"},
                                {"As", "Jc"},
                                {"7c", "4s"},
                                {"Tc", "8c"},
                                {"Td", "8d"},
                                {"Tc", "7h"}
    };

    for (auto i : b) {

        if (i.size() == 5) {

            CHECK(HandClassifier().flushDraw(i, h[0]) == "Flush");
            CHECK(HandClassifier().flushDraw(i, h[1]).empty());
            CHECK(HandClassifier().flushDraw(i, h[2]).empty());
            CHECK(HandClassifier().flushDraw(i, h[3]).empty());

        } else {

            CHECK(HandClassifier().flushDraw(i, h[0]) == "Flush");

            CHECK(HandClassifier().flushDraw(i, h[1]) == "A-H 1C-FD");

            CHECK(HandClassifier().flushDraw(i, h[2]) == "4-H 1C-FD");

            CHECK(HandClassifier().flushDraw(i, h[3]).empty());


        }

    }

}


TEST_CASE("Two-Flush", "[FlushDraw]") {

    vector<vector<string>> b = {{"Ks", "Js", "9d", "7h", "5d"},
                                {"Ks", "Js", "9d", "7h"},
                                {"Ks", "Js", "9d"}};


    vector<vector<string>> h = {{"As", "8s"},
                                {"As", "Jc"},
                                {"7c", "4s"},
                                {"Tc", "8c"},
                                {"Td", "8d"},
                                {"Tc", "7h"}
    };

    for (auto i : b) {

        if (i.size() == 5) {

            CHECK(HandClassifier().flushDraw(i, h[0])=="");
            CHECK(HandClassifier().flushDraw(i, h[1])=="");
            CHECK(HandClassifier().flushDraw(i, h[2])=="");
            CHECK(HandClassifier().flushDraw(i, h[3])=="");

        } else if (i.size() == 4) {

            CHECK(HandClassifier().flushDraw(i, h[0]) == "2C-FD");

            CHECK(HandClassifier().flushDraw(i, h[1])=="");

            CHECK(HandClassifier().flushDraw(i, h[2])=="");

            CHECK(HandClassifier().flushDraw(i, h[3])=="");
        } else {

            CHECK(HandClassifier().flushDraw(i, h[0]) == "2C-FD");

            CHECK(HandClassifier().flushDraw(i, h[1]) == "A-H 1C-BFD");

            CHECK(HandClassifier().flushDraw(i, h[2]) == "4-H 1C-BFD");

            CHECK(HandClassifier().flushDraw(i, h[3])=="");

            CHECK(HandClassifier().flushDraw(i, h[4]) == "BFD");

        }

    }

}


TEST_CASE("Two-FlushDraws", "[FlushDraw]") {

    vector<vector<string>> b = {{"Ks", "Js", "9d", "7d"},
                                {"Ks", "Js", "9d", "7d", "5c"},
                                {"Ks", "Js", "9d", "7d", "5d"},
                                {"Ks", "Js", "9d", "7c"}};


    vector<vector<string>> h = {{"As", "8s"},
                                {"As", "Jc"},
                                {"7c", "4s"},
                                {"Tc", "8c"},
                                {"Td", "8d"},
                                {"Tc", "7h"}
    };
    auto hc = HandClassifier();
    for (int i = 0; i < b.size(); i++) {

        switch(i){
        case 0:
            CHECK(HandClassifier().flushDraw(b[i], h[0]) == "2C-FD");

            CHECK(HandClassifier().flushDraw(b[i], h[1])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[2])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[3])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[4]) == "tFD");

            CHECK(HandClassifier().flushDraw(b[i], h[5])=="");
            break;

        case 1:
            CHECK(HandClassifier().flushDraw(b[i], h[0])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[1])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[2])=="");
            CHECK(HandClassifier().flushDraw(b[i], h[3])=="");
            CHECK(HandClassifier().flushDraw(b[i], h[4])=="");

        CHECK(HandClassifier().flushDraw(b[i], h[5])=="");
        break;
        case 2:

            CHECK(HandClassifier().flushDraw(b[i], h[0])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[1])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[2])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[3])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[4]) == "riveredBFD");

            CHECK(HandClassifier().flushDraw(b[i], h[5])=="");
            break;
        case 3:
            CHECK(HandClassifier().flushDraw(b[i], h[0]) == "2C-FD");

            CHECK(HandClassifier().flushDraw(b[i], h[1])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[2])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[3])=="");

            CHECK(HandClassifier().flushDraw(b[i], h[4]) == "");

            CHECK(HandClassifier().flushDraw(b[i], h[5])=="");
            break;
        default: break;
        }


    }

}


TEST_CASE("Rainbow", "[FlushDraw]") {

    vector<vector<string>> b = {{"Ks", "Jd", "9c"},
                                {"Ks", "Jd", "9c", "7h"},
                                {"Ks", "Jd", "9c", "7h", "5h"}};


    vector<vector<string>> h = {{"As", "8s"},
                                {"As", "Jc"},
                                {"7c", "4s"},
                                {"Tc", "8c"},
                                {"Td", "8d"},
                                {"Tc", "7h"}
    };
    auto hc = HandClassifier();
    for (auto i : b) {

        if (i.size() == 3) {

            CHECK(HandClassifier().flushDraw(i, h[0]) == "BFD");

            CHECK(HandClassifier().flushDraw(i, h[1]).empty());

            CHECK(HandClassifier().flushDraw(i, h[2]).empty());

            CHECK(HandClassifier().flushDraw(i, h[3]) == "BFD");
            CHECK(HandClassifier().flushDraw(i, h[4]) == "BFD");
            CHECK(HandClassifier().flushDraw(i, h[5]).empty());


        } else {
            CHECK(HandClassifier().flushDraw(i, h[0]).empty());
            CHECK(HandClassifier().flushDraw(i, h[1]).empty());
            CHECK(HandClassifier().flushDraw(i, h[2]).empty());
            CHECK(HandClassifier().flushDraw(i, h[3]).empty());
            CHECK(HandClassifier().flushDraw(i, h[4]).empty());
            CHECK(HandClassifier().flushDraw(i, h[5]).empty());


        }


    }

}


TEST_CASE("BackdoorFlush", "[FlushDraw]") {

    vector<vector<string>> b = {{"Ks", "Jd", "9c", "7s"},
                                {"Ks", "Jd", "9c", "7h", "5s"},
                                {"Ks", "Jd", "9c", "7s", "5s"},
                                {"Ks", "Jd", "9c", "7d"},
                                {"Ks", "Jd", "9c", "7d", "5s"},
                                {"Ks", "Jd", "9c", "7d", "5d"},
                                {"Ks", "Jd", "9c", "7c"},
                                {"Ks", "Jd", "9c", "7c", "5s"},
                                {"Ks", "Jd", "9c", "7c", "5c"}
    };


    vector<vector<string>> h = {{"As", "8s"},
                                {"As", "Jc"},
                                {"7c", "4s"},
                                {"Tc", "8c"},
                                {"Td", "8d"},
                                {"Tc", "7h"}
    };


    CHECK(HandClassifier().flushDraw(b[0], h[0]) == "tFD");
    CHECK(HandClassifier().flushDraw(b[0], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[0], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[0], h[3]).empty());
    CHECK(HandClassifier().flushDraw(b[0], h[4]).empty());
    CHECK(HandClassifier().flushDraw(b[0], h[5]).empty());

    CHECK(HandClassifier().flushDraw(b[1], h[0]).empty());
    CHECK(HandClassifier().flushDraw(b[1], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[1], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[1], h[3]).empty());
    CHECK(HandClassifier().flushDraw(b[1], h[4]).empty());
    CHECK(HandClassifier().flushDraw(b[1], h[5]).empty());


    CHECK(HandClassifier().flushDraw(b[2], h[0]) == "riveredBFD");
    CHECK(HandClassifier().flushDraw(b[2], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[2], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[2], h[3]).empty());
    CHECK(HandClassifier().flushDraw(b[2], h[4]).empty());
    CHECK(HandClassifier().flushDraw(b[2], h[5]).empty());


    CHECK(HandClassifier().flushDraw(b[3], h[0]).empty());
    CHECK(HandClassifier().flushDraw(b[3], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[3], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[3], h[3]).empty());
    CHECK(HandClassifier().flushDraw(b[3], h[4]) == "tFD");
    CHECK(HandClassifier().flushDraw(b[3], h[5]).empty());


    CHECK(HandClassifier().flushDraw(b[4], h[0]).empty());
    CHECK(HandClassifier().flushDraw(b[4], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[4], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[4], h[3]).empty());
    CHECK(HandClassifier().flushDraw(b[4], h[4]).empty());
    CHECK(HandClassifier().flushDraw(b[4], h[5]).empty());


    CHECK(HandClassifier().flushDraw(b[5], h[0]).empty());
    CHECK(HandClassifier().flushDraw(b[5], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[5], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[5], h[3]).empty());
    CHECK(HandClassifier().flushDraw(b[5], h[4]) == "riveredBFD");
    CHECK(HandClassifier().flushDraw(b[5], h[5]).empty());


    CHECK(HandClassifier().flushDraw(b[6], h[0]).empty());
    CHECK(HandClassifier().flushDraw(b[6], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[6], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[6], h[3]) == "tFD");
    CHECK(HandClassifier().flushDraw(b[6], h[4]).empty());
    CHECK(HandClassifier().flushDraw(b[6], h[5]).empty());

    CHECK(HandClassifier().flushDraw(b[7], h[0]).empty());
    CHECK(HandClassifier().flushDraw(b[7], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[7], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[7], h[3]).empty());
    CHECK(HandClassifier().flushDraw(b[7], h[4]).empty());
    CHECK(HandClassifier().flushDraw(b[7], h[5]).empty());

    CHECK(HandClassifier().flushDraw(b[8], h[0]).empty());
    CHECK(HandClassifier().flushDraw(b[8], h[1]).empty());
    CHECK(HandClassifier().flushDraw(b[8], h[2]).empty());
    CHECK(HandClassifier().flushDraw(b[8], h[3]) == "riveredBFD");
    CHECK(HandClassifier().flushDraw(b[8], h[4]).empty());
    CHECK(HandClassifier().flushDraw(b[8], h[5]).empty());

}


TEST_CASE("2C-Straights", "[StraightDraw]") {
    //
    vector<vector<string>> b = {{"Ks", "Js", "9s", "7h", "5d"},
                                {"Ks", "Js", "9s", "7h"},
                                {"Ks", "Js", "9s"}};

    vector<vector<string>> h = {{"Qs", "Ts"},
                                {"Ts", "8c"},
                                {"6s", "4c"},
                                {"As", "Qs"},
                                {"8s", "6s"},
                                {"As", "Ts"},
                                {"Ts", "3s"},
                                {"Ts", "7s"},
                                {"9c","9d"}};


    for (auto i : b) {
        if (i.size() == 5) {

            CHECK(HandClassifier().getStrghtDraw(i, h[0]) == "2C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[1]) == "2C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[2]) == "");
            CHECK(HandClassifier().getStrghtDraw(i, h[3]) == "");
            CHECK(HandClassifier().getStrghtDraw(i, h[4]) == "2C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[5]) == "");
            CHECK(HandClassifier().getStrghtDraw(i, h[6]) == "");
            CHECK(HandClassifier().getStrghtDraw(i, h[7]) == "");
            CHECK(HandClassifier().getStrghtDraw(i, h[8]) == "");

        }
        if (i.size() == 4) {

            CHECK(HandClassifier().getStrghtDraw(i, h[0]) == "2C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[1]) == "2C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[2]) == "");
            CHECK(HandClassifier().getStrghtDraw(i, h[3]) == "2C GS");
            CHECK(HandClassifier().getStrghtDraw(i, h[4]) == "2C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[5]) == "2C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[6]) == "1C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[7]) == "1C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[8]) == "");


        }

        if (i.size() == 3) {

            CHECK(HandClassifier().getStrghtDraw(i, h[0]) == "2C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[1]) == "2C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[2]).empty());
            CHECK(HandClassifier().getStrghtDraw(i, h[3]) == "2C GS");
            CHECK(HandClassifier().getStrghtDraw(i, h[4]) == "");
            CHECK(HandClassifier().getStrghtDraw(i, h[5]) == "2C GS");
            CHECK(HandClassifier().getStrghtDraw(i, h[6]) == "1C GS");
            CHECK(HandClassifier().getStrghtDraw(i, h[7]) == "2C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[8]) == "");
        }

    }

}



TEST_CASE("2C-Straights-Round-Two", "[StraightDraw]") {
    //
    vector<vector<string>> b = {{"Qs", "9s", "7d"}, {"Jc","8d", "5s"}};

    vector<vector<string>> h = {{"Jh", "8h"}};



    CHECK(HandClassifier().getStrghtDraw(b[0], h[0]) == "2C GS");
    CHECK(HandClassifier().getStrghtDraw(b[1], h[0]) == "Two-Pair");


}

TEST_CASE("1C-Straights", "[StraightDraw]") {
    //
    vector<vector<string>> b = {{"Ks", "Qs", "Js", "Th", "9d"},
                                {"Qs", "Js", "Th", "9d"},
                                {"Js", "Ts", "9s"}};

    vector<vector<string>> h = {{"As", "Qs"},
                                {"8s", "6s"},
                                {"Ks", "Ts"},
                                {"Qs", "3s"},
                                {"Tc", "7s"},
                                {"6s", "4s"}};


    for (auto i : b) {
        if (i.size() == 5) {

            CHECK(HandClassifier().getStrghtDraw(i, h[0]) == "1C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[1]) == "5-Card Board Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[2]) == "5-Card Board Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[3]) == "5-Card Board Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[4]) == "5-Card Board Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[5]) == "5-Card Board Str.");


        }
        if (i.size() == 4) {

            CHECK(HandClassifier().getStrghtDraw(i, h[0]) == "1C GS");
            CHECK(HandClassifier().getStrghtDraw(i, h[1]) == "1C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[2]) == "1C Str.");
            CHECK(HandClassifier().getStrghtDraw(i, h[4]) == "");
            CHECK(HandClassifier().getStrghtDraw(i, h[5]) == "");
        }

        if (i.size() == 3) {

            CHECK(HandClassifier().getStrghtDraw(i, h[0]) == "2C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[1]) == "1C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[2]) == "1C GS");
            CHECK(HandClassifier().getStrghtDraw(i, h[3]) == "1C OE");
            CHECK(HandClassifier().getStrghtDraw(i, h[4]) == "1C GS");
        }

    }

}


TEST_CASE("Edge Cases", "[StraightDraw]") {
    //
    vector<vector<string>> b = {{"As", "7s", "3s"},
                                {"Js", "Ts", "9s"}};

    vector<vector<string>> h = {{"5s", "4s"},
                                {"Ks", "7s"},
                                {"Ks", "8s"},
                                {"Qs", "3s"},
                                {"Tc", "7s"},
                                {"6s", "4s"}};

    CHECK(HandClassifier().getStrghtDraw(b[0], h[0]) == "2C OE");
    CHECK(HandClassifier().getStrghtDraw(b[1], h[1]) == "2C OE");
    CHECK(HandClassifier().getStrghtDraw(b[1], h[2]) == "2C OE");

}


#pragma clang diagnostic pop