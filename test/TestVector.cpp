#include "stdafx.h"
#include "vector.h"


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace cxs;

namespace test
{
	[TestClass]
	public ref class TestVector
	{
	private:
		TestContext^ testContextInstance;

	public: 
		typedef vector<int> _vInt;
		typedef _vInt::size_type size_type;
		typedef _vInt::difference_type difference_type;
		_vInt* _pVec;

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
			int a[] = {1, 2, 3, 4};
			_pVec = new _vInt(a, 4); 
		}

		[TestCleanup()]
		void TestCleanup(){
			delete _pVec;
		}

		[TestMethod]
		void TestConstruction()
		{
			//
			// TODO: 在此处添加测试逻辑
			_vInt vec_0; //默认构造函数
			Assert::AreEqual(vec_0.size(), (size_type)0);

			_vInt vec_1(4); //vector(const size_type size)
			Assert::AreEqual(vec_1.size(), (size_type)4);
			vec_1[0] = 2;
			Assert::AreEqual(vec_1[0], 2);

			_vInt vec_2(vec_1); //复制构造函数
			Assert::AreEqual(vec_2.size(), (size_type)4);

			int a[] = {1, 3, 2};
			_vInt vec_3(a, 3); //数组
			Assert::AreEqual(vec_3.size(), (size_type)3);
			Assert::AreEqual(vec_3[0], 1);
			Assert::AreEqual(vec_3[1], 3);
			Assert::AreEqual(vec_3[2], 2);

			_vInt vec_4((size_type)2, 5);//vector(size_type n, const T& elem)
			Assert::AreEqual(vec_4.size(), (size_type)2);
			Assert::AreEqual(vec_4[0], 5);
			Assert::AreEqual(vec_4[1], 5);

			_vInt::iterator _end = vec_3.end() - 1;
			_vInt vec_5(vec_3.begin(), _end);
			Assert::AreEqual(vec_5.size(), (size_type)2);
			Assert::AreEqual(vec_5[0], 1);
			Assert::AreEqual(vec_5[1], 3);
			
		}

		[TestMethod]
		void TestOperators(){
			//等号和非const的下标
			_vInt vec;
			vec = *_pVec;
			Assert::AreEqual(vec.size(), (size_type)4);
			Assert::AreEqual(vec[0], 1);
			Assert::AreEqual(vec[1], 2);
			Assert::AreEqual(vec[2], 3);
			Assert::AreEqual(vec[3], 4);

			//const下标
			const _vInt vec2 = *_pVec;
			Assert::AreEqual(vec2.size(), (size_type)4);
			Assert::AreEqual(vec2[0], 1);
			Assert::AreEqual(vec2[1], 2);
			Assert::AreEqual(vec2[2], 3);
			Assert::AreEqual(vec2[3], 4);
		}

		[TestMethod]
		void TestPush(){
			_pVec->push_back(5);
			_pVec->push_back(6);
			for(int i = 0; i < 6; i++){
				Assert::AreEqual(_pVec->at(i), i + 1);
			}
			Assert::AreEqual(_pVec->size(), (size_type)6);
			Assert::AreEqual(_pVec->capacity(), (size_type)8);
		}

		[TestMethod]
		void TestPop(){
			_pVec->pop_back();
			_pVec->pop_back();
			for(int i = 0; i < 2; i++){
				Assert::AreEqual(_pVec->at(i), i + 1);
			}
			Assert::AreEqual(_pVec->size(), (size_type)2);
		}

		[TestMethod]
		void TestAssign(){
			_vInt vec = *_pVec;
			_vInt::iterator _begin = vec.begin() + 1;
			_vInt::iterator _end = vec.begin() + 3;
			_pVec->assign(_begin, _end);
			Assert::AreEqual(_pVec->size(), (size_type)2);
			Assert::AreEqual(_pVec->at(0), 2);
			Assert::AreEqual(_pVec->at(1), 3);

			_pVec->assign((size_type)4, 1);
			Assert::AreEqual(_pVec->size(), (size_type)4);
			for(int i = 0; i < 4; i++){
				Assert::AreEqual(_pVec->at(i), 1);
			}
		}

