////���ļ��Ƕ�SF���ݵ�Ԥ�����ļ�
//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//#include <map>
//
//using namespace std;
//
//string fileNameArray[92];//�����ļ����Ƶ�����
//string proDir = "D:\\VariousWorkspace\\C++Workspace\\playground\\playground\\";//��Ŀ��ַ��Ϊ��֮�󱣴洦�������ݵ�Ŀ¼
//
//struct TeamInfo
//{
//	string userID; //��¼��
//	string position; //ְλ����ɫ
//
//	TeamInfo(string uID, string pos)
//		:userID(uID), position(pos)
//	{}
//};
//
////�Ŷ�ӳ���,��Ϊ�Ŷ�����,ֵΪ�Ŷ�������
//map<string, int> teamMap;
//
////�Ŷ�����Ŷ��¿�����Ա��Ϣ��ӳ���,��ΪС��ID(groupID),ֵΪ��С�����Ա��Ϣ
//map<int, vector<TeamInfo>> team_dev;//�Ŷ����кܶ��Ա
//
////��ɫӳ�����ʾ��ɫ��ӳ���ϵ,��Ϊ��ɫ�ַ���,ֵΪ�ý�ɫ��ӳ��
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
//	for (int i = 1; i <= 12;i++)//1�µ�12��
//	{
//		for (int j = 5; j <= 11; j++)//05�굽11��
//		{
//			fileName = "sf";
//			if (!(j == 5 && i == 1))//2005��û��1�µ�����
//			{
//				//�·�
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
//				//���
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
////��ȡ��ɫ��ӳ���
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
////�������汾���ı��ĵ�
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
//			//��ӽڵ���Ϣ
//			for (int i = 0; i < tInfo.size(); i++)
//			{
//				string pos = tInfo[i].position;
//
//				outfile << "v " << i << " " << positionMap[pos] << endl;
//			}
//
//			//��ӱߵ���Ϣ
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
////������Ԫ���ݣ�����ɫΪ�ո�����������
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
////�ȵõ�С�����Ա��ӳ�䣬���Ž�����С��memberCnt��С����Ե�
//void ignoreSmallGroup(int memberCnt)
//{
//	for (int i = 0; i < 92; i++)
//	{
//		/*************�����ı�**************/
//		//Ԥ�������ļ�����
//		string prefileName = proDir + "preprocess\\";
//		prefileName += fileNameArray[i];
//
//		ifstream infile(prefileName);
//		/*************�����ı�**************/
//
//		/*************�����������**************/
//		//��ȡÿ�е��ı�
//		string s = "";
//
//		//ְλӳ���Ĵ�С
//		int positionMapSize = 0;
//
//		//�Ŷ�ӳ���,��Ϊ�Ŷ�����,ֵΪ�Ŷ�����
//		int teamMapSize = 0;
//		int teamIndex = -1;//��teamMap�в��ҵ���Ҫ������Ϣ������
//
//		//��¼�����Ŷ���Ϣ�ͽ�ɫ��ͨ��#���й��ɷָ�
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
//			//Ѱ��ǰ����#�ţ�����¼���ǵ�����
//			wellNumberIndex1 = s.find('#');
//			wellNumberIndex2 = s.find('#', wellNumberIndex1 + 1);
//			wellNumberIndex3 = s.find('#', wellNumberIndex2 + 1);
//
//			//��ȡ��¼����ְλ���Ŷ���Ϣ
//			loginName = s.substr(0, wellNumberIndex1);
//			teamInfo = s.substr(wellNumberIndex1 + 1, wellNumberIndex2 - wellNumberIndex1 - 1);
//			position = s.substr(wellNumberIndex2 + 1, wellNumberIndex3 - wellNumberIndex2 - 1);
//
//			//cout << loginName << " " << teamInfo << " " <<  position << endl;
//
//			//��ְλ��Ϣ����map��
//			if (positionMapSize == 0 || positionMap.find(position) == positionMap.end())
//			{
//				positionMap.insert(map<string, int>::value_type(position, positionMapSize));
//				positionMapSize++;
//			}
//
//			//��ȡ�Ŷӵ�����
//			//��δ���ֹ����Ŷ���Ϣ����������map��
//			if (teamMapSize == 0 || teamMap.find(teamInfo) == teamMap.end())
//			{
//				teamMap.insert(map<string, int>::value_type(teamInfo, teamMapSize));
//				teamIndex = teamMapSize;
//				teamMapSize++;
//			}
//			else
//				teamIndex = teamMap[teamInfo];
//
//			//���Ŷ�teamIndex�в����¼��ΪloginName,ְλΪposition���³�Ա
//			team_dev[teamIndex].push_back(TeamInfo(loginName, position));
//		}
//
//		//ȥ������С��memberCnt�Ĺ�������������
//		/*******************������***********************/
//		//�����������strResult.txt
//		string outputName = proDir + "largerThanFive\\";
//		outputName += fileNameArray[i];
//
//		outputAbstractDevInfo(outputName,memberCnt);
//
//		//���ְλ��map��Ϣ
//		outputPositionMap();
//
//		infile.close();
//	}
//}
//
////��ȡ�����ʺ��ҽ���Ƶ����ͼ�ھ���ı��ĵ�
//void txtForFrequentSubgraphMining()
//{}
//
//int main()
//{
//	//Step1: �����ļ����Ƶ�����
//	buildFileNameArray();
//
//	/*********************�������*********************/
//	//for (int i = 0; i < 92; i++)
//	//	cout << fileNameArray[i] << endl;
//	/*********************�������*********************/
//
//	//Step2: ������Ԫ���ݣ�����ɫΪ�ո�����������
//	//preprocess();
//
//	//Step3: �ȵõ�С�����Ա��ӳ�䣬���Ž�����С��5��С����Ե�
//	ignoreSmallGroup(5);
//	
//	//Step4: �õ���������Ƶ����ͼ�ھ���ı��ĵ�
//	//txtForFrequentSubgraphMining();
//	
//
//	return 0;
//}