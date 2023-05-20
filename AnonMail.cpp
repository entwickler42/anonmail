#include <vcl.h>
#include "frmsplash.h"
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("main.cpp", Interface);
USEFORM("frmsplash.cpp", Splash);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        TSplash* splash = new TSplash(Application);
        splash->Show();


        while(splash->AlphaBlendValue < 255)
        {
            splash->AlphaBlendValue += 5;
            splash->Update();
            Sleep(10);
        }

        Sleep(1000);
        splash->Hide();
        delete splash;

        Application->Initialize();
        Application->CreateForm(__classid(TInterface), &Interface);

        Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
