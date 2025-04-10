#include<iostream>
using namespace std;


template<typename T>
class LinkedList
{
private:
	class Node;
public:
	class ForwardIterator
	{
	private:
		Node* iter;
	public:
		ForwardIterator(Node* newIter)
		{
			iter = newIter;
		}
		
		bool operator!=(const ForwardIterator& newIter)
		{
			return iter != newIter.iter;
		}
		T& operator * ()
		{
			return iter->data;
		}
		bool operator == (const ForwardIterator& newIter)
		{
			return iter == newIter.iter;
		}
		ForwardIterator& operator ++ ()
		{
			iter = iter->next;
			return *this;
		}
	};
	class ReverseIterator
	{
	private:
		Node* iter;
	public:
		ReverseIterator(Node* newIter)
		{
			iter = newIter;
		}

		bool operator!=(const ReverseIterator& newIter)
		{
			return iter != newIter.iter;
		}
		T& operator * ()
		{
			return iter->data;
		}
		bool operator == (const ReverseIterator& newIter)
		{
			return iter == newIter.iter;
		}
		ReverseIterator& operator ++ ()
		{
			iter = iter->previous;
			return *this;
		}
	};
	class GeneralIterator
	{
	private:
		Node* iter;
	public:
		GeneralIterator(Node* newIter)
		{
			iter = newIter;
		}

		bool operator!=(const GeneralIterator& newIter)
		{
			return iter != newIter.iter;
		}
		T& operator * ()
		{
			return iter->data;
		}
		bool operator == (const GeneralIterator& newIter)
		{
			return iter == newIter.iter;
		}
		GeneralIterator& operator ++ ()
		{
			iter = iter->next;
			return *this;
		}
		GeneralIterator& operator -- ()
		{
			iter = iter->previous;
			return *this;
		}
	};
private:
	class Node
	{
	private:
		Node* previous;
		T data;
		Node* next;
	public:
		Node(int value)
		{
			previous = nullptr;
			data = value;
			next = nullptr;
		}
		friend class LinkedList;
	};
private:
	Node* head;
	Node* tail;
public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
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
			tail = newNode;
		}
		else
		{

			newNode->next = head;
			head->previous = newNode;
			head = newNode;
		}
	}
	void InsertAtTail(T value)
	{
		Node* newNode = new Node(value);
		if (IsEmpty())
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			newNode->previous = tail;
			tail->next = newNode;
			tail = newNode;
		}
	}
	void InsertAfter(T value, T key)
	{
		Node* newNode = new Node(value);
		Node* temp = head;
		while (temp != tail->next)
		{
			if (temp->data == key)
			{
				newNode->previous = temp;
				newNode->next = temp->next;
				temp->next = newNode;
				newNode->next->previous = newNode;
				break;
			}
			temp = temp->next;
		}
	}
	void InsertBefore(T value, T key)
	{
		Node* newNode = new Node(value);
		Node* temp = head;
		while (temp != tail->next)
		{
			if (temp->data == key)
			{
				newNode->previous = temp->previous;
				newNode->next = temp;
				temp->previous->next = newNode;
				temp->previous = newNode;
				break;
			}
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
			tail = tail->previous;
		}
	}
	void RemoveAt(T key)
	{
		Node* temp = head;
		while (temp != tail->next)
		{
			if (temp->data == key)
			{
				temp->previous->next = temp->next;
				temp->next->previous = temp->previous;
				break;
			}
			temp = temp->next;
		}
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
	void splice(GeneralIterator position, LinkedList& otherList)
	{
		if (position == end()) {
			if (!otherList.IsEmpty()) {
				if (IsEmpty()) {
					head = otherList.head;
					tail = otherList.tail;
				}
				else {
					tail->next = otherList.head;
					otherList.head->previous = tail;
					tail = otherList.tail;
				}
				otherList.head = otherList.tail = nullptr;
			}
		}
		else {
			Node* pos = position.iter;
			Node* beforePos = pos->previous;

			if (!otherList.IsEmpty()) {
				if (beforePos) {
					beforePos->next = otherList.head;
					otherList.head->previous = beforePos;
				}
				else {
					head = otherList.head;
				}
				pos->previous = otherList.tail;
				otherList.tail->next = pos;
				otherList.head = otherList.tail = nullptr;
			}
		}
	}



	ForwardIterator fbegin()
	{
		return ForwardIterator(head);
	}
	ForwardIterator fend()
	{
		return ForwardIterator(nullptr);
	}
	ReverseIterator rbegin()
	{
		return ReverseIterator(tail);
	}
	ReverseIterator rend()
	{
		return ReverseIterator(nullptr);
	}
	GeneralIterator begin()
	{
		return GeneralIterator(head);
	}
	GeneralIterator end()
	{
		return GeneralIterator(tail);
	}
};



