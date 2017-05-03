#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <QString>
#include <QMap>
#include <QVector>
#include <QTextEdit>
//name array for all operation names
QString op_name[55]={                                                                                 //Index sequence
    "lw", "lb", "lbu", "lh", "lhu", "sw", "sb", "sh", "add", "addu", "sub", "subu", "slt", "sltu",  //0-13
    "and", "or", "xor", "nor", "sll", "srl", "sra", "mult","multu", "div", "divu", "addi", "addiu", "andi", //14-27
    "ori", "xori", "lui", "slti", "sltiu", "beq", "bne", "blez", "bgtz", "bltz", "bgez","j","jal",  //28-40
    "jalr","jr", "mfhi", "mflo", "mthi", "mtlo", "eret", "mfc0", "mtc0", "break", "syscall", "la",  //41-52
    "move", "li"                                                                                    //53-54
};
//1st representation of register name
QString reg_name_1[32] = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0",
    "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2",
    "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp",
    "sp", "fp", "ra"
};

QString reg_name_2[32] = {
    "R0","R1","R2","R3", "R4", "R5", "R6", "R7", "R8","R9", "R10", "R11","R12","R13","R14","R15","R16","R17","R18","R19",
    "R20","R21","R22","R23","R24","R25","R26","R27","R28","R29","R30","R31"
};

QString reg_name_3[32] = {
    "r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15","r16","r17","r18","r19","r20",
    "r21","r22","r23","r24","r25","r26","r27","r28","r29","r30","r31"
};

//store the opcode or the opfunc of operaton in the array in order
unsigned int opvalue[52] = {
    0x23, 0x20, 0x24, 0x21, 0x25, 0x2B, 0x28, 0x29, 0x20, 0x21,//0-9
    0x22, 0x23, 0x2A, 0x2B, 0x24, 0x25, 0x26, 0x27, 0x00, 0x02,//10-19
    0x03, 0x18, 0x19, 0x1A, 0x1B, 0x08, 0x09, 0x0C, 0x0D, 0x0E,//20-29
    0x0F, 0x0A, 0x0B, 0x04, 0x05, 0x06, 0x07, 0x01, 0x01, 0x02,//30-39
    0x03, 0x09, 0x08, 0x10, 0x12, 0x11, 0x13, 0x18, 0x10, 0x10,//40-49
    0x0D, 0x0C                                                 //50-51
};

QMap<QString, int> SymbolTable;//key is symbol value is the address of the symbol assuming the start address is 0

// find the name of operaton and return the type
int IsOpcode(QString name){
    int i;
    for(i=0;i<55;i++)
        if(name==op_name[i])
            return i;
    return -1;
}

int Find_reg_index(QString code, int& Position){
    int i;
    QString reg;
    while(code[Position]=='\t'||code[Position]==' '||code[Position]=='$'||code[Position]==','||code[Position]=='('||code[Position]==')')
          Position++;
    while((code[Position]>='0'&&code[Position]<='9')||(code[Position]>='a'&&code[Position]<='z')||(code[Position]>='A'&&code[Position]<='Z')){
        reg.append(code[Position]);
        Position++;
    }
    for(i=0;i<32;i++){
        if(reg==reg_name_1[i]||reg==reg_name_2[i]||reg==reg_name_3[i])
            return i;
    }
    return -1;
}

int StringToNum( QChar a){
    if(a=='0')
        return 0;
    else if(a=='1')
        return 1;
    else if(a=='2')
        return 2;
    else if(a=='3')
        return 3;
    else if(a=='4')
        return 4;
    else if(a=='5')
        return 5;
    else if(a=='6')
        return 6;
    else if(a=='7')
        return 7;
    else if(a=='8')
        return 8;
    else
        return 9;
}

