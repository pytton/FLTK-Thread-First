//.h



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#if defined(WIN32) && !defined(__CYGWIN__)
#  include <direct.h>
#  ifndef __WATCOMC__
// Visual C++ 2005 incorrectly displays a warning about the use of POSIX APIs
// on Windows, which is supposed to be POSIX compliant...
#    define chdir _chdir
#    define putenv _putenv
#  endif // !__WATCOMC__
#elif defined __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h> // for chdir()
#include <stdio.h>
#include <stdlib.h> // for system()
#include <string.h>
#else
#  include <unistd.h>
#endif
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/filename.H>
#include <FL/x.H>

#include "FL/Fl_Output.H"
#include "FL/Fl_Progress.H"
//#include <process.h>
#include "DemoMichael.h"


//////////////////////////////////////////////////////////////////////////
//FWD Declaration
int DemoThread();
int ProgressBarDemo();
//////////////////////////////////////////////////////////////////////////


CustomWnd * CustomWnd::m_pSingletonWnd=NULL;


void PrintNumbersInThreadUp(void * pVoidWnd)
{
	CustomWnd * pWnd  = (CustomWnd*)pVoidWnd;

	for (int i = 0; FALSE == pWnd->m_bStopPressed && FALSE == pWnd->m_bDownPressed && TRUE == pWnd->m_bUpPressed; ++i)
	{
		char strNumValue[128]="";
		int newBaseNumToPrint = (pWnd->m_nBaseNum + (pWnd->m_nCounter));
		pWnd->m_nBaseNum=newBaseNumToPrint;
		sprintf(strNumValue, "%d", pWnd->m_nBaseNum);
		pWnd->m_pOutput->value(strNumValue);

		//pWnd->m_pProgressBar->value(baseNum+i);  // update progress bar with 0.0 ~ 1.0 value

		Fl::check();                           // give fltk some cpu to update the screen
		Sleep(500);                          // 'your stuff' that's compute intensive
	}

}


void PrintNumbersInThreadDown(void * pVoidWnd)
{
	CustomWnd * pWnd  = (CustomWnd*)pVoidWnd;

	for (int i = 0; FALSE == pWnd->m_bStopPressed && TRUE == pWnd->m_bDownPressed && FALSE == pWnd->m_bUpPressed; ++i)
	{
		char strNumValue[128]="";
		int newBaseNumToPrint = (pWnd->m_nBaseNum + (pWnd->m_nCounter));
		pWnd->m_nBaseNum=newBaseNumToPrint;
		sprintf(strNumValue, "%d", pWnd->m_nBaseNum);
		pWnd->m_pOutput->value(strNumValue);

		//pWnd->m_pProgressBar->value(baseNum+i);  // update progress bar with 0.0 ~ 1.0 value

		Fl::check();                           // give fltk some cpu to update the screen
		Sleep(500);                          // 'your stuff' that's compute intensive
	}

}

void  CustomWnd::StartButtonClick(Fl_Widget * pWidget, void * pVoid)
{

	static int baseNum = 550;

	CustomWnd * pWnd  = (CustomWnd*)pVoid;

	pWnd->m_bStopPressed = FALSE;
	pWnd->m_bStartPressed = TRUE;

	char strNumValue[128]="";
	int newBaseNumToPrint = pWnd->m_nBaseNum;
	sprintf(strNumValue, "%d", pWnd->m_nBaseNum);
	pWnd->m_pOutput->value(strNumValue);

	/*
	for (int i = 0; i < 200 && FALSE == pWnd->m_bStopPressed; i+=10)
	{
		char strNumValue[128]="";
		sprintf(strNumValue, "%d", baseNum+i);
		pWnd->m_pOutput->value(strNumValue);

		//pWnd->m_pProgressBar->value(baseNum+i);  // update progress bar with 0.0 ~ 1.0 value

		Fl::check();                           // give fltk some cpu to update the screen
		Sleep(1000);                          // 'your stuff' that's compute intensive
	}
	*/
}


void CustomWnd::ResetAllButtons()
{
	m_bStartPressed = FALSE;
	m_bStopPressed= FALSE;
	m_bUpPressed= FALSE;
	m_bDownPressed= FALSE;
}


void CustomWnd::StopButtonClick( Fl_Widget * pWidget, void * pVoid )
{
		CustomWnd * pWnd  = (CustomWnd*)pVoid;

		pWnd->m_bStopPressed = TRUE;
		pWnd->m_bStartPressed = FALSE;
}

void CustomWnd::UpButtonClick( Fl_Widget * pWidget, void * pVoid )
{
	CustomWnd * pWnd  = (CustomWnd*)pVoid;

	pWnd->m_bStopPressed = FALSE;
	pWnd->m_bStartPressed = TRUE;
	pWnd->m_bUpPressed = TRUE;
	pWnd->m_bDownPressed = FALSE;

	pWnd->m_nCounter = abs(pWnd->m_nCounter);

//	_beginthread( PrintNumbersInThreadUp, 0, pWnd);  --- commented out

}

