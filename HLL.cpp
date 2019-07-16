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
    Node* head_element = nullptr;
public:
    void set_head_element(Node* he) { this->head_element = he; }
    Node* get_first_node() { return head_element != nullptr ? this->head_element->next : nullptr; }
    void set_first_node(Node* first) {
        this->head_element->next = first;
    }
    int get_node_count() { return head_element != nullptr ? this->head_element->data : 0; }
    Node* create_node(int data);
    void add(int information);
    void add(int information, int position);
    void delete_node_pos(int position);
    void delete_node_data(int information);
    Node* max_node();
    void reverse_hll();
    void display_hll();
    void display_menu();
    void run();
    void sort_hll();
    void delete_hll();
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
    Node* new_node = create_node(information);
    if(nullptr == head_element) {
        head_element = create_node(1);
        head_element->next = new_node;
    }
    else {
        Node* pe = head_element;
        Node* p = head_element->next;
        while(p != nullptr) {
        pe = p;
        p = p->next;
    }
        pe->next = new_node;
        this->head_element->data++;
    }
    std::cout<<"\nNode with the given data added successfully!\n";
}

void LinkedList::add(int information, int position) {
    Node* new_node = create_node(information);
    if(nullptr == head_element) {
        new_node->next = nullptr;
        head_element = create_node(1);
        head_element->next = new_node;
    }
    else if(1 == position) {
        new_node->next = head_element->next;
        head_element->next = new_node;
        this->head_element->data++;
    }
    else {
        int i = 1;
        Node* pe = head_element;
        Node* p = head_element->next;
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
        this->head_element->data++;
    }
    std::cout<<"\nNode with the given data added successfully!\n";
}

void LinkedList::delete_node_pos(int position) {
    if(head_element != nullptr) {
        int i = 1;
        Node *pe = head_element;
        Node *p = head_element->next;
        while (p != nullptr && i != position) {
            pe = p;
            p = p->next;
            i++;
        }
        if (i != position) {
            std::cout << "\nGiven position doesn't exist.\n";
        }
        else {
            if(head_element == pe) {
                head_element->next = p->next;
                delete(p);
            }
            else {
                pe->next = p->next;
                delete(p);
            }
            this->head_element->data--;
        }
    }
    else std::cout << "\n Given position doesn't exist.\n";
}

void LinkedList::delete_node_data(int information) {
    if(head_element != nullptr) {
        Node* pe = head_element;
        Node* p = head_element->next;
        while(p != nullptr) {
            if(information == p->data) {
                if(head_element == pe) {
                    head_element->next = p->next;
                    delete(p);
                    p = head_element->next;
                }
                else {
                    pe->next = p->next;
                    delete(p);
                    p = pe->next;
                }
                this->head_element->data--;
            }
            else {
                pe = p;
                p = p->next;
            }  
        }
    }
}

Node* LinkedList::max_node() {
    if(nullptr == head_element) {
        return nullptr; 
    }
    int max_data = head_element->next->data;
    Node* max_node = head_element->next;
    Node* p = head_element->next;
    while(p != nullptr) {
        if(p->data > max_data) {
            max_data = p->data;
            max_node = p;
        }
        p = p->next;
    }
    return max_node;
}

void LinkedList::reverse_hll() {
    Node* pe = nullptr;
    Node* p = head_element;
    Node* helper = nullptr;
    if(head_element != nullptr) {
        if(head_element->next != nullptr) {
            p = head_element->next;
            helper = p->next;
            while(helper != nullptr) {
                p->next = pe;
                pe = head_element->next = p;
                p = helper;
                helper = helper->next;
            }
            p->next = pe;
            pe = head_element->next = p;
        }
    }
    std::cout<<"\nReverse complete!\n";
}

void LinkedList::display_hll() {
    if(nullptr == head_element) {
        std::cout<<"\nThe Singly Linked List is empty!\n";
        return;
    }
    Node* current_node = head_element->next;
    std::cout << "\nThe HLL contains " << get_node_count() << " nodes.\n";
    std::cout << "HE - ";
    while(current_node != nullptr) {
        std::cout << current_node->data << " - ";
        current_node = current_node->next;
    }
    std::cout<<"NULL"<<'\n';
}

