#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include "val.h"

Value Value::operator+(const Value& op)const {

	if (IsReal() && op.IsReal()) {
		return Value(GetReal() + op.GetReal());
	}
	else if (IsInt() && op.IsReal()) {
		return Value(GetInt() + op.GetReal());
	}
	else if (IsReal() && op.IsInt()) {
		return Value((GetReal() + op.GetInt()));
	}
	else if ((IsReal() && op.IsString())) {
		try {
			return Value(GetReal() + stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsInt() && op.IsString())) {
		try {
			return Value(GetInt() + stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsReal())) {
		try {
			return Value(stod(GetString()) + op.GetReal());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsInt())) {
		try {
			return Value(stod(GetString()) + op.GetInt());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsString())) {
		try {
			return Value(stod(GetString()) + stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if (IsInt() && op.IsInt()) {
		return Value(GetInt() + op.GetInt());
	}
	else {
		return Value();
	}
}

Value Value::operator-(const Value& op)const {

	if (IsReal() && op.IsReal()) {
		return Value(GetReal() - op.GetReal());
	}
	else if (IsInt() && op.IsReal()) {
		return Value(GetInt() - op.GetReal());
	}
	else if (IsReal() && op.IsInt()) {
		return Value((GetReal() - op.GetInt()));
	}
	else if ((IsReal() && op.IsString())) {
		try {
			return Value(GetReal() - stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsInt() && op.IsString())) {
		try {
			return Value(GetInt() - stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsReal())) {
		try {
			return Value(stod(GetString()) - op.GetReal());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsInt())) {
		try {
			return Value(stod(GetString()) - op.GetInt());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsString())) {
		try {
			return Value(stod(GetString()) - stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if (IsInt() && op.IsInt()) {
		return Value(GetInt() - op.GetInt());
	}
	else {
		return Value();
	}
}

Value Value::operator*(const Value& op)const {
	
	if (IsReal() && op.IsReal()) {
		return Value(GetReal() * op.GetReal());
	}
	else if (IsInt() && op.IsReal()) {
		return Value(GetInt() * op.GetReal());
	}
	else if (IsReal() && op.IsInt()) {
		return Value((GetReal() * op.GetInt()));
	}
	else if ((IsReal() && op.IsString())) {
		try {
			return Value(GetReal() * stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsInt() && op.IsString())) {
		try {
			return Value(GetInt() * stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsReal())) {
		try {
			return Value(stod(GetString()) * op.GetReal());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsInt())) {
		try {
			return Value(stod(GetString()) * op.GetInt());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsString())) {
		try {
			return Value(stod(GetString()) * stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if (IsInt() && op.IsInt()) {
		return Value(double(GetInt() * op.GetInt()));
	}
	else {
		return Value();
	}
}

Value Value::operator/(const Value& op)const {

	if (IsReal() && op.IsReal()) {
		if (op.GetReal() == 0) {
			cout << "Divide by 0 error";
			return Value();
		}
		return Value(GetReal() / op.GetReal());
	}
	else if (IsInt() && op.IsReal()) {
		if (op.GetReal() == 0) {
			cout << "Divide by 0 error";
			return Value();
		}
		return Value(GetInt() / op.GetReal());
	}
	else if (IsReal() && op.IsInt()) {
		if (op.GetInt() == 0) {
			cout << "Divide by 0 error";
			return Value();
		}
		return Value((GetReal() / op.GetInt()));
	}
	else if ((IsReal() && op.IsString())) {
		try {
			if (stod(op.GetString()) == 0) {
				cout << "Divide by 0 error";
				return Value();
			}
			return Value(GetReal() / stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsInt() && op.IsString())) {
		try {
			if (stod(op.GetString()) == 0) {
				cout << "Divide by 0 error";
				return Value();
			}
			return Value(GetInt() / stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsReal())) {
		try {
			if (op.GetReal() == 0) {
				cout << "Divide by 0 error";
				return Value();
			}
			return Value(stod(GetString()) / op.GetReal());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsInt())) {
		try {
			if (op.GetReal() == 0) {
				cout << "Divide by 0 error";
				return Value();
			}
			return Value(stod(GetString()) / op.GetInt());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsString())) {
		try {
			if (stod(op.GetString()) == 0) {
				cout << "Divide by 0 error";
				return Value();
			}
			return Value(stod(GetString()) / stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else {
		return Value();
	}
}

Value Value::operator==(const Value& op)const {
	if (IsReal() && op.IsReal()) {
		return Value(GetReal() == op.GetReal());
	}
	else if (IsReal() && op.IsInt()) {
		return Value(GetReal() == op.GetInt());
	}
	else if (IsReal() && op.IsString()) {
		try {
			return Value(GetReal() == stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if (IsString() && op.IsReal()) {
		try {
			return Value(stod(GetString()) == op.GetReal());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if (IsString() && op.IsString()) {
		try {
			return Value(stod(GetString()) == stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else {
		return Value();
	}
}

Value Value::operator>(const Value& op)const {

	if (IsReal() && op.IsReal()) {
		return Value(GetReal() > op.GetReal());
	}
	else if (IsInt() && op.IsReal()) {
		return Value(GetInt() > op.GetReal());
	}
	else if (IsReal() && op.IsInt()) {
		return Value((GetReal() > op.GetInt()));
	}
	else if ((IsReal() && op.IsString())) {
		try {
			return Value(GetReal() > stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsInt() && op.IsString())) {
		try {
			return Value(GetInt() > stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsReal())) {
		try {
			return Value(stod(GetString()) > op.GetReal());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsInt())) {
		try {
			return Value(stod(GetString()) > op.GetInt());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsString())) {
		try {
			return Value(stod(GetString()) > stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else {
		return Value();
	}
}

Value Value::operator<(const Value& op)const {

	if (IsReal() && op.IsReal()) {
		return Value(GetReal() < op.GetReal());
	}
	else if (IsInt() && op.IsReal()) {
		return Value(GetInt() < op.GetReal());
	}
	else if (IsReal() && op.IsInt()) {
		return Value((GetReal() < op.GetInt()));
	}
	else if ((IsReal() && op.IsString())) {
		try {
			return Value(GetReal() < stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsInt() && op.IsString())) {
		try {
			return Value(GetInt() < stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsReal())) {
		try {
			return Value(stod(GetString()) < op.GetReal());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsInt())) {
		try {
			return Value(stod(GetString()) < op.GetInt());
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else if ((IsString() && op.IsString())) {
		try {
			return Value(stod(GetString()) < stod(op.GetString()));
		}
		catch (invalid_argument& arg) {
			cout << "Invalid conversion from string to double." << endl;
			return Value();
		}
	}
	else {
		return Value();
	}
}

Value Value ::operator^(const Value & oper) const {
	if (IsReal() && oper.IsReal()) {
		return Value(pow(GetReal(), oper.GetReal()));
	}
	/*else if (IsReal() && oper.IsString()) {
		try {
			return Value(pow(GetReal(), stod(oper.GetString())));
		}
		catch (invalid_argument& arg) {
			return Value();
		}
	}
	else if (IsString() && oper.IsReal()) {
		try {
			return Value(pow(stod(GetString()), oper.GetReal()));
		}
		catch (invalid_argument& arg) {
			return Value();
		}
	}*/
	else if (IsInt() && oper.IsInt()) {
		return Value(pow(GetInt(), oper.GetInt()));
	}
	else if (IsReal() && oper.IsInt()) {
		return Value(pow(GetReal(), oper.GetInt()));
	}
	else if (IsInt() && oper.IsReal()) {
		return Value(pow(GetInt(), oper.GetReal()));
	}
	else {
		return Value();
	}
}

Value Value::Catenate(const Value& oper) const {
	if (IsString() && oper.IsReal()) {
		try {
			string s1 = to_string(oper.GetReal());
			s1.erase(s1.find_last_not_of('0') + 1, string::npos);
			if (s1[s1.length() - 1] == '.') {
				s1.erase(s1.length() - 1);
			}
			return Value(GetString() + s1);
		}
		catch (invalid_argument& arg) {
			string s1 = to_string(oper.GetReal());
			s1.erase(s1.find_last_not_of('0') + 1, string::npos);
			if (s1[s1.length() - 1] == '.') {
				s1.erase(s1.length() - 1);
			}
			return Value(GetString() + s1);
		}
	}
	else if (IsReal() && oper.IsString()) {
		try {
			string s1 = to_string(GetReal());
			s1.erase(s1.find_last_not_of('0') + 1, string::npos);
			if (s1[s1.length() - 1] == '.') {
				s1.erase(s1.length() - 1);
			}
			return Value(s1 + oper.GetString());
		}
		catch (invalid_argument& arg) {
			string s1 = to_string(GetReal());
			s1.erase(s1.find_last_not_of('0') + 1, string::npos);
			if (s1[s1.length() - 1] == '.') {
				s1.erase(s1.length() - 1);
			}
			return Value(s1 + oper.GetString());
		}
	}
	else if (IsString() && oper.IsString()) {
		return Value(GetString() + oper.GetString());
	}
	else if (IsReal() && oper.IsReal()) {
		string s1 = to_string(GetReal());
		s1.erase(s1.find_last_not_of('0') + 1, string::npos);
		if (s1[s1.length() - 1] == '.') {
			s1.erase(s1.length() - 1);
		}
		string s2 = to_string(oper.GetReal());
		s2.erase(s2.find_last_not_of('0') + 1, string::npos);
		if (s2[s2.length() - 1] == '.') {
			s2.erase(s2.length() - 1);
		}
		return Value(s1 + s2);
	}
	return Value();
}

Value Value::Repeat(const Value& oper)const {
	if (IsString() && oper.IsReal()){
		string newString = "";
		for(int i = 0;i<oper.GetReal()-1;i++) {
			newString += GetString();
		}
		return Value(newString);
	}
	else if (IsString() && oper.IsInt()) {
		string newString = "";
		for (int i = 0;i<oper.GetInt();i++) {
			newString += GetString();
		}
		return Value(newString);
	}
	return Value();
}

Value Value::SEqual(const Value& oper) const {
	if (IsString() && oper.IsString()) {
		return Value(GetString() == oper.GetString());
	}
	else if (IsString() && oper.IsReal()) {
		try {
			if (stod(GetString()) == oper.GetReal()) {
				return Value(false);
			}
			return Value(true);
		}
		catch (invalid_argument& arg) {
			string s1 = to_string(oper.GetReal());
			return Value(GetString() == s1);
		}
	}
	else if (IsReal() && oper.IsString()) {
		try {
			if (GetReal() == stod(oper.GetString())) {
				return Value(true);
			}
			return Value(false);
		}
		catch (invalid_argument& arg) {
			string s1 = to_string(GetReal());
			return Value(s1 == oper.GetString());
		}

	}
	else if (IsReal() && oper.IsReal()) {
		return Value(GetReal() == oper.GetReal());
	}
	return Value();
}


Value Value::SGthan(const Value& oper) const {
	if (IsString() && oper.IsString()) {
		return Value(GetString() > oper.GetString());
	}
	else if (IsString() && oper.IsReal()) {
		try {
			if (stod(GetString()) == oper.GetReal()) {
				return Value(false);
			}
			return Value(true);
		}
		catch (invalid_argument& arg) {
			string s1 = to_string(oper.GetReal());
			return Value(GetString() > s1);
		}
	}
	else if (IsReal() && oper.IsString()) {
		try {
			if (GetReal() == stod(oper.GetString())) {
				return Value(true);
			}
			return Value(false);
		}
		catch (invalid_argument& arg) {
			string s1 = to_string(GetReal());
			return Value(s1 > oper.GetString());
		}

	}
	else if (IsReal() && oper.IsReal()) {
		return Value(GetReal() > oper.GetReal());
	}
	return Value();
}


Value Value ::SLthan(const Value& oper) const {
	if (IsString() && oper.IsString()) {
		return Value(GetString() < oper.GetString());
	}
	else if (IsString() && oper.IsReal()) {
		try {
			if (stod(GetString()) == oper.GetReal()) {
				return Value(false);
			}
			return Value(true);
		}
		catch (invalid_argument& arg) {
			string s1 = to_string(oper.GetReal());
			return Value(GetString() < s1);
		}
	}
	else if (IsReal() && oper.IsString()) {
		try {
			if (GetReal() == stod(oper.GetString())) {
				return Value(true);
			}
				return Value(false);	
		}
		catch (invalid_argument& arg) {
			string s1 = to_string(GetReal());
			return Value(s1 < oper.GetString());
		}
		
	}
	else if (IsReal() && oper.IsReal()) {
		return Value(GetReal() < oper.GetReal());
	}
	return Value();
}
