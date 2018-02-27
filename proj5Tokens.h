/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Pat Troy
 *
 */

/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

#include <cstdio>
#include <cstring>
#include <cctype>

// Enumarated Type specifying all of the Tokens
enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};


// Class to hold the Token information
class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

  public:

  // Default to initialize to the ERROR TokenType
  Token();

  // Initialize to a specific TokenType
  Token (TokenType t);

  // Set to a specific TokenType
  void setToType(TokenType t);

  // Set to a OPERATOR TokenType with specific operator value
  void setToOperator(char c);

  // Set to a VALUE TokenType with a specific numeric value
  void setToValue(int v);

  // return true if the Current Token is of the given TokenType
  bool equalsType(TokenType t);

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool equalsOperator(char c);

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char getOperator ();

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int getValue();
};


class TokenReader
{
  private:
     char inputline[300];  // this assumes that all input lines are 300 characters or less in length
     bool needline;
     int pos;


  public:

  // initialize the TokenReader class to read from Standard Input
  TokenReader();

  // Force the next getNextToken to read in a line of input
  void clearToEoln();

  // Return the next Token from the input line
  Token getNextToken();
};

class STACK {
private:
    int *Darrayp;
    int Darraysize;
    int top;

public:

    // This class does not have any constructors (yet)
    void stk_create(){
      Darraysize=2;
      Darrayp = new int[Darraysize];
      top=-1;

    }
    //--------------------------------------------------------------------
    void prnstack(){
      int i=0;
      for(i=0;i<Darraysize;i++){
        printf("stk_index:%d   stk_item:%d\n",i,Darrayp[i]);
      }
    }
    //-------------------------------------------------------------------------
    void stk_push(int item){
      if(top == Darraysize-1 ){
        {//printf("array size %d\n",s->Darraysize);
          int *temp;
          temp = new int[Darraysize + 2];
          int i;
          for ( i = 0 ; i < Darraysize ; i++)
            temp[i] = Darrayp[i];
          delete (Darrayp);
          Darrayp = temp;
          Darraysize = Darraysize + 2;
        }
      }

      top++;
        //printf("current top index %d\n",top);
      Darrayp[top] = item;
    }
    //-----------------------------------------------------------------------------------------------------------------
    bool isEmpty ()
    {
      if ( top ==-1)
        return 1;
      else
        return 0;
    }

    //-----------------------------------------------------------------------------------------------------------------
    int Pop_top() {
      int temp=Darrayp[top];
      pop();
      return temp; }
    //-----------------------------------------------------------------------------------------------------------------
    void pop ()
    {//printf("top b4 pop %d\n",top);
      top = top - 1;
      //printf("top after pop %d\n",top);
    }
    int Top(){
        return Darrayp[top];
    }

//-----------------------------------------------------------------------------------------------------------------
    void stk_reset(){
      delete (Darrayp);
      Darraysize=2;
      Darrayp = Darrayp = new int[Darraysize];
      top=0;
    }

};



