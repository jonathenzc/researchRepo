#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct TeamInfo
{
	string loginName; //登录名
	string position; //职位、角色

	TeamInfo(string ln, string pos)
		:loginName(ln), position(pos)
	{}
};

//获取文件dev_vector.txt中一行的内容
string getOneLineString(string s)
{
	string result = "";

	for (int i = 0; i < s.size();i++)
	{
		if (s[i] == '	')
			result += "#";
		else if (s[i] != NULL)
			result += s[i];
	}

	return result;
}

//将dev_vector.txt文件中的tab转换为#
void TurnTabToWellNumber()
{
	string fileName = "dev_vector.txt";
	string outputName = "strResult.txt";

	ifstream infile(fileName);

	ofstream outfile(outputName);

	string s = "";

	while (getline(infile, s))
	{
		outfile << getOneLineString(s) << endl;
	}

	infile.close();
	outfile.close();
}

//将teamMap的信息输出到txt中
void outputTeamMap(map<string, int> m)
{
	string outputName = "teamMap.txt";
	ofstream outfile(outputName);

	map<string, int>::iterator teamIter;

	int index = 0;

	for (teamIter = m.begin(); teamIter != m.end(); teamIter++)
	{
		outfile << teamIter->first << " " << index << endl;
		index++;
	}

	outfile.close();
}

//获取角色的映射表
void outputPositionMap(map<string, int> m)
{
	string outputName = "positionMap.txt";
	ofstream outfile(outputName);

	map<string,int>::iterator positionIter;

	for (positionIter = m.begin(); positionIter != m.end(); positionIter++)
		outfile << positionIter->first << " " << positionIter->second << endl;

	outfile.close();
}

//输出预处理文本
void outputStrResult(map<string, int> teamMap, map<int, vector<TeamInfo>> team_dev)
{
	string fileName = "strResult.txt";
	ofstream outfile(fileName);

	map<string, int>::iterator teamIter;
	map<int, vector<TeamInfo>>::iterator team_devInter;

	vector<TeamInfo> tInfo;

	for (teamIter = teamMap.begin(); teamIter != teamMap.end(); teamIter++)
	{
		outfile << teamIter->first << endl;

		tInfo = team_dev[teamIter->second];

		for (int i = 0; i < tInfo.size(); i++)
			outfile << tInfo[i].loginName << " " << tInfo[i].position << endl;
	}

	outfile.close();
}

//输出抽象版本的文本文档
void outputAbstractDevInfo(map<string, int> teamMap, map<int, vector<TeamInfo>> team_dev, map<string, int>positionMap)
{
	string fileName = "AbstractDevInfo.txt";
	ofstream outfile(fileName);

	map<string, int>::iterator teamIter;
	map<int, vector<TeamInfo>>::iterator team_devInter;

	vector<TeamInfo> tInfo;

	int index = 0;

	for (teamIter = teamMap.begin(); teamIter != teamMap.end(); teamIter++)
	{
		outfile << "t # "<<index << endl;

		tInfo = team_dev[teamIter->second];

		//添加节点信息
		for (int i = 0; i < tInfo.size(); i++)
		{
			string pos = tInfo[i].position;

			outfile <<"v " << i << " " << positionMap[pos] << endl;
		}

		//添加边的信息
		for (int i = 0; i < tInfo.size()-1; i++)
		{
			for (int j = i+1; j < tInfo.size(); j++)
			{
				outfile << "e " << i << " " << j << " 0\n";
			}
		}

		index++;
	}

	outfile.close();
}

//从strResult.txt中提取开发者登录名、职位和所属团队信息
void getLoginName_Position_Team()
{
	string fileName = "strResult.txt";
	string outputName = "devInfo.txt";

	ifstream infile(fileName);
	ofstream outfile(outputName);

	//创建三个数据结构：
	//第一个是团队映射表,键为团队索引,值为团队名称；
	int teamMapSize = 0;
	map<string,int> teamMap;
	int teamIndex = -1;//从teamMap中查找到需要插入信息的索引

	//第二个个是团队与该团队下开发人员信息的映射表
	map<int, vector<TeamInfo>> team_dev;//团队下有很多成员

	//第三个是角色映射表，表示角色的映射关系
	map<string, int> positionMap;
	int positionMapSize = 0;

	//获取每行的文本
	string s = "";

	//登录名、职位和团队信息是通过#号有规律分割
	string loginName = "";
	string position = "";
	string teamInfo = "";

	int wellNumberIndex1 = -1;
	int wellNumberIndex2 = -1;
	int wellNumberIndex3 = -1;

	while (getline(infile,s))
	{
		//寻找前三个#号，并记录它们的索引
		wellNumberIndex1 = s.find('#');
		wellNumberIndex2 = s.find('#',wellNumberIndex1+1);
		wellNumberIndex3 = s.find('#',wellNumberIndex2+1);

		//获取登录名、职位、团队信息
		loginName = s.substr(0,wellNumberIndex1);
		position = s.substr(wellNumberIndex1+1,wellNumberIndex2-wellNumberIndex1-1);
		teamInfo = s.substr(wellNumberIndex2+1,wellNumberIndex3-wellNumberIndex2-1);

		//cout << loginName << " " << position << " " << teamInfo << endl;

		//将职位信息存入map中
		if (positionMapSize == 0 || positionMap.find(position) == positionMap.end())
		{
			positionMap.insert(map<string,int>::value_type(position,positionMapSize));
			positionMapSize++;
		}

		//获取团队的索引
		//从未出现过的团队信息，将它加入map中
		if (teamMapSize == 0 || teamMap.find(teamInfo) == teamMap.end())
		{
			teamMap.insert(map<string, int>::value_type(teamInfo, teamMapSize));
			teamIndex = teamMapSize;
			teamMapSize++;
		}
		else
			teamIndex = teamMap[teamInfo];

		//在团队teamIndex中插入登录名为loginName,职位为position的新成员
		team_dev[teamIndex].push_back(TeamInfo(loginName,position));
	}

	/*******************输出结果***********************/
	//输出抽象结果的strResult.txt
	outputAbstractDevInfo(teamMap,team_dev,positionMap);

	//输出strResult.txt
	//outputStrResult(teamMap, team_dev);

	//输出teamMap的信息
	//outputTeamMap(teamMap);

	//输出职位映射表
	//outputPositionMap(positionMap);

	infile.close();
}



int main()
{
	//文件预处理
	//TurnTabToWellNumber();

	//提取开发者登录名、职位和所属团队
	getLoginName_Position_Team();

	return 0;
}