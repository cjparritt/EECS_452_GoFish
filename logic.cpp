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
		return 1;// game is over
	}
	else if (books_made > 13)
		cerr << "Error! Too many books have been made!";//should never get here.
	else 
	{
		return 0; // game is not over
	}
}

void book_made(int player_num, rank)
{
	++books_made;
	for (int i = 0; i < 4; ++i) // set array col to -1 or "booked"
	{
		cards[i][rank] = -1;
	}
	if (player_num = 1)//com/p1 scored
	{
		++scores[0];
	}
	if (player_num = 2)//p2 scored
	{
		++scores[1];
	}
	if (player_num = 3)//p3 scored
	{
		++scores[2];
	}
	if (player_num = 4)//p4 scored
	{
		++scores[3];
	}
}

int do_i_have(int player_num,bool manual,int from_cam)
{
	int card = 0;
	int target = 0;
	int input = 0;
	if (manual == true) //check for manual input
	{
		cin >> input;
		card = input;
	}
	else
	{
		card = from_cam; // card asked from camera
	}
	target = cards[1][card];
	if (target > 0) // Com has a card(s)
	{
		cards[player_num][card] += cards[1][card];
		cards[0][rank] = 0;
		return 1;
	}
	else // Com does not have a card(s)
	{
		if (cards[player_num][rank] == 0)
		{
			cards[player_num][rank] += 1; // If we did not know if they had card of that rank
			return 0;
		}
		else
		{
			return 0;
		}
		
	}
}

int go_fish(int rank, int drawn_card)
{
	if(rank == drawn_card) // Drew requested card
	{
		cout << "I got what I wanted!\n";
		cards[0][rank] += 1;
		return 1; 
	}
	else // did not get requested card
	{
		cout << "I did not get what I wanted.\n";
		cards[0][drawn_card] += 1;
		if (cards[0][drawn_card] == 4) //check to see if a book was made
			{
				book_made(0, drawn_card);
			}
		++whos_turn;
		return 0;
	}

}

void do_you_have(bool manual,int from_cam)
{
	int draw = 0;
	char input = '';
	if(how_smart_am_i == 1)//DUMB !! may ask same question
	{
		guess_card:
		int guess = srand(rand(srand(rand(777)))) % 13;
		if (cards[0][guess] < 1)
		{
			goto guess_card;/* make sure its valid */
		}
		reroll_d:
		int player_guess = srand(rand(srand(rand(404)))) % 4 + 1;
		if(player_guess == 1)
		{
			goto reroll_d;
		}
		if(guess == 0)
		{
			cout << "Player " << player_guess << "do you have any Aces?\n";
		}
		else if(guess == 10)
		{
			cout << "Player " << player_guess << "do you have any Jacks?\n";
		}
		else if(guess == 11)
		{
			cout << "Player " << player_guess << "do you have any Queens?\n";
		}
		else if(guess == 12)
		{
			cout << "Player " << player_guess << "do you have any Kings?\n";
		}
		else
		{
			cout << "Player " << player_guess << "do you have any "<< guess+1 << "s?\n";
		}
		answer_d:
		cin >> answer;//Y or y yes n or N no
		if(answer == 89 || answer == 121)
		{
			int amount = 0;
			cout << "How many?";
			cin >> amount;
			cards[0][guess] += amount;
			cards[player_guess-1][guess] = 0;
			if (cards[0][guess] == 4)
			{
				 book_made(0, guess);
				 if(isGameOver() == 1)
				 {
				 	return;
				 }
			}
			goto guess_card;
		}
		else if(answer == 78 || answer == 110)
		{
			if (manual == true)
			{
				cin >> input;
				draw = input;
			}
			// else import from cam
			if(go_fish(guess, draw) == 1)
			{
				if (cards[0][guess] == 4)
				{
					book_made(0, guess);
				 	if(isGameOver() == 1)
				 	{
				 	return;
				 	}
				}
				goto guess_card;
			}
			else
			{
				return;
			}
		} 
		else
		{
			cout << "invalid answer\n";
			goto answer_d;
		}

	}

	if(how_smart_am_i == 2)//Normal
	{
		temp_smart://temp
		int target = 0;
		int check = 0;
		int player_target = 0;
		int block_arr[13] = {0};
		int misses = 0;
		find_target_n:
		for (int i = 0; i < 13; ++i)
		{
			if(check < cards[1][i])
				{
					check = cards[1][i];
					target = i;
				}
		}
		for (int j = 1; j < 3; ++j)
		{
			for (int i = 1; i < 4; ++i)
			{
				if(j < cards[i][target])
				{
					player_target = i;
				}
			}
		}
		if (player_target == 0)
		{
			block_arr[target] = 1;
			++misses
			if(misses == 13)//no information about other players
			{
				guess_card_n:
				target = srand(rand(srand(rand(777)))) % 13;
				if (cards[0][target] < 1)
				{
					goto guess_card_n;/* make sure its valid */
				}
				reroll_n:
				int player_target = srand(rand(srand(rand(404)))) % 4 + 1;
				if(player_target == 1)
				{
					goto reroll_n;
				}
			}
			else
			{
				goto find_target_n;
			}
		}
		if(target == 0)
		{
			cout << "Player " << player_target << "do you have any Aces?\n";
		}
		else if(target == 10)
		{
			cout << "Player " << player_target << "do you have any Jacks?\n";
		}
		else if(target == 11)
		{
			cout << "Player " << player_target << "do you have any Queens?\n";
		}
		else if(target == 12)
		{
			cout << "Player " << player_target << "do you have any Kings?\n";
		}
		else
		{
			cout << "Player " << player_target << "do you have any "<< target << "s?\n";
		}
		answer:
		cin >> answer;//Y or y yes n or N no
		if(answer == 89 || answer == 121)
		{
			int amount = 0;
			cin >> amount;
			cards[0][target] += amount;
			cards[player_target][target] = 0;
			if (cards[0][target] == 4)
			{
				 book_made(0, target);
				 if(isGameOver() == 1)
				 {
				 	return;
				 }
			}
			goto find_target_n;
		}
		else if(answer == 78 || answer == 110)
		{
			if (manual == true)
			{
				cin >> input;
				draw = input;
			}
			// else import from cam
			if(go_fish(guess, draw) == 1)
			{
				if (cards[0][guess] == 4)
				{
					book_made(0, guess);
				 	if(isGameOver() == 1)
				 	{
				 	return;
				 	}
				}
				goto guess_card;
			}
		} 
		else
		{
			cout << "invalid answer\n";
			goto answer;
		}
	}
	if(how_smart_am_i == 3)//Smart
	{
		goto temp_smart; // need to figure out a smart AI
	}
	cout << "invalid AI level exiting" << endl; 
	exit(1);
}

