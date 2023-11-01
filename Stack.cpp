//
// Created by Hasan on 25.10.2023.
//

//#include "Stack.h"
#include <string>

template <class Obj>
Stack<Obj>::Stack() //default constructor
{
    topList = NULL;
}

template <class Obj>
const Stack<Obj> & Stack<Obj>::operator=( const Stack<Obj> & rhs ) //overloading the assignment operator for deep copying
{
    if(this != rhs)
    {
        makeEmpty();
        if(rhs.isEmpty())
        {
            return *this;
        }
        Node * rptr = rhs.topList;
        topList = new Node(rptr->element, NULL);
        Node * ptr = topList;
        while(rptr->next != NULL)
        {
            ptr->next = rptr->next;
            rptr = rptr->next;
            ptr = ptr->next;
        }
    }
    return *this;
}

template <class Obj>
Stack<Obj>::Stack(const Stack<Obj> &rhs) //deep copy constructor
{
    *this = rhs;
}

template <class Obj>
bool Stack<Obj>::isEmpty() const //returns true if the list is empty, false otherwise
{
    return topList == NULL;
}

template <class Obj>
void Stack<Obj>::makeEmpty() //removes all the elements in the list
{
    while(!isEmpty())
    {
        pop();
    }
}

template <class Obj>
const Obj & Stack<Obj>::top() const // returns the top of the list
{
    if(!isEmpty())
    {
        return topList->element;
    }
}

template <class Obj>
void Stack<Obj>::pop() //removes the top element
{
    if(!isEmpty())
    {
        Node * temp = topList;
        topList = topList->next;
        delete temp;
    }
}

template <class Obj>
Obj Stack<Obj>::topAndPop() //removes the top element and returns it
{
    Obj topItem = top();
    pop();
    return topItem;
}

template <class Obj>
void Stack<Obj>::push(const Obj &x) //insert a new element at the front of the list
{
    topList = new Node(x,topList);
}

template <class Obj>
Stack<Obj>::~Stack()
{
    makeEmpty();
}


