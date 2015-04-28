#include"stdafx.h"
namespace CQ{

	template<typename T>
	struct __list_node
	{
		T value;
		__list_node* prev;
		__list_node* next;
	};
	template<typename T,typename Ref,typename Ptr>
	struct __list_iterator
	{
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T,Ref,Ptr> self;
		typedef Ref reference;
		typedef Ptr pointer;
		typedef T value_type;
		typedef size_t size_type;
		typedef __list_node<T>* link_type;

		link_type node;
		__list_iterator(){}
		__list_iterator(const link_type& x) :node(x){}
		__list_iterator(const self& x) :node(x.node){}

		bool operator!=(const self& x){ return node != x.node; }
		bool operator==(const self& x){ return node == x.node; }
		reference operator*()const{ return (*node).value; }
		pointer operator->()const{ return &(operator*()) }
		self& operator++(){
			node = node->next;
			return *this;
		}
		self&operator++(int){
			self tmp = *this;
			++(*this);
			return tmp;
		}
		self& operator--(){
			node = node->prev;
			return *this;
		}
		self&operator--(int){
			self tmp = *this;
			(*this)++;
			return tem;
		}
	};

	template<typename T>
	class list_node_allocator
	{
		typedef __list_node<T>* link_type;
		typedef size_t size_type;
		typedef __list_node<T> list_node;
	private:
		static link_type pool;
		static size_type count;
	public:
		list_node_allocator(){};
		static void put_node(link_type p){
			p->next = pool;
			pool = p;
			count++;
		}
		static link_type get_node(){
			link_type tmp;
			if (count==0)
			{
				tmp = new list_node;
				if (tmp == NULL)
				{
					throw("no more memory");
				}
			}
			else
			{
				tmp = pool;
				pool = pool->next;
				count--;
			}
			return tmp;
		}
		static void put_node(link_type p, size_type size){
			p->prev->next = pool;
			pool = p;
			count += size;
		}
		static void clear(){
			link_type tmp=NULL;
			while (pool!=NULL)
			{
				tmp = pool;
				pool = pool->next;
				delete tmp;
			}
		}
		static void destory(){
			clear();
		}
	};
	template<typename T> __list_node<T>* list_node_allocator<T>::pool = NULL;
	template<typename T> size_t list_node_allocator<T>::count = 0;

	//template<typename T>
	//size_type list_node_allocator<T>::count = 0;

	template<typename T,typename allocator=list_node_allocator<T>>
	class list
	{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef __list_node<T> list_node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_node<T>* link_type;
		typedef value_type& reference;
	public:
		list(){
			empty_initialize();
		}
		~list(){ clear(); }
		bool empty(){
			return this->node->next ==NULL&& this->node->prev==NULL;
		}
		iterator begin(){ return node->next; }
		iterator end(){ return node; }
		iterator erase(iterator iter){
			link_type t=iter.node->prev->next;
			iter.node->prev->next = iter.node->next;
			iter.node->next->prev = iter.node->prev;
			iterator tmp = ++iter;
			allocator::put_node(t);
			return tmp;
		}
		void push_back(const value_type& x){ insert(end(), x); }
		void pop_back(){ iterator tmp = end(); erase(--tmp); }
		void push_front(const value_type& x){
			insert(begin(), x);
		}
		void pop_front(){ erase(begin());	}
		void clear(){
			size_type si = size();
			link_type it =node->next;
			node->prev->next = NULL;
			it->prev = node->prev;
			allocator::put_node(it, si);
			node->next = node->prev = node;
		}
		iterator insert(iterator  iter, const value_type& x){
			link_type p = creat_node(x);
			p->next = iter.node;
			p->prev = iter.node->prev;
			iter.node->prev->next = p;
			iter.node->prev = p;
			return p;
		}
		size_type size(){ size_type tmp = 0; distance(begin(), end(), tmp); return tmp; }
		allocator get_allocator(){ return new allocator(); }
		void remove(const value_type& value){
			iterator p = begin();
			while (p!=end())
			{
				if (p.node->value==value)
				{
					erase(p);
				}
			}
		}
		reference front(){ return begin().node->value; }
		reference back(){
			iterator tmp = end();
			--tmp;
			return tmp.node->value;
		}
	private:
		link_type node;
		void distance(iterator _left, iterator _right,size_type& res){
			 res = 0;
			for (iterator i = _left; i != _right; i++)
			{
				++res;
			}
		}
		link_type creat_node(const value_type& x){
			link_type p = allocator::get_node();
			p->value = x;
			return p;
		}
		void destory_node(link_type p){
			allocator::put_node(p);
		}
		void empty_initialize(){
			node = allocator::get_node();
			node->next = node->prev = node;
		}
	};
}