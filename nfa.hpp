#include<vector>
#include<set>
#include"dfa.hpp"

// нига правил дл€ недетерменированного конечного автомата
class NFARulebook {
public:
	NFARulebook(std::vector<FARule> a_rules) :
		m_rules(a_rules)
	{ }

	std::set<unsigned int> next_states(const std::set<unsigned int> a_states, const char a_litera) {
		std::set<unsigned int> result;
		for (unsigned int state : a_states) {
			unsigned int next_state = rule_for(state, a_litera)->follow();
			result.insert(next_state);
		}

		return result;
	}

	const std::vector<FARule>::iterator rule_for(unsigned int a_state, char a_litera) {
		auto result = std::find_if(m_rules.begin(), m_rules.end(), [&](FARule a_it)->bool{
			return a_it.applies_to(a_state, a_litera);
		});

		return result;
	}

private:
	std::vector<FARule> m_rules;
};

//Ќе детерменированный конечный автомат
class NFA {
public:
	NFA (std::set<unsigned int> a_current_states, std::set<unsigned int> an_accept_states, NFARulebook a_rulebook):
		m_current_states(a_current_states),
		m_accept_states(an_accept_states),
		m_rulebook(a_rulebook)
	{ }
	bool accepting() {
		return true;
	}
private:
	std::set<unsigned int> m_current_states;
	std::set<unsigned int> m_accept_states;
	NFARulebook m_rulebook;
};