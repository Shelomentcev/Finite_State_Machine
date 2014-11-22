#ifndef NFA_H_ 
#define NFA_H_

#include<vector>
#include<set>
#include"dfa.hpp"

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

class NFA {
public:
	NFA(std::set<unsigned int> a_current_states, std::set<unsigned int> an_accept_states, NFARulebook a_rulebook) :
		m_current_states(a_current_states),
		m_accept_states(an_accept_states),
		m_rulebook(a_rulebook)
	{ }

	bool accepting() {

		//std::set<unsigned int> intersect_result;
		//std::set<unsigned int>::iterator it = std::set_intersection(m_current_states.begin(), m_current_states.end(),
		//	m_accept_states.begin(), m_accept_states.end(), intersect_result.begin());
		
		//return !intersect_result.empty();
		for (auto accept_state : m_accept_states) {
			for (auto current_state : m_current_states) {
				if (accept_state == current_state) {
#ifdef _DEBUG
					std::cout << "true" << std::endl;
#endif
					return true;
				}
			}
		}
#ifdef _DEBUG
		std::cout << "false" << std::endl;
#endif
		return false;
	}

	void read_character(const char a_litera) {
		m_current_states = m_rulebook.next_states(m_current_states, a_litera);
	}

	void read_string(const std::string a_program){
		for (char litera : a_program) {
			read_character(litera);
		}
	}
private:
	std::set<unsigned int> m_current_states;
	std::set<unsigned int> m_accept_states;
	NFARulebook m_rulebook;
};

class NFADesign{
public:
	NFADesign(std::set<unsigned int> a_current_states,
		std::set<unsigned int> a_accept_states,
		NFARulebook a_rulebook) :
		m_current_states(a_current_states), m_accept_states(a_accept_states), m_rulebook(a_rulebook)
	{ }

	std::unique_ptr<NFA> to_nfa() {
		std::unique_ptr<NFA> temp(new NFA(m_current_states, m_accept_states, m_rulebook));
		return temp;
	}

	bool accepts(std::string a_program) {
		std::unique_ptr<NFA> temp = to_nfa();
		temp->read_string(a_program);
		return temp->accepting();
	}
private:
	std::set<unsigned int> m_current_states;
	std::set<unsigned int> m_accept_states;
	NFARulebook m_rulebook;
};
#endif