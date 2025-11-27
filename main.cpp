#include <cstddef>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>
#include <memory>


template <typename T>
class Tree
{
public:
	Tree(T&& data): m_data{std::make_shared<T>(data)}, m_iter{this, false} 
	{
	}
	Tree(T&& data, Tree* parent): m_data{std::make_shared<T>(data)}, m_parent{parent} ,m_iter{this, false}
	{
	}
	void addChild(T&& data)
	{
		m_children.emplace_back(Tree{std::move(data), this});
	}

	std::shared_ptr<T> getData() const
	{
		return m_data;
	}

	std::vector<Tree>& getChildren() 
	{
		return m_children;
	}

	void makeRoot()
	{
		m_root = this;
	}
	// template <typename V>
	// class Iter
	// {
	//
	// public:
	// 	Iter(std::nullptr_t node) : m_node{nullptr}, m_parent{nullptr}
	// 	{
	// 	}
	//
	// 	Iter(Tree* node, Iter* parent = nullptr) : m_node{node}, m_curr_child(node->m_children.begin()), m_parent(parent)
	// 	{
	// 	// std::cout << "Node: " << node << "Parent: " << parent << "Locals :" << m_node << *m_curr_child << m_parent << "\n";
	// 	}
	// 	Iter& operator++()
	// 	{
	// 		if(m_node->m_children.end() != m_curr_child)
	// 		{
	// 			std::cout << "Not last child\n";
	//
	//
	// 			m_curr_child->m_iter = Iter{std::addressof(*m_curr_child), this};
	// 			auto& temp = m_curr_child->m_iter;
	// 			m_curr_child++;
	//
	// 			return temp;
	// 			// return m_curr_child++;
	// 			// return Iter{std::addressof(*m_curr_child++), this};
	//
	//
	// 			// m_curr_child++;
	// 			// return  m_curr_c
	// 			// Tree<T> tree;
	// 			// return Iter{&tree, this};
	// 		}
	// 		else
	// 		{
	// 			std::cout << " last child\n";
	// 			if(m_parent != nullptr)
	// 			{
	// 				std::cout << "going to parent\n";
	// 				return ++(*m_parent);
	// 			}
	// 			else 
	// 			{
	// 				std::cout << "Finished\n";
	// 				return this->m_node->end();
	// 			}
	// 		}
	// 	}
	//
	// 	Tree<T> operator*()
	// 	{
	// 		return *m_node;
	// 	}
	// 	bool operator!=(Iter& other)
	// 	{
	// 		return (other.m_node != this->m_node);
	// 	}
	// private:
	// 	Iter* m_parent{};
	// 	Tree* m_node{};
	// 	// int m_depth{};
	// 	typename std::vector<Tree>::iterator m_curr_child{};
	// } m_iter;
	
	// template <typename V>
	class Iter
	{

	public:
		Iter(std::nullptr_t node): m_node{nullptr}
		{
		}
		Iter(Tree* node, bool is_root_node) : m_node{node}, m_is_root_node{is_root_node}
		{
		}
		~Iter()
		{
		}
		
