//cardExtractor.h
//by Jiqing Jiang 161121
//for Go Fish!

#define THRESH 40
#define MAX_THRESH_VALUE 255

#define CANNY_THRESH 100
#define CANNY_MAX_THRESH_VALUE 255


//#define MAX_CARD_AREA 50000.0
//#define MIN_CARD_AREA 10000.0
#define MIN_CARD_CONTOUR_SIZE 10

//#define HIERARCHY_NEXT 0
//#define HIERARCHY_PREV 1
#define HIERARCHY_FIRST_CHILD 2
#define HIERARCHY_PARENT 3

//#define NORMALIZE_CARD_WIDTH 100
//#define NORMALIZE_CARD_HEIGHT 140



#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <map>


using namespace cv;
using namespace std;



typedef struct CardContour
{
    size_t index;
    double area;
    vector<Point> contour;
    Vec4i hierarchy;
} CardContour;




void Hi();


//Create a 3x3 second derivative kernel
//to do do the laplacian filtering
void laplacianFilter(const Mat& src, Mat& imgResult);



//Preproccess given image
void preproccess(const Mat& src, Mat& bw);



//Extract rank of cards
void extractRank(const Mat& cardImg, Mat& bw_rank);


//Recognize cards
void recognition(const Mat& bw_rank);



//Find rectangles(edges) of cards from a preproccessed image
void findCardContours(const Mat& src, const Mat& bw, Mat& output);













