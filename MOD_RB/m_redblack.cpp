#include "m_redblack.h"
using namespace std;

void mod_RBTree::leftRotate(Node *x)
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

void mod_RBTree::rightRotate(Node *x)
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

void mod_RBTree::swapColors(Node *x1, Node *x2)
{
    COLOR temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
}

void mod_RBTree::swapValues(Node *u, Node *v)
{
    int temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
}

// fix red red at given node
void mod_RBTree::fixRedRedRed(Node *x) //modified to fix red red red instead ead ead 
{
    // if x is root color it black and return
    //NOTE: Even though this relaxation allows for a red head node, my algorithm requires that the initial node be black
    if (x == root)
    {
        //x->color = BLACK;
        return;
    }

    /*
        CASES: (hold on... theres a lot of them)
            1: insert red node with red parent, red grand parent, and black great grand parent
                a: straight left
                b: zig-zag left
                c: straight right
                d: zig-zag left
            2: insert red node with red parent, red grandparent, red uncle, black great grand parent, and red great uncle
                NOTE: these zig zags are at the newnode/ parent level
                a: straight left
                b: zig zag left
                c: straight right
                d: zig zag right
            3: zig zag at the grandparent parent level (could call this 2e-2f... but thats a lot of case 2)
                NOTE: these zig zags are at the parent grandparent level
                a: grandparent is left
                b: grandparent is right
            4: inset red node with red parent, red grandparent, no greatgrandparent, and a black uncle
                NOTE: this is basically when tree gets out of balance, the out of balanceness is 
                propogated up so theres a triple red at the root and we have to rotate over,
                This means that the tree can be kind of balanced in the long run, but it is possible that it ends unbalanced
    */

    // initialize parent, grandparent, uncle
    Node *parent = x->parent, 
         *grandparent = parent->parent, //get the g pa
         *uncle = x->uncle(), //get the uncle
         *greatGrandparent = (grandparent ? grandparent->parent : nullptr); //if the grandparent is not null, then get the parent and assign it to grandparent

    if(parent->color == RED && 
        (grandparent && grandparent->color == RED)) //three reds in a row -> no good 
    {
        if(greatGrandparent) //a great grandparent exists -> case 1 or 2
        {
            if(uncle && uncle->color == RED) //uncle exists && is red -> case 2
            {
                if((grandparent && grandparent->isOnLeft())
                    && (parent && !parent->isOnLeft())) // grandparent on left and parent on right -> case 3a
                {
                    /*
                        rotate grandparent right
                        color uncle black
                    */
                    rightRotate(grandparent);
                    uncle->color = BLACK;
                }
                else if((grandparent && !grandparent->isOnLeft())
                    && (parent && parent->isOnLeft())) // grandparent on right and parent on left -> case 3b
                {
                    /*
                        Rotate greatgrandparent left
                        color uncle black
                    */
                    leftRotate(greatGrandparent);
                    uncle->color = BLACK;
                }
                else // we are in case 2
                {
                    if(parent && parent->isOnLeft())
                    {
                        if(x->isOnLeft())
                        {
                            /* 
                            left left:
                            rotate greatgrandparent right
                            color parent black
                            */
                            rightRotate(greatGrandparent);
                            parent->color = BLACK;

                        }
                        else //x is on right
                        {
                            /* 
                                left right: 
                                rotate parent left
                                color x black
                                rotate greatgrandparent right
                            */
                            leftRotate(parent);
                            x->color = BLACK;
                            rightRotate(greatGrandparent);
                        }
                        
                    }
                    else //parent is on right
                    {
                        if(x->isOnLeft())
                        {
                            /* 
                                right left
                                rotate parent right
                                color x black
                                rotate greatgrandparent left
                            */
                            rightRotate(parent);
                            x->color = BLACK;
                            leftRotate(greatGrandparent);
                        }
                        else //x is on right
                        {
                            /* 
                                right right 
                                rotate greatgrandparent left
                                color parent black
                            */
                            leftRotate(greatGrandparent);
                            parent->color = BLACK;
                        }
                    }
                }
            }
            else //no red uncle -> case 1
            {
                if(parent && parent->isOnLeft())
                {
                    if(x->isOnLeft())
                    {
                        /* 
                            left left case 
                            rotate grandparent right
                        */
                        rightRotate(grandparent);
                    }
                    else //x is on right
                    {
                        /* 
                            left right case 
                            rotate parent left
                            rotate grandparent right
                        */
                        leftRotate(parent);
                        rightRotate(grandparent);
                    }
                    
                }
                else //parent is on right
                {
                    if(x->isOnLeft())
                    {
                        /* 
                            right left case 
                            rotate parent right
                            rotate grandparent left
                        */
                        rightRotate(parent);
                        leftRotate(grandparent);
                    }
                    else //x is on right
                    {
                        /* 
                            right right case
                            rotate grandparent left
                        */
                        leftRotate(grandparent);
                    }
                }
            }
            
            fixRedRedRed(grandparent); // see if we propogated enough up that we need to roll over the root
        } //if greatgrandparent
        else // no greatgrandparent -> case 4
        {
            if(parent && parent->isOnLeft())
            {
                if(x->isOnLeft())
                {
                    //left left
                    rightRotate(grandparent);
                    grandparent->color = BLACK;
                    uncle->color = RED;
                }
                else
                {
                    //left right
                    leftRotate(parent);
                    rightRotate(grandparent);
                    grandparent->color = BLACK;
                    uncle->color = RED;
                }
                
            }
            else
            {
                if(x->isOnLeft())
                {
                    //right left
                    rightRotate(parent);
                    leftRotate(grandparent);
                    grandparent->color = BLACK;
                    uncle->color = RED;
                }
                else
                {
                    //right right
                    leftRotate(grandparent);
                    grandparent->color = BLACK;
                    uncle->color = RED;
                }
            }
        }
    } //if three reds
} //fix red red