int main()
{
	LinkedList<int> l;
	l.InsertAtFront(23);
	l.InsertAtFront(24);
	l.InsertAtFront(25);
	l.InsertAtFront(26);
	for (LinkedList<int> ::ForwardIterator i = l.fbegin(); i != l.fend(); ++i )
	{
		cout << *i << "  ";
	}
	cout << endl;
	for (LinkedList<int> ::ReverseIterator i = l.rbegin(); i != l.rend(); ++i)
	{
		cout << *i << "  ";
	}
	cout << endl;
	for (LinkedList<int> ::GeneralIterator i = l.begin(); i != l.end(); ++i)
	{
		cout << *i << "  ";
	}
	cout << endl;
	for (LinkedList<int> ::GeneralIterator i = l.end(); i != l.begin(); --i)
	{
		cout << *i << "  ";
	}
	return 0;
}
//
////Question01
//
///**
// * Definition for singly-linked list.
// * struct ListNode {
// *     int val;
// *     ListNode *next;
// *     ListNode() : val(0), next(nullptr) {}
// *     ListNode(int x) : val(x), next(nullptr) {}
// *     ListNode(int x, ListNode *next) : val(x), next(next) {}
// * };
// */
//class Solution {
//public:
//	void insert(ListNode*& head, ListNode*& tail, int data) {
//		ListNode* newNode = new ListNode(data);
//		if (head == NULL) {
//			head = newNode;
//			newNode->next = NULL;
//			tail = newNode;
//		}
//		else {
//			tail->next = newNode;
//			newNode->next = NULL;
//			tail = newNode;
//		}
//	}
//	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
//		ListNode* head = NULL, * tail = NULL;
//
//		while (list1 != NULL && list2 != NULL) {
//			int data1 = list1->val, data2 = list2->val;
//			if (data1 <= data2) {
//				insert(head, tail, data1);
//				list1 = list1->next;
//			}
//			else {
//				insert(head, tail, data2);
//				list2 = list2->next;
//			}
//		}
//		while (list1 != NULL) {
//			insert(head, tail, list1->val);
//			list1 = list1->next;
//		}
//
//		while (list2 != NULL) {
//			insert(head, tail, list2->val);
//			list2 = list2->next;
//		}
//
//		return head;
//
//	}
//};
//
////Questio02
///**
// * Definition for singly-linked list.
// * struct ListNode {
// *     int val;
// *     ListNode *next;
// *     ListNode() : val(0), next(nullptr) {}
// *     ListNode(int x) : val(x), next(nullptr) {}
// *     ListNode(int x, ListNode *next) : val(x), next(next) {}
// * };
// */
//class Solution {
//public:
//	int length(ListNode* head) {
//		int i = 0;
//		while (head != NULL) {
//			i++;
//			head = head->next;
//		}
//		return i;
//	}
//
//	ListNode* removeNthFromEnd(ListNode* head, int k) {
//		if (head->next == NULL) {
//			return NULL;
//		}
//		int n = length(head);
//		int i = 1, pos = n - k + 1;
//		if (pos == 1) {
//			head = head->next;
//			return head;
//		}
//		ListNode* prev = NULL, * curr = head;
//
//		while (i < pos) {
//			prev = curr;
//			curr = curr->next;
//			i++;
//		}
//		prev->next = curr->next;
//		return head;
//	}
//};
//
////Question03
///**
// * Definition for singly-linked list.
// * struct ListNode {
// *     int val;
// *     ListNode *next;
// *     ListNode() : val(0), next(nullptr) {}
// *     ListNode(int x) : val(x), next(nullptr) {}
// *     ListNode(int x, ListNode *next) : val(x), next(next) {}
// * };
// */
//class Solution {
//public:
//	ListNode* swapPairs(ListNode* head) {
//		if (head == NULL)
//		{
//			return NULL;
//		}
//		if (head->next == NULL)
//		{
//			return head;
//		}
//		ListNode* prev = head;
//		ListNode* temp = head;
//		ListNode* curr = prev->next->next;
//		head = head->next;
//		head->next = prev;
//		while (curr != NULL && curr->next != NULL)
//		{
//			temp = curr->next->next;
//			prev->next = curr->next;;
//			prev = curr;
//			curr->next->next = curr;
//			curr = temp;
//		}
//		prev->next = curr;
//		return head;
//	}
//};
//
////Question04
///**
// * Definition for singly-linked list.
// * struct ListNode {
// *     int val;
// *     ListNode *next;
// *     ListNode() : val(0), next(nullptr) {}
// *     ListNode(int x) : val(x), next(nullptr) {}
// *     ListNode(int x, ListNode *next) : val(x), next(next) {}
// * };
// */
//class Solution {
//public:
//	ListNode* rev(ListNode* head) {
//		if (head == NULL || head->next == NULL)
//			return head;
//		ListNode* curr = head;
//		ListNode* prev = NULL;
//		ListNode* nex = NULL;
//		while (curr != NULL) {
//			nex = curr->next;
//			curr->next = prev;
//			prev = curr;
//			curr = nex;
//		}
//		return prev;
//	}
//	ListNode* reverseBetween(ListNode* head, int left, int right) {
//		if (head == NULL || head->next == NULL)
//			return head;
//		if (left == right)
//			return head;
//		ListNode* curr = head;
//		ListNode* t = NULL;
//		ListNode* prev = NULL;
//		ListNode* s = NULL;
//		ListNode* v = NULL;
//		bool f = 0;
//		if (left == 1) {
//			f = 1;
//			t = curr;
//		}
//		int s1 = 1;
//		while (curr != NULL) {
//			if (s1 == left && f == 0) {
//				v = prev;
//				t = curr;
//			}
//			if (s1 == right) {
//				s = curr->next;
//				curr->next = NULL;
//				break;
//			}
//			prev = curr;
//			curr = curr->next;
//			s1++;
//		}
//		if (f == 0) {
//			v->next = NULL;
//		}
//		ListNode* ans = rev(t);
//		t->next = s;
//		if (f == 0)
//			v->next = ans;
//		if (f == 1)
//			head = ans;
//		return head;
//	}
//};
//
////Question05
//class Node {
//public:
//	int val;
//	Node* next;
//	Node(int val) {
//		this->val = val;
//		next = NULL;
//	}
//};
//class MyLinkedList {
//public:
//	int size = 0;
//	Node* head = NULL;
//	Node* tail = NULL;
//	MyLinkedList() {
//	}
//
//	int get(int index) {
//		if (index >= size)
//			return -1;
//		Node* temp = head;
//		for (int i = 0; i < index; ++i)
//			temp = temp->next;
//
//		return temp->val;
//	}
//
//	void addAtHead(int val) {
//		Node* nnode = new Node(val);
//		nnode->next = head;
//		head = nnode;
//		if (size == 0)
//			tail = nnode;
//		size++;
//	}
//
//	void addAtTail(int val) {
//		if (size == 0) {
//			addAtHead(val);
//			return;
//		}
//		Node* nnode = new Node(val);
//		tail->next = nnode;
//		tail = nnode;
//		size++;
//	}
//
//	void addAtIndex(int index, int val) {
//		if (index > size)
//			return;
//		else if (index == size)
//			addAtTail(val);
//		else if (index == 0)
//			addAtHead(val);
//		else {
//			Node* temp = head;
//			Node* nnode = new Node(val);
//			for (int i = 0; i < index - 1; ++i) {
//				temp = temp->next;
//			}
//			nnode->next = temp->next;
//			temp->next = nnode;
//			size++;
//		}
//	}
//
//	void deleteAtIndex(int index) {
//		if (index >= size)
//			return;
//		else if (index == size - 1) {
//
//			if (index == 0) {
//				head == NULL;
//				tail == NULL;
//			}
//			else {
//				Node* temp = head;
//				while (temp->next != tail) {
//					temp = temp->next;
//				}
//				tail = temp;
//				temp->next = NULL;
//			}
//
//		}
//		else if (index == 0) {
//			Node* temp = head;
//			head = head->next;
//			temp = NULL;
//		}
//		else {
//			Node* temp = head;
//			for (int i = 0; i < index - 1; ++i) {
//				temp = temp->next;
//			}
//			Node* t = temp->next;
//			temp->next = temp->next->next;
//			t->next = NULL;
//
//		}
//		size--;
//
//	}
//};
//
///**
// * Your MyLinkedList object will be instantiated and called as such:
// * MyLinkedList* obj = new MyLinkedList();
// * int param_1 = obj->get(index);
// * obj->addAtHead(val);
// * obj->addAtTail(val);
// * obj->addAtIndex(index,val);
// * obj->deleteAtIndex(index);
// */
