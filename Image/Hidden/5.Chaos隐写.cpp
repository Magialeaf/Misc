#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat Chaos(int row,int col,int key)
{
	Mat hide(row, col, CV_8UC1);
	srand(key);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			hide.at<uchar>(i, j) = rand() % 256;
		}
	return hide;
}

Mat Arnold(Mat img, int re = 0, int a = 1, int b = 1)
{
	int row = img.rows;
	int col = img.cols;
	int para_1, para_2, para_3, para_4;
	if (re == 0)
	{
		para_1 = 1; para_2 = b; para_3 = a; para_4 = a * b + 1;
	}
	else
	{
		para_1 = a * b + 1; para_2 = -b; para_3 = -a; para_4 = 1;
	}
	Mat res(row, col, CV_8UC1);
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < col; y++)
		{
			uchar color = img.at<uchar>(x, y);
			int _x = (para_1 * x + para_2 * y) % row;
			int _y = (para_3 * x + para_4 * y) % row;
			_x = (_x + row) % row;
			_y = (_y + row) % row;
			res.at<uchar>(_x, _y) = color;
		}
	}
	return res;
}

// N 是 Arnold 的次数
void show(int N, int key)
{
	Mat res = imread("img\\Chaos.png", 0);
	int row = res.rows;
	int col = res.cols;
	Mat solve = res;
	Mat hide(row, col, CV_8UC1);

	hide = Chaos(row, col, key);
	solve = solve ^ hide;

	for (int i = 0; i < N; i++)
		solve = Arnold(solve,1);

	imshow("fb", solve);
	waitKey(0);
}

// N 是 Arnold 的次数
void write(int N,int key)
{
	Mat img = imread("img\\shaojiu.jpg", 0);

	int maxs = max({ img.rows, img.cols});
	resize(img, img, Size(maxs, maxs));
	Mat arnold = img;
	Mat hide(maxs, maxs, CV_8UC1);

	for (int i = 0; i < N; i++)
		arnold = Arnold(arnold);

	hide = Chaos(maxs,maxs,key);
	arnold = arnold ^ hide;

	imwrite("img\\Chaos.png", arnold);
}


int main()
{
	int co, N, key;
	srand(12345678);
	cout << "1.write" << "\n" << "2.show" << endl;
	cin >> co;
	cout << "N:";
	cin >> N;
	cout << "Key:";
	cin >> key;
	switch (co)
	{
	case 1:write(N,key); break;
	case 2:show(N,key); break;
	default:cout << "error!" << endl;
	}
	return 0;
}
