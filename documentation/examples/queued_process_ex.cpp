#include <QueuedProcess.enh.h>
#include <iostream>

std::mutex mtxCout;

enh::Tristate process(enh::GenInstruct<int, std::string, std::string> msg)
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
	return enh::Tristate::GOOD;
}

int main()
{
	enh::QueuedProcess<enh::GenInstruct<int, std::string, std::string>> prc(process);
	prc.startQueueExecution();
	prc.postMessage({ 0,"con","cat" });
	prc.postMessage({ 1,"1this only","not this" });
	prc.postMessage({ 2,"not this ","2this only" });
	prc.postMessage({ 4,"","" });
	prc.joinAfterQueueEmpty(std::chrono::milliseconds(1));
	return 0;
}

/* ****************************************************************************

Output:
concat
1this only
2this only
error

******************************************************************************/