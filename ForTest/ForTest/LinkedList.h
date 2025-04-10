#pragma once
#include "Node.h"

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
	void InsertAfter(Node* current, string value);
	void InsertBefore(Node* current, string value);
	void InsertAbove(Node* current, string value);
	void InsertBelow(Node* current, string value);

};

