#include "Vector.h"
#include <iostream>
#include <cstring>
#include <cmath>
Vector::Vector(const ValueType* rawArray, const size_t size, float coef)
{
    _size = size;
    _capacity = _size;
    _multiplicativeCoef = coef;
    _data = (_capacity > 0) ? new ValueType[_capacity] : nullptr;

    if (_size > 0)
    {
        std::memcpy(_data, rawArray, size * sizeof(ValueType));
    }
}
Vector::Vector(const Vector& other): _size(other._size), _capacity(other._size), _multiplicativeCoef(other._multiplicativeCoef)
{
    _data = new ValueType[_capacity];
    std::memcpy(_data, other._data, _size * sizeof(ValueType));
}
Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] _data;
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = new ValueType[_capacity];
    std::memcpy(_data, other._data, _size * sizeof(ValueType));

    return *this;
}
Vector::Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity), _multiplicativeCoef(other._multiplicativeCoef)
{
    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
}
Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }


    delete[] _data;
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;

    return *this;
}
Vector::~Vector()
{
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

bool Vector::empty() const
{
    return _size == 0;
}

void Vector::pushBack(const ValueType& value)
{
    if (_size == _capacity)
    {
        if (_capacity == 0)
    	{
        	_capacity = std::ceil(static_cast<size_t>(_multiplicativeCoef));
        	_data = new ValueType[_capacity];
    	}
    	else
    	{
        	_capacity = static_cast<size_t>(std::ceil(_capacity * _multiplicativeCoef));
        	ValueType* newdata = new ValueType[_capacity];
        	std::memcpy(newdata, _data, _size * sizeof(ValueType));
        	delete[] _data;
        	_data = newdata;
        	newdata = nullptr;
    	}
    }

    	_data[_size] = value;
    	_size++;
}
void Vector::pushFront(const ValueType& value)
{
    if (_size == _capacity)
    {
        if (_capacity == 0)
    	{
        	_capacity = std::ceil(static_cast<size_t>(_multiplicativeCoef));
        	_data = new ValueType[_capacity];
    	}
    	else
    	{
        	_capacity = static_cast<size_t>(std::ceil(_capacity * _multiplicativeCoef));
        	ValueType* newdata = new ValueType[_capacity];
        	std::memcpy(newdata, _data, _size * sizeof(ValueType));
        	delete[] _data;
        	_data = newdata;
        	newdata = nullptr;
    	}
    }

    for (size_t i = _size; i > 0; i--)
    {
        _data[i] = _data[i - 1];
    }

    _data[0] = value;
    _size++;
}
void Vector::insert(const ValueType& value, size_t pos)
{
    for (size_t i = _size; i > pos; i--)
    {
        _data[i] = _data[i - 1];
    }

    _data[pos] = value;
    _size++;
}
void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
    while (_capacity <= (_size + size))
    {
        if (_capacity == 0)
    	{
        	_capacity = std::ceil(static_cast<size_t>(_multiplicativeCoef));
        	_data = new ValueType[_capacity];
    	}
    	else
    	{
        	_capacity = static_cast<size_t>(std::ceil(_capacity * _multiplicativeCoef));
        	ValueType* newdata = new ValueType[_capacity];
        	std::memcpy(newdata, _data, _size * sizeof(ValueType));
        	delete[] _data;
        	_data = newdata;
        	newdata = nullptr;
    	}
    }

    for (size_t i = _size; i > pos; i--)
    {
        _data[i + size - 1] = _data[i - 1];
    }

    for (size_t j = 0; j < size; j++)
    {
        _data[pos + j] = values[j];
    }

    _size += size;
}
void Vector::insert(const Vector& vector, size_t pos)
{
    while (_capacity <= (_size + vector._size))
    {
        if (_capacity == 0)
    	{
        	_capacity = std::ceil(static_cast<size_t>(_multiplicativeCoef));
        	_data = new ValueType[_capacity];
    	}
    	else
    	{
        	_capacity = static_cast<size_t>(std::ceil(_capacity * _multiplicativeCoef));
        	ValueType* newdata = new ValueType[_capacity];
        	std::memcpy(newdata, _data, _size * sizeof(ValueType));
        	delete[] _data;
        	_data = newdata;
        	newdata = nullptr;
    	}
    }

    for (size_t i = _size; i > pos; i--)
    {
        _data[i + vector._size - 1] = _data[i - 1];
    }

    for (size_t j = 0; j < vector._size; j++)
    {
        _data[pos + j] = vector._data[j];
    }

    _size += vector._size;
}
void Vector::popBack()
{
    if (_size == 0)
    {
        throw std::underflow_error("Empty vector");
    }

    _size--;
}
void Vector::popFront()
{
    if (_size == 0)
    {
        throw std::underflow_error("Empty vector");
    }

    for (size_t i = 1; i < _size; ++i)
    {
        _data[i - 1] = _data[i];
    }
    
    _size--;
}