		[TestMethod]
		void TestInsert(){
			_vInt::iterator _pos = _pVec->insert(_pVec->begin(), 0); //0, 1, 2, 3, 4
			Assert::AreEqual(_pVec->size(), (size_type)5);
			for(int i = 0; i < 5; i++){
				Assert::AreEqual(_pVec->at(i), i);
			}
			Assert::AreEqual(*_pos, 0);

			_pVec->insert((_vInt::const_iterator)(_pVec->begin() + 1), (size_type)2, 10); // 0, 10, 10, 1, 2, 3, 4
			Assert::AreEqual(_pVec->size(), (size_type)7);
			Assert::AreEqual(_pVec->at(0), 0);
			Assert::AreEqual(_pVec->at(1), 10);
			Assert::AreEqual(_pVec->at(2), 10);
			Assert::AreEqual(_pVec->at(3), 1);
			Assert::AreEqual(_pVec->at(4), 2);
			Assert::AreEqual(_pVec->at(5), 3);
			Assert::AreEqual(_pVec->at(6), 4);

			int a[] = {1, 2};
			_vInt vec(a, 2);
			_pVec->insert(_pVec->end(), vec.begin(), vec.end()); // 0, 10, 10, 1, 2, 3, 4, 1, 2
			Assert::AreEqual(_pVec->size(), (size_type)9);
			Assert::AreEqual(_pVec->at(7), 1);
			Assert::AreEqual(_pVec->at(8), 2);
		}

		[TestMethod]
		void TestClear(){
			_pVec->clear();
			Assert::AreEqual(_pVec->size(), (size_type)0);
		}

		[TestMethod]
		void TestErase(){
			_vInt::iterator _pos = _pVec->begin() + 1;
			Assert::AreEqual(*(_pVec->erase(_pos)), 3);
			Assert::AreEqual(_pVec->size(), (size_type)3);

			_vInt::iterator _begin = _pVec->begin();
			_vInt::iterator _end = _pVec->begin() + 2;
			Assert::AreEqual(*(_pVec->erase(_begin, _end)), 4);
			Assert::AreEqual(_pVec->size(), (size_type)1);
		}

		[TestMethod]
		void TestResize(){
			Assert::AreEqual(_pVec->resize(2), (difference_type)0);
			Assert::AreEqual(_pVec->size(), (size_type)2);
			Assert::AreEqual(_pVec->capacity(), (size_type)4);
			_pVec->resize(6, 1);
			Assert::AreEqual(_pVec->at(0), 1);
			Assert::AreEqual(_pVec->at(1), 2);
			Assert::AreEqual(_pVec->at(2), 1);
			Assert::AreEqual(_pVec->at(3), 1);
			Assert::AreEqual(_pVec->at(4), 1);
			Assert::AreEqual(_pVec->at(5), 1);
		}

		[TestMethod]
		void TestReserve(){
			Assert::AreEqual(_pVec->reserve(2), (difference_type)0);
			Assert::AreEqual(_pVec->size(), (size_type)4);
			Assert::AreEqual(_pVec->capacity(), (size_type)4);
			
			_pVec->reserve(6);
			Assert::AreEqual(_pVec->size(), (size_type)4);
			Assert::AreEqual(_pVec->capacity(), (size_type)6);
		}

		[TestMethod]
		void TestSwap(){
			int num[] = {5, 6};
			_vInt vec2(num, 2);
			_pVec->swap(vec2);
			Assert::AreEqual(_pVec->size(), (size_type)2);
			Assert::AreEqual(_pVec->capacity(), (size_type)2);
			Assert::AreEqual(_pVec->at(0), 5);
			Assert::AreEqual(_pVec->at(1), 6);
			Assert::AreEqual(vec2.size(), (size_type)4);
			Assert::AreEqual(vec2.capacity(), (size_type)4);
			Assert::AreEqual(vec2[0], 1);
			Assert::AreEqual(vec2[1], 2);
			Assert::AreEqual(vec2[2], 3);
			Assert::AreEqual(vec2[3], 4);

			//swap(*_pVec, vec2);
			/*Assert::AreEqual(_pVec->size(), (size_type)4);
			Assert::AreEqual(_pVec->capacity(), (size_type)4);
			Assert::AreEqual(_pVec->at(0), 1);
			Assert::AreEqual(_pVec->at(1), 2);
			Assert::AreEqual(_pVec->at(2), 3);
			Assert::AreEqual(_pVec->at(3), 4);
			Assert::AreEqual(vec2.size(), (size_type)2);
			Assert::AreEqual(vec2.capacity(), (size_type)2);
			Assert::AreEqual(vec2[0], 5);
			Assert::AreEqual(vec2[1], 6);*/
		}



	};
}
