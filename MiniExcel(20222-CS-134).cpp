#pragma once
#include <string>
using namespace std;
class Node
{
public:
	Node* previous;
	Node* next;
	Node* top;
	Node* bottom;
	string data;

	Node()
	{
		previous = nullptr;
		next = nullptr;
		top = nullptr;
		bottom = nullptr;
		data = "0";
	}
	Node(string value)
	{
		previous = nullptr;
		next = nullptr;
		top = nullptr;
		bottom = nullptr;
		data = value;
	}
};

#pragma once
#include "Node.h"
#include<vector>
#include <fstream>

class LinkedList
{
public:
	Node* TopLeft;
	Node* TopRight;
	Node* BottomLeft;
	Node* BottomRight;

	LinkedList()
	{
		TopLeft = nullptr;
		TopRight = nullptr;
		BottomLeft = nullptr;
		BottomRight = nullptr;
	}
	bool IsEmpty();
	bool OnlyOneCell();
	bool IsTopRight(Node* current);
	bool IsTopLeft(Node* current);
	bool IsBottomRight(Node* current);
	bool IsBottomLeft(Node* current);
	Node* GetRightEnd(Node* current);
	Node* GetLeftEnd(Node* current);
	Node* GetTopEnd(Node* current);
	Node* GetBottomEnd(Node* current);
	Node* GetNodeByPosition(string position);
	void SetValue(Node* current, string value);
	void InsertAfter(Node* current, string value);
	void InsertBefore(Node* current, string value);
	void InsertAbove(Node* current, string value);
	void InsertBelow(Node* current, string value);
	void InsertRowAbove(Node* current);
	void InsertRowBelow(Node* current);
	void InsertColumnAfter(Node* current);
	void InsertColumnBefore(Node* current);
	void DeleteCellOfRow(Node* current);
	void DeleteCellOfColumn(Node* current);
	void DeleteColumn(Node* current);
	void DeleteRow(Node* current);
	void ClearColumn(Node* current);
	void ClearRow(Node* current);
	string Sum(string start, string end);
	string Average(string start, string end);
	string Count(string start, string end);
	string Min(string start, string end);
	string Max(string start, string end);
	vector<string> CutRow(string address);
	vector<string> CopyRow(string address);
	void PasteRow(string address, vector<string> data);
	vector<string> CutColumn(string address);
	vector<string> CopyColumn(string address);
	void PasteColumn(string address, vector<string> data);
	void LoadFromFile(const string& filename);
	void StoreToFile(const string& filename);
};

#include "LinkedList.h"
#include "Node.h"
#include<string>
#include <sstream>
#include<vector>

using namespace std;