void Vector::erase(size_t pos, size_t count)
{
    if ((pos + count) > _size)
    {
        count = _size - pos;
    }

    for (size_t i = pos; i < _size - count; ++i)
    {
        _data[i] = _data[i + count];
    }

    _size -= count;

    for (size_t i = _size; i < _size + count; ++i)
    {
        _data[i] = ValueType();
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    ValueType* newdata = new ValueType[_size - (endPos - beginPos)];
    size_t counter = 0;

    for (size_t i = 0; i < _size; i++)
    {
        if (i < beginPos || i >= endPos)
        {
            newdata[counter] = _data[i];
            counter++;
        }
    }

    delete[] _data;
    _data  = newdata;
    newdata = nullptr;
    _size = _size - (endPos - beginPos);
}
size_t Vector::size() const
{
    return _size;
}
size_t Vector::capacity() const
{
    return _capacity;
}
double Vector::loadFactor() const
{
    return (_capacity == 0) ? 0.0 : _size / _capacity;
}
ValueType& Vector::operator[](size_t idx)
{
    if (idx >= _size)
    {
        throw std::out_of_range("Vector index out of range");
    }

    return _data[idx];
}
const ValueType& Vector::operator[](size_t idx) const
{
    if (idx >= _size)
    {
        throw std::out_of_range("Vector index out of range");
    }

    return _data[idx];
}
long long Vector::find(const ValueType& value) const
{
    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i] == value)
        {
            return i;
        }
    }

    return -1;
}
void Vector::reserve(size_t capacity)
{
    if (capacity > _capacity)
    {
        ValueType* newdata = new ValueType[capacity];
        std::memcpy(newdata, _data, _size * sizeof(ValueType));
        delete[] _data;
        _data = newdata;
        _capacity = capacity;
        newdata = nullptr;
    }
}
void Vector::shrinkToFit()
{
    if (_size == _capacity)
    {
        return;
    }

    ValueType* newdata = new ValueType[_size];
    std::memcpy(newdata, _data, _size * sizeof(ValueType));
    delete[] _data;
    _data = newdata;
    _capacity = _size;
    newdata = nullptr;
}
Vector::Iterator::Iterator(ValueType* ptr): _ptr(ptr) {}
ValueType& Vector::Iterator::operator*()
{
    return *_ptr;
}
const ValueType& Vector::Iterator::operator*() const
{
    return *_ptr;
}
ValueType* Vector::Iterator::operator->()
{
    return _ptr;
}
const ValueType* Vector::Iterator::operator->() const
{
    return _ptr;
}
Vector::Iterator Vector::Iterator::operator++()
{
    ++_ptr;

    return *this;
}
Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator copy = *this;
    ++_ptr;

    return copy;
}
bool Vector::Iterator::operator==(const Iterator& other) const
{
    return _ptr == other._ptr;
}
bool Vector::Iterator::operator!=(const Iterator& other) const
{
    return _ptr != other._ptr;
}
Vector::Iterator Vector::begin()
{
    return Iterator(_data);
}
Vector::Iterator Vector::end()
{
    return Iterator(_data + _size);
}
