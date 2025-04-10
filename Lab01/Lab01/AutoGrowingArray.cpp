#include <iostream>
using namespace std;

template<typename T>
class AutoGrowingArray {
private:
	T* DataArray;
	int size;
	int capacity;
public:
	AutoGrowingArray()
	{
		DataArray = new T[capacity];
		size = 0;
		capacity = 1;
	}
	T operator [](int index) const {
		if (index < 0 || index >= size) {
			throw out_of_range("Index is out of range");
		}
		return DataArray[index];
	}

	T operator [](int index) {
		if (index < 0 || index >= size) {
			throw out_of_range("Index is out of range");
		}
		return DataArray[index];
	}
	friend ostream& operator<<(ostream& output, const AutoGrowingArray& obj)
	{
		for (int idx = 0; idx < obj.size; idx++)
		{
			output << obj.DataArray[idx] << "  ";
		}
		return output;
	}

	void PushBack(T value)
	{
		if (size == capacity)
		{
			capacity++;
			T* newArray = new T[capacity];
			for (int idx = 0; idx < size; idx++)
			{
				newArray[idx] = DataArray[idx];
			}

			delete[] DataArray;
			DataArray = newArray;
		}
		DataArray[size] = value;
		size++;
	}


};

int main()
{
	AutoGrowingArray<int>  array;

	array.PushBack(30);
	array.PushBack(40);
	array.PushBack(50);

	cout << "All elements are : " << array << endl;

	cout << "Element at index 2 : " << array[2];
}