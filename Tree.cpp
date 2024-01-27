#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node()
    {
        left = right = NULL;
    }
    Node(int key) : data(key)
    {
        left = right = NULL;
    }
};

// traversals
void preOrder(Node *node)
{
    if (nullptr == node)
    {
        return;
    }
    else
    {
        cout << node->data << " ";
        preOrder(node->left);  // left-sub tree
        preOrder(node->right); // right-sub tree
    }
}
void inOrder(Node* node){
    if(nullptr == node){
        return;
    }
    else{
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
}
void postOrder(Node* node){
    if(nullptr == node){
        return;
    }
    else{
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }
}

bool isBST(Node* node);
bool isBST(Node* root, Node* min, Node* max);
Node* insertBST(Node* root, int val);
Node* searchBST(Node* root, int key);
Node* inOrderSuccessor(Node* root);
Node* deleteBST(Node* root, int key);

// Full Binary Tree
bool isFullBinaryTree(Node* root);
bool checkPerfectTree(Node* root);

// Skewed Binary Tree
bool isSkewedBT(Node* root);

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    preOrder(root);
    cout << endl;
    inOrder(root);
    cout << endl;
    postOrder(root);
    
    // ---- BST ---- //
    Node* root2 = new Node(3);
    root2->left = new Node(2);
    root2->right = new Node(4);
    root2->left->left = new Node(1);
    root2->right->right = new Node(7);
    root2->right->right->right = new Node(9);

    cout << endl <<  (isBST(root2)? "Yes" : "No") <<endl;

    Node* root3 = NULL;
    //root3->data = 20;
    for(int i=0; i<5; i++){
        root3 = insertBST(root3, rand()%100);
    }
    inOrder(root3);

    Node* temp = searchBST(root3, 34);
    if(temp){
        cout << endl << temp->data << endl;
    }

    // -------- Perfect Binary Tree ---------- //
    Node* root4 = new Node(7);
    root4->left = new Node(5);
    root4->right = new Node(6);
    root4->left->left = new Node(8);
    root4->left->right = new Node(1);
    root4->right->left = new Node(3);
    root4->right->right = new Node(9);
    root4->right->right->right = new Node(13);
    root4->right->right->left = new Node(10);
 
    if (checkPerfectTree(root))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;


    // ------ IS skewed ------- //
    Node* root5 =  new Node(1);
    root5->left = new Node(3);
    root5->left->right = new Node(5);
    root5->left->left = new Node(4);
    cout << (isSkewedBT(root5)? "Skewed" : "Not Skewed") << endl;

    return 0;
}

bool isBST(Node* node){
    return isBST(node, NULL, NULL);
}
bool isBST(Node* root, Node* min, Node* max){
    if(nullptr == root){
        return true;
    }
    if(nullptr != min && root->data <= min->data){
        return false;
    }
    if(nullptr != max && root->data >= max->data){
        return false;
    }
    bool l = isBST(root->left, min, root);
    bool r = isBST(root->right, root, max);
    return l and r;
}
Node* insertBST(Node* root, int val){
    if(nullptr == root){
        return new Node(val);
    }
    if(val > root->data){
        root->right = insertBST(root->right, val);
    }
    else{
        root->left = insertBST(root->left, val);
    }
    return root;
}
Node* searchBST(Node* root, int key){
    if(nullptr == root){
        return nullptr;
    }
    if(root->data == key){
        return root;
    }
    if(root->data > key){
        return searchBST(root->left, key);
    }
    else{
        return searchBST(root->right, key);
    }
}
Node* deleteBST(Node* root, int key){
    if(key < root->data){
        root->left = deleteBST(root->left, key);
    }
    else if(key > root->data){
        root->right = deleteBST(root->right, key);
    }
    else{
        if(nullptr == root->left){
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else{
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = inOrderSuccessor(root->right);
        root->data = temp->data;
        root->right = deleteBST(root->right, temp->data);
    }
    return root;
}
Node* inOrderSuccessor(Node* root){
    Node* curr = root;
    while(curr && curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}
bool isFullBinaryTree(Node* root){
    if(nullptr == root){
        return true;
    }
    if(nullptr == root->left && nullptr == root->right){
        return true;
    }
    if(root->left && root->right){
        return isFullBinaryTree(root->left) and isFullBinaryTree(root->right);
    }
    return false;
}
bool checkPerfectTree(Node* root){
    if(nullptr == root){
        return true;
    }
    if(nullptr != root->left && nullptr != root->right){
        return checkPerfectTree(root->left) and checkPerfectTree(root->right);
    }
    if(nullptr == root->left || nullptr == root->right){
        return false;
    }
    return false;
}
bool isSkewedBT(Node* root){
    if(nullptr == root){
        return true;
    }
    if(nullptr == root->left && nullptr == root->right){
        return true;
    }
    if(root->left && root->right){
        return false;
    }
    
    return isSkewedBT(root->left) and isSkewedBT(root->right);
}