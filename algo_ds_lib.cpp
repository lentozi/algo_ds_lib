#include "base/linear_structure.h"
#include <iostream>

using namespace std;

int main() {
	LinearStructure<int>* list = new SqList<int>("SequenceList", 10);
	list->insert(0, 42);
	list->insert(1, 43);
	list->insert(1, 44);
	std::cout << *list << std::endl;

	LinearStructure<int>* linklist = new LinkList<int>("LinkList");
	linklist->insert(0, 42);
	linklist->insert(1, 43);
	linklist->insert(1, 44);
	std::cout << *linklist << std::endl;

	LinearStructure<int>* dlinklist = new DLinkList<int>("DLinkList");
	dlinklist->insert(0, 42);
	dlinklist->insert(1, 43);
	dlinklist->insert(1, 44);
	DoubleNode<int>* node = static_cast<DLinkList<int>*>(dlinklist)->find_node(1);
	static_cast<DLinkList<int>*>(dlinklist)->insert_prior_node(node, 100);
	std::cout << *dlinklist << std::endl;

	LinearStructure<int>* slinklist = new SLinkList<int>("SLinkList", 10);
	slinklist->insert(0, 42);
	slinklist->insert(1, 43);
	slinklist->insert(1, 44);
	std::cout << *slinklist << std::endl;
	std::cout << slinklist->locate(43) << std::endl;

	delete list, linklist, dlinklist, slinklist;
	return 0;
}