bool LinkedList::IsEmpty()
{
	if (TopLeft == nullptr && TopRight == nullptr && BottomLeft == nullptr && BottomRight == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::IsTopRight(Node* current)
{
	if (current->next == nullptr && current->top == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::IsTopLeft(Node* current)
{
	if (current->top == nullptr && current->previous == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::IsBottomRight(Node* current)
{
	if (current->next == nullptr && current->bottom == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::IsBottomLeft(Node* current)
{
	if (current->bottom == nullptr && current->previous == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::OnlyOneCell()
{

	if (TopLeft == TopRight && BottomLeft == BottomRight && TopLeft == BottomLeft && TopRight == BottomRight)
	{
		return true;
	}
	return false;
}
Node* LinkedList::GetRightEnd(Node* current)
{
	Node* required = nullptr;
	Node* temp = current;
	while (temp != nullptr)
	{
		required = temp;
		temp = temp->next;
	}
	return required;
}
Node* LinkedList::GetLeftEnd(Node* current)
{
	Node* required = nullptr;
	Node* temp = current;
	while (temp != nullptr)
	{
		required = temp;
		temp = temp->previous;
	}
	return required;
}
Node* LinkedList::GetTopEnd(Node* current)
{
	Node* required = nullptr;
	Node* temp = current;
	while (temp != nullptr)
	{
		required = temp;
		temp = temp->top;
	}
	return required;
}
Node* LinkedList::GetBottomEnd(Node* current)
{
	Node* required = nullptr;
	Node* temp = current;
	while (temp != nullptr)
	{
		required = temp;
		temp = temp->bottom;
	}
	return required;
}
Node* LinkedList::GetNodeByPosition(string position)
{
	size_t cPos = position.find('C');
	size_t rPos = position.find('R');

	// Extract column and row substrings
	string colStr = position.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = position.substr(rPos + 1);

	// Convert strings to integers
	int col, row;
	istringstream(colStr) >> col;
	istringstream(rowStr) >> row;

	// Check if the linked list has enough rows and columns
	if (row <= 0 || col <= 0) {
		// Handle error or return nullptr, depending on your requirements
		return nullptr;
	}

	Node* temp = TopLeft;

	// Traverse columns
	for (int idx = 1; idx < col; idx++)
	{
		if (temp == nullptr) {
			// Handle error or return nullptr
			return nullptr;
		}
		temp = temp->next;
	}

	// Traverse rows
	for (int idx = 1; idx < row; idx++)
	{
		if (temp == nullptr || temp->bottom == nullptr) {
			// Handle error or return nullptr
			return nullptr;
		}
		temp = temp->bottom;
	}

	return temp;
}
void  LinkedList::SetValue(Node* current, string value)
{
	current->data = value;
}

void LinkedList::InsertAfter(Node* current, string value)
{
	Node* newNode = new Node(value);
	if (IsEmpty())
	{
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (OnlyOneCell())
	{
		current->next = newNode;
		newNode->previous = current;

		Node* emptyNode01 = new Node();
		Node* emptyNode02 = new Node();

		current->bottom = emptyNode01;
		emptyNode01->top = current;
		emptyNode01->next = emptyNode02;
		emptyNode02->previous = emptyNode01;
		newNode->bottom = emptyNode02;
		emptyNode02->top = newNode;

		TopRight = newNode;
		BottomRight = emptyNode02;
		BottomLeft = emptyNode01;
	}
	else if (IsTopRight(current))
	{
		current->next = newNode;
		newNode->previous = current;

		Node* temp01 = newNode;
		Node* temp = current->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopRight = newNode;
		BottomRight = GetBottomEnd(newNode);
	}
	else if (IsBottomRight(current))
	{
		current->next = newNode;
		newNode->previous = current;

		Node* temp01 = newNode;
		Node* temp = current->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->next = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}
		BottomRight = newNode;
		TopRight = GetTopEnd(newNode);
	}
	else if (current->next == nullptr)
	{
		newNode->previous = current;
		current->next = newNode;


		Node* temp01 = newNode;
		Node* temp = current->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->next = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = newNode;
		temp = current->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopRight = GetTopEnd(newNode);
		BottomRight = GetBottomEnd(newNode);
	}
	else if (IsTopLeft(current) || current->top == nullptr)
	{
		newNode->previous = current;
		newNode->next = current->next;
		newNode->bottom = current->bottom->next;
		current->bottom->next->top = newNode;
		current->next->previous = newNode;
		current->next = newNode;

		TopRight = GetRightEnd(newNode);

		Node* temp01 = TopRight;
		Node* temp = TopRight->bottom;
		while (temp != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		temp01 = newNode->bottom->next;
		temp = newNode->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->top = temp;
			temp->bottom = temp01;

			temp01 = temp01->next;
			temp = temp->next;
		}

		BottomRight = GetBottomEnd(TopRight);
	}
	else if (IsBottomLeft(current) || current->bottom == nullptr)
	{
		newNode->previous = current;
		newNode->next = current->next;
		newNode->top = current->top->next;
		current->top->next->bottom = newNode;
		current->next->previous = newNode;
		current->next = newNode;

		BottomRight = GetRightEnd(newNode);

		Node* temp01 = BottomRight;
		Node* temp = BottomRight->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->next = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = newNode->top->next;
		temp = newNode->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->bottom = temp;
			temp->top = temp01;
			temp01 = temp01->next;
			temp = temp->next;
		}
		TopRight = GetTopEnd(BottomRight);

	}
	else
	{
		newNode->previous = current;
		newNode->next = current->next;
		newNode->top = current->top->next;
		newNode->bottom = current->bottom->next;
		current->top->next->bottom = newNode;
		current->next->previous = newNode;
		current->bottom->next->top = newNode;
		current->next = newNode;

		Node* RightEnd = GetRightEnd(current);

		Node* temp01 = RightEnd;
		Node* temp = RightEnd->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->next = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = RightEnd;
		temp = RightEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		Node* temp02 = newNode->bottom->next;
		temp01 = newNode->top->next;
		temp = newNode->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->bottom = temp;
			temp->top = temp01;
			temp02->top = temp;
			temp->bottom = temp02;
			temp02 = temp02->next;
			temp01 = temp01->next;
			temp = temp->next;
		}
		TopRight = GetTopEnd(RightEnd);
		BottomRight = GetBottomEnd(RightEnd);
	}
}
void LinkedList::InsertBefore(Node* current, string value)
{
	Node* newNode = new Node(value);
	if (IsEmpty())
	{
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (OnlyOneCell())
	{
		current->previous = newNode;
		newNode->next = current;

		Node* emptyNode01 = new Node();
		Node* emptyNode02 = new Node();

		current->bottom = emptyNode01;
		emptyNode01->top = current;
		emptyNode01->previous = emptyNode02;
		emptyNode02->next = emptyNode01;
		newNode->bottom = emptyNode02;
		emptyNode02->top = newNode;

		TopLeft = newNode;
		BottomRight = emptyNode01;
		BottomLeft = emptyNode02;
	}
	else if (IsTopLeft(current))
	{
		current->previous = newNode;
		newNode->next = current;

		Node* temp01 = newNode;
		Node* temp = current->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopLeft = newNode;
		BottomLeft = GetBottomEnd(newNode);
	}
	else if (IsBottomLeft(current))
	{
		current->previous = newNode;
		newNode->next = current;

		Node* temp01 = newNode;
		Node* temp = current->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->previous = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->next = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}
		BottomLeft = newNode;
		TopLeft = GetTopEnd(newNode);
	}
	else if (current->previous == nullptr)
	{
		newNode->next = current;
		current->previous = newNode;


		Node* temp01 = newNode;
		Node* temp = current->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->previous = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->next = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = newNode;
		temp = current->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}


		TopLeft = GetTopEnd(newNode);
		BottomLeft = GetBottomEnd(newNode);
	}
	else if (IsTopRight(current) || current->top == nullptr)
	{
		newNode->next = current;
		newNode->previous = current->previous;
		newNode->bottom = current->bottom->previous;
		current->bottom->previous->top = newNode;
		current->previous->next = newNode;
		current->previous = newNode;

		TopLeft = GetLeftEnd(newNode);

		Node* temp01 = TopLeft;
		Node* temp = TopLeft->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		temp01 = newNode->bottom->previous;
		temp = newNode->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->top = temp;
			temp->bottom = temp01;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		BottomLeft = GetBottomEnd(TopLeft);
	}
	else if (IsBottomRight(current) || current->bottom == nullptr)
	{
		newNode->next = current;
		newNode->previous = current->previous;
		newNode->top = current->top->previous;
		current->top->previous->bottom = newNode;
		current->previous->next = newNode;
		current->previous = newNode;

		BottomLeft = GetLeftEnd(newNode);

		Node* temp01 = BottomLeft;
		Node* temp = BottomLeft->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->previous = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->next = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = newNode->top->previous;
		temp = newNode->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->bottom = temp;
			temp->top = temp01;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		TopLeft = GetTopEnd(BottomLeft);
	}
	else
	{
		newNode->next = current;
		newNode->previous = current->previous;
		newNode->top = current->top->previous;
		newNode->bottom = current->bottom->previous;
		current->top->previous->bottom = newNode;
		current->previous->next = newNode;
		current->bottom->previous->top = newNode;
		current->previous = newNode;

		Node* LeftEnd = GetLeftEnd(current);

		Node* temp01 = LeftEnd;
		Node* temp = LeftEnd->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->previous = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->next = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = LeftEnd;
		temp = LeftEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		Node* temp02 = newNode->bottom->previous;
		temp01 = newNode->top->previous;
		temp = newNode->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->bottom = temp;
			temp->top = temp01;
			temp02->top = temp;
			temp->bottom = temp02;
			temp02 = temp02->previous;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		TopLeft = GetTopEnd(LeftEnd);
		BottomLeft = GetBottomEnd(LeftEnd);
	}
}
void LinkedList::InsertAbove(Node* current, string value)
{
	Node* newNode = new Node(value);
	if (IsEmpty())
	{
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (OnlyOneCell())
	{
		current->top = newNode;
		newNode->bottom = current;

		Node* emptyNode01 = new Node();
		Node* emptyNode02 = new Node();

		current->next = emptyNode01;
		emptyNode01->previous = current;
		emptyNode01->top = emptyNode02;
		emptyNode02->bottom = emptyNode01;
		newNode->next = emptyNode02;
		emptyNode02->previous = newNode;

		TopLeft = newNode;
		TopRight = emptyNode02;
		BottomRight = emptyNode01;

	}
	else if (IsTopRight(current))
	{
		current->top = newNode;
		newNode->bottom = current;

		Node* temp01 = newNode;
		Node* temp = current->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->top = emptyNode;
			emptyNode->next = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}
		TopRight = newNode;
		TopLeft = GetLeftEnd(newNode);
	}
	else if (IsTopLeft(current))
	{
		current->top = newNode;
		newNode->bottom = current;

		Node* temp01 = newNode;
		Node* temp = current->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}
		TopLeft = newNode;
		TopRight = GetRightEnd(newNode);
	}
	else if (current->top == nullptr)
	{
		newNode->bottom = current;
		current->top = newNode;

		Node* temp01 = newNode;
		Node* temp = current->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->top = emptyNode;
			emptyNode->next = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = newNode;
		temp = current->next;
		while (temp != nullptr && temp01 != nullptr)
		{

			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}


		TopRight = GetRightEnd(newNode);
		TopLeft = GetLeftEnd(newNode);

	}
	else if (IsBottomRight(current) || current->next == nullptr)
	{
		newNode->bottom = current;
		newNode->top = current->top;
		newNode->previous = current->previous->top;
		current->previous->top->next = newNode;
		current->top->bottom = newNode;
		current->top = newNode;

		TopRight = GetTopEnd(newNode);

		Node* temp01 = TopRight;
		Node* temp = TopRight->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->top = emptyNode;
			emptyNode->next = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = newNode->previous->top;
		temp = newNode->top;
		while (temp != nullptr)
		{
			temp01->next = temp;
			temp->previous = temp01;
			temp01 = temp01->top;
			temp = temp->top;
		}


		TopLeft = GetLeftEnd(TopRight);
	}
	else if (IsBottomLeft(current) || current->previous == nullptr)
	{
		newNode->bottom = current;
		newNode->top = current->top;
		newNode->next = current->next->top;
		current->next->top->previous = newNode;
		current->top->bottom = newNode;
		current->top = newNode;

		TopLeft = GetTopEnd(newNode);

		Node* temp01 = TopLeft;
		Node* temp = TopLeft->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}

		temp01 = newNode->next->top;
		temp = newNode->top;
		while (temp != nullptr)
		{
			temp01->previous = temp;
			temp->next = temp01;
			temp01 = temp01->top;
			temp = temp->top;
		}

		TopRight = GetRightEnd(TopLeft);
	}
	else
	{
		newNode->bottom = current;
		newNode->top = current->top;
		newNode->next = current->next->top;
		newNode->previous = current->previous->top;
		current->previous->top->next = newNode;
		current->next->top->previous = newNode;
		current->top->bottom = newNode;
		current->top = newNode;

		Node* TopEnd = GetTopEnd(current);

		Node* temp01 = TopEnd;
		Node* temp = TopEnd->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->top = emptyNode;
			emptyNode->next = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = TopEnd;
		temp = TopEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{

			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}

		Node* temp02 = newNode->next->top;
		temp01 = newNode->previous->top;
		temp = newNode->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->next = temp;
			temp->previous = temp01;
			temp02->previous = temp;
			temp->next = temp02;
			temp02 = temp02->top;
			temp01 = temp01->top;
			temp = temp->top;
		}

		TopRight = GetRightEnd(TopEnd);
		TopLeft = GetLeftEnd(TopEnd);
	}
}
void LinkedList::InsertBelow(Node* current, string value)
{
	Node* newNode = new Node(value);
	if (IsEmpty())
	{
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (OnlyOneCell())
	{
		current->bottom = newNode;
		newNode->top = current;

		Node* emptyNode01 = new Node();
		Node* emptyNode02 = new Node();

		current->next = emptyNode01;
		emptyNode01->previous = current;
		emptyNode01->bottom = emptyNode02;
		emptyNode02->top = emptyNode01;
		newNode->next = emptyNode02;
		emptyNode02->previous = newNode;

		TopRight = emptyNode01;
		BottomRight = emptyNode02;
		BottomLeft = newNode;
	}
	else if (IsBottomRight(current))
	{
		current->bottom = newNode;
		newNode->top = current;

		Node* temp01 = newNode;
		Node* temp = current->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->next = temp01;
			emptyNode->top = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}
		BottomRight = newNode;
		BottomLeft = GetLeftEnd(newNode);
	}
	else if (IsBottomLeft(current))
	{
		current->bottom = newNode;
		newNode->top = current;

		Node* temp01 = newNode;
		Node* temp = current->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}
		BottomLeft = newNode;
		BottomRight = GetRightEnd(newNode);
	}
	else if (current->bottom == nullptr)
	{
		newNode->top = current;
		current->bottom = newNode;


		Node* temp01 = newNode;
		Node* temp = current->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->next = temp01;
			emptyNode->top = temp;

			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = newNode;
		temp = current->next;
		while (temp != nullptr && temp01 != nullptr)
		{

			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;

			temp01 = temp01->next;
			temp = temp->next;
		}

		BottomRight = GetRightEnd(newNode);
		BottomLeft = GetLeftEnd(newNode);

	}
	else if (IsTopRight(current) || current->next == nullptr)
	{
		newNode->top = current;
		newNode->bottom = current->bottom;
		newNode->previous = current->previous->bottom;
		current->previous->top->next = newNode;
		current->bottom->top = newNode;
		current->bottom = newNode;

		BottomRight = GetBottomEnd(newNode);

		Node* temp01 = BottomRight;
		Node* temp = BottomRight->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->next = temp01;
			emptyNode->top = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = newNode->previous->bottom;
		temp = newNode->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->next = temp;
			temp->previous = temp01;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		BottomLeft = GetLeftEnd(BottomRight);
	}
	else if (IsTopLeft(current) || current->previous == nullptr)
	{
		newNode->top = current;
		newNode->bottom = current->bottom;
		newNode->next = current->next->bottom;
		current->next->bottom->previous = newNode;
		current->bottom->top = newNode;
		current->bottom = newNode;


		BottomLeft = GetBottomEnd(newNode);

		Node* temp01 = BottomLeft;
		Node* temp = BottomLeft->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}

		temp01 = newNode->next->bottom;
		temp = newNode->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->previous = temp;
			temp->next = temp01;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		BottomRight = GetRightEnd(BottomLeft);
	}
	else
	{
		newNode->top = current;
		newNode->bottom = current->bottom;
		newNode->next = current->next->bottom;
		newNode->previous = current->previous->bottom;
		current->previous->bottom->next = newNode;
		current->next->bottom->previous = newNode;
		current->bottom->top = newNode;
		current->bottom = newNode;

		Node* BottomEnd = GetBottomEnd(current);

		Node* temp01 = BottomEnd;
		Node* temp = BottomEnd->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->next = temp01;
			emptyNode->top = temp;

			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = BottomEnd;
		temp = BottomEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{

			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;

			temp01 = temp01->next;
			temp = temp->next;
		}

		Node* temp02 = newNode->next->bottom;
		temp01 = newNode->previous->bottom;
		temp = newNode->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->next = temp;
			temp->previous = temp01;
			temp02->previous = temp;
			temp->next = temp02;
			temp02 = temp02->bottom;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		BottomRight = GetRightEnd(BottomEnd);
		BottomLeft = GetLeftEnd(BottomEnd);
	}
}

void LinkedList::InsertRowAbove(Node* current)
{
	Node* LeftEnd = GetLeftEnd(current);

	if (IsEmpty())
	{
		Node* newNode = new Node();
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (IsTopLeft(LeftEnd))
	{
		Node* firstNode = new Node();

		firstNode->bottom = LeftEnd;
		LeftEnd->top = firstNode;

		Node* temp01 = firstNode;
		Node* temp = LeftEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;

			temp01 = temp01->next;
			temp = temp->next;
		}
		TopLeft = firstNode;
		TopRight = GetRightEnd(firstNode);
	}
	else
	{
		Node* firstNode = new Node();

		firstNode->bottom = LeftEnd;
		firstNode->top = LeftEnd->top;
		LeftEnd->top->bottom = firstNode;
		LeftEnd->top = firstNode;

		Node* temp02 = firstNode;
		Node* temp01 = firstNode->top->next;
		Node* temp = LeftEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			emptyNode->previous = temp02;
			emptyNode->bottom = temp;
			emptyNode->top = temp01;
			temp02->next = emptyNode;
			temp->top = emptyNode;
			temp01->bottom = emptyNode;

			temp = temp->next;
			temp01 = temp01->next;
			temp02 = emptyNode;
		}
		TopLeft = GetTopEnd(LeftEnd);
		TopRight = GetRightEnd(TopLeft);
	}

}
void LinkedList::InsertRowBelow(Node* current)
{
	Node* LeftEnd = GetLeftEnd(current);

	if (IsEmpty())
	{
		Node* newNode = new Node();
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (IsBottomLeft(LeftEnd))
	{
		Node* firstNode = new Node();

		firstNode->top = LeftEnd;
		LeftEnd->bottom = firstNode;

		Node* temp01 = firstNode;
		Node* temp = LeftEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;

			temp01 = temp01->next;
			temp = temp->next;
		}
		BottomRight = firstNode;
		BottomLeft = GetLeftEnd(firstNode);
	}
	else
	{
		Node* firstNode = new Node();

		firstNode->top = LeftEnd;
		firstNode->bottom = LeftEnd->bottom;
		LeftEnd->bottom->top = firstNode;
		LeftEnd->bottom = firstNode;

		Node* temp02 = firstNode;
		Node* temp01 = firstNode->bottom->next;
		Node* temp = LeftEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			emptyNode->previous = temp02;
			emptyNode->top = temp;
			emptyNode->bottom = temp01;
			temp02->next = emptyNode;
			temp->bottom = emptyNode;
			temp01->top = emptyNode;

			temp = temp->next;
			temp01 = temp01->next;
			temp02 = emptyNode;
		}

		BottomLeft = GetBottomEnd(LeftEnd);
		BottomRight = GetRightEnd(BottomLeft);
	}
}

