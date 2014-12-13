#ifndef FARULE_H_
#define FARULE_H_
#include<iostream>

class FARule {
private:
	unsigned int m_state;
	unsigned int m_next_state;
	char m_litera;
public:
	FARule():FARule(0, '\0', 0) {}
	FARule(unsigned int a_state, char a_litera, unsigned int a_next_state) :
		m_state(a_state),
		m_litera(a_litera),
		m_next_state(a_next_state){}

	bool applies_to(unsigned int a_state, char a_litera) {
		return m_state == a_state && m_litera == a_litera;
	}

	unsigned int state() {
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

#endif