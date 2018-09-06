#ifndef BalancedTree_H
#define BalancedTree_H
#include <cstddef>
#include "Key.h"
#include "Value.h"
#include "Node.h"


class BalancedTree
{
public:
	BalancedTree(const Key* min,const Key* max)
	{
		Tmin = min->clone();
		Tmax = max->clone();
		Node* root1 = new Node (Tmax, NULL);
		Node* left = new Node (Tmin, NULL);
		Node* mid = new Node (Tmax, NULL);
		left->set_p(root1);
		mid->set_p(root1);
		root1->set_p(NULL);  
		root1->set_l(left);
		root1->set_m(mid);
		root1->set_r(NULL);
		root = root1;
	}
	
	~BalancedTree()
	{
		this->Destroy(root); 
		delete Tmin;
		delete Tmax;
	}
	
	void Insert(const Key* nkey,const Value* nval);
	Node* Search_node(Node* x ,const Key* key) const; 
	void Delete(const Key* dkey);
	Value* Search(const Key* key) const;
	unsigned Rank(const Key* key) const;
	const Key* Select(unsigned index) const;

	
private:
		const Key* Tmin;
		const Key* Tmax;
		Node* root;
		
		void Destroy(Node* nd)
		{
			if (nd != NULL)
			{
				this->Destroy(nd->get_l());
				this->Destroy(nd->get_m());
				this->Destroy(nd->get_r());
				delete nd;
			}
		}	
Node* Insert_And_Split (Node* w, Node* z)
{
	if ((w == NULL) || (z == NULL))
	{
		return NULL;
	}
	
	if ((w->deg()) == 2)
	{
		if ((z->get_k())->operator<(*(w->get_l()->get_k())))
		{
			w->set_r(w->get_m());
			w->set_m(w->get_l());
			w->set_l(z);
		}
		
		else if ((z->get_k())->operator<(*(w->get_m()->get_k())))
		{
			w->set_r(w->get_m());
			w->set_m(z);
		}
		
		else
		{
			w->set_r(z);
		}
		
		z->set_p(w);
		if (w &&((w->get_k()) != NULL))
		{
			delete (w->get_k());
		}
		w->set_k(w->get_r()->get_k()->clone());
		return NULL;
	}
		
	
	Node* y = new Node(NULL, NULL);
	Node* nl = w->get_l();
	Node* nm = w->get_m();
	Node* nr = w->get_r();
	
	w->set_r(NULL);
	y->set_r(NULL);
	
	if ((z->get_k())->operator<(*(nl->get_k())))
	{
		w->set_l(z);
		w->set_m(nl);
		y->set_l(nm);
		y->set_m(nr);
		z->set_p(w);
		nl->set_p(w);		
		nm->set_p(y);
		nr->set_p(y);
	}
	
	else if ((z->get_k())->operator<(*(nm->get_k())))
	{
		w->set_l(nl);
		w->set_m(z);
		y->set_l(nm);
		y->set_m(nr);
		z->set_p(w);
		nl->set_p(w);		
		nm->set_p(y);
		nr->set_p(y);
	}
	
	else if ((z->get_k())->operator<(*(nr->get_k())) )
	{
		w->set_l(nl);
		w->set_m(nm);
		y->set_l(z);
		y->set_m(nr);
		nm->set_p(w);
		nl->set_p(w);		
		z->set_p(y);
		nr->set_p(y);
	}
	
	else
	{
		w->set_l(nl);
		w->set_m(nm);
		y->set_l(nr);
		y->set_m(z);
		nm->set_p(w);
		nl->set_p(w);		
		z->set_p(y);
		nr->set_p(y);			
	}
	if (w &&((w->get_k()) != NULL))
	{
		delete (w->get_k());
	}
	if (y &&((y->get_k()) != NULL))
	{
		delete (y->get_k());
	}
	w->set_k(w->get_m()->get_k()->clone());
	y->set_k(y->get_m()->get_k()->clone());
	
	y->set_idx((y->get_l()->get_idx()) + (y->get_m()->get_idx()));
	w->set_idx((w->get_l()->get_idx()) + (w->get_m()->get_idx()));
	
	return y; 
}

Node* Borrow_Or_Merge(Node* y)
{
	Node* z ; 
	z = y->get_p();
	Node* x;
	if (y == (z->get_l()))
	{
		x = z->get_m();
		if ((x->deg()) == 3)
		{
			y->set_m(x->get_l());
			(y->get_m())->set_p(y);
			x->set_l(x->get_m());
			x->set_m(x->get_r());
			x->set_r(NULL);
			if (y &&((y->get_k()) != NULL))
			{
				delete (y->get_k());
			}
			y->set_k(y->get_m()->get_k()->clone());
			
			y->set_idx(((y->get_l())->get_idx()) + ((y->get_m())->get_idx()));
			x->set_idx(((x->get_l())->get_idx()) + ((x->get_m())->get_idx()));
		}
		
		else 
		{
			x->set_r(x->get_m());
			x->set_m(x->get_l());
			x->set_l(y->get_l());
			(x->get_l())->set_p(x);
			delete y;
			z->set_l(z->get_m());
			z->set_m(z->get_r());
			z->set_r(NULL);
			x->set_idx(((x->get_l())->get_idx()) + ((x->get_m())->get_idx()) + ((x->get_r())->get_idx()));
		}
	}
	
	else if (y == (z->get_m()))
	{
		x = z->get_l();
		if ((x->deg()) == 3)
		{
			y->set_m(y->get_l());
			y->set_l(x->get_r());
			(y->get_l())->set_p(y);
			x->set_r(NULL);
			if (y &&((y->get_k()) != NULL))
			{
				delete (y->get_k());
			}
			if (x &&((x->get_k()) != NULL))
			{
				delete (x->get_k());
			}
			x->set_k(x->get_m()->get_k()->clone());
			y->set_k(y->get_m()->get_k()->clone());
			
			y->set_idx(((y->get_l())->get_idx()) + ((y->get_m())->get_idx()));
			x->set_idx(((x->get_l())->get_idx()) + ((x->get_m())->get_idx()));
		}
		else
		{
			x->set_r(y->get_l());
			(x->get_r())->set_p(x);
			if (x &&((x->get_k()) != NULL))
			{
				delete (x->get_k());
			}
			x->set_k(x->get_r()->get_k()->clone());
			delete y;
			z->set_m(z->get_r());
			z->set_r(NULL);
			x->set_idx((x->get_l()->get_idx()) + (x->get_m()->get_idx()) + (x->get_r()->get_idx()));
			
		}
	}
	else if (y == (z->get_r()))
	{
		x = z->get_m();
		if ((x->deg()) == 3)
		{
			y->set_m(y->get_l());
			y->set_l(x->get_r());
			(y->get_l())->set_p(y);
			x->set_r(NULL);
			if (y &&((y->get_k()) != NULL))
			{
				delete (y->get_k());
			}
			if (x &&((x->get_k()) != NULL))
			{
				delete (x->get_k());
			}
			x->set_k(x->get_m()->get_k()->clone());
			y->set_k(y->get_m()->get_k()->clone());
			
			y->set_idx((y->get_l()->get_idx()) + (y->get_m()->get_idx()));
			x->set_idx((x->get_l()->get_idx()) + (x->get_m()->get_idx()));
		}
		else
		{
			x->set_r(y->get_l());
			x->get_r()->set_p(x);
			if (x &&((x->get_k()) != NULL))
			{
				delete (x->get_k());
			}
			x->set_k(x->get_r()->get_k()->clone());
			delete y;
			z->set_r(NULL);
			x->set_idx((x->get_l()->get_idx()) + (x->get_m()->get_idx()) + (x->get_r()->get_idx()));

		}
	}
	return z; 
}
};


#endif
