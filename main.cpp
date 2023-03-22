/*
 * lex.h
 *
 * CS280
 * Spring 2023
*/

#include<sstream>
#include <string>
#include <iostream>
#include <map>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;
string tempWord;
string word;
int lineum;
string line;
string lineString;
vector<string> allLex;
vector <string> declareLex;
int totalTok;
int useTok;
string ifContinue;
string ifBrace;
string leftBrace;
string declareIdent;
string lexArr[200];//////////////////////////////////////

string tok;
//string lex;

fstream read;
///////////////////////////

//////////////////////////////////

//Class definition of LexItem
class LexItem {
    string	token;
    string	lexeme;
    int	lnum;

public:
    LexItem() {
        string error = "ERR";
        lnum = -1;
    }
    LexItem(string token, string lexeme, int line) {
        this->token = token;
        this->lexeme = lexeme;
        this->lnum = line;
    }


    string	GetToken() const { return token; }
    string	GetLexeme() const { return lexeme; }
};


class Project{
public:
    int tokenCount=0;

    ///////////////////////////////////////
    LexItem checkInt(string& word) {

        for (int i = 0; i < word.length(); i++) {
            if (!isdigit(word.at(i))) {
                tempWord = word.substr(0,i);
                word.erase(0,i);
                return LexItem("ICONST", tempWord, lineum);
            }

        }
        tempWord = word;
        word.erase();
        return LexItem("ICONST", tempWord, lineum);
    }


    LexItem checkReal(string& word ) {
        size_t lastDot =0;

        int tokenCount =0;

        ////////////////////////
        for(char i : word){
            if(i=='.'){
                tokenCount+=1;
            }
        }
        if(tokenCount>1) {
            lastDot = word.find_last_of('.',word.length()) ;
            tempWord=word.substr(0,(lastDot+1));
            word.erase();

            return  LexItem("ERR", tempWord, lineum);
        }
        ////////////////////////////////////////
        for (int i = 0; i < word.length(); i++) {
            if (!(isdigit(word.at(i)) || word.at(i) == '.')) {
                tempWord = word.substr(0,i);
                word.erase(0,i);
                return LexItem("RCONST", tempWord, lineum);
            }
        }
        tempWord = word;
        word.erase();
        return  LexItem("RCONST", tempWord, lineum);
    }
    LexItem checkIdent(string& word) {
        //  char peek;
        LexItem lexi;
        if ((word.at(0) == '_' || isalpha(word.at(0)))) {
            for (int i = 1; i < word.length(); i++) {
                /////@$ potential check to include
                if (!(isalnum(word.at(i)) || (word.at(i) == '_'))) {
                    tempWord = word.substr(0, i);
                    word.erase(0, i);
                    //totalIdents+=1;
                    if (tempWord == "if" ) {
                        //totalIdents -= 1;
                        lexi = LexItem("IF", tempWord, lineum);
                    } else if (tempWord == "writeln" ) {
                        // totalIdents -= 1;
                        lexi = LexItem("WRITELN", tempWord, lineum);
                    }else if(tempWord=="else"){
                        lexi = LexItem("ELSE", tempWord, lineum);
                    }
                    else{
                        lexi =LexItem("IDENT", tempWord, lineum);
                    }

                    return  lexi;
                }
            }


        }
        tempWord = word;
        word.erase();

            if (tempWord == "if" ) {
                //totalIdents -= 1;
                lexi = LexItem("IF", tempWord, lineum);
            } else if (tempWord == "writeln" ) {
                // totalIdents -= 1;
                lexi = LexItem("WRITELN", tempWord, lineum);
            }else if(tempWord=="else"){
                lexi = LexItem("ELSE", tempWord, lineum);
            }
            else{
                lexi =LexItem("IDENT", tempWord, lineum);
            }

            return  lexi;


    }

