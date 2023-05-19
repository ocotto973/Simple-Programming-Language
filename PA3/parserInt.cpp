/* Implementation of Recursive-Descent Parser
 * parserInt.cpp
 * Programming Assignment 3
 * Spring 2023
*/
//not different from old parser just add extra lines to each
#include "parserInt.h"
#include <string>
#include <queue>
#include <stack>
map<string, bool> defVar;
map<string, Token> SymTable;
map<string, Value> TempsResults; //Container of temporary locations of Value objects for results of expressions, variables values and constants 
queue <Value>* ValQue; //declare a pointer variable to a queue of Value objects
namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if (pushed_back) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem& t) {
		if (pushed_back) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;
	}

}

static int error_count = 0;

int ErrCount()
{
	return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << error_count << ". Line # " << line << ": " << msg << endl;
}
bool IdentList(istream& in, int& line);

bool isIn(map<string, bool> m, string s) {
	if (m.find(s) == m.end()) {
		return false;
	}
	else {
		return true;
	}
}

//Program is: Prog ::= StmtList
bool Prog(istream& in, int& line)
{
	bool f1;
	LexItem tok = Parser::GetNextToken(in, line);


	if (tok.GetToken() == DONE && tok.GetLinenum() <= 1) {
		ParseError(line, "Empty File");
		return true;
	}
	Parser::PushBackToken(tok);
	f1 = StmtList(in, line);

	if (!f1)
	{
		ParseError(line, "Missing Program");
		return false;
	}
	else
		return true;
}//End of Prog

//StmtList ::= Stmt; { Stmt; }
bool StmtList(istream& in, int& line) {
	bool status;

	LexItem tok;

	status = Stmt(in, line);
	while (status)
	{
		tok = Parser::GetNextToken(in, line);
		if (tok == DONE)
		{
			cout << "\n(" << "DONE" << ")" << endl;
			Parser::PushBackToken(tok);
			return true;
		}
		else if (tok == RBRACES)
		{
			Parser::PushBackToken(tok);
			return true;
		}

		if (tok != SEMICOL)
		{
			ParseError(line, "Missing semicolon at end of Statement.");
			return false;
		}

		status = Stmt(in, line);

	}

	tok = Parser::GetNextToken(in, line);
	if (!status) {
		return false;
	}
	if (tok == ELSE)
	{
		ParseError(line, "Missing right brace.");
		return false;
	}
	else if (tok == RBRACES)
	{
		Parser::PushBackToken(tok);
		return true;
	}

	else
	{
		ParseError(line, "Syntactic error in Program Body.");
		return false;
	}

}//End of StmtList function

//Stmt ::= AssignStme | WriteLnStmt | IfStmt  
bool Stmt(istream& in, int& line) {
	bool status = false;

	LexItem t = Parser::GetNextToken(in, line);

	switch (t.GetToken()) {
	case SIDENT: case NIDENT:
		Parser::PushBackToken(t);
		status = AssignStmt(in, line);
		if (!status)
		{
			ParseError(line, "Incorrect Assignment Statement.");
			return status;
		}
		break;
	case WRITELN:

		status = WritelnStmt(in, line);

		if (!status)
		{
			ParseError(line, "Incorrect Writeln Statement.");
			return status;
		}
		break;
	case IF:
		status = IfStmt(in, line);

		if (!status)
		{
			ParseError(line, "Incorrect If-Statement.");
			return status;
		}
		break;
	case ELSE:
		Parser::PushBackToken(t);
		return false;
		break;
	case IDENT:
		ParseError(line, "Invalid variable name");

		Parser::PushBackToken(t);
		return false;
		break;
	default:
		Parser::PushBackToken(t);
		return true;
	}
	return status;
}//End of Stmt function

//WritelnStmt:= WRITELN (ExpreList) 
bool WritelnStmt(istream& in, int& line) {
	LexItem t;
	ValQue = new queue<Value>;

	t = Parser::GetNextToken(in, line);
	if (t != LPAREN) {

		ParseError(line, "Missing Left Parenthesis of Writeln Statement");
		return false;
	}

	bool ex = ExprList(in, line);

	if (!ex) {
		ParseError(line, "Missing expression list after Print");
		while (!(*ValQue).empty())
		{
			ValQue->pop();
		}
		delete ValQue;
		return false;
	}

	//Evaluate: writeln by printing out the list of expressions' values
	while (!(*ValQue).empty())
	{
		Value nextVal = (*ValQue).front();
		cout << nextVal;
		ValQue->pop();
	}
	cout << endl;

	t = Parser::GetNextToken(in, line);
	if (t != RPAREN) {

		ParseError(line, "Missing Right Parenthesis of Writeln Statement");
		return false;
	}
	return true;
}//End of WritelnStmt

