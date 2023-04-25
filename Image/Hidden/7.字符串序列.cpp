#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

vector<int> StrToBin(string key)
{
	vector<int> key_bin;
	for (int i = 0; i < key.size(); i++)
	{
		int x = key[i];
		for (int j =0; j < 8; j++)
		{
			int num = ((x & (1 << (7 - j))) > 0);
			key_bin.push_back(num);
		}
	}
	return key_bin;
}

string BinToStr(vector<int> key_bin)
{
	string key;
	for (int i = 0; i < key_bin.size(); i += 8)
	{
		int temp = 0;
		for (int j = 0; j < 8; j++) 
		{
			temp = temp * 2 + key_bin[i+j];
		}
		key += temp;
	}
	return key;
}

void Decode(int len)
{
	vector<int> key_bin;
	Mat res = imread("img\\Integer.png", 0);
	int row = res.rows;
	int col = res.cols;
	int p = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (p >= len) break;
			int c = res.at<uchar>(i, j) & 1;
			key_bin.push_back(c);
			p++;
		}
	string key = BinToStr(key_bin);
	cout << key << endl;
}

void Encode(string key)
{
	vector<int> key_bin;
	Mat img = imread("img\\shaojiu.jpg", 0);
	int row = img.rows;
	int col = img.cols;
	key_bin = StrToBin(key);
	int p = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (p >= key_bin.size()) break;
			int b = key_bin[p];
			int c = img.at<uchar>(i, j);
			c = c - (c & 1);
			c |= b;
			img.at<uchar>(i, j) = c;
			p++;
		}
	imwrite("img\\Integer.png", img);
	cout << key_bin.size() << endl;
}


int main()
{
	int co, len;
	string key;
	cout << "1.Encode" << "\t" << "2.Decode" << "\n::";
	cin >> co;
	switch (co)
	{
	case 1:	
		cout << "Enter the string you want to hide:";
		cin.ignore(); getline(cin, key); Encode(key);
		break;
	case 2:
		cout << "Enter key length:";
		cin >> len; Decode(len); break;
	default:cout << "error!" << endl;
	}
	return 0;
}
