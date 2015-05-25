#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

string fileNameArray[92];//�����ļ����Ƶ�����
string proDir = "D:\\VariousWorkspace\\C++Workspace\\playground\\playground\\";//��Ŀ��ַ��Ϊ��֮�󱣴洦�������ݵ�Ŀ¼

map < string, int > vertexMap;

void buildFileNameArray()
{
	string fileName = "sf";
	int arrayIndex = 0;
	fileNameArray[arrayIndex++] = "sf0103.txt";
	fileNameArray[arrayIndex++] = "sf1104.txt";
	fileNameArray[arrayIndex++] = "sf1204.txt";

	for (int i = 1; i <= 12; i++)//1�µ�12��
	{
		for (int j = 5; j <= 11; j++)//05�굽11��
		{
			fileName = "sf";
			if (!(j == 5 && i == 1))//2005��û��1�µ�����
			{
				//�·�
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

				//���
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

//�����ǵ���ļ�����
void buildVertexFile(string fileName)
{
	//������ļ�
	ofstream vertexOutFile(fileName);

	map<string, int>::iterator iter;
	for (iter = vertexMap.begin(); iter != vertexMap.end(); iter++)
		vertexOutFile << iter->first << endl;

	vertexOutFile.close();
}

//���ļ���ΪfileName���ļ�����ͼ����Ԥ����
//���а����������ļ��ͱ��ļ�
void GraphPreprocess(string fileName)
{
	/*************�����ı�**************/
	//Ԥ������ļ�����
	string prefileName = proDir + "Artifact_MetaData\\" + fileName;
	ifstream infile(prefileName);

	/*************����ı�**************/
	//��ȡfileName��ǰ׺
	int dotIndex = fileName.find(".");
	string filePrefix = fileName.substr(0,dotIndex);
	//���ļ������ļ�����ļ�����
	string vertexFileName = proDir + "Artifact_Edge_Vertex\\" + filePrefix + "_Vertex.txt";
	string edgeFileName = proDir + "Artifact_Edge_Vertex\\" + filePrefix + "_Edge.txt";
	//������ļ�
	ofstream edgeOutFile(edgeFileName);

	/****************************/
	string s;
	while (!infile.eof())
	{
		getline(infile, s);

		//Ѱ������#�ţ�����¼���ǵ�����
		int wellNumberIndex1 = s.find('#');
		int wellNumberIndex2 = s.find('#', wellNumberIndex1 + 1);

		if (wellNumberIndex1 != -1 && wellNumberIndex2 != -1)
		{
			//��ȡ�����ڵ�
			string startVertex = s.substr(0, wellNumberIndex1);
			string endVertex = s.substr(wellNumberIndex1 + 1, wellNumberIndex2 - wellNumberIndex1 - 1);

			//���ڵ��Ƿ���ڹ�����������������map��
			if (vertexMap.find(startVertex) == vertexMap.end())
				vertexMap[startVertex] = 0;

			if (vertexMap.find(endVertex) == vertexMap.end())
				vertexMap[endVertex] = 0;

			//��ԭ�ȵ�#�Ÿĳɿո�
			s[wellNumberIndex1] = ' ';
			s[wellNumberIndex2] = ' ';

			//���н�β��ӱߵ�Ȩֵ1
			s += "1";

			edgeOutFile << s << endl;
		}
	}

	infile.close();
	edgeOutFile.close();

	//�������ļ�
	buildVertexFile(vertexFileName);

	//��յ��map
	vertexMap.clear();
}

int main()
{
	//Step1: �����ļ����Ƶ�����
	buildFileNameArray();

	/*********************�������*********************/
	//for (int i = 0; i < 92; i++)
	//	cout << fileNameArray[i] << endl;
	/*********************�������*********************/

	//Step2: ��ÿ���ļ��������ļ��ͱ��ļ������Ʒֱ�ΪfileNameArray[i]+_vertex.txt or _edge.txt
	for (int i = 0; i < 92; i++)
	{
		cout << fileNameArray[i] << endl;
		GraphPreprocess(fileNameArray[i]);
	}

	return 0;
}