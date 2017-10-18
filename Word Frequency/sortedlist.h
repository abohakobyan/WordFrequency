

template <typename T>
class SortedList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* prev = nullptr, Node* next = nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* first_;
	Node* last_;
public:
	class iterator{
		friend class SortedList;
		SortedList* myList_;
		iterator(Node* curr,SortedList* myList){
			curr_ = curr;
			myList_ = myList;
		}
	public:
		Node* curr_;
		iterator(){
			curr_ = nullptr;
			myList_ = nullptr;
		}
		T& operator*(){
			return curr_->data_;
		}
		const T& operator*() const{
			return curr_->data_;
		}
		iterator operator++(){
			if (curr_) {
				curr_ = curr_->next_;
			}
			return *this;
		}
		iterator operator++(int){
			iterator old = *this;
			if (curr_) {
				curr_ = curr_->next_;
			}
			return old;
		}
		iterator operator--(){
			if (curr_) {
				curr_ = curr_->prev_;
			}
			return *this;
		}
		iterator operator--(int){
			iterator old = *this;
			if (curr_) {
				curr_ = curr_->prev_;
			}
			return old;
		}
		bool operator==(const iterator& other){
			return other.curr_ == curr_;
		}
		bool operator!=(const iterator& other){
			return other.curr_ != curr_;
		}
	};
	//creates empty linked list
	SortedList() {
		first_ = new Node();
		last_ = new Node();
		first_->next_ = last_;
		last_->prev_ = first_;
	}

	//destructor
	~SortedList() {
		if (this->first_ != nullptr)
		{
			Node * temp = this->first_;
			while (temp != nullptr) {
				temp = first_->next_;
				delete this->first_;
				first_ = temp;
			}

		}
	}

	//copy constructor
	SortedList(const SortedList& other) {
		*this = other;
	}

	//move constructor
	SortedList(const SortedList && other) {
		if (this->first_ != nullptr)
		{
			Node * temp = this->first_;
			while (temp != nullptr) {
				temp = first_->next_;
				delete this->first_;
				first_ = temp;
			}
		}
		*this = move(other);
	}

	//assignment operator
	const SortedList& operator=(const SortedList& other) {
		first_ = new Node();
		last_ = new Node();
		first_->next_ = last_;
		last_->prev_ = first_;
		Node* curr = other.first_;
		Node* end = other.last_;
		curr = curr->next_;
		while (curr != end)
		{
			Node* nn = new Node(curr->data_, last_->prev_, last_);
			last_->prev_->next_ = nn;
			last_->prev_ = nn;
			curr = curr->next_;
		}
		return *this;
	}

	//move operator
	const SortedList& operator=(const SortedList&& other) {
		if (this->first_ != nullptr)
		{
			Node * temp = this->first_;
			while (temp != nullptr) {
				temp = first_->next_;
				delete this->first_;
				first_ = temp;
			}
		}
		Node* curr = other.first_;
		Node* end = other.last_;
		Node * temo = curr;
		Node * tempr = end;
		first_ = temo;
		last_ = tempr;
		other.first_ = nullptr;
		other.last_ = nullptr;

		return move(*this);
	}

	//data into the list
	iterator insert(const T& data) {
		Node * temp = begin().curr_;
		
		if (temp != last_) {
			while (temp != last_) {
				if (data < temp->data_) {
					Node* nn = new Node(data, temp->prev_, temp);
					temp->prev_->next_ = nn;
					temp->prev_ = nn;
					iterator rc(nn, this);
					return rc;
				}
				else					{
					temp = temp->next_;
				}
			}
		}
		else if(temp == last_) {
			Node* nn = new Node(data, first_, last_);
			first_->next_ = nn;
			last_->prev_ = nn;
			return end();
		}
		
			Node* nn = new Node(data, temp->prev_, last_);
			temp->prev_->next_ = nn;
			last_->prev_ = nn;
			return end();
				
	}

	//returns iterator to node containing same value as data
	iterator find(const T& data) {
		Node * temp = begin().curr_;
		
			while (temp != last_) {
				if (data == temp->data_) {
					iterator rc(temp, this);
					return rc;
				}
				temp = temp->next_;
			}
		
		return end();
	}


	//removes the node referred to by it and returns 
	//the node after the removed node.
	iterator erase(iterator it) {
		if (it.myList_ == this) {
			Node* rm = it.curr_;
			Node* curr = first_;
			while (curr->next_ != rm) {
				curr = curr->next_;
			}
			curr->next_ = rm->next_;
			Node * next = rm->next_;
			next->prev_ = curr;
			it++;
			delete rm;

		}
		return it;
	}
	iterator increase(iterator it) {
		Node * temp = it.curr_;
		temp->data_.increase();
		return it;
	}
	//removes all nodes between from and to.  This includes
	//the node referred to by from but NOT the one referred to by 
	//to.  Function returns iterator to the node referred to by to
	iterator erase(iterator from, iterator to) {
		if (from.myList_ == this && to.myList_ == this) {

			Node * temp = from.curr_;
			Node * save = temp->prev_;


			while (from.curr_ != to.curr_) {
				temp = from.curr_->next_;
				delete from.curr_;
				from.curr_ = temp;
			}
			Node * start = save;
			Node * end = to.curr_;
			start->next_ = end;
			end->prev_ = start;
		}

		return to;
	}

	iterator begin(){return iterator(first_->next_, this);}
	iterator end(){return iterator(last_, this);}
};
