#include <timer.enh.h>
#include <iostream>


int main()
{
	enh::timer<1, std::chrono::seconds> test;
	for (int i = 0; i < 10; ++i)
	{
		test.wait();
		auto start = enh::high_res::now();
		test.wait_for(2);
		auto end = enh::high_res::now();

		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		std::cout << "wait time : 2s, measured : " << ms.count() << "ms ; error : " << ms.count() - 2000 << "\n";
	}
	LOG_LINE;
	test.stop();
	LOG_LINE;
	enh::millis<10> test2;
	for (int i = 0; i < 10; ++i)
	{
		test2.wait();
		auto start = enh::high_res::now();
		test2.wait_for(5);
		auto end = enh::high_res::now();

		std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << "wait time : 50ms, measured : " << ms.count() << "us ; error : " << ms.count() - 50000 << "\n";
	}

	test2.stop();
}

/* ****************************************************************************
(measured time may vary)
Output:

wait time : 2s, measured : 2001ms ; error : 1
wait time : 2s, measured : 2000ms ; error : 0
wait time : 2s, measured : 2000ms ; error : 0
wait time : 2s, measured : 2001ms ; error : 1
wait time : 2s, measured : 2000ms ; error : 0
wait time : 2s, measured : 1999ms ; error : -1
wait time : 2s, measured : 2000ms ; error : 0
wait time : 2s, measured : 1999ms ; error : -1
wait time : 2s, measured : 2000ms ; error : 0
wait time : 2s, measured : 2001ms ; error : 1
wait time : 50ms, measured : 51022us ; error : 1022
wait time : 50ms, measured : 49984us ; error : -16
wait time : 50ms, measured : 49986us ; error : -14
wait time : 50ms, measured : 50397us ; error : 397
wait time : 50ms, measured : 50064us ; error : 64
wait time : 50ms, measured : 49843us ; error : -157
wait time : 50ms, measured : 50002us ; error : 2
wait time : 50ms, measured : 49869us ; error : -131
wait time : 50ms, measured : 49974us ; error : -26
wait time : 50ms, measured : 49956us ; error : -44


******************************************************************************/