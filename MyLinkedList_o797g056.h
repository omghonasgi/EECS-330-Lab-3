#ifndef _MY_LINKEDLIST_H_
#define _MY_LINKEDLIST_H_

#include <algorithm>
#include <iostream>

template <typename DataType>
class MyLinkedList
{
  private:
    
    struct Node
    {
        DataType  data;
        Node   *prev;
        Node   *next;
        
        Node(const DataType &d = DataType{ }, Node *p = nullptr, Node *n = nullptr) : 
        data{d}, 
        prev{p}, 
        next{n} 
        { }

        Node(DataType&& d, Node* p = nullptr, Node* n = nullptr) : 
        data{std::move(d)}, 
        prev{p}, 
        next{n} 
        { }
    };

    int theSize;        // the number of elements that the linked list is currently holding
    Node *head;         // pointer to the head node; does not hold real data
    Node *tail;         // pointer to the tail note; does not hold real data

    void init( )
    { 
        // code begins
        theSize = 0;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
        // code ends

        return;
    }

  public:

    // define the const_iterator class
    class const_iterator
    { 
      protected:
        Node *current;
        // returns a mutable object
        // defined as proected as we don't expect it to be called directly by other classess
        DataType& retrieve() const
        { 
            return current->data; 
        }
        // constructor to be hidden from other classes; 
        // we don't expect direct construction of iterator form pointer
        const_iterator(Node *p) : 
        current{p} 
        {}
        
        friend class MyLinkedList<DataType>;

      public:
        const_iterator() : 
        current{nullptr} 
        {}

        // add const to the return type and make the return value by retrieve() non-mutable
        const DataType& operator* () const
        {
            // code begins
            return current->data;
            // code ends
        }
        
        // move to the next data element
        // the prefix increment (e.g. ++ p) with 0 parameter
        const_iterator& operator++ ()
        {
            // code begins
            current = current->next;
            return *this;
            // code ends
        }

        // move to the next data element
        // the suffix increment (e.g. p ++) with 1 int parameter
        const_iterator operator++ ( int )
        {
            // code begins
            const_iterator old = *this;
            ++(*this);
            return old;
            // code ends
        }

        // move to the previous data element
        // the prefix decrement (e.g. -- p) with 0 parameter
        const_iterator& operator-- ()
        {
            // code begins
            current = current->prev;
            return *this;
            // code ends
        }

        // move to the previous data element
        // the suffix decrement (e.g. p --) with 1 int parameter
        const_iterator operator-- (int)
        {
            // code begins
            const_iterator old = *this;
            --(*this);
            return old;
            // code ends
        }

        // check whether two iterators point to the same data element
        bool operator== (const const_iterator& rhs) const
        {
            // code begins
            return this->current == rhs.current;
            // code ends 
        }
        
        // check whether two iterators point to the same data element
        bool operator!= (const const_iterator & rhs) const
        {
            // code begins
            return this->current != rhs.current;
            // code ends
        }
      
    };

    // define the iterator class; inherit from class const_iterator
    class iterator : public const_iterator
    {
      protected:
        iterator(Node *p) : 
        const_iterator{p}
        {}
        
        friend class MyLinkedList<DataType>;
      
      public:
        // default constructor
        iterator()
        {}

        // the return type is mutable
        DataType& operator* ()
        { 
            // code begins
            return const_iterator::retrieve();
            // code ends 
        }
        
        // keep the return type as non-mutable
        const DataType& operator* () const
        { 
            // code begins
            return const_iterator::retrieve();
            // code ends
        }

        iterator & operator++ ()
        {
            // code begins
            this->current = this->current->next;
            return *this;
            // code ends
        }

        iterator operator++ (int)
        {
            // code begins
            iterator old = *this;
            ++(*this);
            return old;
            // code ends
        }

        iterator operator-- ()
        {
            // code begins
            this->current = this->current->prev;
            return *this;
            // code ends
        }
        
        iterator operator-- (int)
        {
            // code begins
            iterator old = *this;
            --(*this);
            return old;
            // code ends
        }

        // don't need to overload operator= and operator!= as they should behave the same as in const_iterator
    };

  // defining the MyLinkedList class methods
  public:

    // default constructor
    MyLinkedList()
    { 
        init(); 
    }
  
    // copy constructor
    MyLinkedList(const MyLinkedList& rhs)
    { 
        // code begins
        init();
        for (const_iterator it = rhs.begin(); it != rhs.end(); ++it){
            push_back(*it);
        }
        // code ends
    }

    // move constructor
    MyLinkedList (MyLinkedList&& rhs) :
    theSize(rhs.theSize),
    head(rhs.head),
    tail(rhs.tail)
    { 
        // code begins
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
        // code ends
    }

    // destructor
    ~MyLinkedList()
    {
        // code begins
        clear();
        delete head;
        delete tail;
        // code ends
    }

    // copy assignment
    MyLinkedList & operator= (const MyLinkedList& rhs)
    { 
        // code begins
        clear();

         for (const_iterator it = rhs.begin(); it != rhs.end(); ++it)
        {
            push_back(*it);  
        }
        return *this;
        // code ends
    }
  
