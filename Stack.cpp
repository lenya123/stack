#include "Stack.h"
#include "StackVector.h"
#include "StackList.h"
Stack::Stack(StackContainer container): _containerType(container)
{
    switch (_containerType)
    {
    case StackContainer::Vector:
        _pimpl = new StackVector();
        break;
    case StackContainer::List:
        _pimpl = new StackList();
        break;
    default:
        throw std::invalid_argument("dont have a container this type");
    }
}
Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container): _containerType(container)
{
    if (arraySize > 0 && valueArray == nullptr)
    {
        throw std::invalid_argument("nullptr");
    }
    switch (_containerType)
    {
    case StackContainer::Vector:
        _pimpl = new StackVector();
        break;
    case StackContainer::List:
        _pimpl = new StackList();
        break;
    default:
        throw std::invalid_argument("dont have a container this type");
    }
    for (size_t i = 0; i < arraySize; i++)
    {
        _pimpl -> push(valueArray[i]);
    }
}
Stack::Stack(const Stack& copyStack): _containerType(copyStack._containerType)
{
    switch (_containerType)
    {
        case StackContainer::Vector:
            _pimpl = new StackVector(*dynamic_cast<StackVector*>(copyStack._pimpl));
            break;
        case StackContainer::List:
            _pimpl = new StackList(*dynamic_cast<StackList*>(copyStack._pimpl));
            break;
        default:
        throw std::invalid_argument("dont have a container this type");
    }
}
Stack& Stack::operator=(const Stack& copyStack)
{
    if (this != &copyStack)
    {
        delete _pimpl;
        _containerType = copyStack._containerType;
        switch (_containerType)
        {
            case StackContainer::Vector:
                _pimpl = new StackVector(*dynamic_cast<StackVector*>(copyStack._pimpl));
                break;
            case StackContainer::List:
                _pimpl = new StackList(*dynamic_cast<StackList*>(copyStack._pimpl));
                break;
            default:
            throw std::invalid_argument("dont have a container this type");
        }
    }
    return *this;
}
Stack::Stack(Stack&& moveStack) noexcept : _pimpl(moveStack._pimpl), _containerType(moveStack._containerType)
{
    moveStack._pimpl = nullptr;
}
Stack& Stack::operator=(Stack&& moveStack) noexcept
{
    if (this != &moveStack)
    {
        delete _pimpl;
        _pimpl = moveStack._pimpl;
        _containerType = moveStack._containerType;
        moveStack._pimpl = nullptr;
    }
    return *this;
}
Stack::~Stack()
{
    delete _pimpl;
    _pimpl = nullptr;
}
void Stack::push(const ValueType& value)
{
    _pimpl -> push(value);
}
void Stack::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("empty container");
    }
    _pimpl -> pop();
}
const ValueType& Stack::top() const
{
    if (isEmpty())
    {
        throw std::runtime_error("empty container");
    }
    return _pimpl -> top();
}
bool Stack::isEmpty() const
{
    return _pimpl -> isEmpty();
}
size_t Stack::size() const
{
    return _pimpl -> size();
}
