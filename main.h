//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TInterface : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TBitBtn *BtnSendMail;
    TBitBtn *BtnQuit;
    TMemo *Mail;
    TLabel *Label1;
    TEdit *To;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *Subject;
    TLabel *Label4;
    TEdit *Server;
    TCheckBox *CheckBox1;
    TEdit *FakeTo;
    TLabel *Label5;
    TEdit *From;
    TBitBtn *LookupMx;
    TLabel *Label6;
    TEdit *Attachment;
    TCheckBox *cbAttach;
    TBitBtn *btnAttach;
    TOpenDialog *OpenDialog;
    TLabel *Label7;
    TEdit *AName;
    void __fastcall BtnQuitClick(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall BtnSendMailClick(TObject *Sender);
    void __fastcall LookupMxClick(TObject *Sender);
    void __fastcall cbAttachClick(TObject *Sender);
    void __fastcall btnAttachClick(TObject *Sender);
private:	// Anwender-Deklarationen
public:		// Anwender-Deklarationen
    __fastcall TInterface(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInterface *Interface;
//---------------------------------------------------------------------------
#endif
