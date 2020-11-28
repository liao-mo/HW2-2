#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

class Node
{
public:
    Node() {
        k1 = -1;
        k2 = -1;
        number = 0;
        left = middle = right = NULL;
    }
    Node(int val) {
        k1 = val;
        k2 = -1;
        number = 1;
        left = middle = right = NULL;
    }
    int k1, k2;                    
    Node* left;
    Node* middle;             
    Node* right;
    int number;  //number of keys in this node
};

class SplitData {
public:
    SplitData() {
        mid_value = -1;
        middle_child = NULL;
    }
    SplitData(Node* n) {
        mid_value = -1;
        middle_child = n;
    }
    SplitData(int mid, Node* n) {
        mid_value = mid;
        middle_child = n;
    }
    int mid_value;
    Node* middle_child;
};




class two3Tree {
public:
    two3Tree() {
        root = NULL;
    }
    Node* root;

    //wrapper function
    void insert(int val) {
        //the first insertion
        if (root == NULL) {
            root = new Node(val);
        }
        else {
            SplitData split_data = insert(val, root);
            //if the split reaches to the root
            if (split_data.middle_child != NULL) {
                Node* newRoot = new Node(split_data.mid_value);
                newRoot->left = root;
                newRoot->middle = split_data.middle_child;
                root = newRoot;
            }
        }
    }

    //inner insert function
    SplitData insert(int val, Node* n) {
        //if n is a leaf node
        if (n->left == NULL && n->middle == NULL && n->right == NULL) {
            //if there still have space for it
            if (n->number == 1) {
                if (val <= n->k1) {
                    n->k2 = n->k1;
                    n->k1 = val;
                }
                else {
                    n->k2 = val;
                }
                n->number = 2;
                //done
                return NULL;
            }
            //already two keys in this node
            else {
                //split the node and return the data upward
                SplitData split_data = split(n, NULL, val);
                //let former recursive to process the split_data
                return split_data;
            }
        }
        // n is not a leaf node
        else {
            //n is a 2 node
            if (n->number == 1) {
                if (val <= n->k1) {
                    //try to insert the value into n's left child
                    SplitData split_data = insert(val, n->left);

                    //if need to split
                    if (split_data.middle_child != NULL) {
                        n->k2 = n->k1;
                        n->k1 = split_data.mid_value;
                        n->right = n->middle;
                        n->middle = split_data.middle_child;
                        n->number = 2;
                    }
                }
                else if (val > n->k1) {
                    //try to insert the value into n's middle child
                    SplitData split_data = insert(val, n->middle);

                    //if need to split
                    if (split_data.middle_child != NULL) {
                        n->k2 = split_data.mid_value;
                        n->right = split_data.middle_child;
                        n->number = 2;
                    }
                }
                //done
                return NULL;
            }
            //n is a 3 node
            else {
                SplitData split_data;
                //try to insert the value into n's left child
                if (val <= n->k1) {
                    split_data = insert(val, n->left);
                }
                //try to insert the value into n's middle child
                else if (val <= n->k2) {
                    split_data = insert(val, n->middle);
                }
                //try to insert the value into n's right child
                else {
                    split_data = insert(val, n->right);
                }

                //if need to split
                if (split_data.middle_child != NULL) {
                    //push the split_data upward
                    split_data = split(n, split_data.middle_child, split_data.mid_value);
                    return split_data;
                }

                //done
                return NULL;
            }
        }
    }



    //split the current node and return the split data
    SplitData split(Node* current, Node* child, int val) {
        int mid_val;
        Node* middle_child = new Node; //this node is to be placed to the middle of the new parent node
                                //the current node is to be placed to the left of the new parent node
        middle_child->number = 1;

        // val/current->k1/current->k2
        if (val <= current->k1) {
            mid_val = current->k1; //parent
            middle_child->k1 = current->k2; //right
            current->k1 = val; //left

            //if current node is non-leaf node
            if (current->left != NULL) {
                //re-arrange current node and middle-child node's children
                middle_child->left = current->middle;
                middle_child->middle = current->right;
                current->middle = child;
            }
        }
        // current->k1/val/current->k2
        else if (val <= current->k2) {
            //don't need to modify current's k1 : left
            mid_val = val; // parent
            middle_child->k1 = current->k2; //right

            //if current node is non-leaf node
            if (current->left != NULL) {
                //re-arrange and middle-child node's children
                middle_child->left = child;
                middle_child->middle = current->right;
            }
        }
        // current->k1/current->k2/val
        else {
            //don't need to modify current's k1 : left
            mid_val = current->k2;
            middle_child->k1 = val;

            //if current node is non-leaf node
            if (current->left != NULL) {
                //re-arrange and middle-child node's children
                middle_child->left = current->right;
                middle_child->middle = child;
            }
        }

        //reset current node's data
        current->right = NULL;
        current->k2 = -1;
        current->number = 1;

        SplitData s(mid_val, middle_child);
        return s;
    }

    //level order display
    void display() {
        queue<Node*> q_current;
        queue<Node*> q_next;
        q_current.push(root);
        bool newLevel = true;

        while (!q_current.empty()) {
            //iterate current level
            newLevel = true;
            while (!q_current.empty()) {
                Node* current_node = q_current.front();
                q_current.pop();
                if (newLevel) {
                    newLevel = false;
                }
                else {
                    cout << " / ";
                }

                //current node has 1 key
                if (current_node->number == 1) {
                    cout << current_node->k1;
                }
                //current node has 2 keys
                else {
                    cout << current_node->k1;
                    cout << " " << current_node->k2;
                }

                if (current_node->left != NULL) {
                    q_next.push(current_node->left);
                }
                if (current_node->middle != NULL) {
                    q_next.push(current_node->middle);
                }
                if (current_node->right != NULL) {
                    q_next.push(current_node->right);
                }
            }
            cout << endl;

            //assign the next queue to current queue
            q_current = q_next;
            //clear the next queue
            std::queue<Node*> empty;
            std::swap(q_next, empty);
        }


    }
};

int main() {
    two3Tree tree;
    int data;
    while (cin >> data) {
        tree.insert(data);
        //cout << "\n\n----------" << endl;
        //tree.display();
        //cout << "----------" << endl;
    }
    tree.display();
	return 0;
}