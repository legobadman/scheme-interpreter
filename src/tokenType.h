
enum TokenType
{
    unknown
    ID = 1,
    NUM,
    STR,        /* string type e.g "Lisp */
    BRACKET,    /* ( ) */
    ARITH_OP,   /* +, -, *, / */
    BOOL_OP,    /* < <= > >= = */

    /* the following token especially for
     * build-in procedure
     */

    PROC,       /* user_defined procedure */
    LIST,       /* list type */
    DEFINE,     /* define */
    IF,
    COND,
    MAP,
    FILTER

};
