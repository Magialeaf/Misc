//#include<iostream>
//#include<opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//
//Mat Arnold(Mat img, int re = 0, int a = 2,int b = 4)
//{
//	int row = img.rows;
//	int col = img.cols;
//	int para_1,para_2,para_3,para_4;
//	if (re == 0)
//	{
//		para_1 = 1; para_2 = b; para_3 = a; para_4 = a * b + 1;
//	}
//	else
//	{
//		para_1 = a * b + 1; para_2 = -b; para_3 = -a; para_4 = 1;
//	}
//	Mat res(row, col, CV_8UC1);
//	for (int x = 0; x < row; x++)
//	{
//		for (int y = 0; y < col; y++)
//		{
//			uchar color = img.at<uchar>(x, y);
//			int _x = (para_1 * x + para_2 * y) % row;
//			int _y = (para_3 * x + para_4 * y) % row;
//			_x = (_x + row) % row;
//			_y = (_y + row) % row;
//			res.at<uchar>(_x, _y) = color;
//		}
//	}
//	return res;
//}
//
//// N 是 Arnold 的次数
//void show(int N)
//{
//	Mat res = imread("img\\Arnold.png", 3);
//	int row = res.rows;
//	int col = res.cols;
//	Mat solve(row, col, CV_8UC1);
//
//	for (int i = 0; i < row; i++)
//		for (int j = 0; j < col; j++)
//		{
//			int page = i % 3;
//			Vec3b x = res.at<Vec3b>(i, j);
//			solve.at<uchar>(i, j) = (x[page] & 1) * 255;
//		}
//
//	for (int i = 0; i < N; i++)
//		solve = Arnold(solve,1);
//
//	imshow("fb", solve);
//	imwrite("img\\solve.png", solve);
//	waitKey(0);
//}
//
//// N 是 Arnold 的次数
//void write(int N)
//{
//	Mat img = imread("img\\kazima.jpg");
//	Mat logo = imread("img\\fb.jpg", 0);
//
//	int maxs = max({ logo.rows, logo.cols, img.rows, img.cols });
//	resize(img, img, Size(maxs,maxs));
//	resize(logo, logo , Size(maxs, maxs));
//	Mat arnold = logo;
//
//	for (int i = 0; i < N; i++)
//		arnold = Arnold(arnold);
//
//	for (int i = 0; i < maxs; i++)
//	{
//		for (int j = 0; j < maxs; j++)
//		{
//			int page = i % 3;
//			int low = img.at<Vec3b>(i, j)[page] & 1;
//			int change = arnold.at<uchar>(i, j) > 128;
//			if (low != change)
//				img.at<Vec3b>(i, j)[page] ^= 1;
//		}
//	}
//
//	imwrite("img\\Arnold.png", img);
//}
//
//
//int main()
//{
//	int co,N;
//	srand(12345678);
//	cout << "1.write" << "\n" << "2.show" << endl;
//	cin >> co;
//	cout << "N:";
//	cin >> N;
//	switch (co)
//	{
//	case 1:write(N); break;
//	case 2:show(N); break;
//	default:cout << "error!" << endl;
//	}
//	return 0;
//}