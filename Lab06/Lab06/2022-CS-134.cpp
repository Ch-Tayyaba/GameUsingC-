#include<iostream>
using namespace std;

template<typename T>
class LinkedList;

template<typename T>
class Stack;

template<typename T>
class Queue;



//Question01
template<typename T>
class LinkedList
{
	class Node
	{
	private:
		T data;
		Node* next;
	public:
		Node()
		{

		}
		Node(int value)
		{
			data = value;
			next = nullptr;
		}
		friend class LinkedList;
	};
private:
	Node* head;
	Node* tail;
	Node* beforeTail;
public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
		beforeTail = nullptr;
	}
	bool IsEmpty()
	{
		if (head == nullptr)
		{
			return true;
		}
		return false;
	}
	void InsertAtFront(T Value)
	{
		Node* newNode = new Node(Value);
		if (IsEmpty())
		{
			head = newNode;
			beforeTail = newNode;
			tail = newNode;
		}
		else
		{
			newNode->next = head;
			head = newNode;
		}
	}
	void InsertAtTail(T value)
	{
		Node* newNode = new Node(value);
		if (IsEmpty())
		{
			head = newNode;
			beforeTail = newNode;
			tail = newNode;
		}
		else
		{
			tail->next = newNode;
			beforeTail = tail;
			tail = tail->next;
		}
	}
	void InsertAtMid(T value)
	{
		Node* newNode = new Node(value);
		Node* mid = head;
		for (int idx = 0; idx < (length() / 2) -1; idx++)
		{
			mid = mid->next;
		}
		newNode->next = mid->next;
		mid->next = newNode;

	}
	void InsertAfter(T value, T key)
	{
		Node* newNode = new Node(value);
		Node* temp = head;
		while (temp != tail->next)
		{
			if (temp->data == key)
			{
				newNode->next = temp->next;
				temp->next = newNode;
				break;
			}
			temp = temp->next;
		}
	}
	void InsertBefore(T value, T key)
	{
		Node* newNode = new Node(value);
		Node* beforeTemp = nullptr;
		Node* temp = head;
		while (temp != tail->next)
		{
			if (temp->data == key)
			{
				newNode->next = temp;
				beforeTemp->next = newNode;
				break;
			}
			beforeTemp = temp;
			temp = temp->next;
		}
	}
	T GetFront()
	{
		if (!(IsEmpty()))
		{
			return head->data;
		}
		return 0;
	}
	T GetTail()
	{
		if (!(IsEmpty()))
		{
			return tail->data;
		}
		return 0;
	}
	Node* Search(T key)
	{
		Node* temp = head;
		while (temp != tail->next)
		{
			if (temp->data == key)
			{
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
	void RemoveFront()
	{
		if (head == tail && !(IsEmpty()))
		{
			head = tail = nullptr;
		}
		else if (head != tail && !(IsEmpty()))
		{
			head = head->next;
		}
	}
	void RemoveTail()
	{
		if (head == tail && !(IsEmpty()))
		{
			head = tail = nullptr;
		}
		else if (head != tail && !(IsEmpty()))
		{
			tail = beforeTail;
		}
	}
	void RemoveMiddle()
	{
		Node* mid = head;
		Node* beforeMid = head;
		for (int idx = 0; idx < (length() / 2); idx++)
		{
			beforeMid = mid;
			mid = mid->next;
		}
		beforeMid->next = mid->next;
	}
	int length()
	{
		int count = 0;
		Node* temp = head;
		while (temp != tail->next)
		{
			count++;
			temp = temp->next;
		}
		return count;
	}
	void Display()
	{
		Node* temp = head;
		while (temp != tail->next)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}
	}

//Question03
	T MiddleElement()
	{
		Node* mid = head;
		for (int idx = 0; idx < (length() / 2) - 1; idx++)
		{
			mid = mid->next;
		}
		return mid->data;
	}
	bool IsCirculic()
	{
		if (tail->next == head)
		{
			return true;
		}
		return false;
	}
	void ReversedList()
	{
		Node* previous = nullptr;
		Node* current = head;
		Node* next = nullptr;
		while (current != nullptr)
		{
			next = current->next;
			current->next = previous;
			previous = current;
			current = next;
		}
		head = previous;
	}
	void displayReverse(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		displayReverse(node->next);
		cout << node->next << endl;

	}
};



//Question02
template<typename T>
class Stack
{
private:
	LinkedList<T> S;
public:
	Stack()
	{

	}
	void Push(T value)
	{
		S.InsertAtFront(value);
	}
	T Pop()
	{
		T value = S.GetFront();
		S.RemoveFront();
		return value;
	}
	bool IsEmpty()
	{
		return S.IsEmpty();
	}
	void display()
	{
		S.Display();
	}

};

template<typename T>
class Queue
{
private:
	LinkedList<T> Q;
public:
	Queue()
	{

	}
	void Enqueue(T value)
	{
		Q.InsertAtTail(value);
	}
	T Dequeue()
	{
		T value = Q.GetFront();
		Q.RemoveFront();
		return value;
	}
	bool IsEmpty()
	{
		return Q.IsEmpty();
	}
	void display()
	{
		Q.Display();
	}
};





int main()
{
	/*LinkedList<int> L;
	cout << "At Head" << endl;
	L.InsertAtFront(50);
	L.InsertAtFront(60);
	L.InsertAtFront(70);
	L.Display();
	cout << "At tail" << endl;
	L.InsertAtTail(10);
	L.InsertAtTail(20);
	L.InsertAtTail(30);
	L.Display();
	cout << "At mid" << endl;
	L.InsertAtMid(100);
	L.Display();
	cout << "Insert Before" << endl;
	L.InsertBefore(22,100);
	L.Display();
	cout << "Insert After" << endl;
	L.InsertAfter(22, 100);
	L.Display();
	cout << "Get Front " << endl;
	cout << L.GetFront() << endl;
	cout << "Get Tail" << endl;
	cout << L.GetTail() << endl;
	cout << "Remove Front " << endl;
	L.RemoveFront();
	L.Display();
	cout << "Remove Tail " << endl;
	L.RemoveTail();
	L.Display();
	cout << "Remove Middle " << endl;
	L.RemoveMiddle();
	L.Display();*/


	/*cout << "Search : 100" << endl;
	Node* newOne = L.Search(100);
	cout << newOne->data;
	cout << "Search : 0" << endl;
	cout << L.Search(0);*/


	Stack<int> S;
	S.Push(12);
	S.Push(13);
	S.Push(14);
	S.Push(15);
	S.display();
	cout << S.Pop() << endl;
	cout << S.Pop() << endl;
	S.display();
	cout << S.IsEmpty() << endl << endl;

	Queue<int> Q;
	Q.Enqueue(12);
	Q.Enqueue(13);
	Q.Enqueue(14);
	Q.Enqueue(15);
	Q.display();
	cout << Q.Dequeue() << endl;
	cout << Q.Dequeue() << endl;
	Q.display();
	cout << Q.IsEmpty() << endl << endl;


	return 0;
}