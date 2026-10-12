#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* root;
    
    // Insert a value into BST
    TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }
        
        if (val < node->val) {
            node->left = insert(node->left, val);
        } else {
            node->right = insert(node->right, val);
        }
        
        return node;
    }
    
    // Find kth largest using reverse inorder traversal
    int kthLargestHelper(TreeNode* node, int k, int& count) {
        if (node == nullptr || count >= k) {
            return -1;
        }
        
        // Traverse right subtree first (larger values)
        int rightResult = kthLargestHelper(node->right, k, count);
        if (rightResult != -1) {
            return rightResult;
        }
        
        // Visit current node
        count++;
        if (count == k) {
            return node->val;
        }
        
        // Traverse left subtree (smaller values)
        return kthLargestHelper(node->left, k, count);
    }
    
public:
    Solution() : root(nullptr) {}
    
    // Build BST from level-order array
    void buildBST(int values[], int n) {
        for (int i = 0; i < n; i++) {
            root = insert(root, values[i]);
        }
    }
    
    // Find kth largest element
    int findKthLargest(int k) {
        int count = 0;
        return kthLargestHelper(root, k, count);
    }
    
    // Clean up memory
    void cleanup(TreeNode* node) {
        if (node == nullptr) return;
        cleanup(node->left);
        cleanup(node->right);
        delete node;
    }
    
    ~Solution() {
        cleanup(root);
    }
};

int main() {
    int values[7];
    int k;
    
    // Read 7 BST node values
    for (int i = 0; i < 7; i++) {
        cin >> values[i];
    }
    
    // Read k (the kth largest to find)
    cin >> k;
    
    Solution solution;
    solution.buildBST(values, 7);
    
    int result = solution.findKthLargest(k);
    cout << result << endl;
    
    return 0;
}