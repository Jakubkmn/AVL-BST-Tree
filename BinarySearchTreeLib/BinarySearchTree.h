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

public:

	size_t size() const;

	void insert(KeyType const& key, ValueType const& value)
	{
		
	};
	
	void remove(KeyType const& key);

	ValueType* find(KeyType const& key);

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
