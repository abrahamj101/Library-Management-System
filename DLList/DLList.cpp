// implementation of the DLList class

#include "DLList.h"

// Default constructor
DLList::DLList() {
  // Initialize the header and trailer nodes
  header.next = &trailer;
  trailer.prev = &header;
}

// Copy constructor
DLList::DLList(const DLList& dll) {
  // Create a new list with the same structure as dll
  header.next = &trailer;
  trailer.prev = &header;

  // Iterate through each node in dll and copy its value
  DLListNode* current = dll.header.next;
  while (current != &dll.trailer) {
    insert_last(current->obj);
    current = current->next;
  }
}

// Move constructor
DLList::DLList(DLList&& dll) {
  // Move the header and trailer pointers
  header.next = dll.header.next;
  trailer.prev = dll.trailer.prev;

  // Update the prev and next pointers of the adjacent nodes
  header.next->prev = &header;
  trailer.prev->next = &trailer;

  // Reset the original list
  dll.header.next = &dll.trailer;
  dll.trailer.prev = &dll.header;
}

// Destructor
DLList::~DLList() {
  // Remove all nodes from the list
  while (!is_empty()) {
    remove_last();
  }
}


// Copy assignment operator
DLList& DLList::operator=(const DLList& dll) {
  // Check for self-assignment
  if (this == &dll) {
    return *this;
  }

  // Clear the existing list
  while (!is_empty()) {
    remove_last();
  }

  // Copy the elements from dll
  DLListNode* current = dll.header.next;
  while (current != &dll.trailer) {
    insert_last(current->obj);
    current = current->next;
  }

  return *this;
}

// Move assignment operator
DLList& DLList::operator=(DLList&& dll) {
  // Check for self-assignment
  if (this == &dll) {
    return *this;
  }

  // Clear the existing list
  while (!is_empty()) {
    remove_last();
  }

  // Transfer ownership from dll to this object
  header.next = dll.header.next;
  trailer.prev = dll.trailer.prev;
  header.next->prev = &header;
  trailer.prev->next = &trailer;

  // Reset dll to an empty list
  dll.header.next = &dll.trailer;
  dll.trailer.prev = &dll.header;

  return *this;
}


// Return the pointer to the first node (header's next)
DLListNode* DLList::first_node() const {
  return header.next;
}

// Return the pointer to the trailer
const DLListNode* DLList::after_last_node() const {
  return &trailer;
}

// Check if the list is empty
bool DLList::is_empty() const {
  return header.next == &trailer;
}

// Return the first object
int DLList::first() const {
  return header.next->obj;
}

// Return the last object
int DLList::last() const {
  return trailer.prev->obj;
}

// Insert an object at the beginning of the list
void DLList::insert_first(int obj) {
  DLListNode* newNode = new DLListNode(obj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

// Remove the first node and return its object
int DLList::remove_first() {
  if (is_empty()) {
    // Handle the case when the list is empty
    throw logic_error("Cannot remove the first node from an empty list.");
  }

  DLListNode* firstNode = header.next;
  int obj = firstNode->obj;
  header.next = firstNode->next;
  firstNode->next->prev = &header;
  delete firstNode;

  return obj;
}


// Insert an object at the end of the list
void DLList::insert_last(int obj) {
  DLListNode* newNode = new DLListNode(obj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// Remove the last node and return its object
int DLList::remove_last() {
  if (is_empty()) {
    // Handle the case when the list is empty
    throw logic_error("Cannot remove the last node from an empty list.");
  }
  
  DLListNode* lastNode = trailer.prev;
  int obj = lastNode->obj;
  trailer.prev = lastNode->prev;
  lastNode->prev->next = &trailer;
  delete lastNode;
  
  return obj;
}


// Insert an object after a specified node
void DLList::insert_after(DLListNode& p, int obj) {
  DLListNode* newNode = new DLListNode(obj, &p, p.next);
  p.next->prev = newNode;
  p.next = newNode;
}

// Insert an object before a specified node
void DLList::insert_before(DLListNode& p, int obj) {
  DLListNode* newNode = new DLListNode(obj, p.prev, &p);
  p.prev->next = newNode;
  p.prev = newNode;
}

// Remove the node after a specified node and return its object
int DLList::remove_after(DLListNode& p) {
  if (p.next == &trailer) {
    // Handle the case when there is no node after p
    throw logic_error("Cannot remove the node after the specified node.");
  }

  DLListNode* nodeToRemove = p.next;
  int obj = nodeToRemove->obj;
  p.next = nodeToRemove->next;
  nodeToRemove->next->prev = &p;
  delete nodeToRemove;

  return obj;
}


// Remove the node before a specified node and return its object
int DLList::remove_before(DLListNode& p) {
  if (p.prev == &header) {
    // Handle the case when there is no node before p
    throw logic_error("Cannot remove the node before the specified node.");
  }
  
  DLListNode* nodeToRemove = p.prev;
  int obj = nodeToRemove->obj;
  p.prev = nodeToRemove->prev;
  nodeToRemove->prev->next = &p;
  delete nodeToRemove;
  
  return obj;
}


// Overload the stream insertion operator to print the list
ostream& operator<<(ostream& out, const DLList& dll) {
  DLListNode* current = dll.first_node();
  while (current != dll.after_last_node()) {
    out << current->obj;
    if (current->next != dll.after_last_node()) {
      out << ", ";
    }
    current = current->next;
  }
  return out;
}


