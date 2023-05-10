#include<iostream>
#include<opencv2/opencv.hpp>

const int K = 3, LEN_A = (1 << K) - 1,UNIT = LEN_A * 8;
/*
#define K 3
#define LEN_A (1<<K)-1
#define UNIT LEN_A * 8
不能define，不然会算出奇怪的结果
*/


using namespace cv;
using namespace std;

vector<int> StrToBin(string key)
{
	vector<int> key_bin;
	for (int i = 0; i < key.size(); i++)
	{
		int x = key[i];
		for (int j = 0; j < 8; j++)
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
			temp = temp * 2 + key_bin[i + j];
		}
		key += temp;
	}
	return key;
}

int EnMatrixCode(vector<int> a, vector<int> x)
{
	int n = a.size(), m = x.size();
	
	assert(n == (1 << m) - 1); // n == 2 ^ m - 1

	int fa = 0;
	for (int i = 1; i <= n; i++)
		fa ^= (a[i - 1] * i);
	int xx = 0;
	for (int i = 0; i < m; i++)
		xx += x[i] * (1 << i);
	return fa ^ xx;
}

vector<int> DeMatrix(vector<int> a)
{
	int n = a.size();
	int m = log2(n + 1);

	vector<int> x;
	int fa = 0;
	for (int i = 1; i <= n; i++)
		fa ^= (a[i - 1] * i);
	for (int i = 1; i <= m; i++)
	{
		x.push_back(fa % 2);
		fa /= 2;
	}
	return x;
}

void Decode(int len)
{
	vector<int> lowest, key_bin;
	Mat res = imread("img\\Matrix_1ton.png", 0);
	int row = res.rows;
	int col = res.cols;
	int str_len = (len / K * LEN_A);
	str_len = str_len + (str_len - (str_len + 56) % 56);
	// 读取最低位
	for (int i = 0,p = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (p >= (str_len))
				goto out;
			lowest.push_back(res.at<uchar>(i, j) & 1);
			p++;
		}
out:
	// 最低位修改
	for (int i = 0; i < lowest.size(); i += LEN_A)
	{
		vector<int>a, x;
		for (int j = 0; j < LEN_A; j++)
		{
			a.push_back(lowest[i + j]);
		}
		x = DeMatrix(a);
		for (auto& xx : x)
			key_bin.push_back(xx);
	}
	//输出
	string key = BinToStr(key_bin);
	for (int i = 0; i < key.size(); i++) //手动截断
		if (key[i] == 0)
			break;
		else
			cout << key[i];
}

void Encode(string key)
{
	vector<int> lowest, key_bin;
	key_bin = StrToBin(key);
	Mat img = imread("img\\shaojiu.jpg", 0);
	int row = img.rows;
	int col = img.cols;
	// 读取最低位
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			lowest.push_back(img.at<uchar>(i, j) & 1);
		}
	// 最低位修改
	for (int i = 0, p = 0; i < key_bin.size(); i += K, p += LEN_A)
	{
		vector<int> x,a;
		for (int j = 0; j < K; j++)
		{
			if (i + j < key_bin.size())
				x.push_back(key_bin[i + j]);
			else
				x.push_back(0);  //防溢出
		}		
		for (int j = 0; j < LEN_A; j++)
			a.push_back(lowest[p + j]);
		int s = EnMatrixCode(a, x);
		if (s != 0)
			lowest[p + s - 1] ^= 1;
	}
	// 嵌入
	int p = 0;
	for (int i = 0; i < K; i++)
		for (int j = 0; j < col; j++)
		{
			if (p > (key_bin.size() / K * LEN_A))
				goto out;
			uchar& c = img.at<uchar>(i, j);
			c -= c & 1;
			c += lowest[p];
			p++;
		}
out:
	imwrite("img\\Matrix_1ton.png", img);
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
