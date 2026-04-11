#pragma once

#include <vector>
#include <memory>

template <typename T>
class Tree
{
public:
	Tree(T&& data): m_data{std::make_shared<T>(data)}
	{
	}
	Tree(T&& data, Tree* parent): m_data{std::make_shared<T>(data)}, m_parent{parent}
	{
	}
	Tree(Tree&) = delete;
	Tree& operator=(Tree&) = delete;
	// ~Tree()
	// {
	// 	std::cout << 
	// }
	void addChild(T&& data)
	{
		m_children.emplace_back(std::make_unique<Tree>(std::move(data), this));
	}

	void dropChild(int idx)
	{
		m_children.erase(m_children.begin() + idx);
	}

	std::shared_ptr<T> getData() const
	{
		return m_data;
	}

	std::vector<std::unique_ptr<Tree>>& getChildren() 
	{
		return m_children;
	}

	// void makeRoot()
	// {
	// 	m_root = this;
	// }
	
	class Iter
	{

	public:
		Iter(std::nullptr_t node): m_node{nullptr}
		{
		}
		Iter(Tree* node, bool is_root_node) : m_node{node}
		{ 
			if(is_root_node)
			{
				m_root = node;
				m_node->m_curr_child = m_node->m_children.begin();
			}
			
		}
		~Iter()
		{
		}
		
		bool operator!=(Iter& other)
		{
			return (other.m_node != this->m_node);
		}
		Tree<T>& operator*()
		{
			return *m_node;
		}
		Iter operator++(int)
		{
			auto temp = *this;
			++(*this);
			return temp;
		}
		Iter& operator++()
		{
			if(m_node->m_curr_child != m_node->m_children.end())
			{
				// m_node = std::addressof(*m_node->m_curr_child);

				m_node = m_node->m_curr_child->get();
				m_node->m_curr_child = m_node->m_children.begin();
				return *this;
			}
			else
			{

				if(m_node == m_root)
				{

					m_node = nullptr;
					return *this;
				}
				else if(m_node->m_parent != nullptr)
				{
					auto sibling = ++m_node->m_parent->m_curr_child;
					if(sibling != m_node->m_parent->m_children.end())
					{

						m_node = sibling->get();
						m_node->m_curr_child = m_node->m_children.begin();
						return *this;
					}
					else
					{
						m_node = m_node->m_parent;
						return ++(*this);
					}
				}
				else
				{
					std::cout << "Error what to do?? returned a unique ptr to a newly allocated Iter that should be enough\n";
					exit(-1);
					return *this;
				}
			}
		}

	private:
		Tree* m_root{};
		Tree* m_node{};

	};
	Iter begin()
	{
		return Iter{this, true};
	}
	Iter end()
	{
		return Iter{nullptr};
	}


	template <typename B>
	friend void print_all(Tree<B>& root, int ind);

private:
	std::vector<std::unique_ptr<Tree>> m_children{};
	// I think of changing the shared pointer to the data itself so that the tree class holds the data inside it
	std::shared_ptr<T> m_data{};
	Tree* m_parent{};
	// Tree* m_root{nullptr};
	typename std::vector<std::unique_ptr<Tree>>::iterator m_curr_child{}; // For the Iter
};
