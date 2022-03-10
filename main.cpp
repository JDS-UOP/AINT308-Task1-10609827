//James Rogers Jan 2022 (c) Plymouth University
//Student ID: 10609827
#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/opencv_modules.hpp>

using namespace std;
using namespace cv;

int main(){

    //Path of image folder
    string PathToFolder = "../Task1/Car Images/";

    //Loop through the 30 car images
    for(int n = 0; n < 30; ++n){

        //Each image is named 0.png, 1.png, 2.png, etc. So generate the image file path based on n and the folder path
        string PathToImage = PathToFolder+to_string(n)+".png";

        cout << PathToImage << endl;

        //Load car image at the file paths location
        Mat Car = imread(PathToImage);

        //Normalise image
        normalize(Car, Car, 0, 255, NORM_MINMAX, CV_8UC3);

        //Establish colour counters for entire image/rectangle
        int blueCounter = 0, greenCounter = 0, redCounter = 0;
        int blueCounterRect = 0, greenCounterRect = 0, redCounterRect = 0;

        /// Two methods have been used for RGB colour detection.
        /// Method 1 examines the pixels in the entire image.
        /// Method 2 examines the pixels in a select area, highlighted by a rectangle.

        /// Method 1 ///
        //Nested for-loops to process each individual pixel in the entire image
        for(int y=0; y<Car.size().height; y++){
            for(int x=0; x<Car.size().width; x++){
                Vec3b PixelValue = Car.at<Vec3b>(y,x); //Read colour values of pixel (BGR)
                if ((int)PixelValue[0] > (int)PixelValue[1] && (int)PixelValue[0] > (int)PixelValue[2]){
                    blueCounter++;
                }
                else if ((int)PixelValue[1] > (int)PixelValue[0] && (int)PixelValue[1] > (int)PixelValue[2]){
                    greenCounter++;
                }
                else if ((int)PixelValue[2] > (int)PixelValue[0] && (int)PixelValue[2] > (int)PixelValue[1]){
                    redCounter++;
                }
            }
        }

        /// Method 2 ///
        //Nested for-loops to process each individual pixel in the specified rectangular area
        for(int y=160; y<260; y++){ //x and y values initialised for specific area
            for(int x=220; x<420; x++){
                rectangle(Car, Rect(220, 160, 200, 100), Scalar(0, 0, 0), 4); //Draw rectangle to highlight specified area
                Vec3b PixelValue = Car.at<Vec3b>(y,x); //Read colour values of pixel (BGR)
                if ((int)PixelValue[0] > (int)PixelValue[1] && (int)PixelValue[0] > (int)PixelValue[2]){
                    blueCounterRect++;
                }
                else if ((int)PixelValue[1] > (int)PixelValue[0] && (int)PixelValue[1] > (int)PixelValue[2]){
                    greenCounterRect++;
                }
                else if ((int)PixelValue[2] > (int)PixelValue[0] && (int)PixelValue[2] > (int)PixelValue[1]){
                    redCounterRect++;
                }
            }
        }

        //Print colour counter values, then use largest value to determine likely car colour
        cout << "Method 1 (Full Image)  -> Blue Pixels: " << blueCounter << ", Green Pixels: " << greenCounter << ", Red Pixels: " << redCounter << "." << endl;

        if (blueCounter > greenCounter && blueCounter > redCounter){
            cout << "Method 1: The car is blue." << endl;
        }
        else if (greenCounter > blueCounter && greenCounter > redCounter){
            cout << "Method 1: The car is green." << endl;
        }
        else
            cout << "Method 1: The car is red." << endl;

        cout << "Method 2 (Center Area) -> Blue Pixels: " << blueCounterRect << ", Green Pixels: " << greenCounterRect << ", Red Pixels: " << redCounterRect << "." << endl;

        if (blueCounterRect > greenCounterRect && blueCounterRect > redCounterRect){
            cout << "Method 2: The car is blue." << endl;
        }
        else if (greenCounterRect > blueCounterRect && greenCounterRect > redCounterRect){
            cout << "Method 2: The car is green." << endl;
        }
        else
            cout << "Method 2: The car is red." << endl;

        /// RESULTS
        /// Method 1: 23/30 = 76% Correct
        /// Method 2: 29/30 = 96% Correct

        ////////// Additional Image Display //////////

        //Create Mats
        Mat CarHSV, redMask, blueMask, greenMask;

        //Convert to HSV format
        cvtColor(Car, CarHSV, COLOR_BGR2HSV);

        //HSV Ranges for Red, Blue and Green
        Scalar lower_red(0, 150, 50);
        Scalar upper_red(10, 255, 255);
        Scalar lower_green(45, 150, 50);
        Scalar upper_green(65, 255, 255);
        Scalar lower_blue(115, 150, 0);
        Scalar upper_blue(125, 255, 255);

        //Assign upper and lower thresholds for each colour
        inRange(CarHSV, lower_red, upper_red, redMask);
        inRange(CarHSV, lower_blue, upper_blue, blueMask);
        inRange(CarHSV, lower_green, upper_green, greenMask);

        //Display car images until x is pressed
        while(waitKey(10)!='x'){

            imshow("Car", Car);
            imshow("CarHSV", CarHSV);
            imshow("redMask", redMask);
            imshow("blueMask", blueMask);
            imshow("greenMask", greenMask);
        }

    }

}
