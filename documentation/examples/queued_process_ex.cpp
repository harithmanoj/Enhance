#include <queued_process.enh.h>
#include <iostream>

std::mutex mtxCout;

enh::tristate process(enh::gen_instruct<int, std::string, std::string> msg)
{
	std::lock_guard<std::mutex> lock(mtxCout);
	if (msg.op == 0)
		std::cout << msg.lParam + msg.uParam << "\n";
	else if (msg.op == 1)
		std::cout << msg.lParam << "\n";
	else if (msg.op == 2)
		std::cout << msg.uParam << "\n";
	else
		std::cout << "error\n";
	return enh::tristate::GOOD;
}

int main()
{
	enh::queued_process<enh::gen_instruct<int, std::string, std::string>> prc(process);
	prc.start_queue_process();
	prc.postMessage({ 0,"con","cat" });
	prc.postMessage({ 1,"1this only","not this" });
	prc.postMessage({ 2,"not this ","2this only" });
	prc.postMessage({ 4,"","" });
	prc.WaitForQueueEmpty(std::chrono::milliseconds(1));
	prc.stopQueue();
	prc.WaitForQueueStop();
}

/* ****************************************************************************

Output:
concat
1this only
2this only
error

******************************************************************************/