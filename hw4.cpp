//HW4 due: Thursday (10/8/2020).
#include <iostream>
#include <list>
#include <string>
#include "vector"

using namespace std;
template <class T> class ThreeD {
public:
    T ht;
    T wid;
    T dep;
    ThreeD() :ht(0), wid(0), dep(0) {}
    ThreeD(T i, T j, T k) :ht(i), wid(j), dep(k) {}
    T getVol() const { return ht * wid * dep; }
    bool operator==(const ThreeD<T>& t) const { return getVol() == t.getVol(); }
};

template <class T> class node {
public:
    T value;
    node<T>* next;
    node<T>* previous;
    node<T>() { next = nullptr; previous = nullptr; }
    node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
    bool operator==(const node<T>& t) const { return value == t.value; }
};

template <class T> class linked_list {
public:
    node<T>* head;
    node<T>* tail;
    linked_list() { head = tail = nullptr; }
    linked_list(const initializer_list<T>& V);
    void push_front(T t);//The implementation is given below.
    void push_back(T t);//The implementation is given below.
    bool operator==(const linked_list<T>& L) const;

    linked_list(const linked_list<T>& L); //copy constructor
    linked_list(linked_list<T>&& L); //move constructor
    ~linked_list();//destructor
    void operator=(const linked_list<T>& L);//Lvalue operator= ; i.e., copy assignment
    void operator=(linked_list<T>&& L);//Rvalue operator= ; i.e., move assignment

};
template <class T> linked_list<T>::linked_list(const initializer_list<T>& V) : linked_list() {
    //Your code
    cout << "initializer_list LL" << endl;
    for(auto cell : V){
        push_back(cell);
    }
}

template <class T> linked_list<T>::~linked_list() {  //destructor										
    //Your code
    cout << "Destructor LL" << endl;
    while(head){
        node<T>* p = head->next;
        delete head;
        head = p;
    }
    head = tail = nullptr;
}

template <class T> linked_list<T>::linked_list(const linked_list<T>& L) : linked_list() { //copy constructor																			  																		  //num_nodes = 0;
    //Your code
    cout << "Copy Constructor LL" << endl;
    node<T>* h = L.head;
    while(h){
        push_back(h->value);
        h = h->next;
    }

}
template <class T> linked_list<T>::linked_list(linked_list<T>&& L) {//move constructor
    //Your code
    cout << "Move Constructor LL" << endl;
    head = L.head;
    tail = L.tail;
    L.head = L.tail = nullptr;
}

template <class T> void linked_list<T>::operator=(const linked_list<T>& L) { //Lvalue operator=
    //Your code
    cout << "Copy Assignment LL" << endl;
    while(head){
        node<T>* p = head->next;
        delete head;
        head = p;
    }
    head = tail = nullptr;
    while(L.head){
        push_back(L.head->value);
    }
}

template<class T> void linked_list<T>::operator=(linked_list<T>&& L) {//R-value operator=
    //Your code
    cout << "Move Assignment LL" << endl;
    while(head){
        node<T>* p = head->next;
        delete head;
        head = p;
    }
    head = tail = nullptr;
    head = L.head;
    tail = L.tail;
    L.head = L.tail = nullptr;
}


template <class T> void linked_list<T>::push_front(T t) {
    node<T>* p = new node<T>(t);
    if (head == nullptr) { head = tail = p; }
    else {
        p->next = head;
        head->previous = p;
        head = p;
    }
}

template <class T> void linked_list<T>::push_back(T t)
{
    node<T>* p = new node<T>(t);
    if (head == nullptr) { head = tail = p; }

    else {
        p->previous = tail;
        tail->next = p;
        tail = p;
    }
}

