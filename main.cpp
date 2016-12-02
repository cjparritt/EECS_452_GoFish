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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <set>
#include <map>

#include "global.h"

#include "extractcard.h"

#include "take_pictures.h"

#include "logic.h"
#include <iostream>
#include <iomanip>



using namespace cv;
using namespace std;



int main()
{
/*

    if( argc != 2)
    {
        cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
        return -1;
    }
    
    Mat src;                                                                    //Source image
    src = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
    
    if(! src.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }



   
    Mat src;                                                                    //Source image
    src = imread("test.jpg");   // Read the file


Hi();

    imshow("Source Image", src);
    //waitKey(0);


    // Create binary image from source image
    Mat bw_src;
    preproccess(src, bw_src);
    imshow("Binary Image", bw_src);
    waitKey(0);




    //Find contours of cards and approximate them as rectangles
    vector<vector<Point> > contours;

    Mat output(Size(450,630), CV_8UC3);
    findCardContours(src, bw_src, output);
    
  










    printf("Hello World!\n");
    return 0;
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
			for(int i = 1; i < 6; ++i)
			{
				cout << "Input card "<< i << " rank\n"; // asuming we put in only right inputs TODO: add period
				cin >> input;
				init_card[i-1] = input - '0';
			}
			manual = true;
			game_init(init_card[0],init_card[1],init_card[2],init_card[3],init_card[4]);
			if(starter == 4)
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
		play://TODO:Need to add functions
		if (whos_turn == 0)
		{
<<<<<<< HEAD
			do_you_have();
			if(isGameOver(books_made) == 1)
=======
			do_you_have(man_switch);
			if(isGameOver() == 1)
>>>>>>> parent of 5c39234... Finished Main Logic
			{
				score_screen();
				
			}
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