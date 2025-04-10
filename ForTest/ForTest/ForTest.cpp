#pragma once
#include"Node.h"
#include"LinkedList.h"
#include<iostream>
using namespace std;

int main()
{
    LinkedList Excel;
    Excel.InsertAfter(Excel.TopLeft, "01");
    Excel.InsertAfter(Excel.TopRight, "02");
    Excel.InsertAfter(Excel.TopLeft->bottom, "03");
    Excel.InsertAfter(Excel.TopRight->bottom, "04");
    Excel.InsertAfter(Excel.BottomLeft, "05");
    Excel.InsertBelow(Excel.BottomLeft, "06");
    Excel.InsertBelow(Excel.TopRight->previous, "07");
    Excel.InsertBelow(Excel.BottomRight->top, "08");
    Excel.InsertAbove(Excel.BottomRight->previous, "09");
    Excel.InsertAbove(Excel.BottomLeft->top, "10");
    Excel.InsertAbove(Excel.TopLeft, "11");
    Excel.InsertBefore(Excel.TopLeft->next->next, "12");
    Excel.InsertBefore(Excel.TopRight->previous->bottom, "13");
    Excel.InsertBefore(Excel.TopLeft, "14");

    Node* temp = Excel.TopLeft;
    int row = 0;
    while (temp != nullptr)
    {
        Node* rowStart = temp;
        int col = 0;
        while (temp != nullptr)
        {
            cout << temp->data << "   ";
            temp = temp->next;

            col++;
        }
        cout << endl;
        temp = rowStart->bottom;
        row++;
    }




    return 0;
}