#ifndef QueueP_07092022
#define QueueP_07092022
#pragma once
//#indef QueueP;
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include<map>
typedef int handle;
class QueueP
{
public:
    QueueP()=default;
    QueueP(const std::vector<int>& values) {};
    ~QueueP() {};
    bool operator==(const QueueP& rhs) const;
    QueueP(const QueueP& copy) {};
    bool isEmpty() const;
    struct Node {
        int v{ 0 };
        std::unique_ptr<Node> pNext;
        Node() :v(0), pNext(nullptr){}
        Node(int v) :v(v), pNext(nullptr) {}
        ~Node()
        {

        };
    };
    void push(int new_val);
    void pop();
    int top() const;
    std::ostream& WriteTo(std::ostream& ostream) const;
private:
    int size{0};
    std::unique_ptr<Node> head{ nullptr };
    std::unique_ptr<Node> tail{nullptr};
};
class Manager {
public:
    std::map<handle, QueueP> data;
    //static int  next = 0;
    //if(v.find(x)==)//валидный или мусор
    static int push(handle* id, int x)//что handle указатель
    {
        data[id].push(x);
    }
    ~Manager() 
    {

    };

private:
    handle i;
    QueueP Q;
};
int Push(handle* id, int x)
{
    Manager::push(id, x);
}

std::ostream& operator<<(std::ostream& ostream,const QueueP& val)
{
    
    return val.WriteTo(ostream);
}
std::istream& operator>>(std::istream& istream, QueueP& val)
{
    std::vector<int> c;
    for (int i = 0; i < c.size(); i++)
    {
        istream >> c[i];
        val.push(c[i]);
    }
    return istream;
}
#endif
