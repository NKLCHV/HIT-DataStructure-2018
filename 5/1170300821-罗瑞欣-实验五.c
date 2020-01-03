#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <queue>
#include <fstream>
#define MAX 1000000
typedef int keytype;
using namespace std;
//���������ݽṹ
typedef struct records {
	keytype key;
}LIST[MAX];
LIST A;
clock_t start, stop;
double duration;
//ʵ�ֽ���
void swap(records &x, records &y) {
	records temp;
	temp = x;
	x = y;
	y = temp;
}
//ѡ������
void SelectSort(int n, LIST A) {
	keytype lowkey;
	int i, j, lowindex;
	for (i = 1; i < n; i++) {
		lowindex = i;
		lowkey = A[i].key;//���Ϊ��һ��
		for (j = i + 1; j <= n; j++) {
			if (A[j].key < lowkey) {
				lowkey = A[j].key;//����и����
				lowindex = j;
			}
		}
		swap(A[i], A[lowindex]);
	}
}
//��������
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
			swap(A[r], A[2 * r]);//����Ƚ�
			r = 2 * r;
		}
		else if (A[r].key<A[2 * r + 1].key && A[2 * r + 1].key>A[2 * r].key) {
			swap(A[r], A[2 * r + 1]);//���ұȽ�
			r = 2 * r + 1;
		}
		else {
			r = last;
		}
	}
}
//����
void HeapSort(int n, LIST A) {
	int i;
	for (i = n / 2; i >= 1; i--) {
		PushUp(i, n);//���������
	}
	for (i = n; i >= 2; i--) {
		swap(A[1], A[i]);//����
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

//�������A[max]
void CreateNumber(int n) {
	srand(n);
	for (int i = 1; i <= n; i++) {
		A[i].key = rand() % (10 * n);
	}
}
int main(int argc, const char * argv[]) {
	int kkk = 1;
	double kk[100] = { 0 };
	while (kkk <= 100)//ѭ������100������
	{
		int size, way, num, i = 0;
		int sum = 0, z = 0, haha;
		switch (3) {
		case 1://�������
			size = 10000 * (kkk++);
			CreateNumber(size);
			break;
		case 2://˳������
			haha = 10000 * (kkk++);
			num = haha;
			for (z = 0; z < num; z++) {
				A[z].key = haha;
				haha = haha - 1;
			}
			size = 10000 * (kkk);
			break;
		case 3://��������
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
		cout << "Ԫ�������ɳɹ�������" << size << "��Ԫ�أ�" << endl;
		ofstream output("A.txt", ios::ate);
		for (int i = 1; i <= size; i++) {
			output << right << setw(10) << A[i].key;
			if (i % 15 == 0) output << endl;
		}
		output << endl << "����ǰԪ����ȫ��д�룡" << endl;
		output.close();
		bool flag = false;
		int times = 0;
		ofstream output3("����ʱ��.txt", ios::app);
		switch (1) {
		case 1:
			start = clock();//��¼ʱ��
			SelectSort(size, A);
			stop = clock();
			break;
		case 2:
			start = clock();//��¼ʱ��
			HeapSort(size, A);
			stop = clock();
			break;
		default:
			break;
		}
		duration = (static_cast <double>(stop - start)) / CLK_TCK;
		cout << "������ʱ��" << setprecision(20) << duration << "��" << endl;
		output3 << setprecision(20) << (int)(duration * 1000) << endl;//������ʱ��д���ļ�
		output.open("A.txt", ios::app);
		for (int i = 1; i <= size; i++) {
			output << right << setw(10) << A[i].key;//������������д���ļ�
			if (i % 15 == 0) output << endl;
		}
		output << endl << "�����Ԫ��д����ϣ�" << endl;
		output.close();
		ifstream output2; //������������д���ļ�
		output2.open("A.txt", ios::in);
		for (int i = 1; i <= size; i++) {
			output2 >> A[i].key;
		}
		output2.close();
	}
	system("pause");
	return 0;
}
