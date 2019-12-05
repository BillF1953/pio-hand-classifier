//
// Created by tylerf on 6/21/19.
//

#include "HandClassifier.h"



//TODO Add Logging and Exception Handling


struct order_holecards{

    int order(char a) {
        if(a == 'A') {a = 'Z';}
        if(a == 'K') {a = 'Y';}
        if(a == 'Q') {a = 'X';}
        if(a == 'J') {a = 'W';}

        return (int) a;
    }

    bool operator()(std::string a, std::string b) {
        if(a[0] == b[0]){
            return a > b;
        }
        return order(a[0]) > order(b[0]);
    }
};


void HandClassifier::printSpot(std::vector<std::string>& board, std::vector<std::string>& hand) {
    std::cout << "Board is ";
    for(auto b : board){

        std::cout << b << " ";
    }
    std::cout << "\nHand is ";

    for(auto h: hand){

        std::cout <<  h << " ";

    }
    std::cout << std::endl;

}

void HandClassifier::get_cards(const std::string& strCard, std::vector<std::string>& cards) {


    std::istringstream iss(strCard);
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(), back_inserter(cards));


}

/**
 * Assumes sorted board from high to low
 * @param board
 * @return
 */
std::string HandClassifier::getBoardType(std::vector<std::string> &board) {

    int currentPairCount = 0;

    int PairCount = 0;


    for(int i = 1; i < board.size(); i++){

        if(board[i-1][0] == board[i][0]){
            currentPairCount++;

        }

        else{

            if(PairCount == 1 && currentPairCount == 1 ){
                         PairCount = 4;

            }
            if(PairCount == 0){

                PairCount = currentPairCount;

            }

            currentPairCount = 0;


        }




    }
    if(!PairCount){
        PairCount = currentPairCount;
    }
    else if(currentPairCount){
       if(PairCount == 1 && currentPairCount == 1){
           PairCount = 4;
       }
       else{
           PairCount = 5;
       }

    }



    if(PairCount == 5) boardType_ = FullHouse;
    if(PairCount == 4) boardType_ = DoublePaired;
    if(PairCount == 3) boardType_ = Quads;
    if(PairCount == 2) boardType_ = ThreeofaKind;
    if(PairCount == 1) boardType_ = Paired;
    if(PairCount == 0) boardType_ = Unpaired;


    return getBoardAsString();

}

std::string HandClassifier::getBoardAsString() const {
    switch (boardType_) {


        case Quads:
            return "Quads";

        case ThreeofaKind:
            return "Three-of-a-Kind";

        case Paired:
            return "Paired";

        case FullHouse:
            return "Full-House";

        case DoublePaired:
            return "Double-Paired";

        case Unpaired:
            return "Unpaired";

    }
}


void HandClassifier::get_holecards(std::string& hand, std::vector<std::string>& holeCards) {

    holeCards.push_back(hand.substr(0,2));
    holeCards.push_back(hand.substr(2,4));




}

HandClassifier::HandClassifier() = default;

std::string HandClassifier::getHandType(std::vector<std::string> &hand) {

    if(hand[0][0] == hand[1][0]) handType_= PocketPair;
    else handType_ = NotPocketPair;

    return getHandTypeAsString();


}

std::string HandClassifier::getHandTypeAsString() const {
    switch (handType_) {
        case PocketPair:
            return "Paired";
        case NotPocketPair:
            return "Unpaired";
    }
}

std::string HandClassifier::getUnpairedPr(std::vector<std::string> &board, std::vector<std::string> &hand) {

    for(int i = 0; i < board.size(); i++){

        if(hand[0][0] == board[i][0]){
            handStrength_ = "Set";
            break;
        }

        if (order_holecards()(hand[0], board[i]) && handStrength_.empty()){
            if(i == 0){
                handStrength_ = "Overpair";
            }
            else if(i == 1){
                handStrength_ = "PPuTP";
            }
            else if(i == 2){
                handStrength_ = "PPu2ndPr";
            }
            else if(i == 3){

                handStrength_ = "PPu3rdPr";

            }
            else if(i == 4){

                handStrength_ = "PPu4thPr";
            }

        }
    }

    if(handStrength_.empty()){

        switch(board.size()) {
            case 3:
                handStrength_ = "PPu3rdPr";
                break;
            case 4:
                handStrength_ = "PPu4thPr";
                break;
            case 5:
                handStrength_ = "PPu5thPr";
                break;
            default: break;
        }

    }


    return(handStrength_);

}
std::string HandClassifier::getUnpaired(std::vector<std::string> &board, std::vector<std::string> &hand) {

    getPair(board, hand);

    if(handStrength_.empty()){
      gethighCard(board, hand);

    }
    return handStrength_;

}

