#ifndef _TOKEN_TYPE_
#define _TOKEN_TYPE_

enum TokenType
{
    unknown,
    ID,         /* exclude argument */
    NUM,
    STR,        /* string type e.g "Lisp */
    BRACKET,    /* ( ) */
    ARITH_OP,   /* +, -, *, / */
    BOOL_OP,    /* < <= > >= = */

    /* the following token especially for
     * build-in procedure
     */

    PROC,       /* user_defined procedure */
    CONS,       /* cons */
    LIST,       /* list type */
    DEFINE,     /* define */
    ARGUMENT,   /* special type of "ID"  */
    IF,
    COND,
    CAR,
    CDR,
    MAP,
    FILTER,

};


#endif
