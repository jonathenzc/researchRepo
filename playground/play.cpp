////#include <iostream>
////#include <vector>
////#include <map>
////#include <algorithm>
////
////using namespace std;
////
////int findinBinary(int *arr, int start, int end,int target,bool &hit)
////{
////	int mid; 
////	while (start != end)
////	{
////		mid = (start + end) / 2;
////		if (target == arr[mid])
////		{
////			hit = true;
////			return mid;
////		}
////		else if (target < arr[mid])
////			end = mid;
////		else
////			start = mid+1;
////	}
////
////	if (arr[start] == target)
////		hit = true;
////	return start;
////}
////
////int main()
////{
////	vector<int> requests;
////	vector<int> pro_start;
////	vector<int> pro_end;
////
////	requests.push_back(6);
////	requests.push_back(5);
////	requests.push_back(2);
////	requests.push_back(3);
////
////	pro_start.push_back(1);
////	pro_start.push_back(4);
////
////	pro_end.push_back(5);
////	pro_end.push_back(6);
////
////	int *requestsArr = new int[requests.size()];
////	//sort requests array
////	for (int i = 0; i < requests.size(); i++)
////		requestsArr[i] = requests[i];
////	sort(requestsArr, requestsArr + requests.size());
////
////	//create hashmap for requests
////	map<int, int> m;
////	for (int i = 0; i < requests.size(); i++)
////		m[requestsArr[i]]=i;
////
////	//count professional
////	int *pro_Cnt = new int[pro_start.size()];
////
////	for (int i = 0; i < pro_start.size(); i++)
////	{
////		int start = 0, end = requests.size()-1;
////		bool isStartFound = false;
////		bool isEndFound = false;
////
////		int pro_start_index = findinBinary(requestsArr, start, end, pro_start[i], isStartFound);
////		int pro_end_index = findinBinary(requestsArr, start, end, pro_end[i], isEndFound);
////		pro_Cnt[i] = pro_end_index-pro_start_index;
////
////		if (!isStartFound && isEndFound)
////			pro_Cnt[i]++;
////	}
////
////	for (int i = 0; i < pro_start.size(); i++)
////		cout << pro_Cnt[i]<<endl;
////	
////	
////	//for (int i = 0; i < 14; i++)
////	//{
////	//	bool a = false;
////	//	cout << i << ": " << findinBinary(requestsArr, 0, requests.size() - 1, i, a) << " " << bool(a) << endl;
////	//}
////
////
////	return 0;
////}
//
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <unordered_map>
//using namespace std;
//
//int findPos(int *arr,int size, int target)
//{
//	for (int i = 0; i < size; i++)
//	{
//		if (arr[i]>target)
//		{
//			if (i == 0)
//				return 0;
//			else
//				return i - 1;
//		}
//	}
//}
//
//struct requestPair
//{
//	int startTime;
//	int endTime;
//};
//
//bool compare(requestPair x, requestPair y)
//{
//	return x.endTime < y.endTime;
//}
//
//int main()
//{
//	vector<int> req_start;
//	vector<int> req_end;
//
//	req_start.push_back(4);
//	req_start.push_back(1);
//	req_start.push_back(5);
//	req_start.push_back(6);
//
//	req_end.push_back(5);
//	req_end.push_back(4);
//	req_end.push_back(7);
//	req_end.push_back(8);
//
//	//map is not a data structure on our demand because if we set end as a key, it will ignore the requests which the end time are the same but start time is different.
//	//so we choose end and start as the key
//	vector<requestPair> v;
//	
//	for (int i = 0; i < req_start.size(); i++)
//	{
//		requestPair r;
//		r.endTime = req_end[i];
//		r.startTime = req_start[i];
//
//		v.push_back(r);
//	}
//
//	sort(v.begin(),v.end(),compare);
//
//	//get sorted request end arry
//	int *sortedEndArr = new int[req_start.size()+1];
//	int endArrIndex = 0;
//
//	for (int i=0; i<v.size(); i++)
//		sortedEndArr[endArrIndex++] = v[i].endTime;
//
//	unordered_map<int, int> max_req;
//	int maxRequest=0;
//
//	//max_req[sortedEndArr[0]] = 0;
//
//	for (int i=0; i < v.size(); i++)
//	{
//		int pos = findPos(sortedEndArr, req_start.size(), v[i].startTime);
//		if (maxRequest <= max_req[sortedEndArr[pos]] + 1)
//			max_req[v[i].endTime] = max_req[sortedEndArr[pos]] + 1;
//		else
//			max_req[v[i].endTime] = maxRequest;
//
//		maxRequest = max_req[v[i].endTime];
//	}
//
//	//unordered_map<int, int>::iterator iter;
//	//for (iter = max_req.begin(); iter != max_req.end(); iter++)
//	//	cout << iter->first<<" "<<iter->second<<endl;
//
//	cout << maxRequest;
//
//	return 0;
//}

