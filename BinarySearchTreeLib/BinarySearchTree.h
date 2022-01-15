#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>
#include <iostream>

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
		Node* q;

		if (n == nullptr)
			return nullptr;

		if (n->left == nullptr && n->right == nullptr)
		{
			if (n == root)
				root = nullptr;
			delete n;
			return nullptr;
		}

		if (k < n->key)
			n->left = remove(n->left, k);
		else if (k > n->key)
			n->right = remove(n->right, k);
		else
		{
			if (height(n->left) > height(n->right))
			{
				q = InPre(n->left);
				n->key = q->key;
				n->left = remove(n->left, q->key);
			}
			else
			{
				q = InSucc(n->right);
				n->key = q->key;
				n->right = remove(n->right, q->key);
			}
		}
		return n;
	};

	template<typename K, typename I>
	void _find(Node* n, const K& k) const
	{
		if (!n)
			throw std::domain_error("critical exception");
		if (n->key == k)
			return n;
		if (n->key < k)
			return _find<K, I>(n->right, k);
		else if (n->key > k)
			return _find<K, I>(n->left, k);
		else
			throw std::domain_error("element not found");
	};

	unsigned int height(Node* n)
	{
		int x;
		int y;
		if (n == nullptr)
		{
			return 0;
		}
		x = height(n->left);
		y = height(n->right);
		return x > y ? x + 1 : y + 1;
	};

	Node* InPre(Node* n)
	{
		while (n && n->right != nullptr)
			n = n->right;
		return n;
	};

	Node* InSucc(Node* n)
	{
		while (n && n->left != nullptr)
			n = n->left;
		return n;
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

	std::string toString(Node* n)
	{
		std::string result = "";
		if (n == nullptr)
			return "";
		result += toString(n->left);
		result += toString(n->right);
		return result;
	}
public:

	BinarySearchTree()
	{
		root = nullptr;
	};

	~BinarySearchTree()
	{
		clean(root);
	};

	size_t size() const
	{
		return height(root);
	}

	void insert(KeyType const& key, ValueType const& value)
	{
		root = insert(root, key, value);
	};
	
	void remove(KeyType const& key)
	{
		root = remove(root, key);
	};

	ValueType* find(KeyType const& key)
	{
		return _find<const KeyType, ValueType>(root, key)->value;
	};

	std::string toString() const
	{
		return std::to_string(root->key) + std::to_string(root->value);
	};
	
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
		std::cout << "[" << n->key << "|" << n->value << "] ";
		print(st, n->right);
	};
};

template<typename KeyType, typename ValueType>
std::ostream& operator <<(std::ostream& stream, BinarySearchTree<KeyType, ValueType> const& tree)
{
	tree.print<std::ostream>(stream);
	return stream;
}
