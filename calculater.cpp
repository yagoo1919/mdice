
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<any>
#include<sstream>
using namespace std;
class Logic {
public:
	Logic() = default;				//缺省构造
	double input(string& str) {		//API：表达式->结果
		M_exp = Load(str);
		P_exp = trans(M_exp);
		return get_result(P_exp);
	}
	int get_priority(const char&); //API：运算符->优先级
	string get_midExp() {		   //API：获取中缀表达式
		return show_exp(M_exp);
	}
	string get_postExp() {		   //API：获取后缀表达式
		return show_exp(P_exp);
	}

private:
	vector<any> Load(string);
	vector<any> trans(vector<any>&);                           //中缀式->后缀式
	double get_result(const vector<any>&);					   //根据后缀式获取计算结果
	string show_exp(vector<any>& exp);
	double calc(stack<double>&, const char& op);			  //基础运算
	vector<any> M_exp;                            //中缀式
	vector<any> P_exp;                            //后缀式
	string operators = "+-*%^/()";			     //运算符集
};
vector<any> Logic::Load(string str) {
	vector<any> m_exp;
	for (int i = 0; i < str.length(); i++) {
		string tmp;
		while ((str[i] == '-' && (i == 0 || operators.find(str[i - 1]) != string::npos)) || i < str.length() && operators.find(str[i]) == string::npos) {//对于非运算符，进行数字转换
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
		if (strcmp(exp[i].type().name(), "double") == 0)		//数据类型
			out << *exp[i]._Cast<double>() << " ";
		else
			out << *exp[i]._Cast<char>() << " ";
	}
	return out.str();
}

double Logic::get_result(const vector<any>& p_exp) {
	stack<double> res;            //此栈用作运算
	double a, b;
	for (int i = 0; i < p_exp.size(); i++) {
		if (strcmp(p_exp[i].type().name(), "double") == 0)       //遇到操作数，根据“字典”翻译后入栈
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
		if (strcmp(m_exp[i].type().name(), "double") == 0)	//	操作数直接存入后缀式中
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
				stk.pop();                         //弹出左括号
			}
			else {
				while ((!stk.empty()) && (get_priority(ch) <= get_priority(stk.top()))) {    //当栈不为空时，进行优先级判断
					p_exp.push_back(stk.top());   //若当前操作符优先级低于栈顶，弹出栈顶，放到后缀式中
					stk.pop();
				}
				stk.push(ch);             //将当前操作符入栈
			}
		}
	}
	while (!stk.empty()) {    //将栈中剩余操作符放到后缀式中
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