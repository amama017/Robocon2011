#include <assert.h>

template < class queueElementType >
class Queue {
public:
   Queue();
   bool isEmpty();
   void enqueue(queueElementType e);
   queueElementType dequeue();
   queueElementType front();
private:
   struct Node;
   typedef Node * nodePtr;
   struct Node {
      queueElementType data;
      nodePtr next;
   };
   nodePtr f;
   nodePtr r;
};


template < class queueElementType > 
Queue < queueElementType >::Queue()
{
   f = 0;
   r = 0;
}

template < class queueElementType > 
bool Queue < queueElementType >::isEmpty()
{
     return f==0;
}

template < class queueElementType >
void Queue < queueElementType >::enqueue(queueElementType e)
{
   nodePtr n(new Node);
   assert(n);
   n->next = 0;
   n->data = e;
   if (f != 0) {
      r->next = n;
      r = n;
   }
else {
      f = n;
      r = n;
   }
}

template < class queueElementType >
queueElementType Queue < queueElementType >::dequeue()
{
   assert(!isEmpty());
   nodePtr n(f);
   queueElementType frontElement(f->data);
   f = f->next;
   delete n;
   if (f == 0)
      r = 0;
   return frontElement;
}

template < class queueElementType >
queueElementType Queue < queueElementType >::front()
{
   assert(!isEmpty());
   return f->data;
}