int Find_num(QString code, int& Position){
    int num=0,num2;
    int flag=0;//whether negative or not
    while(code[Position]=='\t'||code[Position]==' '||code[Position]=='$'||code[Position]==','||code[Position]=='('||code[Position]==')')
        Position++;
    if(code[Position]=='-'){
        flag=1;
        Position++;
    }
    while(code[Position]>='0'&&code[Position]<='9'){
        num2=StringToNum(code[Position]);
        num=num*10+num2;
        Position++;
    }
    if(flag==1)
        return (-1)*num;
    return num;
}

unsigned int Arith_RType(int Index, QString code, int Position){//all opcode is 0
    QString operation=op_name[Index];
    unsigned int opcode, opfunc,instruction=0;
    int rs, rd, rt,sa;
    opcode=0;
    opfunc=opvalue[Index];
    instruction|=opfunc;
    if(Index>=8&&Index<=17){
        rd=Find_reg_index(code, Position);
        rs=Find_reg_index(code, Position);
        rt=Find_reg_index(code, Position);
        instruction|=rd<<11;
        instruction|=rt<<16;
        instruction|=rs<<21;
    }
    else if(Index>=18&&Index<=20){
        rd=Find_reg_index(code,Position);
        rt=Find_reg_index(code,Position);
        sa=Find_num(code,Position);
        sa&=0x0000FFFF;
        instruction|=sa<<6;
        instruction|=rd<<11;
        instruction|=rt<<16;
    }
    else if(Index>=21&&Index<=24){
        rs=Find_reg_index(code,Position);
        rt=Find_reg_index(code,Position);
        instruction|=rt<<16;
        instruction|=rs<<21;
    }
    else if(Index==41){//jalr
        rd=Find_reg_index(code,Position);
        rs=Find_reg_index(code,Position);
        if(rs==-1){
            rs=rd;
            rd=31;
        }
        instruction|=rd<<11;
        instruction|=rs<<21;
    }
    else if(Index==53){//move
        rd=Find_reg_index(code,Position);
        rs=Find_reg_index(code,Position);
        opfunc=0x20;
        instruction|=opfunc;
        instruction|=rd<<11;
        instruction|=rs<<21;
    }
    else if(Index==42||Index==45||Index==46){//jr,mthi,mtlo
        rs=Find_reg_index(code, Position);
        instruction|=rs<<21;
    }
    else if(Index==43||Index==44){
        rs=Find_reg_index(code, Position);
        instruction|=rs<<11;
    }
    else if(Index==50||Index==51){//break,syscall
        ;//do nothing
    }
    return instruction;
}

unsigned int Privilege(int Index, QString code, int Position){
    unsigned int opcode, opfunc, instruction=0;
    int rd,rt;
    opcode=0x10;
    if(Index==47){//eret
        opfunc=opvalue[Index];
        instruction|=opfunc;
        instruction|=1<<25;
        instruction|=opcode<<26;
    }
    else if(Index==48){//mfc0
        rt=Find_reg_index(code, Position);
        rd=Find_reg_index(code, Position);
        instruction|=rd<<11;
        instruction|=rt<<16;
        instruction|=opcode<<26;
    }
    else if(Index==49){//mtc0
        rt=Find_reg_index(code, Position);
        rd=Find_reg_index(code, Position);
        instruction|=rd<<11;
        instruction|=rt<<16;
        instruction|=4<<21;
        instruction|=opcode<<26;
    }
    return instruction;
}

