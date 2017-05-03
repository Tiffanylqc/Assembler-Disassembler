#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include <math.h>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
//name array for all operation names
string op_name2[43]={                                                                                 //Index sequence
    "lw", "lb", "lbu", "lh", "lhu", "sw", "sb", "sh", "add", "addu", "sub", "subu", "slt", "sltu",  //0-13
    "and", "or", "xor", "nor", "sll", "srl", "sra", "mult","multu", "div", "divu", "addi", "addiu", "andi", //14-27
    "ori", "xori", "lui", "slti", "sltiu", "beq", "bne", "blez", "bgtz", "bltz", "bgez","j","jal",  //28-40
    "jalr","jr",   //41-42
};
//1st representation of register name
string reg_name[32] = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0",
    "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2",
    "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp",
    "sp", "fp", "ra"
};

//store the opcode or the opfunc of operaton in the array in order
int opvalue2[43] = {
    0x23, 0x20, 0x24, 0x21, 0x25, 0x2B, 0x28, 0x29, 0x20, 0x21,//0-9
    0x22, 0x23, 0x2A, 0x2B, 0x24, 0x25, 0x26, 0x27, 0x00, 0x02,//10-19
    0x03, 0x18, 0x19, 0x1A, 0x1B, 0x08, 0x09, 0x0C, 0x0D, 0x0E,//20-29
    0x0F, 0x0A, 0x0B, 0x04, 0x05, 0x06, 0x07, 0x01, 0x01, 0x02,//30-39
    0x03, 0x09, 0x08, //40-42
};

int LineCnt;
int LabelCnt;
map<int,int> SymbolTable2;
int UnsignedStringToNum(string offset){
    int num=0;
    int len=offset.length();
    int i=len;
    while(i!=0){
        num+=(offset[len-i]-'0')*(pow(2,i-1));
        i--;
    }
    return num;
}

int SignedStringToNum(string offset){
    int num=0,neg=0;
    if(offset[0]=='1')
        neg=1;
    int len=offset.length();
    int i=len;
    while(i!=0){
        num+=(offset[len-i]-'0')*(pow(2,i-1));
        i--;
    }
    if(neg==0)
        return num;
    else
        return num-pow(2,len);
}

void SaveAddrBranch(string instruction){//offset is a signed number
    string offset;
    int address;
    offset.assign(instruction,16,16);
    address=SignedStringToNum(offset);
    address=address<<2;
    address=address+LineCnt*4;
    SymbolTable2[address+4]=LabelCnt;
    LabelCnt++;
}

void SaveAddrJump(string instruction){
    string target;
    int address;
    target.assign(instruction,6,26);
    address=UnsignedStringToNum(target);
    address=address<<2;
    address=address|0xF0000000;
    unsigned int temp;
    temp=(LineCnt*4)|0x0FFFFFFF;
    address=address&temp;
    SymbolTable2[address]=LabelCnt;
    LabelCnt++;
}

int FindOpIndex(string code){
    int num=UnsignedStringToNum(code);
    int i;
    for(i=0;i<43;i++)
        if(num==opvalue2[i])
            break;
    return i;
}

string  FindReg(string code){
    int num=UnsignedStringToNum(code);
    string reg;
    reg.append(reg_name[num]);
    return reg;
}

string FindOperation(string code){
    int num=UnsignedStringToNum(code);
    int i;
    for(i=0;i<43;i++)
        if(num==opvalue2[i])
            break;
    return op_name2[i];
}

string FindOperation1(string code){
    int num=UnsignedStringToNum(code);
    int i;
    for(i=8;i<=24;i++)
        if(num==opvalue2[i])
            break;
    return op_name2[i];
}

int FindOp(string code){
    int i;
    for(i=0;i<43;i++)
        if(code==op_name2[i])
            break;
    return i;
}

