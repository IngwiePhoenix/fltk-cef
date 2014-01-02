// simple_app.cpp
#include "simple_app.h"
#include "simple_handler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"

#include <FL/x.H>
#include <string>

#ifdef __APPLE__
// This is a C/C++ api-thingy-ding to use ObjC from a Non objective-* scope. useful, as we already use it minimaly :)
// but lets first stick to mm.
#endif

SimpleApp::SimpleApp(Fl_CEF_Window *win) { this->window=win; }

void SimpleApp::OnContextInitialized() {
  REQUIRE_UI_THREAD();

  // Information used when creating the native window.
  CefWindowInfo window_info;
  #ifdef __APPLE__
  /*
  	We dont need to do anything here.
  	The browser will automatically grab the actual latest NSWindow and use it - although its an FLWindow.
  	Therefore, we do not need to use
  		CefWindowInfo -> setAsChild(NSView, x, y, h, w)
  	Bad thing is: we don't get all additional controls we may want.
  */
  #endif


#if defined(OS_WIN)
  // On Windows we need to specify certain flags that will be passed to
  // CreateWindowEx().
  window_info.SetAsPopup(NULL, "cefsimple");
#endif

  // SimpleHandler implements browser-level callbacks.
  CefRefPtr<SimpleHandler> handler(new SimpleHandler(this->window));

  // Specify CEF browser settings here.
  CefBrowserSettings browser_settings;

  std::string url;

  // Check if a "--url=" value was provided via the command-line. If so, use
  // that instead of the default URL.
  CefRefPtr<CefCommandLine> command_line =
      CefCommandLine::GetGlobalCommandLine();
  url = command_line->GetSwitchValue("url");
  if (url.empty())
    url = "http://www.google.com";

  // Create the first browser window.
  CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url, browser_settings);
}
