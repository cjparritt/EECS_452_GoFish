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

Description: This file contains the logic for an atrificial
go fish player. It is made to interface with perrifirial devices and
programs sunch as OpenCV and a camera to acquire infromation on cards in its
hand and to be asked for cards.
*/

#include "logic.h"

int isGameOver(int books_made)
{
	if (books_made == 13)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void book_made(int player_num, rank)
{
	++books_made;
	cards[rank] = -1;
	if (player_num = 1)
	{
		++score_P1;
	}
	if (player_num = 2)
	{
		++score_P2;
	}
	if (player_num = 3)
	{
		++score_P3;
	}
	if (player_num = 4)
	{
		++score_P4;
	}
}

int do_i_have(int rank)
{

}

int go_fish(int rank, int drawn_card)
{
	if(rank == drawn_card)
	{
		return 1; 
	}
	else
	{
		++whos_turn;
		return 0;
	}

}

void do_you_have()
{
	
}

void game_init(int card_1_rank,int card_2_rank,int card_3_rank,int card_4_rank,
	int card_5_rank,int ai_level)
	{
		int i = 0;
		for(i = 0; i < 13; ++i)
		{
			cards[i] = 0;
		}
		books_made = 0;
		cards[card_1_rank] = 1;
		cards[card_2_rank] = 1;
		cards[card_3_rank] = 1;
		cards[card_4_rank] = 1;
		cards[card_5_rank] = 1;
		how_smart_am_i = ai_level;
	}