template <class T> bool linked_list<T>::operator==(const linked_list<T>& L) const {
    //Your code
    //Two linked lists are equal if they have same number of nodes, and each pair of corresponding nodes have equal values.
    cout << "operator== LL" << endl;
    vector<node<T>*> v1;
    vector<node<T>*> v2;

    node<T>* current = L.head;
    while(current){
        v1.push_back(current);
        current = current->next;
    }
    current = head;
    while(current){
        v2.push_back(current);
        current = current->next;
    }
    if(v1.size() != v2.size()){
        return false;
    }
    for (int i = 0; i < v1.size(); i++){
        if(v1[i]->value == v2[i]->value){
            continue;
        }else{
            return false;
        }
    }
    return true;
}







template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
    str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
    return str;
}

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L) {
    str << "[";
    node<T>* p = L.head;
    while (p) {
        str << p->value << " ";
        p = p->next;
    }
    str << "]";
    return str;
}

template <typename T> class Node { //Your T has to support either int or float
public:
    T * pValue; //pValue is a pointer to an object of type T
    Node<T> * row_next;//Points to the next node in the same row
    Node<T> * col_next;//Points to the nexe node in the same col
    Node() {}
    Node(T v) { pValue = new T (v); }
};

template <typename T> class Ring2D {
public:
    Node<T> * head;//Points to the node at first row and first column
    T * pValue;

    Ring2D(): head(nullptr) {};

    //Implement the following functions:
    Ring2D(const initializer_list< initializer_list<T>>& I); //nested initializer_list; will explain in class
    /*
    For example, {{1, 2, 3, 4} , {5, 6, 7, 8},  {9, 10, 11, 12}}: 3 rows and 4 columns; first row: pointers to 1 2 3 4;
    second row: pointers to 5 6 7 8; third row: pointers to 9 10 11 12
    */

    ~Ring2D();//destructor;
    Ring2D(const Ring2D<T>& R);//copy constructor

    void operator=(const Ring2D<T>& R);//Lvalue operator=; i.e., copy assignment

    Ring2D(Ring2D<T>&& R);//move constructor
    void operator=(Ring2D<T>&& R);//Rvalue operator=; i.e.,move assignment
    Ring2D<T> ThreeTimes();//Return a Ring2D with values being three times of the current Ring2D

    bool operator==(const Ring2D<T>& R) const;
};

template <class T> bool Ring2D<T>::operator==(const Ring2D<T>& R) const {
    //Your code
    //If you return in the middle of code, you also need to print the following message
    cout << "Operator== Ring2D" << endl;

    vector<vector<Node<T>*>> r_v;
    vector<vector<Node<T>*>> head_v;

    bool flag_row = false;
    Node<T>* current_row = R.head;
    while(not flag_row || current_row != R.head){
        if (current_row == R.head){
            flag_row = true;
        }
        vector<Node<T>*> current_row_v;
        Node<T>* current_node = current_row;
        bool flag_column = false;
        while(not flag_column || current_node != current_row){
            if (current_node == current_row){
                flag_column = true;
            }
            current_row_v.push_back(current_node);
            current_node = current_node->row_next;
        }
        r_v.push_back(current_row_v);
        current_row_v.clear();
        current_row = current_row->col_next;
    }


    flag_row = false;
    current_row = head;
    while(not flag_row || current_row != head){
        if (current_row == head){
            flag_row = true;
        }
        vector<Node<T>*> current_row_v;
        Node<T>* current_node = current_row;
        bool flag_column = false;
        while(not flag_column || current_node != current_row){
            if (current_node == current_row){
                flag_column = true;
            }
            current_row_v.push_back(current_node);
            current_node = current_node->row_next;
        }
        head_v.push_back(current_row_v);
        current_row_v.clear();
        current_row = current_row->col_next;
    }

    int r_row = r_v.size();
    int r_column = r_v[0].size();
    int head_row = head_v.size();
    int head_column = head_v[0].size();
    if (r_row != head_row || r_column != head_column){
        return false;
    }
    for (int r = 0; r < r_row; r++){
        for (int c = 0; c < r_column; c++){
            if(*r_v[r][c]->pValue == *head_v[r][c]->pValue){
                continue;
            }else{
                return false;
            }
        }
        r_v[r].clear();
        head_v[r].clear();
    }
    r_v.clear();
    head_v.clear();
    return true;
}



