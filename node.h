/*******************************************************************************
  Chocoholics CS314 Program: Entities Interface
Names: Yollaine Brooks,
Description of Program:
 *********************************************************************************/

template <typename TYPE>
struct node
{
	typedef node<TYPE>* node_ptr;
	TYPE data;
	node_ptr next;

	node(const TYPE& d) : data(d), next(nullptr) {}
};
