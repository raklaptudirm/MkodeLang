#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

//-----------------------------------------
string do_op(string ag1, string ag2, string op){
    int ar1, ar2, ans;
    string ret;
    stringstream answer;
    stringstream a1(ag1);
    a1 >> ar1;
    stringstream a2(ag2);
    a2 >> ar2;
    if (op=="+"){
        ans=ar1+ar2;
    } else if (op=="-"){
        ans=ar1-ar2;
    } else if (op=="*"){
        ans=ar1*ar2;
    } else if (op=="/"){
        ans=ar1/ar2;
    } else if (op=="%"){
        ans=ar1%ar2;
    } else {
        return "Error >> Operator"+op;
    }
    answer << ans;
    answer >> ret;
    return ret;
}
//-----------------------------------------
string evaluate(string ex){ //Evaluator
    int st_count, st_list=0, last=1, st_count2, st_count3, pre, minus=0;
    string st_chars="", st_store="", calc[ex.size()];
    string temp;
    string precedence[]={"/","*","%","+","-"};
    for (st_count=0;st_count<ex.size();st_count++){//Seperating calc
        st_chars=ex[st_count];
        if ((st_chars!="+"&&st_chars!="-"&&st_chars!="*"&&st_chars!="/"&&st_chars!="%")||st_count==0){
            if (st_chars!=" "){
                st_store=st_store+st_chars;
                last=0;
            }
        } else {
            if (last==1){
                system("cls");
                cerr << "Two calc next to one another";
                return "2";
            }
            calc[st_list]=st_store;
            st_list++;
            calc[st_list]=st_chars;
            st_list++;
            last=1;
            st_store="";
        }
    }
    calc[st_list]=st_store;
    st_list++;

    for (st_count=0;st_count<5;st_count++){
        for (pre=1;pre<st_list;pre=pre+2){
            if (calc[pre]==precedence[st_count]){
                minus=0;
                if((calc[pre]=="+"||calc[pre]=="-")&&calc[pre-2]=="-"){
                    calc[pre-1]="-"+calc[pre-1];
                    minus=1;
                }
                st_store=do_op(calc[pre-1],calc[pre+1],calc[pre]);
                calc[pre+1]=st_store;
                calc[pre-1]="";
                calc[pre]="";

                st_count3=pre-1;
                if (minus==1){
                    calc[pre-2]="+";
                }
                //cout << "Count2 >> " << st_count3;
                //Expulsing voids----------------------------
                for (st_count2=st_count3;(st_count2+2)<st_list;st_count2++){
                    temp=calc[st_count2+2];
                    calc[st_count2]=temp;
                    pre=1;
                }
                st_list=st_list-2;
                pre=pre-2;
                //--------------------------------------------
                
            }
        }
    }
    return st_store;
}

//------------------------------------------
string parse(string st_parse) { //String Parser (for Console:out)
    string output="", st_char,st_sto="";
    int st_count, st_string=0;
    for (st_count=0;st_count<st_parse.size();st_count++){
        st_char=st_parse.at(st_count);
        if (st_char!="&"&&st_char!="\""){
            st_sto=st_sto+st_char;
        } else if (st_char=="&"){
            if (st_string==0){
                st_sto=evaluate(st_sto);
            }
            output=output+st_sto;
            st_sto="";
            st_string=0;
        } else if (st_char=="\"") {
            st_string=1;
        }
    }
    if (st_string==0){
        st_sto=evaluate(st_sto);
    }
    output=output+st_sto;
    return output;
}
//------------------------------------------

