#include "syntaxhilight.h"
#include "ui_syntaxhilight.h"

syntaxhilight::syntaxhilight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::syntaxhilight)
{
    ui->setupUi(this);
    syntaxhilight::initlang();
}

syntaxhilight::~syntaxhilight()
{
    delete ui;
}
void syntaxhilight::initlang()
{

  ui->codelist->addItem("Ada","ada");
  ui->codelist->addItem("Action Script 3","as3");
  ui->codelist->addItem("Auto Hot Key","autohotkey");
  ui->codelist->addItem("AppleScript","applescript");
  ui->codelist->addItem("Assembler","asm");
  ui->codelist->addItem("Bash(shell)","shell");
  ui->codelist->addItem("Bat(cmd)","bat");
  ui->codelist->addItem("C#","csharp");
  ui->codelist->addItem("Clojure","clj");
  ui->codelist->addItem("ColdFusion","coldfusion");
  ui->codelist->addItem("Cpp","cpp");
  ui->codelist->addItem("C","c");
  ui->codelist->addItem("Css","css");
  ui->codelist->addItem("Delphi","delphi");
  ui->codelist->addItem("Pascal","pascal");
  ui->codelist->addItem("Diff","diff");
  ui->codelist->addItem("Erlang","erlang");
  ui->codelist->addItem("F#","fsharp");
  ui->codelist->addItem("Groovy","groovy");
  ui->codelist->addItem("JavaSript","javascript");
  ui->codelist->addItem("Java","java");
  ui->codelist->addItem("Java Fx","javafx");
  ui->codelist->addItem("Latex","latex");
  ui->codelist->addItem("Lsl","lsl");
  ui->codelist->addItem("Lua","lua");
  ui->codelist->addItem("Mathematica","mathematica");
  ui->codelist->addItem("MatLab","matlab");
  ui->codelist->addItem("MatlabKey","matlabkey");
  ui->codelist->addItem("Nasm","nasm");
  ui->codelist->addItem("Objective C","objc");
  ui->codelist->addItem("Perl","perl");
  ui->codelist->addItem("Php","php");
  ui->codelist->addItem("Plain","text");
  ui->codelist->addItem("Power Shell","powershell");
  ui->codelist->addItem("Processing","processing");
  ui->codelist->addItem("Python","python");
  ui->codelist->addItem("RouterOS","ros");
  ui->codelist->addItem("RPG","rpgle");
  ui->codelist->addItem("Ruby","ruby");
  ui->codelist->addItem("Sahi Script","sahiscript");
  ui->codelist->addItem("Scala.","scala");
  ui->codelist->addItem("SQL","sql");
  ui->codelist->addItem("Visual Basic(.Net)","vb");
  ui->codelist->addItem("Xml","xml");
  ui->codelist->addItem("Yaml","yaml");

}

void syntaxhilight::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
/// #include "QDebug"
void syntaxhilight::on_codelist_activated(int index)
{
//qDebug()<<    ui->codelist->itemData(index,32);
}

QString syntaxhilight::gethtml()
{
    QString str="<p>[prevclass='brush: "+ui->codelist->itemData(ui->codelist->currentIndex(),32).toString()+";'pclass]"+ui->codetxt->toPlainText().toAscii()+"[/preclass]</p>";
    str.replace("\n","<br>");
  return str;
}

