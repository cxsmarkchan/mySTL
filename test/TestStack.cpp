#include "stdafx.h"
#include "stack.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace cxs;

namespace test
{
	[TestClass]
	public ref class TestStack
	{
	private:
		TestContext^ testContextInstance;

	public: 
		typedef stack<int> _Mystack;
		typedef _Mystack::size_type size_type;
		_Mystack* _stack;
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
			_stack = new _Mystack();
			_stack->push(1);
			_stack->push(2);
			_stack->push(3);
		};

		[TestCleanup]
		void TestCleanup(){
			delete _stack;
		}

		[TestMethod]
		void TestConstruction()
		{
			//
			// TODO: 在此处添加测试逻辑
			//
			_Mystack s1;
			Assert::AreEqual(s1.empty(), true);
			_Mystack s2(*_stack);
			Assert::AreEqual(s2.top(), 3);
			Assert::AreEqual(s2.size(), (size_type)3);
			_Mystack s3(std::move(s2));
			s2 = _Mystack();
			Assert::AreEqual(s3.top(), 3);
			Assert::AreEqual(s3.size(), (size_type)3);
		};

		[TestMethod]
		void TestOperators(){
			_Mystack s1;
			s1 = *_stack;
			Assert::AreEqual(s1.top(), 3);
			Assert::AreEqual(s1.size(), (size_type)3);
			_Mystack s2;
			s2 = std::move(s1);
			s1 = _Mystack();
			Assert::AreEqual(s2.top(), 3);
			Assert::AreEqual(s2.size(), (size_type)3);

		};

		[TestMethod]
		void TestPop(){
			_stack->pop();
			Assert::AreEqual(_stack->top(), 2);
			Assert::AreEqual(_stack->size(), (size_type)2);
		};

		[TestMethod]
		void TestTop(){
			//非const情形已测试，下面是const情形
			const _Mystack s1 = *_stack;
			Assert::AreEqual(s1.top(), 3);
		}

		[TestMethod]
		void TestSwap(){
			_Mystack s1;
			s1.swap(*_stack);
			Assert::AreEqual(_stack->empty(), true);
			Assert::AreEqual(s1.size(), (size_type)3);
			Assert::AreEqual(s1.top(), 3);

			swap(*_stack, s1);
			Assert::AreEqual(s1.empty(), true);
			Assert::AreEqual(_stack->size(), (size_type)3);
			Assert::AreEqual(_stack->top(), 3);
		};

		[TestMethod]
		void TestClear(){
			_stack->clear();
			Assert::AreEqual(_stack->empty(), true);
		}

	};
}