void game_init(int card_1_rank,int card_2_rank,int card_3_rank,int card_4_rank,
	int card_5_rank)
	{
		for(int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 13; ++j)
			{
				cards[i][j] = 0;
			}
		}
		books_made = 0;
		cards[0][card_1_rank] += 1;
		cards[0][card_2_rank] += 1;
		cards[0][card_3_rank] += 1;
		cards[0][card_4_rank] += 1;
		cards[0][card_5_rank] += 1;
		int ai_level;
		ai_set:
		cout << "How smart am I?";
		cin >> ai_level;
		if(ai_level > 3 || ai_level < 1)
		{
			cout << "invalid level\n choose 1-3\n";
			goto ai_set;
		}
		how_smart_am_i = ai_level;
		whos_turn = 0;
		return;
	}

void  other_players_turn(bool manual, int from_cam) //Assuming we will not provide wrong data
{
	char input = '';
	int amount = 0;
	int rank = 0;
	int asked_player;
	q0:
	cout << "Who did they ask? \n";
	cin >> input;
	asked_player = atoi(asked_player);
	if(asked_player == 0)
	{
		if(do_i_have(whos_turn,manual,from_cam) == 1)
		{
			if(isGameOver() == 1)
			{
				return;
			}
			goto q0;
		}
		else
		{
			cout << "Go Fish!\n"
			goto q2;
		}
	}
	q1:
	cout << "What did they ask for?\n"
	cin >> input;
	if(input == 'a' || input == "A")
	{
		rank = 0;
	}
	else if(input == 'j' || input == "J")
	{
		rank = 10;
	}
	else if(input == 'q' || input == "Q")
	{
		rank = 11;
	}
	else if(input == 'k' || input == "K")
	{
		rank = 12;
	}
	else if(input == '0')
	{
		rank = 9;
	}
	else if(input == '1')
	{
		rank = 0;
	}
	else if(input == '2')
	{
		rank = 1;
	}
	else if(input == '3')
	{
		rank = 2;
	}
	else if(input == '4')
	{
		rank = 3;
	}
	else if(input == '5')
	{
		rank = 4;
	}
	else if(input == '6')
	{
		rank = 5;
	}
	else if(input == '7')
	{
		rank = 6;
	}
	else if(input == '8')
	{
		rank = 7;
	}
	else if(input == '9')
	{
		rank = 8;
	}
	q2:
	cout << "Did the asked player have what they wanted?\n";
	cin >> input;//Y or y yes n or N no
		if(input== 89 || input == 121)//yes
		{
			cards[asked_player][rank] = 0;
			cout << "How many did they get?\n";
			cin >> input;
			amount = atoi(input);
			cards[whos_turn][rank] += amount;
			if (cards[whos_turn][rank] == 4)
			{
				book_made(whos_turn,rank);
				if(isGameOver() == 1)
				{
					return;
				}
			}
			goto q0;
		}
		if(input == 78 || input == 110)//no
		{ 
			q3:
			cout << "Did they draw what they were looking for?\n";
			if (input == 89 || input == 121)//yes
			{
				cards[whos_turn][rank] += 1;
				cout << "Did they book?\n";
				cin >> input;//Y or y yes n or N no
				if(input== 89 || input == 121)//yes
				{
					book_made(whos_turn,rank);
					if(isGameOver() == 1)
					{
						return;
					}
				}
			goto q0;
			}
			if(input == 78 || input == 110)//no
			{
				if(cards[whos_turn][rank] == 0)
				{
					cards[whos_turn][rank] = 1;
					++whos_turn;
					return;
				}
				else
				{
					++whos_turn;
					return;
				}
			}
			else
			{
				cout << "invalid answer\n";
				goto q3;
			} 
		else
		{
			cout << "invalid answer\n";
			goto q2;
		}
	}
}

void score_screen()
{
	int highest = 0;
	int winner[4] = {0,0,0,0};
	for (int i = 0; i < 4; ++i)
	{
		if (scores[i] >= highest)
		{
			winner[i] = 1;
			highest = scores[i];
		}
	}
	for (int i = 0; i < count; ++i)
	{
		if(winner[i] == 1)
		{
			cout << "Player" << (i+1) << " wins\n";
		}
	}
}