//#include <iostream>
//#include <string>
//#include <vector>
//#include <map>
//
//using namespace std;
//
//struct letterTree
//{
//	char letter;
//	int namesIndex;
//	char minChar;
//	map < char, letterTree* > m;
//};
//
//char tolower(char c)
//{
//	if (c >= 'A' && c <= 'Z')
//		c += 32;
//
//	return c;
//}
//
//void typeahead(vector<string> usernames, vector<string> queries)
//{
//	//build a letter tree
//	letterTree *root = new letterTree;
//	root->minChar = ' ';
//
//	for (int i = 0; i < usernames.size(); i++)
//	{
//		letterTree *node = root;
//		for (int nameI = 0; nameI < usernames[i].size(); nameI++)
//		{
//			char c = usernames[i][nameI];
//			if (node->m.find(c) == node->m.end())//not found
//			{
//				letterTree *treeNode = new letterTree;
//				treeNode->minChar = ' ';
//				node->letter = c;
//				node->m[c] = treeNode;
//
//				if (node->minChar == ' ' || tolower(c) < node->minChar)
//				{
//					node->minChar = c;
//					node->namesIndex = i;
//				}
//			}
//
//			node = node->m[c];
//		}
//	}
//
//	for (int i = 0; i < queries.size(); i++)
//	{
//		letterTree *node = root;
//		int index = -1;
//		for (int queriesI = 0; queriesI < queries[i].size(); queriesI++)
//		{
//			char c = queries[i][queriesI];
//			//it must find it
//			node = node->m[c];
//			index = node->namesIndex;
//		}
//
//		cout << usernames[index]<<endl;
//	}
//
//}
//
//int main()
//{
//	vector<string> usernames;
//	vector<string> queries;
//
//	usernames.push_back("james");
//	usernames.push_back("jBlank");
//
//	queries.push_back("j");
//	queries.push_back("jm");
//	queries.push_back("jbl");
//	queries.push_back("JB");
//
//	typeahead(usernames, queries);
//
//	return 0;
//}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int **cm;
int *shortLength;

int countIntersection(const vector<string> &cm)
{

}

void buildCity(const vector<string> &cm)
{}

void dijkstra(int source)
{}

void find_closest_car(const vector<string> &city_map, const vector<int> &cars, int customer)
{
	//get the number of intersection
	int cnt_intersection = countIntersection(city_map);

	//building city map with adjacency matrix
	buildCity(city_map);

	//all pairs shortest paths
	dijkstra(customer);

	//find the closest car
	int min = 10000;
	int carIndex = 0;
	for (int i = 0; i < cars.size(); i++)
	{
		if (cm[customer][cars[i]] < min)
		{
			min = cm[customer][cars[i]];
			carIndex = i;
		}
	}

	cout << carIndex + 1;
}

int main()
{
	vector<string> cm;
	cm.push_back("1,2,1");
	cm.push_back("2,3,2");
	cm.push_back("1,3,1");
	cm.push_back("3,4,1");

	vector<int> cars;
	cars.push_back(2);
	cars.push_back(1);

	int customer;

	find_closest_car(cm,cars,customer);

	return 0;
}