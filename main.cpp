#include <iostream>
#include "dfa.hpp"
using namespace std;



int main()
{
	DFARulebook rulebook({
		FARule(1, 'a', 2), FARule(1, 'b', 1),
		FARule(2, 'a', 2), FARule(2, 'b', 3),
		FARule(3, 'a', 3), FARule(3, 'b', 3)
	});

	DFADesign dfa(1, {3}, rulebook);
	dfa.accepts("a");
	dfa.accepts("baa");
	dfa.accepts("baba");;
    system("pause");
    return 0;
}

