#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

template <typename T>
class BST
{
private:
	class Node
	{
	public:
		Node* Left;
		Node* Right;
		T data;
	
		Node(T value) {
			Left = nullptr;
			Right = nullptr;
			data = value;
		}
	};
	Node* Root;
public:
	BST()
	{
		Root = nullptr;
	}
	void InsertInBST(T data)
	{
		Root = Insert(Root, data);
	}

	Node* Insert(Node* root, T data)
	{
		if (root == nullptr)
			return new Node(data);

		if (data < root->data)
			root->Left = Insert(root->Left, data);
		else if (data > root->data)
			root->Right = Insert(root->Right, data);

		return root;
	}

	bool SearchInBST(T data)
	{
		return Search(Root, data);
	}

	bool Search(Node* root, T data)
	{
		if (root == nullptr)
			return false;

		if (data == root->data)
			return true;

		if (data < root->data)
			return Search(root->Left, data);
		else
			return Search(root->Right, data);
	}

	void RecursivePrinting()
	{
		RecursivePrint(Root);
	}

	void RecursivePrint(Node* root)
	{
		if (root != nullptr)
		{
			RecursivePrint(root->Left);
			cout << root->data << " ";
			RecursivePrint(root->Right);
		}
	}

	void Start()
	{
		srand(time(0));
		for (int i = 0; i < 10; ++i)
		{
			int randomValue = rand() % 100;
			InsertInBST(randomValue);
		}
	}

	void End()
	{
		RecursivePrinting();
		cout << endl;
	}
	bool areIdentical(Node* root1, Node* root2) {
		if (root1 == nullptr && root2 == nullptr)
			return true;

		if (root1 == nullptr || root2 == nullptr)
			return false;

		return (root1->data == root2->data) &&
			areIdentical(root1->Left, root2->Left) &&
			areIdentical(root1->Right, root2->Right);
	}

	bool areIdentical(BST<T>& otherTree) {
		return areIdentical(Root, otherTree.Root);
	}
	int countEvenNumbers(Node* current) {
		if (current == nullptr)
			return 0;

		int count = 0;
		if (current->data % 2 == 0)
			count++;

		count += countEvenNumbers(current->Left);  
		count += countEvenNumbers(current->Right);

	}
	int countEvenNumbers() {
		return countEvenNumbers(Root);
	}

	int calculateHeight(Node* current) {
		if (current == nullptr)
			return 0;

		int leftHeight = calculateHeight(current->Left);
		int rightHeight = calculateHeight(current->Right);

		return max(leftHeight, rightHeight) + 1;
	}


	int calculateHeight() {
		return calculateHeight(Root);
	}

	bool isValidBST(Node* current, T minVal, T maxVal) {
		if (current == nullptr)
			return true;

		if (current->data <= minVal || current->data >= maxVal)
			return false;

		return isValidBST(current->Left, minVal, current->data) &&
			isValidBST(current->Right, current->data, maxVal);
	}


	bool isValidBST() {
		return isValidBST(Root, numeric_limits<T>::min(), numeric_limits<T>::max());
	}

	void sortArrayToBST(T arr[], int start, int end) {
		if (start > end)
			return;

		int mid = (start + end) / 2;
		InsertInBST(arr[mid]);
		sortArrayToBST(arr, start, mid - 1);
		sortArrayToBST(arr, mid + 1, end);
	}

	void sortArrayToBST(T arr[], int size) {
		sortArrayToBST(arr, 0, size - 1);
	}

	int countInternalNodesWithOneBranch(Node* current) {
		if (current == nullptr || (current->Left == nullptr && current->Right == nullptr))
			return 0;

		if (current->Left == nullptr || current->Right == nullptr)
			return 1;

		return countInternalNodesWithOneBranch(current->Left) +
			countInternalNodesWithOneBranch(current->Right);
	}

	int countInternalNodesWithOneBranch() {
		return countInternalNodesWithOneBranch(Root);
	}

	void outputTree(Node* current, int space) {
		if (current == nullptr)
			return;

		space += 5;

		outputTree(current->Right, space);  

		cout << endl;
		for (int i = 5; i < space; i++)
			cout << " ";
		cout << current->data << "\n";

		outputTree(current->Left, space);
	}

	void outputTree() {
		outputTree(Root, 0);
	}

	int countLeaves(Node* current) {
		if (current == nullptr)
			return 0;

		if (current->Left == nullptr && current->Right == nullptr)
			return 1;

		return countLeaves(current->Left) + countLeaves(current->Right);
	}

