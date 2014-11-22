#ifndef DFA_H_
#define DFA_H_
#include<set>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<memory>

class FARule {
private:
	unsigned int m_state;
	unsigned int m_next_state;
	char m_litera;
public:
	FARule() :FARule(0, 0, 0) {}
	FARule(unsigned int a_state, char a_litera, unsigned int a_next_state) :
		m_state(a_state),
		m_litera(a_litera),
		m_next_state(a_next_state){}

	bool applies_to(unsigned int a_state, char a_litera) {
		return m_state == a_state && m_litera == a_litera;
	}

	const unsigned int state() {
		return m_state;
	}

	const char litera() {
		return m_litera;
	}

	const unsigned int follow() {
		return m_next_state;
	}

	void inspect() {
		std::cout << "FARule: " << m_state << "--" << m_litera << "-->" << m_next_state << std::endl;
	}
};

class DFARulebook {
public:
	DFARulebook(std::vector<FARule> a_rules) :
		m_rules(a_rules)
	{ }

	unsigned int next_state(const unsigned int a_state, const char a_litera) {
		auto rule = rule_for(a_state, a_litera);
#ifdef _DEBUG
		rule->inspect();
#endif
		return rule->follow();
	}

private:
	std::vector<FARule> m_rules;
	const std::vector<FARule>::iterator rule_for(unsigned int a_state, char a_litera) {
		auto result = std::find_if(m_rules.begin(), m_rules.end(), [&](FARule a_it)->bool{
			return a_it.applies_to(a_state, a_litera);
		});

		return result;
	}
};

class DFA {
private:
	unsigned int m_current_state;
	std::set<unsigned int> m_accept_states;
	DFARulebook m_rulebook;
public:
	DFA(unsigned int a_start_state, std::set<unsigned int> an_accept_states, DFARulebook a_rulebook) :
		m_current_state(a_start_state),
		m_accept_states(an_accept_states),
		m_rulebook(a_rulebook)
	{	}

	void read_string(const std::string a_program){
		for (char litera : a_program) {
			read_character(litera);
		}
	}

	void read_character(const char a_litera) {
		m_current_state = m_rulebook.next_state(m_current_state, a_litera);
	}

	bool accepting() {
		bool isAccepting = m_accept_states.find(m_current_state) != m_accept_states.end();
#ifdef _DEBUG
		std::cout << "DFA accepting state ";
		if (isAccepting)
			std::cout << "true";
		else
			std::cout << "false";
		std::cout << std::endl;
#endif
		return isAccepting;
	}
};

class DFADesign{
private:
	unsigned int m_current_state;
	std::set<unsigned int> m_accept_states;
	DFARulebook m_rulebook;
public:
	DFADesign(unsigned int a_current_state, std::set<unsigned int> an_accept_state, DFARulebook a_rulebook) :
		m_current_state(a_current_state),
		m_accept_states(an_accept_state),
		m_rulebook(a_rulebook)
	{}

	std::unique_ptr<DFA> to_dfa() {
		std::unique_ptr<DFA> temp(new DFA(m_current_state, m_accept_states, m_rulebook));
		return temp;
	}

	bool accepts(std::string a_program) {
		std::unique_ptr<DFA> temp = to_dfa();
		temp->read_string(a_program);
		return temp->accepting();
	}
};
#endif