#include <iostream>
#include <queued_process.enh.h>

#define ASSERT_TEST(condition, message_fail)		if(condition) \
													{\
														std::cerr << "PASS : " << __FILE__ << " : " << __func__ << "\n";\
														return true;\
													}\
													else\
													{\
														std::cerr << "FAIL : " << __FILE__ << " : " << __func__ << " : " message_fail "\n"; \
													}


namespace testCase
{
	bool basicTest()
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

		ASSERT_TEST(t == exp, "Not evaluating all messages");
	}

	bool forceStopTest()
	{
		unsigned t = 0;
		enh::queued_process<unsigned> tQ;
		tQ.RegisterProc(
			[&](unsigned a) -> enh::tristate {
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				t += a; 
				std::cout << t << " " << a << "\n";
				return enh::tristate::GOOD; 
			}
		);
		tQ.start_queue_process();
		unsigned exp = 0;

		for (unsigned i = 0; i < 10; ++i)
		{
			tQ.postMessage(i);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5 * 5));

		exp = 0 + 1 + 2 + 3 + 4;

		tQ.force_join();

		ASSERT_TEST(t <= exp, "Evaluating even after force stop");
	}

	bool restartTest()
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

		tQ.start_queue_process();
		for (unsigned i = 0; i < 5; ++i)
		{
			exp += i;
			tQ.postMessage(i);
		}

		ASSERT_TEST(t == exp, "Restart queue failed");
	}
}

int main()
{

	bool full_pass = testCase::basicTest();
	if (!full_pass)
		return 1;

	full_pass = full_pass | testCase::forceStopTest();
	if (!full_pass)
		return 1;

	full_pass == full_pass | testCase::restartTest();
	if (!full_pass)
		return 1;
	
	if (full_pass)
		return 0;
	
}