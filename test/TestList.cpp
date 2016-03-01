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
		};
	};
}