void HandClassifier::getPair(std::vector<std::string> &board, std::vector<std::string> &hand) {


    for(int i = 0; i < board.size(); i++){


        helperGetPair(board, hand, i, 0);

        if(!handStrength_.empty()) break;

        helperGetPair(board, hand, i, 1);

        if(!handStrength_.empty()) break;


    }


}

void HandClassifier::helperGetPair(const std::vector<std::string> &board, const std::vector<std::string> &hand, int i, int k) {


    if (board[i][0] == hand[k][0]) {

        for (int j = i + 1; j < board.size(); j++) {

            if (board[j][0] == hand[abs(k-1)][0]) {

                handStrength_ = "Two-Pair";
                return;
            }

        }

        switch(i){

            case 0:  handStrength_ = "Top-Pr";
                break;
            case 1:  handStrength_ = "Second-Pr";
                break;
            case 2:  handStrength_ = "Third-Pr";
                break;
            case 3:   handStrength_ = "Fourth-Pr";
                break;
            case 4:   handStrength_ = "Fifth-Pr";
                break;
            default:
                std::cout << "HelperGetPair(): Unexpected Output\n";
                printSpot(const_cast<std::vector<std::string> &>(board), const_cast<std::vector<std::string> &>(hand));


        }
    }




}

void HandClassifier::getClassification(){

    if((drawFlush == "Flush" || drawFlush.find("4Flush") != std::string::npos || drawFlush.find("5Flush") != std::string::npos ||
    drawFlush == "Flush" || drawFlush == "riveredBFD") && (strghtDraw == "2C Str." || strghtDraw == "1C Str.")){
        handStrength_ = "Straight Flush";
    }

    else if (drawFlush.find("4Flush") != std::string::npos || drawFlush.find("5Flush") != std::string::npos ||
       drawFlush == "Flush" || drawFlush == "riveredBFD"){

        handStrength_ = drawFlush;
    }
    else if(strghtDraw == "2C Str." || strghtDraw == "1C Str." || strghtDraw == "5-Card Board Str."){
        handStrength_ = strghtDraw;

    }
    else if(drawFlush.empty() && strghtDraw.empty()){

        draw_.append("NoDraw");

    }
    else{
        draw_.append(strghtDraw);
        if(!strghtDraw.empty() && !drawFlush.empty()){
            draw_.append(" ");
        }
        draw_.append(drawFlush);
    }



}




void HandClassifier::gethighCard(std::vector<std::string> &board, std::vector<std::string> &hand) {

    if (hand[0][0] == 'A') handStrength_ = "A-H";
    else if (hand[0][0] == 'K') handStrength_ = "K-H";
    else if (hand[0][0] == 'Q') handStrength_ = "Q-H";
    else {
        handStrength_ = "Air";
    }


}

std::string HandClassifier::flushDraw(std::vector<std::string>&board, std::vector<std::string>& hand){

    getFlushDraw(board);
    getDraw(board, hand);

    return drawFlush;

}

std::string HandClassifier::getFlushDraw(std::vector<std::string> &board) {
    // TODO Cleanup names
    int spades = 0, diamonds=0, clubs=0;

    for(auto b : board){
        if(b[1]=='s') spades++;
        if(b[1] == 'd') diamonds++;
        if(b[1] == 'c') clubs++;
    }

    if(checkIfRainbow(board)){

        if(board.size() == 4){

            if (spades == 2) {
                drawType = "BackdoorFlushDrawS";
            }
            if(diamonds == 2){

                drawType = "BackdoorFlushDrawD";
            }
            if(clubs == 2){

                drawType = "BackdoorFlushDrawC";
            }

        }

        else if(spades == 3){
            drawType = "BackdoorFlushS";
        }
        else if(diamonds == 3){

            drawType = "BackdoorFlushD";

        }
        else if (clubs == 3){
            drawType = "BackdoorFlushC";
        }
        else if(board.size() == 3){
            drawType = "Rainbow";
        }
        else{
            drawType= "NoFlushDrawPossible";
        }

    }
    else{
        switch(spades){

            case 3: drawType = "Three-Flush";
            break;
            case 4: drawType = "Four-Flush";
            break;
            case 5: drawType = "Five-Flush";
            break;
            default:
                if(board.size() != 5)
                    drawType = diamonds == 2 ? "TwoFlushDraws" : "FlushDraw";
                else
                    if(diamonds==3)
                        drawType = "BackdoorFlushD";
            break;


        }



    }




    return drawType;


}

