#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/x.H>
#include "FL/Fl_Output.H"
#include "FL/Fl_Window.H"


class CustomWnd : public Fl_Window
{
private:

	static CustomWnd * m_pSingletonWnd;

	CustomWnd::CustomWnd();

public:

	Fl_Output * m_pOutput;
	Fl_Button *m_pBtnStart;
	Fl_Button *m_pBtnStop;
	Fl_Button *m_pBtnUp;
	Fl_Button *m_pBtnDown;
	Fl_Widget * m_pSLider;
	int m_nCounter;

	int m_nBaseNum;

	BOOL m_bStartPressed;
	BOOL m_bStopPressed;
	BOOL m_bUpPressed;
	BOOL m_bDownPressed;

	//Fl_Progress *m_pProgressBar;

	static void  StartButtonClick(Fl_Widget * pWidget, void * pVoid);
	static void  StopButtonClick(Fl_Widget * pWidget, void * pVoid);
	static void  UpButtonClick(Fl_Widget * pWidget, void * pVoid);
	static void  DownButtonClick(Fl_Widget * pWidget, void * pVoid);

	static CustomWnd * CreateWnd();

	void ResetAllButtons();
};