void LinkedList::InsertColumnAfter(Node* current)
{
	Node* TopEnd = GetTopEnd(current);

	if (IsEmpty())
	{
		Node* newNode = new Node();
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (IsTopRight(TopEnd))
	{
		Node* firstNode = new Node();

		firstNode->previous = TopEnd;
		TopEnd->next = firstNode;

		Node* temp01 = firstNode;
		Node* temp = TopEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopRight = firstNode;
		BottomRight = GetBottomEnd(firstNode);
	}
	else
	{
		Node* firstNode = new Node();

		firstNode->previous = TopEnd;
		firstNode->next = TopEnd->next;
		TopEnd->next->previous = firstNode;
		TopEnd->next = firstNode;

		Node* temp02 = firstNode;
		Node* temp01 = firstNode->next->bottom;
		Node* temp = TopEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			emptyNode->top = temp02;
			emptyNode->previous = temp;
			emptyNode->next = temp01;
			temp02->bottom = emptyNode;
			temp->next = emptyNode;
			temp01->previous = emptyNode;

			temp = temp->bottom;
			temp01 = temp01->bottom;
			temp02 = emptyNode;
		}

		TopRight = GetRightEnd(firstNode);
		BottomRight = GetBottomEnd(TopRight);

	}
}
void LinkedList::InsertColumnBefore(Node* current)
{
	Node* TopEnd = GetTopEnd(current);

	if (IsEmpty())
	{
		Node* newNode = new Node();
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (IsTopLeft(TopEnd))
	{
		Node* firstNode = new Node();

		firstNode->next = TopEnd;
		TopEnd->previous = firstNode;

		Node* temp01 = firstNode;
		Node* temp = TopEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;

			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopLeft = firstNode;
		BottomLeft = GetBottomEnd(firstNode);
	}
	else
	{
		Node* firstNode = new Node();

		firstNode->next = TopEnd;
		firstNode->previous = TopEnd->previous;
		TopEnd->previous->next = firstNode;
		TopEnd->previous = firstNode;

		Node* temp02 = firstNode;
		Node* temp01 = firstNode->previous->bottom;
		Node* temp = TopEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			emptyNode->top = temp02;
			emptyNode->next = temp;
			emptyNode->previous = temp01;
			temp02->bottom = emptyNode;
			temp->previous = emptyNode;
			temp01->next = emptyNode;

			temp = temp->bottom;
			temp01 = temp01->bottom;
			temp02 = emptyNode;
		}

		TopLeft = GetLeftEnd(firstNode);
		BottomLeft = GetBottomEnd(TopRight);
	}
}

