// BNGU_OpenCV.cpp: 定义应用程序的入口点。
//
#include<opencv2/opencv.hpp>
#include "ColourDivision.h"

using namespace std;
using namespace cv;

int readPhotoAndFliter(cv::String location) {
	Mat image_bgr = imread(location);
	if (image_bgr.empty()) {
		cout << "Failed to load!" << endl;
		return -1;
	}

	Mat image_hsv;
	cvtColor(image_bgr, image_hsv, COLOR_BGR2HSV);
	vector<Mat> channels;
	split(image_hsv, channels);

	Mat mask_h, mask_s, mask_v;
	inRange(channels[0], 60, 255, mask_h);
	inRange(channels[1], 80, 255, mask_s);
	inRange(channels[2], 50, 255, mask_v);

	Mat mask_h_and_s;
	bitwise_and(mask_h, mask_s, mask_h_and_s);
	Mat mask;
	bitwise_and(mask_h_and_s, mask_v, mask);

	Mat out_image;
	bitwise_and(image_bgr, image_bgr, out_image, mask);
	imshow("Display Image", out_image);
	waitKey(0);
}
