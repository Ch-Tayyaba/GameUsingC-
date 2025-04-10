#pragma once
#include<iostream>
using namespace std;

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
		for (int idx = 0; idx < (length() / 2) - 1; idx++)
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
};