unsigned int IType(int Index, QString code, int Position,int LineNum){
    unsigned int opcode,instruction=0;
    QString flag;
    opcode=opvalue[Index];
    int rt, rs,base,offset,imme;
    if(Index>=0&&Index<=7){
        rt=Find_reg_index(code, Position);
        offset=Find_num(code, Position);
        base=Find_reg_index(code, Position);
        offset&=0x0000FFFF;
        instruction|=offset;
        instruction|=rt<<16;
        instruction|=base<<21;
        instruction|=opcode<<26;
    }
    else if(Index>=25&&Index<=32&&Index!=30){
        rt=Find_reg_index(code, Position);
        rs=Find_reg_index(code, Position);
        imme=Find_num(code, Position);
        imme&=0x0000FFFF;
        instruction|=imme;
        instruction|=rt<<16;
        instruction|=rs<<21;
        instruction|=opcode<<26;
    }
    else if(Index==30){
        rt=Find_reg_index(code, Position);
        imme=Find_num(code, Position);
        imme&=0x0000FFFF;
        instruction|=imme;
        instruction|=rt<<16;
        instruction|=opcode<<26;
    }
    else if(Index>=33&&Index<=34){
        rs=Find_reg_index(code, Position);
        rt=Find_reg_index(code, Position);
        offset=Find_num(code, Position);
        if(offset==0){
            while(code[Position]=='\t'||code[Position]==' ')
                Position++;
            while((code[Position]>='0'&&code[Position]<='9')||(code[Position]>='a'&&code[Position]<='z')||(code[Position]>='A'&&code[Position]<='Z')||code[Position]=='.'){
                flag.append(code[Position]);
                Position++;
            }
            offset=SymbolTable[flag];
        }
        offset=offset-LineNum*4-4;
        offset=offset>>2;
        offset&=0x0000FFFF;
        instruction|=offset;
        instruction|=rt<<16;
        instruction|=rs<<21;
        instruction|=opcode<<26;
    }
    else if(Index>=35&&Index<=37){
        rs=Find_reg_index(code, Position);
        offset=Find_num(code, Position);
        if(offset==0){
            while(code[Position]=='\t'||code[Position]==' ')
                Position++;
            while((code[Position]>='0'&&code[Position]<='9')||(code[Position]>='a'&&code[Position]<='z')||(code[Position]>='A'&&code[Position]<='Z')||code[Position]=='.'){
                flag.append(code[Position]);
                Position++;
            }
            offset=SymbolTable[flag];
        }
        offset=offset-LineNum*4-4;
        offset=offset>>2;
        offset&=0x0000FFFF;
        instruction|=offset;
        instruction|=rs<<21;
        instruction|=opcode<<26;
    }
    else if(Index==38){
        rs=Find_reg_index(code, Position);
        offset=Find_num(code, Position);
        if(offset==0){
            while(code[Position]=='\t'||code[Position]==' ')
                Position++;
            while((code[Position]>='0'&&code[Position]<='9')||(code[Position]>='a'&&code[Position]<='z')||(code[Position]>='A'&&code[Position]<='Z')||code[Position]=='.'){
                flag.append(code[Position]);
                Position++;
            }
            offset=SymbolTable[flag];
        }
        offset=offset-LineNum*4-4;
        offset=offset>>2;
        offset&=0x0000FFFF;
        instruction|=offset;
        instruction|=1<<16;
        instruction|=rs<<21;
        instruction|=opcode<<26;
    }
    return instruction;
}

unsigned int JType(int Index, QString code, int Position){
    unsigned int target,instruction=0,opcode;
    QString flag;
    opcode=opvalue[Index];
    target=Find_num(code, Position);
    if(target==0){
        while(code[Position]=='\t'||code[Position]==' ')
            Position++;
        while((code[Position]>='0'&&code[Position]<='9')||(code[Position]>='a'&&code[Position]<='z')||(code[Position]>='A'&&code[Position]<='Z')||code[Position]=='.'){
            flag.append(code[Position]);
            Position++;
        }
        target=SymbolTable[flag];
    }
    target=target>>2;
    instruction|=target;
    instruction|=opcode<<26;
    return instruction;
}

QChar NumToString(int i){
    if(i==0)
        return '0';
    else if(i==1)
        return '1';
    else if(i==2)
        return '2';
    else if(i==3)
        return '3';
    else if(i==4)
        return '4';
    else if(i==5)
        return '5';
    else if(i==6)
        return '6';
    else if(i==7)
        return '7';
    else if(i==8)
        return '8';
    else
        return '9';
}

//put instruction out to output file
void binarycout(unsigned n,QTextEdit* edit){
    QChar c;
    QString str;
    for(int i=31;i>=0;i--){
        c=NumToString((n>>i)&1);
        str.append(c);
    }
    edit->append(str);
}

#endif // ASSEMBLER_H
