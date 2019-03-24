#include "redblack.h"
using namespace std;

// left rotates the given node
void RBTree::leftRotate(Node *x)
{
    // new parent will be node's right child
    Node *nParent = x->right;

    // update root if current node is root
    if (x == root)
        root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's left element
    x->right = nParent->left;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left != NULL)
        nParent->left->parent = x;

    // connect new parent with x
    nParent->left = x;
}

void RBTree::rightRotate(Node *x)
{
    // new parent will be node's left child
    Node *nParent = x->left;

    // update root if current node is root
    if (x == root)
        root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's right element
    x->left = nParent->right;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right != NULL)
        nParent->right->parent = x;

    // connect new parent with x
    nParent->right = x;
}

void RBTree::swapColors(Node *x1, Node *x2)
{
    COLOR temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
}

void RBTree::swapValues(Node *u, Node *v)
{
    int temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
}

// fix red red at given node
void RBTree::fixRedRed(Node *x)
{
    // if x is root color it black and return
    if (x == root)
    {
        x->color = BLACK;
        return;
    }

    // initialize parent, grandparent, uncle
    Node *parent = x->parent, *grandparent = parent->parent,
         *uncle = x->uncle();

    if (parent->color != BLACK)
    {
        if (uncle != NULL && uncle->color == RED)
        {
            // uncle red, perform recoloring and recurse
            parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            fixRedRed(grandparent);
        }
        else
        {
            // Else perform LR, LL, RL, RR
            if (parent->isOnLeft())
            {
                if (x->isOnLeft())
                {
                    // for left right
                    swapColors(parent, grandparent);
                }
                else
                {
                    leftRotate(parent);
                    swapColors(x, grandparent);
                }
                // for left left and left right
                rightRotate(grandparent);
            }
            else
            {
                if (x->isOnLeft())
                {
                    // for right left
                    rightRotate(parent);
                    swapColors(x, grandparent);
                }
                else
                {
                    swapColors(parent, grandparent);
                }

                // for right right and right left
                leftRotate(grandparent);
            }
        }
    }
}

// find node that do not have a left child
// in the subtree of the given node
Node * RBTree::successor(Node *x)
{
    Node *temp = x;

    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}

// prints level order for given node
void RBTree::levelOrder(Node *x)
{
    if (x == NULL)
        // return if node is null
        return;

    // queue for level order
    queue<Node *> q;
    Node *curr;

    // push x
    q.push(x);

    while (!q.empty())
    {
        // while q is not empty
        // dequeue
        curr = q.front();
        q.pop();

        // print node value
        cout << curr->val << " ";

        // push children to queue
        if (curr->left != NULL)
            q.push(curr->left);
        if (curr->right != NULL)
            q.push(curr->right);
    }
}

// prints inorder recursively
void RBTree::inorder(Node *x)
{
    if (x == NULL)
        return;
    inorder(x->left);
    cout << x->val << " ";
    inorder(x->right);
}

// searches for given value
// if found returns the node (used for delete)
// else returns the last node while traversing (used in insert)
Node * RBTree::search(int n)
{
    Node *temp = root;
    while (temp != NULL)
    {
        if (n < temp->val)
        {
            if (temp->left == NULL)
                break;
            else
                temp = temp->left;
        }
        else if (n == temp->val)
        {
            break;
        }
        else
        {
            if (temp->right == NULL)
                break;
            else
                temp = temp->right;
        }
    }

    return temp;
}

// inserts the given value to tree
void RBTree::insert(int n)
{
    Node *newNode = new Node(n);
    if (root == NULL)
    {
        // when root is null
        // simply insert value at root
        newNode->color = BLACK;
        root = newNode;
    }
    else
    {
        Node *temp = search(n);

        if (temp->val == n)
        {
            // return if value already exists
            return;
        }

        // if value is not found, search returns the node
        // where the value is to be inserted

        // connect new node to correct node
        newNode->parent = temp;

        if (n < temp->val)
            temp->left = newNode;
        else
            temp->right = newNode;

        // fix red red voilaton if exists
        fixRedRed(newNode);
    }
}

// prints inorder of the tree
void RBTree::printInOrder()
{
    cout << "Inorder: " << endl;
    if (root == NULL)
        cout << "Tree is empty" << endl;
    else
        inorder(root);
    cout << endl;
}

// prints level order of the tree
void RBTree::printLevelOrder()
{
    cout << "Level order: " << endl;
    if (root == NULL)
        cout << "Tree is empty" << endl;
    else
        levelOrder(root);
    cout << endl;
}