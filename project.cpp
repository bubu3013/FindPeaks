#include<iostream>
#include<stdio.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#define MAX 10000

using namespace std;
vector< pair <int,int> > location;
//to compare pair with first element and then the second one
struct compare
{
	bool operator()(const pair<int,int> &a,const pair<int,int> &b)
	{
		if(a.first!=b.first)
		{
			return a.first<b.first;
		}
		return a.second<b.second;
	}
};

 // Function to find a peak element with loops QQ
int findPeak(vector<vector<int> > a,int m,int n)
{
	//4 vertices
	//upleft
	if(a[0][0]>=a[0][1]&&a[0][0]>=a[1][0])
	{
		location.push_back(make_pair(1,1));
	}
	if(a[0][n-1]>=a[0][n-2]&&a[0][n-1]>=a[1][n-1])
	{
		location.push_back(make_pair(1,n));
	}
	//downleft
	if(a[m-1][0]>=a[m-1][1]&&a[m-1][0]>=a[m-2][0])
	{
		location.push_back(make_pair(m,1));
	}
	//downright
	if(a[m-1][n-1]>=a[m-1][n-2]&&a[m-1][n-1]>=a[m-2][n-1])
	{
		location.push_back(make_pair(m,n));
	}
	//4 edges
	//left edge without vertices
	for (int i=1;i<m-1;i++)
	{
		//大於上 下 右
		if (a[i][0]>=a[i-1][0]&&a[i][0]>=a[i+1][0]&&a[i][0]>=a[i][1])
		{
			location.push_back(make_pair(i+1,1));
		}
	}
	//up edge without vertices
	for (int j=1;j<n-1;j++)
	{
		//大於左 下 右
		if (a[0][j]>=a[0][j-1]&&a[0][j]>=a[0][j+1]&&a[0][j]>=a[1][j])
		{
			location.push_back(make_pair(1,j+1));
		}
	}
	//right edge without vertices
	for (int i=1;i<m-1;i++)
	{
		//大於上 下 左
		if (a[i][n-1]>=a[i-1][n-1]&&a[i][n-1]>=a[i+1][n-1]&&a[i][n-1]>=a[i][n-2])
		{
			location.push_back(make_pair(i+1,n));
		}
	}
	//down edge without vertices
	for (int j=1;j<n-1;j++)
	{
		//大於左 上 右
		if (a[m-1][j]>=a[m-1][j-1]&&a[m-1][j]>=a[m-1][j+1]&&a[m-1][j]>=a[m-2][j])
		{
			location.push_back(make_pair(m,j+1));
		}
	}
	//the rest of them
 	for (int i=1;i<m-1;++i)
 	{
 		for (int j=1;j<n-1;++j)
		{
			//如果大於 上 左  下 右
			if(a[i][j]>=a[i-1][j]&&a[i][j]>=a[i][j-1]&&a[i][j]>=a[i+1][j]&&a[i][j]>=a[i][j+1])
			{
				location.push_back(make_pair(i+1,j+1));
			}
		}
	}
}

int main(int argc, char *argv[])
{
    int i=0;
    int row=0,col=0;
    int l_size;
    //*argv[1] is student_id
	compare comp;
	//string of output data name
	//to control the file input and output
    fstream file;
    //get input_student_id
    string data_name="";
    string id="";
    while(argv[1][i]!='\0')
    {
        id+=argv[1][i];
        i++;
	}
	data_name="./"+id+"./matrix.data";
    file.open(data_name,ios::in);
    data_name="./"+id+"./final.peak";
    ofstream fout(data_name);

	//utilize vector to store array
    vector<vector<int> > a;
    vector<int> rowVector(MAX);
	
	file>>row;
    file>>col;

	/*got all the elements here in 2d array*/
    if (file.is_open())
    {
		int i=0;
        while(file.good())
        {
        	if (i<row)a.push_back(rowVector);
            for (int j=0;j<col;j++)
            {
                    file>>a[i][j];
            }
            i++;
        }
    }
    file.close();
	//to find all the peaks
    findPeak(a, row, col);
    //to sort the data
    sort(location.begin(),location.end(),comp);

    l_size=location.size();

	fout<<l_size<<endl;

    for (int i=0;i<l_size;i++)
    {
			fout<<location[i].first<<" "<<location[i].second<<endl;
    }

    return 0;
}