template <class T> void Ring2D<T>::operator=(Ring2D<T>&& R) {//;//Rvalue operator=; move assignment
    //Your code
    cout << "Move Assignment Ring2D" << endl;
    // delete current head content
    if(head != nullptr){
        vector<vector<Node<T>*>> og_2d;
        Node<T>* og_head = head;

        bool flag_row = false;
        Node<T>* current_row = og_head;
        while(not flag_row || current_row != og_head){
            vector<Node<T>*> current_row_v;
            if (current_row == og_head){
                flag_row = true;
            }
            Node<T>* current_node = current_row;
            bool flag_column = false;
            while(not flag_column || current_node != current_row){
                if (current_node == current_row){
                    flag_column = true;
                }
                current_row_v.push_back(current_node);
                current_node = current_node->row_next;
            }
            og_2d.push_back(current_row_v);
            current_row_v.clear();
            current_row = current_row->col_next;
        }
        // right now, we have already found all previous nodes
        // delete them
        int row_size = og_2d.size();
        int column_size = og_2d[0].size();
        for(int r = 0; r < row_size; r++){
            for(int c = 0; c < column_size; c++){
                delete og_2d[r][c];
                if(c == column_size - 1){
                    og_2d[r].clear();
                }
            }
        }
        og_2d.clear();
    }

    head = R.head;
    R.head = nullptr;
}

template<class T> Ring2D<T>::Ring2D(Ring2D<T>&& R) {//;//move constructor
    //Your code
    cout << "Move Constructor Ring2D" << endl;
    head = R.head;
    R.head = nullptr;
}

template <class T> Ring2D<T> Ring2D<T>::ThreeTimes() {//ThreeTimes;
    //Your code

    // pointing to the current object, copy constructor
    Ring2D<T> tmp {*this};
    cout << "ThreeTimes Ring2D" << endl;
    Node<T> *tmp_head = tmp.head;
    bool flag_row = false;
    Node<T> *current_row = tmp_head;
    while (not flag_row || current_row != tmp_head) {
        if (current_row == tmp_head) {
            flag_row = true;
        }
        Node<T> *current_node = current_row;
        bool flag_column = false;
        while (not flag_column || current_node != current_row) {
            if (current_node == current_row) {
                flag_column = true;
            }
            *current_node->pValue = (*current_node->pValue) * 3;
            current_node = current_node->row_next;
        }
        current_row = current_row->col_next;
    }
    return tmp;
}



template <class T> Ring2D<T>::~Ring2D() {//;//destructor
    //Your code
    //If you return in the middle of your code, you also need to print the following message.
    cout << "Destructor Ring2D" << endl;

    // we create a 2-dimension vector to store all nodes, then delete all nodes.
    if(head != nullptr){
        vector<vector<Node<T>*>> og_2d;
        Node<T>* og_head = head;

        bool flag_row = false;
        Node<T>* current_row = og_head;
        while(not flag_row || current_row != og_head){
            vector<Node<T>*> current_row_v;
            if (current_row == og_head){
                flag_row = true;
            }
            Node<T>* current_node = current_row;
            bool flag_column = false;
            while(not flag_column || current_node != current_row){
                if (current_node == current_row){
                    flag_column = true;
                }
                current_row_v.push_back(current_node);
                current_node = current_node->row_next;
            }
            og_2d.push_back(current_row_v);
            current_row_v.clear();
            current_row = current_row->col_next;
        }
        // right now, we have already found all previous nodes
        // delete them
        int row_size = og_2d.size();
        int column_size = og_2d[0].size();
        for(int r = 0; r < row_size; r++){
            for(int c = 0; c < column_size; c++){
                delete og_2d[r][c];
                if(c == column_size - 1){
                    og_2d[r].clear();
                }
            }
        }
        og_2d.clear();
    }
}


