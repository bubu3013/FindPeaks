#include<iostream>
#include<queue>
#include<fstream>
#include<string>
#include<vector>
#include <sstream>
#define MAX 10000

using namespace std;
//finding peak with binary search mid is the col/2
int findMax(int a[][MAX], int rows, int mid, int &max)
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
int findPeak(int arr[][MAX],int rows,int columns,int mid)
{
    // Evaluating maximum of mid column.
    //max is passed by reference.
    int max = 0;
    int max_index = findMax(arr, rows, mid, max);
     // If we are on the first or last column, max is a peak
    //??????
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
int count_peaks(int a[][MAX],int m,int n,int peak)
{
    int sum=0;
    queue<int> location;
     //peak_location initialize in the
    int* peak_location = &a[0][0];
    //to find x from peak_location to peak_location+rows*cols
    for (int i=0;i<m;i++)
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
    for (int i=0;i<sum*2;i++)
    {
        cout<<location.front()<<" ";
        location.pop();
        if (i%2==1)cout<<endl;
    }
    //cout<<peak<<endl;
}
int main(int argc, char *argv[])
{
    //input row and col
    int m,n;
    int j;

    ifstream input("TA_matrix_3.data");
    ofstream fout("file.txt"); 

    stringstream ss,s0,s1;
	
    vector<string> v;

    string matrix;
    string m_and_n;
    string buffer;

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
	/*got all the elements here in 2d array*/
    int a[][MAX] = {{11,10,10,10,10},
                    {10,10,10,10,11},
                    {10,11,10,10,10},
                    {10,10,10,11,10},
                    {10,10,11,10,10}};
    
    count_peaks(a,m,n,findPeak(a, m, n,n/2));
    return 0;
}
