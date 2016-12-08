/*
Copyright 2016 Christian Parritt

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

This is the header file for logic.c and contains the declarations for its
functions, required includes, and predefined varables.
*/

#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/opencv.hpp>

//#include "take_pictures.h"
//#include "extractcard.h"

extern int scores[4];
extern int ai_level;
extern int books_made;
extern int whos_turn;
extern int cards[4][13]; //rows represent suit and columns represent rank.
extern bool manual;
extern int num_players;

using namespace std;
//using namespace cv;

int isGameOver();
/*
R: number of books made
M: N/A
E: Checks to see if books_made is 13 and returns 1 if true
*/

void book_made(int player_num, int rank);
/*
R: player number and rank of book made
M: books_made, cards array, and player score
E: increments books_made and the correct playes score by 1 and sets
   card array rank position to booked.
*/

int do_i_have(int rank,int player_num);
/*
R: rank of cards asked for and who asked
M: cards array
E: Checks to see if the computer has a card asked for and returns 1 if true.
   Alters card array based on if true and AI level. 
*/


int go_fish(int rank,int drawn_card);
/*
R: rank of card looking for and card drawn
M: cards array and maybe whos turn
E: returns 1 if computer got what it was looking for and may call book_made.
   It may also increment whos_turn
*/

void do_you_have();
/*
R: Manual switch variable (TRUE if playing in manual mode)
M: cards array
E: askes for a card based on the card array
*/

void other_players_turn();
/*
R: N/A
M: cards array books made whos turn
E: gathers data from operator during other players turns
*/

void game_init(int card_1_rank,int card_2_rank,int card_3_rank,int card_4_rank,
	int card_5_rank);
/*
R: the five cards drawn
M: card array and AI level
E: preps the game for play
*/

void score_screen();
/*
R: N/A
M: N/A
E: Displays the winner(s)
*/

int yes_no_box(string question);
// Requires: Caller must supply a yes or no question to be asked in the form of a string.
// Modifies:
// Explain: A dialog box will pop up displaying the question where the user can select yes or no. Function returns 1 if user selects yes, 0 if user selects no,-1 if no selection is made, and -2 if there is an error.

/*

void getcards(int *newhand);
// Requires: Caller supplies a pointer to an array of length 13 to hold the
// new values for the computer's hand. 

// Modifies: The function populates newhand with integers corresponding to the number of cards of each rank
// detected, where the indices 0-12 represent the ranks A-K.

// Explain: If the computer has drawn or been given cards for itself, the caller should supply
// a pointer to cards[0][0]. If it is another player's turn and they are
// asking the computer for a card, the caller should create a temporary array
// of length 13 and provide that pointer to get_cards. The caller should then run card_diff_check on the computer's
// current hand and the temporary array to determine what card is being asked for.

void card_diff_check(int * currenthand, int * temphand);
// Requires: Caller supplies a pointer to two arrays of length 13.
// Modifies: The function modifies each element of temphand by setting the element to be the difference between the values of temphand and currenthand at that index.
// Explain: Use to determine what card is being asked for by the user. The currenthand array should be the array containing the computer's current hand (cards[0]). The temphand array should contain the hand detected through image processing (see get_cards function).

int identify_new_card();
// Requires: N/A
// Modifies: N/A
// Effects: Checks what card has been added to the computer's hand and returns the rank of that card.

string rank_to_str(int rank);
// Requires: A rank 0-12.
//Modifies: N/A
//Effects: Returns a string with A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, or K depending on the value of rank.
 
void print_ai_cards();
*/

#endif