void LinkedList::DeleteCellOfRow(Node* current)
{
	Node* temp = current;
	while (temp->next != nullptr)
	{
		temp->data = temp->next->data;

		temp = temp->next;
	}
	Node* RightEnd = GetRightEnd(current);
	RightEnd->data = "0";
}
void LinkedList::DeleteCellOfColumn(Node* current)
{
	Node* temp = current;
	while (temp->bottom != nullptr)
	{
		temp->data = temp->bottom->data;

		temp = temp->bottom;
	}
	Node* BottomEnd = GetBottomEnd(current);
	BottomEnd->data = "0";
}

void LinkedList::DeleteRow(Node* current)
{
	if (current->top == nullptr)
	{
		
		TopLeft = TopLeft->bottom;
		TopRight = TopRight->bottom;
		Node* temp = TopLeft;
		while (temp != nullptr)
		{
			temp->top = nullptr;
			temp = temp->next;
		}

	}
	else if (current->bottom == nullptr)
	{
		BottomLeft = BottomLeft->top;
		BottomRight = BottomRight->top;
		Node* temp = BottomLeft;
		while (temp != nullptr)
		{
			temp->bottom = nullptr;
			temp = temp->next;
		}
	}
	else
	{
		Node* temp = GetLeftEnd(current);
		while (temp != nullptr)
		{
			temp->top->bottom = temp->bottom;
			temp->bottom->top = temp->top;
			temp = temp->next;
		}

	}

}
void LinkedList::DeleteColumn(Node* current)
{
	if (current->next == nullptr)
	{
		TopRight = TopRight->previous;
		BottomRight = BottomRight->previous;
		Node* temp = TopRight;
		while (temp != nullptr)
		{
			temp->next = nullptr;
			temp = temp->bottom;
		}

	}
	else if (current->previous == nullptr)
	{
		TopLeft = TopLeft->next;
		BottomLeft = BottomLeft->next;
		Node* temp = TopLeft;
		while (temp != nullptr)
		{
			temp->previous = nullptr;
			temp = temp->bottom;
		}

	}
	else
	{
		Node* temp = GetTopEnd(current);
		while (temp != nullptr)
		{
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
			temp = temp->bottom;
		}
	}
}
void LinkedList::ClearRow(Node* current)
{
	Node* temp = GetLeftEnd(current);
	while (temp != nullptr)
	{
		temp->data = "0";
		temp = temp->next;
	}
}
void LinkedList::ClearColumn(Node* current)
{
	Node* temp = GetTopEnd(current);
	while (temp != nullptr)
	{
		temp->data = "0";
		temp = temp->bottom;
	}
}

