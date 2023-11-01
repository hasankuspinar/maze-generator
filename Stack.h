//
// Created by Hasan on 25.10.2023.
//

#ifndef CS300HOMEWORK01_STACK_H
#define CS300HOMEWORK01_STACK_H
template <class Obj>
class Stack
{
private:
struct Node
{
    Obj element;
    Node * next;
    Node (const Obj & elem, Node * p)
            : element(elem), next(p)
    {};
};
    Node * topList;
public:
    Stack( );
    Stack( const Stack<Obj> & rhs );
    ~Stack( );

    bool isEmpty( ) const;
    void makeEmpty( );

    void pop( );
    void push( const Obj & x );
    Obj topAndPop( );
    const Obj & top( ) const;

    const Stack<Obj> & operator=( const Stack<Obj> & rhs );


};


#endif //CS300HOMEWORK01_STACK_H
#include "Stack.cpp"