//#include <iostream>
//
//using namespace std;
//
////���ص�kС����
//int getKthNumber(int a[], int size, int kth)
//{
//	if (kth > 0 && kth <= size)
//	{
//		int kthNumber = -1;
//		int pivot = -1;
//		int start = 0;
//		int end = size - 1;
//		kth--;//��Ϊ�±��0��ʼ�����Ǵ�1��ʼ
//
//		while (start<=end)
//		{
//			pivot = partition(a, start, end);
//
//			if (pivot == kth)
//				return a[kth];
//			else if (pivot < kth) //��pivotǰ�����ص�
//				start = pivot + 1;
//			else//��pivot������ص�
//				end = pivot - 1;
//		}
//
//		return kthNumber;
//	}
//}
//
////�����е��з�����
//int partition(int a[],int start,int end)
//{
//	int target = a[start];
//	int i = start;
//	int j = end;
//
//	while (start <= end)
//	{
//		while (j >= start && a[j] >= target)
//			j--;
//
//		a[]
//
//	}
//}
//
//int main()
//{
//	int a[6] = {34,12,23,67,45,78};
//
//	cout << "3rd: " << getKthNumber(a, 6, 3) << endl
//		<< "4th; " << getKthNumber(a,6,4) << endl;
//
//
//	return 0;
//}

//��ͼ����������

#include <iostream>

int main()
{
	return 0;
}