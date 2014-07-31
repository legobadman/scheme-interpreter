#! -*- coding:utf8 -*-


# 'grammer'

'''
Lisp -> exp | DEF (须要人工干预以消除二义性)
    
    exp -> ( procedure exp_ ) | Value
        procedure -> operator | LAMB
        exp_ -> exp exp_ | None
        Value -> " ID | ID | NUM

    DEF -> ( define DEFOBJ DEFBODY )
        DEFOBJ -> ID | ( ID Argulist )
            Argulist -> ID Argulist | None
        DEF

'''





import sys

currentTokenIndex = 0
TokenString = []

def match( s ):
    print 'match %s' % s

def error( s ):
    print 'not match %s' % s
    sys.exit(0)

def exp():
    global currentTokenIndex
    global TokenString
    if TokenString[currentTokenIndex] == '(':
        match('(')
        currentTokenIndex += 1
    else:
        error('(')

    # 手动解决二义性
    # if TokenString[currentTokenIndex] == 'define':
    procedure()
    exp_()
    if TokenString[currentTokenIndex] == ')':
        match(')')
        currentTokenIndex += 1
    else:
        error(')')

def procedure():
    global currentTokenIndex
    global TokenString

    token = TokenString[currentTokenIndex];

    if token in ['+','-','*','/']:
        match( token )
        currentTokenIndex += 1
    elif token=='define':
        define()

    elif token=='ID':
        match( token )
        currentTokenIndex += 1

    else:
        error('procedure()')

def exp_():
    global currentTokenIndex
    global TokenString

    if TokenString[currentTokenIndex] == 'NUM':
        match( 'NUM' )
        currentTokenIndex += 1
        exp_()

    elif TokenString[currentTokenIndex] == '(':
        exp()
        exp_()

    elif TokenString[currentTokenIndex] == 'ID':
        match( 'ID' )
        currentTokenIndex += 1
        exp_()

    elif TokenString[currentTokenIndex] == ')':
        return
    else:
        error( 'exp_()' )


def define():
    global currentTokenIndex 
    global TokenString

    if TokenString[currentTokenIndex] == 'define':
        match("define")
        currentTokenIndex += 1

    token = TokenString[currentTokenIndex]
    if token=='ID' or token=='(':
        DEF_Name()
    else:
        print '定义格式错误，应为单个标识符或者（名字，参数列表）'

    token = TokenString[currentTokenIndex]

    while True:
        if token=='(':
            match('(')
            currentTokenIndex += 1
            token = TokenString[currentTokenIndex]
            
             



def DEF_Name():
    global currentTokenIndex
    global TokenString

    if TokenString[currentTokenIndex] == 'ID':
        match('ID')
        currentTokenIndex += 1

    elif TokenString[currentTokenIndex] == '(':
        match('(')
        currentTokenIndex += 1

        ProcedureName()
        Parameter()

        if TokenString[currentTokenIndex] == ')':
            match(')')
            currentTokenIndex += 1
        else:
            error(')')

    else:
        error('DEF_Name')

def DEF_Body():
    global currentTokenIndex
    global TokenString

    if TokenString[currentTokenIndex] == '(':
        exp()
    else:
        error("DEF_BODY()")

def ProcedureName():
    global currentTokenIndex
    global TokenString
    
    if TokenString[currentTokenIndex] == 'ID':
        match('ID')
        currentTokenIndex += 1
    else:
        error('ID')

def Parameter():
    global currentTokenIndex
    global TokenString

    if TokenString[currentTokenIndex] == 'ID':
        match('ID')
        currentTokenIndex += 1
        Parameter()

    elif TokenString[currentTokenIndex] == ')':
        return

    else:
        error("Parameter()")

def scan():
    TokenString = []
    line = filter(lambda x:x!='',raw_input().strip().split(' '))
    TokenString.extend(line)
    while line:
        line = filter(lambda x:x!='',raw_input().strip().split(' '))
        TokenString.extend(line)

    return TokenString

if __name__ == "__main__":
    TokenString = scan()
    exp() 
