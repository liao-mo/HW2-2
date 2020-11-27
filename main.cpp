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


class two3Tree {
public:
    two3Tree() {
        root = NULL;
    }
    Node* root;

    Node* insert(int val, Node* n, Node* parent) {
        //if there still have space for it
        if (n->number == 1) {
            if (val <= n->k1) {
                n->k2 = n->k1;
                n->k1 = val;
            }
            else {
                n->k2 = val;
            }
            return n;
        }
        //already two keys in this node
        else {
            //if current node is the root
            if (n == parent) {
                Node* newParent = new Node;
                Node* newLeft = new Node;
                Node* newRight = new Node;

                //if the value is smaller than k1
                if (val <= n->k1) {
                    newParent->k1 = n->k1;
                    newParent->number = 1;
                    
                }
                //if the value is larger than k2
                else if (val >= n->k2) {

                }
            }
            else {

            }
        }



        return 0;
    }

    void insert(int val) {
        //the first insertion
        if (root == NULL) {
            root = new Node(val);
        }
        else {
            Node* parent = root;
            root = insert(val, root, parent);
        }
    }
    void display() {

    }
};






int main() {
    two3Tree tree;
    int data;
    while (cin >> data) {
        tree.insert(data);
    }
    tree.display();
	return 0;
}