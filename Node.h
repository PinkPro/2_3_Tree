#ifndef Node_H
#define Node_H
#include <cstddef>
#include "Key.h"
#include "Value.h"

class Node  
{
public:
	
	Node(const Key* nkey, const Value* nval)
	{
		if (nkey == NULL)
		{
			k = NULL;
		}
		else 
		{
			k = nkey->clone();
		}
		if (nval == NULL)
		{
			v = NULL;
		}
		else
		{
			v = nval->clone();
		}
		r = NULL;
		m = NULL;
		l = NULL;
		index = 0;

	}

	void set_p (Node* p) // sets p to be the parent of the node func was applied on
	{
	parent = p;
	}

	void set_r (Node* right)
	{ 
	r = right;
	}
	
	void set_m (Node* middle)
	{ 
	m = middle;
	}

	void set_l (Node* left)
	{ 
	l = left;
	}
	
	Key* get_k ()
	{
		return k;
	}
	
	Value* get_val ()
	{
		return v;
	}
	
	Node* get_l ()
	{
		return this->l;
	}
	
	Node* get_m ()
	{
		return this->m;
	}
	
	Node* get_r ()
	{
		return this->r;
	}
	
	Node* get_p ()
	{
		return this->parent;
	}
	
	void set_k (Key* nkey)
	{
		this->k = nkey;
	}
	
	void up_idx ()
	{
		(this->index)++;
	}
	
	unsigned get_idx ()
	{
		return this->index;
	}
	
	void set_idx (unsigned tmp)
	{
		this->index = 0;
		while (tmp > 0)
		{
		(this->index)++;
		tmp--;
		}
	}
	
	bool not_leaf() const;
	
	~Node()
	{
		if (v!= NULL)
		{
			delete v;
		}
		if (k!= NULL)
		{
			delete k; 
		}	
	}
	
	unsigned deg();
	
	Value* nSearch (const Key* key);
	
	unsigned nRank (const Key* key);
	
	const Key* nSelect(unsigned idx) const;
	
private:
		Key* k;
		Value* v;
		Node* parent;
		Node* r;
		Node* m;
		Node* l;
			
		unsigned index;
};

#endif