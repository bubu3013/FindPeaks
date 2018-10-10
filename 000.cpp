#include<iostream>
#include<queue>
#include<fstream>
#include<string>
#include<vector>
#include <sstream>
#define MAX 10000

using namespace std;
queue<int> location;

//finding peak with binary search mid is the col/2
int findMax(vector<vector<int> > a, int rows, int mid, int &max)
{
    int peak_index = 0;
    for (int i = 0; i < rows; i++)
    {
        //if a[i][mid] is larger than now_max
        if (max<a[i][mid])
        {   //to store its location
            max=a[i][mid];
            peak_index = i;
            //to store peak's row and col
        }
    }
    return peak_index;
}
 // Function to find a peak element with binary search
int findPeak(vector<vector<int> > arr,int rows,int columns,int mid)
{
    // Evaluating maximum of mid column.
    //max is passed by reference.
    int max = 0;
    int max_index = findMax(arr, rows, mid, max);
     // If we are on the first or last column, max is a peak
    if (mid == 0 || mid == columns-1)
        return max;
     // If mid column maximum is also peak
    if (max >= arr[max_index][mid-1] &&
            max >= arr[max_index][mid+1])
        return max;
     // If max is less than its left
    if (max < arr[max_index][mid-1])
        return findPeak(arr, rows, columns, mid - mid/2);
     // If max is less than its right
    if (max < arr[max_index][mid+1])
        return findPeak(arr, rows, columns, mid+mid/2);
}
int count_peaks(vector<vector<int> > a,int m,int n,int peak)
{
	int sum=0;
    //to find x from peak_location to peak_location+rows*cols
    for (int i=1;i<=m;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (a[i][j]==peak)
            {
                location.push(i);
                location.push(j);
                sum++;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    //input row and col
    int m,n;
    int j;
    int row=0,col=0;
    int q_size;
    
    fstream file; 
    ifstream input("TA_matrix_3.data");
    ofstream fout("file.txt"); 

    stringstream ss,s0,s1;
	
    vector<string> v;
    vector<vector<int> > a;
    //vector<int> rowVector;

    string matrix;
    string m_and_n;
    string buffer;

    file.open("TA_matrix_3.data",ios::in);
    
    /*all the elements in matrix is in string matrix with space*/
    do
    {
        getline(input,matrix);
        v.push_back(matrix);
        
    }while(!input.eof());
    /*got the m_and_n and matrix string here*/
    ss<<v.at(0);
    m_and_n=ss.str();
    ss.str("");
    ss << v.at(1);
    matrix=ss.str();
	ss.str("");
    /*got the m and n here*/
    for(int i=0;m_and_n[i]!=' ';i++)
    {
        buffer+=m_and_n[i];
        j=i;
    }
    s0<<buffer;
    s0>>m;
	s0.str("");
    buffer.clear();
    
	for(int i=j+2;m_and_n[i]!='\0';i++)
    {
        buffer+=m_and_n[i];
    }
    s1<<buffer;
    s1>>n;
    j=0;
	/*got all the elements here in 2d array*/
    vector<int> rowVector(n);
    if (file.is_open())
    {
        while(file.good())
        {
        	a.push_back(rowVector);
			if (row==0)
			{
				for (int col=0;col<2;++col)
				{
					file>>a[row][col];
				}
			}
            else
            {
                for (int col=0;col<n;col++)
                {
                    file>>a[row][col];
                }
            }
            row++;
        }
    }
    file.close();
    
    count_peaks(a,m,n,findPeak(a, m, n,n/2));

    q_size=location.size();

	fout<<q_size/2<<endl;
    
    for (int i=0;i<q_size;i++)
    {
        if (i%2==0)
		{
			fout<<location.front()-1<<" ";
		}
		else if (i%2==1)
		{	
			fout<<location.front()<<endl;
		}
        location.pop();
    }
    
    return 0;
}
