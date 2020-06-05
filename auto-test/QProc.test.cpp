#include <iostream>
#include <queued_process.enh.h>

int main()
{
	unsigned t = 0;
	enh::queued_process<unsigned> tQ;
	tQ.RegisterProc(
		[&](unsigned a) -> enh::tristate {t += a; return enh::tristate::GOOD; }
	);
	tQ.start_queue_process();
	unsigned exp = 0;

	for (unsigned i = 0; i < 5; ++i)
	{
		exp += i;
		tQ.postMessage(i);
	}

	tQ.safe_join(std::chrono::milliseconds(1));

	if (t != exp)
	{
		std::cerr << "QProc.test.cpp : Test 0 : Not evaluating all messages.";
		return 1;
	}
	else
	{
		std::cerr << "QProc.test.cpp : Test 0 : Has evaluated all messages.";
	}
}