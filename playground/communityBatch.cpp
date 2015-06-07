#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

string fileNameArray[92];

void buildFileNameArray()
{
	string fileName = "sf";
	int arrayIndex = 0;
	fileNameArray[arrayIndex++] = "sf0103";
	fileNameArray[arrayIndex++] = "sf1104";
	fileNameArray[arrayIndex++] = "sf1204";

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

				//fileName += ".txt";

				fileNameArray[arrayIndex++] = fileName;
			}
		}
	}

	fileNameArray[arrayIndex++] = "sf0112";
	fileNameArray[arrayIndex++] = "sf0212";
	fileNameArray[arrayIndex++] = "sf0312";
	fileNameArray[arrayIndex++] = "sf0412";
	fileNameArray[arrayIndex++] = "sf0512";
	fileNameArray[arrayIndex++] = "sf0612";
}

//command: "./convert -i graph.txt -o graph.bin"
void convertToBin(string fileName)
{
	string edgeFile = "../mapGraph/"+fileName+"_Edge.txt";
	string targetBinName = "../result/graphBin/"+fileName+".bin";
	string binCmd = "./convert -i "+edgeFile+" -o "+targetBinName;
//	cout<<binCmd<<endl;
	system(binCmd.c_str());
}

//command: "./community graph.bin -l -1 -v > graph.tree"
void computeCommunities(string fileName)
{
	string binFile = "../result/graphBin/"+fileName+".bin";
	string treeName = "../result/tree/"+fileName+".tree";
	string communityCmd = "./community "+binFile+" -l -1 -v > "+treeName;
//	cout<<communityCmd<<endl;
	system(communityCmd.c_str());
}

int main()
{
	buildFileNameArray();

	for(int i=0;i<92;i++)
	{
		//Step1:先进行二进制转化
		//convertToBin(fileNameArray[i]);
		//Step2:进行社区发现
		computeCommunities(fileNameArray[i]);
	}

	return 0;
}
