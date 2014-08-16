#! /usr/bin/python
# -*- coding:utf8 -*-

# 'grammer'
'''
Lisp -> exp | DEF (需要人工干预以消除二义性)
    
    exp -> ( procedure exp_ ) | Value
        procedure -> operator | LAMB | ID
            operator -> + | - | * | /
            LAMB -> ( lambda ( ArguRefList ) exp )
        exp_ -> exp exp_ | None
        Value -> " ID | ID | NUM

    DEF -> ( define DEFOBJ DEFBODY )
        DEFOBJ -> ID | ( ID Argulist )
            Argulist -> ID Argulist | None
        DEFBODY -> exp DEFBODY | DEF DEFBODY | None

    ArguRefList -> ID Argulist | None
    ArguCallList -> exp ArguCallList | None
    
'''


import sys

currentTokenIndex = 0
TokenString = []

def Lisp():
    global TokenString
    global currentTokenIndex
    token = TokenString[currentTokenIndex]
    nexttoken = TokenString[currentTokenIndex+1]

    if nexttoken == 'define':
        DEF()
    else:
        exp()

def match( s ):
    global currentTokenIndex
    global TokenString

    token = TokenString[currentTokenIndex]
    matchString = s

    if type(s) == type(''):
        s = ''.join(s)

    if token in s:
        currentTokenIndex += 1
        print 'match %s' % token
    else:
        print 'not match %s' % s 
        sys.exit(0)

def error( s ):
    print 'not match %s' % s
    sys.exit(0)

def exp():
    global currentTokenIndex
    global TokenString

    token = TokenString[currentTokenIndex]
    if token=='(':
        match('(')
        procedure()
        exp_()
        match(')')
    elif token in ['"','ID','NUM']:
        Value()
    
    else:
        error("exp()")


def Value():
    global currentTokenIndex
    global TokenString

    token = TokenString[currentTokenIndex]
    if token == '"':
        match('"')
    elif token == 'ID':
        match('ID')
    elif token == 'NUM':
        match('NUM')
    else:
        error("Value()")

def procedure():
    global currentTokenIndex
    global TokenString

    token = TokenString[currentTokenIndex];

    if token in ['+','-','*','/']:
        Operator()

    elif token=='(':
        LAMB()

    elif token=='ID':
        match('ID')

    else:
        error('procedure()')

def Operator():
    match( ['+','-','*','/'] ) 

def LAMB():
    match( '(' )
    match( 'lambda' )
    match( '(' )
    ArguRefList()
    match( ')' )
    exp()
    match( ')' )


def exp_():
    global currentTokenIndex
    global TokenString
    token = TokenString[currentTokenIndex]

    if token in ['(','"','ID','NUM']:
        exp()
        exp_()

    # follow set of exp_ is [')']
    elif token == ')':
        return
    else:
        error("exp_()")

def ArguRefList():
    global currentTokenIndex
    global TokenString

    token = TokenString[currentTokenIndex]

    if token=='ID':
        match('ID')
        ArguRefList()

    elif token==')':
        return

    else:
        error("ArguRefList()")


def DEF():
    match('(')
    match('define')
    DEFOBJ()
    DEFBODY()
    match(')')

def DEFOBJ():
    global currentTokenIndex
    global TokenString

    token = TokenString[currentTokenIndex]

    if token == 'ID':
        match('ID')

    elif token == '(':
        match('(')
        match('ID')
        ArguRefList()
        match(')')

    else:
        error('DEFOBJ()')

def DEFBODY():
    global currentTokenIndex
    global TokenString

    token = TokenString[currentTokenIndex]
    # special process
    if token == '(':
        next_token = TokenString[currentTokenIndex+1]
        if next_token == 'define':
            DEF()
            DEFBODY()
        else:
            exp()
            DEFBODY()
    elif token==')':
        return
    elif token=='ID':
        match('ID')
    else:
        error( "DEFBODY()" )


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
    Lisp()
