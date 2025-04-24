#include "StackList.h"
void StackList::push(const ValueType& value)
{
    data.push_back(value);
}
void StackList::pop()
{
    data.pop_back();
}
const ValueType& StackList::top() const
{
    return data.back();
}
bool StackList::isEmpty() const
{
    return data.empty();
}
size_t StackList::size() const
{
    return data.get_len();
}