#include "notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTextBlock>
#include <QString>
#include <string>
#include <assembler.h>
#include <disassembler.h>
using namespace std;
Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionOpen_triggered()
{
    QString openFile = QFileDialog::getOpenFileName(this,"Open a File");
        if(!openFile.isEmpty())
        {
            fileName = openFile;
            QFile sFile(fileName);
            if(sFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&sFile);
                QString content = in.readAll();
                ui->textEdit->setPlainText(content);
                sFile.close();
            }
        }
}

void Notepad::on_actionSave_triggered()
{
    if(fileName.isEmpty())
        {
            fileName = QFileDialog::getSaveFileName(this,tr("Save File"), QString(),
                                                    tr("Text Files (*.txt);;assmenly files(*.asm *.ASM);;coe files (*.coe);;bin files(*.bin)"));
        }
        QFile sFile(fileName);
        if(sFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&sFile);
            out << ui->textEdit->toPlainText();
            out.flush();
            sFile.close();
            QMessageBox::information(this,"Notify","Saved");
        }
}


void Notepad::on_actionExit_triggered()
{
    close();
}

void Notepad::on_actionNew_triggered()
{
    fileName = "";  //文件名设置为空
        ui->textEdit->setPlainText(""); //纯文本设置为空
}

void Notepad::on_actionSave_As_triggered()
{
    fileName = QFileDialog::getSaveFileName(this,tr("Save File"), QString(),
                                            tr("Text Files (*.txt);;assmenly files(*.asm *.ASM);;coe files (*.coe);;bin files(*.bin)"));
    on_actionSave_triggered();
}



void Notepad::on_pushButton_clicked()
{
        QTextDocument *doc= ui->textEdit->document();
        QString in_buffer;
        QString out_buffer;
        QString FirstString;  //string shown first in each line
        int i;
        int Index;
        int LineNum=0;//count linenumber from 0
        QTextBlock tb;
        SymbolTable.clear();
        //Pass One: Construct the symbol table
        while(LineNum<(doc->lineCount())){
            tb=doc->findBlockByLineNumber(LineNum);
            QString in_buffer= tb.text();
            i=0;
            //skip all spaces and tabs
            while(in_buffer[i]==' '||in_buffer[i]=='\t')
                i++;
            //if the first nonspace chars are # or // then comment line, so continue to next line
            if(in_buffer[i]=='#'||(in_buffer[i]=='/'&&in_buffer[i+1]=='/'))
                continue;
            //read in the first string in each line
            while((in_buffer[i]>='a'&&in_buffer[i]<='z')||(in_buffer[i]>='A'&&in_buffer[i]<='Z')||in_buffer[i]=='.'||(in_buffer[i]>='0'&&in_buffer[i]<='9')){
                FirstString.append(in_buffer[i]);
                i++;
            }
            //if FirstString isn't a opcode then make an entry in the symbol table
            if(IsOpcode(FirstString)==-1){
                SymbolTable[FirstString]=LineNum*4;
            }
            FirstString.clear();
            in_buffer.clear();
            LineNum++;
        }


        in_buffer.clear();
        LineNum=0;

        while(LineNum<doc->lineCount()){
            tb=doc->findBlockByLineNumber(LineNum);
            QString in_buffer= tb.text();
            i=0;
            //skip all spaces and tabs
            while(in_buffer[i]==' '||in_buffer[i]=='\t')
                i++;
            //if the first nonspace chars are # or // then it is the comment line, so continue to next line
            if(in_buffer[i]=='#'||(in_buffer[i]=='/'&&in_buffer[i+1]=='/'))
                continue;
            //read in the first 'real' opcode in each line,skip ALL FLAGs
            while((in_buffer[i]>='a'&&in_buffer[i]<='z')||(in_buffer[i]>='A'&&in_buffer[i]<='Z')||in_buffer[i]=='.'||(in_buffer[i]>='0'&&in_buffer[i]<='9')){
                FirstString.append(in_buffer[i]);
                i++;
            }
            if(IsOpcode(FirstString)==-1){
                i++;
                FirstString.clear();
                while(in_buffer[i]==' '||in_buffer[i]=='$')
                    i++;
                while((in_buffer[i]>='a'&&in_buffer[i]<='z')||(in_buffer[i]>='A'&&in_buffer[i]<='Z')||in_buffer[i]=='.'||(in_buffer[i]>='0'&&in_buffer[i]<='9')){
                    FirstString.append(in_buffer[i]);
                    i++;
                }
            }
            //show the index of firststring in the string array
            Index=IsOpcode(FirstString);

            unsigned int instruction=0, instruction1=0, instruction2=0, addr,opcode,imme;
            int rt;
            //first 6 bits are all zeros
            if((Index>=8&&Index<=24)||(Index>=41&&Index<=46)||Index==50||Index==51||Index==53){
                instruction=Arith_RType(Index, in_buffer, i);
                binarycout(instruction, ui->textEdit_2);
            }
            else if(Index>=47&&Index<=49){
                instruction=Privilege(Index,in_buffer,i);
                binarycout(instruction, ui->textEdit_2);
            }
            else if((Index>=0&&Index<=7)||(Index>=25&&Index<=38)){
                instruction=IType(Index, in_buffer, i,LineNum);
                binarycout(instruction, ui->textEdit_2);
            }
            else if(Index==39||Index==40){
                instruction=JType(Index, in_buffer, i);
                binarycout(instruction, ui->textEdit_2);
            }
            else if(Index==52){//la
                rt=Find_reg_index(in_buffer, i);
                QString flag;
                while(in_buffer[i]=='\t'||in_buffer[i]==' ')
                    i++;
                while((in_buffer[i]>='0'&&in_buffer[i]<='9')||(in_buffer[i]>='a'&&in_buffer[i]<='z')||(in_buffer[i]>='A'&&in_buffer[i]<='Z')||in_buffer[i]=='.'){
                    flag.append(in_buffer[i]);
                    i++;
                }
                addr=SymbolTable[flag];

                imme=addr>>16;
                opcode=opvalue[30];
                instruction1|=imme;
                instruction1|=rt<<16;
                instruction1|=opcode<<26;
                binarycout(instruction1, ui->textEdit_2);

                opcode=opvalue[28];
                imme=addr&0xFFFF;
                instruction2|=imme;
                instruction2|=rt<<16;
                instruction2|=rt<<21;
                instruction2|=opcode<<26;
                binarycout(instruction2, ui->textEdit_2);
            }
            else if(Index==54){//li
                rt=Find_reg_index(in_buffer, i);
                addr=Find_num(in_buffer,i);

                imme=addr>>16;
                opcode=opvalue[30];
                instruction1|=imme;
                instruction1|=rt<<16;
                instruction1|=opcode<<26;
                binarycout(instruction1, ui->textEdit_2);

                opcode=opvalue[28];
                imme=addr&0xFFFF;
                instruction2|=imme;
                instruction2|=rt<<16;
                instruction2|=rt<<21;
                instruction2|=opcode<<26;
                binarycout(instruction2, ui->textEdit_2);
            }
            FirstString.clear();
            LineNum++;
        }

}

