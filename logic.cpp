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

int scores[4] = { 0,0,0,0 };
int ai_level = 0;
int books_made = 0;
int whos_turn = 0;
int cards[4][13] = { 0 }; //rows represent suit and columns represent rank.
bool manual = false;
int num_players = 0;

int isGameOver()
{
	if (books_made == 13)
	{
		return 1;
	}
	else if (books_made > 13)
		cerr << "Error! Too many books have been made!";
	else
	{
		return 0;
	}
}

void book_made(int player_num, int rank)
{
	++books_made;
	for (int i = 0; i < 4; ++i)
	{
		cards[i][rank] = -1;
	}
	if (player_num == 1)
	{
		++scores[0];
	}
	if (player_num == 2)
	{
		++scores[1];
	}
	if (player_num == 3)
	{
		++scores[2];
	}
	if (player_num == 4)
	{
		++scores[3];
	}
}

int do_i_have(int rank,int player_num)
{
	int target = 0;
	target = cards[0][rank];
	if (target > 0)
	{
		cards[player_num][rank] += cards[0][rank];
		cards[0][rank] = 0;
		return 1;
	}
	else
	{
		if (cards[0][rank] == 0)
		{
			cards[player_num][rank] += 1;
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
	if(rank == drawn_card)
	{
		cout << "I got what I wanted!\n";
		cards[0][rank] += 1;
		if (cards[0][rank] == 4)
			{
				 book_made(1, rank);
				 if(isGameOver() == 1)
				 {
				 	return;
				 }
			}
		return 1; 
	}
	else
	{
		cout << "I did not get what I wanted.\n";
		cards[0][drawn_card] += 1;
		if (cards[0][drawn_card] == 4)
			{
				 book_made(1, drawn_card);
				 if(isGameOver() == 1)
				 {
				 	return;
				 }
			}
		++whos_turn;
		return 0;
	}

}

void do_you_have()
{
	int draw = 0;
	int response = -1;
	char input = ' ';
	int misses = 0;
	if(ai_level == 1)//DUMB !! may ask same question
	{
		guess_card:
		srand(time(0));
		int guess = rand() % 13;
		if (cards[0][guess] < 1)
		{
			goto guess_card;/* make sure its valid */
		}
		reroll_d:
		int player_guess = (rand() % num_players) + 1;
		if(player_guess == 1)
		{
			goto reroll_d;
		}
		if(guess == 0)
		{
			response = yes_no_box("Player "+to_string(player_guess)+" do you have any Aces?");
		}
		else if(guess == 10)
		{
			response = yes_no_box("Player "+to_string(player_guess)+" do you have any Jacks?");
		}
		else if(guess == 11)
		{
			response = yes_no_box("Player "+to_string(player_guess)+" do you have any Queens?");
		}
		else if(guess == 12)
		{
			response = yes_no_box("Player "+to_string(player_guess)+" do you have any Kings?");
		}
		else
		{
			response = yes_no_box("Player "+to_string(player_guess)+" do you have any "+rank_to_str(guess)+"s?");
		}
		answer_d:
		if(response==1) //Yes
		{
			int amount = 0;
			cout << "How many?\n";
			cin >> amount;
			cards[0][guess] += amount;
			cards[player_guess-1][guess] = 0;
			if (cards[0][guess] == 4)
			{
				 book_made(1, guess);
				 if(isGameOver() == 1)
				 {
				 	return;
				 }
			}
			goto guess_card;
		}
		else if(response==0)//No
		{
			cout << "Please draw me a card! \n";
			if (manual == false)
			{
				if(misses < 2)
				{
					cam_draw_1:
					cout << "Please press Y when ready.\n";
					cin >> input;
					draw = identify_new_card();
					cout << "Did I get a " << rank << "?\n";
					if(input==89 || input==121)//yes
					{
						goto gf;
					}
					else
					{
						++misses;
						goto cam_draw_1;
					}
				}
				else
				{
					cout << "Too many errors.\nManual input required.\n"
					goto e1;
				}
			}
			else
			{
				e1:
				cout << "What rank did you draw for me? Please enter 0-12 for A-K:\n";
				cin >> draw;
			}
			gf:
			if(go_fish(guess, draw) == 1)
			{
				goto guess_card;
			}
			else
			{
				return;
			}
		} 
		else
		{
			cout << "Oh no! Something went wrong. Let's try again.\n";
			if(guess == 0)
			{
				response = yes_no_box("Player "+to_string(player_guess)+" do you have any Aces?");
			}
			else if(guess == 10)
			{
				response = yes_no_box("Player "+to_string(player_guess)+" do you have any Jacks?");
			}
			else if(guess == 11)
			{
				response = yes_no_box("Player "+to_string(player_guess)+" do you have any Queens?");
			}
			else if(guess == 12)
			{
				response = yes_no_box("Player "+to_string(player_guess)+" do you have any Kings?");
			}
			else
			{
				response = yes_no_box("Player "+to_string(player_guess)+" do you have any "+rank_to_str(guess)+"s?");
			}

			goto answer_d;
		}

	}

	if(ai_level == 2)//Normal
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
				if(check < cards[0][i] && !block_arr[i])
				{
					check = cards[0][i];
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
			++misses;
			if(misses == 13)//no information about other players
			{
				guess_card_n:
				target = rand() % 13;
				if (cards[0][target] < 1)
				{
					goto guess_card_n;/* make sure its valid */
				}
				reroll_n:
				int player_target = (rand() % num_players) + 1;
				if(player_target == 0)
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
			cout << "Player " << player_target << " do you have any Aces?\n";
		}
		else if(target == 10)
		{
			cout << "Player " << player_target << " do you have any Jacks?\n";
		}
		else if(target == 11)
		{
			cout << "Player " << player_target << " do you have any Queens?\n";
		}
		else if(target == 12)
		{
			cout << "Player " << player_target << " do you have any Kings?\n";
		}
		else
		{
			cout << "Player " << player_target << " do you have any "<< target << "s?\n";
		}
		answer:
		cin >> input;//Y or y yes n or N no
		if(input == 89 || input == 121)
		{
			int amount = 0;
			cin >> amount;
			cards[0][target] += amount;
			cards[player_target][target] = 0;
			if (cards[0][target] == 4)
			{
				 book_made(1, target);
				 if(isGameOver() == 1)
				 {
				 	return;
				 }
			}
			goto find_target_n;
		}
		else if(input == 78 || input == 110)
		{
			cout << "Please draw me a card! \n";
			if (manual == false)
			{
				if(misses < 2)
				{
					cam_draw_2:
					cout << "Please press Y when ready.\n";
					cin >> input;
					draw = identify_new_card();
					cout << "Did I get a " << rank << "?\n";
					if(input==89 || input==121)//yes
					{
						goto gf;
					}
					else
					{
						++misses;
						goto cam_draw_2;
					}
				}
				else
				{
					cout << "Too many errors.\nManual input required.\n"
					goto e2;
				}
			}
			else
			{
				e2:
				cout << "What rank did you draw for me? Please enter 0-12 for A-K:\n";
				cin >> draw;
			}
			gf:
			if(go_fish(guess, draw) == 1)
			{
				goto guess_card;
			}
			else
			{
				return;
			}
		} 
		} 
		else
		{
			cout << "invalid answer\n";
			goto answer;
		}
	}
	if(ai_level == 3)//Smart
	{
		goto temp_smart; // should not get here now.
	}
	cout << "invalid AI level exiting" << endl; //add endline
	exit(1);
}

void game_init(int card_1_rank,int card_2_rank,int card_3_rank,int card_4_rank,
	int card_5_rank)
	{
		if (manual == false)
		{
			int temp_hand[13] = {0};
			getcards(int temphand[0]);
			for(int i = 0; i < 13; ++i)
			{
				cards[0][i] = temphand[i];
			}
			books_made = 0;
			goto ai_set; I
		}
		else
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
		}
		ai_set:
		cout << "How smart am I? Please select 1, 2, or 3:\n";
		cin >> ai_level;
		if(ai_level > 3 || ai_level < 1)
		{
			cout << "invalid level\n choose 1-3\n";
			goto ai_set;
		}
		if (ai_level == 3)
		{
			ai_level = 2;
			cout << "You have choosen a level beyond the scope of my programing.\n";
			cout << "Reverting to default AI level.\n";
		}
	    player_set:
		cout << "How many players are there? Please select 2, 3, or 4:\n";
		cin >> num_players;
		if (num_players > 4 || num_players < 2)
		{
			cout << "invalid number\n choose 2-4\n";
			goto player_set;
		}
		whos_turn = 1;
		return;
	}

