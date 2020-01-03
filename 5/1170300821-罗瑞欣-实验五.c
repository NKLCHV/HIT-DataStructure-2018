#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <queue>
#include <fstream>
#define MAX 1000000
typedef int keytype;
using namespace std;
//排序表的数据结构
typedef struct records {
	keytype key;
}LIST[MAX];
LIST A;
clock_t start, stop;
double duration;
//实现交换
void swap(records &x, records &y) {
	records temp;
	temp = x;
	x = y;
	y = temp;
}
//选择排序
void SelectSort(int n, LIST A) {
	keytype lowkey;
	int i, j, lowindex;
	for (i = 1; i < n; i++) {
		lowindex = i;
		lowkey = A[i].key;//标记为第一个
		for (j = i + 1; j <= n; j++) {
			if (A[j].key < lowkey) {
				lowkey = A[j].key;//如果有更大的
				lowindex = j;
			}
		}
		swap(A[i], A[lowindex]);
	}
}
//大数上排
void PushUp(int first, int last) {
	int r = first;
	while (r <= last / 2) {
		if (r == last / 2 && last % 2 == 0) {
			if (A[r].key < A[2 * r].key) {
				swap(A[r], A[2 * r]);
			}
			r = last;
		}
		else if (A[r].key < A[2 * r].key && A[2 * r].key >= A[2 * r + 1].key) {
			swap(A[r], A[2 * r]);//向左比较
			r = 2 * r;
		}
		else if (A[r].key<A[2 * r + 1].key && A[2 * r + 1].key>A[2 * r].key) {
			swap(A[r], A[2 * r + 1]);//向右比较
			r = 2 * r + 1;
		}
		else {
			r = last;
		}
	}
}
//堆排
void HeapSort(int n, LIST A) {
	int i;
	for (i = n / 2; i >= 1; i--) {
		PushUp(i, n);//将数据入堆
	}
	for (i = n; i >= 2; i--) {
		swap(A[1], A[i]);//排序
		PushUp(1, i - 1);
	}
}
int Radix(int k, int p) {
	int power = 1;
	for (int i = 1; i <= p - 1; i++) {
		power = power * 10;
	}
	return (k % (power * 10)) / power;
}

//随机生成A[max]
void CreateNumber(int n) {
	srand(n);
	for (int i = 1; i <= n; i++) {
		A[i].key = rand() % (10 * n);
	}
}
int main(int argc, const char * argv[]) {
	int kkk = 1;
	double kk[100] = { 0 };
	while (kkk <= 100)//循环测试100组数据
	{
		int size, way, num, i = 0;
		int sum = 0, z = 0, haha;
		switch (3) {
		case 1://随机数据
			size = 10000 * (kkk++);
			CreateNumber(size);
			break;
		case 2://顺序数据
			haha = 10000 * (kkk++);
			num = haha;
			for (z = 0; z < num; z++) {
				A[z].key = haha;
				haha = haha - 1;
			}
			size = 10000 * (kkk);
			break;
		case 3://倒序数据
			num = 10000 * (kkk++);
			for (z = 0; z < num; z++) {
				A[z].key = sum;
				sum++;
			}
			size = num;
			break;
		default:
			break;
		}
		cout << "元素已生成成功！共有" << size << "个元素！" << endl;
		ofstream output("A.txt", ios::ate);
		for (int i = 1; i <= size; i++) {
			output << right << setw(10) << A[i].key;
			if (i % 15 == 0) output << endl;
		}
		output << endl << "排序前元素已全部写入！" << endl;
		output.close();
		bool flag = false;
		int times = 0;
		ofstream output3("排序时间.txt", ios::app);
		switch (1) {
		case 1:
			start = clock();//记录时间
			SelectSort(size, A);
			stop = clock();
			break;
		case 2:
			start = clock();//记录时间
			HeapSort(size, A);
			stop = clock();
			break;
		default:
			break;
		}
		duration = (static_cast <double>(stop - start)) / CLK_TCK;
		cout << "共消耗时间" << setprecision(20) << duration << "秒" << endl;
		output3 << setprecision(20) << (int)(duration * 1000) << endl;//将排序时间写入文件
		output.open("A.txt", ios::app);
		for (int i = 1; i <= size; i++) {
			output << right << setw(10) << A[i].key;//将待排序数据写入文件
			if (i % 15 == 0) output << endl;
		}
		output << endl << "排序后元素写入完毕！" << endl;
		output.close();
		ifstream output2; //将待排序数据写入文件
		output2.open("A.txt", ios::in);
		for (int i = 1; i <= size; i++) {
			output2 >> A[i].key;
		}
		output2.close();
	}
	system("pause");
	return 0;
}
