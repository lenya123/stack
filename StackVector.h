#pragma once
#include "StackImplementation.h"
#include "Vector.h"
class StackVector: public IStackImplementation
{
public:
    virtual void push(const ValueType& value) override;
    virtual void pop() override;
    virtual const ValueType& top() const override;
    virtual bool isEmpty() const override;
    virtual size_t size() const override;
    virtual ~StackVector() override = default;
private:
    Vector data;
};