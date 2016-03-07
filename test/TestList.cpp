#include "stdafx.h"
#include "list.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace cxs;

namespace test
{
	[TestClass]
	public ref class TestList
	{
	private:
		TestContext^ testContextInstance;
	public:
		typedef list<int> _Mylist;
		typedef _Mylist::size_type size_type;
		typedef _Mylist::difference_type difference_type;
	private:
		_Mylist *pList1; //10, 10, 10, 10, 10
		_Mylist *pList2; //1, 2, 3, 4, 5

	public: 
		/// <summary>
		///获取或设置测试上下文，该上下文提供
		///有关当前测试运行及其功能的信息。
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		//编写测试时，可以使用以下附加特性:
		//
		//在运行类中的第一个测试之前，使用 ClassInitialize 来运行代码
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//在类中的所有测试都已运行之后，使用 ClassCleanup 来运行代码
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//在运行每个测试之前，使用 TestInitialize 来运行代码
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//在每个测试运行完之后，使用 TestCleanup 来运行代码
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestInitialize()]
		void TestInitialize(){
			pList1 = new _Mylist(5, 10);
			pList2 = new _Mylist;
			for(int i = 1; i <= 5; i++){
				pList2->push_back(i);
			}
		};

		[TestCleanup()]
		void TestCleanup(){
			delete pList1;
			delete pList2;
		};

		[TestMethod]
		void TestIterators(){
			//测试iterator的功能
			//->和*
			list<_Mylist> _order2_list(1, *pList2);
			list<_Mylist>::iterator _order2_it = _order2_list.begin();
			Assert::AreEqual(_order2_it->front(), 1);
			Assert::AreEqual((*_order2_it).front(), 1);
			//++,--
			_Mylist::iterator _it = pList2->begin();
			Assert::AreEqual(*(_it++), 1);
			Assert::AreEqual(*(++_it), 3);
			Assert::AreEqual(*(_it--), 3);
			Assert::AreEqual(*(--_it), 1);
			//==, !=
			_Mylist::iterator _it2 = pList2->begin();
			Assert::AreEqual(_it == _it2, true);
			Assert::AreEqual(_it != _it2, false);
			_it2++;
			Assert::AreEqual(_it == _it2, false);
			Assert::AreEqual(_it != _it2, true);
			//getPointer
			Assert::AreEqual(_it.getPointer()->value, 1);

			//reverse_iterator
			_Mylist::reverse_iterator _rit = pList2->rbegin();
			Assert::AreEqual(*(_rit++), 5);
			Assert::AreEqual(*(++_rit), 3);
			Assert::AreEqual(*(_rit--), 3);
			Assert::AreEqual(*(--_rit), 5);
		};

		[TestMethod]
		void TestConstruction()
		{
			//
			// TODO: 在此处添加测试逻辑
			//
			_Mylist lst1;
			Assert::AreEqual(lst1.size(), (size_type)0);

			_Mylist lst2(5);
			Assert::AreEqual(lst2.size(), (size_type)5);
			for(_Mylist::iterator _it = lst2.begin(); _it != lst2.end(); _it++){
				Assert::AreEqual(*_it, 0);
			}

			_Mylist lst3(5, 10);
			Assert::AreEqual(lst3.size(), (size_type)5);
			for(_Mylist::iterator _it = lst3.begin(); _it != lst3.end(); _it++){
				Assert::AreEqual(*_it, 10);
			}

			_Mylist lst4(lst3);
			Assert::AreEqual(lst4.size(), (size_type)5);
			for(_Mylist::iterator _it = lst4.begin(); _it != lst4.end(); _it++){
				Assert::AreEqual(*_it, 10);
			}

			_Mylist lst5(lst3.begin(), lst3.end());
			Assert::AreEqual(lst5.size(), (size_type)5);
			for(_Mylist::iterator _it = lst5.begin(); _it != lst5.end(); _it++){
				Assert::AreEqual(*_it, 10);
			}

			_Mylist lst6 = std::move(lst3);
			Assert::AreEqual(lst6.size(), (size_type)5);
			for(_Mylist::iterator _it = lst6.begin(); _it != lst6.end(); _it++){
				Assert::AreEqual(*_it, 10);
			}
		};

		[TestMethod]
		void TestOperators(){
			_Mylist lst1;
			_Mylist lst2;

			lst1 = *pList1;
			lst2 = std::move(*pList1);

			_Mylist::const_iterator _it;

			Assert::AreEqual(lst1.size(), (size_type)5);
			for(_it = lst1.begin(); _it != lst1.end(); _it++){
				Assert::AreEqual(*_it, 10);
			}

			Assert::AreEqual(lst2.size(), (size_type)5);
			for(_it = lst2.begin(); _it != lst2.end(); _it++){
				Assert::AreEqual(*_it, 10);
			}
		};

