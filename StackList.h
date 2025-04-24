#pragma once
#include "StackImplementation.h"
#include "ForwardList.h"
class StackList: public IStackImplementation
{
public:
    virtual void push(const ValueType& value) override;
    virtual void pop() override;
    virtual const ValueType& top() const override;
    virtual bool isEmpty() const override;
    virtual size_t size() const override;
    virtual ~StackList() override = default;
private:
    ForwardList data;
};