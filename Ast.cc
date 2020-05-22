#include"Ast.h"

string Expr::parenthesize(const string& name,const initializer_list<Expr*>& exprs){
		string ret = "(" + name;
		for(auto& e:exprs){
			ret += " ";
			ret += e->print();
		}
		ret += ")";
		return ret;
}

LoxObject Binary::accept(Visitor* visitor){
	return visitor->visit(this);
}


LoxObject Grouping::accept(Visitor* visitor){
	return visitor->visit(this);
}

LoxObject Literal::accept(Visitor* visitor){
	return visitor->visit(this);
}

LoxObject Unary::accept(Visitor* visitor){
	return visitor->visit(this);
}