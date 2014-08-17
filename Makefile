objects=\
	LL1.o Number.o scan.o AST.o Fraction.o\
	lex.yy.o procedure.o LispEnvironment.o

main: $(objects)
	g++ -g $(objects) -o main
	#rm $(objects)

LL1.o: LL1.h LL1.cpp Tree.h Token.h tokenType.h
	g++ -g -c LL1.h LL1.cpp Tree.h Token.h tokenType.h

Number.o: Number.h Number.cpp
	g++ -g -c Number.h Number.cpp

scan.o: Token.h lex.yy.h scan.cpp
	g++ -g -c Token.h lex.yy.c scan.cpp

AST.o: Tree.h LL1.h Token.h Number.h AST.cpp tokenType.h
	g++ -g -c Tree.h LL1.h Token.h Number.h AST.cpp tokenType.h

Fraction.o: Fraction.h Fraction.cpp
	g++ -g -c Fraction.h Fraction.cpp

lex.yy.o: Token.h lex.yy.c
	g++ -g -c Token.h lex.yy.c

procedure.o: procedure.cpp procedure.h Tree.h LL1.h LispEnvironment.h
	g++ -g -c procedure.cpp procedure.h Tree.h LL1.h LispEnvironment.h
    
LispEnvironment.o: LispEnvironment.cpp LispEnvironment.h
	g++ -g -c LispEnvironment.h LispEnvironment.cpp