void CustomWnd::DownButtonClick( Fl_Widget * pWidget, void * pVoid )
{
	CustomWnd * pWnd  = (CustomWnd*)pVoid;

	pWnd->m_bStopPressed = FALSE;
	pWnd->m_bStartPressed = TRUE;
	pWnd->m_bUpPressed = FALSE;
	pWnd->m_bDownPressed = TRUE;

	pWnd->m_nCounter = abs(pWnd->m_nCounter) * -1;

	_beginthread( PrintNumbersInThreadDown, 0, pWnd);
}


CustomWnd::CustomWnd():Fl_Window(500,500)
{

	m_bStartPressed = FALSE;
	m_bStopPressed= FALSE;
	m_bUpPressed= FALSE;
	m_bDownPressed= FALSE;

	m_nCounter = 40;
	m_nBaseNum = 550;

	this->begin();

	m_pBtnStart = new Fl_Button(10,80,80,20, "Start");
	m_pBtnStop = new Fl_Button(120,80,80,20, "Stop");
	m_pBtnUp = new Fl_Button(80,50,50,20, "Up");
	m_pBtnDown = new Fl_Button(80,120,50,20, "Down");
	m_pOutput = new Fl_Output(80,200,100,20,"Output");

	//m_pProgressBar = new Fl_Progress(80,250,100,20, "Number");

	this->end();

	m_pBtnStart->callback(StartButtonClick,this);
	m_pBtnStop->callback(StopButtonClick,this);
	m_pBtnUp->callback(UpButtonClick,this);
	m_pBtnDown->callback(DownButtonClick,this);

	m_pBtnStart->redraw();
	m_pBtnStop->redraw();
	m_pBtnUp->redraw();
	m_pBtnDown->redraw();
	m_pOutput->redraw();

	//m_pProgressBar->minimum(0);
	//m_pProgressBar->maximum(100000);
	//m_pProgressBar->redraw();
}


CustomWnd * CustomWnd::CreateWnd()
{
	if (NULL == m_pSingletonWnd)
	{
		m_pSingletonWnd = new CustomWnd();
	}


	return m_pSingletonWnd;
}

//
//void OnButtonClick(Fl_Widget * pWidget, void * pVoid)
//{
//	Fl_Button *pBtn = (Fl_Button *) pWidget;
//	pBtn->label("Button Clicked");
//	pBtn->redraw();
//
//}


void StartWindowInThread(void * pVoidWnd)
{
	CustomWnd * pCustomwWnd = (CustomWnd *) pVoidWnd;

	pCustomwWnd->show();
	Fl::run();
}


void StartDemo()
{
	//DemoThread();
	//ProgressBarDemo();
	//return;

	CustomWnd * pCustomwWnd = CustomWnd::CreateWnd();

	pCustomwWnd->show();


	//Fl::lock();
	//Fl_Window myWnd(500,500, "My First Window");
	//myWnd.begin();
	//Fl_Button myWndBtn(10,150,80,20, "Start");
	//myWndBtn.callback(OnButtonClick);
	//myWnd.end();
	//myWnd.show();

	Fl::run();

}

///////////////////////////////////////////////////////////////////////////////////////

//Multithreading Demo

void  silly( void *arg )
{
	printf( "The silly() function was passed %d\n", (INT_PTR)arg ) ;
}

int DemoThread()
{
	// Our program's first thread starts in the main() function.
	printf( "Now in the main() function.\n" );

	// Let's now create our second thread and ask it to start
	// in the silly() function.


	//_beginthread( silly, 0, (void*)12 );  -- comment out

	// From here on there are two separate threads executing
	// our one program.

	// This main thread can call the silly() function if it wants to.

	silly( (void*)-5 );
	Sleep( 100 );

	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////

void butt_cb(Fl_Widget *butt, void *data)
{
	// Deactivate the button
	butt->deactivate();                        // prevent button from being pressed again
	Fl::check();                               // give fltk some cpu to gray out button
	// Make the progress bar
	Fl_Window *w = (Fl_Window*)data;           // access parent window
	w->begin();                                // add progress bar to it..
	Fl_Progress *progress = new Fl_Progress(10,50,200,30);

	progress->minimum(0);                      // set progress range to be 0.0 ~ 1.0
	progress->maximum(1);
	progress->color(0x88888800);               // background color
	progress->selection_color(0x4444ff00);     // progress bar color
	progress->labelcolor(FL_WHITE);            // percent text color
	w->end();                                  // end adding to window
	// Computation loop..

	for ( int t=1; t<=500; t++ )
	{
		progress->value(t/500.0);              // update progress bar with 0.0 ~ 1.0 value
		char percent[10];
		sprintf(percent, "%d%%", int((t/500.0)*100.0));
		progress->label(percent);              // update progress bar's label
		Fl::check();                           // give fltk some cpu to update the screen
		Sleep(1000);                          // 'your stuff' that's compute intensive
	}

	// Cleanup
	w->remove(progress);                       // remove progress bar from window
	delete(progress);                          // deallocate it
	butt->activate();                          // reactivate button
	w->redraw();                               // tell window to redraw now that progress removed
}


// Main
int ProgressBarDemo()
{
	Fl_Window win(220,90);
	Fl_Button butt(10,10,100,25,"Press");
	butt.callback(butt_cb, &win);
	win.resizable(win);
	win.show();
	return(Fl::run());
}
