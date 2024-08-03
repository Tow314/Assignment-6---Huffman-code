#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

// Node structure for the Huffman tree
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char character, int frequency) {
        this->character = character;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

// Comparator for priority queue (min-heap) to order nodes by frequency
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

// Function to print Huffman codes in preorder traversal
void printHuffmanCodes(Node* root, std::string code) {
    if (!root) return;

    // If the node is a leaf, print the character and its code
    if (!root->left && !root->right) {
        std::cout << code << " ";
    }

    // Recur for left and right children
    printHuffmanCodes(root->left, code + "0");
    printHuffmanCodes(root->right, code + "1");
}

// Function to build the Huffman tree and print codes
void buildHuffmanTree(const std::string& characters, const std::vector<int>& frequencies) {
    // Priority queue to store nodes of the Huffman tree
    std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;

    // Create a leaf node for each character and add to the priority queue
    for (size_t i = 0; i < characters.size(); ++i) {
        minHeap.push(new Node(characters[i], frequencies[i]));
    }

    // Iterate until the heap contains only one node (the root)
    while (minHeap.size() != 1) {
        // Extract the two nodes with the minimum frequency
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with a frequency equal to the sum of the two nodes
        int sum = left->frequency + right->frequency;
        Node* top = new Node('\0', sum);
        top->left = left;
        top->right = right;

        // Add the new node to the priority queue
        minHeap.push(top);
    }

    // The remaining node is the root of the Huffman tree
    Node* root = minHeap.top();

    // Print Huffman codes using preorder traversal
    printHuffmanCodes(root, "");
    std::cout << std::endl;
}

int main() {
    // Input characters and their frequencies
    std::string S = "abcdef";
    std::vector<int> f = { 5, 9, 12, 13, 16, 45 };

    // Build Huffman tree and print the codes
    buildHuffmanTree(S, f);

    return 0;
}