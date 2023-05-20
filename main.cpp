#include <vcl.h>
#include <winsock2.h>
#include "windns.h"

#pragma hdrstop

#include "main.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TInterface *Interface;

extern "C" char* encode_b64_file(char* file, unsigned int* size);

//---------------------------------------------------------------------------
__fastcall TInterface::TInterface(TComponent* Owner) : TForm(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TInterface::BtnQuitClick(TObject *Sender)
{
    Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TInterface::CheckBox1Click(TObject *Sender)
{
    FakeTo->Enabled = CheckBox1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TInterface::cbAttachClick(TObject *Sender)
{
    Attachment->Enabled = cbAttach->Checked;
    AName->Enabled      = cbAttach->Checked;
    btnAttach->Enabled  = cbAttach->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TInterface::BtnSendMailClick(TObject *Sender)
{
    int cs;
    WSAData data;
    char buf[512];
    char *cipher;
    unsigned long addr;
    unsigned int c_size;
    struct hostent* host;
    struct sockaddr_in server;

    WSAStartup(MAKEWORD(1,1),&data);

    // Resolve inet_addr for server
    host = gethostbyname(Server->Text.c_str());
    if(host == NULL)    addr = inet_addr(Server->Text.c_str());
    else                memcpy(&addr,host->h_addr_list[0],4);

    if(addr == INADDR_NONE)
    {
        Application->MessageBoxA("Can not resolve server address !","Error",MB_OK);
        return;
    }

    server.sin_family        = AF_INET;
    server.sin_port          = htons(25);
    *(long*)&server.sin_addr = addr;
    memset(server.sin_zero,0,8);

    // create socket and connect remote mailserver
    cs = socket(AF_INET,SOCK_STREAM,0);

    if(connect(cs,(struct sockaddr*)&server,sizeof(struct sockaddr_in)) != 0)
    {
        Application->MessageBoxA("Can not connect to mailserver !","Error",MB_OK);
        closesocket(cs);
        return;
    }

    // send out the mail
    recv(cs,buf,512,0);

    strcpy(buf,"ehlo AnonMail\n");
    send(cs,buf,strlen(buf),0);
    recv(cs,buf,512,0);

    strcpy(buf,"MAIL FROM:<");
    strcat(buf,From->Text.c_str());
    strcat(buf,">\n");
    send(cs,buf,strlen(buf),0);
    recv(cs,buf,512,0);

    strcpy(buf,"RCPT TO:<");
    strcat(buf,To->Text.c_str());
    strcat(buf,">\n");
    send(cs,buf,strlen(buf),0);
    recv(cs,buf,512,0);

    strcpy(buf,"data\n");
    send(cs,buf,strlen(buf),0);
    recv(cs,buf,512,0);

    strcpy(buf,"From: ");
    strcat(buf,From->Text.c_str());
    strcat(buf,"\n");
    send(cs,buf,strlen(buf),0);

    strcpy(buf,"Subject: ");
    strcat(buf,Subject->Text.c_str());
    strcat(buf,"\n");
    send(cs,buf,strlen(buf),0);

    if(CheckBox1->Checked)
    {
        strcpy(buf,"To: ");
        strcat(buf,FakeTo->Text.c_str());
        strcat(buf,"\n");
        send(cs,buf,strlen(buf),0);
    }

    strcpy(buf,"Mine-Version: 1.0\nContent-Type: multipart/mixed;\n  boundary=\"----001\"\n\n");
    send(cs,buf,strlen(buf),0);

    strcpy(buf,"------001\nContent-Type: text/html; charset=ISO-8859-1\nContent-Transfer-Encoding: quoted-printable\n\n");
    send(cs,buf,strlen(buf),0);

    send(cs,Mail->Text.c_str(),Mail->Text.Length(),0);

    if(cbAttach->Checked)
    {
        strcpy(buf,"\n------001\nContent-Type: application/octet-stream;\n name=");
        strcat(buf,AName->Text.c_str());
        strcat(buf,"\nContent-Transfer-Encoding: base64\nContent-Disposition: attachment;\n filename=");
        strcat(buf,AName->Text.c_str());
        strcat(buf,"\n\n");
        send(cs,buf,strlen(buf),0);

        cipher = encode_b64_file(Attachment->Text.c_str(),&c_size);

        unsigned int j=0;
        for(unsigned int i=0; i<c_size; i++)
        {
            send(cs,cipher+i,1,0);
            if(j++ == 76)
            {
                send(cs,"\n",1,0);
                j = 0;
            }
        }

        strcpy(buf,"\n");
        send(cs,buf,1,0);
    }

    strcpy(buf,"\n------001--\n");
    send(cs,buf,strlen(buf),0);

    strcpy(buf,"\n.\n");
    send(cs,buf,strlen(buf),0);
    recv(cs,buf,512,0);

    strcpy(buf,"quit\n");
    send(cs,buf,strlen(buf),0);
    recv(cs,buf,512,0);

    closesocket(cs);
    WSACleanup();

    Application->MessageBoxA("Mail Procedure Done !","Message",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TInterface::LookupMxClick(TObject *Sender)
{
    PDNS_RECORD rr;
    char addr[256];     memset(addr,0,256);
    char srv[256];      memset(srv,0,256);
    char *ch = addr;

    strcpy(addr,To->Text.c_str());
    while(*ch != '@') ch++;
    strcpy(srv,++ch);

    if(DnsQuery(srv,DNS_TYPE_MX,DNS_QUERY_STANDARD,NULL,&rr,NULL)==0)
    {
        Server->Text = AnsiString(rr->Data.Mx.pNameExchange);
        DnsRecordListFree(rr,0x01);
    }
    else Server->Text = AnsiString("ERROR");
}
//---------------------------------------------------------------------------

void __fastcall TInterface::btnAttachClick(TObject *Sender)
{
    if(OpenDialog->Execute())
    {
        Attachment->Text = OpenDialog->FileName;
        Attachment->Hint = OpenDialog->FileName;
    }
}
//---------------------------------------------------------------------------

