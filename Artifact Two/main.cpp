#include <iostream>
#include <queue>
#include <unordered_map>

/*
    Below is a demostration of the implementation and manipulation of an AVL tree

        - Time complexities of AVL Trees for searching, inserting, deleting, and rotating: O(log*n) 
*/

using namespace std;

// Creating a node
struct node {
    struct node* left;
    int data;
    int height;
    struct node* right;

};

// Creating the AVL tree
class AVL {
private:

public:
    // Giving a node to the AVL tree, and pointing it to NULL when the tree is created
    struct node* root;
    AVL() {
        this->root = NULL;

    }

    // Retreiving the height from the AVL tree
    int calheight(struct node* p) {

        if (p->left && p->right) {
            if (p->left->height < p->right->height)
                return p->right->height + 1;
            else return  p->left->height + 1;
        }
        else if (p->left && p->right == NULL) {
            return p->left->height + 1;
        }
        else if (p->left == NULL && p->right) {
            return p->right->height + 1;
        }
        return 0;

    }

    // Retreiving the balance factor of the AVL tree
    int bf(struct node* n) {
        if (n->left && n->right) {
            return n->left->height - n->right->height;
        }
        else if (n->left && n->right == NULL) {
            return n->left->height;
        }
        else if (n->left == NULL && n->right) {
            return -n->right->height;
        }
    }

    // Implementing a Left-Left rotation
    struct node* llrotation(struct node* n) {
        struct node* p;
        struct node* tp;
        p = n;
        tp = p->left;

        p->left = tp->right;
        tp->right = p;

        return tp;
    }

    // Implementing a Right-Right rotation
    struct node* rrrotation(struct node* n) {
        struct node* p;
        struct node* tp;
        p = n;
        tp = p->right;

        p->right = tp->left;
        tp->left = p;

        return tp;
    }

    // Implementing a Right-Light rotation
    struct node* rlrotation(struct node* n) {
        struct node* p;
        struct node* tp;
        struct node* tp2;
        p = n;
        tp = p->right;
        tp2 = p->right->left;

        p->right = tp2->left;
        tp->left = tp2->right;
        tp2->left = p;
        tp2->right = tp;

        return tp2;
    }

    // Implementing a Left-Right rotation
    struct node* lrrotation(struct node* n) {
        struct node* p;
        struct node* tp;
        struct node* tp2;
        p = n;
        tp = p->left;
        tp2 = p->left->right;

        p->left = tp2->right;
        tp->right = tp2->left;
        tp2->right = p;
        tp2->left = tp;

        return tp2;
    }

    // Inserting into the tree
    struct node* insert(struct node* r, int data) {

        if (r == NULL) {
            struct node* n;
            n = new struct node;
            n->data = data;
            r = n;
            r->left = r->right = NULL;
            r->height = 1;
            return r;
        }
        else {
            if (data < r->data)
                r->left = insert(r->left, data);
            else
                r->right = insert(r->right, data);
        }

        // Passing the height value onto the node 'r'
        r->height = calheight(r);

        // Else-If ladders determining which rotation to do based on the balance factor of the node
        if (bf(r) == 2 && bf(r->left) == 1) {
            r = llrotation(r);
        }
        else if (bf(r) == -2 && bf(r->right) == -1) {
            r = rrrotation(r);
        }
        else if (bf(r) == -2 && bf(r->right) == 1) {
            r = rlrotation(r);
        }
        else if (bf(r) == 2 && bf(r->left) == -1) {
            r = lrrotation(r);
        }

        return r;

    }

    // Returns a message indicating that the AVL is empty
    void levelorder_newline() {
        if (this->root == NULL) {
            cout << "\n" << "Empty tree" << "\n";
            return;
        }
        levelorder_newline(this->root);
    }

    // Implements a Queue to push and pop nodes while the AVL tree is being traversed
    void levelorder_newline(struct node* v) {
        queue <struct node*> q;
        struct node* cur;
        q.push(v);
        q.push(NULL);

        while (!q.empty()) {
            cur = q.front();
            q.pop();
            if (cur == NULL && q.size() != 0) {
                cout << "\n";

                q.push(NULL);
                continue;
            }
            if (cur != NULL) {
                cout << " " << cur->data;

                if (cur->left != NULL) {
                    q.push(cur->left);
                }
                if (cur->right != NULL) {
                    q.push(cur->right);
                }
            }


        }
    }

    // Deletes a node
    struct node* deleteNode(struct node* p, int data) {

        if (p->left == NULL && p->right == NULL) {
            if (p == this->root)
                this->root = NULL;
            delete p;
            return NULL;
        }

        struct node* t;
        struct node* q;
        if (p->data < data) {
            p->right = deleteNode(p->right, data);
        }
        else if (p->data > data) {
            p->left = deleteNode(p->left, data);
        }
        else {
            if (p->left != NULL) {
                q = inpre(p->left);
                p->data = q->data;
                p->left = deleteNode(p->left, q->data);
            }
            else {
                q = insuc(p->right);
                p->data = q->data;
                p->right = deleteNode(p->right, q->data);
            }
        }

        if (bf(p) == 2 && bf(p->left) == 1) { p = llrotation(p); }
        else if (bf(p) == 2 && bf(p->left) == -1) { p = lrrotation(p); }
        else if (bf(p) == 2 && bf(p->left) == 0) { p = llrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == -1) { p = rrrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == 1) { p = rlrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == 0) { p = llrotation(p); }


        return p;
    }

    struct node* inpre(struct node* p) {
        while (p->right != NULL)
            p = p->right;
        return p;
    }

    struct node* insuc(struct node* p) {
        while (p->left != NULL)
            p = p->left;

        return p;
    }

    ~AVL() {

    }
};

// One and only main function
int main() {

    AVL b;
    int c, x;


    // A do-while loop take in user-input 
    do {
        cout << "\n1.Display levelorder on newline";
        cout << "\n2.Insert";
        cout << "\n3.Delete\n";
        cout << "\n0.Exit\n";
        cout << "\nChoice: ";

        cin >> c;

        switch (c)
        {
        case 1:
            b.levelorder_newline();
            // to print the tree in level order
            break;

        case 2:
            cout << "\nEnter no. ";
            cin >> x;
            b.root = b.insert(b.root, x);
            break;

        case 3:
            cout << "\nWhat to delete? ";
            cin >> x;
            b.root = b.deleteNode(b.root, x);
            break;

        case 0:
            break;
        }

    } while (c != 0);

}