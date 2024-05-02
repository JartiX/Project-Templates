#pragma once

#ifndef _LINELIST_H
#define _LINELIST_H
#include <iostream>
using namespace std;

template <class T>
class LineListElem
{
    T data;
    LineListElem *next;

public:
    LineListElem(const T &adata, LineListElem *anext);
    const T &getData() const;
    LineListElem *getNext();
    template <class t>
    friend class LineList;
};

class LineListException
{
};

template <class T>
class LineList
{
    LineList(const LineList &list);
    int size;

public:
    LineListElem<T> *start;
    LineList();
    ~LineList();
    LineListElem<T> *getStart();
    int getSize();

    void deleteFirst();
    void deleteAfter(LineListElem<T> *ptr);
    void insertFirst(const T &data);
    void insertAfter(LineListElem<T> *ptr, const T &data);

    template <class t>
    friend ostream &operator<<(ostream &out, LineList &list);
};

template <class T>
LineListElem<T>::LineListElem(const T &adata, LineListElem<T> *anext)
{
    data = adata;
    next = anext;
}

template <class T>
const T &LineListElem<T>::getData() const
{
    return data;
}

template <class T>
LineListElem<T> *LineListElem<T>::getNext()
{
    return next;
}

template <class T>
LineList<T>::LineList()
{
    start = 0;
    size = 0;
}

template <class T>
LineList<T>::~LineList()
{
    while (start)
    {
        deleteFirst();
    }
}

template <class T>
LineListElem<T> *LineList<T>::getStart()
{
    return start;
}

template <class T>
void LineList<T>::deleteFirst()
{
    if (start)
    {
        LineListElem<T> *temp = start->next;
        delete start;
        start = temp;
        size--;
    }
    else
        throw LineListException();
}

template <class T>
void LineList<T>::deleteAfter(LineListElem<T> *ptr)
{
    if (ptr && ptr->next)
    {
        LineListElem<T> *temp = ptr->next;
        ptr->next = ptr->next->next;
        delete temp;
        size--;
    }
    else
        throw LineListException();
}

template <class T>
void LineList<T>::insertFirst(const T &data)
{
    LineListElem<T> *second = start;
    start = new LineListElem<T>(data, second);
    size++;
}

template <class T>
void LineList<T>::insertAfter(LineListElem<T> *ptr, const T &data)
{
    if (ptr)
    {
        LineListElem<T> *temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
    }
    size++;
}

template <class T>
ostream &operator<<(ostream &out, LineList<T> &list)
{
    LineListElem<T> *ptr = list.start;
    if (!ptr)
        out << "EMPTY ";
    else
        while (ptr)
        {
            out << ptr->getData() << ' ';
            ptr = ptr->getNext();
        }
    return out;
}

template <class T>
int LineList<T>::getSize() {
    return size;
}
#endif