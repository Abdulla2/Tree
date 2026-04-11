#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include "tree.h"




template <typename T>
void print_all(Tree<T>& root, int ind = 0)
{
	for(auto i {0}; i < ind; ++i)
	{
		std::cout << '\t';
	}
	std::cout << *root.m_data << '\n';
	for(auto& child: root.m_children)
	{
		print_all(*child, ind +1);
	}
}

class DataClass
{

public:
	DataClass(int x): m_x{x}
	{
		std::cout<<"Data Class Constructed with " << x << "\n";
	}

	DataClass(const DataClass& data): m_x{data.m_x}
	{
		std::cout<<"Data copied to this from " << data.m_x << "\n";
	}
	DataClass& operator=(const DataClass& data)
	{
		m_x = data.m_x;
		std::cout<<"Data copied to this from " << data.m_x << "\n";
		return *this;
	}
	~DataClass()
	{
		std::cout<<"Data Class destructed of " << m_x << "\n";
	}
	int m_x;
	friend std::ostream&  operator<<(std::ostream& out, const DataClass& data); 
};


std::ostream&  operator<<(std::ostream& out, const DataClass& data)
{
	return out<<data.m_x;
}

void testFunc()
{
	std::cout << "Test Func Begin\n";
	Tree<DataClass> parent{5};


	parent.addChild(6);
	parent.addChild(8);
	parent.addChild(9);

	
	for (std::unique_ptr<Tree<DataClass>>& element : parent.getChildren()) {
		// std::cout << '\t' << *element.getData() << '\n';
		element->addChild(300);
		element->addChild(400);
		element->addChild(500);
	}
	print_all(parent);

	for(auto& elem: parent)
	{
		std::cout << "elem: " << *elem.getData() << '\n';
	}
	parent.dropChild(1);

	print_all(parent);
	for(auto& elem: parent)
	{
		std::cout << "elem2: " << *elem.getData() << '\n';
	}
	std::cout << "Test Func End\n";
}

std::unique_ptr<Tree<DataClass>> createSomeTree()
{

	std::unique_ptr<Tree<DataClass>> parent { new Tree<DataClass>{12}};


	parent->addChild(6);
	parent->addChild(8);
	parent->addChild(9);


	return parent;

}
void tempUn()
{

	auto new_parent =  createSomeTree();
	for(auto& elem: *new_parent )
	{
		std::cout << "elem4: " << *elem.getData() << '\n';
	}
	print_all(*new_parent);
}
int main()
{

	std::cout << "from inside Test Func Begin\n";
	testFunc();
	std::cout << "from inside Test Func End\n";

	tempUn();
	#if 0
	std::cout << "Tree Size " << sizeof(Tree<std::string>) << std::endl;

	Tree<DataClass> parent{4};

	// std::cout << *parent.getData() << ":\n";
	parent.addChild(5);
	parent.addChild(7);
	parent.addChild(7);

	// std::cout << parent.getData() << ":\n";
	for (std::unique_ptr<Tree<DataClass>>& element : parent.getChildren()) {
		// std::cout << '\t' << *element.getData() << '\n';
		element->addChild(300);
		element->addChild(400);
		element->addChild(500);
	}
	print_all(parent);


	// #if 0
	Tree<DataClass> parent2{4};
	for(const auto& elem2: parent2)
	{
		std::cout << "elem2: " << *elem2.getData() << '\n';
	}
	std::cout << "-----------------" << std::endl;
	auto it1 = parent.begin();

	// std::cout << *it1.m_node->getData() << "  " <<  it1.m_node << "  1 \n";
	// ++it1;
	// std::cout << *it1.m_node->getData() << "  " <<  it1.m_node << "  2 \n";
	// ++it1;
	// std::cout << *it1.m_node->getData() << "  " <<  it1.m_node << "  3 \n";
	// // #if 0
	std::cout << "-----------------" << std::endl;

	std::cout << "-----------------" << std::endl;
	for (const auto& elem : parent) {

		std::cout << "elem: " << *elem.getData() << '\n';
	}

	std::cout << "-----------------" << std::endl;
	std::cout << "-----------------" << std::endl;
	parent.addChild(9);
	parent.getChildren().back()->addChild(100);
	parent.getChildren().back()->addChild(200);
	parent.getChildren().at(1)->getChildren().pop_back();

	std::cout << "-----------------" << std::endl;
	std::cout << "-----------------" << std::endl;

	print_all(parent);
	std::cout << "-----------------" << std::endl;
	std::cout << "-----------------" << std::endl;
	Tree<float> parent3{9.0};
	parent3.addChild(8.0);
	parent3.getChildren().at(0)->addChild(7.0);
	parent3.getChildren().at(0)->getChildren().at(0)->addChild(6.0);
	std::cout << "-----------------" << std::endl;
	std::cout << "-----------------" << std::endl;
	for (const auto& elem : parent) {
		std::cout << "elem: " << *elem.getData() << '\n';
	}
	std::cout << "-----------------" << std::endl;
	std::cout << "-----------------" << std::endl;
	for (const auto& elem : parent3) {
		std::cout << "elem: " << *elem.getData() << '\n';
	}
	std::cout << "-----------------" << std::endl;
	std::cout << "-----------------" << std::endl;

	for(const auto& elem: *parent.getChildren().at(0))
	{
		std::cout << "elem: " << *elem.getData() << '\n';
	}
	std::cout << "cap: " <<  parent.getChildren().capacity() << '\n';

	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	parent.addChild(42);
	// #endif
	std::cout << "cap: " <<  parent.getChildren().capacity() << '\n';


	print_all(parent);
	// #endif
	#endif
	return 0;
}
