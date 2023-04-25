#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int encode(int i)
{
	int res;
	res = rand() % 3;
	return res;
}

int decode(int i)
{
	return encode(i);
}

void show()
{
	Mat res = imread("img\\three_way.png", 3);
	int row = res.rows;
	int col = res.cols;
	Mat solve(row, col, CV_8UC1);
	int page = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			page = decode(i);
			Vec3b x = res.at<Vec3b>(i, j);
			solve.at<uchar>(i, j) = (x[page] & 1) * 255;
		}
	imshow("fb", solve);
	waitKey(0);
}

void write()
{
	Mat img = imread("img\\kazima.jpg");
	Mat logo = imread("img\\fb.jpg", 0);
	int img_row = img.rows;
	int img_col = img.cols;
	int fb_row = logo.rows;
	int fb_col = logo.cols;
	int low, change;
	resize(img, img, Size(fb_col, fb_row));
	int page = 0;
	for (int i = 0; i < fb_row; i++)
	{
		for (int j = 0; j < fb_col; j++)
		{
			page = encode(i);
			low = img.at<Vec3b>(i, j)[page] & 1;
			change = logo.at<uchar>(i, j) > 128;
			if (low != change)
				img.at<Vec3b>(i, j)[page] ^= 1;
		}
	}
	imwrite("img\\three_way.png", img);
}


int main()
{
	int co;
	srand(12345678);
	cout << "1.write" << "\n" << "2.show" << endl;
	cin >> co;
	switch (co)
	{
	case 1:write(); break;
	case 2:show(); break;
	default:cout << "error!" << endl;
	}
	return 0;
}