bool IfStmt(istream& in, int& line) {
	bool ex = false, status;
	LexItem t;
	t = Parser::GetNextToken(in, line);
	if (t != LPAREN) {

		ParseError(line, "Missing Left Parenthesis of If condition");
		return false;
	}
	Value retVal;
	ex = Expr(in, line, retVal);
	if (!ex) {
		ParseError(line, "Missing if statement Logic Expression");
		return false;
	}
	

	t = Parser::GetNextToken(in, line);
	if (t != RPAREN) {

		ParseError(line, "Missing Right Parenthesis of If condition");
		return false;
	}
	if (retVal.GetType() != VBOOL) {
		ParseError(line, "Illegal Type for If statement condition.");
		return false;
	}
	if (retVal.GetBool() == true) {
		t = Parser::GetNextToken(in, line);
		if (t != LBRACES)
		{
			ParseError(line, "If Statement Syntax Error: Missing left brace");
			return false;
		}
		status = StmtList(in, line);
		if (!status)
		{
			ParseError(line, "Missing Statement for If-Stmt Clause");
			return false;
		}
		t = Parser::GetNextToken(in, line);
		if (t != RBRACES)
		{
			ParseError(line, "If Statement Syntax Error: Missing right brace.");
			return false;
		}
		t = Parser::GetNextToken(in, line);
		if (t == ELSE) {
			t = Parser::GetNextToken(in, line);
			if (t != LBRACES) {
				ParseError(line, "If Statement Syntax Error: Missing left brace");
				return false;
			}
			t = Parser::GetNextToken(in, line);
			while (t != RBRACES) {
				t = Parser::GetNextToken(in, line);
			}
		}
		else {
			Parser::PushBackToken(t);
		}
	}
	else {
		while (t != ELSE) {
			t = Parser::GetNextToken(in, line);
		}
		if (t == ELSE) {
			t = Parser::GetNextToken(in, line);
			if (t != LBRACES)
			{
				ParseError(line, "If Statement Syntax Error: Missing left brace");
				return false;
			}
			status = StmtList(in, line);
			if (!status)
			{
				ParseError(line, "Missing Statement for Else-Clause");
				return false;
			}
			t = Parser::GetNextToken(in, line);
			if (t != RBRACES)
			{
				Parser::PushBackToken(t);
				ParseError(line, "If Statement Syntax Error: Missing right brace.");
				return false;
			}
			//Parser::PushBackToken(t);
		}
		else
		{
			Parser::PushBackToken(t);
			return true;
		}
	}
	return true;
}//End of IfStmt function

//AssignStmt:= Var = Expr
bool AssignStmt(istream& in, int& line) {
	bool varstatus = false, 
	status = false;
	LexItem t = Parser::GetNextToken(in,line);
	Parser::PushBackToken(t);
	Value retVal;
	varstatus = Var(in, line, t);

	if (varstatus) {
		LexItem varTok = t; //left hand side variable
		t = Parser::GetNextToken(in, line);

		if (t == ASSOP) {
			status = Expr(in, line, retVal);

			if (!status) {
				ParseError(line, "Missing Expression in Assignment Statement");
				return status;
			}

			if(varTok.GetToken()== NIDENT){
				if (retVal.GetType() != VINT && retVal.GetType() != VREAL) {
					ParseError(line, "Invalid assignment statement conversion of a string value to a double variable.");
					return false;
				}	
			}
			if (varTok.GetToken() == NIDENT || varTok.GetToken() == SIDENT) {
				if (retVal.GetType() == VBOOL) {
					ParseError(line, "Invalid assignment statement conversion of a string value to a double variable.");
					return false;
				}
			}
			TempsResults[varTok.GetLexeme()] = retVal;
			
		}
		else if (t.GetToken() == ERR) {
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << t.GetLexeme() << ")" << endl;
			return false;
		}
		else {
			ParseError(line, "Missing Assignment Operator");
			return false;
		}
	}
	else {
		ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
		return false;
	}
	return status;
}//End of AssignStmt
//Var ::= NIDENT | SIDENT
bool Var(istream& in, int& line, LexItem& idtok) { //idtok is left side of equal sign when assigning variable
	string identstr;

	LexItem tok = Parser::GetNextToken(in, line);
	if (tok == NIDENT || tok == SIDENT) {
		identstr = tok.GetLexeme();

		if (!(isIn(defVar,identstr)))
		{
			defVar[identstr] = true;
			SymTable[identstr] = tok.GetToken();
		}
		return true;
	}
	else if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");

		return false;
	}

	return false;
}//End of Var



