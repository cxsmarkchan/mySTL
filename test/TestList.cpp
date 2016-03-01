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
		///��ȡ�����ò��������ģ����������ṩ
		///�йص�ǰ�������м��书�ܵ���Ϣ��
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
		//��д����ʱ������ʹ�����¸�������:
		//
		//���������еĵ�һ������֮ǰ��ʹ�� ClassInitialize �����д���
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//�����е����в��Զ�������֮��ʹ�� ClassCleanup �����д���
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//������ÿ������֮ǰ��ʹ�� TestInitialize �����д���
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//��ÿ������������֮��ʹ�� TestCleanup �����д���
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void TestConstruction()
		{
			//
			// TODO: �ڴ˴���Ӳ����߼�
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