    // move assignment
    MyLinkedList & operator= (MyLinkedList && rhs)
    { 
        // code begins
        clear();

        theSize = rhs.theSize;
        head = rhs.head;
        tail = rhs.tail;

        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;

        return *this;
        // code ends
    }

    // iterator interface
    iterator begin()
    { 
        // code begins
        return head->next;
        // code ends 
    }

    const_iterator begin() const
    { 
        // code begins
        return head->next;
        // code ends 
    }
  
    iterator end()
    { 
        // code begins
        return tail;
        // code ends 
    }

    const_iterator end() const
    { 
        // code begins
        return tail;
        // code ends 
    }
  
    // gets the size of the linked list
    int size() const
    {
        // code begins
        return theSize;
        // code ends
    }

    // checks if the linked list is empty; return True if empty, false otherwise
    bool empty( ) const
    { 
        // code begins
        return theSize == 0;
        // code ends 
    }

    // deletes all nodes excepts the head and tail
    void clear( )
    {
        // code begins
        for (iterator it = begin(); it != end(); ++it){
            iterator temp = it;
            delete temp.current;
        }

        head->next = tail;
        tail->prev = head;
        theSize = 0;
        // code ends
    }

    // return the first data element as mutable
    DataType& front()
    { 
        // code begins
        return head->next->data;
        // code ends 
    }

    // return the first data element as non-mutable
    const DataType& front() const
    { 
        // code begins
        return head->next->data;
        // code ends
    }

    // return the last data element as mutable
    DataType& back()
    { 
        // code begins
        return tail->prev->data;
        // code ends 
    }

    // return the last data element as non-mutable
    const DataType& back() const
    { 
        // code begins
        return tail->prev->data;
        // code ends 
    }

    // insert x before itr; return iterator pointing to the newly inserted data element
    iterator insert(iterator itr, const DataType& x)
    {
        // code begins
        Node *p = itr.current;
        Node *n = new Node(x, p->prev, p);
        p->prev->next = n;
        p->prev = n;
        ++theSize;
        return --itr;
        // code ends
    }

    // insert x before itr; return iterator pointing to the newly inserted data element
    iterator insert(iterator itr, DataType&& x)
    {
        // code begins
        Node *p = itr.current;
        Node *n = new Node(x, p->prev, p);
        p->prev->next = n;
        p->prev = n;
        ++theSize;
        return --itr;
        // code ends 
    }

    // delete the data element pointed by itr; return the iterator pointing to the data element next to the one being deleted
    iterator erase(iterator itr)
    {
        // code begins
        Node *p = itr.current;
        iterator rItr{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p ;
        -- theSize;
        return rItr;
        // code ends
    }

    // delete the data elements from iterator "from" (inclusive) to iterator "to" (exclusive)
    // return the iterator "to"
    iterator erase( iterator from, iterator to )
    { 
        // code begins
        for(auto it = from; it != to; it++){
            it = erase(it);
        }
        return to;
        // code ends
    }

    // insert data element x to the very begining of the linked list
    void push_front(const DataType& x)
    { 
        // code begins
        insert(begin(), x);
        // code ends
    }
  
    void push_front(DataType&& x)
    { 
        // code begins
        insert(begin(), x);
        // code ends 
    }
    
    // insert data element x to the very end of the linked list
    void push_back(const DataType& x)
    {
        // code begins
        insert(end(), x);
        // code ends
    }
    
    void push_back(DataType&& x)
    { 
        // code begins
        insert(end(), x);
        // code ends
    }
    
    // delete the very first data element
    void pop_front()
    {
        // code begins
        erase(begin());
        // code ends
    }
    
    // delete the very last data element
    void pop_back( )
    { 
        // code begins
        erase(--end());
        // code ends
    }
    
    // reverse the entire linked list
    void reverseList()
    {
        // code begins
       Node* current = head;
        while (current) {
            std::swap(current->next, current->prev);
            current = current->prev; // Since prev is now next
        }
        std::swap(head, tail);
        // code ends
    }
 
    // append a linked list to the end of the current one
    MyLinkedList<DataType>& appendList(MyLinkedList<DataType>&& rlist) 
    {
        // code begins
        for (iterator it = rlist.begin(); it != rlist.end(); ++it){
            push_back(*it);
        }
        theSize = theSize + rlist.theSize;

        return *this;
        // code ends
    }

    // swap the data element pointed by itr with its next data element
    // return false if the next data element does not exist; true otherwise
    bool swapAdjElements(iterator& itr)
    {
        // code begins
            // Ensure there's a next element to swap with
    if (itr.current == nullptr || itr.current->next == nullptr)
        return false;

    // Pointers to the current node and the next node
    Node* p = itr.current;
    Node* nextNode = p->next;

   
    p->next = nextNode->next;
    if (p->next != nullptr) { 
        p->next->prev = p;
    }

    nextNode->prev = p->prev;
    if (nextNode->prev != nullptr) {  
        nextNode->prev->next = nextNode;
    }

    p->prev = nextNode;
    nextNode->next = p;

    itr.current = nextNode;

    return true;
        // code ends
    }

};

#endif // __MYLIST_H__