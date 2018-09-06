#include "BalancedTree.h"

void BalancedTree:: Insert(const Key* nkey,const Value* nval)
{
	if (nkey == NULL)
	{
		return ;
	}
	
	Node* z = new Node(nkey, nval);
	Node* y = root;
	Node* w = NULL;
	
	while ((y != NULL) && (y->not_leaf()) )
	{
		w = y;
	
		if ((z->get_k())->operator<(*(y->get_l()->get_k())) )
		{
			y = y->get_l();
		}
	
		else if ((z->get_k())->operator<(*(y->get_m()->get_k())) )
		{
			y = y->get_m();
		}
	
		else
		{
			y = y->get_r();
		}
	}
	z->set_idx(1);
	z = this->Insert_And_Split (w,z);
	
	if (z == NULL)
	{	
		while (w!=NULL)
		{
			w->set_idx(w->get_idx()+1);
			w = w->get_p();
		}
	}
	while ((z != NULL) && (w != root))
	{
		w = w->get_p();
		z = this->Insert_And_Split (w,z);
	
		if (z == NULL)
		{
			while (w!=NULL)
			{
			w->set_idx(w->get_idx()+1);
			w = w->get_p();
			}
		}
	}
	
	if (z != NULL)
	{
		Node* a = new Node (NULL, NULL); // connecting the new node created (in the split) to the existed tree
		
		if ((z->get_k())->operator<(*w->get_k()))
		{
		a->set_l(z);
		a->set_m(w);
		a->set_k(w->get_k()->clone());
		w->set_p(a);
		z->set_p(a);
		}
		
		else
		{
		a->set_l(w);
		a->set_m(z);
		a->set_k(z->get_k()->clone());
		w->set_p(a);
		z->set_p(a);
		}
		
		root = a;
		a->set_p(NULL);
		a->set_idx((a->get_l()->get_idx()) + (a->get_m()->get_idx()));
	}
}


Node* BalancedTree::Search_node(Node* x ,const Key* key) const
{
	if (!(x->not_leaf())) // if x is a leaf
	{
		if ((!((x->get_k())->operator<(*key))) && (!(key->operator< (*(x->get_k()))))) // if x.k = key
		{
			return x;
		}
		
		else 
		{
			return NULL;
		}
	}
	
	if ((!(key->operator< (*(x->get_l()->get_k())))) && (!((x->get_l()->get_k())->operator<(*key)))) // if key=x.l.k
	{
		return Search_node(x->get_l(), key);
	}
	
	if (key->operator<(*(x->get_l()->get_k()))) // if key < x.l.k
	{
		return Search_node(x->get_l(), key);
	}
	
	if ((!(key->operator< (*(x->get_m()->get_k())))) && (!((x->get_m()->get_k())->operator<(*key)))) //if key=x.m.k
	{
		return Search_node(x->get_m(), key);
	}
	
	if (key->operator<(*(x->get_m()->get_k()))) // if key < x.m.k
	{
		return Search_node(x->get_m(), key);
	}
	
	else	
	{
		return Search_node(x->get_r(), key);
	}
}

void BalancedTree::Delete(const Key* dkey)
{
	Node* x = Search_node(root, dkey);
	
	if (!x)
	{
		return;
	}	
	
	Node* y;
	y = x->get_p();
	
	if (x == (y->get_l()))
	{
		y->set_l(y->get_m());
		y->set_m(y->get_r());
		y->set_r(NULL);
	}
	
	else if (x == (y->get_m()))
	{
		y->set_m(y->get_r());
		y->set_r(NULL);
	}
	
	else 
	{
		y->set_r(NULL);
	}
	delete x;
	y->set_idx((y->get_idx()) - 1);
	
	while (y != NULL)
	{
		if ((y->deg()) >= 2) // if y has two childern or more
		{
			if ((y->get_r()) != NULL)
			{
				if (y &&((y->get_k()) != NULL))
				{
					delete (y->get_k());
				}
				y->set_k(y->get_r()->get_k()->clone());	
			}
			else 
			{
				if (y &&((y->get_k()) != NULL))
				{
					delete (y->get_k());
				}
				y->set_k(y->get_m()->get_k()->clone());
			}
			
			y = y->get_p();
		}
		// if y has 1 child
		else if (y != root)
		{
			y = this->Borrow_Or_Merge(y);
		}
		
		else // if y is the root
		{
			root = y->get_l();
			root->set_p(NULL);
			delete y;
			y = NULL;
		}
	}
}


Value* BalancedTree::Search(const Key* key) const
{
	return root->nSearch(key);
}

unsigned BalancedTree::Rank(const Key* key) const
{
	return root->nRank(key);
}

const Key* BalancedTree::Select(unsigned index) const
{
	return root->nSelect(index);
}

