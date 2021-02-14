#include <iostream>
#include <memory>
#include <random>
#include <filesystem>
#include <fstream>


template <typename T>
class Stack {

private:
	struct pointNode {
		T data;
		std::unique_ptr<pointNode> next;

		pointNode():data(std::move(T{})),next(std::move(std::unique_ptr<pointNode>{})){}
		pointNode(T n_data, std::unique_ptr<pointNode> ptr) : data(std::move(n_data)), next(std::move(ptr)) {}

		bool operator!=(Stack<T>::pointNode obj1) const {
			if (this) return true;
			else return false;
		}
		pointNode* operator++() {
			return this->next.get();
			//return m_temp;

		}

		const T& getValue() {
			return this->data;
		}

	
	};
	std::unique_ptr<pointNode> head;
public:
	
	class Iterator {
		using Iterator_type = Stack<T>::pointNode;
	public:
		Iterator() = default;

		Iterator(Iterator_type* rNode) {
			current_node = rNode;
		}

		Iterator_type* operator=(Iterator_type* rNode) {
			this->current_node = rNode;
		}
		int a;


	private:

		Iterator_type* current_node;

	};






	using type_t = T;
	Stack() : head(std::unique_ptr<pointNode>{}) {}
	Stack(const T& data);
	Stack(const T& data, std::unique_ptr<pointNode> ptr);
	template<typename...Args>
	Stack(Args&&...args);
	void push(const T& data);
	void pop() ;
	const T& top() const  noexcept;
	bool is_empty() const  noexcept;
	inline void print_stack() const noexcept;
	inline typename pointNode* Begin() noexcept;
	inline typename pointNode* Next(pointNode*)noexcept;
	inline typename Stack<T>::pointNode* End()noexcept;
	T& findValue(T);
	void clear() noexcept;
	void fill_rnumb(int,int,int);
	void write_to_file(std::filesystem::path filePath);
	void read_fr_file(std::filesystem::path filePath);



};

template <typename T>
Stack<T>::Stack(const T& data, std::unique_ptr<pointNode> ptr) :head(std::move(ptr)) {
	head->data = std::move(data);
}

template <typename T>
Stack<T>::Stack(const T& data) : head(std::make_unique<pointNode>(std::move(data), 
								 std::move(std::unique_ptr<pointNode>{}))) {}


template<typename T>
template<typename ...Args>
inline Stack<T>::Stack(Args && ...args)
{
	//int tmp{};
	//(tmp += ... += (head = std::make_unique<pointNode>(std::forward<Args>(args), std::move(head)), 0));
	((head = std::make_unique<pointNode>(std::forward<Args>(args),std::move(head))),...);
	

}

template <typename T>
void Stack<T>::push(const T& data) {
	try {
		auto temp = std::make_unique<pointNode>(data, nullptr);
		if (head == nullptr) head = std::move(temp);
		else {
			temp->next = std::move(head);
			head = std::move(temp);
		}
	}
	catch (std::bad_alloc e)
	{
		std::cout << e.what() << std::endl;
		return;
	}

}

template <typename T>
bool Stack<T>::is_empty() const noexcept {
	if (head) return false;
	else return true;
}



template<typename T>
inline typename Stack<T>::pointNode* Stack<T>::Begin() noexcept
{
	pointNode* head = this->head.get();
	return head;
}

template<typename T>
inline typename Stack<T>::pointNode* Stack<T>::Next(pointNode* current) noexcept
{
	if (current) {
		current= current->next.get();
	}

	else return nullptr;
}

template<typename T>
inline typename Stack<T>::pointNode* Stack<T>::End() noexcept
{
	return nullptr;
}

template<typename T>
T& Stack<T>::findValue(T search_numb)
{
	pointNode* head = this->head.get();
	int count{};
	while (head) {
		if (head->data == search_numb)
			return count;
		else {
			count++;
			head = head->next.get();
		}
	}
	throw std::exception("Число не найдено");
}

template <typename T>
void Stack<T>::pop()  {
	if (!is_empty())
		head = std::move(head->next);
	else
		throw std::exception("Стек пуст");
}

template<typename T>
inline void Stack<T>::clear() noexcept
{
	while (head) {
		this->pop();
	}
}

template<typename T>
void Stack<T>::fill_rnumb(int counter, int l_border, int r_border)
{
	std::random_device rd;    
	std::mt19937 rng(rd());    
	std::uniform_int_distribution<int> uni(l_border, r_border);
	while (counter) {
		auto random_integer = uni(rng);
		this->push(random_integer);
		counter--;
	}
}

template<typename T>
inline void Stack<T>::write_to_file(std::filesystem::path filePath)
{
	std::wofstream writeFile(filePath, std::ios::trunc);
	pointNode* head = this->head.get();
	while (head) {
		writeFile << head->data << " ";
		head = head->next.get();
		
	}
	writeFile.close();
}

template<typename T>
inline void Stack<T>::read_fr_file(std::filesystem::path filePath)
{
	
	std::wifstream readFile(filePath, std::ios::end);
	T symb;
	while (readFile >> symb) {
		this->push(symb);
	}
	

}

template <typename T>
const T& Stack<T>::top() const  noexcept {
	if (!is_empty())
		return head->data;

	else return T{};


}


