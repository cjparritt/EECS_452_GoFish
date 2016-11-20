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

Description: This file contains the logic for an artificial
go fish player. It is made to interface with peripheral devices and
programs sunch as OpenCV and a camera to acquire information on cards in its
hand and to be asked for cards.
*/

#include "logic.h"
#include <iostream>
#include <iomanip>

bool man_switch = false;
int whos_turn = 0;

int main()
{
	int loop_end = 0;
	char input = '';
	int init_card[5] = {0};
	int scan_card = 0;
	int starter = 0;

	choice:
		cout << "Do you want to play in manual mode or camera mode?\n";
		cout << "Please input M or m for manual and C or c for camera.\n";
		cin >> input;
		if(input == 77 || input == 109)//Manual
		{
			for(int i = 1; i < 6; ++i)
			{
				cout << "Input card "<< i << " rank\n"; // asuming we put in only right inputs TODO: add period
				cin >> input;
				init_card[i-1] = atoi(input);
			}
			man_switch = true;
			game_init(init_card[0],init_card[1],init_card[2],init_card[3],init_card[4]);
			if(starter == 4)
			{
				starter = 0;
				whos_turn += starter;
			}
			else
			{
				whos_turn += starter
				starter++;
			}
			goto play;			
		}
		else if(input == 67 || input == 99)//Camera
		{
			//TODO: Need to add cam init stuff 
			
		}
		else
		{
				cout << "invalid input\n";
				goto choice;
		}
	
	while (loop_end == 0)
	{
		play:
		cout << "It is player" << whos_turn << "'s turn.\n";
		if (whos_turn == 0)
		{
			do_you_have(man_switch,1); // 1 is a placeholder for cam fun
			if(isGameOver() == 1)
			{
				score_screen();
				++loop_end;
			}
		}
		else
		{
			other_players_turn(man_switch,1); //1 is placeholder for cam fun
			if(isGameOver() == 1)
			{
				score_screen();
				++loop_end;
			}
		}
		if(whos_turn >= 4)
		{
			whos_turn = 0;
		}
	}
	again:
	cout << "Do you want to play again? Type Y or N.\n";
	cin >> input;//Y or y yes n or N no
	if(input == 89 || input == 121)
	{
		loop_end = 0;
		input = '';
		init_card = {0,0,0,0,0};
		scan_card = 0;
		ai_level = 0;
		man_switch = false;
		goto choice;
	}
	else if(input == 78 || input == 110)
	{
		cout << "Goodbye" << endl;
		return 0;
	}
	else
		{
			cout << "Invalid input!\n";
			goto again;
		}
}