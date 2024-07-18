#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    void insert(int value);
    void deleteNode(int value);
    Node* deleteNodeHelper(Node* node, int value);
    Node* search(int value);
    void inorderTraversal(Node* node);
    void preorderTraversal(Node* node);
    void postorderTraversal(Node* node);
    Node* minValueNode(Node* node);
};

void BST::insert(int value) {
    Node* newNode = new Node(value);
    if (root == nullptr) {
        root = newNode;
    } else {
        Node* current = root;
        while (true) {
            if (value < current->data) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }
        }
    }
}

void BST::deleteNode(int value) {
    root = deleteNodeHelper(root, value);
}

Node* BST::deleteNodeHelper(Node* node, int value) {
    if (node == nullptr) {
        return node;
    }

    if (value < node->data) {
        node->left = deleteNodeHelper(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNodeHelper(node->right, value);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = deleteNodeHelper(node->right, temp->data);
    }

    return node;
}

Node* BST::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* BST::search(int value) {
    Node* current = root;
    while (current != nullptr) {
        if (value == current->data) {
            return current;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

void BST::inorderTraversal(Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

void BST::preorderTraversal(Node* node) {
    if (node != nullptr) {
        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

void BST::postorderTraversal(Node* node) {
    if (node != nullptr) {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << " ";
    }
}

class Visualizer {
public:
    BST bst;

    void visualize();
    void visualizeNode(Node* node, int level);
};

void Visualizer::visualize() {
    cout << "\n\n\t\t\tBinary Search Tree:" << endl;
    if (bst.root == nullptr) {
        cout << "\t\t\tNot available" << endl;
    } else {
        visualizeNode(bst.root, 0);
    }
    cout << endl;
}

void Visualizer::visualizeNode(Node* node, int level) {
    if (node != nullptr) {
        for (int i = 0; i < level; i++) {
            cout << "\t";
        }
        cout << node->data << endl;
        visualizeNode(node->left, level + 1);
        visualizeNode(node->right, level + 1);
    }
}

int main() {
    Visualizer visualizer;

    while (true) {
        cout << "\n\n\t\t\tBST Visualizer" << endl;
        cout << "\t\t\t-----------------" << endl;
        cout << "\t\t1. Insert node" << endl;
        cout << "\t\t2. Delete node" << endl;
        cout << "\t\t3. Search for node" << endl;
        cout << "\t\t4. Visualize BST" << endl;
        cout << "\t\t5. Inorder Traversal" << endl;
        cout << "\t\t6. Preorder Traversal" << endl;
        cout << "\t\t7. Postorder Traversal" << endl;
        cout << "\t\t8. Exit" << endl << endl;
        visualizer.visualize();
        cout << "\nEnter your choice: ";
        int choice; cin >> choice;
        int value;
        Node* result;
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                visualizer.bst.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                visualizer.bst.deleteNode(value);
                break;
            case 3:
                cout << "Enter value to search for: ";
                cin >> value;
                result = visualizer.bst.search(value);
                if (result != nullptr) {
                    cout << "Value found in BST." << endl;
                } else {
                    cout << "Value not found in BST." << endl;
                }
                break;
            case 4:
                visualizer.visualize();
                break;
            case 5:
                cout << "Inorder Traversal: ";
                visualizer.bst.inorderTraversal(visualizer.bst.root);
                cout << endl;
                break;
            case 6:
                cout << "Preorder Traversal: ";
                visualizer.bst.preorderTraversal(visualizer.bst.root);
                cout << endl;
                break;
            case 7:
                cout << "Postorder Traversal: ";
                visualizer.bst.postorderTraversal(visualizer.bst.root);
                cout << endl;
                break;
            case 8:
                return 0;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }

    return 0;
}
