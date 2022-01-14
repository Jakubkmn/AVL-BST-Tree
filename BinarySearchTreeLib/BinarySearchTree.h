#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>

template<typename KeyType, typename ValueType>
class BinarySearchTree
{
private:
	struct Node
	{
		KeyType key;
		ValueType value;
		Node* left;
		Node* right;

		Node(const KeyType& k, const ValueType& v) : key(k), value(v)
		{
			left = nullptr;
			right = nullptr;
		};

	};
	Node* root;

	int s = 0;

	Node* insert(Node* n, const KeyType& k, const ValueType& v)
	{
		if (n == nullptr)
		{
			s++;
			return new Node(k ,v);
		}

		if (k < n->key)
			n->left = insert(n->left, k, v);
		else
			n->right = insert(n->right, k, v);
		return n;
	};

	Node* remove(Node* n, const KeyType& k)
	{
		if (!n)
			throw std::domain_error("critical exception");
		if (k < n->key)
			n->left = remove(n->left, k);
		else if (k > n->key)
			n->right = remove(n->right, k);
		else
		{
			Node* lnode = n->left;
			Node* rnode = n->right;
			delete n;
		}
	};

	Node* find(Node* n, const KeyType& k)
	{
		if (!n)
			throw std::domain_error("critical exception");
		if (n->key == k)
			return n;
		if (n->key < k)
			return find(n->right, k);
		else if (n->key > k)
			return find(n->left, k);
		else
			throw std::domain_error("element not found");
	};

	void clean(Node* n)
	{
		if (n)
		{
			clean(n->left);
			clean(n->right);
			delete n;
			s = 0;
		}
	};
public:

	BinarySearchTree()
	{
		root = nullptr;
	};

	~BinarySearchTree()
	{
		clean(root);
	};

	size_t size() const;

	void insert(KeyType const& key, ValueType const& value)
	{
		root = insert(root, key, value);
	};
	
	void remove(KeyType const& key)
	{
		//try
	
			root = remove(root, key);
		/*catch (element_not_found)
		{
			throw element_not_found();
		}*/
	};

	ValueType* find(KeyType const& key)
	{
		  Node* t = find(this->root, key);
		  return t->value;
	};

	std::string toString() const;

	template<typename StreamType>
	void print(StreamType& stream) const
	{
		print(stream, root);
	};

	template<typename StreamType>
	void print(StreamType& st, Node* n) const
	{
		if (!n) return;
		print(st, n->left);
		cout << "[" << n->key << "|" << n->value << "] ";
		print(st, n->right);
	};
};

template<typename KeyType, typename ValueType>
std::ostream& operator <<(std::ostream& stream, BinarySearchTree<KeyType, ValueType> const& tree)
{
	tree.print<std::ostream>(stream);
	return stream;
}
