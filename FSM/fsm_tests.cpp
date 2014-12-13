#include <iostream>
#include "DFA.hpp"
#include "NFA.hpp"

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
	std::cout << "\nNFA TEST: " << std::endl;
	NFARulebook nfa_rulebook({
		FARule(1, 'a', 1), FARule(1, 'b', 1), FARule(1, 'b', 2),
		FARule(2, 'a', 3), FARule(2, 'b', 3), 
		FARule(3, 'a', 4), FARule(3, 'b', 4)
	});

	NFADesign nfa({ 1 }, {4}, nfa_rulebook);
	std::cout << "Should: true ";
	nfa.accepts("bab");
	std::cout << "Should: true ";
	nfa.accepts("bbbbb");
	std::cout << "Should: false ";
	nfa.accepts("bbabb");
	std::cout << "\nFree moves test: " << std::endl;
	NFARulebook free_moves_rulebook({
		FARule(1, '\0', 2),
		FARule(1, '\0', 4),
		FARule(2, 'a', 3),
		FARule(3, 'a', 2),
		FARule(4, 'a', 5),
		FARule(5, 'a', 6),
		FARule(6, 'a', 4)
	});
	NFADesign nfa_fm({ 1 }, {2, 4}, free_moves_rulebook);
	std::cout << "Should: true ";
	nfa_fm.accepts("aa");
	std::cout << "Should: true ";
	nfa_fm.accepts("aaa");
	std::cout << "Should: true ";
	nfa_fm.accepts("aaaa");
	std::cout << "Should: false ";
	nfa_fm.accepts("aaaaa");
	std::cout << "Should: true ";
	nfa_fm.accepts("aaaaaa");
	system("pause");
    return 0;
}

