//cardExtractor.cpp



//by Jiqing Jiang 161121
//for Go Fish!


#include "extractcard.h"



using namespace cv;
using namespace std;




void Hi()
{
    cout << "Hi" << endl;
}



void laplacianFilter(const Mat& src, Mat& imgResult)
{

    // Create a kernel that we will use for accuting/sharpening our image
    Mat kernel = (Mat_<float>(3,3) <<
            1,  1, 1,
            1, -8, 1,
            1,  1, 1); // an approximation of second derivative, a quite strong kernel
    // do the laplacian filtering as it is
    // well, we need to convert everything in something more deeper then CV_8U
    // because the kernel has some negative values,
    // and we can expect in general to have a Laplacian image with negative values
    // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
    // so the possible negative number will be truncated
    Mat imgLaplacian;
    Mat sharp = src; // copy source image to another temporary one
    filter2D(sharp, imgLaplacian, CV_32F, kernel);
    src.convertTo(sharp, CV_32F);
    
    imgResult = sharp - imgLaplacian;
    // convert back to 8bits gray scale
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
    //imshow( "Laplace Filtered Image", imgLaplacian );
    //waitKey(0);
}

void preproccess(const Mat& src, Mat& bw)
{
    cvtColor(src, bw, CV_BGR2GRAY);
    threshold(bw, bw, THRESH, MAX_THRESH_VALUE, CV_THRESH_BINARY | CV_THRESH_OTSU);
}


void extractRank(const Mat& cardImg, Mat& bw_rank)
{

    Mat subImg=cardImg(Range(20, 95), Range(10, 60));

    preproccess(subImg, bw_rank);


    //For saving templates
    imwrite("extractedRank.tif", bw_rank);
    

imshow("Binary Rank", bw_rank);
waitKey(0);

}




void recognition(const Mat& bw_rank)
{
/*    Mat templateA=imread("ATemp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template2=imread("2Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template3=imread("3Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template4=imread("4Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template5=imread("5Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template6=imread("6Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template7=imread("7Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template8=imread("8Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template9=imread("9Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat template10=imread("10Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat templateJ=imread("JTemp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat templateQ=imread("QTemp.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat templateK=imread("KTemp.tif", CV_LOAD_IMAGE_GRAYSCALE);


    int thresholdA = (double)(templateA.rows * templateA.cols) * 0.7;
    int threshold2 = (double)(template2.rows * template2.cols) * 0.7;
    int threshold3 = (double)(template3.rows * template3.cols) * 0.7;
    int threshold4 = (double)(template4.rows * template4.cols) * 0.7;
    int threshold5 = (double)(template5.rows * template5.cols) * 0.7;
    int threshold6 = (double)(template6.rows * template6.cols) * 0.7;
    int threshold7 = (double)(template7.rows * template7.cols) * 0.7;
    int threshold8 = (double)(template8.rows * template8.cols) * 0.7;
    int threshold9 = (double)(template9.rows * template9.cols) * 0.7;
    int threshold10 = (double)(template10.rows * template10.cols) * 0.7;
    int thresholdJ = (double)(templateJ.rows * templateJ.cols) * 0.7;
    int thresholdQ = (double)(templateQ.rows * templateQ.cols) * 0.7;
    int thresholdK = (double)(templateK.rows * templateK.cols) * 0.7;


    Mat targetImg = bw_rank;

    Mat result(Size(50, 75), CV_8UC3);


    compare(targetImg, templateA, result, CMP_EQ);
    int similarPixels = countNonZero(result);
    
    if (similarPixels > thresholdA)
    {
        cout << "A" << endl;
    }
    else if (similarPixels > threshold2)
    {
        cout << "2" << endl;
    }
    else if (similarPixels > threshold3)
    {
        cout << "3" << endl;
    }
    else if (similarPixels > threshold4)
    {
        cout << "4" << endl;
    }
    else if (similarPixels > threshold5)
    {
        cout << "5" << endl;
    }
    else if (similarPixels > threshold6)
    {
        cout << "6" << endl;
    }
    else if (similarPixels > threshold7)
    {
        cout << "7" << endl;
    }
    else if (similarPixels > threshold8)
    {
        cout << "8" << endl;
    }
    else if (similarPixels > threshold9)
    {
        cout << "9" << endl;
    }
    else if (similarPixels > threshold10)
    {
        cout << "10" << endl;
    }
    else if (similarPixels > thresholdJ)
    {
        cout << "J" << endl;
    }
    else if (similarPixels > thresholdQ)
    {
        cout << "Q" << endl;
    }
    else if (similarPixels > thresholdK)
    {
        cout << "K" << endl;
    }
    else
    {
        cout << "Cannot recognize!" << endl;
    }

*/


//////////////////////////////////// compare similar code



    Mat targetImg=bw_rank;
    Mat templateImg=imread("10Temp.tif", CV_LOAD_IMAGE_GRAYSCALE);



//imshow("b", templateImg);
//waitKey(0);


//cout << targetImg << endl;

//cout << templateImg << endl;


    Mat result(Size(50, 75), CV_8UC3);

//    int threshold = (double)(templateImg.rows * templateImg.cols) * 0.7;

    int threshold = (double)(templateImg.rows * templateImg.cols) * 0.7;

    //compare(targetImg, bw3, result, CMP_EQ);


    compare(targetImg, templateImg, result, CMP_EQ);

//cout << bw3 << endl;



//cout << result << "    " << threshold << endl;

//cout << result.size() << endl;


    int similarPixels = countNonZero(result);

//cout << similarPixels << endl;


    if (similarPixels > threshold)
    {
        cout << "similar" << endl;
 


    }
    else 
        cout << "not similar" << endl;







}
