string LinkedList::Sum(string start, string end)
{
	string answer;
	int ans = 0;
	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;

	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{
		Node* temp = starting;
		while (temp != ending->bottom)
		{
			ans += stoi(temp->data);
			temp = temp->bottom;
		}
	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			ans += stoi(temp->data);
			temp = temp->next;
		}
	}
	else
	{
		ans = stoi(starting->data) + stoi(ending->data);
	}
	answer = to_string(ans);
	return answer;
}
string LinkedList::Average(string start, string end)
{

	string answer;
	int ans = 0;
	int count = 0;
	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;

	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{

		Node* temp = starting;
		while (temp != ending->bottom)
		{
			ans += stoi(temp->data);
			if (temp->data != "0")
			{
				count++;
			}
			temp = temp->bottom;

		}
		ans = ans / count;

	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			ans += stoi(temp->data);
			if (temp->data != "0")
			{
				count++;
			}
			temp = temp->next;
		}
		ans = ans / count;
	}
	else
	{
		ans = stoi(starting->data) + stoi(ending->data);
		ans = ans / 2;
	}
	answer = to_string(ans);
	return answer;

}
string LinkedList::Count(string start, string end)
{
	int count = 0;
	string answer;
	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;


	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{
		Node* temp = starting;
		while (temp != ending->bottom)
		{
			if (temp->data != "0")
			{
				count++;
			}
			temp = temp->bottom;
		}
	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			if (temp->data != "0")
			{
				count++;
			}
			temp = temp->next;
		}
	}
	else
	{
		count = -1;
	}
	answer = to_string(count);
	return answer;
}
string LinkedList::Min(string start, string end)
{
	string answer;
	int min = 100000;
	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;

	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{
		Node* temp = starting;
		while (temp != ending->bottom)
		{
			if (min > stoi(temp->data))
			{
				min = stoi(temp->data);
			}
			temp = temp->bottom;
		}
	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			if (min > stoi(temp->data))
			{
				min = stoi(temp->data);
			}
			temp = temp->next;
		}
	}
	else
	{
		min = -1;
	}
	answer = to_string(min);
	return answer;
}
string LinkedList::Max(string start, string end)
{
	string answer;
	int max = -999;

	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;

	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{
		Node* temp = starting;
		while (temp != ending->bottom)
		{
			if (max < stoi(temp->data))
			{
				max = stoi(temp->data);
			}
			temp = temp->bottom;
		}
	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			if (max < stoi(temp->data))
			{
				max = stoi(temp->data);
			}
			temp = temp->next;
		}
	}
	else
	{
		max = -1;
	}
	answer = to_string(max);
	return answer;
}

vector<string> LinkedList::CutRow(string address)
{
	vector<string> data;
	Node* temp = GetNodeByPosition(address);
	Node* LeftEnd = GetLeftEnd(temp);
	while (temp != nullptr)
	{
		data.push_back(temp->data);
		temp->data = "0";
		temp = temp->next;
	}
	return data;
}
vector<string> LinkedList::CutColumn(string address)
{
	vector<string> data;
	Node* temp = GetNodeByPosition(address);
	Node* TopEnd = GetTopEnd(temp);
	while (temp != nullptr)
	{
		data.push_back(temp->data);
		temp->data = "0";
		temp = temp->bottom;
	}
	return data;
}
vector<string> LinkedList::CopyRow(string address)
{
	vector<string> data;
	Node* temp = GetNodeByPosition(address);
	Node* LeftEnd = GetLeftEnd(temp);
	while (temp != nullptr)
	{
		data.push_back(temp->data);
		temp = temp->next;
	}
	return data;
}
vector<string> LinkedList::CopyColumn(string address)
{
	vector<string> data;
	Node* temp = GetNodeByPosition(address);
	Node* TopEnd = GetTopEnd(temp);
	while (temp != nullptr)
	{
		data.push_back(temp->data);
		temp = temp->bottom;
	}
	return data;
}
void LinkedList::PasteRow(string address, vector<string> data)
{
	Node* temp = GetNodeByPosition(address);
	Node* LeftEnd = GetLeftEnd(temp);
	while (temp != nullptr)
	{
		temp->data = data.front();
		data.erase(data.begin());
		temp = temp->next;
	}
}
void LinkedList::PasteColumn(string address, vector<string> data)
{
	Node* temp = GetNodeByPosition(address);
	Node* TopEnd = GetTopEnd(temp);
	while (temp != nullptr)
	{
		temp->data = data.front();
		data.erase(data.begin());
		temp = temp->bottom;
	}
}

void LinkedList::LoadFromFile(const string& filename)
{
	ifstream file(filename);
	/*if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}*/

	string line;
	vector<vector<Node*>> nodes;

	// Read data from the file into nodes
	while (getline(file, line))
	{
		istringstream iss(line);
		vector<Node*> row;

		string value;
		while (getline(iss, value, ','))
		{
			row.push_back(new Node(value));
		}

		nodes.push_back(row);
	}

	// Make links between nodes
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		for (size_t j = 0; j < nodes[i].size(); ++j)
		{
			if (i > 0)
				nodes[i][j]->top = nodes[i - 1][j];
			if (i < nodes.size() - 1)
				nodes[i][j]->bottom = nodes[i + 1][j];
			if (j > 0)
				nodes[i][j]->previous = nodes[i][j - 1];
			if (j < nodes[i].size() - 1)
				nodes[i][j]->next = nodes[i][j + 1];
		}
	}

	// Set the corners
	TopLeft = nodes[0][0];
	TopRight = nodes[0][nodes[0].size() - 1];
	BottomLeft = nodes[nodes.size() - 1][0];
	BottomRight = nodes[nodes.size() - 1][nodes[nodes.size() - 1].size() - 1];

	file.close();
}
void LinkedList::StoreToFile(const string& filename)
{
	ofstream file(filename);
	/*if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}*/

	Node* current = TopLeft;

	while (current)
	{
		Node* rowStart = current;
		while (current)
		{
			file << current->data;
			if (current->next)
				file << ",";
			current = current->next;
		}

		file << "\n";
		current = rowStart->bottom;
	}

	file.close();
}


#pragma once
#include <wx/wx.h>

class App : public wxApp
{
public:
    virtual bool OnInit();
};

#include "App.h"
#include "MainFrame.h"
#include "Node.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("MiniExcel", wxPoint(50, 50), wxSize(800, 600));
    mainFrame->Center();
    mainFrame->Show();

    return true;
}
#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include"Node.h"
#include <wx/sizer.h>
#include <wx/event.h>

enum EventIDs
{
    ID_HelpItem = wxID_HIGHEST + 1,

    ID_DeleteCellOfRow = 401,
    ID_DeleteCellOfColumn,
    ID_DeleteRow,
    ID_DeleteColumn,
    ID_ClearRow,
    ID_ClearColumn,

