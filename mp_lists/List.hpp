/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <cmath>
template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;                 //modified 2/24
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);               //modified 2/24, change NULL to head_ according to lec13
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);               //modified 2/24, change NULL to nullptr according to lec13
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {      //modified 2/24
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    ListNode * tmp = head_ -> next;
    delete head_;
    head_ = tmp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {              //modified 2/24, adding several sentences
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
    head_ = newNode;
  }
  else {
    tail_ = newNode;
    newNode -> next = NULL;
    head_ = newNode;
  }
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {             //modified 2/24, reference to insertfront
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
    tail_ = newNode;
  }
  else {
    head_ = newNode;
    newNode -> prev = NULL;
    tail_ = newNode;
  }
  

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {               //modifed 2/24/2021
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  if (splitPoint <= 0){
    return start;
  }
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    if (curr -> next != NULL){
      curr = curr->next;
    }
    else{
      return curr;
    }
  }
  curr->prev->next = NULL;
  curr->prev = NULL;
  return curr; 
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {                        //modified 2/25/2021, separte the whole numbers into groups, each group try to throw in 3 members
  // @todo Graded in MP3.1
  if (length_ <= 2){
    return;
  }
  else{
    ListNode * fst_element = head_;
    ListNode * sec_element = fst_element -> next;
    ListNode * thd_element = sec_element -> next;                 //define three pts to the every number in one group

    ListNode * curr = head_;                                      //curr is the ptr pointing to the first element in each group, used for locating which group
    ListNode * group_start = NULL;
    ListNode * group_end = NULL;
    head_ = sec_element;
    int c = 0;                                                    //c is a counter to save the cth group we are now deading with
    

    while (curr && curr -> next && (curr -> next) -> next){       //do triple rotate when this group has exactly three members
      fst_element = curr;
      sec_element = curr -> next;
      thd_element = (curr -> next) -> next;

      group_start = curr -> prev;  
      
      curr = ((curr -> next) -> next) -> next;                    //moves to the next 3-member-group

      if (c != ceil(length_/3) -1){                               //check if it is not the last group
        group_end = thd_element -> next -> next;                  //for instance 12345678..., group_end pts to 5 when c = 0                          
      }
      else{                                                       //when this is the last group
        if ((length_ % 3 == 1) || (length_ % 3 == 2)){            //when last group has one or two element
          group_end = thd_element -> next;                        //for instance 12345678, group_end pts to 7 when c = 1
        }
        else{                                                     //when last group has 2 element
          group_end = NULL;                                       //for instance 123456, group_end pts to null when c = 1
        }
      }

      sec_element -> prev = group_start;
      sec_element -> next = thd_element;
      thd_element -> prev = sec_element;
      thd_element -> next = fst_element;
      fst_element -> prev = thd_element;
      fst_element -> next = group_end;                            //change the links
      tail_ = fst_element;

      
      c = c + 1;
    }
  }  
  
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (head_ == NULL || tail_ == NULL){                                    //deal with the case while list is empty
    return;
  }

  ListNode * curr = startPoint;
  ListNode * prev = curr -> prev;
  ListNode * next = curr -> next;                                         //define vars for three cotinous elements in the list

  while (curr != endPoint){                                               //while not reaching the end
    if (curr == startPoint){                                              //special case of the very first element
      curr -> next = endPoint -> next;
      curr -> prev = next;
      curr = next;
    }
    else{                                                                 //exchange postions of nodes
      next = curr -> next;
      curr -> next = curr -> prev;
      curr -> prev = next;
      curr = next;
    }
  }
  endPoint -> next = endPoint -> prev;
  endPoint -> prev = prev;

  if (head_ != startPoint){                                               //special cases for reverseNth
    prev -> next = curr;
  }
  if (tail_ != endPoint){
    startPoint -> next -> prev = startPoint;
  }
  if (head_ == startPoint){
    head_ = endPoint;
  }
  if (tail_ == endPoint){
    tail_ = startPoint;
  }

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (head_ == NULL || tail_ == NULL) {                              //deal with the case while list is empty
    return;
  }

  ListNode * start = head_;
  ListNode * end = start;                                            //define two vars to locate the start and end points so that we can use reverse fcn

  while (start != NULL) {                                            //while not reaching the very end
    for (int count = 0; count < n - 1; count++) {                    //counter is for letting us know whether we finish the group of size n 
      if (end != tail_) {
        end = end -> next;                                           //save the ptr to the last element in the group in "end"
      }
    }
    reverse(start, end);
    start = start -> next;
    end = start;
  }
  }



/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL && second == NULL){
    return NULL;
  }
  if (first == NULL && second != NULL){
    return second;
  }
  if (first != NULL && second == NULL){
    return first;
  }                                                                               //deal with the case while list is empty
  
	ListNode *curr_fst = first;
	ListNode *curr_sec = second;
	ListNode *realfst = first;
  ListNode *tmp = NULL;                                                           //four ptrs. curr_fst, curr_sec is the moving ptr in two lists, realfst saves the ptr to the first element in list1 

	if (curr_fst -> data < curr_sec -> data){                                       //do the compariosn of first elements in two lists
		curr_fst = first -> next;
	} 
  else{
		realfst = second;
		curr_sec = second -> next;
	}

	tmp = realfst;
	while(curr_fst != NULL && curr_sec != NULL){                                    //do the compariosn of other elements in two lists
		if (curr_fst -> data < curr_sec -> data || curr_sec == NULL){                 //if smaller, deal with the tmp node
			tmp -> next = curr_fst;
			curr_fst -> prev = tmp;
			tmp = curr_fst;
			curr_fst = curr_fst -> next;
		}
		else{                                                                         //else. insert smaller node in list 2 into the correct positon in list 1
			tmp -> next = curr_sec;
			curr_sec -> prev = tmp;
			tmp = curr_sec;
			curr_sec = curr_sec -> next;
		}
	}
	if (curr_fst == NULL){
		tmp -> next = curr_sec;
		curr_sec -> prev = tmp;
	}
	else{
		tmp -> next = curr_fst;
		curr_fst -> prev = tmp;
	}
  
	second = NULL;
  first = realfst;
	return first;                                                                   //undate second, first ptrs, and return list1

}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start == NULL) {                                                              //deal with the case while list is empty
    return NULL;
  }

  if (chainLength == 1){                                                            //base case
    return start;
  } 
  ListNode * splitted = split(start, chainLength / 2);
  ListNode * fst = mergesort(start, chainLength / 2);
  ListNode * sec = mergesort(splitted, chainLength / 2 + chainLength % 2);
  return merge(fst, sec);
}
