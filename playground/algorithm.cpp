//#include <iostream>
//
//using namespace std;
//
////返回第k小的数
//int getKthNumber(int a[], int size, int kth)
//{
//	if (kth > 0 && kth <= size)
//	{
//		int kthNumber = -1;
//		int pivot = -1;
//		int start = 0;
//		int end = size - 1;
//		kth--;//因为下标从0开始，不是从1开始
//
//		while (start<=end)
//		{
//			pivot = partition(a, start, end);
//
//			if (pivot == kth)
//				return a[kth];
//			else if (pivot < kth) //将pivot前的数截掉
//				start = pivot + 1;
//			else//将pivot后的数截掉
//				end = pivot - 1;
//		}
//
//		return kthNumber;
//	}
//}
//
////快排中的切分助手
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

//求图的拓扑排序

#include <iostream>

int main()
{
	return 0;
}