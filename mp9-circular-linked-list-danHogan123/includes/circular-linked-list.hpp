#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:

//helpers
  void InsertAscending(const T& data);
  void InsertDescending(const T& data);
  void Clear();
  void ChangeDirection();
 // void Reverse(unsigned int& count, Node<T>* node,unsigned int size);
  unsigned int SizeOf();


  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};




//copy constructor
  template <typename T>
  CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) 
  {
    if (source.head_ == nullptr) 
    {
      head_ = tail_ = nullptr;
      node_order_ = source.node_order_; 
    }
    else if (source.head_ == source.tail_)
    {
      head_ = tail_ = new Node<T>(source.head_->data);
      tail_->next = head_;
      node_order_ = source.node_order_;
    }
    else
    {
      head_ = new Node<T>(source.head_->data);

      Node<T>* current = head_;
      Node<T>* loop = source.head_->next;

      while (loop != source.head_)
      {
        current->next= new Node<T>(loop->data);
        loop = loop->next;
        current = current->next;
      }
      current->next = head_;
      tail_ = current;
      node_order_ = source.node_order_;
    }
  }


//copy assignment operator
  template <typename T>
  CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source){
    if (this == &source){ return *this;}
    Clear();
    if (source.head_ == nullptr) 
    {
      head_ = tail_ = nullptr;
      node_order_ = source.node_order_; 
    }
    else if (source.head_ == source.tail_)
    {
      head_ = tail_ = new Node<T>(source.head_->data);
      tail_->next = head_;
      node_order_ = source.node_order_;
    }
    else
    {
      head_ = new Node<T>(source.head_->data);
      Node<T>* current = head_;
      Node<T>* loop = source.head_->next;

      while (loop != source.head_)
      {
        current->next = new Node<T>(loop->data);
        loop = loop->next;
        current = current->next;
      }
      current->next = head_;
      tail_ = current;
      node_order_ = source.node_order_;
    }
    return *this;
  }

  template <typename T>
  void CircularLinkedList<T>::Clear()
  {
    Node<T>* curr = head_;

    while (curr != tail_) 
    {
      curr = curr->next;
      delete head_;
      head_ = curr;
    }
    delete tail_;
    head_ = tail_ = nullptr;
  }

  template <typename T>
  CircularLinkedList<T>::~CircularLinkedList()
  {
    Clear();
  }

  template <typename T>
  void CircularLinkedList<T>::ChangeDirection()
  {
    if (node_order_ == Order::kASC) {node_order_ = Order::kDESC;}
    if (node_order_ == Order::kDESC) {node_order_ = Order::kASC;}
  }

//ascending
  template <typename T>
  void CircularLinkedList<T>::InsertAscending(const T& data) 
  {
    if (head_ == nullptr)
    {
      head_ = tail_ = new Node<T>(data);
      tail_->next = head_;
    }
    else if (data <= head_->data) 
    {
      auto* node = new Node<T>(data);
      node->next = head_;
      tail_->next = node;
      head_ = node;
    }
    else if (data >= tail_->data)
    {
      auto* node = new Node<T>(data);
      node->next = head_;
      tail_->next = node;
      tail_ = node;
    }
    else 
    {
      Node<T>* current = head_->next;

      while (current != tail_ && data < current->data)
      {
        current = current->next;
      }
      auto* temp = new Node<T>(data);
      temp->next = current->next;
      current->next = temp;
    }
  }
//descending 
  template <typename T>
  void CircularLinkedList<T>::InsertDescending(const T& data)
  {
    if (head_ == nullptr)
    {
      head_ = tail_ = new Node<T>(data);
      tail_->next = head_;
    }
    else if (data >= head_->data) 
    {
      auto* node = new Node<T>(data);
      node->next = head_;
      tail_->next = node;
      head_ = node;
    }
    else if (data <= tail_->data)
    {
      auto* node = new Node<T>(data);
      node->next = head_;
      tail_->next = node;
      tail_ = node;
    }
    else 
    {
      Node<T>* current = head_->next;

      while (current != tail_ && data > current->data)
      {
        current = current->next;
      }
      auto* temp = new Node<T>(data);
      temp->next = current->next;
      current->next = temp;
  }
}

  template <typename T>
  void CircularLinkedList<T>::InsertInOrder(const T& data)
  {
    if (node_order_ == Order::kASC)
      InsertAscending(data); 
    else 
      InsertDescending(data);  
  }


template <typename T>
  unsigned int CircularLinkedList<T>::SizeOf()
  {
    unsigned int size = 0;
    Node<T>* curr = head_;

     while (curr != tail_)
     {
      size++;
      curr = curr->next;
     }
     size++;
     return size;
  }


//  template <typename T>
//   void CircularLinkedList<T>::Reverse(unsigned int& count, Node<T>* node, unsigned int size)
//   {
//     if(count != size-1){
//       Reverse(count, node, size);
//     for (unsigned int i=0; i<size-1-count; ++i) //size-1
//     {
//       node = node->next;
//     }
//     count++;
//     head_->next =node;}
//   }

  template <typename T>
  void CircularLinkedList<T>::Reverse()
  {
    ChangeDirection();
    if (head_ == nullptr)
      return;

    Node<T>* curr = head_;
    Node<T>* next = curr->next;
    Node<T>* temp = curr->next->next;

    Node<T>* tail = head_;
    Node<T>* head = tail_;

    while (curr != tail_) {
      next->next = curr;
      curr = next;
      next = temp;
      temp = temp->next;
    }
    next->next = curr;
    head_->next = tail_;
    head_ = head;
    tail_ = tail;
  }


template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif