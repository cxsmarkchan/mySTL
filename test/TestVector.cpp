#include "stdafx.h"
#include "vector.h"


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace cxs;
//using namespace std;

namespace test
{
	[TestClass]
	public ref class TestVector
	{
	private:
		TestContext^ testContextInstance;

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
		void TestMethod1()
		{
			//
			// TODO: �ڴ˴���Ӳ����߼�
			vector<int> vec(4);
			vec.push_back(10);
			vec.push_back(20);
			//Assert.AreEqual(vec[0],10);
			//cerr << vec[0];
			Assert::AreEqual(vec[1], 20);
			//
		};
	};
}