// find node that do not have a left child
// in the subtree of the given node
Node *mod_RBTree::successor(Node *x)
{
    Node *temp = x;

    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}

// prints level order for given node
void mod_RBTree::levelOrder(Node *x)
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
void mod_RBTree::inorder(Node *x)
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
Node *mod_RBTree::search(int n)
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
//TODO: Force the first node to be black
void mod_RBTree::insert(int n)
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
        fixRedRedRed(newNode);
    }
}

// prints inorder of the tree
void mod_RBTree::printInOrder()
{
    cout << "Inorder: " << endl;
    if (root == NULL)
        cout << "Tree is empty" << endl;
    else
        inorder(root);
    cout << endl;
}

// prints level order of the tree
void mod_RBTree::printLevelOrder()
{
    cout << "Level order: " << endl;
    if (root == NULL)
        cout << "Tree is empty" << endl;
    else
        levelOrder(root);
    cout << endl;
}

/*
    do an in order traversal of the graph and update the max height found each time 
    we hit the bottom 
    the max height of the tree is stored maxBlackHeight
*/
void mod_RBTree::getBlackHeights(Node* n, int & maxBlackheight, int & tmpBlackHeight)
{
    if(n == nullptr) {
        tmpBlackHeight > maxBlackheight ? maxBlackheight = tmpBlackHeight : maxBlackheight = maxBlackheight;
        tmpBlackHeight = 0;
        return;
    }
    
    if(n->color == BLACK)
        tmpBlackHeight++;
    
    getBlackHeights(n->left, maxBlackheight, tmpBlackHeight);
    getBlackHeights(n->right, maxBlackheight, tmpBlackHeight);
}

/*
    Super elegant algorithm from this thread:
    https://stackoverflow.com/questions/20037137/how-to-calculate-the-height-of-a-red-black-tree
*/
int mod_RBTree::getHeights(Node* n)
{
    if(n == nullptr) 
        return -1;
    return max(getHeights(n->left), getHeights(n->right)) + 1;
}