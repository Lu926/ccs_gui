#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#include "display.h"
#include "../smt/graphicize.h"
#include "../utilities/utilities.h"
#include "../smt/configuration.h"
#include "../smt/paths.h"
#include "../smt/cc-dubins.h"
#include "../smt/cc-rs.h"



// maximum curvature and derivative of curvature
double KappaMax = 1.0; //0.2;
double SigmaMax = 1.0; //0.05;

// start configuration
SMT_Configuration start (13.5, -4.1, -2.780, 0.8);
// end configuration
SMT_Configuration goal (0, 0, 0.785, 0);
// graphic trace mode toggle.  if TRUE then do not reset the graphic
// display window between two clicks
bool graphic_trace = false;
// graphic display and control windows
char *window_title = strdup("SMT");
FLTK_Display_Control control (100, 250, -250, 500, 500, window_title);

// test callback function: compute both cc-dubins and cc-reeds-shepp paths
void cb_dubins_rs (Fl_Widget *w, void *data) {
    FLTK_Display *display = static_cast<FLTK_Display*>(w);

    // reset graphic objects list
    if ( !graphic_trace ) display->clear_objects ();

    // retrieve clicked position
    double world_x = display_to_world_x (Fl::event_x (),
                                         display->get_unit_size (),
                                         display->get_scroll_x ());
    double world_y = display_to_world_y (Fl::event_y (),
                                         display->get_unit_size (),
                                         display->get_scroll_y ());
    // update end configuration
    goal.x = world_x;
    goal.y = world_y;

    float random = ((float) rand()) / (float) RAND_MAX;
    float r = random * 6.28;
    goal.theta = r;

    // compute cc-dubins path, display it in red
    SMT_CC_Dubins_Path *d_path;

    d_path = cc_dubins (start, goal, KappaMax, SigmaMax);
    d_path->print (true);		// alphanumeric display
    graphicize (*d_path, display, FL_RED, FL_SOLID, 0); // graphic display

    // compute cc-reeds-shepp path, display it in green
    SMT_CC_RS_Path *rs_path;

    rs_path = cc_reeds_shepp (start, goal, 1, 1);
    rs_path->print (true);	// alphanumeric display
    graphicize (*rs_path, display, FL_GREEN, FL_SOLID, 0); // graphic display

    // display start and end configuration in black
    graphicize (start, display, FL_BLACK, FL_SOLID, 0);
    graphicize (goal, display, FL_BLACK, FL_SOLID, 0);

    // update graphic display
    display->redraw ();
}


// test callback function: empty
void cb_empty (Fl_Widget *w, void *data) {
    FLTK_Display *display = (FLTK_Display *)w;

    // reset graphic objects list
    if ( !graphic_trace ) display->clear_objects ();

    // display start and end configuration in black
    graphicize (start, display, FL_BLACK, FL_SOLID, 0);
    graphicize (goal, display, FL_BLACK, FL_SOLID, 0);

    // update graphic display
    display->redraw ();
}

//// ############################################################################
//int main(int argc, char **argv)
//{
//  control.add_callback (cb_dubins_rs);
//  control.clear_objects ();

//  Fl::run();
//}


int main(int argc, char *argv[])
{
    control.add_callback (cb_dubins_rs);
    control.clear_objects ();

    Fl::run();

    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

    //    return a.exec();
    return 0;
}




