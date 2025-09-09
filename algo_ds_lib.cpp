#include "base/linear_structure.h"
#include "base/stack_structure.h"
#include <iostream>

using namespace std;

int main() {
	LinearStructure<int> *list = new SqList<int>("SequenceList", 10);
	list->insert(0, 42);
	list->insert(1, 43);
	list->insert(1, 44);
	std::cout << *list << std::endl;

	LinearStructure<int> *linklist = new LinkList<int>("LinkList");
	linklist->insert(0, 42);
	linklist->insert(1, 43);
	linklist->insert(1, 44);
	std::cout << *linklist << std::endl;

	LinearStructure<int> *dlinklist = new DLinkList<int>("DLinkList");
	dlinklist->insert(0, 42);
	dlinklist->insert(1, 43);
	dlinklist->insert(1, 44);
	DoubleNode<int> *node = dynamic_cast<DLinkList<int> *>(dlinklist)->find_node(1);
	dynamic_cast<DLinkList<int> *>(dlinklist)->insert_prior_node(node, 100);
	std::cout << *dlinklist << std::endl;

	LinearStructure<int> *slinklist = new SLinkList<int>("SLinkList", 10);
	slinklist->insert(0, 42);
	slinklist->insert(1, 43);
	slinklist->insert(1, 44);
	std::cout << *slinklist << std::endl;
	std::cout << "locate number 43: " << slinklist->locate(43) << std::endl;

	StackStructure<int> *sqstack = new SqStack<int>("SqStack", 10);
	sqstack->push(42);
	sqstack->push(43);
	sqstack->push(44);
	std::cout << *sqstack << std::endl;

	delete list, linklist, dlinklist, slinklist, sqstack;
	return 0;
}
