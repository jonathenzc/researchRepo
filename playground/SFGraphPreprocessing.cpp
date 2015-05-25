#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

string fileNameArray[92];//储存文件名称的数组
string proDir = "D:\\VariousWorkspace\\C++Workspace\\playground\\playground\\";//项目地址，为了之后保存处理后的数据的目录

map < string, int > vertexMap;

void buildFileNameArray()
{
	string fileName = "sf";
	int arrayIndex = 0;
	fileNameArray[arrayIndex++] = "sf0103.txt";
	fileNameArray[arrayIndex++] = "sf1104.txt";
	fileNameArray[arrayIndex++] = "sf1204.txt";

	for (int i = 1; i <= 12; i++)//1月到12月
	{
		for (int j = 5; j <= 11; j++)//05年到11年
		{
			fileName = "sf";
			if (!(j == 5 && i == 1))//2005年没有1月的数据
			{
				//月份
				if (i >= 10)
				{
					fileName += '1';
					fileName += char(i - 10 + '0');
				}
				else
				{
					fileName += '0';
					fileName += char(i + '0');
				}

				//年份
				if (j >= 10)
				{
					fileName += '1';
					fileName += char(j - 10 + '0');
				}
				else
				{
					fileName += '0';
					fileName += char(j + '0');
				}

				fileName += ".txt";

				fileNameArray[arrayIndex++] = fileName;
			}
		}
	}

	fileNameArray[arrayIndex++] = "sf0112.txt";
	fileNameArray[arrayIndex++] = "sf0212.txt";
	fileNameArray[arrayIndex++] = "sf0312.txt";
	fileNameArray[arrayIndex++] = "sf0412.txt";
	fileNameArray[arrayIndex++] = "sf0512.txt";
	fileNameArray[arrayIndex++] = "sf0612.txt";
}

//参数是点的文件名称
void buildVertexFile(string fileName)
{
	//点输出文件
	ofstream vertexOutFile(fileName);

	map<string, int>::iterator iter;
	for (iter = vertexMap.begin(); iter != vertexMap.end(); iter++)
		vertexOutFile << iter->first << endl;

	vertexOutFile.close();
}

//对文件名为fileName的文件进行图构建预处理
//其中包括构建点文件和边文件
void GraphPreprocess(string fileName)
{
	/*************输入文本**************/
	//预处理的文件名称
	string prefileName = proDir + "Artifact_MetaData\\" + fileName;
	ifstream infile(prefileName);

	/*************输出文本**************/
	//获取fileName的前缀
	int dotIndex = fileName.find(".");
	string filePrefix = fileName.substr(0,dotIndex);
	//点文件、边文件输出文件名称
	string vertexFileName = proDir + "Artifact_Edge_Vertex\\" + filePrefix + "_Vertex.txt";
	string edgeFileName = proDir + "Artifact_Edge_Vertex\\" + filePrefix + "_Edge.txt";
	//边输出文件
	ofstream edgeOutFile(edgeFileName);

	/****************************/
	string s;
	while (!infile.eof())
	{
		getline(infile, s);

		//寻找两个#号，并记录它们的索引
		int wellNumberIndex1 = s.find('#');
		int wellNumberIndex2 = s.find('#', wellNumberIndex1 + 1);

		if (wellNumberIndex1 != -1 && wellNumberIndex2 != -1)
		{
			//获取两个节点
			string startVertex = s.substr(0, wellNumberIndex1);
			string endVertex = s.substr(wellNumberIndex1 + 1, wellNumberIndex2 - wellNumberIndex1 - 1);

			//检查节点是否存在过，如果不存在则加入map中
			if (vertexMap.find(startVertex) == vertexMap.end())
				vertexMap[startVertex] = 0;

			if (vertexMap.find(endVertex) == vertexMap.end())
				vertexMap[endVertex] = 0;

			//将原先的#号改成空格
			s[wellNumberIndex1] = ' ';
			s[wellNumberIndex2] = ' ';

			//该行结尾添加边的权值1
			s += "1";

			edgeOutFile << s << endl;
		}
	}

	infile.close();
	edgeOutFile.close();

	//构建点文件
	buildVertexFile(vertexFileName);

	//清空点的map
	vertexMap.clear();
}

int main()
{
	//Step1: 构建文件名称的数组
	buildFileNameArray();

	/*********************测试输出*********************/
	//for (int i = 0; i < 92; i++)
	//	cout << fileNameArray[i] << endl;
	/*********************测试输出*********************/

	//Step2: 对每个文件构建点文件和边文件，名称分别为fileNameArray[i]+_vertex.txt or _edge.txt
	for (int i = 0; i < 92; i++)
	{
		cout << fileNameArray[i] << endl;
		GraphPreprocess(fileNameArray[i]);
	}

	return 0;
}