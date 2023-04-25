#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int a1 = 1,a2 = 0,a3 = 1;
void insert(int x1, int x2)
{
	if (((a1 ^ a3) == x1) && ((a2 ^ a3) == x2));
	else if (((a1 ^ a3) != x1) && ((a2 ^ a3) == x2))
		a1 = !a1;
	else if (((a1 ^ a3) == x1) && ((a2 ^ a3) != x2))
		a2 = !a2;
	else if (((a1 ^ a3) != x1) && ((a2 ^ a3) != x2))
		a3 = !a3;
}

void getValue()
{
	int x1, x2;
	x1 = a1 ^ a3;
	x2 = a2 ^ a3;
	cout << "x1 = " << x1 << " x2 = " << x2 << endl;
}

int main()
{
	int co, x1,x2;
	do
	{
		cout << "a1 = " << a1 << " a2 = " << a2 << " a3 = " << a3 << endl;
		cout << "1.insert()  2.getValue()  0.exit()\ninput:";
		cin >> co;
		switch (co)
		{
		case 1:cout << "x1 x2:"; cin >> x1 >> x2; insert(x1, x2); break;
		case 2:getValue(); break;
		case 0:break;
		default:cout << "Error input!" << endl;
		}
	} while (co != 0);
	return 0;
}
