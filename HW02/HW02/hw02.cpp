#include <stack>
#include <vector>
#include <iostream>

using namespace std;
enum TokenType { EOL, VALUE, OPAREN, CPAREN, EXP, MULT, DIV, PLUS, MINUS };
// PREC_TABLE matches order of Token enumeration
struct Precedence
{
    int inputSymbol;
    int topOfStack;
};
// and
vector<Precedence> PREC_TABLE =
{
    { 0, -1 }, { 0, 0 }, // EOL, VALUE
    { 100, 0 }, { 0, 99 }, // OPAREN, CPAREN
    { 6, 5 }, // EXP
    { 3, 4 }, { 3, 4 }, // MULT, DIV
    { 1, 2 }, { 1, 2 } // PLUS, MINUS
};



int main ( ) {
    stack<TokenType> opStack;
    opStack.push(EOL); // EOL == end of line
    opStack.push(PLUS);
    opStack.push(MULT);
    opStack.push(EXP);
    opStack.push(EXP);
    TokenType topOp;
    TokenType lastType = DIV;

    while( PREC_TABLE[ lastType ].inputSymbol <= PREC_TABLE[ topOp = opStack.top( ) ].topOfStack )
    {
        opStack.pop();
        cout << topOp << endl;
    }
    if( lastType != EOL )
        opStack.push( lastType );
    // show what are the contents of opStack at this point in the code.
    return 0;
}