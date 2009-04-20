#ifndef ALARM_WINDOW_H
#include "AlarmWindow.h"
#endif

#ifndef ALARM_VIEW_H
#include "AlarmView.h"
#endif

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _BUTTON_H
#include <Button.h>
#endif

#ifndef _MESSENGER_H
#include <Messenger.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#define BUTTON_ALARM_OK 'alok'
#define SET_ALARM 'salr'
#define ALARM_MSG 'alrm'

AlarmWindow :: AlarmWindow (BRect frame, BHandler *handler) : BWindow (frame, "Set alarm for this note", B_TITLED_WINDOW,B_NOT_RESIZABLE) {
	
    fMessenger = new BMessenger(handler);

//Istanzio la view AlarmView e la associo ad AlarmWindow
	
	frame.OffsetTo(B_ORIGIN);
	fAlarmView = new AlarmView(frame,"AlarmView");
	fAlarmView->SetViewColor(216, 216, 216);
	AddChild(fAlarmView);

//Istanzio i text field per l'inserimento dei dati
	
	hour=new BTextControl(BRect(20,30,100,35),   "hour",     "hour:", "", NULL);
	minute=new BTextControl(BRect(20,70,100,35), "minute",  "min:", "", NULL);
	day=new BTextControl(BRect(20,110,100,35),   "day",     "day:", "", NULL);
	month=new BTextControl(BRect(20,150,100,35), "month",    "month:", "", NULL);
	year=new BTextControl(BRect(20,190,100,35),  "year",     "year:", "", NULL);

//faccio in modo che il label del text field sia visibile

	hour->SetDivider(hour->StringWidth("hour:")+5);
	minute->SetDivider(minute->StringWidth("min:")+5);
	day->SetDivider(day->StringWidth("day:")+5);
	month->SetDivider(month->StringWidth("month:")+5);
	year->SetDivider(year->StringWidth("year:")+5);

//istanzio il bottone OK	
	
	fButtonOk = new BButton (BRect(400,230,450,240),	"ok", "OK", new BMessage(BUTTON_ALARM_OK));

//associo le text field e i bottoni alla view	
	fAlarmView->AddChild(hour);
	fAlarmView->AddChild(minute);
	fAlarmView->AddChild(day);
	fAlarmView->AddChild(month);
	fAlarmView->AddChild(year);

	fAlarmView->AddChild(fButtonOk);
	
	
	Show();
}


void AlarmWindow :: MessageReceived(BMessage* message) {
	switch (message -> what) {

		case BUTTON_ALARM_OK: {
		
		//quando premo il bottone OK parte il messaggio che "riempie" la struct
		//preparo i dati da includere nel messaggio
		
		const char *hourTextField;
		const char *minuteTextField;
		const char *dayTextField;
		const char *monthTextField;
		const char *yearTextField;

		hourTextField = hour->Text();
		minuteTextField = minute->Text();
		dayTextField = day->Text();
		monthTextField = month->Text();
		yearTextField = year->Text();

//si dovranno mettere un bel po' di controlli: stringhe vuote e dati inconsistenti

		BMessage *msg = new BMessage (ALARM_MSG);
		int16 i;
		
		i = atoi (hourTextField);
		msg -> AddInt16 ("hour", i);
		i = atoi (minuteTextField);
		msg -> AddInt16 ("minute", i);
		i = atoi (dayTextField);
		msg -> AddInt16 ("day", i);
		i = atoi (monthTextField);
		msg -> AddInt16 ("month", i);
		i = atoi (yearTextField);
		msg -> AddInt16 ("year", i);
//...........
		fMessenger->SendMessage(msg);



//Alla fine la finestra viene chiusa
		Quit();			
		}
			
		default:
			BWindow::MessageReceived(message);
	}
}