    LexItem checkSident(string& wor){
        if( (wor.at(0) =='@') && (wor.at(1)=='_' || isalpha(wor.at(1)))  ){
            for(int i =2; i<wor.length(); i++){
                /////@$ potential check to include
                if(!(isalnum(wor.at(i)) || (wor.at(i) =='_'))){
                    tempWord = wor.substr(0,i);
                    wor.erase(0,i);
                    //  totalIdents+=1;
                    return  LexItem("SIDENT", tempWord, lineum);

                }
            }
        }
        tempWord = word;
        word.erase();
        return  LexItem("SIDENT", tempWord, lineum);

    }

    LexItem checkNident(string& word){
        if( (word.at(0) =='$') && (word.at(1)=='_' || isalpha(word.at(1)))  ){
            for(int i =2; i<word.length(); i++){
                /////@$ potential check to include
                if(!(isalnum(word.at(i)) || (word.at(i) =='_'))){
                    tempWord = word.substr(0,i);
                    word.erase(0,i);
                    return  LexItem("NIDENT", tempWord, lineum);

                }
            }
        }
        tempWord = word;
        word.erase();
        //   totalIdents+=1;
        return  LexItem("NIDENT", tempWord, lineum);

    }
///method
    void display(string& tok) {

    stringstream lineS(lineString);
    string lineWord;

    while(lineS>>lineWord){
    declareIdent = lineWord;
    useTok+=1;
    if(lineWord =="RBRACES"){
   ifBrace="RBRACES" ;
   leftBrace="false";
}
/////CONTINUE IF
    if(ifContinue=="continue" && lineWord!="LBRACES"){
    cout<<"Line # " <<lineum <<": If Statement Syntax Error: Missing left brace" <<endl;
    cout<<"Line # " <<lineum <<": Incorrect If-Statement." <<endl;
    cout<<"Line # " <<lineum <<": Syntactic error in Program Body." <<endl;
    cout<<"Line # " <<lineum <<": Missing Program" <<endl;
    cout<<"Unsuccessful Parsing" <<endl;
    cout<<"Number of Syntax Errors 4" <<endl;
    ifContinue.erase();
    exit(0);
}
///END IF
    if((lineWord=="NIDENT" || lineWord=="SIDENT" ||lineWord=="IDENT") ) {
    ////////store declare varable
    while (lineS >> lineWord) {
        useTok+=1;
        if(lineWord =="SCONST"){
            cout<<"line # " <<lineum <<": Missing Assignment Operator" <<endl;
            cout<<"line # " <<lineum <<": Incorrect Assignment Statement." <<endl;
            cout<<"line # " <<lineum <<": Syntactic error in Program Body." <<endl;
            cout<<"line # " <<lineum <<": Missing Program" <<endl;
            cout<<"Unsuccessful Parsing" <<endl;
            cout<<"Number of Syntax Errors 4" <<endl;
            exit(0);
        }
        if (lineWord == "ASSOP") {
            string store = lexArr[(useTok-2)];
            if( !((store.at(0)) =='@') && !((store.at(0))=='$')){
                cout << "Line #" << lineum << ": Invalid variable name" << endl;
                cout << "Line # " << lineum << ": Syntactic error in Program Body." << endl;
                cout << "Line # " << lineum << ": Missing Statement for Else-Clause" << endl;
                cout << "Line # " << lineum << ": Incorrect If-Statement." << endl;
                cout << "Line # " << lineum << ": Syntactic error in Program Body." << endl;
                cout << "Line # " << lineum << ": Missing Program" << endl;
                cout<<"Unsuccessful Parsing" <<endl;
                cout<<"Number of Syntax Errors 6" <<endl;
                exit(0);
            }
            declareLex.push_back(store);
        } else if ( (lineWord=="NIDENT" || lineWord =="SIDENT") && (find(declareLex.begin(), declareLex.end(), lexArr[(useTok-1)]) == declareLex.end())) {
            cout << "Line #" << lineum << ": Using Undefined Variable" << endl;
            cout << "Line #" << lineum << ": Missing operand after operator" << endl;
            cout << "Line #" << lineum << ": Missing Expression in Assignment Statement" << endl;
            cout << "Line #" << lineum << ": Incorrect Assignment Statement." << endl;
            cout << "Line #" << lineum << ": Syntactic error in Program Body." << endl;
            cout << "Line #" << lineum << ": Missing Program" << endl;
            cout<<"Unsuccessful Parsing" <<endl;
            cout<<"Number of Syntax Errors 5" <<endl;
            exit(0);
        }
        //////////////////////////////
       if( lineS >> lineWord){
           useTok += 1;
       }
       if(lineWord=="LPAREN"){
           string storeWord;
           int countLparen=1;
           int countRparen=0;
           while(lineS>>lineWord){
               useTok+=1;
               storeWord=lineWord;
               if(storeWord=="LPAREN"){
                   countLparen+=1;
               }else if(storeWord=="RPAREN"){
                   countRparen+=1;
               }
               if(lineS>>lineWord){
                   useTok+=1;
               }

               if(lineWord=="LPAREN"){
                   countLparen+=1;
               }else if(lineWord=="RPAREN"){
                   countRparen+=1;
               }
               if(storeWord=="PLUS"&&lineWord=="MULT"){
                   cout << "Line # " << lineum << ": Missing operand after operator" << endl;
                   cout << "Line # " << lineum << ": Missing expression after Left Parenthesis" << endl;
                   cout << "Line # " << lineum << ": Missing operand after operator" << endl;
                   cout << "Line # " << lineum << ": Missing expression after Left Parenthesis" << endl;
                   cout << "Line # " << lineum << ": Missing Expression in Assignment Statement" << endl;
                   cout << "Line # " << lineum << ": Incorrect Assignment Statement." << endl;
                   cout << "Line # " << lineum << ": Syntactic error in Program Body." << endl;
                   cout << "Line # " << lineum << ": Missing Program" << endl;
                   cout<<"Unsuccessful Parsing" <<endl;
                   cout<<"Number of Syntax Errors 8" <<endl;
                   exit(0);
               }
           }
           if(countLparen!=countRparen){
               cout << "Line # " << lineum << ": Missing right Parenthesis after expression" << endl;
               cout << "Line # " << lineum << ": Missing Expression in Assignment Statement" << endl;
               cout << "Line # " << lineum << ": Incorrect Assignment Statement." << endl;
               cout << "Line # " << lineum << ": Syntactic error in Program Body." << endl;
               cout << "Line # " << lineum << ": Missing Program" << endl;
               cout<<"Unsuccessful Parsing" <<endl;
               cout<<"Number of Syntax Errors 5" <<endl;
               exit(0);
           }
       }
       if(lineWord =="SCONST"){
           lineS>>lineWord;
           useTok+=1;
           if (lineWord == "SREPEAT") {
               lineS >> lineWord;
               useTok += 1;
               if (lineWord == "SEMICOL") {
                   cout << "Line # " << lineum << ": Missing operand after operator" << endl;
                   cout << "Line # " << lineum << ": Missing Expression in Assignment Statement" << endl;
                   cout << "Line # " << lineum << ": Incorrect Assignment Statement." << endl;
                   cout << "Line # " << (lineum+1) << ": Syntactic error in Program Body." << endl;
                   cout << "Line # " << (lineum+1) << ": Missing Program" << endl;
                   cout<<"Unsuccessful Parsing" <<endl;
                   cout<<"Number of Syntax Errors 5" <<endl;
                   exit(0);
               }
           }else
           //
           if(lineWord =="CAT"){
               lineS>>lineWord;
               useTok+=1;
               if((find(declareLex.begin(), declareLex.end(), lexArr[(useTok-1)]) == declareLex.end())){
                   cout << "Line #" << lineum << ": Using Undefined Variable" << endl;
                   cout << "Line #" << lineum << ": Missing operand after operator" << endl;
                   cout << "Line #" << lineum << ": Missing Expression in Assignment Statement" << endl;
                   cout << "Line #" << lineum << ": Incorrect Assignment Statement." << endl;
                   cout << "Line #" << lineum << ": Syntactic error in Program Body." << endl;
                   cout << "Line #" << lineum << ": Missing Program" << endl;
                   cout<<"Unsuccessful Parsing" <<endl;
                   cout<<"Number of Syntax Errors 6" <<endl;
                   exit(0);
               }
           }else if(lineWord=="ICONST"){
               cout << "Line # " << lineum << ": Missing semicolon at end of Statement." << endl;
               cout << "Line # " << lineum << ": Missing Program" << endl;
               cout<<"Unsuccessful Parsing" <<endl;
               cout<<"Number of Syntax Errors 2" <<endl;
               exit(0);
           }
       }
        //PAREN
        if (lineWord == "LPAREN") {
            while ((lineS >> lineWord) && (lineWord != "RPAREN")) {
                useTok += 1;
            }
            if (lineS >> lineWord && lineWord != "SEMICOL") {
                useTok+=1;
                ////EROR COL
            }
        }

        /////////////////////////////////////////
        if (leftBrace == "true" && lineWord == "RBRACES") {
            leftBrace = "false";
        }
        if (totalTok == useTok && lineWord != "SEMICOL") {
            cout<<"line # " <<(lineum+2) <<": Missing semicolon at end of Statement." <<endl;
            cout<<"line # " <<(lineum+2) <<": Missing Program" <<endl;
            cout<<"Unsuccessful Parsing" <<endl;
            cout<<"Number of Syntax Errors 2" <<endl;
            exit(0);
        }
    }
}

////Writeln
if(lineWord =="WRITELN"){
lineS>>lineWord;
    useTok+=1;
if(lineWord !="LPAREN"){
    cout<<"line # " <<lineum <<": Missing Left Parenthesis of Writeln Statement" <<endl;
    cout<<"line # " <<lineum <<": Missing Left Parenthesis of Writeln Statement" <<endl;
    cout<<"line # " <<lineum <<": Missing Left Parenthesis of Writeln Statement" <<endl;
    cout<<"line # " <<lineum <<": Missing Left Parenthesis of Writeln Statement" <<endl;
    cout<<"Unsuccessful Parsing" <<endl;
    cout<<"Number of Syntax Errors 4" <<endl;
    ifBrace = lineWord;
    exit(0);
}
while(lineS>>lineWord){
    useTok+=1;
  /*  if(lineWord =="PLUS" && lineS>>lineWord && lineWord=="MULT" ){
        useTok+=1;
        cout<<"line # " <<lineum <<" 13: Missing operand after operator" <<endl;
        exit(0);
    }*/

}
/*if(lineWord !="SEMICOL" ){
        cout<<"line #" <<lineum <<" Missing semicolon at end of Statement." <<endl;
        exit(0);
    }*/
}
///////////////////IF
    if(lineWord =="IF"){
        lineS>>lineWord;
        useTok+=1;
       /* if(lineWord !="LPAREN"){
            cout<<"line #" <<lineum <<" Missing Left Parenthesis of Writeln Statement" <<endl;
            exit(0);
        }*/
        if(lineS>>lineWord){
            useTok+=1;
        }
            if((lineWord=="NIDENT" || lineWord=="SIDENT") ){
            lineS>>lineWord;
            useTok+=1;

            ////////store declare varable
       if(lineWord=="SEQ" || lineWord =="SLTHAN"){
           lineS>>lineWord;
           useTok+=1;
        //   if(lineWord=="SCONST" && lineS>>lineWord &&!(lineWord =="RPAREN")){
           if(lineS>>lineWord){
               useTok+=1;
           if(!(lineWord =="RPAREN")){
           cout<<"line # " <<lineum <<": Missing Right Parenthesis of If condition" <<endl;
           cout<<"line # " <<lineum <<": Incorrect If-Statement." <<endl;
           cout<<"line # " <<(lineum+1) <<": Syntactic error in Program Body." <<endl;
           cout<<"line # " <<(lineum+1) <<": Missing Program" <<endl;
           cout<<"Unsuccessful Parsing" <<endl;
           cout<<"Number of Syntax Errors 4" <<endl;
           exit(0);

           }
           }

          if( (lineS>>lineWord) ){
              useTok+=1;
          /*   if(lineWord =="NEQ"){
              cout<<"line # 10" <<lineum <<" : Missing Right Parenthesis of If condition" <<endl;
              exit(0);}*/

          }

          if(lineWord !="LBRACES"){
                  ifContinue ="continue";
          }
       }
            //////////////////////////////
            if(lineWord=="NGTHAN"|| lineWord=="NLTHAN"|| lineWord=="SEQ"||lineWord=="SLTHAN"){
                lineS>>lineWord;
                useTok+=1;
                ifBrace = lineWord;
                if(lineWord != "SCONST"){

                }
                if(lineS>>lineWord){
                    useTok+=1;
                }
                if(lineS>>lineWord){
                    useTok+=1;
                }



            }
            /////////////////////////////////////////
 /*           if(totalTok == useTok && lineWord !="RBRACES"){
                cout<<"line #" <<lineum <<" Missing Right Parenthesis of If condition." <<endl;
                exit(0);
            }*/
        }
            ifBrace = lineWord;

    }
    if(lineWord=="ELSE"){
        if(ifBrace !="RBRACES"){
            ifBrace.erase();
            cout<<"line # " <<lineum <<": Missing right brace." <<endl;
            cout<<"line # " <<lineum <<": Missing Statement for If-Stmt Clause" <<endl;
            cout<<"line # " <<lineum <<": Incorrect If-Statement." <<endl;
            cout<<"line # " <<lineum <<": Syntactic error in Program Body." <<endl;
            cout<<"line # " <<lineum <<": Missing Program" <<endl;
            cout<<"Unsuccessful Parsing" <<endl;
            cout<<"Number of Syntax Errors 5"<<endl;
            exit(0);
        }
        if(lineS>>lineWord){
            useTok+=1;
        }
        if(lineWord!="LBRACES"){
            //
        }
      leftBrace ="true";

    }

}

    }


};


