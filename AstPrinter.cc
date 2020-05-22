#include"AstPrinter.h"

string AstPrinter::parenthesize(const string& name,const initializer_list<Expr*>& exprs){
		string ret = "(" + name;
		for(auto& e:exprs){
			ret += " ";
			ret += e->print();
		}
		ret += ")";
		return ret;
}
LoxObject AstPrinter::visit(Binary* expr) {
    return parenthesize(expr->op.lexeme,{expr->left,expr->right});
}

LoxObject AstPrinter::visit(Grouping* expr) {
    return parenthesize("group",{expr->expression});
}
LoxObject AstPrinter::visit(Literal* expr) {
    if(expr->type == NUMBER) return to_string(expr->num);
	return expr->str;
}
LoxObject AstPrinter::visit(Unary* expr){
    return parenthesize(expr->op.lexeme,{expr->right});
}