		[TestMethod]
		void TestAssign(){
			_Mylist lst1, lst2;

			lst1.assign(2, 5);
			lst2.assign(pList1->begin(), --pList1->end());

			_Mylist::const_iterator _it;

			Assert::AreEqual(lst1.size(), (size_type)2);
			for(_it = lst1.begin(); _it != lst1.end(); _it++){
				Assert::AreEqual(*_it, 5);
			}

			Assert::AreEqual(lst2.size(), (size_type)4);
			for(_it = lst2.begin(); _it != lst2.end(); _it++){
				Assert::AreEqual(*_it, 10);
			}
		};

		[TestMethod]
		void TestInsert(){
			//insert(pos, elem)
			int benchmark1[] = {10, 2, 10, 10, 10, 10};
			pList1->insert(++pList1->begin(), 2);
			_Mylist::const_iterator _it1 = pList1->begin();
			for(int i = 0; _it1 != pList1->end(); _it1++, i++){
				Assert::AreEqual(*_it1, benchmark1[i]);
			}

			//insert(pos, n, elem)
			int benchmark2[] = {10, 2, 10, 10, 10, 3, 3, 3, 3, 10};
			pList1->insert(--pList1->end(), 4, 3);
			_Mylist::const_iterator _it2 = pList1->begin();
			for(int i = 0; _it2 != pList1->end(); _it2++, i++){
				Assert::AreEqual(*_it2, benchmark2[i]);
			}

			//insert(pos, begin, end)
			int benchmark3[] = {10, 2, 10, 10, 10, 3, 3, 3, 3, 10, 1, 2, 3, 4, 5};
			pList1->insert(pList1->end(), pList2->begin(), pList2->end());
			_Mylist::const_iterator _it3 = pList1->begin();
			for(int i = 0; _it3 != pList1->end(); _it3++, i++){
				Assert::AreEqual(*_it3, benchmark3[i]);
			}

			//insert_exist
			int benchmark4[] = {10, 1, 2, 10, 10, 10, 3, 3, 3, 3, 10, 1, 2, 3, 4, 5};
			_Mylist::_Mylistnode *node = new _Mylist::_Mylistnode(1);
			pList1->insert_exist(++(pList1->begin()), _Mylist::iterator(node));
			Assert::AreEqual(pList1->size(), (size_type)16);
			_Mylist::const_iterator _it4 = pList1->begin();
			for(int i = 0; _it4 != pList1->end(); _it4++, i++){
				Assert::AreEqual(*_it4, benchmark4[i]);
			}

		};

		[TestMethod]
		void TestClear(){
			pList1->clear();
			Assert::AreEqual(pList1->size(), (size_type)0);
			Assert::AreEqual(pList1->begin() == pList1->end(), true);
		};

		[TestMethod]
		void TestErase(){
			//erase(pos)
			int benchmark1[] = {1, 3, 4, 5};
			_Mylist::iterator _next = pList2->erase(++pList2->begin());

			Assert::AreEqual(*_next, 3);
			Assert::AreEqual(pList2->size(), (size_type)4);
			_Mylist::const_iterator _it1 = pList2->begin();
			for(int i = 0; _it1 != pList2->end(); _it1++, i++){
				Assert::AreEqual(*_it1, benchmark1[i]);
			}

			//erase_return(pos)
			int benchmark2[] = {1, 4, 5};
			_Mylist::iterator _rtn = pList2->erase_return(++pList2->begin());
			Assert::AreEqual(*_rtn, 3);
			Assert::AreEqual(pList2->size(), (size_type)3);
			_Mylist::const_iterator _it2 = pList2->begin();
			for(int i = 0; _it2 != pList2->end(); _it2++, i++){
				Assert::AreEqual(*_it2, benchmark2[i]);
			}


		};

		[TestMethod]
		void TestPushBack(){
			Assert::AreEqual(pList2->size(), (size_type)5);
			_Mylist::const_iterator _it = pList2->begin();
			for(int i = 1; _it != pList2->end(); _it++, i++){
				Assert::AreEqual(*_it, i);
			}
		};

		[TestMethod]
		void TestPushFront(){
			pList2->push_front(0);
			Assert::AreEqual(pList2->size(), (size_type)6);
			_Mylist::const_iterator _it = pList2->begin();
			for(int i = 0; _it != pList2->end(); _it++, i++){
				Assert::AreEqual(*_it, i);
			}
		};

		[TestMethod]
		void TestPopBack(){
			pList2->pop_back();
			Assert::AreEqual(pList2->size(), (size_type)4);
			_Mylist::const_iterator _it = pList2->begin();
			for(int i = 1; _it != pList2->end(); _it++, i++){
				Assert::AreEqual(*_it, i);
			}
		};

		[TestMethod]
		void TestPopFront(){
			pList2->pop_front();
			Assert::AreEqual(pList2->size(), (size_type)4);
			_Mylist::const_iterator _it = pList2->begin();
			for(int i = 2; _it != pList2->end(); _it++, i++){
				Assert::AreEqual(*_it, i);
			}
		};