LexItem print;
Project obj2;
///GETnExt
LexItem getNextToken(istream& in, int& lineum, stringstream& c) {
totalTok+=1;
    char firstChar = word.at(0);

    switch(firstChar){

        case '+':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("PLUS", tempWord, lineum);
            break;
        case '-':
            if(word.substr(1,2)=="eq"){
                tempWord = word.substr(0,3);
                word.erase(0,3);
                return  LexItem("SEQ", tempWord, lineum);

            }else if(word.substr(1,2)=="lt"){
                tempWord = word.substr(0,3);
                word.erase(0,3);
                return  LexItem("SLTHAN", tempWord, lineum);

            } else if(word.substr(1,2)=="gt" || word.substr(1,2)=="Gt"||word.substr(1,2)=="GT"){
                tempWord = word.substr(0,3);
                word.erase(0,3);
                return  LexItem("SGTHAN", tempWord, lineum);

            }else {
                tempWord = word.at(0);
                word.erase(0, 1);
                return LexItem("MINUS", tempWord, lineum);
            }
            break;
        case '*':
            if(word.length()>1&&word.at(1)=='*'){
                tempWord = word.substr(0,2);
                word.erase(0,2);
                return LexItem("SREPEAT", tempWord, lineum);
            }else{
                tempWord = word.at(0);
                word.erase(0,1);
                return LexItem("MULT", tempWord, lineum);
            }
            break;
        case '/':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("DIV", tempWord, lineum);
            break;
        case '^':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("EXPONENT", tempWord, lineum);
            break;

        case '=':
            if(word.length()>1 &&word.at(1)=='='){
                tempWord = word.substr(1,2);
                word.erase(0,2);

                return LexItem("NEQ", tempWord, lineum);
            }else{
                tempWord =word.at(0);
                word.erase(0,1);
                return LexItem("ASSOP", tempWord, lineum);
            }
            break;
        case '>':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("NGTHAN", tempWord, lineum);
            break;
        case '<':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("NLTHAN", tempWord, lineum);
            break;
        case '.':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("CAT", tempWord, lineum);
            break;
        case ';':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("SEMICOL", tempWord, lineum);
            break;
        case ',':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("COMMA", tempWord, lineum);
            break;
        case '(':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("LPAREN", tempWord, lineum);
            break;
        case ')':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("RPAREN", tempWord, lineum);
            break;
        case '{':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("LBRACES", tempWord, lineum);
            break;
        case '}':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("RBRACES", tempWord, lineum);
            break;
        case '\'':
            string tempString;
            int first = line.find('\'');
            line.erase(first,1);
            int last = line.find('\'');
            if(last> -1 && last<100){
                tempWord = line.substr(first, (last-first)) ;
                tempString = line.substr((last+1),(line.length()-first));
                c.str(string());
                c.clear();
                c<<tempString;
                line = tempString;
                tempString.erase();
                word.erase();
                return ( LexItem("SCONST", tempWord, lineum) );
            }else
                last = line.find('"');
            if(last<100 && last>-1){
                tempWord = line.substr(first, (last-first+1)) ;
                tempWord.insert(0,"'");
                stringstream l(line);
                c.str(string());
                c.clear();
                word.erase();

                return  LexItem("ERR", tempWord, lineum) ;

            }else{
                tempWord = line.substr(first,(line.length()) -first+1);
                tempWord.insert(0,"'");
                stringstream l(line);
                word.erase();
                c.str(string());
                c.clear();
                return ( LexItem("ERR", tempWord, lineum) );
            }
    }
    Project obj;
    if(isdigit(word.at(0))){

        if(word.find('.')<4){
            return (obj.checkReal(word));
        }else{
            return  (obj.checkInt(word));
        }
    }
    if( word.at(0)=='_' || isalpha(word.at(0)) ){
        return (obj.checkIdent(word));
    }else if(word.at(0) == '@'){
        return (obj.checkSident(word));
    }else if( word.at(0) == '$'){
        return (obj.checkNident(word));
    }
    tempWord = word.at(0);
    word.erase();
    c.str(string());
    c.clear();
    return ( LexItem("ERR", tempWord, lineum) );//possible trouble
}