string R_Arith(string instruction){
    string func, rs, rt, rd, result,sa,str;
    int num;
    func.assign(instruction,26,6);
    func=FindOperation1(func);
    stringstream ss,ss1;
    int index=FindOp(func);

    if(index>=8&&index<=17){
        rs.assign(instruction,6,5);
        rt.assign(instruction,11,5);
        rd.assign(instruction,16,5);
        rs=FindReg(rs);
        rt=FindReg(rt);
        rd=FindReg(rd);

        int count;
        string label;
        if(SymbolTable2.find(LineCnt*4)!=SymbolTable2.end()){
            count=SymbolTable2[LineCnt*4];
            ss.str("");
            ss<<count;
            ss>>label;
            result.append("LABEL");
            result.append(label);
            result.append("\t");
        }
        else
            result.append("\t");
        result.append(func);
        result.append(" ");
        result.append(rd);
        result.append(",");
        result.append(rs);
        result.append(",");
        result.append(rt);
    }
    else if(index>=18&&index<=20){
        rt.assign(instruction,11,5);
        rd.assign(instruction,16,5);
        rd=FindReg(rd);
        rt=FindReg(rt);
        sa.assign(instruction,21,5);
        num=UnsignedStringToNum(sa);
        ss1.str("");
        ss1<<num;
        ss1>>str;
        int count;
        string label;
        if(SymbolTable2.find(LineCnt*4)!=SymbolTable2.end()){
            count=SymbolTable2[LineCnt*4];
            ss<<count;
            ss>>label;
            result.append("LABEL");
            result.append(label);
            result.append("\t");
        }
        else
            result.append("\t");
        result.append(func);
        result.append(" ");
        result.append(rd);
        result.append(",");
        result.append(rt);
        result.append(",");
        result.append(str);
    }
    else {
        rs.assign(instruction,6,5);
        rt.assign(instruction,11,5);
        rs=FindReg(rs);
        rt=FindReg(rt);

        int count;
        string label;
        if(SymbolTable2.find(LineCnt*4)!=SymbolTable2.end()){
            count=SymbolTable2[LineCnt*4];
            ss.str("");
            ss<<count;
            ss>>label;
            result.append("LABEL");
            result.append(label);
            result.append("\t");
        }
        else
            result.append("\t");
        result.append(func);
        result.append(" ");
        result.append(rs);
        result.append(",");
        result.append(rt);
    }
    return result;
}

string FindOperation2(string code){
    int num=UnsignedStringToNum(code);
    int i;
    for(i=0;i<=7;i++)
        if(num==opvalue2[i])
            break;
    return op_name2[i];
}

string Load_Store(string instruction){
    string base,rt,opcode,offstr,result,str;
    int offset;
    stringstream ss;
    opcode.assign(instruction,0,6);
    opcode=FindOperation2(opcode);
    base.assign(instruction,6,5);
    base=FindReg(base);
    rt.assign(instruction,11,5);
    rt=FindReg(rt);
    offstr.assign(instruction,16,16);
    offset=SignedStringToNum(offstr);
    ss.str("");
    ss<<offset;
    ss>>str;

    stringstream ss1;
    int count;
    string label;
    if(SymbolTable2.find(LineCnt*4)!=SymbolTable2.end()){
        count=SymbolTable2[LineCnt*4];
        ss1.str("");
        ss1<<count;
        ss1>>label;
        result.append("LABEL");
        result.append(label);
        result.append("\t");
    }
    else
        result.append("\t");

    result.append(opcode);
    result.append(" ");
    result.append(rt);
    result.append(",");
    result.append(str);
    result.append("(");
    result.append(base);
    result.append(")");
    return result;
}

string FindOperation3(string code){
    int num=UnsignedStringToNum(code);
    int i;
    for(i=25;i<=32;i++)
        if(num==opvalue2[i])
            break;
    return op_name2[i];
}

string IType(string instruction){
    string opcode, rt, rs, result, imme,str;
    int num;
    stringstream ss;
    opcode.assign(instruction,0,6);
    opcode=FindOperation3(opcode);
    int index=FindOp(opcode);
    if(index==30){
        rt.assign(instruction,11,5);
        rt=FindReg(rt);
        imme.assign(instruction,16,16);
        num=SignedStringToNum(imme);
        ss.str("");
        ss<<num;
        ss>>str;
        stringstream ss1;
        int count;
        string label;
        if(SymbolTable2.find(LineCnt*4)!=SymbolTable2.end()){
            count=SymbolTable2[LineCnt*4];
            ss1.str("");
            ss1<<count;
            ss1>>label;
            result.append("LABEL");
            result.append(label);
            result.append("\t");
        }
        else
            result.append("\t");
        result.append(opcode);
        result.append(" ");
        result.append(rt);
        result.append(",");
        result.append(str);
    }
    else {
        rs.assign(instruction,6,5);
        rs=FindReg(rs);
        rt.assign(instruction,11,5);
        rt=FindReg(rt);
        imme.assign(instruction,16,16);
        num=SignedStringToNum(imme);
        ss.str("");
        ss<<num;
        ss>>str;

        stringstream ss1;
        int count;
        string label;
        if(SymbolTable2.find(LineCnt*4)!=SymbolTable2.end()){
            count=SymbolTable2[LineCnt*4];
            ss1.str("");
            ss1<<count;
            ss1>>label;
            result.append("LABEL");
            result.append(label);
            result.append("\t");
        }
        else
            result.append("\t");
        result.append(opcode);
        result.append(" ");
        result.append(rt);
        result.append(",");
        result.append(rs);
        result.append(",");
        result.append(str);
    }
    return result;
}

