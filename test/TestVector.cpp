#include "stdafx.h"
#include "vector.h"
//#include <vector>


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace cxs;
//using namespace std;
//using namespace std;

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
			
		};
	};
}
