#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;

int fast_triSum(vector<int>& series, int num);


// Question 01
//01
int SumOfNaturalNumbers(int n)
{
	if(n == 1)
	{
		return 1;
	}
	return n + SumOfNaturalNumbers(n - 1);
}

//02
int SumOfOddNumbers(int n)
{
	if(n== 1)
	{
		return 1;
	}
	return n + SumOfOddNumbers(n - 2);
}

//03
int SumOfGPBase2(int n)
{
	if (n == 1)
	{
		return 1;
	}
	return pow(2, n) + SumOfGPBase2(n - 1);
}

//04
int SumOfGPBase3(int n)
{
	if (n == 1)
	{
		return 1;
	}
	return pow(3, n) + SumOfGPBase3(n - 1);
}

//05
int SumOfGPBy3(int n)
{
	if (n == 1)
	{
		return 1;
	}
	return n + SumOfGPBy3(n / 3);
}

//06
int SumOfGPBy2(int n)
{
	if (n == 1)
	{
		return 1;
	}
	return n + SumOfGPBy2(n / 2);
}

//Question02
//01
string DecimalToBinary(int number)
{
	if (number == 0)
	{
		return "";
	}
	return DecimalToBinary(number / 2) + to_string(number % 2);

}
//02
string ITOA(int number)
{
	
	if (number == 0)
	{
		return "";
	}
	if (number < 0)
	{
		string positive = "-";
		positive += ITOA(-number);
		return positive;
	}
	char endChar = '0' + number % 10;
	return ITOA(number / 10) + endChar;
}
//03
int GCD(int a, int b)
{
	if (a % b == 0)
	{
		return b;
	}
	return GCD(b, a % b);
}

//Question03
//01
int SearchFirstEntry(int array[], int start, int end)
{
	if (start == end)
	{
		return array[end];
	}
	int max = SearchFirstEntry(array, start + 1, end);
	if (array[start] >= max)
	{
		return array[start];
	}
	return max;
}

//02
int SearchLastEntry(int array[], int start, int end)
{
	if (start == end)
	{
		return array[end];
	}
	int max = SearchLastEntry(array, start, end - 1);
	if (array[end] >= max)
	{
		return array[end];
	}
	return max;
}

//03
int BinarySearch(int array[], int start, int end,int max)
{
	if (start == end)
	{
		return end;
	}
	int mid = (start + end) / 2;
	if (array[mid] == max)
	{
		return mid;
	}
	if (array[mid] < max)
	{
		return BinarySearch(array, mid + 1, end, max);
	}
	if (array[mid] > max)
	{
		return BinarySearch(array, start, mid - 1, max);
	}
}

//Question04
int PowerLog(int X, int Y, int M)  
{
	if (Y == 0)
	{
		return 1;
	}
	else if (Y % 2 == 0)
	{
		int temp = PowerLog(X, Y / 2, M);
		return ((temp * temp) % M);
	}
	int result = PowerLog(X, Y - 1, M);
	return (result * (X % M)) % M;
}

int PowerSimple(int X, int Y, int M) 
{
	if (Y == 0)
	{
		return 1;
	}
	int result = PowerSimple(X, Y - 1, M);
	return (result * X) % M;
}

void generateSubArray(vector <int>& array, int start, int end, vector <vector<int >>& result)
{
	if (start > end)
	{
		return;
	}
	for (int i = start; i <= end; i++)
	{
		vector <int> subarray;
		for (int j = start; j <= i; j++)
		{
			subarray.push_back(array[j]);
		}
		result.push_back(subarray);
	}
	generateSubArray(array, start + 1, end, result);
}

//Question 07

int FibonacciSeries(int number)
{
	int previous = 0;
	int current = 1;
	int result;
	if (number == 0)
	{
		return previous;
	}
	for (int idx = 2; idx <= number; idx++)
	{
		result = previous + current;
		previous = current;
		current = result;
	}
	return current;
}

int fib(int number)
{
	if (number == 0 || number == 1)
	{
		return number;
	}
	return(fib(number - 1) + fib(number - 2));
}

int fast_fib(vector<int>& FS, int num)
{
	if (FS[num] != -1)
	{
		return FS[num];
	}
	return (fast_fib(FS, num - 1) + fast_fib(FS, num - 2));
}

int mem_fib(int num)
{
	vector<int> FS(num + 1, { -1 });
	FS[0] = 0;
	FS[1] = 1;
	return fast_fib(FS, num);
}


int fib_bottomUp(int n)
{
	if (n <= 1)
	{
		return n;
	}
	vector<int> series(n + 1);
	series[0] = 0;
	series[1] = 1;
	for (int idx = 2; idx <= n; idx++)
	{
		series[idx] = series[idx - 1] + series[idx - 2];

	}
	return series[n];
}

//Question 08

int iterative_Trisum(int num)
{
	if (num == 0)
	{
		return 1;
	}
	if (num == 1)
	{
		return 2;
	}
	if (num == 2)
	{
		return 3;
	}
	int first = 1;
	int second = 2;
	int third = 3;
	int result;
	for (int idx = 3; idx <= num; idx++)
	{
		result = first + second + third;
		first = second;
		second = third;
		third = result;
	}
	return third;
}

int recurssive_Trisum(int num)
{
	if (num < 0)
	{
		return -1;
	}
	if (num == 0)
	{
		return 1;
	}
	if (num == 1)
	{
		return 2;
	}
	if (num == 2)
	{
		return 3;
	}
	return recurssive_Trisum(num - 1) + recurssive_Trisum(num - 2) + recurssive_Trisum(num - 3);
}