    ID_FormulaSUM = 301,
    ID_FormulaMIN,
    ID_FormulaMAX,
    ID_FormulaCOUNT,
    ID_FormulaAVERAGE,

    ID_InsertRowAbove = 205,
    ID_InsertRowBelow,
    ID_InsertColumnRight,
    ID_InsertColumnLeft,
    ID_InsertValue,

    ID_CopyRow = 101,
    ID_CopyColumn,
    ID_CutRow,
    ID_CutColumn,
    ID_PasteRow,
    ID_PasteColumn,

    ID_GRID,
    ID_InsertAfter,
    ID_InsertBefore,
    ID_InsertAboveGrid,
    ID_InsertBelowGrid,
    
};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);


private:
    wxGrid* grid;
    wxPanel* panel;
    wxSizer* currentSizer;
    wxSizer* newSizer;
    string prevCellPosition;

    void OnCellLeftClick(wxGridEvent& event);
    void OnSize(wxSizeEvent& event);

    void OnInsertCellAfter(wxCommandEvent& event);
    void OnInsertCellBefore(wxCommandEvent& event);
    void OnInsertCellAbove(wxCommandEvent& event);
    void OnInsertCellBelow(wxCommandEvent& event);

    void OnInsertRowAbove(wxCommandEvent& event);
    void OnInsertRowBelow(wxCommandEvent& event);
    void OnInsertColumnRight(wxCommandEvent& event);
    void OnInsertColumnLeft(wxCommandEvent& event);
    void OnInsertValue(wxCommandEvent& event);

    void OnDeleteCellOfRow(wxCommandEvent& event);
    void OnDeleteCellOfColumn(wxCommandEvent& event);
    void OnDeleteRow(wxCommandEvent& event);
    void OnDeleteColumn(wxCommandEvent& event);
    void OnClearRow(wxCommandEvent& event);
    void OnClearColumn(wxCommandEvent& event);

    void OnFormulaSUM(wxCommandEvent& event);
    void OnFormulaMIN(wxCommandEvent& event);
    void OnFormulaMAX(wxCommandEvent& event);
    void OnFormulaCOUNT(wxCommandEvent& event);
    void OnFormulaAVERAGE(wxCommandEvent& event);

    void OnCopyRow(wxCommandEvent& WXUNUSED(event));
    void OnCopyColumn(wxCommandEvent& WXUNUSED(event));
    void OnCutRow(wxCommandEvent& WXUNUSED(event));
    void OnCutColumn(wxCommandEvent& WXUNUSED(event));
    void OnPasteRow(wxCommandEvent& WXUNUSED(event));
    void OnPasteColumn(wxCommandEvent& WXUNUSED(event));

    void OnFileSave(wxCommandEvent& event);
    void OnFileExit(wxCommandEvent& event);
   
    void OnHelp(wxCommandEvent& event);

    void CustomizeGrid();
    void UpdateGrid();
    void PrintValues();
    

    wxDECLARE_EVENT_TABLE();
};

#include "MainFrame.h"
#include"Node.h"
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/gbsizer.h>
#include <wx/event.h>
#include <sstream>
#include "LinkedList.h"


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)

EVT_GRID_CELL_LEFT_CLICK(MainFrame::OnCellLeftClick)

EVT_MENU(ID_InsertAfter, MainFrame::OnInsertCellAfter)
EVT_MENU(ID_InsertBefore, MainFrame::OnInsertCellBefore)
EVT_MENU(ID_InsertAboveGrid, MainFrame::OnInsertCellAbove)
EVT_MENU(ID_InsertBelowGrid, MainFrame::OnInsertCellBelow)

EVT_MENU(ID_InsertRowAbove, MainFrame::OnInsertRowAbove)
EVT_MENU(ID_InsertRowBelow, MainFrame::OnInsertRowBelow)

EVT_MENU(ID_InsertColumnRight, MainFrame::OnInsertColumnRight)
EVT_MENU(ID_InsertColumnLeft, MainFrame::OnInsertColumnLeft)
EVT_MENU(ID_InsertColumnLeft, MainFrame::OnInsertValue)

EVT_MENU(ID_DeleteCellOfRow, MainFrame::OnDeleteCellOfRow)
EVT_MENU(ID_DeleteCellOfColumn, MainFrame::OnDeleteCellOfColumn)
EVT_MENU(ID_DeleteRow, MainFrame::OnDeleteRow)
EVT_MENU(ID_DeleteColumn, MainFrame::OnDeleteColumn)
EVT_MENU(ID_ClearRow, MainFrame::OnClearRow)
EVT_MENU(ID_ClearColumn, MainFrame::OnClearColumn)

EVT_MENU(ID_FormulaSUM, MainFrame::OnFormulaSUM)
EVT_MENU(ID_FormulaMIN, MainFrame::OnFormulaMIN)
EVT_MENU(ID_FormulaMAX, MainFrame::OnFormulaMAX)
EVT_MENU(ID_FormulaCOUNT, MainFrame::OnFormulaCOUNT)
EVT_MENU(ID_FormulaAVERAGE, MainFrame::OnFormulaAVERAGE)

EVT_MENU(ID_CopyRow, MainFrame::OnCopyRow)
EVT_MENU(ID_CopyColumn, MainFrame::OnCopyColumn)
EVT_MENU(ID_CutRow, MainFrame::OnCutRow)
EVT_MENU(ID_CutColumn, MainFrame::OnCutColumn)
EVT_MENU(ID_PasteRow, MainFrame::OnPasteRow)
EVT_MENU(ID_PasteColumn, MainFrame::OnPasteColumn)

EVT_MENU(ID_HelpItem, MainFrame::OnHelp)

wxEND_EVENT_TABLE()

