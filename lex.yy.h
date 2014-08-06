#ifndef _LEX_YY_H_
#define _LEX_YY_H_

#define numOfRegex 4

int Recognize_for_ID(const char*);
int RecognizeAndAct_for_ID( );
int Recognize_for_NUM(const char*);
int RecognizeAndAct_for_NUM( );
int Recognize_for_str(const char*);
int RecognizeAndAct_for_str( );


void set_functions_for_allfunctions();

#endif