template <class T> void Ring2D<T>::operator=(const Ring2D<T>& R) {//;//Lvalue operator=; copy assignment
    //Your code
    //If you return in the middle of your code, you also need to print the following message.
    cout << "Copy Assignment Ring2D" << endl;

    // delete the existing head first, we can do the same thing
    // putting the all of nodes into a 2-D vector, then deleting them one by one
    if(head != nullptr){
        vector<vector<Node<T>*>> og_2d;
        Node<T>* og_head = head;

        bool flag_row = false;
        Node<T>* current_row = og_head;
        while(not flag_row || current_row != og_head){
            vector<Node<T>*> current_row_v;
            if (current_row == og_head){
                flag_row = true;
            }
            Node<T>* current_node = current_row;
            bool flag_column = false;
            while(not flag_column || current_node != current_row){
                if (current_node == current_row){
                    flag_column = true;
                }
                current_row_v.push_back(current_node);
                current_node = current_node->row_next;
            }
            og_2d.push_back(current_row_v);
            current_row_v.clear();
            current_row = current_row->col_next;
        }
        // right now, we have already found all previous nodes
        // delete them
        int row_size = og_2d.size();
        int column_size = og_2d[0].size();
        for(int r = 0; r < row_size; r++){
            for(int c = 0; c < column_size; c++){
                delete og_2d[r][c];
                if(c == column_size - 1){
                    og_2d[r].clear();
                }
            }
        }
        og_2d.clear();
    }

    // do the same thing as copy constructor
    vector<vector<Node<T>*>> r2d;
    vector<vector<Node<T>*>> new_v;
    Node<T>* r_head = R.head;

    // start the traversal
    bool flag_row = false;
    Node<T>* current_row = r_head;
    while(not flag_row || current_row != r_head){
        if(current_row == r_head){
            flag_row = true;
        }
        vector<Node<T>*> current_row_v;
        vector<Node<T>*> new_row_v;

        //start the traversal current row
        Node<T>* current = current_row;
        bool flag_column = false;
        while(not flag_column || current != current_row){
            if(current == current_row){
                flag_column = true;
            }
            current_row_v.push_back(current);
            new_row_v.push_back(new Node<T>{*current->pValue});
            current = current->row_next;
        }
        r2d.push_back(current_row_v);
        new_v.push_back(new_row_v);
        current_row_v.clear();
        new_row_v.clear();
        current_row = current_row->col_next;
    }
    r2d.clear();
    int row_size = new_v.size();
    int column_size = new_v[0].size();
    for(int r = 0; r < row_size; r++){
        for(int c = 0; c < column_size; c++){
            if (c == column_size - 1){
                new_v[r][c]->row_next = new_v[r][0];
                new_v[r].clear();
            }else{
                new_v[r][c]->row_next = new_v[r][c + 1];
            }
            if (r == row_size - 1){
                new_v[r][c]->col_next = new_v[0][c];
            }else{
                new_v[r][c]->col_next = new_v[r + 1][c];
            }
        }
    }
    new_v.clear();
    head = new_v[0][0];
    pValue = head->pValue;
}


