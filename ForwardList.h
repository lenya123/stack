#pragma once
#include <iostream>
using ValueType = double;
class ForwardList
{
private:
    struct Node
    {
        ValueType data;
        Node* next;
        Node(ValueType val);
    };
    Node* head;
public:
    ForwardList();
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other) noexcept;
    ~ForwardList();
    ForwardList& operator=(const ForwardList& other);
    ForwardList& operator=(ForwardList&& other) noexcept;
    void push_front(ValueType val);
    void pop_front();
    void push_back(ValueType val);
    void pop_back();
    void insert(int index, ValueType val);
    void erase(ValueType val);
    void clear();
    void pop_element(int index);
    Node* get_index(int index);
    Node* operator[](int index);
    size_t get_len() const;
    bool empty() const;
    void printlist() const;
    bool element_in_list(int val) const;
    bool cycle_existence() const;
    Node* cycle_head() const;
    size_t cycle_length() const;
    Node* get_head() const;
    ValueType& back() const;
};