string Branch1(string instruction){
    string result, opcode, rs, rt, offstr,str;
    int offset,label;
    stringstream ss,ss1;

    opcode.assign(instruction,0,6);
    opcode=FindOperation(opcode);
    rs.assign(instruction,6,5);
    rs=FindReg(rs);
    rt.assign(instruction,11,5);
    rt=FindReg(rt);
    offstr.assign(instruction,16,16);
    offset=SignedStringToNum(offstr);
    offset=offset<<2;
    offset=offset+LineCnt*4+4;
    label=SymbolTable2[offset];
    ss.str("");
    ss<<label;
    ss>>str;

    result.append("\t");
    result.append(opcode);
    result.append(" ");
    result.append(rs);
    result.append(",");
    result.append(rt);
    result.append(",");
    result.append("LABEL");
    result.append(str);
    return result;
}

string Branch2(string instruction){
    string result,opcode,offstr,str,rs;
    int address;
    int label;
    stringstream ss;

    opcode.assign(instruction,0,6);
    opcode=FindOperation(opcode);
    rs.assign(instruction,6,5);
    rs=FindReg(rs);

    offstr.assign(instruction,16,16);
    address=SignedStringToNum(offstr);
    address=address<<2;
    address=address+LineCnt*4+4;
    label=SymbolTable2[address];
    ss.str("");
    ss<<label;
    ss>>str;

    result.append("\t");
    result.append(opcode);
    result.append(" ");
    result.append(rs);
    result.append(",");
    result.append("LABEL");
    result.append(str);
    return result;
}

string Branch3(string instruction){
    string result,opcode,offstr,str,rs;
    stringstream ss;
    int offset,label;
    opcode.assign(instruction,11,5);
    if(opcode=="00000")
        opcode=op_name2[37];
    else
        opcode=op_name2[38];
    rs.assign(instruction,6,5);
    rs=FindReg(rs);
    offstr.assign(instruction,16,16);
    offset=SignedStringToNum(offstr);
    offset=offset<<2;
    offset=offset+LineCnt*4+4;
    label=SymbolTable2[offset];
    ss.str("");
    ss<<label;
    ss>>str;

    result.append("\t");
    result.append(opcode);
    result.append(" ");
    result.append(rs);
    result.append(",");
    result.append("LABEL");
    result.append(str);
    return result;
}

string FindOperation4(string code){
    int num=UnsignedStringToNum(code);
    int i;
    for(i=39;i<43;i++)
        if(num==opvalue2[i])
            break;
    return op_name2[i];
}

string Jump1(string instruction){
    string opcode,target,str,result;
    opcode.assign(instruction,0,6);
    opcode=FindOperation4(opcode);
    stringstream ss;
    int address;
    target.assign(instruction,6,26);
    address=UnsignedStringToNum(target);
    address=address<<2;
    address=address|0xF0000000;
    unsigned int temp;
    temp=(LineCnt*4)|0x0FFFFFFF;
    address=address&temp;
    int label;
    label=SymbolTable2[address];
    ss.str("");
    ss<<label;
    ss>>str;
    result.append("\t");
    result.append(opcode);
    result.append(" ");
    result.append("LABEL");
    result.append(str);
    return result;
}

string Jump2(string instruction){
    string result, opcode,rs;
    opcode.assign(instruction,26,6);
    opcode=FindOperation4(opcode);
    rs.assign(instruction,6,5);
    rs=FindReg(rs);
    result.append("\t");
    result.append(opcode);
    result.append(" ");
    result.append(rs);
    return result;
}

#endif // DISASSEMBLER_H
