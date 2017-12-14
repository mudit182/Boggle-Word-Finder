//
//  Board.cpp
//  Boggle_Word_Finder
//
//  Created by Mudit Gurjar on 12/12/17.
//  Copyright © 2017 Mudit Gurjar. All rights reserved.
//

#include "Board.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>


// Constructor initializes board, and fills it with letters
Board::Board(int rows, int cols) : b_rows(rows), b_cols(cols), board(rows, primitive_Row(cols))
{
    srand( (unsigned int)time(NULL) );
    generate_vowel_indicators();
    generate_letters();
}





void Board::word_finder()
{
    
    // create dictionary from a .txt file of English words database
    store_dictionary();
    
    // recursively go to each cell, test for all possible words starting from that letter
    // and store in vector 'valid_words_vec' all the correct English words found on the Board
    find_all_words();
    
    // sort the valid words vector alphabetically
    std::sort(valid_words_vec.begin(), valid_words_vec.end());
    
    // log words in a file "valid_words"
    log_words();
    
}




// Given row and column indices, check when outside board
bool Board::is_outside_board(int row, int col)
{
    if ( (row > -1) && (row < b_rows) && (col > -1) && (col < b_cols) )
        return 0;
    else
        return 1;
}





// Before generating actual letters for the board,
// decide for each cell if it gets filled with a vowel or consonant
// 1: vowel & 2: consonant
void Board::generate_vowel_indicators()
{
    int neighbor_info, neighbor_vowels, neighbor_consonants;
    for (int i = 0; i < b_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            neighbor_info = get_neighbor_vowel_indicators(i, j);
            neighbor_vowels = neighbor_info%10;
            neighbor_consonants = (neighbor_info - neighbor_vowels)/10;
            // if neighbor consonant/vowel difference is 0, prob(consonant)/prob(vowel) = 6/5
            // if neighbor cells have how many more consonant than vowels, that difference
            // skews the probability of current cell's vowel/consonant generation
            int rand_int = std::rand()%11 + 1;
            if (rand_int < 6 + (neighbor_consonants - neighbor_vowels)) {
                (board[i][j]).set_vowel_indicator(1);
            }
            else
                (board[i][j]).set_vowel_indicator(10);
        }
    }
}






int Board::get_neighbor_vowel_indicators(int row, int col)
{
    int neighbor_indicators = 0;
    // neighbor 1
    if (!is_outside_board(row-1, col-1)) {
        neighbor_indicators += (get_cell(row-1, col-1)).get_vowel_indicator();
    }
    // neighbor 2
    if (!is_outside_board(row-1, col)) {
        neighbor_indicators += (get_cell(row-1, col)).get_vowel_indicator();
    }
    // neighbor 3
    if (!is_outside_board(row -1, col+1)) {
        neighbor_indicators += (get_cell(row-1, col+1)).get_vowel_indicator();
    }
    // neighbor 4
    if (!is_outside_board(row, col-1)) {
        neighbor_indicators += (get_cell(row, col-1)).get_vowel_indicator();
    }
    return neighbor_indicators;
}






// Generate letters for the board
void Board::generate_letters()
{
    int letter_indice;
    // letter weightage based on scrabbles tile frequencies
    // So (roughly) a,e,o have more probability of getting selected than i,u,y
    std::string vowel_density = "eeeeaaaoooiiuy";
    // Similarly probability d,g,l,n,r,s,t is more than, b,c,f,h,m,p,v,w, whic is itself more
    // than probability of j,k,q,x,z to be selected
    std::string consonant_density = "nnnnnrrrrrtttttllllssssdddggghhhmmmbbccffppvvwwjkqxz";
    
    for (int i = 0; i < b_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            if ((get_cell(i, j)).get_vowel_indicator() == 1) {
                // pick vowel
                letter_indice = std::rand()%vowel_density.length();
                (board[i][j]).set_letter(vowel_density[letter_indice]);
            }
            else {
                // pick consonant
                letter_indice = std::rand()%consonant_density.length();
                (board[i][j]).set_letter(consonant_density[letter_indice]);
            }
        }
    }
}






// Display the letter-only board as a boggle board for playing
void Board::display()
{
    std::cout << std::endl << std::endl;
    
    for (int i = 0; i < b_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            std::cout << " " << " " << (char)(toupper((get_cell(i,j)).get_letter())) << " ";
        }
        std::cout << std::endl << std::endl;
    }
    
    std::cout << std::endl << std::endl << std::endl;
}






// Creates a dictionary vector from a file database containing all English words
void Board::store_dictionary()
{
    std::string word;
    std::ifstream all_words_database;
    all_words_database.open("resources/corncob_lowercase.txt");
    
    while(std::getline(all_words_database, word) )
    {
        if( word[word.length()-1] == '\r' || word[word.length()-1] == '\n' )
            word.resize(word.length()-1);
            dictionary.push_back(word);
    }
    
    all_words_database.close();
}





void Board::find_all_words()
{
    std::string word;
    for (int i = 0; i < b_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            word = "";
            extend_word(i, j, word);
        }
    }
}





void Board::move_to_cell_on_the_right(int current_cell_row, int current_cell_col, std::string word)
{
    int step = 1;
    
    if (word.length() <= max_word_length) {
        switch (step) {
            case 1:
                extend_word(current_cell_row, current_cell_col, word);
            case 2:
                current_cell_row--;
                extend_word(current_cell_row, current_cell_col, word);
            case 3:
                current_cell_col++;
                extend_word(current_cell_row, current_cell_col, word);
            case 4:
                current_cell_col++;
                extend_word(current_cell_row, current_cell_col, word);
            case 5:
                current_cell_row++;
                extend_word(current_cell_row, current_cell_col, word);
            case 6:
                current_cell_row++;
                extend_word(current_cell_row, current_cell_col, word);
            case 7:
                current_cell_col--;
                extend_word(current_cell_row, current_cell_col, word);
            case 8:
                current_cell_col--;
                extend_word(current_cell_row, current_cell_col, word);
        }
    }
}


void Board::extend_word(int current_cell_row, int current_cell_col, std::string word)
{
    if( !is_outside_board(current_cell_row, current_cell_col) ) {
        if ( !(board[current_cell_row][current_cell_col]).been_here() ) {
            word = word + (board[current_cell_row][current_cell_col]).get_letter();
            if (sequence_is_still_valid(word)) {
                (board[current_cell_row][current_cell_col]).set_been_here(1);
                move_to_cell_on_the_right(current_cell_row, current_cell_col - 1, word);
                if (word.length() >= min_word_length) {
                    if (std::binary_search(dictionary.begin(), dictionary.end(), word)) {
                        valid_words_vec.push_back(word);
                    }
                }
                (board[current_cell_row][current_cell_col]).set_been_here(0);
            }
        }
    }
}




bool Board::sequence_is_still_valid(std::string word)
{
    std::vector<std::string>::iterator iter = std::upper_bound(dictionary.begin(), dictionary.end(), word);
    std::string dic_word = *iter;
    dic_word.resize(word.length());
    if (dic_word == word) {
        return 1;
    }
    else
        return 0;
}




void Board::log_words()
{
    
    
    // log into new file 'valid_words.txt'
    std::ofstream valid_words("resources/valid_words.txt");
    
    for (int i = 0; i < valid_words_vec.size(); i++)
    {
        valid_words << valid_words_vec.at(i) << '\n';
        std::cout << valid_words_vec.at(i) << '\n';
    }
    
    std::cout << "Valid words = " << valid_words_vec.size() << std::endl;
    
    valid_words.close();
    
}





