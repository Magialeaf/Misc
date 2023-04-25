#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Watermark(int x,int y,double a)
{
	Mat img = imread("img\\kazima.jpg", 3);
	Mat logo = imread("img\\watermark.png", 3);
	int img_row = img.rows;
	int img_col = img.cols;
	int logo_row = logo.rows;
	int logo_col = logo.cols;
	for (int i = 0; i < logo_row; i++)
	{
		for (int j = 0; j < logo_col; j++)
		{
			int tx = i + x;
			int ty = j + y;
			if (tx < img_row && ty < img_col)
			{
				Vec3b img_c = img.at<Vec3b>(tx, ty);
				Vec3b logo_c = logo.at<Vec3b>(i, j);
				Vec3b c = img_c * a + logo_c * (1 - a);
				img.at<Vec3b>(tx, ty) = c;
			}
		}
	}
	imshow("fusion", img);
	imwrite("img\\fusion.png", img);
	waitKey(0);
}


int main()
{
	int x, y;
	double a;
	cout << "坐标x和y,透明度a：";
	cin >> x >> y >> a;
	Watermark(x, y, a);
}
