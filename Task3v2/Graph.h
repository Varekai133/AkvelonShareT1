#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <string>
using namespace std;

template <typename T>
class Node
{
public:
	T _data;
	bool _visited;
	vector<Node<T>*> _next;

	Node()
	{

	}

	Node(T data)
	{
		_data = data;
	}

	Node(T data, vector<Node<T>*> next)
	{
		_data = data;
		_next = next;
	}
};

template <typename T>
class Graph
{
public:
	vector<Node<T>*> _nodes;
	vector<Node<T>*> _sortnodes;
	int _nodesnumber;
	class Iterator;

	Iterator begin() { return _sortnodes[0]; }
	Iterator end() { return  _sortnodes[_nodesnumber - 1]; }

	Node<T>& operator[] (const int& n)
	{
		if (n > 0 || n < _nodesnumber)
			return *_nodes[n];
		else return *_nodes[0];
	}


	Graph()
	{

	}

	void DSearch()
	{
		Node<T>* node = _nodes[0];
		node->_visited = true;
		list<Node<T>*> q;
		q.push_back(node);

		while (!q.empty())
		{
			Node<T>* u = q.front();
			q.pop_front();
			_sortnodes.push_back(u);
			int k = 0;
			vector<Node<T>*> unext = u->_next;
			while (k < unext.size())
			{
				Node<T>* v = unext[k];
				if (!v->_visited)
				{
					v->_visited = true;
					q.push_back(v);
					unext = v->_next;
					k = 0;
				}
				else k++;
			}
		}
	}

	void WSearch()
	{
		Node<T>* node = _nodes[0];
		node->_visited = true;
		list<Node<T>*> q;
		q.push_back(node);

		while (!q.empty())
		{
			Node<T>* u = q.front();
			q.pop_front();
			_sortnodes.push_back(u);

			for (int i = 0; i < u->_next.size(); ++i)
			{
				Node<T>* v = u->_next[i];
				if (!v->_visited)
				{
					v->_visited = true;
					q.push_back(v);
				}
			}
		}
	}

	void Printindex()
	{
		for (int i = 0; i < _nodesnumber; ++i)
		{
			cout << "[" << to_string(i) << "]" << _nodes[i]->_data << " ";
			cout << endl;
		}
	}

	void AddNode(T data)
	{
		Node<T> *node = new Node<T>(data);
		_nodes.push_back(node);
		_nodesnumber++;
	}

	void AddEdge(Node<T> &from, Node<T> &to)
	{
		from._next.push_back(&to);
	}

	void Print()
	{
		cout << "  ";
		for (int i = 0; i < _nodesnumber; ++i)
		{
			cout << _nodes[i]->_data << " ";
		}
		cout << endl;
		for (int i = 0; i < _nodesnumber; ++i)
		{
			cout << _nodes[i]->_data << " ";
			Node<T>* node = _nodes[i];
			for (int j = 0; j < _nodesnumber; ++j)
			{
				if (find(node->_next.begin(), node->_next.end(), _nodes[j]) != node->_next.end())
				{
					cout << "1 ";
				}
				else cout << "0 ";
			}
			cout << "\n";
		}
	}

	void UnvisitAll()
	{
		for (int i = 0; i < _nodesnumber; ++i)
		{
			Node<T>* node = _nodes[i];
			node->_visited = false;
		}
		_sortnodes.clear();
	}

	bool isEmpty()
	{
		if (_nodesnumber > 0)
			return false;
		else return true;
	}

	void DeleteNode(int index)
	{
		Node<T>* node1 = _nodes[index];

		for (auto it = _nodes.begin(); it != _nodes.end(); ++it)
		{
			Node<T>* n = *it;
			for (auto it2 = n->_next.begin(); it2 != n->_next.end(); ++it2)
			{
				if (*it2 == node1)
				{
					n->_next.erase(it2);
					break;
				}
			}
		}

		node1->_next.clear();

		for (auto it3 = _nodes.begin(); it3 != _nodes.end(); ++it3)
		{
			if (*it3 == node1)
			{
				Node<T>* t = *it3;
				_nodes.erase(it3);
				_nodesnumber--;
				delete t;
				break;
			}
		}
	}

	void DeleteEdge(int index1, int index2)
	{
		Node<T>* node1 = _nodes[index1];
		Node<T>* node2 = _nodes[index2];

		for (auto it = node1->_next.begin(); it != node1->_next.end(); ++it)
		{
			if (*it == node2)
			{
				node1->_next.erase(it);
				break;
			}
		}
	}

public:
	class Iterator
	{
	public:
		Iterator()
		{

		}

		Iterator(Node<T>* node) : _cur(node)
		{
			
		}

		Iterator(vector<Node<T>>* node) : _res(node)
		{
			
		}

		bool operator!= (const Iterator& it) { return _cur != it._cur; }
		bool operator== (const Iterator& it) { return _cur == it._cur; }


		Node<T>& operator++ (int)
		{		
			_index = ++_index;
			_cur = _res.at(_index);
			return *_res.at(_index);
		}

		Node<T>& operator+ (int n)
		{
			return *_res.at(n);
		}

	public:
		Node<T>* _cur;
		vector<Node<T>*> _res;
		int _index = 0;
	};

	/*class DIterator
	{
	public:
		DIterator(Node<T>* node) : _cur(node)
		{

		}

		bool operator!= (const DIterator& it) { return _cur != it._cur; }
		bool operator== (const DIterator& it) { return _cur == it._cur; }

		Node<T>& operator++ (int)
		{
			_index = ++_index;
			_cur = _res.at(_index);
			return *_res.at(_index);
		}

		Node<T>& operator+ (int n)
		{
			return *_res.at(n);
		}

	public:
		Node<T>* _cur;
		vector<Node<T>*> _res;
		int _index = 0;
	};*/
};
