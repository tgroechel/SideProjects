#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <stack>
#include <bitset>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <math.h>

using namespace std;

//Test file for mess around programs/studying/interview ?'s'
//-Tom Groechel

/*notes about & etc that accumulate
 //these are c++ short hands for that loop
 //that you write 1trillion times in programming
	for(const int &i : v1)
	{
		cout << i << endl;
	}
	for(auto i : v1)
	{
		cout << i << endl;
	}
 //sentinal is last thing to quit like enter -1 instead
*/


//used to print out vectors while testing
template<typename T>
void printVec(vector<T>& vec)
{
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ' ';
	}
	cout << endl;
}
//requires lleft and right are within the index of vec
//overloads printVec allowing to print vector 
//from [left,right]
template<typename T>
void printVec(vector<T>& vec, int left, int right)
{
	for(unsigned int i = left; i <=right ; i++)
	{
		cout << vec[i] << ' ';
	}
	cout << endl;
}

//used to make random vectors of random sizes
// that have been shuffled
//returns a vector that has size given and randomly
// distributed elements (not mem efficient but oh well)
vector<int> makeVec(int size)
{
	vector<int> v(size,-1);
	generate(v.begin(), v.end(), rand);
	return v;
}
//same thing as above but restricts values from [0, rang)
//comment out srand if you want same vec everytime
vector<int> makeVec(int size, int rang)
{
	srand(time(NULL));
	vector<int> v(size,-1);
	generate(v.begin(), v.end(), rand);
	for(int i = 0; i < size; ++i)
	{
		v[i] = v[i] % rang;
	}
	return v;
}
//same thing as make vec but make half the value negative
//plus ones whose index divisible by 7 cause 7, 
//values from (-rang, rang)
vector<int> makeVecN(int size, int rang)
{
	srand(time(NULL));
	vector<int> v(size,-1);
	generate(v.begin(), v.end(), rand);
	for(int i = 0; i < size; ++i)
	{
		if(i % 2 == 0 || i % 7 == 0)
		{
			v[i] = (v[i] % rang) * -1;
		}
		else
		{
			v[i] = (v[i] % rang);
		}
	}
	return v;
}


//takes in x and y and returns x^y
//must run O(log(n))
int powerOf(int x, int y)
{
	if(!y)
	{
		return 1;
	}
	if(!x)
	{
		return 0;
	}
	int count = 0;
	int xtra = x;
	while(count < y/2)
	{
		x = x * x;
		count++;
	}
	if(y%2 && y != 1)
	{
		x *= xtra;
	}
	return x;
}

//requires a vector that is already sorted (maybe not anymore)
//returns a vector of pairs (x,y) such that x+y = z
//must run in O(n) time, messed with other like abs val and y-x
//not efficient but tested for many interview questions
vector< vector<int> > * findPairs(vector<int> * sorted, int z)
{
	int x = 0, y = 1, result, result2;
	vector< vector<int> > * vec = new vector< vector<int> >;

	for(unsigned int i = 1; i < sorted->size(); i++)
	{
		result = sorted->at(y) + sorted->at(x);
		result2 = sorted->at(x) + sorted->at(y);
		if(result < z)
		{
			vector<int> temp;
			temp.push_back(x);
			temp.push_back(y);	
			vec->push_back(temp);
			x++;
			if(x == y)
			{
				y++;
			}
			else
			{
				i--;
			}
		}
		if(result2 < z)
		{
			vector<int> temp;
			temp.push_back(y);
			temp.push_back(x);	
			vec->push_back(temp);
			x++;
			if(x == y)
			{
				y++;
			}
			else
			{
				i--;
			}
		}
		else
		{
			y++;
		}

	}

	return vec;
}

//requires two bitsets of size 8
//returns the result of them anded
bool isOddBit(bitset<8> a)
{
	bitset<8> b(string("00000001"));
	cout << b[0] << endl;
	b &= a;
	return b[0];
}

//requires a vector to be nicely formed
//sorts the vector from leat int to greatest
//O(n^2) sort average/ is stable
//taking in improvements, once sorted it will break
void bubbleSort(vector <int>& vec)
{
	if(vec.empty() || vec.size() == 1)
	{
		return;
	}
	bool swapped;
	for(unsigned int i = vec.size() - 1; i > 0; i--)
	{
		swapped = false;
		for(unsigned int j = 0; j < i; j++)
		{
			if(vec[j] > vec[j+1])
			{
				swapped = true;
				iter_swap(vec.begin() + j, vec.begin() + j + 1);
			}
		}
		if(!swapped)
		{
			break;
		}
	}
}

//O(n^2) sort average/is stable
//reduces number of swaps if min is already at current
//index of i
void selectionSort(vector<int>& vec)
{
	if(vec.size() == 0 || vec.size() == 1)
	{
		return;
	}
	int min;
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		min = i;
		for(unsigned int j = i; j < vec.size(); j++)
		{
			if(vec[j] < vec[min])
			{
				min = j;
			}
		}
		if(min != i)
		{
			iter_swap(vec.begin() + min, vec.begin() + i);
		}
	}
}
//O(n^2) sort
//stable but can be improved
void insertionSort(vector<int>& vec)
{
	if(vec.size() == 0 || vec.size() == 1)
	{
		return;
	}
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		for(unsigned int j = i; j > 0; j--)
		{
			if(vec[j] < vec[j-1])
			{
				iter_swap(vec.begin() + j - 1, vec.begin() + j);
			}
		}
	}
}

