#include <iostream>
#include <ostream>
#include <queue/queue.h>
#include<memory>
#include<queue>
#include <vector>
#include <algorithm>

QueueP::QueueP(const std::vector<int>& values)
{
    for (int i; i < values.size(); i++)
    {
        push(values[i]);
    }
}
QueueP::~QueueP()
{
    while (head)
    {
        head = std::move(head->pNext);
    }
}
bool QueueP::isEmpty() const
{
    return head == nullptr;
}

QueueP::QueueP(const QueueP& copy) : head(nullptr)
{
    if (copy.isEmpty()) return;
    head = std::make_unique<Node>();
    head->v = copy.top();
    Node* iter_new = head.get();
   const  Node* iter_copy = copy.head.get();//?
   while (iter_copy != nullptr)
   {
       iter_new->pNext = std::make_unique<Node>();
       iter_new = iter_new->pNext.get();
       iter_new->v = iter_copy->v;
       iter_copy = iter_copy->pNext.get();
   }
   return;
}
bool QueueP::operator==(const QueueP& rhs) const
{
    Node* lhs1 = head.get();
    Node* rhs1 = rhs.head.get();
    while (lhs1 != nullptr && rhs1 != nullptr)
    {
        if (lhs1->v != rhs1->v)
            return false;
        lhs1 = (lhs1->pNext).get();
        rhs1 = (rhs1->pNext).get();

    }
    return true;

}
void QueueP::push( int new_val)
{
    Node *tmp=head.get();
    while (new_val >= ((tmp->pNext)->v) && tmp->pNext != nullptr)
    {
        tmp = (tmp->pNext).get();
    }
    std::unique_ptr<Node> new_tmp = std::make_unique<Node>();
    new_tmp->v = new_val;
    new_tmp->pNext = std::move(tmp->pNext);;
    tmp->pNext = std::move(new_tmp->pNext);
}

int QueueP::top() const
{
    return head->v;
}

void QueueP::pop()
{
    if (isEmpty())
    {
        return;
    }
    head = std::move(head->pNext);
}
std::ostream& QueueP::WriteTo(std::ostream& ostream) const
{
    const Node* itr = head.get();
    while (itr != nullptr)
    {
        ostream << itr->v << ' ';
        itr = itr->pNext.get();

    }
    return ostream;
}