//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
	bool status = false;
	Value retVal;

	status = Expr(in, line, retVal);
	if (!status) {
		ParseError(line, "Missing Expression");
		return false;
	}
	ValQue->push(retVal);
	LexItem tok = Parser::GetNextToken(in, line);

	if (tok == COMMA) {
		status = ExprList(in, line);
	}
	else if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else {
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}//End of ExprList
bool Expr(istream& in, int& line, Value& retVal) {
	LexItem tok;
	bool t1 = RelExpr(in, line, retVal);

	if (!t1) {
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if (tok == NEQ || tok == SEQ){
		Value leftVal = retVal;
		t1 = RelExpr(in, line, retVal);
		if (!t1)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		if (tok == NEQ) {
			retVal = leftVal == retVal;
		}
		else {
			retVal = leftVal.SEqual(retVal);
		}
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR) {
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
}//End of Expr/EqualExpr

//RelExpr ::= AddExpr [ ( -LT | -GT | < | > )  AddExpr ]
bool RelExpr(istream& in, int& line, Value& retVal) {
	LexItem tok;
	bool t1 = AddExpr(in, line, retVal);

	if (!t1) {
		return false;
	}
	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if (tok == NGTHAN || tok == NLTHAN || tok == SGTHAN || tok == SLTHAN)
	{
		Value leftVal = retVal;
		t1 = AddExpr(in, line, retVal);
		if (!t1)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		if (tok == SGTHAN) {
			retVal = leftVal.SGthan(retVal);
		}
		else if (tok == SLTHAN) {
			retVal = leftVal.SLthan(retVal);
		}
		else if (tok == NGTHAN) {
			retVal = leftVal > retVal;
		}
		else {
			retVal = leftVal < retVal;
		}
		if (retVal.GetType() == VERR) {
			ParseError(line, "Illegal Opperand Type for the operation.");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR) {
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}

	Parser::PushBackToken(tok);
	return true;
}//End of RelExpr

//AddExpr :: MultExpr { ( + | - | .) MultExpr }
bool AddExpr(istream& in, int& line, Value& retVal) {
	bool t1 = MultExpr(in, line, retVal);
	LexItem tok;

	if (!t1) {
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while (tok == PLUS || tok == MINUS || tok == CAT)
	{
		Value leftVal = retVal;
		t1 = MultExpr(in, line, retVal);
		if (!t1)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		if (tok == PLUS) {
			retVal = leftVal + retVal;
		}
		else if (tok == MINUS) {
			retVal = leftVal - retVal;
		}
		else {
			retVal = leftVal.Catenate(retVal);
		}
		if (retVal.GetType() == VERR) {
			ParseError(line, "Illegal Opperand Type for the operation.");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR) {
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
}//End of AddExpr

//MultExpr ::= ExponExpr { ( * | / | **) ExponExpr }
bool MultExpr(istream& in, int& line, Value& retVal) {
	bool t1 = ExponExpr(in, line, retVal);
	LexItem tok;

	if (!t1) {
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while (tok == MULT || tok == DIV || tok == SREPEAT)
	{
		Value leftVal = retVal;
		t1 = ExponExpr(in, line, retVal);

		if (!t1) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
		if (tok == MULT) {
			retVal = leftVal * retVal;
		}
		else if (tok == DIV) {
			retVal = leftVal / retVal;
		}
		else if (tok == SREPEAT) {
			retVal = leftVal.Repeat(retVal);
			
		}
		if (retVal.GetType() == VERR) {
			ParseError(line, "Illegal Opperand Type for the operation.");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR) {
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
}//End of MultExpr

//ExponExpr ::= UnaryExpr { ^ UnaryExpr }
//enforcing right associativity using right recursiveness
bool ExponExpr(istream& in, int& line, Value& retVal) {
	bool status;
	status = UnaryExpr(in, line, retVal);
	if (!status) {
		return false;
	}

	LexItem tok = Parser::GetNextToken(in, line);
	if (tok == EXPONENT)
	{
		Value leftVal = retVal;
		status = ExponExpr(in, line, retVal);
		if (!status) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
		retVal = leftVal ^ retVal;
		if (retVal.GetType() == VERR) {
			ParseError(line, "Illegal Opperand Type for the operation.");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR) {
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	else if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	Parser::PushBackToken(tok);
	return true;
}//End of ExponExpr

//UnaryExpr ::= ( - | + ) PrimaryExpr | PrimaryExpr
bool UnaryExpr(istream& in, int& line, Value& retVal) {
	LexItem t = Parser::GetNextToken(in, line);
	bool status;
	int sign = 0;
	if (t == MINUS)
	{
		sign = -1;
	}
	else if (t == PLUS)
	{
		sign = 1;
	}
	else
		Parser::PushBackToken(t);

	status = PrimaryExpr(in, line, sign, retVal);
	return status;
}//End of UnaryExpr


//PrimaryExpr ::= IDENT | NIDENT | SIDENT | ICONST | RCONST | SCONST | ( Expr )
bool PrimaryExpr(istream& in, int& line, int sign, Value& retVal) {
	LexItem tok = Parser::GetNextToken(in, line);

	if (tok == NIDENT || tok == SIDENT) {
		string lexeme = tok.GetLexeme();
		if (!(isIn(defVar, lexeme)))
		{
			ParseError(line, "Using Undefined Variable");
			return false;
		}
		if (sign != 0 && tok == NIDENT) {
			if (TempsResults[lexeme].GetType() == VREAL) {
				Value v = TempsResults[lexeme];
				lexeme = to_string(v.GetReal() * sign);
				retVal.SetType(VREAL);
				retVal.SetReal(stod(lexeme));
				return true;
			}
		}
		retVal.SetType(TempsResults[lexeme].GetType());
		if (TempsResults[lexeme].GetType() == VINT) {
			retVal.SetInt(TempsResults[lexeme].GetInt());
		}
		else if (TempsResults[lexeme].GetType() == VREAL) {
			retVal.SetReal(TempsResults[lexeme].GetReal());
		}
		else if (TempsResults[lexeme].GetType() == VSTRING) {
			retVal.SetString(TempsResults[lexeme].GetString());
		}
		return true;
	}
	else if (tok == ICONST) {
		/*if (sign != 0) {
			tok.GetLexeme() = to_string(stod(tok.GetLexeme()) * sign);
		}*/
		retVal.SetType(VREAL);
		retVal.SetReal(stod(tok.GetLexeme()));
		return true;
	}
	//maybe something with symtable???
	else if (tok == SCONST) {
		if (sign != 0) {
			ParseError(line, "Illegal Operand Type for Sign Operator");
			return false;
		}
		retVal.SetType(VSTRING);
		retVal.SetString(tok.GetLexeme());
		return true;
	}
	else if (tok == RCONST) {
		string lexeme = tok.GetLexeme();
		if (lexeme[lexeme.length() - 1] == '.') { //check if last character is . , if it is make it a int instead.
			retVal.SetType(VINT);
			retVal.SetInt(stoi(tok.GetLexeme()));
		}
		else {
			retVal.SetType(VREAL);
			retVal.SetReal(stod(tok.GetLexeme()));
		}
		return true;
	}
	else if (tok == LPAREN) {
		bool ex = Expr(in, line, retVal);
		if (!ex) {
			ParseError(line, "Missing expression after Left Parenthesis");
			return false;
		}
		if (Parser::GetNextToken(in, line) == RPAREN)
			return ex;
		else
		{
			Parser::PushBackToken(tok);
			ParseError(line, "Missing right Parenthesis after expression");
			return false;
		}
	}
	else if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}

	return false;
}