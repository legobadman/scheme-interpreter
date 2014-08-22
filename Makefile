VPATH = src

objects=\
	LL1.o Number.o scan.o AST.o Fraction.o\
	lex.yy.o procedure.o LispEnvironment.o\
	SymbolTable.o

main: $(objects)
	g++ -g $(objects) -o main
	rm $(objects)

LL1.o: LL1.h LL1.cpp Tree.h Token.h tokenType.h LispEnvironment.h procedure.h
#	g++ -g -c LL1.h LL1.cpp Tree.h Token.h tokenType.h LispEnvironment.h procedure.h

Number.o: Number.h Number.cpp
#	g++ -g -c Number.h Number.cpp

scan.o: Token.h lex.yy.h scan.cpp
#	g++ -g -c Token.h lex.yy.c scan.cpp

AST.o: Tree.h LL1.h Token.h Number.h AST.cpp tokenType.h
#	g++ -g -c Tree.h LL1.h Token.h Number.h AST.cpp tokenType.h

Fraction.o: Fraction.h Fraction.cpp
#	g++ -g -c Fraction.h Fraction.cpp


lex.yy.o: Token.h lex.yy.c
	g++ -g -c src/Token.h src/lex.yy.c

procedure.o: procedure.cpp procedure.h Tree.h LL1.h LispEnvironment.h
#	g++ -g -c procedure.cpp procedure.h Tree.h LL1.h LispEnvironment.h
    
LispEnvironment.o: SymbolTable.h LispEnvironment.cpp LispEnvironment.h procedure.h
#	g++ -g -c SymbolTable.h LispEnvironment.h procedure.h LispEnvironment.cpp

SymbolTable.o: SymbolTable.h SymbolTable.cpp Tree.h
#	g++ -g -c SymbolTable.h SymbolTable.cpp Tree.h
