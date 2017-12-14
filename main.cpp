//
//  main.cpp
//  Boggle_Word_Finder
//
//  Created by Mudit Gurjar on 12/12/17.
//  Copyright © 2017 Mudit Gurjar. All rights reserved.
//

#include "Board.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main() {
    
    int a = 5, b = 5;
    
    // create and display the filled board
    Board my_board(a, b);
    my_board.display();
    
    my_board.word_finder();
    
    return 0;
}