void Notepad::on_pushButton_2_clicked()
{
    QTextDocument *doc= ui->textEdit_2->document();
    string instruction,opcode,assembly;
    QTextBlock tb;
    QString assem;
    LabelCnt=0;
    LineCnt=0;
    SymbolTable2.clear();
    while(LineCnt<doc->lineCount()){
        tb=doc->findBlockByLineNumber(LineCnt);
        QString inst= tb.text();
        instruction=inst.toUtf8().constData();
        opcode.assign(instruction,0,6);
        if(opcode=="000100"||opcode=="000101"||opcode=="000110"||opcode=="000111"||opcode=="000001"){//beq bne blez bgtz bltz=bgez
            SaveAddrBranch(instruction);
        }
        else if(opcode=="000010"||opcode=="000011"){//jal j
            SaveAddrJump(instruction);
        }
        LineCnt++;
    }

    LineCnt=0;
    while(LineCnt<doc->lineCount()){
        tb=doc->findBlockByLineNumber(LineCnt);
        QString inst= tb.text();
        instruction=inst.toUtf8().constData();
        string str;
        opcode.assign(instruction,0,6);
        str.assign(instruction,26,6);
        if(opcode=="000000"&&(str=="001000"||str=="001001"))
            assembly=Jump2(instruction);
        else if(opcode=="000000")
            assembly=R_Arith(instruction);
        else if(FindOpIndex(opcode)>=0&&FindOpIndex(opcode)<=7)
            assembly=Load_Store(instruction);
        else if(FindOpIndex(opcode)>=25&&FindOpIndex(opcode)<=32)
            assembly=IType(instruction);
        else if(opcode=="000100"||opcode=="000101")//beq bne
            assembly=Branch1(instruction);
        else if(opcode=="000110"||opcode=="000111"){//blez bgtz
            assembly=Branch2(instruction);
        }
        else if(opcode=="000001"){//bltz bgez
            assembly=Branch3(instruction);
        }
        else if(opcode=="000010"||opcode=="000011"){//j jal
            assembly=Jump1(instruction);
        }
        assem=QString::fromUtf8(assembly.data(),assembly.size());
        ui->textEdit->append(assem);
        LineCnt++;
    }
}

void Notepad::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}

void Notepad::on_pushButton_4_clicked()
{
    ui->textEdit_2->clear();
}

void Notepad::on_actionOpen_2_triggered()
{
    QString openFile = QFileDialog::getOpenFileName(this,"Open a File");
    if(!openFile.isEmpty())
        {
            fileName = openFile;
            QFile sFile(fileName);
            if(sFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&sFile);
                QString content = in.readAll();
                ui->textEdit_2->setPlainText(content);
                sFile.close();
            }
        }
}

void Notepad::on_actionNew_2_triggered()
{
    fileName = "";  //文件名设置为空
    ui->textEdit_2->setPlainText(""); //纯文本设置为空
}

void Notepad::on_actionSave_2_triggered()
{
    if(fileName.isEmpty())
        {
            fileName = QFileDialog::getSaveFileName(this,tr("Save File"), QString(),
                                                    tr("Text Files (*.txt);;assmenly files(*.asm *.ASM);;coe files (*.coe);;bin files(*.bin)"));
        }
        QFile sFile(fileName);
        if(sFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&sFile);
            out << ui->textEdit_2->toPlainText();
            out.flush();
            sFile.close();
            QMessageBox::information(this,"Notify","Saved");
        }
}

void Notepad::on_actionSave_AS_triggered()
{
    fileName = QFileDialog::getSaveFileName(this,tr("Save File"), QString(),
                                            tr("Text Files (*.txt);;assmenly files(*.asm *.ASM);;coe files (*.coe);;bin files(*.bin)"));
    on_actionSave_2_triggered();
}
