#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>

template<typename KeyType, typename ValueType>
class AVLTree
{
private:
	struct Node 
	{
		KeyType key;
		ValueType value;
		int height;
		Node* left;
		Node* right;

		Node(const KeyType& k, const ValueType& v) : key(k), value(v), height(1)
		{
			left = nullptr;
			right = nullptr;
		}
	};
	Node* root;

	int height(Node* n) const
	{
		if (n) return n->height;
		else return 0;
	};

	Node* balance(Node* n)
	{
		if (!n) throw std::domain_error("");
		hrepair(n);

		if (bfactor(n) == 2)
		{
			if (bfactor(n->right) < 0)
				n->right = Rrotate(n->right);
			return Lrotate(n);
		}
		if (bfactor(n) == -2)
		{
			if (bfactor(n->left > 0))
				n->left = Lrotate(n->left);
			return Rrotate(n);
		}
		return n;
	};

	Node* Rrotate(Node* n)
	{
		if (n)
			return rotator(n, 'r');
		else
			throw std::domain_error("");
	};

	Node* Lrotate(Node* n)
	{
		if (n)
			return rotator(n, 'l');
		else
			throw std::domain_error("");
	}

	Node* rotator(Node* n, char rotate)
	{
		Node* t;
		if (rotate == 'r')
		{

		}
	}

	Node* insert(Node* n, const KeyType& k, const ValueType& v)
	{
		Node* t;
		if (n == nullptr)
		{
			t = new Node(k, v);
			return t;
		}

		if (k < n->key)
			n->left = insert(n->left, k, v);
		else
			n->right = insert(n->right, k, v);
		return balance(n);

	};
public:
	size_t size() const;

	void insert(KeyType const& key, ValueType const& value)
	{
		root = insert(root, key, value);
	}

	ValueType* find(KeyType const& key);

	std::string toString() const;

	template<typename StreamType>
	void print(StreamType& stream) const
	{
		print(stream, root);
	};

	template<typename StreamType>
	void print(StreamType & st, Node * n) const
	{
		if (!n) return;
		print(st, n->left);
		cout << "[" << n->key << "|" << n->value << "] ";
		print(st, n->right);
	};
};

template<typename KeyType, typename ValueType>
std::ostream& operator <<(std::ostream& stream, AVLTree<KeyType, ValueType> const& tree)
{
	tree.print<std::ostream>(stream);
	return stream;
}