//used for heapSort
//fixes tree from top down
//O(logn)
void fixdown()
{
}
//uses binary heap to 
void heapSort()
{
}
//heapSort

//used for quick sort
//finds partion and sorts things to left and right of it
int partion(vector<int>& arr, int left, int right)
{
	//int pivot = (right + left)/2;
	//iter_swap(arr.begin() + right, arr.begin() + pivot);
	int pivot = right;
	right--;

	while(true)
	{
		while(arr[left] < arr[pivot])
		{
			left++;
		}
		while(arr[right] >= arr[pivot] && right > left)
		{
			right--;
		}

		if(left >= right)
		{
			break;
		}
		iter_swap(arr.begin() + left, arr.begin() + right);
	}
	iter_swap(arr.begin() + left, arr.begin() + pivot);
	return left;
}

//requires that arr size is between left and right
//recurssive quicksort, sorts [left,right]
//O(nlog(n)) average case O(n^2) worst, usually beats mergeSort
void quickSort(vector<int>& arr, int left, int right)
{
	//if arr is of size 1 or 0, then it is already sorted
	if(left >= right)
	{
		return;
	}
	printVec(arr, left, right);
	int pivot = partion(arr, left, right);
	quickSort(arr, left, pivot-1);
	quickSort(arr, pivot+1, right);
}

//used for merge sort
//merges two vectors: copies back to adress left
//to right in vector passed in with sorted version
void merge(vector<int>& vec, int left, int mid, int right)
{
	vector<int> temp(right - left + 1);
	unsigned int i = left, j = mid + 1;
	for(unsigned int k = 0; k < right - left + 1; k++)
	{
		if(i > mid)
		{
			temp[k] = vec[j];
			j++;
		}
		else if(j > right)
		{
			temp[k] = vec[i];
			i++;
		}
		else
		{
			if(vec[i] <= vec[j])
			{
				temp[k] = vec[i];
				i++;
			}
			else
			{
				temp[k] = vec[j];
				j++;
			}
		}
	}
	printVec(temp);
	copy(temp.begin(), temp.end(), &vec[left]);
}

//mergesort [left,right]
//O(nlogn) even if sorted/nonadaptive/needs extra memory/copy
//stable, great for linked lists(not implemented),top down
void mergeSort(vector<int>& vec, int left, int right)
{
	if(left >= right)
	{
		return;
	}
	int mid = (right + left)/2;
	mergeSort(vec, left, mid);
	mergeSort(vec, mid+1,right);
	merge(vec, left, mid, right);
}

//requires 2 ordered sets
//merges 2 sets in order into result in sorted order
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator mergeSets(InputIterator1 start1, InputIterator1 end1,
							 InputIterator2 start2, InputIterator2 end2,
							 OutputIterator result)
{
	while(start1!= end1 && start2 != end2)
	{
		if(*start1 <= *start2)
		{
			*result++ = *start1++;
		}
		else
		{
			*result++ = *start2++;
		}
	}
	while(start1 != end1)
	{
		*result++ = *start1++;
	}
	while(start2 != end2)
	{
		*result++ = *start2++;
	}
	return result;
}
//requires the 2 input lists are sorted
//finds intersection of 2 sets
//O(n) complexity
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator findIntersect(InputIterator1 start1, InputIterator1 end1,
							 InputIterator2 start2, InputIterator2 end2,
							 OutputIterator result)
{
	while(start1 != end1 && start2 != end2)
	{
		if(*start1 < *start2)
		{
			start1++;
		}
		else if(*start2 < *start1)
		{
			start2++;
		}
		else
		{
			*result = *start1;
			start1++;
			start2++;
			result++;
		}

	}
	return result;
}

//requires the 2 input lists are sorted
//finds everything that is in the two sets that isn't in both
//O(n)?
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator ridOverlap(InputIterator1 start1, InputIterator1 end1,
							 InputIterator2 start2, InputIterator2 end2,
							 OutputIterator result)
{
	while(start1 != end1 && start2 != end2)
	{
		if(*start1 == *start2)
		{
			InputIterator1 temp1 = start1;
			InputIterator2 temp2 = start2;
			while(*temp1 == *start2 && temp1 != end1)
			{
				temp1++;
			}
			while(*temp2 == *start1 && temp2 != end2)
			{
				temp2++;
			}
			start1 = temp1;
			start2 = temp2;
			continue;
		}
		if(*start1 < *start2)
		{
			*result = *start1;
			start1++;
		}
		else if(*start2 < *start1)
		{
			*result = *start2;
			start2++;
		}
		result++;
	}
	while(start1 != end1)
	{
		*result = *start1;
		result++;
		start1++;
	}
	while(start1 != end1)
	{
		*result = *start1;
		result++;
		start1++;
	}
	return result;
}
/*
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator findIntersect(InputIterator1 start1, InputIterator1 end1,
							 InputIterator2 start2, InputIterator2 end2,
							 OutputIterator result)
{
	while(start1 != end1 && start2 != end2)
	{
		if(*start1 < *start2)
		{
			start1++;
		}
		else if(*start2 < *start1)
		{
			start2++;
		}
		else
		{
			*result = *start1;
			start1++;
			start2++;
			result++;
		}

	}
	return result;
}
*/
int main()
{
	cout << "hello World" << endl;


	return 0;
}

