#include <iostream>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class FARule {
    unsigned int m_state;
    unsigned int m_next_state;
    char m_litera;
public:
    FARule():
    FARule(0, 0, 0)//Надо придумать что-то другое
    {}
    FARule(unsigned int a_state, char a_litera, unsigned int a_next_state):
    m_state(a_state),
    m_litera(a_litera),
    m_next_state(a_next_state){}

    bool applies_to(unsigned int a_state, char a_litera) {
        return m_state == a_state && m_litera == a_litera;
    }

    unsigned int state() {
        return m_state;
    }

    char litera() {
        return m_litera;
    }

    unsigned int follow() {
        return m_next_state;
    }

    void inspect() {
        cout << "FARule " << m_state << "--" << m_litera << "--> " << m_next_state;
    }
};

class DFARulebook {
    vector<FARule> m_rules;
    DFARulebook(vector<FARule> a_rules) {
        m_rules = a_rules;
    }
    unsigned int next_state(unsigned int a_state, char a_litera) {

    }
private:
    FARule rule_for(unsigned int a_state, char a_litera) {
        return find_if(m_rules.begin(), m_rules.end(), [a_state, a_litera](FARule a_it){
            return a_it.applies_to(a_state, a_litera);
        });
    }
};

class FSM {
public:

};

int main()
{

    system("pause");
    return 0;
}

