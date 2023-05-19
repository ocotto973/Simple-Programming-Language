# Simple-Programming-Language
Simple Programming Language
Created by: Oscar Cotto

This Simple Programming Language(SPL) reads texts files and interprets it into my created language rules. 

Time spent: 50+ hours spent in total

Required Features
The following required functionality is completed:

  Needs a text file to read from. 
  
  Will break down each file character by character with lexical analyzer.
  
  Will check language rules with parser. The language rules are as followed (EBNF notation):
  1. Prog : := StmtList 
  2. StmtList : := Stmt ; { Stmt; } 
  3. Stmt ::= AssignSome | WriteLnStmt | IfStmt 
  4. WriteLnStmt ::= WRITELN (ExprList) 
  5. IfStmt : := IF (Expr) \{\ StmtList \ ]' [ ELSE . { ' StmtList &quot; )' ] 
  6. AssignStmt : := Var = Expr 
  7. Var : := NIDENT | SIDENI 
  8. Exprlist : := Expr { , Expr } 
  9. Expr : := RelExpr [ (-eq|==) RelExpr ] 
  10. RelExpr : := AddExpr [ ( -It | -gt | &lt; | &gt; ) AddExpr ] 
  11. AddExpr : : MultExpr { ( + | - | .) MultExpr } 
  12. MultExpr : := ExponExpr { ( * | / | **) ExponExpr } 
  13. ExponExpr : := UnaryExpr { ^ UnaryExpr } 
  14. UnaryExpr : := [( - | + )] PrimaryExpr
  15. PrimaryExpr : := IDENT | SIDENT | NIDENT | ICONST | RCONST | SCONST | (Expr)
  
  Will check the logic with interpreter.
