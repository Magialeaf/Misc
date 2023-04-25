#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void show()
{
	Mat res = imread("img\\res.png", 3);
	int row = res.rows;
	int col = res.cols;
	Mat solve(row, col, CV_8UC1);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			Vec3b x = res.at<Vec3b>(i, j);
			solve.at<uchar>(i, j) = (x[0] & 1) * 255;
		}
	imshow("fb", solve);
	waitKey(0);
}


int main()
{
	show();
	return 0;

	Mat img = imread("img\\shaojiu.jpg");
	Mat logo = imread("img\\fb.jpg", 0);
	int img_row = img.rows;
	int img_col = img.cols;
	int fb_row = logo.rows;
	int fb_col = logo.cols;
	int low, change;
	cout << fb_row << " " << fb_col << endl;
	resize(img, img, Size(fb_col, fb_row));
	for (int i = 0; i < fb_row; i++)
	{
		for (int j = 0; j < fb_col; j++)
		{
			low = img.at<Vec3b>(i, j)[0] & 1;
			change = logo.at<uchar>(i, j) > 128;
			if (low != change)
				img.at<Vec3b>(i, j)[0] ^= 1;
		}
	}
	imwrite("img\\res.png", img);
	return 0;
}