void GetAddressFromUser(string& start, string& end, string& destination);
Node* CreateInitiallyLinkedList();
string cellPosition;
LinkedList Excel;
vector<string> copied;


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), grid(new wxGrid(this, wxID_ANY))
{
    CreateInitiallyLinkedList();
    //Excel.LoadFromFile("excel.txt");
    

   

    PrintValues();
   
    // Create the menu bar
    wxMenuBar* menuBar = new wxMenuBar;

    // Create the File menu
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_SAVE, "Save");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "Exit");
    menuBar->Append(fileMenu, "File");

    // Create the Home menu
    wxMenu* homeMenu = new wxMenu;
    wxMenu* copySubMenu = new wxMenu;
    copySubMenu->Append(101, "Row");
    copySubMenu->Append(102, "Column");
    homeMenu->AppendSubMenu(copySubMenu, "Copy");
    wxMenu* cutSubMenu = new wxMenu;
    cutSubMenu->Append(103, "Row");
    cutSubMenu->Append(104, "Column");
    homeMenu->AppendSubMenu(cutSubMenu, "Cut");
    wxMenu* pasteSubMenu = new wxMenu;
    pasteSubMenu->Append(105, "Row");
    pasteSubMenu->Append(106, "Column");
    homeMenu->AppendSubMenu(pasteSubMenu, "Paste");
    menuBar->Append(homeMenu, "Home");

    // Create the Insert menu
    wxMenu* insertMenu = new wxMenu;
    wxMenu* insertCellSubMenu = new wxMenu;
    insertCellSubMenu->Append(201, "After");
    insertCellSubMenu->Append(202, "Before");
    insertCellSubMenu->Append(203, "Above");
    insertCellSubMenu->Append(204, "Below");
    insertMenu->AppendSubMenu(insertCellSubMenu, "Cell");
    wxMenu* insertRowSubMenu = new wxMenu;
    insertRowSubMenu->Append(205, "Above");
    insertRowSubMenu->Append(206, "Below");
    insertMenu->AppendSubMenu(insertRowSubMenu, "Row");
    wxMenu* insertColumnSubMenu = new wxMenu;
    insertColumnSubMenu->Append(207, "Right");
    insertColumnSubMenu->Append(208, "Left");
    insertMenu->AppendSubMenu(insertColumnSubMenu, "Column");
    insertMenu->Append(209, "Value");
    menuBar->Append(insertMenu, "Insert");

    // Create the Formulas menu
    wxMenu* formulasMenu = new wxMenu;
    formulasMenu->Append(301, "SUM");
    formulasMenu->Append(302, "MIN");
    formulasMenu->Append(303, "MAX");
    formulasMenu->Append(304, "COUNT");
    formulasMenu->Append(305, "AVERAGE");
    menuBar->Append(formulasMenu, "Formulas");

    // Create the Deletion menu
    wxMenu* deletionMenu = new wxMenu;
    wxMenu* deletionSubMenu = new wxMenu;
    wxMenu* cellSubMenu = new wxMenu;
    cellSubMenu->Append(401, "Of Row");
    cellSubMenu->Append(402, "Of Column");
    deletionMenu->AppendSubMenu(cellSubMenu, "Cell");
    deletionSubMenu->Append(403, "Row");
    deletionSubMenu->Append(404, "Column");
    deletionMenu->AppendSubMenu(deletionSubMenu, "Delete");
    wxMenu* clearSubMenu = new wxMenu;
    clearSubMenu->Append(405, "Row");
    clearSubMenu->Append(406, "Column");
    deletionMenu->AppendSubMenu(clearSubMenu, "Clear");
    menuBar->Append(deletionMenu, "Deletion");

    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(ID_HelpItem, "Help");
    menuBar->Append(helpMenu, "Help");
    // Set the menu bar
    SetMenuBar(menuBar);

    Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
    Bind(wxEVT_GRID_CELL_LEFT_CLICK, &MainFrame::OnCellLeftClick, this, ID_GRID);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFileSave, this, wxID_SAVE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFileExit, this, wxID_EXIT);

    Bind(wxEVT_MENU, &MainFrame::OnInsertCellAfter, this, ID_InsertAfter);
    Bind(wxEVT_MENU, &MainFrame::OnInsertCellBefore, this, ID_InsertBefore);
    Bind(wxEVT_MENU, &MainFrame::OnInsertCellAbove, this, ID_InsertAboveGrid);
    Bind(wxEVT_MENU, &MainFrame::OnInsertCellBelow, this, ID_InsertBelowGrid);

    Bind(wxEVT_MENU, &MainFrame::OnInsertRowAbove, this, ID_InsertRowAbove);
    Bind(wxEVT_MENU, &MainFrame::OnInsertRowBelow, this, ID_InsertRowBelow);
    Bind(wxEVT_MENU, &MainFrame::OnInsertColumnRight, this, ID_InsertColumnRight);
    Bind(wxEVT_MENU, &MainFrame::OnInsertColumnLeft, this, ID_InsertColumnLeft);
    Bind(wxEVT_MENU, &MainFrame::OnInsertValue, this, ID_InsertValue);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaSUM, this, ID_FormulaSUM);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaMIN, this, ID_FormulaMIN);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaMAX, this, ID_FormulaMAX);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaCOUNT, this, ID_FormulaCOUNT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaAVERAGE, this, ID_FormulaAVERAGE);

    Bind(wxEVT_MENU, &MainFrame::OnCopyRow, this, ID_CopyRow);
    Bind(wxEVT_MENU, &MainFrame::OnCopyColumn, this, ID_CopyColumn);
    Bind(wxEVT_MENU, &MainFrame::OnCutRow, this, ID_CutRow);
    Bind(wxEVT_MENU, &MainFrame::OnCutColumn, this, ID_CutColumn);
    Bind(wxEVT_MENU, &MainFrame::OnPasteRow, this, ID_PasteRow);
    Bind(wxEVT_MENU, &MainFrame::OnPasteColumn, this, ID_PasteColumn);
    Bind(wxEVT_MENU, &MainFrame::OnHelp, this, ID_HelpItem);

}

// Event handling methods in MainFrame class
void MainFrame::OnInsertCellAfter(wxCommandEvent& event) {
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertAfter(current, Svalue);
    UpdateGrid();

}
void MainFrame::OnInsertCellBefore(wxCommandEvent& event) {
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertBefore(current, Svalue);
    UpdateGrid();
}

void MainFrame::OnInsertCellAbove(wxCommandEvent& event) {
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertAbove(current, Svalue);
    UpdateGrid();
}

void MainFrame::OnInsertCellBelow(wxCommandEvent& event) {
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertBelow(current, Svalue);
    UpdateGrid();
}

void MainFrame::OnInsertRowAbove(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertRowAbove(current);
    UpdateGrid();
}

void MainFrame::OnInsertRowBelow(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertRowBelow(current);
    UpdateGrid();
}

void MainFrame::OnInsertColumnRight(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertColumnAfter(current);
    UpdateGrid();
}

void MainFrame::OnInsertColumnLeft(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertColumnBefore(current);
    UpdateGrid();
}

void MainFrame::OnInsertValue(wxCommandEvent& event)
{
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.SetValue(current,Svalue);
    UpdateGrid();
}

void MainFrame::OnDeleteCellOfRow(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.DeleteCellOfRow(current);
    UpdateGrid();
}

void MainFrame::OnDeleteCellOfColumn(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.DeleteCellOfColumn(current);
    UpdateGrid();
}

void MainFrame::OnDeleteRow(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.DeleteRow(current);
    UpdateGrid();
}

void MainFrame::OnDeleteColumn(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.DeleteColumn(current);
    UpdateGrid();
}

void MainFrame::OnClearRow(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.ClearRow(current);
    UpdateGrid();
}

void MainFrame::OnClearColumn(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.ClearColumn(current);
    UpdateGrid();
}