std::string HandClassifier::getDrawType(void){

    return drawType;
}




std::string HandClassifier::getDraw(std::vector<std::string> &board, std::vector<std::string> &hand) {
    if(drawType == "Five-Flush"){

        drawFlush = "5Flush";
    }

    if(suited(hand)) {

        if (hand[0][1] == 's') {
            getSpadeDraw(board, hand);

            if(checkIfRainbow(board)){
                getBFDraw('S');
            }

        }
        else if (hand[0][1] == 'c') {
            getBFDraw('C');

        }
        else if (hand[0][1] == 'd') {
            getBFDraw('D');

            if (drawType == "TwoFlushDraws")
                drawFlush = "tFD";
            if(board.size() == 3)
                drawFlush = "BFD";
        }
        else{

            // heart doesn't do anything
        }
    }
    else{

        checksingle(board, hand[0]);
        checksingle(board, hand[1]);


    }

     return drawFlush;
}



bool HandClassifier::suited(std::vector<std::string> &hand) {
    return hand[0][1] == hand[1][1];
}

void HandClassifier::getSpadeDraw( std::vector<std::string>& board, std::vector<std::string>& hand) {


    if(drawType == "Three-Flush"){
        drawFlush = "Flush";
    }

    if(drawType == "Four-Flush"){
        mk_flshstr(hand[0][0], "4Flush");

    }

    if(drawType== "Five-Flush" &&
        order_holecards()(hand[0], board[4])){
        mk_flshstr(hand[0][0], "5Flush");
    }

    if(drawType == "FlushDraw" || drawType == "TwoFlushDraws"){
        drawFlush = "2C-FD";
    }





}

void HandClassifier::mk_flshstr(const char card, const std::string &flsh_type){
    drawFlush.clear();
    drawFlush.push_back(card);
    drawFlush.append("-H ");
    drawFlush.append(flsh_type);

}


void HandClassifier::checksingle(std::vector<std::string> &board, std::string &card) {

    if(card[1] != 's') return;

    if(drawType == "Four-Flush"){
        mk_flshstr(card[0], "4Flush");
    }

    if(drawType== "Five-Flush"){

        if(order_holecards()(card, board[4])){
            mk_flshstr(card[0], "5Flush");
        }

    }

    if(drawType == "Three-Flush" && board.size()!= 5){
        mk_flshstr(card[0], "1C-FD");

    }
    if(drawType == "FlushDraw" && board.size() == 3){
        mk_flshstr(card[0], "1C-BFD");
    }


}

void HandClassifier::getBFDraw(char suit) {
    if(drawType=="Rainbow"){
        drawFlush = "BFD";
    }

    if(drawType.back() == suit){
        char temp = drawType.back();
        drawType.pop_back();

        if(drawType == "BackdoorFlushDraw"){
             drawFlush = "tFD";
        }
        if(drawType == "BackdoorFlush"){
            drawFlush = "riveredBFD";
        }
        drawType.push_back(temp);

    }


}

std::string HandClassifier::getStrghtDraw(std::vector<std::string> &board, std::vector<std::string>& hand) {
   std::vector<int> stridx;
   getStrIdx(board, stridx);
   getStrIdx(hand, stridx);
   getPossibleStraightDraws(stridx, board, hand);
   return strghtDraw;


}

bool HandClassifier::checkIfRainbow(std::vector<std::string> &board) {
    int spades = 0;
    for(int i = 0; i < 3; i++){

        if(board[i][1] == 's') spades++;

    }
    return spades == 1;


}

void HandClassifier::getStrIdx(std::vector<std::string> &cards, std::vector<int> &stridx) {
    for(auto c : cards){

        switch(c[0]) {
            case 'A':   stridx.push_back(0);
                        stridx.push_back(13);
                break;
            case 'K':  stridx.push_back(12);
                break;
            case 'Q':  stridx.push_back(11);
                break;
            case 'J':  stridx.push_back(10);
                break;
            case 'T':   stridx.push_back(9);
                break;
            default: stridx.push_back((int)(c[0] - '0') - 1);

        }


    }

    std::sort(stridx.begin(), stridx.end(), std::greater<int>());
    stridx.erase(unique(stridx.begin(), stridx.end()), stridx.end());


}