template<class T> Ring2D<T>::Ring2D(const Ring2D<T>& R) {//copy constructor
    //Your code
    //If you return in the middle of your code, you also need to print the following message.
    vector<vector<Node<T>*>> r2d;
    vector<vector<Node<T>*>> new_v;
    Node<T>* r_head = R.head;

    // start the traversal
    bool flag_row = false;
    Node<T>* current_row = r_head;
    while(not flag_row || current_row != r_head){
        if(current_row == r_head){
            flag_row = true;
        }
        vector<Node<T>*> current_row_v;
        vector<Node<T>*> new_row_v;

        //start the traversal current row
        Node<T>* current = current_row;
        bool flag_column = false;
        while(not flag_column || current != current_row){
            if(current == current_row){
                flag_column = true;
            }
            current_row_v.push_back(current);
            new_row_v.push_back(new Node<T>{*current->pValue});
            current = current->row_next;
        }
        r2d.push_back(current_row_v);
        new_v.push_back(new_row_v);
        current_row_v.clear();
        new_row_v.clear();
        current_row = current_row->col_next;
    }
    r2d.clear();
    int row_size = new_v.size();
    int column_size = new_v[0].size();
    for(int r = 0; r < row_size; r++){
        for(int c = 0; c < column_size; c++){
            if (c == column_size - 1){
                new_v[r][c]->row_next = new_v[r][0];
                new_v[r].clear();
            }else{
                new_v[r][c]->row_next = new_v[r][c + 1];
            }
            if (r == row_size - 1){
                new_v[r][c]->col_next = new_v[0][c];
            }else{
                new_v[r][c]->col_next = new_v[r + 1][c];
            }
        }
    }
    new_v.clear();
    head = new_v[0][0];
    pValue = head->pValue;
    cout << "Copy Constructor Ring2D" << endl;
}

template <class T> Ring2D<T>::Ring2D(const initializer_list< initializer_list<T>>& I) {
    //Your code

    vector<vector<Node<T>*>> r2d;
    for(auto it1 = I.begin(); it1 != I.end(); it1++){
        vector<Node<T>*> current_row;
        for (auto it2 = it1->begin(); it2 != it1->end(); it2++){
            Node<T>* new_node = new Node<T>;
            new_node->pValue = new T(*it2);
            current_row.push_back(new_node);
        }
        r2d.push_back(current_row);
        current_row.clear();
    }
    for(int row = 0; row < r2d.size(); row++){
        for(int column = 0; column < r2d[0].size(); column++){
            if(column == r2d[0].size()-1){
                r2d[row][column]->row_next = r2d[row][0];
            }else{
                r2d[row][column]->row_next = r2d[row][column + 1];
            }
            if(row == r2d.size() - 1){
                r2d[row][column]->col_next = r2d[0][column];
            }else{
                r2d[row][column]->col_next = r2d[row + 1][column];
            }
        }
    }
    head = r2d[0][0];
    pValue = head->pValue;
    for(int row = 0; row < r2d.size(); row++){
        r2d[row].clear();
    }
    r2d.clear();
    cout << "initializer_list Ring2D" << endl;
}


template<class T> ostream& operator<<(ostream& str, const Ring2D<T>& R) {
    //Your codeR
    Node<T>* current_row = R.head;
    if (not current_row){
        return str;
    }
    // only one row
    if(current_row->row_next == current_row){
        Node<T>* current_cell = current_row;
        if(current_cell == current_cell->row_next){
            str << *current_cell << endl;
        }else{
            bool column_seen = false;
            while(not column_seen){
                if(current_cell->row_next == current_row){
                    column_seen = true;
                }
                str << *current_cell << " ";
            }
        }
    }
    // normal condition
    bool row_seen = false;
    while (not row_seen){
        if(current_row->col_next == R.head){
            row_seen = true;
        }
        Node<T>* current_cell = current_row;
        bool column_seen = false;
        cout << "{ " ;
        while(not column_seen){
            if(current_cell->row_next == current_row){
                column_seen = true;
            }
            str << *current_cell << " ";
            current_cell = current_cell->row_next;
        }
        cout << "} " << endl;
        current_row = current_row->col_next;
    }
    return str;

}

template<class T> ostream& operator<<(ostream& str, const Node<T>& n){
    str << *n.pValue << " ";
    return str;
}

