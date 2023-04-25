#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Calc_gradient()
{
	Mat img = imread("img\\shaojiu.jpg", 0);
	int row = img.rows;
	int col = img.cols;
	Mat res(row, col, CV_8UC1);
	for (int i = 1; i < row; i++)
		for (int j = 1; j < col; j++)
			// res.at<uchar>(i, j) = ((img.at<uchar>(i, j) - img.at<uchar>(i - 1, j)) > 10) * 255; // 上梯度 col = 0;
			res.at<uchar>(i, j) = (((img.at<uchar>(i, j) - img.at<uchar>(i - 1, j)) + (img.at<uchar>(i, j) - img.at<uchar>(i, j - 1))) > 10) * 255; // 上左梯度 col = 1;
	imwrite("img\\texture.png", res);
	imshow("Original",img);
	imshow("texture",res);
	waitKey(0);

}

int main()
{
	Calc_gradient();
	return 0;
}
