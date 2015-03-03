#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct TeamInfo
{
	string loginName; //��¼��
	string position; //ְλ����ɫ

	TeamInfo(string ln, string pos)
		:loginName(ln), position(pos)
	{}
};

//��ȡ�ļ�dev_vector.txt��һ�е�����
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

//��dev_vector.txt�ļ��е�tabת��Ϊ#
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

//��strResult.txt����ȡ�����ߵ�¼����ְλ�������Ŷ���Ϣ
void getLoginName_Position_Team()
{
	string fileName = "strResult.txt";
	string outputName = "devInfo.txt";

	ifstream infile(fileName);
	ofstream outfile(outputName);

	//�����������ݽṹ��һ�����Ŷ�ӳ���,��Ϊ�Ŷ�����,ֵΪ�Ŷ����ƣ�
	//��һ�����Ŷ�����Ŷ��¿�����Ա��Ϣ��ӳ���
	int mapSize = 0;
	map<string,int> teamMap;
	int teamIndex = -1;//��teamMap�в��ҵ���Ҫ������Ϣ������

	map<int, vector<TeamInfo>> team_dev;//�Ŷ����кܶ��Ա

	//��ȡÿ������
	string s = "";

	//��¼����ְλ���Ŷ���Ϣ��ͨ��#���й��ɷָ�
	string loginName = "";
	string position = "";
	string teamInfo = "";

	int wellNumberIndex1 = -1;
	int wellNumberIndex2 = -1;
	int wellNumberIndex3 = -1;

	while (getline(infile,s))
	{
		//Ѱ��ǰ����#�ţ�����¼���ǵ�����
		wellNumberIndex1 = s.find('#');
		wellNumberIndex2 = s.find('#',wellNumberIndex1+1);
		wellNumberIndex3 = s.find('#',wellNumberIndex2+1);

		//��ȡ��¼����ְλ���Ŷ���Ϣ
		loginName = s.substr(0,wellNumberIndex1);
		position = s.substr(wellNumberIndex1+1,wellNumberIndex2-wellNumberIndex1-1);
		teamInfo = s.substr(wellNumberIndex2+1,wellNumberIndex3-wellNumberIndex2-1);

		//cout << loginName << " " << position << " " << teamInfo << endl;

		//��ȡ�Ŷӵ�����
		//��δ���ֹ����Ŷ���Ϣ����������map��
		if (mapSize==0 || teamMap.find(teamInfo) == teamMap.end())
		{
			teamMap.insert(map<string,int>::value_type(teamInfo,mapSize));
			teamIndex = mapSize;
			mapSize++;
		}
		else
			teamIndex = teamMap[teamInfo];

		//���Ŷ�teamIndex�в����¼��ΪloginName,ְλΪposition���³�Ա
		team_dev[teamIndex].push_back(TeamInfo(loginName,position));
	}

	//��������outfile
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

	infile.close();
	outfile.close();
}

int main()
{
	//�ļ�Ԥ����
	//TurnTabToWellNumber();

	//��ȡ�����ߵ�¼����ְλ�������Ŷ�
	getLoginName_Position_Team();

	return 0;
}