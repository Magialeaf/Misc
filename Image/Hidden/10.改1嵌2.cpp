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
	for (int i = 0; i < 8; i++)
		key_bin.push_back(0);
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

void calc_Matrix(int &a1, int& a2, int& a3, int x1, int x2)
{
	int p1 = a1 ^ a3, p2 = a2 ^ a3;
	if ((p1 == x1) && (p2 == x2));
	else if ((p1 != x1) && (p2 == x2))
		a1 ^= 1;
	else if ((p1 == x1) && (p2 != x2))
		a2 ^= 1;
	else if ((p1 != x1) && (p2 != x2))
		a3 ^= 1;
}

void Decode(int len)
{
	vector<int> lowest,key_bin;
	Mat res = imread("img\\Matrix_1to2.png", 0);
	int row = res.rows;
	int col = res.cols;
	int str_len = len / 2 * 3;
	str_len = str_len + (24 - (str_len + 24) % 24);
	int p = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (p >= (str_len))
				goto out;
			lowest.push_back(res.at<uchar>(i, j) & 1);
			p++;
		}
out:
	p = 0;
	for (int i = 0; i < lowest.size(); i += 3)
	{
		int a1 = lowest[i],a2 = lowest[i + 1], a3 = lowest[i + 2];
		int x1 = a1 ^ a3;
		int x2 = a2 ^ a3;
		key_bin.push_back(x1);
		key_bin.push_back(x2);
		p += 2;
	}
	string key = BinToStr(key_bin);
	for (int i = 0; i < key.size(); i++) //手动截断
		if (key[i] == 0)
			break;
		else
			cout << key[i];
}

void Encode(string key)
{
	vector<int> lowest,key_bin;
	key_bin = StrToBin(key);
	Mat img = imread("img\\shaojiu.jpg", 0);
	int row = img.rows;
	int col = img.cols;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			lowest.push_back(img.at<uchar>(i, j) & 1);
		}

	int p = 0;
	for (int i = 0; i < key_bin.size(); i+=2)
	{
		int x1 = key_bin[i], x2 = key_bin[i + 1];
		int& a1 = lowest[p], &a2 = lowest[p + 1], &a3 = lowest[p + 2];
		calc_Matrix(a1, a2, a3, x1, x2);
		p += 3;
	}
	p = 0;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < col; j++)
		{
			if (p > (key_bin.size() / 2 * 3))
				goto out;
			uchar& c = img.at<uchar>(i, j);
			c -= c & 1;
			c += lowest[p];
			p++;
		}
out:
	imwrite("img\\Matrix_1to2.png", img);
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
