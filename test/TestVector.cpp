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
			_vInt vec_0; //Ĭ�Ϲ��캯��
			Assert::AreEqual(vec_0.size(), (size_type)0);

			_vInt vec_1(4); //vector(const size_type size)
			Assert::AreEqual(vec_1.size(), (size_type)4);
			vec_1[0] = 2;
			Assert::AreEqual(vec_1[0], 2);

			_vInt vec_2(vec_1); //���ƹ��캯��
			Assert::AreEqual(vec_2.size(), (size_type)4);

			int a[] = {1, 3, 2};
			_vInt vec_3(a, 3); //����
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