void  other_players_turn() //Assuming we will not provide wrong data
{
	char input = ' ';
	int amount = 0;
	int rank = 0;
	int asked_player;
	int scan_miss = 0;
	int response;
	q1:
	cout << "Who did they ask? \n";
	cin >> asked_player;
	if(asked_player == 1)
	{
		if(manual == false)
		{
			scan:
			if(scan_miss < 2)
			{
				
				cout << "Please show me your card.\nAre you ready?\nPress \'Y\' when ready\n";
				cin >> input;
				rank = identify_new_card();
				response = yes_no_box("Did you ask for "+rank_to_str(rank)+"s?");
				if(response == 1)//yes
				{
					goto q4;
				}
				else if (response == 0)
				{
					++scan_miss;
					goto scan;
				}
				else cout << "Something went wrong! Oh no\n!";
			}
			else
			{
				cout << "Too many errors. Temp manual input in effect\n";
				goto q2;
			}
		}
		else
		{
			goto q2;
		}
		q4:
		if(do_i_have(rank,whos_turn+1) == 1)
		{
			response = yes_no_box("Yes, here you go!\nWas a book made?");
			if(response==1)//yes
			{
				book_made(whos_turn + 1, rank);
			}
			else if (response==-1)
			{
				cout << "Error!\n";
			}
			if(isGameOver() == 1)
			{
				return;
			}
			else
			{
				goto q1;
			}
		}
		else
		{
			cout << "Go Fish!\n";
			goto q5;
		}
	}
	q2:
	cout << "What did player " << whos_turn + 1 << " ask for? Select A, 2-9, T, J, Q, or K:" << endl;
	cin >> input;
	if (input == '1' || input == '0')
	{
		cin.ignore(10000,'\n');
		cout << "Try typing T instead of 10, 1, or 0 please.\n";
		cin >> input;
	}
	if (input == 'a' || input == 'A')
	{
		rank = 0;
	}
	else if (input == 'j' || input == 'J')
	{
		rank = 10;
	}
	else if (input == 'q' || input == 'Q')
	{
		rank = 11;
	}
	else if (input == 'k' || input == 'K')
	{
		rank = 12;
	}
	else if (input == 't' || input == 'T')
	{
		rank = 9;
	}
	else
	{
		rank = input - '1';
	}
	if (man == true)
	{
		goto q4;
	}
	q3:
	cout << "Did the other player have what they wanted?\n";
	cin >> input;//Y or y yes n or N no
		if(input== 89 || input == 121)//yes
		{
			cards[asked_player][rank] = 0;
			cout << "How many did they get?\n";
			cin >> amount;
			cards[whos_turn][rank] += amount;
			cout << "Was a book made?" << endl;
			cin >> input;
			if(input==89 || input==121) //yes
			{
				int player_num = whos_turn + 1;
				book_made(player_num, rank);
				if(isGameOver() == 1)
				book_made(whos_turn,rank);
				if(isGameOver() == 1)
				{
					return;
				}
			}
			goto q1;
		}
		else if(input == 78 || input == 110)//no
		{ 
			q5:
			response = yes_no_box("Go Fish!\nDid player "+to_string(whos_turn+1)+" draw what they were looking for?\n");
			if (response == 1)//yes
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
			goto q1;
			}
			else if(response == 0)//no
			{
				response = yes_no_box("Was a book made?");
				if(response==1) //yes
				{
					int book_rank;
					cout << "Please enter a rank 0-12.\n";
					cin >> book_rank;
					int player_num = whos_turn + 1;
					book_made(player_num, book_rank);
				}
				else if(response==-1)
				{
					cout << "Oh no! Something went wrong. Let's try again.\n";
				}

				if(cards[whos_turn][rank] == 0)
				{
					cards[whos_turn][rank] = 1;
				}
				if(whos_turn == 3)
				{
					whos_turn = 0;
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
				cout << "Oh no! Something went wrong. Let's try again.\n";
				goto q5;
			}
		} 
		else
		{
			cout << "invalid answer\n";
			goto q3;
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
	for (int i = 0; i < 4; ++i)
	{
		if(winner[i] == 1)
		{
			cout << "Player" << (i+1) << " wins\n";
		}
	}
}

int yes_no_box(string question)
{
	int response = 42;
	string command = "./dynbox.sh \"" + question + "\"";
	system(command.c_str());
	ifstream tempfile;
	tempfile.open ("temp");
	tempfile >> response;
	tempfile.close();	
	if (response == 0 || response == 1 || response == -1)
	{
		return response;
	}
	else if (response == 42)
	{
		cout << "Error opening file!\n";
		return -2;
	}
	else return -2;
}

void getcards(int * newhand)
{
	vector<int> cards_in_hand;

	//Obtain source image
	take_pictures("source.jpg");
    	Mat src;
    	src = imread("source.jpg");

	//namedWindow("Source Image", WINDOW_NORMAL);
	//imshow("Source Image", src);
	//resizeWindow("Source Image", WINDOW_WIDTH, WINDOW_HEIGHT);
	//waitKey(0);

    	// Create binary image from source image
    	Mat bw_src;
    	preproccess(src, bw_src);

	//    namedWindow("Binary Image", WINDOW_NORMAL);
	//    imshow("Binary Image", bw_src);
	//    resizeWindow("Binary Image", WINDOW_WIDTH, WINDOW_HEIGHT);
	//    waitKey(0);

	//imwrite("1201_1.tif", bw_src);

    	//Find contours of cards and approximate them as rectangles
	//    vector<vector<Point> > contours;

    	Mat output(Size(450,630), CV_8UC3);
    	
	cards_in_hand = findCardContours(src, bw_src, output);

	//Initialize newhand to zero
	for(int i = 0; i < 13; i++)
	{
		newhand[i] = 0;
	}

	//Output cards to newhand
    	for(int i = 0; i < cards_in_hand.size(); i++)
    	{
        	newhand[cards_in_hand[i]]++;
    	}
}

void card_diff_check(int * currenthand, int * temphand)
{
	for (int i = 0; i < 13; i++)
	{
		temphand[i] = temphand[i] - currenthand[i];
	}
}

int identify_new_card()
{
	int temphand[13];
	getcards(temphand);
	card_diff_check(cards[0],temphand);
	int max = -100;
	int idx_max = -1;
	for (int i = 0; i < 13; i++)
		{
			if (temphand[i] > max)
			{
				max = temphand[i];
				idx_max = i;
			}
		}
return idx_max;
}


string rank_to_str(int rank)
{
	string rank_str;
	if (rank == 0)
	{
		rank_str = "Ace";
	}
	if (rank == 10)
	{
		rank_str = "Jack";
	}
	if (rank == 11)
	{
		rank_str = "Queen";
	}
	if (rank == 12)
	{
		rank_str = "King";
	}
	else rank_str = to_string(rank + 1);
	
	return rank_str;
}

void print_ai_cards()
{
	for (int i = 0; i < 13; i++)
	{
		cout << "I have " << cards[0][i] << " of rank " << i << ".\n";
	}
}
