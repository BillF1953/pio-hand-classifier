//
// Created by tylerf on 6/21/19.
//

#ifndef HANDCLASSIFIER_SRC_HANDCLASSIFIER_H
#define HANDCLASSIFIER_SRC_HANDCLASSIFIER_H

#include <string>
#include <algorithm>
#include <map>
#include <unistd.h>
#include <iostream>
#include<iterator>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <set>


class HandClassifier {
private:


    std::string handStrength_;
    std::string drawType;
    std::string drawFlush;
    std::string strghtDraw;
    std::string draw_;
    enum BT {Quads, ThreeofaKind, Paired, FullHouse,  DoublePaired, Unpaired} boardType_;
    enum HT {PocketPair, NotPocketPair} handType_;
    //    std::vector<std::string> board;
    //    std::vector<std::string> hand;


    bool suited(std::vector<std::string> &hand);

    std::string getDrawType(void);

    void getSpadeDraw(std::vector<std::string> &hand, std::vector<std::string> &board);

    void checksingle(std::vector<std::string> &board, std::string &card);

    void getBFDraw(char suit);


    bool checkIfRainbow(std::vector<std::string> &board);

    void mk_flshstr(const char card, const std::string &flsh_type);

    void getStrIdx(std::vector<std::string> &board, std::vector<int> &stridx);


    void checkStraight(std::vector<int> &stridx, std::vector<std::string> &hand, int i);

    void checkGutshot(std::vector<int> &stridx, std::vector<std::string> &hand, int i, std::string &strghttype);

    void checkOpenEnded(std::vector<int> &stridx, std::vector<std::string> &hand, int i, int length);

    void getPossibleStraightDraws(std::vector<int> &stridx, std::vector<std::string> &board, std::vector<std::string> &hand);


    void getClassification();

    int getNumBoardCardsUsed(std::vector<int> &stridx, std::vector<std::string> &board, int start, int length);

    void printBoard(std::vector<std::string> &board);


public:

    HandClassifier();
    HandClassifier(std::basic_string<char>, std::basic_string<char>);
    void printSpot(std::vector<std::string>& board, std::vector<std::string>& hand);
    void get_cards(const std::string& strCard, std::vector<std::string>& cards);
    std::string getBoardType(std::vector<std::string> &board);


    std::string getDraw(std::vector<std::string>& board, std::vector<std::string>& hand);

    void get_holecards(std::string &hand, std::vector<std::string> &holeCards);

    std::string getHandType(std::vector<std::string> &hand);

    std::string getUnpairedPr(std::vector<std::string> &board, std::vector<std::string> &hand);

    std::string getUnpaired(std::vector<std::string> &board, std::vector<std::string> &hand);

    void helperGetPair(const std::vector<std::string> &board, const std::vector<std::string> &hand, int i, int k);

    void gethighCard(std::vector<std::string> &board, std::vector<std::string> &hand);

    void getPair(std::vector<std::string> &board, std::vector<std::string> &hand);

    std::string getFlushDraw(std::vector<std::string> &board);

    std::string flushDraw(std::vector<std::string> &board, std::vector<std::string> &hand);

    std::string getStrghtDraw(std::vector<std::string> &board, std::vector<std::string> &hand);

    std::string handStrength() const{
        if(handStrength_.empty()){return "NA";}
        else{return handStrength_;}
    }
    std::string draw() const{
        if(draw_.empty()) return "NA";
        else{return draw_;}

    }



    void getHandCategory(std::vector<std::string> &board, std::vector<std::string> &hand);


    std::string getBoardAsString() const;

    std::string getHandTypeAsString() const;
};


#endif //HANDCLASSIFIER_SRC_HANDCLASSIFIER_H
