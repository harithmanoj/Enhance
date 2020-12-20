#include <ConfinedValue.enh.h>
#include <iostream>


int main()
{
	unsigned foo = 50;
	unsigned bar = 1;
	enh::confined_base<unsigned> b(
		[&foo](long long a) {
			return (a <= foo);
		},
		[&bar](long long a) {
			return (a >= bar);
		},
		[&foo]() {
			return foo;
		},
		[&bar]() {
			return bar;
		});

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			std::cout << i << " " << j << " " << b.get() << "\n";
			b.add(20);
		}
		foo += 10;
		bar += 5;
		b.re_eval();
	}

	return 0;
}

/* ****************************************************************************

Output:

0 0 1
0 1 21
0 2 41
0 3 11
0 4 31
1 0 6
1 1 26
1 2 46
1 3 11
1 4 31
2 0 51
2 1 11
2 2 31
2 3 51
2 4 11
3 0 31
3 1 51
3 2 71
3 3 26
3 4 46
4 0 66
4 1 86
4 2 36
4 3 56
4 4 76


******************************************************************************/