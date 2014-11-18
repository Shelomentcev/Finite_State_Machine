#include <iostream>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class FARule {
private:
    unsigned int m_state;
    unsigned int m_next_state;
    char m_litera;
public:
    FARule():FARule(0, 0, 0) {}
    FARule(unsigned int a_state, char a_litera, unsigned int a_next_state):
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
        cout << "FARule: " << m_state << "--" << m_litera << "-->" << m_next_state << endl;
    }
};

class DFARulebook {
public:
    DFARulebook(vector<FARule> a_rules) {
        m_rules = a_rules;
	}

    const unsigned int next_state(const unsigned int a_state, const char a_litera) {
		auto rule = rule_for(a_state, a_litera);
#ifdef _DEBUG
		rule->inspect();
#endif
		return rule->follow();
	}

private:
	vector<FARule> m_rules;
    const vector<FARule>::iterator rule_for(unsigned int a_state, char a_litera) {
		auto result = find_if(m_rules.begin(), m_rules.end(), [&](FARule a_it)->bool{
			return a_it.applies_to(a_state, a_litera);
		});
		
		return result;
    }
};

int main()
{
	DFARulebook rulebook({
		FARule(1, 'a', 2), FARule(1, 'b', 1),
		FARule(2, 'a', 2), FARule(2, 'b', 3),
		FARule(3, 'a', 3), FARule(3, 'b', 3)
	});

	cout << rulebook.next_state(1, 'a') << endl;

    system("pause");
    return 0;
}

