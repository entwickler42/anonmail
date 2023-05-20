//---------------------------------------------------------------------------

#ifndef frmsplashH
#define frmsplashH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TSplash : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TImage *Image1;
private:	// Anwender-Deklarationen
public:		// Anwender-Deklarationen
    __fastcall TSplash(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSplash *Splash;
//---------------------------------------------------------------------------
#endif
