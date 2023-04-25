#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void show()
{
	Mat res = imread("res.png", 0);
	int row = res.rows;
	int col = res.cols;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			res.at<uchar>(i, j) &= 1;
			res.at<uchar>(i, j) *= 255;
		}
	imshow("res", res);
	waitKey(0);
}


int main()
{
	Mat img = imread("shaojiu.jpg", 0);
	Mat logo = imread("logo.png", 0);
	int row = logo.rows;
	int col = logo.cols;
	int low,change;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			low = img.at<uchar>(i, j) & 1;
			change = logo.at<uchar>(i, j) > 128;
			if (low != change)
				img.at<uchar>(i, j) ^= 1;
		}
		cout << endl;
	}
	imwrite("res.png",img);
	show();
	return 0;
}