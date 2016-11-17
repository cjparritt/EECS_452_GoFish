<<<<<<< HEAD
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

int main()
{
	int loop_end = 0;
	char input = '';
	int init_card[5] = {0};
	int scan_card = 0;
	bool man_switch = false;

	start:
	while (loop_end == 0)
	{
		choice:
		cout << "Do you want to play in manual mode or camera mode?\n";
		cout << "Please input M or m for manual and C or c for camera.\n";
		cin >> input;
		if(input == 77 || input == 109)//Manual
		{
			for(int i = 1; i < 6; ++i)
			{
				cout << "Input card "<< i << " rank.\n"; // asuming we put in only right inputs
				cin >> input;
				init_card[i-1] = atoi(input);
			}
			man_switch = true;
			goto play;			
		}
		else if(input == 67 || input == 99)//Camera
		{
			//TODO: Need to add cam stuff
		}
		else
		{
				cout << "Invalid input!\n";
				goto choice;
		}
		play://TODO: Need to add functions
		game_init(init_card[0],init_card[1],init_card[2],init_card[3],init_card[4]);

	}
	again:
	cout << "Do you want to play again?\n"; //TODO: Add Y or N query
	cin >> input;//Y or y yes n or N no
	if(input == 89 || input == 121)
	{
		loop_end = 0;
		input = '';
		init_card = {0,0,0,0,0};
		scan_card = 0;
		ai_level = 0;
		man_switch = false;
		goto start;
	}
	else if(input == 78 || input == 110)
	{
		cout << "Goodbye" << endl;
		return 0;
	}
	else
		{
			cout << "invalid input\n";
			goto again;
		}
=======
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

int main()
{
	int loop_end = 0;
	char input = '';
	int init_card[5] = {0};
	int scan_card = 0;
	int starter = 0;

	choice:
		cout << "Do you want to play in manual mode or camera mode?\n";
		cout << "Please input M or m for manual and C or c for camera\n"; //TODO: Add period.
		cin >> input;
		if(input == 77 || input == 109)//Manual
		{
			for(int i = 1; i < 6; ++i)
			{
				cout << "Input card "<< i << " rank\n"; // asuming we put in only right inputs TODO: add period
				cin >> input;
				init_card[i-1] = atoi(input);
			}
			cout << "Input AI level (1-3)\n" //TODO: remove AI query here. It is duplicated in game_init
			cin >> input;
			ai_level = atoi(input);
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
			//TODO: Need to add cam stuff
			
		}
		else
		{
				cout << "invalid input\n";
				goto choice;
		}
	
	while (loop_end == 0)
	{
		play://Need to add functions
		if (whos_turn == 0)
		{
			do_you_have(man_switch);
			if(isGameOver() == 1)
			{
				score_screen();
				
			}
		}


	}
	again:
	cout << "Do you want to play again?\n"; //TODO: Add Y or N query
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
			cout << "invalid input\n";
			goto again;
		}
>>>>>>> refs/remotes/origin/master
}