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

LoxObject Variable::accept(Visitor* visitor){
	return visitor->visit(this);
}

LoxObject Assign::accept(Visitor* visitor){
	return visitor->visit(this);
}

LoxObject Call::accept(Visitor* visitor){
	return visitor->visit(this);
}

void Expression::accept(StmtVisitor* visitor){
		visitor->visit(this);
}

void Print::accept(StmtVisitor* visitor){
	visitor->visit(this);
}

void Var::accept(StmtVisitor* visitor){
	visitor->visit(this);
}

void Block::accept(StmtVisitor* visitor){
	visitor->visit(this);
}

void If::accept(StmtVisitor* visitor){
	visitor->visit(this);
}

void While::accept(StmtVisitor* visitor){
	visitor->visit(this);
}

void Function::accept(StmtVisitor* visitor){
	visitor->visit(this);
}