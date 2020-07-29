
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<any>
#include<sstream>
using namespace std;
class Logic {
public:
	Logic() = default;				//ȱʡ����
	double input(string& str) {		//API�����ʽ->���
		M_exp = Load(str);
		P_exp = trans(M_exp);
		return get_result(P_exp);
	}
	int get_priority(const char&); //API�������->���ȼ�
	string get_midExp() {		   //API����ȡ��׺���ʽ
		return show_exp(M_exp);
	}
	string get_postExp() {		   //API����ȡ��׺���ʽ
		return show_exp(P_exp);
	}

private:
	vector<any> Load(string);
	vector<any> trans(vector<any>&);                           //��׺ʽ->��׺ʽ
	double get_result(const vector<any>&);					   //���ݺ�׺ʽ��ȡ������
	string show_exp(vector<any>& exp);
	double calc(stack<double>&, const char& op);			  //��������
	vector<any> M_exp;                            //��׺ʽ
	vector<any> P_exp;                            //��׺ʽ
	string operators = "+-*%^/()";			     //�������
};
vector<any> Logic::Load(string str) {
	vector<any> m_exp;
	for (int i = 0; i < str.length(); i++) {
		string tmp;
		while ((str[i] == '-' && (i == 0 || operators.find(str[i - 1]) != string::npos)) || i < str.length() && operators.find(str[i]) == string::npos) {//���ڷ����������������ת��
			tmp += str[i];
			i++;
		}
		if (!tmp.empty())
			m_exp.push_back(stod(tmp));
		if (i != str.length())
			m_exp.push_back(str[i]);
	}
	return m_exp;
}
int Logic::get_priority(const char& ch) {
	if (ch == '^')	return 4;
	if (ch == '*' || ch == '/')		return 3;
	if (ch == '%')		return 2;
	if (ch == '+' || ch == '-')		return 1;
	if (ch == '(')		return -1;
	return 0;
}
string Logic::show_exp(vector<any>& exp) {
	ostringstream out;
	for (int i = 0; i < exp.size(); i++) {
		if (strcmp(exp[i].type().name(), "double") == 0)		//��������
			out << *exp[i]._Cast<double>() << " ";
		else
			out << *exp[i]._Cast<char>() << " ";
	}
	return out.str();
}

double Logic::get_result(const vector<any>& p_exp) {
	stack<double> res;            //��ջ��������
	double a, b;
	for (int i = 0; i < p_exp.size(); i++) {
		if (strcmp(p_exp[i].type().name(), "double") == 0)       //���������������ݡ��ֵ䡱�������ջ
			res.push(*p_exp[i]._Cast<double>());
		else
			res.push(calc(res, *p_exp[i]._Cast<char>()));
	}
	return res.top();
}
double Logic::calc(stack<double>& stk, const char& op) {
	double& a = stk.top(); stk.pop();
	double& b = stk.top(); stk.pop();
	if (op == '+') return a + b;
	else if (op == '-')return  b - a;
	else if (op == '*') return a * b;
	else if (op == '/') return b * a;
	else if (op == '^') return pow(b, a);
	else if (op == '%') return int(b) % int(a);
	return 0;
}

vector<any> Logic::trans(vector<any>& m_exp) {
	vector<any> p_exp;
	stack<char> stk;
	for (int i = 0; i < m_exp.size(); i++) {
		if (strcmp(m_exp[i].type().name(), "double") == 0)	//	������ֱ�Ӵ����׺ʽ��
			p_exp.push_back(*m_exp[i]._Cast<double>());
		else {
			char ch = *m_exp[i]._Cast<char>();
			if (ch == '(')
				stk.push(ch);
			else if (ch == ')') {
				while (stk.top() != '(') {
					p_exp.push_back(stk.top());
					stk.pop();
				}
				stk.pop();                         //����������
			}
			else {
				while ((!stk.empty()) && (get_priority(ch) <= get_priority(stk.top()))) {    //��ջ��Ϊ��ʱ���������ȼ��ж�
					p_exp.push_back(stk.top());   //����ǰ���������ȼ�����ջ��������ջ�����ŵ���׺ʽ��
					stk.pop();
				}
				stk.push(ch);             //����ǰ��������ջ
			}
		}
	}
	while (!stk.empty()) {    //��ջ��ʣ��������ŵ���׺ʽ��
		p_exp.push_back(stk.top());
		stk.pop();
	}
	return p_exp;
}
string calculater(string str) {
	Logic logic;
	string answer = to_string(logic.input(str));
	return answer;
}