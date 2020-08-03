#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;
int code_length;

//-----------------------------------------
string do_op(string ag1, string ag2, string op){
    if (ag1=="NaN"||ag2=="NaN"){
        return "NaN";
    } else if (ag1=="infinity"||ag2=="infinity"){
        if (ag2=="infinity"&&(op=="/"||op=="%")){
            return "NaN";
        }
        return "infinity";
    }
    double ar1, ar2, ans;
    int arg1, arg2;
    string ret;
    stringstream answer;
    stringstream a1(ag1);
    if (op!="%"){
        a1 >> ar1;
    } else {
        a1 >> arg1;
    }
    stringstream a2(ag2);
    if (op!="%"){
        a2 >> ar2;
    } else {
        a2 >> arg2;
    }
    if (op=="+"){
        ans=ar1+ar2;
    } else if (op=="-"){
        ans=ar1-ar2;
    } else if (op=="*"){
        ans=ar1*ar2;
    } else if (op=="/"){
        if (ar2==0){
            return "NaN";
        }
        ans=ar1/ar2;
    } else if (op=="%"){
        if (arg2==0){
            return"NaN";
        }
        ans=arg1%arg2;
    } else {
        return "Error >> Operator"+op;
    }
    answer << ans;
    answer >> ret;
    return ret;
}
//-----------------------------------------
string evaluate(int type, string ex){ //Evaluator
    int var_num=0;
    string var_names[code_length];
    if (type==0){
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
    } else {
        
    }
}

//------------------------------------------
string UES(string u_ex){
    int p_depth=0, p_count=0, p_con=0, p_list=0, p_de[u_ex.size()+2], highest_b=0, p_count2, p_count3, stacks=0, prev_b=0, sub=0,p_count4,str;
    string p_store="", p_ex[u_ex.size()+2],p_chars="",out="abc";
    for (p_count=0;p_count<u_ex.size();p_count++){
        p_chars=u_ex[p_count];
        if (p_chars=="("){
            p_con=1;
            break;
        }
        
    }
    if (p_con==1){
        u_ex="("+u_ex+")";
        for (p_count=0;p_count<u_ex.size();p_count++){
            p_chars=u_ex[p_count];
            if (p_chars!="("&&p_chars!=")"){
                p_store=p_store+p_chars;
            } else if (p_chars=="("){
                if (p_store!=""){
                    p_de[p_list]=p_depth;
                    p_ex[p_list]=p_store;
                    p_store="";
                    p_list++;
                }
                p_depth++;
                if (p_depth>highest_b){
                    highest_b=p_depth;
                }
            } else if (p_chars==")"){
                if (p_store!=""){
                    p_de[p_list]=p_depth;
                    p_ex[p_list]=p_store;
                    p_store="";
                    p_list++;
                }
                p_depth--;
            }
        }
        stringstream er;
        for (p_count=0;p_count<p_list;p_count++){//Calculate Highest Brackets
                if (p_de[p_count]==highest_b){
                    p_de[p_count]=highest_b-1;
                    p_ex[p_count]=evaluate(0,p_ex[p_count]);
                    for (p_count4=0;p_count4<p_list;p_count4++){
                        er << "" << p_de[0] << p_ex[0] ;
                    }
                }
            }
        for(;highest_b!=0;highest_b--){
            stacks=0;
            prev_b=0;
            for (p_count=0;p_count<p_list;p_count++){
                if ((p_de[p_count]==highest_b-1)&&(prev_b!=1)){
                    stacks++;
                    prev_b=1;
                } else if (p_de[p_count]!=highest_b-1){
                    prev_b=0;
                }
            }
            p_count3=0;
            for (p_count=0;p_count<stacks;p_count++){
                for (p_count3=0;p_de[p_count3]!=highest_b-1;p_count3++){
                }
                p_store="";
                sub=0;
                for (p_count2=p_count3;p_de[p_count2]==highest_b-1;p_count2++){
                    p_store=p_store+p_ex[p_count2];
                    sub++;
                }
                p_ex[p_count2-1]=evaluate(0,p_store);
                p_de[p_count2-1]=highest_b-2;
                sub--;
                for (p_count2=p_count3;p_count2<p_list;p_count2++){
                    p_store=p_ex[p_count2+sub];
                    p_ex[p_count2]=p_store;
                    str=p_de[p_count2+sub];
                    p_de[p_count2]=str;
                }
                p_list=p_list-sub;
            }
        }
        out=p_ex[0];
    } else {
        out=evaluate(0,u_ex);
    }
    return out; 
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
                st_sto=UES(st_sto);
            }
            output=output+st_sto;
            st_sto="";
            st_string=0;
        } else if (st_char=="\"") {
            st_string=1;
        }
    }
    if (st_string==0){
        st_sto=evaluate(0,st_sto);
    }
    output=output+st_sto;
    return output;
}
//------------------------------------------

int main() { 
    int sl=0, ml=0, com_count;
    string code="", ch, temp_com, com_char;
    const string version="v0.1.0.2";
    ifstream read("Source.mkode");
    while (getline(read,ch)) {
        sl=0;
        temp_com="";
        for (com_count=0;com_count<ch.size();com_count++){
            com_char=ch[com_count];
            if (ch[com_count]=='#'){
                if (ch[com_count+1]=='\''){
                    ml=1;
                } else if (ml==1&&ch[com_count-1]=='\''){
                } else {
                    sl=1;
                }
            }
            if (sl!=1&&ml!=1){
                temp_com=temp_com.append(com_char);
            }
            if (com_char=="#"&&ch[com_count-1]=='\''){
                ml=0;
            }
        }
        code=code.append(temp_com);
    }
    if (code==""){
        system("cls");
        cerr << "Cant find source file/Empty source file (\"mkode.txt\" = void)";
        return 9;
    }
    read.close();
    //---------------------------------------
    code_length=code.size();
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
                            chars[4+line_start]=UES(chars[4+line_start]);
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
