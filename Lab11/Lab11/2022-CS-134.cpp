#include <queue>  
#include <vector>  
#include <iostream> 
#include <cstdlib> 
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

template <typename T>
void sort(vector<T>& arr, int low, int high);

template <typename T>
int partition(vector<T>& arr, int low, int high);

void RandomNumbersInFile(string dataFilePath, size_t fileSize);



template <typename T>
class Compare
{
public:
    bool operator() (const T& a, const T& b) const
    {
        return a > b;
    }
};


template <typename T>
void HeapSort(vector<T>& V)
{
    priority_queue<T, vector<T>, Compare<T>> PQ;
    for (int vi = 0; vi < V.size(); vi++)
    {
        PQ.push(V[vi]);
    }
    V.clear();
    while (!PQ.empty())
    {
        V.push_back(PQ.top());
        PQ.pop();
    }
}

template <typename T>
void BubbleSort(vector<T>& V) {
    int n = V.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (V[j] > V[j + 1]) {
                 swap(V[j], V[j + 1]);
            }
        }
    }
}

template <typename T>
void SelectionSort(vector<T>& V) {
    int n = V.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (V[j] < V[minIndex]) {
                minIndex = j;
            }
        }
        swap(V[i], V[minIndex]);
    }
}


template <typename T>
void QuickSort(vector<T>& arr) {
    sort(arr, 0, arr.size() - 1);
}

template <typename T>
void sort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        sort(arr, low, pi - 1);
        sort(arr, pi + 1, high);
    }
}
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


template <typename T>
void Randomized_Init(vector<T>& V)
{
    for (int vi = 0; vi < V.size(); vi++)
    {
        V[vi] = rand() % 100;
    }
}
template <typename T>
void Vector_Print(vector<T>& V)
{
    for (int vi = 0; vi < V.size(); vi++)
    {
        cout << V[vi] << "    ";
    }
    cout << endl;
}
void RandomNumbersInFile(string dataFilePath, size_t fileSize)
{
    std::ofstream dataFile(dataFilePath, std::ios::binary);
    std::vector<int> data(fileSize / sizeof(int));
    std::generate(data.begin(), data.end(), []() { return rand() % 100; });
    dataFile.write(reinterpret_cast<const char*>(data.data()), fileSize);
    dataFile.close();
}

int main()
{


    string dataFilePath = "data.txt";
    size_t fileSize = 100000;

    
    RandomNumbersInFile(dataFilePath, fileSize);
    ifstream inputFile(dataFilePath, ios::binary);
    vector<int> dataArray(fileSize / sizeof(int));
    inputFile.read(reinterpret_cast<char*>(dataArray.data()), fileSize);
    inputFile.close();

    int option;
    cout << "1.Heap Sort" << endl;
    cout << "2.Bubble Sort" << endl;
    cout << "3.Selection Sort" << endl;
    cout << "4.Quick Sort" << endl;
    cout << "Enter Option: ";
    cin >> option;
   /* vector<int> values(20);
    Randomized_Init(values);*/
    cout << "Before Sorting:" << endl << endl << endl;
    Vector_Print(dataArray);

    auto start =  chrono::high_resolution_clock::now();

    if (option == 1)
    {
        HeapSort(dataArray);
    }
    else if (option == 2)
    {
        BubbleSort(dataArray);
    }
    else if (option == 3)
    {
        SelectionSort(dataArray);
    }
    else if (option == 4)
    {
        QuickSort(dataArray);
    }
    auto stop =  chrono::high_resolution_clock::now();
    auto duration =  chrono::duration_cast< chrono::milliseconds>(stop - start);

    cout << "After Sorting: " << endl << endl << endl;
    Vector_Print(dataArray);
    cout << "BubbleSort Sorting Time: " << duration.count() << " milliseconds" << endl;

    return 0;
}