		bool operator!=(Iter& other)
		{
			return (other.m_node != this->m_node);
		}
		Tree<T> operator*()
		{
			return *m_node;
		}
		void print_data()
		{

		// std::cout << "
		}
		Iter& operator++()
		{
			std::cout << "Entered ++ op: state: " << static_cast<int>(m_state) << "\n";
			switch(m_state)
			{
				case node_iter_state::init_state:
					/*Todo: This State is redundant and will cause issues*/
					m_curr_child = m_node->m_children.begin();
					m_state = node_iter_state::children_iter_state;
						std::cout << "this " << this << "child: " << std::addressof(m_curr_child->m_iter) << "\n";
						std::cout << "m_node " << m_node << "m_child: " << std::addressof(*m_curr_child) << "\n";
					return *this;
				case node_iter_state::children_iter_state:
					if(m_curr_child != m_node->m_children.end())
					{
						std::cout << "looping children\n";
						// auto retval = m_curr_child;
						m_curr_child->m_iter = Iter{std::addressof(*m_curr_child),false};
						std::cout << "this " << this << "child: " << std::addressof(m_curr_child->m_iter) << "\n";
						std::cout << "m_node " << m_node << "m_child: " << std::addressof(*m_curr_child) << "\n";
						return m_curr_child->m_iter;
					}
					else
					{

						std::cout << "finished children\n";
						m_state = node_iter_state::finished_state;
						if(m_is_root_node)
						{
							
							std::cout << "last child\n";
							m_node = nullptr;
							return *this;
						}
						else if(m_node->m_parent != nullptr)
						{
							auto sibling = ++m_node->m_parent->m_iter.m_curr_child;
							if(sibling != m_node->m_parent->m_children.end())
							{
								std::cout << "going to sibling no children left\n";
								sibling->m_iter = Iter{std::addressof(*sibling),false};
								return sibling->m_iter;
							}
							else
							{
								std::cout << "going to parent no children nor siblings left\n";
								return ++m_node->m_parent->m_iter;
							}
						}
						else
						{
							std::cout << "Error what to do?? returned a unique ptr to a newly allocated Iter that should be enough\n";

							exit(-1);
							return *this;
							// return std::make_unique(Iter{m_node, true});
						}
					}
				break;
				default:
				std::cout << "ERRROR\n";
					exit(-1);
					return *this;
				break;
			}
		}
	// private:
		bool m_is_root_node{false};
		Tree* m_node{};
		// bool 
		enum class node_iter_state
		{
			init_state,
			children_iter_state,
			finished_state
		};

		node_iter_state m_state{node_iter_state::init_state};
		typename std::vector<Tree>::iterator m_curr_child{};

	};
	Iter begin()
	{
		// m_iter = {this};
		// m_iter = Iter{this, true};
		return Iter{this, true};
	}
	Iter end()
	{
		return Iter{nullptr};
	}


	template <typename B>
	friend void print_all(Tree<B>& root, int ind);

private:
	std::vector<Tree> m_children{};
	std::shared_ptr<T> m_data{};
	Tree* m_parent{};
	Tree* m_root{nullptr};
	// Iter m_iter{};
};

template<typename T>
class MyArray
{
public:
	MyArray(): arr{}
	{
	}


	T& operator[](int idx)
	{
		return arr[idx];
	}

	T* begin()
	{
		return &arr[0];
	}
	T* end()
	{
		return &arr[9];
	}
private:
	T arr[10]{};
};

template <typename T>
void print_all(Tree<T>& root, int ind = 0)
{
	for(auto i {0}; i < ind; ++i)
	{
		std::cout << '\t';
	}
	std::cout << *root.m_data << '\n';
	for(auto child: root.m_children)
	{
		// std::cout << child.m_data << '\n';
		print_all(child, ind +1);
	}
}

int main()
{



	for(int elem: MyArray<int>{})
	{

     std::cout << elem << '\n';
	}


	std::cout << "Tree Size " << sizeof(Tree<std::string>) << std::endl;

	Tree<int> parent{4};

	// std::cout << *parent.getData() << ":\n";
	parent.addChild(5);
	parent.addChild(7);
	parent.addChild(7);

	// std::cout << parent.getData() << ":\n";
	for (Tree<int>& element : parent.getChildren()) {
		// std::cout << '\t' << *element.getData() << '\n';
		element.addChild(300);
		element.addChild(400);
		element.addChild(500);
	}

	print_all(parent);


	Tree<int> parent2{4};
	for(auto elem2: parent2)
	{
		std::cout << "elem2: " << *elem2.getData() << '\n';
	}
	std::cout << "-----------------" << std::endl;
	auto it1 = parent.begin();

	std::cout << *it1.m_node->getData() << "  " <<  it1.m_node << "  1 \n";
	++it1;
	std::cout << *it1.m_node->getData() << "  " <<  it1.m_node << "  2 \n";
	++it1;
	std::cout << *it1.m_node->getData() << "  " <<  it1.m_node << "  3 \n";
	#if 0
	std::cout << "-----------------" << std::endl;

	for (auto elem : parent) {
	
		std::cout << "elem: " << *elem.getData() << '\n';
	}

	#endif

	return 0;
}
