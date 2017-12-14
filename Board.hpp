//
//  Board.hpp
//  Boggle_Word_Finder
//
//  Created by Mudit Gurjar on 12/12/17.
//  Copyright © 2017 Mudit Gurjar. All rights reserved.
//

// On instantiation, the board class generates the cells' letters and displays the entire board
// The letters are currently generated absolutely randomly, with each letter having equal probability


#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <vector>


class primitive_cell
{
    char letter;
    int vowel_indicator;
    bool been_here_value;
    std::vector<int> data_numbers;
    std::vector<std::string> data_strings;
    
public:
    primitive_cell(): letter('0'), vowel_indicator(0), been_here_value(0)
    {
        data_numbers.reserve(2); data_strings.reserve(2);
    }
    char get_letter() {return letter;}
    int get_vowel_indicator() {return vowel_indicator;}
    bool been_here() {return been_here_value;}
    std::vector<int> get_data_numbers() {return data_numbers;}
    std::vector<std::string> get_data_strings() {return data_strings;}
    
    void set_letter(char let) {letter = let;}
    void set_vowel_indicator(int indicator) {vowel_indicator = indicator;}
    void set_been_here(bool answer) {been_here_value = answer;}
    void set_data_numbers(std::vector<int> data_n) {data_numbers = data_n;}
    void set_data_string(std::vector<std::string> data_s) {data_strings = data_s;}
};


class Board
{
    // Stores the board rows and columns
    int b_rows, b_cols;
    int min_word_length = 4, max_word_length = 20;
    
    
    // Creating a 2D board of characters
    // The boggle board of letters only, that will be displayed to user
    typedef std::vector<char> Row_char;
    typedef std::vector<Row_char> Matrix_char;
    Matrix_char letter_board;
    
    // Creating the underlying data structure of the board, to help with computations
    // Basically a 2D vector of "primitive cells" - cells containing the letter, as well as other values
    typedef std::vector<primitive_cell> primitive_Row;
    typedef std::vector<primitive_Row> primitive_Matrix;
    primitive_Matrix board;
    
    // get primitive cell by row and column
    primitive_cell get_cell(int row_n, int col_n) {return board[row_n][col_n];}
    
    
    
    // Given row and column indices, check when outside board
    bool is_outside_board(int row, int col);
    
    /*
     Function that will generate the vowel/consonant indicators for each cell
     Fills the cells from topmost row, moving left to right, then filling the next row down, etc
     Each cell has at most 4 adjacent cells that are already filled with an indicator
     The function outputs the indicator with weighted randomness, depending on the adjacent cells
     */
    void generate_vowel_indicators();
    int get_neighbor_vowel_indicators(int row, int col);
    
    /*
     function that generates letters based on the numbers generated in the cells
     Each cell already has predetermined type: consonants or vowels
     However the actual consonant is determined by a weighted random function
     Basically the random function favors the more used vowels/consonants over the lesser used
     */
    void generate_letters();
    
    
    // vector storing database of all English words in alphabetical order
    std::vector< std::string > dictionary;
    
    // vector to store all valid English words on the Board
    std::vector< std::string > valid_words_vec;
    
    
    // function that converts letter board to primitive cells board,
    // in case word_finder receives a letters-only board
    void convert_letter_2_primitive();
    
    // function that gets an 'English words' database: corncob_lowercase.txt file and stores all its words inside a usable vector
    void store_dictionary();
    
    // finds all possible valid words
    void find_all_words();
    // function inside find_all_words used in conjunction with the recursve 'extend_word' function
    // searches for all possible words, ystematically goes from current letter to all 8 adjacent letters
    // if still on the board and on a new letter, extend word and move again to all 8 adjacent letters
    void move_to_cell_on_the_right(int from_cell_row, int from_cell_col, std::string word);
    // recursive function used in 'find_all_words' and in conjunction with move_to_cells_on_the_right
    // checks words with dictionary and stores if they are valid words
    void extend_word(int current_cell_row, int current_cell_col, std::string word);
    // function that checks if current word sequence still can yield a valid word
    bool sequence_is_still_valid(std::string word);
    // main function that finds all possible unique letter combinations on the board
    // checks and stores if they are valid English words, then sorts alphabetically
    void log_words();

    
    
public:
    Board(int rows, int cols);
    
    // displays the board
    void display();
    
    // main function that outputs all the valid words in a file
    // can accept a primitive cells board, or a letters-only board
    void word_finder();
    

};


#endif /* Board_hpp */