void findCardContours(const Mat& src, const Mat& bw, Mat& output)
{

    vector<vector<Point> > rects;
    
    int canny_thresh = 100;
    int max_thresh = 255;

    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;                       //hierarchy[Next, Previous, First_Child, Parent]

    /// Detect edges using canny
    Canny( bw, canny_output, canny_thresh, canny_thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

imshow("canny output", canny_output);
waitKey(0);

    map<size_t, CardContour> ccMap;
    
    for(size_t i=0; i<contours.size(); i++)
    {
        vector<Point> contour = contours[i];
        Vec4i contourHierarchy = hierarchy[i];
        // filter by contour size (points)
        if(contourHierarchy[HIERARCHY_FIRST_CHILD] == -1 || contour.size() < MIN_CARD_CONTOUR_SIZE)
        {
            continue;
        }
        // filter by contour area
        double area = contourArea(contour);
        if(area > 105000 || area < 1000)
        {
            continue;
        }

        CardContour cc = {i, area, contour, contourHierarchy};
        ccMap.insert(make_pair(i, cc));
    }

   
    set<size_t> toDel;
    map<size_t, CardContour>::iterator iter1;
    for (iter1 = ccMap.begin(); iter1 != ccMap.end(); ++iter1)
    {
        size_t parentIndex = iter1->second.hierarchy[HIERARCHY_PARENT];
        map<size_t, CardContour>::iterator parent = ccMap.find(parentIndex);
        if(parent!=ccMap.end())
        {
            // found
            double area = iter1->second.area;
            double parentArea = parent->second.area;
            if(area/parentArea > 0.9)
            {
                toDel.insert(parentIndex);
            }
            else
            {
                toDel.insert(iter1->first);
            }
        }
        
    }
    
    set<size_t>::iterator iter2;
    for(iter2 = toDel.begin(); iter2 != toDel.end(); ++iter2)
    {
        ccMap.erase(*iter2);
    }
    
    for (iter1 = ccMap.begin(); iter1 != ccMap.end(); ++iter1)
    {
        rects.push_back(iter1->second.contour);
    }



    double peri;



    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );      //drawing is black now

    for (int i=0; i<rects.size(); i++)
    {
        //Register each card into a rectangular representation.
        //Approximate a polynomial from the contour.
        
        vector<vector<Point> > rects_poly(rects.size());
        peri=arcLength(rects[i], true);
        approxPolyDP( Mat(rects[i]), rects_poly[i], 0.02*peri, true);
        drawContours(drawing,rects_poly,i, Scalar(0,255,0),4,8,hierarchy,0,Point());

imshow("Ouput", drawing);
waitKey(0);

        //Extract cards

        Point2f inputQuad[4];                 //Original corner coordinates
        Point2f inputQuad2[4];                //Transferred corner coordinates
        Point2f outputQuad[4];                //Output corner coordinates

        //Original corner coordinates
        inputQuad[0]=rects_poly[i][0];
        inputQuad[1]=rects_poly[i][1];
        inputQuad[2]=rects_poly[i][2];
        inputQuad[3]=rects_poly[i][3];

        //Initialize final corner coordinates
        Point2f topleft=inputQuad[0];
        Point2f topright=inputQuad[0];
        Point2f botleft=inputQuad[0];
        Point2f botright=inputQuad[0];

        int c_sum, maxSum, minSum, c_diff, maxDiff, minDiff;


        //topleft
        //min(x+y)

        minSum=inputQuad[0].x+inputQuad[0].y;
    
        int topleft_index=0;

        for (int i=0; i<4; i++)
        {
            c_sum=inputQuad[i].x+inputQuad[i].y;
            if (c_sum < minSum)
            {
                minSum=c_sum;
                topleft_index=i;
            }
        }

        //topright
        //max(x-y)

        maxDiff=inputQuad[0].x-inputQuad[0].y;
    

        int topright_index=0;

        for (int i=0; i<4; i++)
        {
            c_diff=inputQuad[i].x-inputQuad[i].y;
            if (c_diff > maxDiff)
            {
                maxDiff=c_diff;
                topright_index=i;
            }
        }


        //botleft
        //min(x-y)

        minDiff=inputQuad[0].x-inputQuad[0].y;
    
        int botleft_index=0;

        for (int i=0; i<4; i++)
        {
            c_diff=inputQuad[i].x-inputQuad[i].y;
            if (c_diff < minDiff)
            {
                minDiff=c_diff;
                botleft_index=i;
            }
        }


        //botright
        //max(x+y)

        maxSum=inputQuad[0].x+inputQuad[0].y;

        int botright_index=0;

        for (int i=0; i<4; i++)
        {
            c_sum=inputQuad[i].x+inputQuad[i].y;
            if (c_sum > maxSum)
            {
                maxSum=c_sum;
                botright_index=i;
            }
        }


        //Compare edges between the interested point

        Point2f edge1, edge2;

        edge1=Vec2f(inputQuad[topleft_index].x, inputQuad[topleft_index].y)-Vec2f(inputQuad[topright_index].x, inputQuad[topright_index].y);
        edge2=Vec2f(inputQuad[topleft_index].x, inputQuad[topleft_index].y)-Vec2f(inputQuad[botleft_index].x, inputQuad[botleft_index].y);

        if (norm(edge1) < norm(edge2))
        {
            inputQuad2[0]=inputQuad[topleft_index];
            inputQuad2[1]=inputQuad[botleft_index];
            inputQuad2[2]=inputQuad[botright_index];
            inputQuad2[3]=inputQuad[topright_index];
        }
    
        else
        {
            inputQuad2[3]=inputQuad[topleft_index];
            inputQuad2[0]=inputQuad[botleft_index];
            inputQuad2[1]=inputQuad[botright_index];
            inputQuad2[2]=inputQuad[topright_index];    
        }



        //Output corner coordinates
        outputQuad[0]= Point2f(0,0);
        outputQuad[1]= Point2f(0,629);
        outputQuad[2]= Point2f(449,629);
        outputQuad[3]= Point2f(449,0);
    
        Mat transform;
        //Mat output(Size(450,630), CV_8UC3);
    
        transform = getPerspectiveTransform(inputQuad2, outputQuad);
        warpPerspective(src, output, transform, output.size());
   
imshow("Output", output);
waitKey(0);


        //Extract bw rank image from the card
        Mat bw_rank;
        extractRank(output, bw_rank);


        //Recognize card
        recognition(bw_rank);

    }
}
















