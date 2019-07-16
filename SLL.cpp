//Cr34t0r: @p1nkpengw1n 
//Checked for memory leaks w/ ASan. Use -std=c++11 (or higher) switch when compiling with g++/clang++. Cheers! x) 
//16.07.19//

#include <iostream>

class Node {
public:
    Node* next;
    int data;
};

class LinkedList {
private:
    Node* first = nullptr;
public:
    Node* get_first_node() { return this->first; }
    void set_first_node(Node* first) {
        this->first = first;
    }
    Node* create_node(int data);
    void add(int information);
    void add(int information, int position);
    void delete_node_pos(int position);
    void delete_node_data(int information);
    Node* max_node();
    void reverse_sll();
    void display_sll();
    void display_menu();
    void run();
    void sort_sll();
    void delete_sll();
};

Node* LinkedList::create_node(int data) {
    Node* new_node = new (class Node); //ALTERNATIVES(w/ slight discrepancy): (class Node*) malloc(sizeof(class Node)); OR new Node();
    if(nullptr == new_node) {
        std::cout << "\nMemory allocation failed.\n";
        exit(1);
    }
    new_node->data = data;
    new_node->next = nullptr;
    return new_node;
}

void LinkedList::add(int information) {
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

void LinkedList::add(int information, int position) {
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

void LinkedList::delete_node_pos(int position) {
    int i = 1;
    Node *pe = nullptr;
    Node *p = first;
    while (p != nullptr && i != position) {
        pe = p;
        p = p->next;
        i++;
    }
    if (i != position || nullptr == first) {
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

void LinkedList::delete_node_data(int information) {
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

Node* LinkedList::max_node() {
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

void LinkedList::reverse_sll() {
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

void LinkedList::display_sll() {
    Node* current_node = first;
    if(nullptr == current_node) std::cout<<"\nThe Singly Linked List is empty!\n";
    while(current_node != nullptr) {
        std::cout << current_node->data << " - ";
        current_node = current_node->next;
    }
    std::cout<<"NULL"<<'\n';
}

void LinkedList::delete_sll() {
    Node* pe = nullptr;
    Node* p = first;
    while(p != nullptr) {
        pe = p;
        p = p->next;
        delete(pe);
    }
}

void LinkedList::sort_sll() { //Alternative version (slightly changed) of insertion sort on SLL. The time complexity results O(n^2).
                               //Note that the process would be slightly more efficient on Linked Lists with a head element. 
                               //Also note that merge sort has the smallest time complexity on Singly Linked Lists.
    Node* pe = nullptr;
    Node* p = get_first_node();
    if(p != nullptr) {
        //Dealing with the first node. The most efficient way (after personal assessment) involves selecting the node with the smallest data and attaching it to the beginning.
        Node* min_node = p;
        Node* min_node_prev = pe;
        int min_data = p->data;
        pe = p;
        p = p->next;
        bool first_is_changed = false;
        while(p != nullptr) {
            if(p->data < min_data) {
                min_node_prev = pe;
                min_node = p;
                min_data = p->data;
                first_is_changed = true;
            }
            pe = p;
            p = p->next;
        }
        if(first_is_changed) {
            Node* prev_first = get_first_node();
            min_node_prev->next = min_node->next;
            set_first_node(min_node);
            get_first_node()->next = prev_first;
        }

        //Sorting the rest of the list
        if(get_first_node()->next != nullptr) {
            pe = get_first_node()->next;
            p = pe->next;

            while(p != nullptr) {
                if(p->data < pe->data) {
                    pe->next = p->next;
                    Node* helper_prev = get_first_node();
                    Node* helper = get_first_node()->next;
                    while(p->data > helper->data) {
                        helper_prev = helper;
                        helper = helper->next;
                    }
                    helper_prev->next = p;
                    p->next = helper;
                }
                pe = p;
                p = p->next;
            }
        }
    }
    std::cout << "\nSorting is done!\n";
}

static Node* sort_linked_lists(Node* f1, Node* f2) {
    Node* sorted_first = nullptr;
    Node* ll1 = f1;
    Node* ll2 = f2;
    if(ll1 != nullptr && ll2 != nullptr) {
        if(ll1->data < ll2->data) {
            sorted_first = ll1;
            ll1 = ll1->next;
        }
        else {
            sorted_first = ll2;
            ll2 = ll2->next;
        }
    }
    else if(nullptr == ll1 && ll2 != nullptr) {
        sorted_first = ll2;
        return sorted_first;
    }
    else if(nullptr == ll2 && ll1 != nullptr) {
        sorted_first = ll1;
        return sorted_first;
    }
    else return sorted_first;
    Node* p = sorted_first;
    while(ll1 != nullptr && ll2 != nullptr) {
        if(ll1->data < ll2->data) {
            p->next = ll1;
            p = p->next;
            ll1 = ll1->next;
        }
        else if(ll1->data > ll2->data) {
            p->next = ll2;
            p = p->next;
            ll2 = ll2->next;
        }
        else {
            p->next = ll1;
            p = p->next;
            ll1 = ll1->next;
        }
    }
    if(nullptr == ll1) {
        p->next = ll2;
        return sorted_first;
    }
    else p->next = ll1;
    return sorted_first;
}

void LinkedList::display_menu() {
    std::cout << "\n------------------\n"
        	  << "Press 1 to add a node to the end of the SLL\n"
              << "Press 2 to add a node to a given position of the SLL\n"
              << "Press 3 to delete a node from a given position of the SLL\n"
              << "Press 4 to delete node(s) holding the given data\n"
              << "Press 5 to reverse the SLL\n"
              << "Press 6 to find the node with the maximum data of the SLL\n"
              << "Press 7 to display the SLL\n"
              << "Press 8 to perform insertion sort on the SLL\n"
              << "Press 9 to quit\n"
              << "------------------\n";
}

void LinkedList::run() {
    int x;
    while(x != 9) {
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
            if(max_node() != nullptr)
                std::cout <<"\nThe maximum node value is: " << max_node()->data << '\n';
            else std::cout << "\nThe SLL is empty!\n";
            display_menu();
            break;
        case 7:
            display_sll();
            display_menu();
            break;
        case 8:
            sort_sll();
            display_sll();
            display_menu();
            break;
        /*became obsolete after creating more than one linked list
        case 9:
            exit(1); 
            break;*/
        default:
            display_menu();
            break;
        }
    }
}

//Demo test run 
//Creating two linked lists and merging their sorted versions together

int main() {

    LinkedList ll;
    ll.display_menu();
    ll.run();
    
    LinkedList ll2;
    ll2.display_menu();
    ll2.run();

    ll.sort_sll();
    ll2.sort_sll();

    LinkedList merged;
    merged.set_first_node(sort_linked_lists(ll.get_first_node(),ll2.get_first_node()));
    merged.display_sll();

    if(merged.get_first_node() != nullptr)
        merged.delete_sll();
}