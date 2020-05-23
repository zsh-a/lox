#include"Ast.h"


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