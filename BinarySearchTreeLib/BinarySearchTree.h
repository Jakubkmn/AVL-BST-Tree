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

	Node* insert(Node* n, const KeyType& k, const ValueType& v)
	{
		if (n == nullptr)
			return new Node(k ,v);

		if (k == n->key)
		{
			n->value = v;
			return n;
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
		else if (k < n->key)
			n->left = remove(n->left, k);
		else if (k > n->key)
			n->right = remove(n->right, k);
		else if(n->left && n->right)
		{
			q = findmin(n->right);
			n->key = q->key;
			n->right = remove(n->right, n->key);
		}
		else
		{
			q = n;
			if (n->left == nullptr)
				n = n->right;
			else if (n->right == nullptr)
				n = n->left;
			delete q;
		}
		return n;
		
	};

	Node* findmin(Node* n)
	{
		if (n == nullptr)
			return nullptr;
		else if (n->left == nullptr)
			return n;
		else
			return findmin(n->left);
	}

	Node* _find(Node* n, const KeyType& k) const
	{
		if (!n)
			return nullptr;
		if (n->key == k)
			return n;
		if (n->key < k)
			return _find(n->right, k);
		else if (n->key > k)
			return _find(n->left, k);
		else
			return nullptr;
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
		}
	};

	std::string rPrint(Node* n) const
	{
		if (n == nullptr)
			return "";
		std::stringstream output;
		output << '(' << '[';
		output << n->key << ',' << n->value << ']';
		output << ',';
		if (n->left)
			output << rPrint(n->left);
		output << ',';
		if (n->right)
			output << rPrint(n->right);
		output << ')';
		return output.str();
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
		try {
			return &(_find(root, key)->value);
		}
		catch (const std::domain_error &e)
		{
			return nullptr;
		}
	};

	std::string toString() const
	{
		return rPrint(root);
	};
	
	template<typename StreamType>
	void print(StreamType& stream) const
	{
		_print(stream, root);
	};

	template<typename StreamType>
	void _print(StreamType& st, Node* n) const
	{
		if (!n) return;
		_print(st, n->left);
		std::cout << "[" << n->key << "," << n->value << "]\n";
		_print(st, n->right);
	};
};

template<typename KeyType, typename ValueType>
std::ostream& operator <<(std::ostream& stream, BinarySearchTree<KeyType, ValueType> const& tree)
{
	tree.print<std::ostream>(stream);
	return stream;
}
