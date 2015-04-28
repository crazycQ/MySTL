#include"stdafx.h"
#define Nsize 20

namespace CQ{
	template<typename T>
	class vector
	{
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type* iterator;
		typedef value_type& reference;
		typedef size_t size_type;
		typedef const value_type* const_pointer;
		typedef const value_type* const_iterator;
	private:
		iterator start;
		iterator finish;
		iterator end_of_storage;
		void fill_initialize(size_type size, const value_type& value){
			this->start = new T[size]{value};
			this->finish = this->end_of_storage = this->start + size;
		}
		void construct(iterator iter, value_type value){
			judge_the_range(iter - start);
			if (finish == end_of_storage)
			{
				iterator temp = new value_type[2 * (end_of_storage - start)];
				end_of_storage = temp + 2 * (end_of_storage - start);
				iterator i = start;
				size_type n = 0;
				for (; i != iter;)
				{
					*(temp + n++) = *i++;
				}
				*(temp + n++) = value;
				for (; i != finish;)
				{
					*(temp + n++) = *i++;
				}
				finish = temp + size() + 1;
				start = temp;
			}
			else
			{
				iterator i = end();
				for (; i > iter; i--)
				{
					*i = *(i - 1);
				}
				*iter = value;
				finish++;
			}


		}
		void judge_the_range(size_type index){
			if (index<0 || index>this->size())
			{
				throw("out of range");
			}
		}

		void copy_from(iterator _left, iterator _right, iterator _dist){
			for (iterator i = _left; i < _right; i++)
			{
				*(_dist++) = *i;
			}
		}
	public:
		vector(){
			this->start = this->finish = new T[Nsize];
			this->end_of_storage = this->start + Nsize;
		}
		vector(size_type size, const T& value)		{
			fill_initialize(size, value);
		}
		vector(iterator _left, iterator _right){
			this->start = this->finish = new T[_right - _left];
			this->end_of_storage = _right - _left;
			copy_from(_left, _right, finish);
			finish += vec.size();
		}
		vector(const vector&vec){
			this->start = this->finish = new T[vec.max_size()];
			this->end_of_storage = this->start + vec.max_size();
			copy_from(vec.start, vec.finish, this->start);
			finish += vec.size();
		}

		vector& operator=(const vector& vec){
			delete[]this->start;
			this->start = this->finish = new T[vec.max_size()];
			this->end_of_storage = this->start + vec.max_size();
			copy_from(vec.start, vec.finish, this->start);
			finish += vec.size();
			return *this;
		}
		iterator begin(){ return start; }
		iterator end(){ return finish; }
		size_type size(){ return finish - start; }
		size_type max_size(){ return end_of_storage - start; }
		size_type capacity(){ return end_of_storage - finish; }
		bool empty(){ return start == end; }
		reference operator[](size_type n){
			judge_the_range(n);
			return start[n];
		}
		reference front(){ return *begin(); }
		reference back(){ return *(end() - 1); }
		reference at(size_type index){
			judge_the_range(index);
			return start[index];
		}
		pointer data(){
			if (empty()){ throw("there is no element in vector"); }
			return start;
		}
		void clear(){ finish = start; }
		iterator emplace(iterator iter, value_type val){ construct(iter, val); return iter; }
		void emplace_back(value_type val){ construct(finish, val); }
		iterator erase(iterator iter){
			for (iterator it = iter; it != finish - 1; it++)
			{
				*it = *(it + 1);
			}
			finish--;
			return iter;
		}
		iterator erase(iterator _first, iterator _last){
			for (iterator itl = _last, itl = _first; it != finish - 1; it++)
			{
				*itf = *(itl + 1);
			}
			finish -= (_last - _first);
			return _first;
		}
		void pop_back(){ erase(back()); }
		void push_back(value_type val){ construct(finish, val); }
		static void swap(value_type _left, value_type _right){
			value_type temp = _left;
			_left = _right;
			_right = temp;
		}
		void destory(){
			delete[]start;
			end_of_storage = finish = start = NULL;

		}

		~vector(){
			destory();
		}
	};
}