int main() {

    cout << "..............R1.............." << endl;
    Ring2D<int> R1{{1, 2, 3, 4},  {5, 6, 7, 8},  {9, 10, 11, 12} };//initializer_list
    cout << R1 << endl << endl;

    cout << "..............R2.............." << endl;
    Ring2D<int> R2{ R1 };
    cout << R2 << endl;
    cout << "..............R3.............." << endl;
    Ring2D<int> R3{};
    R3 = R1;
    cout << R3 << endl;
    cout << "..............R4.............." << endl;
    Ring2D<int> R4;
    R4 = R1.ThreeTimes();
    cout << R4 << endl;
    cout << (R4 == R3) << endl;
    cout << "..............R5.............." << endl;
    Ring2D<linked_list<ThreeD<int>>> R5{ {{{3,4,5},{7,1,4},{6,7,3}},       {{8,4,2},{8,8,2}}},
                                         {{{9,5,4},{10,3,2},{7,9,1},{2,2,3}},      { {5,4,8 },{4,2,16},{7, 8, 4} } }
    };
    cout << R5 << endl;
    cout << "..............R6.............." << endl;
    Ring2D<linked_list<ThreeD<int>>> R6{ {{{5,3,4,},{14,2,1},{6,7,3}},{{8,2,4},{8,4,4}}},
                                         {{{9,4,5},{10,3,2},{7,3,3},{2,3,2}}, { {4, 5,8 },{8,2,8  }, {2, 16, 7} } } };
    cout << R6 << endl;

    cout << "..............R5==R6.............." << endl;
    if (R5 == R6) {
        cout << "EQUAL" << endl;
    }else {
        cout << "NOT EQUQL" << endl;
    }
    cout << "..............p1.............." << endl;
    Ring2D<linked_list<ThreeD<int>>>* p1 = new Ring2D<linked_list<ThreeD<int>>>
            { {{{5,3,4,},{14,2,1},{6,7,3}},     {{8,2,4},{8,4,4}}},
              {{{9,4,5},{10,3,2},{7,3,3},{2,3,2}},   { {4, 5,8 },{8,2,8  }, {2, 16, 7} } } };
    cout << *p1 << endl;
    delete p1;
    return 0;
}
/*
    //Sample screenshot

 R1
initializer_list Ring2D
{ 1 2 3 4 }
{ 5 6 7 8 }
{ 9 10 11 12 }

R2
Copy Constructor Ring2D
{ 1 2 3 4 }
{ 5 6 7 8 }
{ 9 10 11 12 }

 R3
Copy Assignment Ring2D
{ 1 2 3 4 }
{ 5 6 7 8 }
{ 9 10 11 12 }

 R4
Copy Constructor Ring2D
ThreeTimes Ring2D
Move Constructor Ring2D
Destructor Ring2D
Move Assignment Ring2D
Destructor Ring2D
{ 3 6 9 12 }
{ 15 18 21 24 }
{ 27 30 33 36 }

initializer_list LL
initializer_list LL
initializer_list LL
initializer_list LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
initializer_list Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
{ [(3, 4, 5) (7, 1, 4) (6, 7, 3) ] [(8, 4, 2) (8, 8, 2) ] }
{ [(9, 5, 4) (10, 3, 2) (7, 9, 1) (2, 2, 3) ] [(5, 4, 8) (4, 2, 16) (7, 8, 4) ] }

initializer_list LL
initializer_list LL
initializer_list LL
initializer_list LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
initializer_list Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
{ [(5, 3, 4) (14, 2, 1) (6, 7, 3) ] [(8, 2, 4) (8, 4, 4) ] }
{ [(9, 4, 5) (10, 3, 2) (7, 3, 3) (2, 3, 2) ] [(4, 5, 8) (8, 2, 8) (2, 16, 7) ] }

operator== LL
operator== LL
operator== LL
operator== LL
Operator== Ring2D
EQUAL
initializer_list LL
initializer_list LL
initializer_list LL
initializer_list LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
initializer_list Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
{ [(5, 3, 4) (14, 2, 1) (6, 7, 3) ] [(8, 2, 4) (8, 4, 4) ] }
{ [(9, 4, 5) (10, 3, 2) (7, 3, 3) (2, 3, 2) ] [(4, 5, 8) (8, 2, 8) (2, 16, 7) ] }

Destructor Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
Destructor Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
Destructor Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
Destructor Ring2D
Destructor Ring2D
Destructor Ring2D
Destructor Ring2D	
    */