int main() { 
    string code="", ch;
    const string version="v0.1.2.7";
    ifstream read("mkode.txt");
    while (getline(read,ch)) {
        code=code.append(ch);
    }
    if (code==""){
        system("cls");
        cerr << "Cant find source file/Empty source file (\"mkode.txt\" = void)";
        return 9;
    }
    read.close();
    //---------------------------------------
    int err;//Lexer
    err=0;
    int count=0, listl=0;
    string chars[code.size()], store="";
    string character;
    for(count=0;count<code.size();count++) { //Breaking the code into tokens
        character=code.at(count);
             if ((character!=";")&&(character!=":")&&(character!="[")&&(character!="]")&&(character!="{")&&(character!="}")&&(character!="\\")&&(character!="=")) {
                 store=store+character;
             } else if (character=="\\") {
                 if (store!=""){
                     chars[listl]=store;
                 }
                 store="";
                 listl++;
                 store=character;
                 count++;
                 character=code.at(count);
                 store=store+character;
                 chars[listl]=store;
                 store="";
                 listl++;
             } else if (character==" ") {
                 if (store!=""){
                     chars[listl]=store;
                     listl++;
                 }
                 store="";
             } else {
                 if (store!=""){
                     chars[listl]=store;
                     listl++;
                 }
                 chars[listl]=character;
                 listl++;
                 store="";
             }
    }
    chars[listl]=store;
    int count2=0, extras=0;
    //-----------------------------------
    
    for (count=0;count<=listl;count++){ //Counting voids
        if (chars[count]==""){
            extras++;
        }
    }
    
    for (count=0;count<=listl;count++){ //Expulsing voids
        if (chars[count]==""){
            for (count2=count;count2<=listl;count2++){
                 store=chars[count2+1];
                chars[count2]=store;
            }
        } 
    }
   
    listl=listl-extras+1;
   
    /*for(count=1;count<=listl;count++) { //Printing tokens
        cout << count << ") " << chars[count-1] << endl;
    }*/
    //-----------------------------------
    int line=1, line_start=0,structure=0; //Structured Compiling
    string command;
    while (line_start<listl){
        if (chars[line_start+1]==":"){
            structure=1;//Library Method
        } else if (chars[line_start+1]=="="){
            structure = 2;//Variable initialization
        } else if (chars[line_start+1]=="["){
            structure= 3;//Loop, if, etc
        } else {
            system("cls");
            cerr << "Unidentified statement structure at line "<< line;
            return 3;
        }
        //-----------------------------------
        switch (structure){
            case (1):
                if (chars[0+line_start]=="Console"){
                    command = "Console";
                } else if (chars[0+line_start]=="Kode"){
                    command="Kode";
                } else {
                    system("cls");
                    cerr << "Illegal start to a statement >> line " << line;
                    return 1;
                    break;
                }
                if (command=="Console"){
                    if (chars[2+line_start]=="clear"){
                        if (chars[3+line_start]=="["&&chars[4+line_start]=="]"&&chars[5+line_start]==";"){
                            system("cls");
                            line_start=line_start+6;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2;
                        }

                    } else if (chars[2+line_start]=="nextLine"){
                        if (chars[3+line_start]=="["&&chars[5+line_start]=="]"&&chars[6+line_start]==";"){
                            chars[4+line_start]=evaluate(chars[4+line_start]);
                            stringstream s(chars[4+line_start]);
                            s >> count2;
                            for (count=0;count<count2;count++){
                                cout << endl;
                            }
                            line_start=line_start+7;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2;
                        }

                    } else if (chars[2+line_start]=="out"){
                        if (chars[3+line_start]=="["&&chars[5+line_start]=="]"&&chars[6+line_start]==";"){
                            store=parse(chars[4+line_start]);
                            cout << store;
                            line_start=line_start+7;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2; 
                        }
                    } else {
                        system("cls");
                        cerr << "Unexpected token >> " << chars[2+line_start] <<" at line >> " << line;
                        return 2;
                    }
                } else if (command=="Kode"){
                    if (chars[2+line_start]=="halt"){
                        if (chars[3+line_start]=="["&&chars[4+line_start]=="]"&&chars[5+line_start]==";"){
                            return 0;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2;
                        }
                    /*} else if (chars[2+line_start]=="in"){
                            if (chars[3+line_start]=="["&&chars[4+line_start]=="]"&&chars[5+line_start]==";"){
                            cout << "Coming soon!"
                            line_start=line_start+6;*/
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2;
                        }
                }
                break;
            case (2):
                system("cls");
                cerr << "Variable initialization not included in " << version;
                return 5;
                break;
            case (3):
                system("cls");
                cerr << "Loop statements are not included in " << version;
                return 5;
                break;
        }
        line++;
    }
    //-----------------------------------
    
    //-----------------------------------
    return 0;
}