	int countLeaves() {
		return countLeaves(Root);
	}

};

int main()
{
	BST<int> myBST;

	myBST.Start();

	cout << "Randomized BST: ";
	myBST.End();

	int searchValue = 42;
	if (myBST.SearchInBST(searchValue))
		cout << "Value " << searchValue << " found in the BST." << endl;
	else
		cout << "Value " << searchValue << " not found in the BST." << endl;


	BST<int> tree1;
	BST<int> tree2;

	tree1.InsertInBST(10);
	tree1.InsertInBST(5);
	tree1.InsertInBST(15);

	tree2.InsertInBST(10);
	tree2.InsertInBST(5);
	tree2.InsertInBST(15);

	if (tree1.areIdentical(tree2))
		cout << "The trees are identical." << endl;
	else
		cout << "The trees are not identical." << endl;

	BST<int> tree;

	tree.InsertInBST(10);
	tree.InsertInBST(5);
	tree.InsertInBST(15);
	tree.InsertInBST(3);
	tree.InsertInBST(7);
	tree.InsertInBST(12);
	tree.InsertInBST(20);

	cout << "Number of even numbers: " << tree.countEvenNumbers() << endl;

	cout << "Tree height: " << tree.calculateHeight() << endl;

	cout << "Is Valid BST? " << (tree.isValidBST() ? "Yes" : "No") << endl;
	
	cout << "Number of internal nodes with exactly 1 branch out: " << tree.countInternalNodesWithOneBranch() << endl;

	cout << "Tree printed vertically:\n";
	tree.outputTree();

	cout << "Number of leaves: " << tree.countLeaves() << endl;

	BST<int> Treee;
	int arr[] = { 15, 10, 20, 8, 12, 18, 25 };
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	cout << "Sorted array using BST: ";
	Treee.sortArrayToBST(arr, arrSize);
	Treee.outputTree();


	return 0;
}


//Question 02
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
//
//class Solution {
//
//private:
//	TreeNode* solve(TreeNode* node, int val)
//	{
//		if (node == NULL)
//		{
//			node = new TreeNode(val);
//			return node;
//		}
//
//		if (val < node->val)
//		{
//			node->left = solve(node->left, val);
//		}
//		else if (val > node->val)
//		{
//			node->right = solve(node->right, val);
//		}
//
//		return node;
//	}
//public:
//	TreeNode* insertIntoBST(TreeNode* root, int val) {
//
//		return solve(root, val);
//	}
//};

//Question 04 (a)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

//class Solution {
//public:
//	vector<int> inorderTraversal(TreeNode* root) {
//		vector<int> ans;
//		if (root == NULL) return ans;
//		vector<int> left = inorderTraversal(root->left);
//		ans.insert(ans.end(), left.begin(), left.end());
//		ans.push_back(root->val);
//		vector<int> right = inorderTraversal(root->right);
//		ans.insert(ans.end(), right.begin(), right.end());
//		return ans;
//	}
//
//};

//Question 04 (b)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

//class Solution {
//public:
//	void solver(TreeNode* root, vector<int>& ans) {
//		if (root == nullptr) {
//			return;
//		}
//		if (root->left) {
//			solver(root->left, ans);
//		}
//		if (root->right) {
//			solver(root->right, ans);
//		}
//		ans.push_back(root->val);
//	}
//	vector<int> postorderTraversal(TreeNode* root) {
//		vector<int> ans;
//		solver(root, ans);
//		return ans;
//	}
//};

//Question 04 (c)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

//class Solution {
//public:
//	void preorder(TreeNode* root, vector<int>& ans) {
//		if (root == nullptr)return;
//		ans.push_back(root->val);
//		preorder(root->left, ans);
//		preorder(root->right, ans);
//	}
//	vector<int> preorderTraversal(TreeNode* root) {
//		vector<int> ans;
//		preorder(root, ans);
//		return ans;
//	}
//};

//Question 05
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

//class Solution {
//public:
//	vector<vector<int>> levelOrder(TreeNode* root) {
//		vector<vector<int>>ans;
//		if (root == nullptr)return ans;
//		queue<TreeNode*>q;
//		q.push(root);
//		while (!q.empty()) {
//			int s = q.size();
//			vector<int>v;
//			for (int i = 0; i < s; i++) {
//				TreeNode* node = q.front();
//				q.pop();
//				if (node->left != nullptr)q.push(node->left);
//				if (node->right != nullptr)q.push(node->right);
//				v.push_back(node->val);
//			}
//			ans.push_back(v);
//		}
//		return ans;
//	}
//};