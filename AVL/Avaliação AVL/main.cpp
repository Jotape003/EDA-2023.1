#include <iostream>
#include <algorithm>
using namespace std;

// Definindo a estrutura do nó da árvore AVL
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
};

// Função para criar um novo nó
Node* createNode(int key) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

// Função para calcular a altura de um nó
int getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Função para calcular o fator de balanceamento de um nó
int getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Função para atualizar a altura de um nó
void updateHeight(Node* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// Função para fazer uma rotação simples à esquerda (LL rotation)
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Função para fazer uma rotação simples à direita (RR rotation)
Node* rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Função para fazer uma rotação dupla esquerda-direita (LR rotation)
Node* rotateLeftRight(Node* x) {
    x->left = rotateLeft(x->left);
    return rotateRight(x);
}

// Função para fazer uma rotação dupla direita-esquerda (RL rotation)
Node* rotateRightLeft(Node* x) {
    x->right = rotateRight(x->right);
    return rotateLeft(x);
}

// Função para inserir um novo nó na árvore AVL (versão iterativa)
Node* insert(Node* root, int key) {
    Node* newNode = createNode(key);
    if (root == nullptr) {
        return newNode;
    }
    
    // Percorrendo a árvore para encontrar a posição correta para inserir o novo nó
    Node* parentNode = nullptr;
    Node* currentNode = root;
    while (currentNode != nullptr) {
        if (key < currentNode->key) {
            parentNode = currentNode;
            currentNode = currentNode->left;
        } else if (key > currentNode->key) {
            parentNode = currentNode;
            currentNode = currentNode->right;
        } else {
            // Chave já existe, não fazemos nada
            return root;
        }
    }
    
    // Inserindo o novo nó na árvore
    if (key < parentNode->key) {
        parentNode->left = newNode;
    } else {
        parentNode->right = newNode;
    }
    
    // Atualizando os fatores de balanceamento e realizando as rotações necessárias
    currentNode = newNode;
    while (currentNode != nullptr) {
        updateHeight(currentNode);
        int bf = getBalanceFactor(currentNode);

        if (bf > 1) {
            if (key < currentNode->left->key) {
                // LL - Rotação simples à direita
                currentNode = rotateRight(currentNode);
            } else {
                // LR - Rotação dupla esquerda-direita
                currentNode = rotateLeftRight(currentNode);
            }
        } else if (bf < -1) {
            if (key > currentNode->right->key) {
                // RR - Rotação simples à esquerda
                currentNode = rotateLeft(currentNode);
            } else {
                // RL - Rotação dupla direita-esquerda
                currentNode = rotateRightLeft(currentNode);
            }
        }
        
        // Atualizando o nó pai
        if (currentNode == root) {
            root = currentNode;
            break;
        } else {
            Node* parent = currentNode;
            currentNode = (currentNode == parentNode->left) ? parentNode->right : parentNode->left;
            parentNode = parent;
        }
    }
    
    return root;
}

// Função para imprimir a árvore AVL (em ordem)
void printTree(Node* node) {
    if (node == nullptr) {
    return;
    }
    printTree(node->left);
    cout << node->key << " ";
    printTree(node->right);
}

void bshow(Node *node, std::string heranca) {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

// Função para desalocar a memória da árvore AVL
void deleteTree(Node* node) {
    if (node == nullptr) {
    return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Função principal
int main() {
system ("chcp 65001 > nul");
Node* root = nullptr;
//Inserindo os nós na árvore AVL
// root = insert(root, 10);
// root = insert(root, 5);
// root = insert(root, 7);
// root = insert(root, 20);
// root = insert(root, 18);
// root = insert(root, 25);
for(int i = 1; i <= 20; i++) {
    root = insert(root, i);
}

// Imprimindo a árvore AVL
cout << "Árvore AVL em ordem: ";
printTree(root);
cout << endl;
bshow(root, "");

// Desalocando a memória da árvore AVL
deleteTree(root);

return 0;
}