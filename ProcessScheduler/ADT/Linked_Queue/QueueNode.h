
#ifndef _queuenode
#define _queuenode
#pragma once 

template < typename t>
class queuenode
{
private:
	t item; // a data item
	queuenode<t>* next; // pointer to next queuenode
public:
	queuenode();
	queuenode(const t& r_item);
	queuenode(const t& r_item, queuenode<t>* nextqueuenodeptr);
	void setitem(const t& r_item);
	void setnext(queuenode<t>* nextqueuenodeptr);
	t getitem() const;
	queuenode<t>* getnext() const;
}; // end queuenode
#endif

template < typename t>
queuenode<t>::queuenode()
{
	next = nullptr;
}

template < typename t>
queuenode<t>::queuenode(const t& r_item)
{
	item = r_item;
	next = nullptr;
}

template < typename t>
queuenode<t>::queuenode(const t& r_item, queuenode<t>* nextqueuenodeptr)
{
	item = r_item;
	next = nextqueuenodeptr;
}
template < typename t>
void queuenode<t>::setitem(const t& r_item)
{
	item = r_item;
}

template < typename t>
void queuenode<t>::setnext(queuenode<t>* nextqueuenodeptr)
{
	next = nextqueuenodeptr;
}

template < typename t>
t queuenode<t>::getitem() const
{
	return item;
}

template < typename t>
queuenode<t>* queuenode<t>::getnext() const
{
	return next;
}