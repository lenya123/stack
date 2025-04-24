#include "ForwardList.h"
ForwardList::Node::Node(ValueType val): data(val), next(nullptr) {}
ForwardList::ForwardList(): head(nullptr) {}
ForwardList::ForwardList(const ForwardList& other) : head(nullptr)
{
    if (other.head == nullptr)
    {
        return;
    }
    head = new Node(other.head -> data);
    Node* current = head;
    Node* otherCurrent = other.head -> next;
    while (otherCurrent != nullptr)
    {
        current -> next = new Node(otherCurrent -> data);
        current = current -> next;
        otherCurrent = otherCurrent -> next;
    }
}
ForwardList& ForwardList::operator=(const ForwardList& other)
{
    if (this != &other)
    {
        clear();
        if (other.head != nullptr)
        {      
            head = new Node(other.head -> data);
            Node* current = head;
            Node* otherCurrent = other.head -> next;
            while (otherCurrent != nullptr)
            {
                current -> next = new Node(otherCurrent -> data);
                current = current -> next;
                otherCurrent = otherCurrent -> next;
            }
        }
        else
        {
            head = nullptr;
        }
    }
    return *this;
}
ForwardList::ForwardList(ForwardList&& other) noexcept: head(other.head)
{
    other.head = nullptr;
}
ForwardList& ForwardList::operator=(ForwardList&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    clear();
    head = other.head;
    other.head = nullptr;
    return *this;
}
ForwardList::~ForwardList()
{
    if (cycle_existence())
    {
        Node* c_head = cycle_head();
        Node* current = c_head;
        while (current -> next != c_head)
        {
            current = current -> next;
        }
        current -> next = nullptr;
    }
    clear();
}
ForwardList::Node* ForwardList::get_head() const
{
    return head;
}
void ForwardList::push_front(ValueType val)
{
    Node* new_node = new Node(val);
    new_node -> next = head;
    head = new_node;
}
void ForwardList::pop_front()
{
    if (empty())
    {
        throw std::out_of_range("List is empty");
    }
    Node* temp = head;
    head = head -> next;
    delete temp;
}
void ForwardList::push_back(ValueType val)
{
    if (empty())
    {
        push_front(val);
    }
    else
    {
        Node* current = head;
        while (current -> next != nullptr)
        {
            current = current -> next;
        }
        Node* new_node = new Node(val);
        current -> next = new_node;
        new_node -> next = nullptr;
    }
}
void ForwardList::pop_back()
{
    if (empty())
    {
        throw std::out_of_range("List is empty");
    }
    if (cycle_existence())
    {
        throw std::logic_error("Can't pop_back: cycle detected");
    }
    if (head -> next == nullptr)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node* current = head;
        while (current -> next -> next != nullptr)
        {
            current = current -> next;
        }
        delete current -> next;
        current -> next = nullptr;
    }
}
void ForwardList::pop_element(int index)
{
    if (empty()) 
    {
        throw std::out_of_range("List is empty");
    }
    if (index < 0)
    {
        throw std::out_of_range("Invalid index");
    }        
    else
    {
        Node* current = head;
        int current_index = 0;
        Node* prev = nullptr;
        while (current != nullptr && current_index < index)
        {
            prev = current;
            current = current -> next;
            current_index++;
        }
        if (current == nullptr)
        {
            throw std::out_of_range("Invalid index");
        }
        if (prev == nullptr)
        {
            head = current -> next;
        }
        else
        {
            prev -> next = current -> next;
        }
        delete current;
    }
}
ForwardList::Node* ForwardList::get_index(int index)
{
    if (index < 0)
    {
        throw std::out_of_range("Invalid index");
    }
    Node* current = head;
    for (int i = 0; i < index && current != nullptr; i++)
    {
        current = current -> next;
    }
    if (current == nullptr)
    {
        throw std::out_of_range("Invalid index");
    }
    return current;
}
size_t ForwardList::get_len() const
{
    if (empty())
    {
        return 0;
    }
    size_t counter = 0;
    Node* current = head;
    while (current != nullptr)
    {
        current = current -> next;
        counter++;
    }
    return counter;
}
void ForwardList::insert(int index, ValueType val)
{
    if (index < 0)
    {
        throw std::out_of_range("Invalid index");
    }
    if (index == 0)
    {
        push_front(val);
        return;
    }
    else if (get_len() == index)
    {
        push_back(val);
    }
    else
    {
        Node* current = head;
        for (int i = 0; i < index - 1 && current != nullptr; i++)
        {
            current = current -> next;
        }
        if (current == nullptr)
        {
            throw std::out_of_range("Invalid index");
        }
        Node* new_node = new Node(val);
        new_node -> next = current -> next;
        current -> next = new_node;
    }
}
bool ForwardList::element_in_list(int val) const
{
    if (empty())
    {
        return false;
    }
    Node* current = head;
    while (current -> next != nullptr)
    {
        if (current -> data == val)
        {
            return true;
        }
        current = current -> next;
    }
    if (current -> data == val)
    {
        return true;
    }
    return false;
}
void ForwardList::printlist() const
{
    if (empty())
    {
        return;
    }
    Node* current = head;
    while (current != nullptr)
    {
        std::cout << current -> data << " ";
        current = current -> next;
    }
    std::cout << std::endl;
}
ForwardList::Node* ForwardList::operator[](int index)
{
    return get_index(index);
}
bool ForwardList::empty() const
{
    return head == nullptr;
}
void ForwardList::erase(ValueType val)
{
    while (element_in_list(val))
    {
        if (empty())
        {
            throw std::out_of_range("List is empty");
        }
        if (head -> data == val)
        {
            pop_front();
            continue;
        }
        Node* current = head;
        while (current -> next != nullptr && current -> next -> data != val)
        {
            current = current -> next;
        }
        if (current -> next != nullptr)
        {
            Node* temp = current -> next;
            current -> next = temp -> next;
            delete temp;
        }
    }
}
void ForwardList::clear()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head -> next;
        delete temp;
    }
}
bool ForwardList::cycle_existence() const
{
    if (head == nullptr)
    {
        return false;
    }
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast -> next != nullptr)
    {
        slow = slow -> next;
        fast = fast -> next -> next;
        if (slow == fast)
        {
            return true;
        }
    }
    return false;
}
ForwardList::Node* ForwardList::cycle_head() const
{
    if (!cycle_existence())
    {
        return nullptr;
    }
    Node* slow = head;
    Node* fast = head;
    do
    {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    while (slow != fast);
    slow = head;
    while (slow != fast)
    {
        slow = slow -> next;
        fast = fast -> next;
    }
    return slow;
}
size_t ForwardList::cycle_length() const
{
    if (!cycle_existence())
    {
        return 0;
    }
    Node* meet_point = cycle_head();
    Node* current = meet_point;
    size_t len = 1;
    while (current -> next != meet_point)
    {
        current = current -> next;
        ++len;
    }
    return len;
}
ValueType& ForwardList::back() const
{
    if (empty())
    {
        throw std::out_of_range("List is empty");
    }
    Node* current = head;
    while (current -> next != nullptr)
    {
        current = current -> next;
    }
    return current -> data;
}
