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
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;


int score_P1 = 0; //This is the computer.
int score_P2 = 0;
int score_P3 = 0;
int score_P4 = 0;

int how_smart_am_i = 0;
//used for dificulty? 0-x

int books_made = 0;

int whos_turn = 0;

int cards[4][13] = {0};
//rows represent suit and columns represent rank.

int isGameOver(int books_made);
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
R: N/A
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

#endif