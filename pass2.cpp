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

// #include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;

string table(ifstream &infile, const string &n) {
    string no, name, addr;
    while (infile >> no >> name >> addr) {
        if (no == n) {
            infile.clear(); 
            infile.seekg(0, ios::beg); 
            return addr;
        }
    }
    infile.clear(); 
    infile.seekg(0, ios::beg); 
    return "NAN";
}


int main(){
    ifstream ic, st, lt;
    ic.open("ic.txt");
    st.open("symtable.txt");
    lt.open("littable.txt");

    ofstream outfile;
    outfile.open("machinecode.txt");

    string lc, ic1, ic2, ic3;
    cout << "\n -- ASSEMBLER PASS-2 OUTPUT --" << endl;
	cout << "\n LC\t <INTERMEDIATE CODE>\t\t\tLC\t <MACHINE CODE>" << endl;

    while(ic >> lc >> ic1 >> ic2 >> ic3){
        string machine_code;
        // cout << ic1.substr(4,2)<<endl;

        if (ic1.substr(1,2) == "AD" || ((ic1.substr(1, 2) == "DL" && ic1.substr(4, 2) == "02"))){
            machine_code = "No Machine Code";
        }

        else if(ic1.substr(1,2) == "DL" && ic1.substr(4, 2) == "01"){
            machine_code = "00\t0\t00" + ic2.substr(3, 1);
        }
        else{
            if(ic1 == "(IS,00)") 
				machine_code = ic1.substr(4, 2) + "\t0\t000";
			else if(ic2.substr(1, 1) == "S") 
				machine_code = ic1.substr(4, 2) + "\t0\t" + table(st, ic2.substr(4, 1));
			else
			{
				if(ic3.substr(1, 1) == "S") 
					machine_code = ic1.substr(4, 2) + "\t" + ic2.substr(1, 1) + "\t" + table(st, ic3.substr(4, 1));
				else 
					machine_code = ic1.substr(4, 2) + "\t" + ic2.substr(1, 1) + "\t" + table(lt, ic3.substr(4, 1));
			}
		}

		if(ic1 == "(AD,03)") 
		{
			cout << " " << lc << "\t" << ic1 << "\t" << ic2 << " " << ic3 << "\t\t\t" << lc << "\t" << machine_code << endl;
			outfile << lc << "\t" << machine_code << endl;
			continue;
		}
		
		cout << " " << lc << "\t" << ic1 << "\t" << ic2 << "\t " << ic3 << "\t\t\t" << lc << "\t" << machine_code << endl;
		outfile << lc << "\t" << machine_code << endl;
        
    }

    return 0;
}