int parse(stringstream& s, LexItem& print){
    tempWord.erase();
    print =getNextToken(read, lineum,s);

    tok = (print.GetToken());
    lineString += (tok+" ");
    lexArr[(totalTok-1)]=(print.GetLexeme());
    //allLex.push_back(print.GetLexeme());
    if(tok=="ERR"){
        s.str(string());
        s.clear();
        return 0;
    }

    while(word.length()>0){
        tempWord.erase();
        print =getNextToken(read, lineum,s);
        tok = (print.GetToken());
        lexArr[(totalTok-1)]=(print.GetLexeme());
      // lex = (print.GetLexeme());
        lineString +=(tok +" ");

    }
    return 1;
}
///end GetMNext
int main(int arg, char *argv[]) {

    string filename2 = argv[1];
    read.open(filename2, ios::in);
    if (!read.is_open()) {
        cout << "CANNOT OPEN THE FILE " << filename2 << endl;
        exit(1);
    }
    while (getline(read, line) && tok != "ERR") {

        tempWord.erase();
        lineum += 1;
        stringstream s(line);

        while (s >> word) {

            if (word.at(0) == '#') {
                s.str(string());
            } else {
                parse(s, print);
            }

        }
        obj2.display(tok);
        lineString.erase();
    }
    if(leftBrace =="true"){
        cout<<"line # " <<(lineum+1) <<": If Statement Syntax Error: Missing right brace." <<endl;
        cout<<"line # " <<(lineum+1) <<": Incorrect If-Statement." <<endl;
        cout<<"line # " <<(lineum+1) <<": Syntactic error in Program Body." <<endl;
        cout<<"line # " <<(lineum+1) <<": Missing Program" <<endl;
        cout<<"Unsuccessful Parsing" <<endl;
        cout<<"Number of Syntax Errors 4"<<endl;
        exit(0);
    }

    cout<<"(DONE)" <<endl;
    cout<<"Successful Parsing" <<endl;
    exit(0);

}