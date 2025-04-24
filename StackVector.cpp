#include "StackVector.h"
void StackVector::push(const ValueType& value)
{
    data.pushBack(value);
}
void StackVector::pop()
{
    data.popBack();
}
const ValueType& StackVector::top() const
{
    return data[data.size() - 1];
}
bool StackVector::isEmpty() const
{
    return data.empty();
}
size_t StackVector::size() const
{
    return data.size();
}
