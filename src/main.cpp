


#define CATCH_CONFIG_RUNNER

#include <iostream>

#include <csv.h>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

#include <algorithm>
#include "../tst/catch.hpp"
#include "HandClassifier.h"


using namespace std;

std::string GetCurrentWorkingDir(void ) {
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}



int main(int argc, char* argv[]) {
    //TODO Figure out how to write back to the CSV
    // TODO Figure out how to tell how big the board is
    // TODO How to pass in Input File
//    if(argc < 2){
//       throw std::invalid_argument("Please specify input file: HandClassifier <filename>");
//    }


    std::cout << GetCurrentWorkingDir() << std::endl;

    ofstream outputFile;


   string filename = argv[1];
   for(int i = 0; i < 4; i++){
       filename.pop_back();
   }

   filename.append("HandCat.csv");

    outputFile.open(filename);
    outputFile << "Board,Hand,Cat,Draw\n";

    io::CSVReader<4> in(argv[1]);
    in.read_header(io::ignore_missing_column, "Flop", "Turn", "Hand","River");

    std::string flop, turn, hand, river;


    bool has_turn = in.has_column("Turn");
    bool has_river = in.has_column("River");

    while(in.read_row(flop, turn, hand, river)){
//
//
        std::string board = flop;

        if(has_turn){

        board.push_back(' ');
        board.append(turn);
    }




    if(has_river){
        board.push_back(' ');
        board.append(river);
    }

    auto hc = HandClassifier(board, hand);

    outputFile << board << "," << hand << ",";
    outputFile << hc.handStrength() << "," <<  hc.draw() << "\n";

//
    }

    outputFile.close();

//    if(rename("testOut1.csv", "testOut.csv")) perror("Error renaming File");

    if(strcmp(argv[2], "-t")==0){

        int result = Catch::Session().run( );
    }





    return 0;
}