void SeriesFormulator(int n)
{
	for (int idx = 0; idx <= n; idx++)
	{
		cout << recurssive_Trisum(idx) << " ";
	}
}

int mem_trisum(int num)
{
	vector<int>series(num + 1, { -1 });
	series[0] = 1;
	series[1] = 2;
	series[2] = 3;
	return fast_triSum(series, num);

}

int fast_triSum(vector<int>& series, int num)
{
	if (series[num] != -1)
	{
		return series[num];
	}
	return (fast_triSum(series, num - 1) + fast_triSum(series, num - 2) + fast_triSum(series, num - 3));

}

int BottomUp_Trisum(int num)
{
	if (num < 1)
	{
		return -1;
	}
	vector <int>series(num + 1);
	series[0] = 1;
	series[1] = 2;
	series[2] = 3;
	for (int idx = 3; idx <= num; idx++)
	{
		series[idx] = series[idx - 1] + series[idx - 2] + series[idx - 3];
	}
	return series[num];
}

//Challenge 1

void PrintsubArray(int input[], int size, int index, string result)
{
	if (index == size)
	{
		cout << "[" << result << "]";
		return;
	}
	PrintsubArray(input, size, index + 1, result + " " + to_string(input[index]) + " ");
	PrintsubArray(input, size, index + 1, result);

}

//Challenge 2

void insertSorted(stack<int>& s, int element) {
	if (s.empty() || element > s.top()) {
		s.push(element);
	}
	else {
		int topElement = s.top();
		s.pop();
		insertSorted(s, element);
		s.push(topElement);
	}
}

void sortStack(stack<int>& s) {
	if (!s.empty()) {
		int topElement = s.top();
		s.pop();
		sortStack(s);
		insertSorted(s, topElement);
	}
}

int main() {
	//// Question 01
	//// 01
	//cout << "Sum of Natural Numbers: " << SumOfNaturalNumbers(5) << endl;

	//// 02
	//cout << "Sum of Odd Numbers: " << SumOfOddNumbers(5) << endl;

	//// 03
	//cout << "Sum of GP Base 2: " << SumOfGPBase2(3) << endl;

	//// 04
	//cout << "Sum of GP Base 3: " << SumOfGPBase3(3) << endl;

	//// 05
	//cout << "Sum of GP by 3: " << SumOfGPBy3(27) << endl;

	//// 06
	//cout << "Sum of GP by 2: " << SumOfGPBy2(16) << endl;

	//// Question 02
	//// 01
	//cout << "Decimal to Binary: " << DecimalToBinary(10) << endl;

	//// 02
	//cout << "Integer to String: " << ITOA(-123) << endl;

	//// 03
	//cout << "GCD of 15 and 25: " << GCD(15, 25) << endl;

	//// Question 03
	//int array[] = { 3, 8, 5, 2, 7 };
	//int arraySize = sizeof(array) / sizeof(array[0]);

	//// 01
	//cout << "Search First Entry: " << SearchFirstEntry(array, 0, arraySize - 1) << endl;

	//// 02
	//cout << "Search Last Entry: " << SearchLastEntry(array, 0, arraySize - 1) << endl;

	//// 03
	//int maxElement = SearchFirstEntry(array, 0, arraySize - 1);
	//cout << "Binary Search: Index of " << maxElement << " is " << BinarySearch(array, 0, arraySize - 1, maxElement) << endl;

	//// Question 04
	//cout << "Power (log): " << PowerLog(2, 5, 100) << endl;
	//cout << "Power (simple): " << PowerSimple(2, 5, 100) << endl;

	//// Question 05
	//vector<int> numbers = { 1, 2, 3 };
	//vector<vector<int>> subArrays;
	//generateSubArray(numbers, 0, numbers.size() - 1, subArrays);

	//cout << "Subarrays:" << endl;
	//for (const auto& subArray : subArrays) {
	//	for (const auto& num : subArray) {
	//		cout << num << " ";
	//	}
	//	cout << endl;
	//}

	//// Question 07
	//cout << "Fibonacci Series (Iterative): " << FibonacciSeries(0) << endl;
	//cout << "Fibonacci Series (Recursive): " << fib(4) << endl;
	//cout << "Fibonacci Series (Memoization): " << mem_fib(8) << endl;
	//cout << "Fibonacci Series (Bottom-up): " << fib_bottomUp(5) << endl;

	//// Question 08
	//cout << "TriSum (Iterative): " << iterative_Trisum(0) << endl;
	//cout << "TriSum (Recursive): " << recurssive_Trisum(5) << endl;
	//cout << "TriSum (Memoization): " << mem_trisum(8) << endl;
	//cout << "TriSum (Bottom-up): " << BottomUp_Trisum(5) << endl;

	//// Challenge 1
	//int input[] = { 1, 2, 3 };
	//int size = sizeof(input) / sizeof(input[0]);
	//cout << "Subarrays:" << endl;
	//PrintsubArray(input, size, 0, "");

	// Challenge 2
	stack<int> s;
	s.push(4);
	s.push(1);
	s.push(5);
	s.push(3);

	cout << "Stack before sorting: ";
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	s.push(4);
	s.push(1);
	s.push(5);
	s.push(3);

	sortStack(s);

	cout << "Stack after sorting: ";
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	return 0;
}