void LinkedList::delete_hll() {
    Node* pe = nullptr;
    Node* p = head_element;
    while(p != nullptr) {
        pe = p;
        p = p->next;
        delete(pe);
    }
}

void LinkedList::sort_hll() {
    Node* pe = nullptr;
    Node* p = get_first_node();
    if(p != nullptr) {
        if(get_first_node()->next != nullptr) {
            pe = get_first_node();
            p = pe->next;
            while(p != nullptr) {
                if(p->data < pe->data) {
                    pe->next = p->next;
                    Node* helper_prev = head_element;
                    Node* helper = get_first_node();
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
    Node* sorted_head_element = nullptr;
    Node* ll1 = f1;
    Node* ll2 = f2;
    if(ll1 != nullptr && ll2 != nullptr) {
        if(ll1->data < ll2->data) {
            sorted_head_element = new (class Node);
            sorted_head_element->next = ll1;
            ll1 = ll1->next;
        }
        else {
            sorted_head_element = new (class Node);
            sorted_head_element->next = ll2;
            ll2 = ll2->next;
        }
    }
    else if(nullptr == ll1 && ll2 != nullptr) {
        sorted_head_element = new (class Node);
        sorted_head_element->next = ll2;
        return sorted_head_element->next;
    }
    else if(nullptr == ll2 && ll1 != nullptr) {
        sorted_head_element = new (class Node);
        sorted_head_element->next = ll1;
        return sorted_head_element->next;
    }
    else return sorted_head_element->next;
    Node* p = sorted_head_element->next;
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
        return sorted_head_element->next;
    }
    else p->next = ll1;
    return sorted_head_element->next;
}

void LinkedList::display_menu() {
    std::cout << "\n------------------\n"
        	  << "Press 1 to add a node to the end of the HLL\n"
              << "Press 2 to add a node to a given position of the HLL\n"
              << "Press 3 to delete a node from a given position of the HLL\n"
              << "Press 4 to delete node(s) holding the given data\n"
              << "Press 5 to reverse the HLL\n"
              << "Press 6 to find the node with the maximum data of the HLL\n"
              << "Press 7 to display the HLL\n"
              << "Press 8 to perform insertion sort on the HLL\n"
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
            display_hll();
            display_menu();
            break;
        case 2:
            int z,zz;
            std::cout<<"\nEnter node data:\n";
            std::cin>>z;
            std::cout<<"\nEnter node position:\n";
            std::cin>>zz;
            add(z,zz);
            display_hll();
            display_menu();
            break;
        case 3:
            int zzz;
            std::cout<<"\nEnter position to delete node from:\n";
            std::cin>>zzz;
            delete_node_pos(zzz);
            display_hll();
            display_menu();
            break;
        case 4:
            int d;
            std::cout<<"\nEnter node data to be removed from the HLL:\n";
            std::cin>>d;
            delete_node_data(d);
            display_hll();
            display_menu();
            break;
        case 5:
            reverse_hll();
            display_hll();
            display_menu();
            break;
        case 6:
            if(max_node() != nullptr)
                std::cout <<"\nThe maximum node value is: " << max_node()->data << '\n';
            else std::cout << "\nThe HLL is empty!\n";
            display_menu();
            break;
        case 7:
            display_hll();
            display_menu();
            break;
        case 8:
            sort_hll();
            display_hll();
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

    ll.sort_hll();
    ll2.sort_hll();

    LinkedList merged;
    Node* head = new (class Node);
    if(head != nullptr) {
        head->data = ll.get_node_count() + ll2.get_node_count();
        merged.set_head_element(head);
        merged.set_first_node(sort_linked_lists(ll.get_first_node(),ll2.get_first_node()));
        merged.display_hll();

        if(merged.get_first_node() != nullptr)
            merged.delete_hll();
    }
    else {
        if(ll.get_first_node() != nullptr) 
            ll.delete_hll();
        if(ll2.get_first_node() != nullptr)
            ll2.delete_hll();
    }
}
