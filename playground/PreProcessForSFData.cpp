////该文件是对SF数据的预处理文件
//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//#include <map>
//
//using namespace std;
//
//string fileNameArray[92];//储存文件名称的数组
//string proDir = "D:\\VariousWorkspace\\C++Workspace\\playground\\playground\\";//项目地址，为了之后保存处理后的数据的目录
//
//struct TeamInfo
//{
//	string userID; //登录名
//	string position; //职位、角色
//
//	TeamInfo(string uID, string pos)
//		:userID(uID), position(pos)
//	{}
//};
//
////团队映射表,键为团队名称,值为团队索引；
//map<string, int> teamMap;
//
////团队与该团队下开发人员信息的映射表,键为小组ID(groupID),值为该小组的组员信息
//map<int, vector<TeamInfo>> team_dev;//团队下有很多成员
//
////角色映射表，表示角色的映射关系,键为角色字符串,值为该角色的映射
//map<string, int> positionMap;
//
//void buildFileNameArray()
//{
//	string fileName = "sf";
//	int arrayIndex = 0;
//	fileNameArray[arrayIndex++] = "sf0103.txt";
//	fileNameArray[arrayIndex++] = "sf1104.txt";
//	fileNameArray[arrayIndex++] = "sf1204.txt";
//
//	for (int i = 1; i <= 12;i++)//1月到12月
//	{
//		for (int j = 5; j <= 11; j++)//05年到11年
//		{
//			fileName = "sf";
//			if (!(j == 5 && i == 1))//2005年没有1月的数据
//			{
//				//月份
//				if (i >= 10)
//				{
//					fileName += '1';
//					fileName += char(i - 10 + '0');
//				}
//				else
//				{
//					fileName += '0';
//					fileName += char(i + '0');
//				}
//
//				//年份
//				if (j >= 10)
//				{
//					fileName += '1';
//					fileName += char(j - 10 + '0');
//				}
//				else
//				{
//					fileName += '0';
//					fileName += char(j + '0');
//				}
//
//				fileName += ".txt";
//
//				fileNameArray[arrayIndex++] = fileName;
//			}
//		}
//	}
//
//	fileNameArray[arrayIndex++] = "sf0112.txt";
//	fileNameArray[arrayIndex++] = "sf0212.txt";
//	fileNameArray[arrayIndex++] = "sf0312.txt";
//	fileNameArray[arrayIndex++] = "sf0412.txt";
//	fileNameArray[arrayIndex++] = "sf0512.txt";
//	fileNameArray[arrayIndex++] = "sf0612.txt";
//}
//
////获取角色的映射表
//void outputPositionMap()
//{
//	string outputName = proDir + "largerThanFive\\positionMap.txt";
//	ofstream outfile(outputName);
//
//	map<string, int>::iterator positionIter;
//
//	for (positionIter = positionMap.begin(); positionIter != positionMap.end(); positionIter++)
//		outfile << positionIter->first << " " << positionIter->second << endl;
//
//	outfile.close();
//}
//
////输出抽象版本的文本文档
//void outputAbstractDevInfo(string outputName,int memberCnt)
//{
//	ofstream outfile(outputName);
//
//	cout << outputName << endl;
//
//	map<string, int>::iterator teamIter;
//
//	vector<TeamInfo> tInfo;
//
//	int index = 0;
//
//	for (teamIter = teamMap.begin(); teamIter != teamMap.end(); teamIter++)
//	{
//		if (team_dev[teamIter->second].size() > memberCnt)
//		{
//			tInfo = team_dev[teamIter->second];
//
//			outfile << "t # " << index << endl;
//
//			//添加节点信息
//			for (int i = 0; i < tInfo.size(); i++)
//			{
//				string pos = tInfo[i].position;
//
//				outfile << "v " << i << " " << positionMap[pos] << endl;
//			}
//
//			//添加边的信息
//			for (int i = 0; i < tInfo.size() - 1; i++)
//			{
//				for (int j = i + 1; j < tInfo.size(); j++)
//				{
//					outfile << "e " << i << " " << j << " 0\n";
//				}
//			}
//
//			index++;
//		}
//	}
//
//	outfile.close();
//}
//
////处理下元数据，将角色为空格的内容清理掉
//void preprocess()
//{
//	for (int i = 0; i < 92; i++)
//	{
//		string documentName = proDir + "hisData\\";
//		string outputFileName = proDir + "preprocess\\";
//
//		documentName += fileNameArray[i];
//		outputFileName += fileNameArray[i];
//
//		ifstream infile(documentName);
//		ofstream outfile(outputFileName);
//
//		string s = "";
//
//		cout << documentName << endl;
//
//		while (!infile.eof())
//		{
//			getline(infile, s);
//
//			if (s.size() != 0 && s[0] != 'S')
//			{
//				if (s[s.size() - 1 - 2] != '#')
//					outfile << s << endl;
//			}
//		}
//
//		infile.close();
//		outfile.close();
//	}
//}
//
////先得到小组和组员的映射，接着将人数小于memberCnt的小组忽略掉
//void ignoreSmallGroup(int memberCnt)
//{
//	for (int i = 0; i < 92; i++)
//	{
//		/*************输入文本**************/
//		//预处理后的文件名称
//		string prefileName = proDir + "preprocess\\";
//		prefileName += fileNameArray[i];
//
//		ifstream infile(prefileName);
//		/*************输入文本**************/
//
//		/*************具体操作过程**************/
//		//获取每行的文本
//		string s = "";
//
//		//职位映射表的大小
//		int positionMapSize = 0;
//
//		//团队映射表,键为团队名称,值为团队索引
//		int teamMapSize = 0;
//		int teamIndex = -1;//从teamMap中查找到需要插入信息的索引
//
//		//登录名、团队信息和角色是通过#号有规律分割
//		string loginName = "";
//		string teamInfo = "";
//		string position = "";
//
//		int wellNumberIndex1 = -1;
//		int wellNumberIndex2 = -1;
//		int wellNumberIndex3 = -1;
//
//		while (getline(infile, s))
//		{
//			//寻找前三个#号，并记录它们的索引
//			wellNumberIndex1 = s.find('#');
//			wellNumberIndex2 = s.find('#', wellNumberIndex1 + 1);
//			wellNumberIndex3 = s.find('#', wellNumberIndex2 + 1);
//
//			//获取登录名、职位、团队信息
//			loginName = s.substr(0, wellNumberIndex1);
//			teamInfo = s.substr(wellNumberIndex1 + 1, wellNumberIndex2 - wellNumberIndex1 - 1);
//			position = s.substr(wellNumberIndex2 + 1, wellNumberIndex3 - wellNumberIndex2 - 1);
//
//			//cout << loginName << " " << teamInfo << " " <<  position << endl;
//
//			//将职位信息存入map中
//			if (positionMapSize == 0 || positionMap.find(position) == positionMap.end())
//			{
//				positionMap.insert(map<string, int>::value_type(position, positionMapSize));
//				positionMapSize++;
//			}
//
//			//获取团队的索引
//			//从未出现过的团队信息，将它加入map中
//			if (teamMapSize == 0 || teamMap.find(teamInfo) == teamMap.end())
//			{
//				teamMap.insert(map<string, int>::value_type(teamInfo, teamMapSize));
//				teamIndex = teamMapSize;
//				teamMapSize++;
//			}
//			else
//				teamIndex = teamMap[teamInfo];
//
//			//在团队teamIndex中插入登录名为loginName,职位为position的新成员
//			team_dev[teamIndex].push_back(TeamInfo(loginName, position));
//		}
//
//		//去除人数小于memberCnt的工作在输出中完成
//		/*******************输出结果***********************/
//		//输出抽象结果的strResult.txt
//		string outputName = proDir + "largerThanFive\\";
//		outputName += fileNameArray[i];
//
//		outputAbstractDevInfo(outputName,memberCnt);
//
//		//输出职位的map信息
//		outputPositionMap();
//
//		infile.close();
//	}
//}
//
////获取最终适合我进行频繁子图挖掘的文本文档
//void txtForFrequentSubgraphMining()
//{}
//
//int main()
//{
//	//Step1: 构建文件名称的数组
//	buildFileNameArray();
//
//	/*********************测试输出*********************/
//	//for (int i = 0; i < 92; i++)
//	//	cout << fileNameArray[i] << endl;
//	/*********************测试输出*********************/
//
//	//Step2: 处理下元数据，将角色为空格的内容清理掉
//	//preprocess();
//
//	//Step3: 先得到小组和组员的映射，接着将人数小于5的小组忽略掉
//	ignoreSmallGroup(5);
//	
//	//Step4: 得到最终用于频繁子图挖掘的文本文档
//	//txtForFrequentSubgraphMining();
//	
//
//	return 0;
//}