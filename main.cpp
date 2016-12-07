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

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <set>
#include <map>
#include <cstring>
#include "logic.h"

//#include "take_pictures.h"
//#include "extractcard.h"


//using namespace cv;
using namespace std;



int main()
{/*
take_pictures("source.jpg");
vector<int> cards_in_hand;
    Mat src;                                                                    //Source image
    src = imread("source.jpg");   // Read the file




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
    for(int i = 0; i < cards_in_hand.size(); i++)
    {
        cout << cards_in_hand[i] << "\n";
    }
  









*/
	
	int loop_end = 0;
	char input = ' ';
	int init_card[5] = {0};
	int scan_card = 0;
	int starter = 0;
	srand(time(0));

	choice:
		cout << "Do you want to play in manual mode or camera mode?\n";
		cout << "Please input M or m for manual and C or c for camera.\n";
		cin >> input;
		if(input == 77 || input == 109)//Manual
		{
			cout << "What cards do I have? Input A,2-9,T,J,Q,or K:" << endl;
			for(int i = 1; i < 6; ++i)
			{
				cout << "Input card "<< i << " rank:\n"; // asuming we put in only right inputs
				cin >> input;
				if (input == '1' || input == '0')
				{
					cin.ignore(10000,'\n');
					cout << "Try typing T instead of 10, 1, or 0 please.\n";
					cin >> input;
				}
				if (input == 'a' || input == 'A')
				{
					init_card[i - 1] = 0;
				}
				else if (input == 'j' || input == 'J')
				{
					init_card[i - 1] = 10;
				}
				else if (input == 'q' || input == 'Q')
				{
					init_card[i - 1] = 11;
				}
				else if (input == 'k' || input == 'K')
				{
					init_card[i - 1] = 12;
				}
				else if (input == 't' || input == 'T')
				{
					init_card[i-1] = 9;
				}
				else if (input == '1')
				{
					cin.ignore(10000,'\n');
					cout << "Try typing T instead of 10, you fool! \n";
					cin >> input;
				}
				else
				{
					init_card[i - 1] = input - '1';
				}
			}
			manual = true;
			game_init(init_card[0],init_card[1],init_card[2],init_card[3],init_card[4]);
			if(starter == num_players)
			{
				starter = 0;
				whos_turn += starter;
			}
			else
			{
				whos_turn += starter;
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
		play:
			cout << "It is player " << whos_turn + 1 << "'s turn.\n";
			if (whos_turn == 0)
			{
				do_you_have(); // 1 is a placeholder for cam fun
				if (isGameOver() == 1)
				{
					score_screen();
					loop_end = 1;
					++loop_end;
				}
			}
			else
			{
				other_players_turn();
				if (isGameOver() == 1)
				{
					score_screen();
					loop_end = 1;
				}
			}
			if (whos_turn == num_players)
				whos_turn = 0;
				//other_players_turn(); //1 is placeholder for cam fun
			if (isGameOver() == 1)
			{
				score_screen();
				++loop_end;
			}
			if (whos_turn >= num_players)
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
		input = ' ';
		memset(init_card,0,sizeof(init_card));
		scan_card = 0;
		ai_level = 0;
		manual = false;
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