void MainFrame::OnFormulaSUM(wxCommandEvent& event)
{   
    string start , end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Sum(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnFormulaMIN(wxCommandEvent& event)
{
    string start, end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Min(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnFormulaMAX(wxCommandEvent& event)
{
    string start, end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Max(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnFormulaCOUNT(wxCommandEvent& event)
{
    string start, end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Count(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnFormulaAVERAGE(wxCommandEvent& event)
{
    string start, end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Average(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnCopyRow(wxCommandEvent& WXUNUSED(event)) {
   
    copied = Excel.CopyRow(cellPosition);
}

void MainFrame::OnCopyColumn(wxCommandEvent& WXUNUSED(event)) {

    copied = Excel.CopyColumn(cellPosition);
}

void MainFrame::OnCutRow(wxCommandEvent& WXUNUSED(event)) {

    copied = Excel.CutRow(cellPosition);
    UpdateGrid();
}

void MainFrame::OnCutColumn(wxCommandEvent& WXUNUSED(event)) {

    copied = Excel.CutColumn(cellPosition);
    UpdateGrid();
}

void MainFrame::OnPasteRow(wxCommandEvent& WXUNUSED(event)) {
    
    Excel.PasteRow(cellPosition, copied);
    UpdateGrid();
}
void MainFrame::OnPasteColumn(wxCommandEvent& WXUNUSED(event)) {

    Excel.PasteColumn(cellPosition, copied);
    UpdateGrid();
}

void MainFrame::OnFileSave(wxCommandEvent& event)
{
    //Excel.StoreToFile("excel.txt");
}
void MainFrame::OnFileExit(wxCommandEvent& event)
{
    Close(true);
}
void MainFrame::OnSize(wxSizeEvent& event)
{
    Layout();
    event.Skip();
}

void MainFrame::OnHelp(wxCommandEvent& event)
{
    wxMessageBox("Before every function/task implementation you have to select cell every time.The cel will be selected with left click of mouse.\n Every thing should be done by mouse and there is no funtion which is imolemented by keyboard. ", "Help Menu", wxOK | wxICON_INFORMATION, this);
}


void MainFrame::CustomizeGrid() {
    // Set row labels (1, 2, 3, ...)
    for (int row = 0; row < grid->GetNumberRows(); ++row) {
        grid->SetRowLabelValue(row, wxString::Format("%d", row + 1));
    }

    // Set column labels (A, B, C, ...)
    for (int col = 0; col < grid->GetNumberCols(); ++col) {
        grid->SetColLabelValue(col, wxString::Format("%d", col + 1));
        grid->SetColSize(col, 80);  // Set the width of each column
    }

    // Set the height of each row
    for (int row = 0; row < grid->GetNumberRows(); ++row) {
        grid->SetRowSize(row, 30);  // Set the height of each row
    }
    // Enable row and column labels
    grid->SetRowLabelSize(wxGRID_AUTOSIZE);
    grid->SetColLabelSize(wxGRID_AUTOSIZE);
}

void MainFrame::OnCellLeftClick(wxGridEvent& event) {
    string previousPosition;
    previousPosition = cellPosition;
    size_t cPos = previousPosition.find('C');
    size_t rPos = previousPosition.find('R');

    // Extract column and row substrings
    string colStr = previousPosition.substr(cPos + 1, rPos - cPos - 1);
    string rowStr = previousPosition.substr(rPos + 1);

    // Convert strings to integers
    int Pcol, Prow;
    istringstream(colStr) >> Pcol;
    istringstream(rowStr) >> Prow;
    Pcol--;
    Prow--;

    int row = event.GetRow();
    int col = event.GetCol();

    wxString position = wxString::Format("C%dR%d", col + 1, row + 1);
    cellPosition = position.ToStdString();
    if (grid) {
        // Set the background color of the clicked cell to baby pink
        grid->SetCellBackgroundColour(Prow, Pcol, wxColour(255, 255, 255));
        grid->SetCellBackgroundColour(row, col, wxColour(255, 182, 193));  // RGB for baby pink
        grid->Refresh();  // Refresh the grid to apply the color change
    }


    
}

void MainFrame::UpdateGrid()
{
    grid->ClearGrid();
    PrintValues();
    grid->Refresh();
}

void MainFrame::PrintValues()
{
    
    // Assuming you have these member variables in your class
    panel = nullptr;
    currentSizer = nullptr; 
    newSizer = nullptr;      
    grid = nullptr;

    // Set up your grid and other initialization code here
    grid = new wxGrid(this, ID_GRID);  // Use the frame as the parent, and assign an ID
    grid->CreateGrid(20, 16);
    grid->AutoSizeColumns();
    grid->AutoSizeRows();

    // Set the height of each row
    for (int row = 0; row < grid->GetNumberRows(); ++row) {
        grid->SetRowSize(row, 30);  // Set the height of each row
    }

    // Set the width of each column
    for (int col = 0; col < grid->GetNumberCols(); ++col) {
        grid->SetColSize(col, 80);  // Set the width of each column
    }

    Node* temp = Excel.TopLeft;
    int row = 0;
    while (temp != nullptr)
    {
        Node* rowStart = temp;
        int col = 0;
        while (temp != nullptr)
        {
            grid->SetCellValue(row, col, wxString::FromUTF8(temp->data.c_str()));
            temp = temp->next;
            col++;
        }
        temp = rowStart->bottom;
        row++;
    }
    grid->GetCellValue(0, 0);
    for (int row = 0; row < grid->GetNumberRows(); ++row)
    {
        for (int col = 0; col < grid->GetNumberCols(); ++col)
        {
            wxString value = grid->GetCellValue(row, col);
            wxPrintf(value);
        }
    }


    // Customize the grid
    CustomizeGrid();

    // Set up the layout with wxGridSizer
    wxGridSizer* sizer = new wxGridSizer(0, 0, 0, 0);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 0);

    if (!panel)
    {
        panel = new wxPanel(this, wxID_ANY);
    }

    if (panel->GetContainingSizer()) {
        wxSizer* currentContainingSizer = panel->GetContainingSizer();
        currentContainingSizer->Detach(panel);
    }

    panel->SetSizerAndFit(sizer);

    // Add the panel to the current sizer
    if (!currentSizer) {
        currentSizer = new wxBoxSizer(wxHORIZONTAL);  
    }
    currentSizer->Add(panel, 1, wxEXPAND);

    panel->SetSizerAndFit(newSizer);

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(currentSizer, 1, wxEXPAND);
    SetSizerAndFit(frameSizer);

    // Show the frame
    Show(true);

} 

void GetAddressFromUser(string& start, string& end, string& destination)
{
    wxString starting, ending, final;

    starting = wxGetTextFromUser("Location Of Starting Cell:", "Input", "", NULL);
    ending = wxGetTextFromUser("Location Of Ending Cell:", "Input", "", NULL);
    final = wxGetTextFromUser("Location for Answer:", "Input", "", NULL);
    start = starting.ToStdString();
    end = ending.ToStdString();
    destination = final.ToStdString();

}
Node* CreateInitiallyLinkedList()
{
    Excel.InsertAfter(Excel.TopLeft, "1");
    Excel.InsertAfter(Excel.TopLeft, "2");
    Excel.InsertAfter(Excel.TopLeft, "3");
    Excel.InsertAfter(Excel.TopLeft, "4");
    Excel.InsertAfter(Excel.TopLeft, "5");
    Excel.InsertBelow(Excel.TopLeft, "6");
    Excel.InsertBelow(Excel.TopLeft, "7");
    Excel.InsertBelow(Excel.TopLeft, "8");
    return Excel.TopLeft;
}
