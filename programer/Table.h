#include <assert.h>
#include "Queue.h"

const int MAX_TABLE = 100;
template < class tableKeyType, class tableDataType >
class Table
{
public:
   Table();
   void insert(const tableKeyType & key, const tableDataType & data);
   bool lookup(const tableKeyType & key, Queue < tableDataType > & Q);
   void deleteKey(const tableKeyType & key);
private:
   struct Slot;
   typedef Slot * Link;
   struct Slot {
      tableKeyType key;
      tableDataType data;
      Queue < tableDataType >Q;
      Link next;
   };
   Link T[MAX_TABLE];
   int hash(const tableKeyType & key);
   bool search(Link & slotPointer, const tableKeyType & target);
};

template < class tableKeyType, class tableDataType >
int Table < tableKeyType, tableDataType > ::hash(const tableKeyType & key)
{
 int hashvalue=0;
 int letter;
 for(int i=0;i<key.length();i++)
 {
  letter=key[i]-96;
  hashvalue=(hashvalue*27+letter)%MAX_TABLE;
 }
 return hashvalue;   

}

template < class tableKeyType, class tableDataType >
bool Table < tableKeyType, tableDataType > ::search(Link & slotPointer, const tableKeyType & target)
{
   for ( ; slotPointer; slotPointer = slotPointer -> next)
      if (slotPointer->key == target)
         return true;
   return false;
}
template < class tableKeyType, class tableDataType >
Table < tableKeyType, tableDataType > ::Table()
{
   int i;
   for (i = 0; i < MAX_TABLE; i++)
      T[i] = 0;
}
template < class tableKeyType, class tableDataType >
void Table < tableKeyType, tableDataType > ::insert(const tableKeyType & key, const tableDataType & data)
{
   int pos(hash(key));
   Link sp(T[pos]);
   if (!search(sp, key)) {
      Link insertedSlot = new Slot;
      insertedSlot->key = key;
      insertedSlot->Q.enqueue(data);
      insertedSlot->next = T[pos];
      T[pos] = insertedSlot;
   }
   else
   sp->Q.enqueue(data);
}
template < class tableKeyType, class tableDataType >
bool Table < tableKeyType, tableDataType > ::lookup(const tableKeyType & key, Queue < tableDataType > & Q)
{
   int pos(hash(key));
   Link sp(T[pos]);
   if (search(sp, key)) {
      Q = sp->Q;
      return true;
   }
   else
      return false;
}
template < class tableKeyType, class tableDataType >
void Table < tableKeyType, tableDataType >::deleteKey(const tableKeyType & key)
{
   int pos(hash(key));
   Link p;
   if (0 == T[pos])
      return;
   if (T[pos]->key == key) {
      Link deleteSlot(T[pos]);
      T[pos] = T[pos]->next;
      delete deleteSlot;
   }

   else
      for (p = T[pos]; p->next; p = p->next)
         if (p->next->key == key) {
            Link deleteSlot = p->next;
            p->next = p->next->next;
            delete deleteSlot;
            break;
         }
}
