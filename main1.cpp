#include "stack.h"
#include <iostream>

using namespace std;

int main() {
    Stack<int> st;
    st.Push(1);
    st.Push(2);
    st.Push(3);
    st.Push(4);
    st.Push(5);


    cout << "initial capacity: " << st.Capacity() << endl;
    cout << "Size: " << st.Size() << endl; 

    while (!st.IsEmpty()) {
        cout << st.Pop() << endl;
        cout << "Current Size: " << st.Size() << endl; 
    }

    cout << "final capacity: " << st.Capacity() << endl;

    return 0;
}