void HandClassifier::getPossibleStraightDraws(std::vector<int> &stridx, std::vector<std::string>& board, std::vector<std::string> &hand)
{

    for(int i = 0; i < stridx.size() - 4; i++){

        if(stridx[i] - stridx[i+4]  == 4){

            checkStraight(stridx, board, i);
            return;
        }

    }


    if(board.size() == 5) return;


    for(int i = 0; i < stridx.size() - 3; i++){

        if(stridx[i] - stridx[i+3]  == 3){

            checkOpenEnded(stridx, board, i, 3);
            return;
        }
        else if(stridx[i] - stridx[i+3] == 4){

            //This conditions handles AKJT97 or QT986 draws
            int j = i+1;
            while(j + 3 < stridx.size() && (stridx[j] - stridx[j+3] == 4 || stridx[j] - stridx[j+3] == 3)) {j++;}
            j = j - i - 1;


            if(j){
                checkOpenEnded(stridx, board, i, j+3);
                return;
            }

            else{
                std::string g = "GS";
                checkGutshot(stridx, board, i, g);
                return;

            }


        }


    }


}

void HandClassifier::checkOpenEnded(std::vector<int> &stridx, std::vector<std::string> &board, int i, int length) {



    int numHoleCardsUsed = length - getNumBoardCardsUsed(stridx, board, i, length) + 1;

    switch(numHoleCardsUsed){

        case 2:

            if(length > 4 ||( stridx[i] != 13 && stridx[i+3] != 0 )) {

                strghtDraw = "2C OE";

            }

            else if (length != 4) {

                strghtDraw = "2C GS";

            } else {

                if(stridx[i+1] - stridx[i+4] == 4) {
                    std::string s = "GS";
                    checkGutshot(stridx, board, i + 1, s);
                }
                else{
                    checkOpenEnded(stridx, board, i + 1, 3);

                }

                if (strghtDraw == "1C GS") strghtDraw = "2C GS";
                if (strghtDraw == "1C OE") strghtDraw = "2C OE";


            }
            break;
        case 1:
            if((stridx[i] == 13|| stridx[i+3] == 0)){
                strghtDraw = "1C GS";
            }
            else{

                strghtDraw = "1C OE";
            }
            break;

        default: break;
//            std::cout << "4-Straight Board: ";
//            printBoard(board);


    }


}

int HandClassifier::getNumBoardCardsUsed(std::vector<int> &stridx, std::vector<std::string> &board, int start, int length) {
    int numBoardCardsUsed = 0;
    std::vector<int> brdidx;
    getStrIdx(board, brdidx);

    for (int j = start; j < start + length + 1; j++) {

        for(int i : brdidx){
            if (stridx[j] == i) numBoardCardsUsed++;

        }

    }
    return numBoardCardsUsed;
}

void HandClassifier::checkStraight(std::vector<int> &stridx, std::vector<std::string> &board, int i) {


    int numCardsinStraight = 5;
    int numHoleCardsUsed = numCardsinStraight - getNumBoardCardsUsed(stridx, board, i, 4);

    switch(numHoleCardsUsed){
        case 2: strghtDraw = "2C Str.";
        break;
        case 1: strghtDraw =  "1C Str.";
        break;
        case 0: strghtDraw = "5-Card Board Str.";
        break;
        default:
            strghtDraw = "";


    }

}



void HandClassifier::checkGutshot(std::vector<int> &stridx, std::vector<std::string> &board, int i, std::string& strghttype) {


    int k = getNumBoardCardsUsed(stridx, board, i, 3);

    if(k == 2) {

        strghtDraw.append("2C ");
        strghtDraw.append(strghttype);

    }

    else if(k == 3){

        strghtDraw.append("1C ");
        strghtDraw.append(strghttype);
    }
    else{
        //TODO add exception handling
    }


}

void HandClassifier::printBoard(std::vector<std::string> &board) {

    for(const auto& brd : board){

        std::cout << brd << " ";
    }
    std::cout << "\n";

}


HandClassifier::HandClassifier(const std::basic_string<char> brd, std::basic_string<char> hnd) {
    std::vector<std::string> board, hand;
    get_cards(brd, board);
    get_holecards(hnd, hand);
    flushDraw(board,hand);



    boardType_ = Unpaired;
    handType_ = NotPocketPair;

    sort(board.begin(), board.end(), order_holecards());
    getBoardType(board);
    getHandType(hand);

    if(boardType_ == Unpaired){

        getStrghtDraw(board, hand);
        getHandCategory(board, hand);
        getClassification();
    }

//




}


void HandClassifier::getHandCategory(std::vector<std::string>& board, std::vector<std::string>& hand) {

    switch(boardType_){
        case Unpaired: if(handType_ == PocketPair)
                           getUnpairedPr(board, hand);
                       else
                           getUnpaired(board, hand);
                       break;
        default:
            break;

     }




}










