#include "stdafx.h"
#include "queue.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace cxs;

namespace test
{
	[TestClass]
	public ref class TestQueue
	{
	public:
		typedef queue<int> _Myqueue;
		typedef _Myqueue::size_type size_type;
		_Myqueue *_queue;
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

		[TestInitialize()]
		void TestInitialize(){
			_queue = new _Myqueue();
			_queue->push(1);
			_queue->push(2);
			_queue->push(3);
		};

		[TestCleanup()]
		void TestCleanup(){
			delete _queue;
		}

		[TestMethod]
		void TestConstruction()
		{
			//
			// TODO: �ڴ˴���Ӳ����߼�
			//
			Assert::AreEqual(_queue->size(), (size_type)3);
			Assert::AreEqual(_queue->front(), 1);
			Assert::AreEqual(_queue->back(), 3);

			_Myqueue q1 = *_queue;
			Assert::AreEqual(q1.size(), (size_type)3);
			Assert::AreEqual(q1.front(), 1);
			Assert::AreEqual(q1.back(), 3);

			_Myqueue q2 = std::move(q1);
			q1 = _Myqueue();
			Assert::AreEqual(q2.size(), (size_type)3);
			Assert::AreEqual(q2.front(), 1);
			Assert::AreEqual(q2.back(), 3);
		};

		[TestMethod]
		void TestSize(){
			Assert::AreEqual(_queue->size(), (size_type)3);
		}

		[TestMethod]
		void TestEmpty(){
			Assert::AreEqual(_queue->empty(), false);
			_Myqueue q1;
			Assert::AreEqual(q1.empty(), true);
		}

		[TestMethod]
		void TestFront(){
			Assert::AreEqual(_queue->front(), 1);

			const _Myqueue q1 = *_queue;
			Assert::AreEqual(_queue->front(), 1);
		};

		[TestMethod]
		void TestBack(){
			Assert::AreEqual(_queue->back(), 3);
			const _Myqueue q1 = *_queue;
			Assert::AreEqual(_queue->back(), 3);
		};

		[TestMethod]
		void TestOperators(){
			_Myqueue q1;
			q1.push(1);
			q1 = *_queue;
			Assert::AreEqual(q1.size(), (size_type)3);
			Assert::AreEqual(q1.front(), 1);
			Assert::AreEqual(q1.back(), 3);

			q1 = _Myqueue();
			Assert::AreEqual(q1.size(), (size_type)0);
		};

		[TestMethod]
		void TestPush(){
			Assert::AreEqual(_queue->back(), 3);
			Assert::AreEqual(_queue->front(), 1);
			int a = 1;
			_queue->push(a);
			Assert::AreEqual(_queue->back(), 1);
		};

		[TestMethod]
		void TestPop(){
			_queue->pop();
			Assert::AreEqual(_queue->back(), 3);
			Assert::AreEqual(_queue->front(), 2);
			_queue->pop();
			Assert::AreEqual(_queue->back(), 3);
			Assert::AreEqual(_queue->front(), 3);
			_queue->pop();
			Assert::AreEqual(_queue->empty(), true);
		};

		[TestMethod]
		void TestClear(){
			_queue->clear();
			Assert::AreEqual(_queue->empty(), true);
		};

		[TestMethod]
		void TestSwap(){
			_Myqueue q;
			q.swap(*_queue);
			Assert::AreEqual(q.size(), (size_type)3);
			Assert::AreEqual(q.front(), 1);
			Assert::AreEqual(q.back(), 3);
			Assert::AreEqual(_queue->empty(), true);
			swap(q, *_queue);
			Assert::AreEqual(q.empty(), true);
			Assert::AreEqual(_queue->size(), (size_type)3);
			Assert::AreEqual(_queue->front(), 1);
			Assert::AreEqual(_queue->back(), 3);
		};

	};
}
