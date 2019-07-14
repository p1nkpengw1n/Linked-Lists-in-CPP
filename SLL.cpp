//Cr34t0r: @p1nkpengw1n Checked for memory leaks w/ ASan. Cheers! x) //14.07.19//
#include <iostream>

class Node {
public:
    Node* next;
    int data;
};

Node* first = nullptr;
Node* create_node(int data);
void add(int information);
void add(int information, int position);
void delete_node_pos(int position);
void delete_node_data(int information);
Node* max_node();
void reverse_sll();
void display_sll();
void delete_sll();

Node* create_node(int data) {
    Node* new_node = new (class Node); //ALTERNATIVES(w/ slight discrepancy): (class Node*) malloc(sizeof(class Node)); OR new Node();
    if(nullptr == new_node) {
        std::cout << "\nMemory allocation failed.\n";
        exit(1);
    }
    new_node->data = data;
    new_node->next = nullptr;
    return new_node;
}

void add(int information) {
    Node* pe = nullptr;
    Node* p = first;
    Node* new_node = create_node(information);
    if(nullptr == first) first = new_node; //lhs check to avoid accidental assignment
    else {
        while(p != nullptr) {
        pe = p;
        p = p->next;
    }
    pe->next = new_node;
    }
    std::cout<<"\nNode with the given data added successfully!\n";
}

void add(int information, int position) {
    Node* new_node = create_node(information);
    if(1 == position) {
        new_node->next = first;
        first = new_node;
    }
    else {
        int i = 1;
        Node* pe = nullptr;
        Node* p = first;
        while(p != nullptr && i != position) {
            pe = p;
            p = p->next;
            i++;
        }
        if(i != position) {
            std::cout<<"\nGiven position doesn't exist. Node will be attached to the end of the SLL.\n";
            pe->next = new_node;
        }
        else {
            pe->next = new_node;
            new_node->next = p;
        }
    }
    std::cout<<"\nNode with the given data added successfully!\n";
}

void delete_node_pos(int position) {
    int i = 1;
    Node *pe = nullptr;
    Node *p = first;
    while (p != nullptr && i != position) {
        pe = p;
        p = p->next;
        i++;
    }
    if (i != position) {
        std::cout << "\nGiven position doesn't exist.\n";
    }
    else {
        if(nullptr == pe) {
            first = p->next;
            delete(p);
        }
        else {
            pe->next = p->next;
            delete(p);
        }
    }
}

void delete_node_data(int information) {
    Node* pe = nullptr;
    Node* p = first;
    while(p != nullptr) {
        if(information == p->data) {
            if(nullptr == pe) {
                first = p->next;
                delete(p);
                p = first;
            }
            else {
                pe->next = p->next;
                delete(p);
                p = pe->next;
            }

        }
        else {
            pe = p;
            p = p->next;
        }  
    }
}

Node* max_node() {
    if(nullptr == first) {
        return nullptr; 
    }
    int max_data = first->data;
    Node* max_node = first;
    Node* p = first->next;
    while(p != nullptr) {
        if(p->data > max_data) {
            max_data = p->data;
            max_node = p;
        }
        p = p->next;
    }
    return max_node;
}

void reverse_sll() {
    Node* pe = nullptr;
    Node* p = first;
    Node* helper = nullptr;
    if(nullptr != first) {
        helper = first->next;
        while(helper != nullptr) {
            p->next = pe;
            pe = first = p;
            p = helper;
            helper = helper->next;
    }
        p->next = pe;
        pe = first = p;
    }
    std::cout<<"\nReverse complete!\n";
}

void display_sll() {
    Node* current_node = first;
    if(current_node == nullptr) std::cout<<"\nThe Singly Linked List is empty!\n";
    while(current_node != nullptr) {
        std::cout << current_node->data << " - ";
        current_node = current_node->next;
    }
    std::cout<<"NULL"<<'\n';
}

void delete_sll() {
    Node* pe = nullptr;
    Node* p = first;
    while(p != nullptr) {
        pe = p;
        p = p->next;
        delete(pe);
    }
}

void display_menu() {
    std::cout << "\n------------------\n"
        	  << "Press 1 to add a node to the end of the SLL\n"
              << "Press 2 to add a node to a given position of the SLL\n"
              << "Press 3 to delete a node from a given position of the SLL\n"
              << "Press 4 to delete node(s) holding the given data\n"
              << "Press 5 to reverse the SLL\n"
              << "Press 6 to find the node with the maximum data of the SLL\n"
              << "Press 7 to display the SLL\n"
              << "Press 8 to quit\n"
              << "------------------\n";
}

void run() {
    while(true) {
        int x;
        std::cin>>x;
    switch(x) {
        case 1:
            int y;
            std::cout<<"\nEnter node data:\n";
            std::cin>>y;
            add(y);
            display_sll();
            display_menu();
            break;
        case 2:
            int z,zz;
            std::cout<<"\nEnter node data:\n";
            std::cin>>z;
            std::cout<<"\nEnter node position:\n";
            std::cin>>zz;
            add(z,zz);
            display_sll();
            display_menu();
            break;
        case 3:
            int zzz;
            std::cout<<"\nEnter position to delete node from:\n";
            std::cin>>zzz;
            delete_node_pos(zzz);
            display_sll();
            display_menu();
            break;
        case 4:
            int d;
            std::cout<<"\nEnter node data to be removed from the SLL:\n";
            std::cin>>d;
            delete_node_data(d);
            display_sll();
            display_menu();
            break;
        case 5:
            reverse_sll();
            display_sll();
            display_menu();
            break;
        case 6:
            std::cout <<"\nThe maximum node value is: " << max_node()->data << '\n';
            display_menu();
            break;
        case 7:
            display_sll();
            display_menu();
            break;
        case 8:
            exit(1);
            break;
        default:
            display_menu();
            break;
        }
    }
}

int main() {
    display_menu();
    run();
    delete_sll();
}