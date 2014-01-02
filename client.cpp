// native includes
#include <iostream>

// FLTK
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <Fl/Fl_Text_Display.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Sys_Menu_Bar.H>

// CEF
#import "include/cef_app.h"
#import "include/cef_base.h"
#import "include/cef_browser.h"
#import "include/cef_client.h"
#import "include/cef_command_line.h"
#import "include/cef_frame.h"
#import "include/cef_runnable.h"

// Fixups
#ifdef __APPLE__
#import "include/cef_application_mac.h"
#endif

// other includes
#include "simple_app.h"
#include "simple_handler.h"


// We need to extend here, and call the previous constructor, adding to it too.
Fl_CEF_Window::Fl_CEF_Window(int height, int width) : Fl_Window(height, width) {
	// openApp
}
Fl_CEF_Window::~Fl_CEF_Window() {
	// Called when we're effectively killing the window
}
void Fl_CEF_Window::applicationShouldTerminate() {
	// Request that all browser windows close.
	if (SimpleHandler* handler = SimpleHandler::GetInstance()) {
		handler->CloseAllBrowsers(false);
	}
}

// entry
int main(int argc, char **argv) {
  	// Provide CEF with command-line arguments.
  	CefMainArgs main_args(argc, argv);
  	
	// Start off with an FLTK window, we need one.
	Fl_CEF_Window *win = new Fl_CEF_Window(500,500);

  	// SimpleApp implements application-level callbacks. It will create the first
  	// browser instance in OnContextInitialized() after CEF has initialized.
  	CefRefPtr<SimpleApp> app(new SimpleApp(win));

  	// Specify CEF global settings here.
  	CefSettings settings;

  	// Initialize CEF for the browser process.
  	CefInitialize(main_args, settings, app.get());
  

  	// Run the CEF message loop. This will block until CefQuitMessageLoop() is
  	// called.
   	win->show();   	    
  	CefRunMessageLoop();

  	// Shut down CEF.
  	CefShutdown();
	win->end();

    return 0;
}
