#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class DLList;

template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T>* prev, * next;
  DLListNode(T e = T(), DLListNode* p = nullptr, DLListNode* n = nullptr) :
    obj(e), prev(p), next(n) {}
};

template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
    DLList() :
      header(T(), nullptr, nullptr), trailer(T(), nullptr, nullptr) {
      header.next = &trailer;
      trailer.prev = &header;
    }

    ~DLList() {
      DLListNode<T>* curr_node = header.next;
      while (curr_node != &trailer) {
        DLListNode<T>* next_node = curr_node->next;
        curr_node->prev->next = next_node;
        next_node->prev = curr_node->prev;
        delete curr_node;
        curr_node = next_node;
      }
      header.next = &trailer;
      trailer.prev = &header;
    }

    DLList(const DLList& dll) {
      header.next = &trailer;
      trailer.prev = &header;

      DLListNode<T>* current = dll.header.next;
      while (current != &dll.trailer) {
        insert_last(current->obj);
        current = current->next;
      }
    }

    DLList& operator=(const DLList& dll) {
      if (this == &dll) {
        return *this;
      }

      DLListNode<T>* curr_node = header.next;
      while (curr_node != &trailer) {
        DLListNode<T>* next_node = curr_node->next;
        delete curr_node;
        curr_node = next_node;
      }
      header.next = &trailer;
      trailer.prev = &header;

      DLListNode<T>* orig_curr_node = dll.header.next;
      while (orig_curr_node != &(dll.trailer)) {
        insert_last(orig_curr_node->obj);
        orig_curr_node = orig_curr_node->next;
      }

      return *this;
    }

    DLList(DLList&& dll) :
      header(T(), nullptr, nullptr), trailer(T(), nullptr, nullptr) {
      header.next = &trailer;
      trailer.prev = &header;

      DLListNode<T>* dll_node = dll.header.next;
      DLListNode<T>* temp_dll_node = nullptr;
      while (dll_node != &(dll.trailer)) {
        insert_last(dll_node->obj);
        temp_dll_node = dll_node;
        dll_node = dll_node->next;
        delete temp_dll_node;
      }
      dll.header.next = &dll.trailer;
      dll.trailer.prev = &dll.header;
    }

    DLList& operator=(DLList&& dll) {
      if (this == &dll) {
        return *this;
      }

      while (!is_empty()) {
        remove_last();
      }
      header.next = &trailer;
      trailer.prev = &header;

      DLListNode<T>* temp = nullptr;
      DLListNode<T>* dll_node = dll.header.next;
      while (dll_node != &(dll.trailer)) {
        this->insert_last(dll_node->obj);
        temp = dll_node;
        delete temp;
        dll_node = dll_node->next;
      }
      dll.header.next = &dll.trailer;
      dll.trailer.prev = &dll.header;

      return *this;
    }

    DLListNode<T>* first_node() const {
      return header.next;
    }

    const DLListNode<T>* after_last_node() const {
      return &trailer;
    }

    bool is_empty() const {
      return header.next == &trailer;
    }

    T first() const {
      return header.next->obj;
    }

    T last() const {
      return trailer.prev->obj;
    }

    void insert_first(T obj) {
      DLListNode<T>* newNode = new DLListNode<T>(obj, &header, header.next);
      header.next->prev = newNode;
      header.next = newNode;
    }

    T remove_first() {
      if (is_empty()) {
        throw std::runtime_error("Not possible list is empty");
      }

      DLListNode<T>* to_be_deleted = header.next;
      T wanted_obj = to_be_deleted->obj;

      to_be_deleted->next->prev = &header;
      header.next = to_be_deleted->next;

      delete to_be_deleted;
      return wanted_obj;
    }

    void insert_last(T obj) {
      DLListNode<T>* newNode = new DLListNode<T>(obj, trailer.prev, &trailer);
      trailer.prev->next = newNode;
      trailer.prev = newNode;
    }

    T remove_last() {
      if (is_empty()) {
        throw std::runtime_error("Not possible list is empty");
      }

      DLListNode<T>* to_be_deleted = trailer.prev;
      T wanted_obj = to_be_deleted->obj;

      to_be_deleted->prev->next = &trailer;
      trailer.prev = to_be_deleted->prev;

      delete to_be_deleted;
      return wanted_obj;
    }

    void insert_after(DLListNode<T>& p, T obj) {
      DLListNode<T>* newNode = new DLListNode<T>(obj, &p, p.next);
      p.next->prev = newNode;
      p.next = newNode;
    }

    void insert_before(DLListNode<T>& p, T obj) {
      DLListNode<T>* newNode = new DLListNode<T>(obj, p.prev, &p);
      p.prev->next = newNode;
      p.prev = newNode;
    }

    T remove_after(DLListNode<T>& p) {
      if (is_empty()) {
        throw std::runtime_error("Not possible list is empty");
      }

      DLListNode<T>* to_be_deleted = p.next;
      T wanted_obj = to_be_deleted->obj;

      to_be_deleted->next->prev = &p;
      p.next = to_be_deleted->next;

      delete to_be_deleted;
      return wanted_obj;
    }

    T remove_before(DLListNode<T>& p) {
      if (is_empty()) {
        throw std::runtime_error("Not possible list is empty");
      }

      DLListNode<T>* to_be_deleted = p.prev;
      T wanted_obj = to_be_deleted->obj;

      to_be_deleted->prev->next = &p;
      p.prev = to_be_deleted->prev;

      delete to_be_deleted;
      return wanted_obj;
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& out, const DLList<T>& dll) {
  DLListNode<T>* curr_node = dll.first_node();

  while (curr_node != dll.after_last_node()) {
    out << curr_node->obj;
    if (curr_node->next != dll.after_last_node())
      out << ", ";
    curr_node = curr_node->next;
  }

  return out;
}

#endif
