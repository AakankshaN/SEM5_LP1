#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Asm {
private:
    unordered_map<string, int> symbolTable;      // Symbol table: label -> address
    vector<pair<string, int>> literalTable;      // Literal table: (literal, address)
    vector<int> poolTable;                       // Pool table: indices in the literal table
    unordered_map<string, pair<string, int>> IS; // Imperative Statements set
    unordered_map<string, pair<string, int>> AD; // Assembler Directives set
    unordered_map<string, pair<string, int>> DL; // Declarative Statements set
    unordered_map<string, int> REG_CC;           // Registers and Conditional Codes set

    vector<vector<string>> inputs; // Input lines
    int currentAddress;
    int literalPoolIndex;

    vector<string> intermediateCode; // Intermediate code

public:
    Asm() {
        IS["STOP"] = make_pair("IS", 00);
        IS["ADD"] = make_pair("IS", 01);
        IS["SUB"] = make_pair("IS", 02);
        IS["MUL"] = make_pair("IS", 03);
        IS["MOVER"] = make_pair("IS", 04);
        IS["MOVEM"] = make_pair("IS", 05);
        IS["COMP"] = make_pair("IS", 06);
        IS["BC"] = make_pair("IS", 07);
        IS["DIV"] = make_pair("IS", 8);
        IS["READ"] = make_pair("IS", 9);
        IS["PRINT"] = make_pair("IS", 10);

        AD["START"] = {"AD", 01};
        AD["END"] = {"AD", 02};
        AD["ORIGIN"] = {"AD", 03};
        AD["EQU"] = {"AD", 04};
        AD["LTORG"] = {"AD", 05};

        DL["DC"] = {"DL", 01};
        DL["DS"] = {"DL", 02};

        REG_CC["AREG"] = 01;
        REG_CC["BREG"] = 02;
        REG_CC["CREG"] = 03;
        REG_CC["DREG"] = 04;
        REG_CC["LT"] = 01;
        REG_CC["LE"] = 02;
        REG_CC["EQ"] = 03;
        REG_CC["GT"] = 04;
        REG_CC["GE"] = 05;
        REG_CC["ANY"] = 06;

        currentAddress = 0;
        literalPoolIndex = 0;
        poolTable.push_back(0); // Initial pool table entry
    }

    void readInputFromFile(const string& filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string label, instruction, operand1, operand2;
            ss >> label >> instruction >> operand1 >> operand2;
            inputs.push_back({label, instruction, operand1, operand2});
        }
        inputFile.close();
    }

    void processPassOne() {
        for (const auto& line : inputs) {
            string label = line[0];
            string instruction = line[1];
            string operand1 = line[2];
            string operand2 = line[3];

            // Process label
            if (label != "--" && !label.empty()) {
                symbolTable[label] = currentAddress;
            }

            // Process Imperative Statements
            if (IS.find(instruction) != IS.end()) {
                // string code = to_string(currentAddress)+" ";
                string code = "(" + IS[instruction].first + "," + to_string(IS[instruction].second) + ") ";
                code += getOperandCode(operand1) + " " + getOperandCode(operand2);
                intermediateCode.push_back(code);
                currentAddress++;
            }
            // Process Assembler Directives
            else if (AD.find(instruction) != AD.end()) {
                // string code = " -- ";
                string code = "(" + AD[instruction].first + "," + to_string(AD[instruction].second) + ") ";
                code += getOperandCode(operand1);
                intermediateCode.push_back(code);

                if (instruction == "START") {
                    currentAddress = stoi(operand1);
                }
                else if (instruction == "END") {
                    // Process literals for END
                    processLiterals();
                }
                else if (instruction == "ORIGIN") {
                    currentAddress = evaluateExpression(operand1);
                }
                else if (instruction == "EQU") {
                    symbolTable[label] = evaluateExpression(operand1);
                }
                else if (instruction == "LTORG") {
                    processLiterals();
                }
            }
            // Process Declarative Statements
            else if (DL.find(instruction) != DL.end()) {
                // string code = to_string(currentAddress)+" ";
                string code = "(" + DL[instruction].first + "," + to_string(DL[instruction].second) + ") ";
                code += getOperandCode(operand1);
                intermediateCode.push_back(code);

                if (instruction == "DC") {
                    currentAddress++;
                }
                else if (instruction == "DS") {
                    currentAddress += stoi(operand1);
                }
            }
        }
    }

    string getOperandCode(string operand) {
        if (operand == "--") {
            return "(C,--)";
        }
        else if (REG_CC.find(operand) != REG_CC.end()) {
            return "(R," + to_string(REG_CC[operand]) + ")";
        }
        else if (operand[0] == '=') {
            literalTable.push_back(make_pair(operand, -1)); // address will be updated later
            return "(L," + to_string(literalTable.size()) + ")";
        }
        else if (isdigit(operand[0])) {
            return "(C," + operand + ")";
        }
        else {
            return "(S," + to_string(symbolTable[operand] + 1) + ")";
        }
    }

    int evaluateExpression(string expr) {
        // For simplicity, assume expression is a single number or label
        if (isdigit(expr[0])) {
            return stoi(expr);
        }
        else if (symbolTable.find(expr) != symbolTable.end()) {
            return symbolTable[expr];
        }
        return 0; // Default if the label is not found
    }

    void processLiterals() {
        // Update addresses for literals in the pool
        for (int i = literalPoolIndex; i < literalTable.size(); ++i) {
            literalTable[i].second = currentAddress++;
        }

        // Update the pool table index
        literalPoolIndex = literalTable.size();
        poolTable.push_back(poolTable[poolTable.size()-1]+1);
    }

    void saveTablesToFile() {
        ofstream symbolFile("SymbolTable.txt");
        symbolFile << "Symbol Table:\n";
        for (const auto& entry : symbolTable) {
            symbolFile << entry.first << "\t" << entry.second << endl;
        }
        symbolFile.close();

        ofstream literalFile("LiteralTable.txt");
        literalFile << "Literal Table:\n";
        for (const auto& literal : literalTable) {
            literalFile << literal.first << "\t" << literal.second << endl;
        }
        literalFile.close();

        ofstream poolFile("PoolTable.txt");
        poolFile << "Pool Table:\n";
        for (const auto& poolIndex : poolTable) {
            poolFile << poolIndex << endl;
        }
        poolFile.close();

        ofstream intermediateFile("IntermediateCode.txt");
        intermediateFile << "Intermediate Code:\n";
        for (const auto& code : intermediateCode) {
            intermediateFile << code << endl;
        }
        intermediateFile.close();
    }
};

int main() {
    Asm assembler;

    assembler.readInputFromFile("Input.txt");
    cout<<"inp read"<<endl;
    assembler.processPassOne();
    cout<<"pass1 donne b4 saving in table"<<endl;
    assembler.saveTablesToFile();
    cout<<"pass 1 done";
    return 0;
}
