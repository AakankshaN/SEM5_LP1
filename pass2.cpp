// #include <bits/stdc++.h>
// using namespace std;

// int main()
// {
//     ifstream sin;
//     sin.open("SymbolTable.txt");

//     ifstream lin;
//     lin.open("LiteralTable.txt");

//     ifstream fin;
//     fin.open("IntermediateCode.txt");

//     ofstream fout;
//     fout.open("machine.txt");

//     string line, word;

//     vector<pair<string, int>> symtab;
//     while (getline(sin, line))
//     {
//         stringstream st(line);
//         st >> word;    
//         string label = word;

//         st >> word;
//         symtab.push_back({label,stoi(word)});
       
//     }
//     sin.close();

//     vector<pair<string, int>> littab;
//     while (getline(lin, line))
//     {
//         stringstream st(line);
//         st >> word;
//         string label = word;
//         st >> word;
//         littab.push_back({label, stoi(word)});
//     }
//     lin.close();


//     while (getline(fin, line))
//     {
//         stringstream st(line);
//         st >> word;
//         string cls, mnemonic;
//         cls = word.substr(1, 2);
//         mnemonic = word.substr(4, 2);

//         if (cls == "AD")
//         {
            
//             if (mnemonic == "05")
//             {
//                 st >> word;
//                 st >> word;
//                 word=word.substr(3,1);
//                 fout<<"(00)"<<" "<<"(0)"<<"("<<word<<")"<<endl;
//             }
//             else
//             {
//                 fout << " --No Machine Code--" << endl;
//             }
            
//         }
//         else if (cls == "IS")
//         {
//             fout << "(" << mnemonic << ")";
          
//             if (mnemonic == "00")
//             {
//                 fout << "(0) (000)" << endl;
//                 continue;
//             }
//             st >> word;
//             if (word[1] != 'S' && word[1] != 'L')
//             {
//                 word = word.substr(1, 1);
//                 fout <<"("<< word << ")";
//                 st >> word;
//             }
//             else
//             {
//                 fout << "(0)";
//             }

//             string temp = word.substr(3, 1);//
//             int num = stoi(temp);
//             //num--;
           
//             if (word[1] == 'S')
//             {
//                 fout <<"("<< symtab[num].second << ")"<<endl;
//             }
//             else if (word[1] == 'L')
//             {
//                 fout <<"(" << littab[num-1].second <<")"<< endl;
//             }
//         }
//         else if (cls == "DL")
//         {
            
//             if(mnemonic=="01")
//             {
//                 st>>word;
//                 fout<<"(00)"<<"(0) (00"<<word.substr(3,word.length()-4)<<")"<<endl;
//             }
//             else
//             {
//                 fout<<"No machine code"<<endl;
//             }
             
//         }
//     }
//     fout.close();
//     fin.close();
//     cout << "\nProgram Executed\n";

//     return 0;
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream sin("SymOutput.txt");
    ifstream lin("LitOutput.txt");
    ifstream fin("ICOutput.txt");
    ofstream fout("MachineOutput.txt");

    string mytext, word;

    vector<pair<string, int>> symtable;
    while (getline(sin, mytext)) {
        try {
            stringstream st(mytext);
            st >> word;

            string label = word;
            st >> word;
            symtable.push_back({label, stoi(word)});
        } catch (const std::invalid_argument &e) {
            cerr << e.what() << " used" << endl;
        }
    }
    sin.close();

    vector<pair<string, int>> litable;
    while (getline(lin, mytext)) {
        try {
            stringstream st(mytext);
            st >> word;

            string label = word.substr(1, word.length() - 2); // remove '=' and "'"
            st >> word;
            litable.push_back({label, stoi(word)});
        } catch (const std::invalid_argument &e) {
            cerr << e.what() << "Used" << endl;
        }
    }
    lin.close();

    int lc = -1;
    while (getline(fin, mytext)) {
        stringstream st(mytext);
        st >> word;

        string cls, mnemonic;
        cls = word.substr(1, 2);
        mnemonic = word.substr(4, 2);

        if (cls == "AD") {
            fout << "  No Machine Code  " << endl;

            if (mnemonic == "01") {
                try {
                    st >> word;
                    word = word.substr(3, word.length() - 4);
                    lc = stoi(word);
                } catch (const std::invalid_argument &e) {
                    cerr << e.what() << "used" << endl;
                }
            } else if (mnemonic == "03") {
                try {
                    st >> word;
                    word = word.substr(4, 1);
                    int ind = stoi(word);
                    ind--;
                    lc = symtable[ind].second;
                } catch (const std::invalid_argument &e) {
                    cerr << e.what() << " used" << endl;
                }
            }
        } else if (cls == "IS") {
            fout << lc << " " << mnemonic << " ";
            lc++;

            if (mnemonic == "00") {
                fout << "0 000" << endl;
                continue;
            }

            st >> word;
            if (word[1] != 'S' && word[1] != 'L') {
                word = word.substr(1, 1);
                fout << word << " ";
                st >> word;
            } else {
                fout << "0 ";
            }

            try {
                if (word[1] == 'S') {
                    string temp = word.substr(3, 2);
                    int num = stoi(temp);
                    num--;
                    fout << symtable[num].second << endl;
                } else if (word[1] == 'L') {
                    string temp = word.substr(3, 2);
                    int num = stoi(temp);
                    num--;
                    fout << litable[num].second << endl;
                }
            } catch (const std::invalid_argument &e) {
                cerr << e.what() << " used" << endl;
            }
        } else if (cls == "DL") {
            fout << lc << " ";
            lc++;

            if (mnemonic == "01") {
                fout << "00 0 ";
                st >> word;
                word = word.substr(3, 1);
                fout << "00" << word << endl;
            } else if (mnemonic == "02") {
                fout << "No Machine Code" << endl;
            }
        }
    }

    fin.close();
    fout.close();

    cout << "Program Executed";

    return 0;
}
