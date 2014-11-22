#include <iostream>
#include "dfa.hpp"
#include "nfa.hpp"
using namespace std;



int main()
{
	std::cout << "DFA TEST: " << std::endl;
	DFARulebook dfa_rulebook({
		FARule(1, 'a', 2), FARule(1, 'b', 1),
		FARule(2, 'a', 2), FARule(2, 'b', 3),
		FARule(3, 'a', 3), FARule(3, 'b', 3)
	});
	DFADesign dfa(1, {3}, dfa_rulebook);
	dfa.accepts("a");
	dfa.accepts("baa");
	dfa.accepts("baba");
	std::cout << "NFA TEST: " << std::endl;
	NFARulebook nfa_rulebook({
		FARule(1, 'a', 1), FARule(1, 'b', 1), FARule(1, 'b', 2),
		FARule(2, 'a', 3), FARule(2, 'b', 3), 
		FARule(3, 'a', 4), FARule(3, 'b', 4)
	});

	NFADesign nfa({ 1 }, {4}, nfa_rulebook);
	nfa.accepts("bab");
	nfa.accepts("bbbbb");
	nfa.accepts("bbabb");
	system("pause");
    return 0;
}

