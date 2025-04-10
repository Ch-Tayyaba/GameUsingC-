#include "LinkedList.h"
#include "Node.h"
#include<string>
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

