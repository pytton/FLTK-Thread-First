#include "FL/Fl.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Button.H"
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

void StartDemo();


class MyWindow : public Fl_Window
{

public: 

	Fl_Button * m_pBtn;
	Fl_Output * m_pOutput;

	MyWindow():Fl_Window(500, 500)
	{
		m_pBtn = new Fl_Button(10,150,70,30, "Start");
		//Fl_Button btnStop(90,150,70,30, "Stop");
		//Fl_Button btnUp(10,200,70,30, "Up");
		//Fl_Button btnDown(90,200,70,30, "Down");

		//Fl_Input input(50,50,140,30,"Input");
		m_pOutput = new Fl_Output(50,300,140,30,"Out");

	}

};


void OnButtonClick(Fl_Widget * widget, void * pWidgetOutput)
{
	Fl_Button * pBtn = (Fl_Button *)  widget;
	//pBtn->label("Good Job");

	Fl_Output * pOutput = (Fl_Output *) pWidgetOutput;

	static BOOL bStop = FALSE; 

	int nBaseNum = 550;
	int i = 1; 
	for(i = 1; i<500 /*&& bStop==FALSE*/; i+=50)
	{
		char strLabel[64] = "";

		sprintf(strLabel, "%d", nBaseNum + i);
		pOutput->value(strLabel);
		//pOutput->redraw();
		//pOutput->show();
		Sleep(1000);

	}

	//pBtn->resize(10,150,140,30);

	pBtn->redraw();
}



void ButtonExample()
{
	Fl_Window myWndFirst(350,350, "My Wnd");
	//Fl_Box boxFLTK(100,100,105,105, "Hello FLTK, First Prog");
	//myWndFirst.show();
	myWndFirst.begin();

	Fl_Button btnStart(10,150,70,30, "Start");
	Fl_Button btnStop(90,150,70,30, "Stop");
	Fl_Button btnUp(10,200,70,30, "Up");
	Fl_Button btnDown(90,200,70,30, "Down");

	//Fl_Input input(50,50,140,30,"Input");
	Fl_Output output(50,300,140,30,"Out");

	//Fl_Input input(50, 50, 140, 30, "In"); //child 2 : 3rd widget
	//Fl_Output output(50, 100, 140, 30, "Out"); //child 3 : 4th widget


	myWndFirst.end();

	btnStart.callback(OnButtonClick, &output);

	myWndFirst.show();
	Fl::run();
}


int main()
{
	//ButtonExample();


	StartDemo();
	return 1;

	////Point pt1(20,50);
	//Fl_Window myWndFirst(250,250, "My Wnd");
	//Fl_Box boxFLTK(100,100,105,105, "Hello FLTK, First Prog");
	//myWndFirst.show();
	//Fl::run();

	return 1;
}