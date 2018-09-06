#include <cstddef>
#include "Node.h"
	
bool Node::not_leaf() const
{
	if (l != NULL)
	{
		return true;
	}		
	return false;
}
	
unsigned Node::deg()
{
	if ((this->get_r()) == NULL)
	{
		if (((this->get_l()) == NULL) && ((this->get_m()) == NULL))
		{
			return 0;
		}
		else if ((this->get_m()) == NULL)
		{
			return 1;
		}
		else if ((this->get_l()) == NULL)
		{
			return 1;
		}
		return 2;
	}
	else if ((this->get_m()) == NULL)
	{
		if ((this->get_l()) == NULL)
		{
			return 1;
		}
		return 2;
	}
	else if ((this->get_l()) == NULL)
	{
		return 2;
	}
return 3;
}
	
Value* Node::nSearch (const Key* key)
{
	if ((this == NULL) || (key == NULL))
	{
		return NULL;
	}
	
	if (!(this->not_leaf()))
	{
		if (this == NULL)
		{
			return NULL;
		}
		if (!(k->operator<(*key)) && !(key->operator<(*k)))
		{
			return v;
		}
		
		else 
		{
			return NULL;
		}
	}

	else if (!(key->operator<(*(l->k))) && !((l->k)->operator<(*key)))
	{
		return l->nSearch(key);
	}
		
	else if (key->operator<(*(l->k)))
	{
		return l->nSearch(key);
	}
		
	else if (!(key->operator<(*(m->k))) && !((m->k)->operator<(*key)))
	{
		return m->nSearch(key);
	}
			
	else if (key->operator<(*(m->k)))
	{
		return m->nSearch(key);
	}	
	
	else	
	{
		return r->nSearch(key);
	}
}
	
unsigned Node::nRank (const Key* key)
{
	if (this == NULL || key == NULL)
	{
		return 0;
	}
	
	if (!(this->not_leaf()))	
	{
		return 1;
	}
	
	if ((!(key->operator<(*(l->get_k())))) && (!((l->get_k())->operator<(*key))))
	{
		return l->nRank(key);
	}
	
	else if (key->operator<(*(l->get_k())))
	{
		return l->nRank(key);
	}
	
	else if ((!(key->operator<(*(m->get_k())))) && (!((m->get_k())->operator<(*key))))
	{
		return ((l->index) + (m->nRank(key)));
	}
	else if (key->operator<(*(m->get_k())))
	{
		return ((l->index) + (m->nRank(key)));
	}
	else
	{
		return ((l->index) + (m->index) + (r->nRank(key)));
	}
	return 0;
}

const Key* Node::nSelect(unsigned idx) const
{
	if (this && (index < idx))
	{
		return NULL;
	}
		
	if (!(this->not_leaf()))
	{
		return this->k;
	}
	
	else if (idx <= (this->l->index))
	{
		return l->nSelect(idx);
	}
	else if (idx <= ((m->index)+(l->index)))
	{
		return m->nSelect(idx-(l->index));
	}
	else
	{
		return r->nSelect((idx-(l->index))-(m->index));
	}

}