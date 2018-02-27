/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Meesum Ali
 *
 */

#include "proj5Tokens.h"
#define TRUE 1
#define FALSE 0
int debugmode=FALSE;
void printCommands();

void processExpression (Token inputToken, TokenReader *tr, STACK op, STACK val);
int eval ( int v1, int ch, int v2 ){
    int iresult=0;
    int iv1 = v1;
    int iv2 = v2;
    switch(ch) {
        case 43: iresult=iv1+iv2;
            break;
        case 45: iresult=iv1-iv2;
            break;
        case 42: iresult=iv1*iv2;
            break;
        case 47: if(iv2!=0) iresult=iv1/iv2;
            break;
    }
    if(debugmode){printf("Current computation is :%d %c %d = %d\n",v1,ch,v2,iresult);}
    return iresult;
}
int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    for (int i = 0; i < argc; i++){
        if(strcmp(argv[i],"-d")==0){ debugmode= TRUE;}
    }
    STACK op,val;
    op.stk_create();
    val.stk_create();
    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr, op,val);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

void processExpression (Token inputToken, TokenReader *tr, STACK op, STACK val)
{
 /**********************************************/
 /* Declare both stack head pointers here      */

 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       /* make this a debugMode statement */
          if(debugmode){printf ("\nVal: %d, Value Stack below\n", inputToken.getValue() );}

       // add code to perform this operation here
          int cval=inputToken.getValue();
          val.stk_push(cval);
          if(debugmode){val.prnstack();}
      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
       /* make this a debugMode statement */
          if(debugmode){printf ("\nOP: %c, Operation Stack below\n", inputToken.getOperator() );}

       // add code to perform this operation here
          int oval= inputToken.getOperator();
          if(oval=='(')
              op.stk_push(oval);
          if(oval=='+'||oval=='-'){
              while(op.isEmpty()!=1 && op.Top()!='(' && op.Top()!=')'){
                  int ch=op.Pop_top();
                  int v1 = val.Pop_top();
                  int v2 = val.Pop_top();
                  val.stk_push(eval(v2,ch,v1));
              }
              op.stk_push(oval);
          }
          if(oval=='*'||oval=='/'){
              //printf("error case------------------below\n");
              while(op.isEmpty()!=1 && (op.Top()=='*' || op.Top()=='/')){
                  int ch=op.Pop_top();
                  int v1 = val.Pop_top();
                  int v2 = val.Pop_top();
                  val.stk_push(eval(v2,ch,v1));
              }
              op.stk_push(oval);
          }
          if(oval==')'){
              while(op.isEmpty()!=1 && op.Top()!='(' ){
                  int ch=op.Pop_top();
                  int v1 = val.Pop_top();
                  int v2 = val.Pop_top();
                  val.stk_push(eval(v2,ch,v1));
              }
              if(op.isEmpty()){printf("operator stack is empty when it shouldn't be\n");}
              else{if(op.Top()=='('){op.Pop_top();}}
              //printf("error case------------------above\n");
          }
        if(debugmode){op.prnstack();}
      }

    /* get next token from input */
    inputToken = tr->getNextToken ();
   }

 /* The expression has reached its end */

 // add code to perform this operation here
    while(op.isEmpty()!=1){
        int ch=op.Pop_top();
        int v1 = val.Pop_top();
        int v2 = val.Pop_top();
        val.stk_push(eval(v2,ch,v1));
    }
    printf("result of expression: %d\n",val.Pop_top());
    val.stk_reset();
    op.stk_reset();
 printf ("\n");
}