		[TestMethod]
		void TestResize(){
			pList1->resize(3);
			Assert::AreEqual(pList1->size(), (size_type)3);

			pList1->resize(6);
			Assert::AreEqual(pList1->size(), (size_type)6);
			int benchmark1[] = {10, 10, 10, 0, 0, 0};
			_Mylist::const_iterator _it1 = pList1->begin();
			for(int i = 0; _it1 != pList1->end(); _it1++, i++){
				Assert::AreEqual(*_it1, benchmark1[i]);
			}

			pList1->resize(10, 3);
			Assert::AreEqual(pList1->size(), (size_type)10);
			int benchmark2[] = {10, 10, 10, 0, 0, 0, 3, 3, 3, 3};
			_Mylist::const_iterator _it2 = pList1->begin();
			for(int i = 0; _it2 != pList1->end(); _it2++, i++){
				Assert::AreEqual(*_it2, benchmark2[i]);
			}

		};

		[TestMethod]
		void TestSwap(){
			pList1->swap(*pList2);

			int benchmark1[] = {1, 2, 3, 4, 5};
			_Mylist::const_iterator _it1 = pList1->begin();
			for(int i = 0; _it1 != pList1->end(); _it1++, i++){
				Assert::AreEqual(*_it1, benchmark1[i]);
			}

			int benchmark2[] = {10, 10, 10, 10, 10};
			_Mylist::const_iterator _it2 = pList2->begin();
			for(int i = 0; _it2 != pList2->end(); _it2++, i++){
				Assert::AreEqual(*_it2, benchmark2[i]);
			}
		};

		[TestMethod]
		void TestQueries(){
			const _Mylist cList = *pList2;
			//non const
			int i = 1;
			for(_Mylist::iterator _it = pList2->begin(); _it != pList2->end(); _it++){
				Assert::AreEqual(*_it, i++);
			}
			i = 5;
			for(_Mylist::reverse_iterator _it = pList2->rbegin(); _it != pList2->rend(); _it++){
				Assert::AreEqual(*_it, i--);
			}
			Assert::AreEqual(pList2->front(), 1);
			Assert::AreEqual(pList2->back(), 5);

			//const
			i = 1;
			for(_Mylist::const_iterator _it = cList.begin(); _it != cList.end(); _it++){
				Assert::AreEqual(*_it, i++);
			}
			i = 5;
			for(_Mylist::const_reverse_iterator _it = cList.rbegin(); _it != cList.rend(); _it++){
				Assert::AreEqual(*_it, i--);
			}
			Assert::AreEqual(cList.front(), 1);
			Assert::AreEqual(cList.back(), 5);
			
			//empty
			Assert::AreEqual(pList2->empty(), false);
			pList2->clear();
			Assert::AreEqual(pList2->empty(), true);

			Assert::AreEqual(cList.size(), (size_type)5);
		};

		[TestMethod]
		void TestMerge(){
			_Mylist lst1;
			_Mylist lst2;
			lst1.push_back(1);
			lst1.push_back(3);
			lst1.push_back(5);
			lst1.push_back(7);
			lst1.push_back(9);
			lst2.push_back(2);
			lst2.push_back(4);
			lst2.push_back(6);
			lst2.push_back(7);
			lst2.push_back(9);
			lst1.merge(lst2);
			Assert::AreEqual(lst2.size(), (size_type)0);
			Assert::AreEqual(lst1.size(), (size_type)10);
			int test[] = {1, 2, 3, 4, 5, 6, 7, 7, 9, 9};
			int i = 0;
			for(_Mylist::const_iterator _it = lst1.begin(); _it != lst1.end(); _it++){
				Assert::AreEqual(*_it, test[i++]);
			}
		};

		[TestMethod]
		void TestSplice(){
			int i;
			_Mylist::iterator _begin = pList2->begin();
			_begin++;
			_Mylist::iterator _end = pList2->end();
			_end--;
			_Mylist::iterator _pos = pList1->begin();
			_pos++;
			//test1
			pList1->splice(_pos, *pList2, _begin, _end);
			Assert::AreEqual(pList1->size(), (size_type)8);
			Assert::AreEqual(pList2->size(), (size_type)2);
			int test1[] = {10, 2, 3, 4, 10, 10, 10, 10};
			i = 0;
			for(_Mylist::const_iterator _it = pList1->begin(); _it != pList1->end(); _it++){
				Assert::AreEqual(*_it, test1[i++]);
			}
			//test2
			pList1->splice(pList1->end(), *pList2);
			Assert::AreEqual(pList1->size(), (size_type)10);
			Assert::AreEqual(pList2->size(), (size_type)0);
			int test2[] = {10, 2, 3, 4, 10, 10, 10, 10, 1, 5};
			i = 0;
			for(_Mylist::const_iterator _it = pList1->begin(); _it != pList1->end(); _it++){
				Assert::AreEqual(*_it, test2[i++]);
			}
		};
	};


}
