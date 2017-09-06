#include <cstdlib>
#include <string>
#include <iostream>
#include "Table.h"

using namespace std;

int main(int argc, char *argv[])
{
    Queue <string>Q,temp;
    string S;
    
    //Abdelrazik&Abdelgawad (Indexing)
    string key;
    string data,x;
    Table < string, string >T;
    
    T.insert("A", "Ahmed");
    T.insert("ah", "Mohmed");
    T.insert("se", "Senouse");
    T.insert("sa", "sadej");
    T.insert("ki", "kjlhasrfglk");
    
    //Searching
    do{
    cout<<"enter key"<<endl;
    cin>>key;
    T.lookup(key, Q);
    while(!Q.isEmpty())
    {x=Q.dequeue();
    temp.enqueue(x);
    cout<<x<<endl;
    }
    while(!temp.isEmpty())
    Q.enqueue(temp.dequeue());
    cout<<"enter e to exit"<<endl;
    cin>>S;
    }while(S!="e");
    system("PAUSE");
    return EXIT_SUCCESS;
}
