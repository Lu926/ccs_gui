// *** File: display.cc
// *** Author(s): Th. Fraichard
// *** Last modified on 08 Aug 2008

// Description: definition de la classe FLTK_Display, widget d'affichage
// graphique, et de la classe FLTK_Display_Control, widget de controle associe.

#include <display.h>

// ############################################################################
// FLTK_Display
// ############################################################################
// callback(s)
void cb_empty_callback (Fl_Widget *, void *) {}

// constructeur(s)
FLTK_Display::FLTK_Display (const double _unit_size, 
			    const double _scroll_x, const double _scroll_y,
			    const int _w, const int _h, const char* _title) 
  : Fl_Double_Window (_w, _h, _title) 
{
  unit_size = init_unit_size = _unit_size;
  scroll_x = init_scroll_x = _scroll_x; 
  scroll_y = init_scroll_y = _scroll_y;
  callback (cb_empty_callback); resizable (this); end (); show ();
}

// reinitialisation de list_objects
void FLTK_Display::clear_objects ()
{
  // d'abord on desalloue les objets pointes par list_objects
  for (vector<FLTK_Graphic_Object *>::iterator index = list_objects.begin ();
       index != list_objects.end (); 
       ++index)
    { delete (*index); }
  // puis on reinitialise le vecteur list_objects
  list_objects.clear ();
}

// destructeur
FLTK_Display::~FLTK_Display ()
{
  clear_objects ();
}

// lecture des attributs
double FLTK_Display::get_init_unit_size () const { return init_unit_size; }
double FLTK_Display::get_init_scroll_x () const { return init_scroll_x; }
double FLTK_Display::get_init_scroll_y () const { return init_scroll_y; }
double FLTK_Display::get_unit_size () const { return unit_size; }
double FLTK_Display::get_scroll_x () const { return scroll_x; }
double FLTK_Display::get_scroll_y () const { return scroll_y; }
vector<FLTK_Graphic_Object *> FLTK_Display::get_list_objects () const {
  return list_objects; }

// ecriture des attributs
void FLTK_Display::set_unit_size (const double _unit_size) 
{ unit_size = _unit_size; }
void FLTK_Display::set_scroll_x (const double _scroll_x) 
{ scroll_x = _scroll_x; }
void FLTK_Display::set_scroll_y (const double _scroll_y) 
{ scroll_y = _scroll_y; }

// ajout d'un object graphique dans list_objects
void FLTK_Display::add_object (FLTK_Graphic_Object *object)
{ list_objects.push_back(object); }

// affichage graphique des objets de list_objects
void FLTK_Display::draw () 
{
  fl_clip (0, 0, w(), h());
  fl_color (FL_WHITE);		// fond blanc
  fl_rectf (0, 0, w(), h());

  fl_color (FL_GRAY);		// repere gris
  fl_line_style (FL_DASH);
  fl_line			// axes x et y
    (world_to_display_x (-0.25, get_unit_size (), get_scroll_x ()), 
     world_to_display_y (0, get_unit_size (), get_scroll_y ()), 
     world_to_display_x (1.25, get_unit_size (), get_scroll_x ()), 
     world_to_display_y (0, get_unit_size (), get_scroll_y ()));
  fl_line 
    (world_to_display_x (0, get_unit_size (), get_scroll_x ()), 
     world_to_display_y (-0.25, get_unit_size (), get_scroll_y ()),
     world_to_display_x (0, get_unit_size (), get_scroll_x ()), 
     world_to_display_y (1.25, get_unit_size (), get_scroll_y ()));
  fl_line_style (FL_SOLID);
  fl_line			// "tickmarks"
    (world_to_display_x (1, get_unit_size (), get_scroll_x ()), 
     world_to_display_y (-0.1, get_unit_size (), get_scroll_y ()), 
     world_to_display_x (1, get_unit_size (), get_scroll_x ()), 
     world_to_display_y (0.1, get_unit_size (), get_scroll_y ()));
  fl_line 
    (world_to_display_x (-0.1, get_unit_size (), get_scroll_x ()), 
     world_to_display_y (1, get_unit_size (), get_scroll_y ()),
     world_to_display_x (0.1, get_unit_size (), get_scroll_x ()), 
     world_to_display_y (1, get_unit_size (), get_scroll_y ()));

  // affichage des objets de list_objects
  for (vector<FLTK_Graphic_Object *>::iterator index = list_objects.begin ();
       index != list_objects.end (); 
       ++index)
    { 
      (*index)->draw (this);
    }
  fl_pop_clip();
}

// gestion des evenements
int FLTK_Display::handle (int event) 
{
  switch (event) {
  case FL_ENTER:
    // modification du curseur quand celui-ci entre dans la fenetre
    cursor (Fl_Cursor (18), FL_BLACK, FL_WHITE);
    return 1;
  case FL_LEAVE:
    // restauration du curseur quand celui-ci quitte la fenetre
    cursor (FL_CURSOR_DEFAULT, FL_BLACK, FL_WHITE);
    return 1;
  case FL_PUSH:
    // appel du callback (eventuellement defini par l'utilisateur)
    do_callback ();
    return 1;
  case FL_KEYBOARD:
    // appel du callback (eventuellement defini par l'utilisateur)
    do_callback ();
    return 1;
  default:
    return 0;
  }
}


// ############################################################################
// FLTK_Display_Control
// ############################################################################
// callbacks
// quit button
void cb_quit (Fl_Widget *w, void *data) 
{   
  FLTK_Display *display = (FLTK_Display *)data;
  display->hide ();
  w->window ()->hide ();
}

// clear button
void cb_clear (Fl_Widget *, void *data) 
  // reinitialisation de la liste des objets graphiques
{   
  FLTK_Display *display = (FLTK_Display *)data;
  display->clear_objects (); 
  display->redraw ();
}

// xfig output button
void cb_xfig (Fl_Widget *, void *data) 
{   
  FLTK_Display *display = (FLTK_Display *)data;
  // creation du nom du fichier de sortie
  char filename[100];
  sprintf (filename, "%s-output.fig", display->label());
  // ouverture du fichier de sortie xfig
  ofstream output (filename, ios::out);
  // entete du fichier xfig
  output << "#FIG 3.2" << endl << "Portrait" << endl << "Center" << endl 
	 << "Inches" << endl << "A4" << endl << "100.00" << endl 
	 << "Single" << endl << "-2" << endl << "1200 2" << endl 
	 << "# end of preamble" << endl
	 << "# definition of the grey colors" << endl
	 << "0 32 #202020" << endl // dark grey
	 << "0 33 #404040" << endl
	 << "0 34 #606060" << endl
	 << "0 35 #808080" << endl // medium grey
	 << "0 36 #A0A0A0" << endl
	 << "0 37 #C0C0C0" << endl
	 << "0 38 #E0E0E0" << endl; // light grey
  // repere
  int x1, x2, y1, y2;
  output << "# origin frame" << endl;
  output << "2 1 1 1 35 -1 100 0 -1 0.000 0 0 -1 0 0 2" << endl; // axe x
  x1 = xfig_x (-0.25); x2 = xfig_x (1.25);
  output << "     " << x1 << " " << 0  << " " << x2 << " " << 0 << endl;

  output << "2 1 1 1 35 -1 100 0 -1 0.000 0 0 -1 0 0 2" << endl; // tickmark y
  x2 = xfig_x (0.25); y1 = xfig_y (1);
  output << "     " << x1 << " " << y1 << " " << x2 << " " << y1 << endl;

  output << "2 1 1 1 35 -1 100 0 -1 0.000 0 0 -1 0 0 2" << endl; // axe y
  y1 = xfig_y (-0.25); y2 = xfig_y (1.25);
  output << "     " << 0 << " " << y1 << " " << 0 << " " << y2 << endl;

  output << "2 1 1 1 35 -1 100 0 -1 0.000 0 0 -1 0 0 2" << endl; // tickmark x
  x1 = xfig_x (1); y2 = xfig_y (0.25); 
  output << "     " << x1 << " " << y1 << " " << x1 << " " << y2 << endl;

  // "xfigicization" des objets de list_objects
  for (vector<FLTK_Graphic_Object *>::iterator index =
	 display->list_objects.begin (); 
       index != display->list_objects.end (); 
       ++index)
    { 
      //(*index)->print ();
      (*index)->xfigicize (output);
    }
  // fermeture du fichier de sortie xfig
  output.close ();
}

// zoom management group
void cb_zoom_plus (Fl_Widget *w, void *data)
  // la taille en pixel de l'unite est augmentee de 20%
{
  FLTK_Display *display = (FLTK_Display *)data;
  double unit_size = display->get_unit_size ();
  unit_size = unit_size * 1.2;
  display->set_unit_size (unit_size);
  display->redraw ();
  Fl_Group *g = (Fl_Group *)w->parent ();
//   g->child (1)-> label (form ("%.2f\n", unit_size));
  char label[100];
  sprintf (label,"%.2f\n", unit_size);
  g->child (1)-> label (label);
//
  g->window ()->redraw ();
}

void cb_zoom_minus (Fl_Widget *w, void *data) 
  // la taille en pixel de l'unite est diminuee de 20%
{
  FLTK_Display *display = (FLTK_Display *)data;
  double unit_size = display->get_unit_size ();
  unit_size = unit_size * 0.8;
  display->set_unit_size (unit_size);
  display->redraw ();
  Fl_Group *g = (Fl_Group *)w->parent ();
//   g->child (1)-> label (form ("%.2f\n", unit_size));
  char label[100];
  sprintf (label, "%.2f\n", unit_size);
  g->child (1)-> label (label);
//
  g->window ()->redraw ();
}

void cb_zoom_reset (Fl_Widget *w, void *data) 
  // la taille en pixel de l'unite est reinitialisee
{
  FLTK_Display *display = (FLTK_Display *)data;
  double unit_size = display->get_init_unit_size ();
  display->set_unit_size (unit_size);
  display->redraw ();
  Fl_Group *g = (Fl_Group *)w->parent ();
//   g->child (1)-> label (form ("%.2f\n", unit_size));
  char label[100];
  sprintf (label, "%.2f\n", unit_size);
  g->child (1)-> label (label);
//
  g->window ()->redraw ();
}

// scroll management group
void cb_scroll_up (Fl_Widget *w, void *data)
  // la fenetre "monte" de 20% sa taille verticale
{
  FLTK_Display *display = (FLTK_Display *)data;
  double scroll_y = display->get_scroll_y ();
  double height = display->h ();
  scroll_y = scroll_y - height / 5;
  display->set_scroll_y (scroll_y);
  display->redraw ();
  Fl_Group *g = (Fl_Group *)w->parent ();
//   g->child (2)-> label (form ("%.0f\n", scroll_y));
  char label[100];
  sprintf (label, "%.0f\n", scroll_y);
  g->child (2)-> label (label);
//
  g->window ()->redraw ();
}

void cb_scroll_down (Fl_Widget *w, void *data) 
  // la fenetre "descend" de 20% sa taille verticale
{
  FLTK_Display *display = (FLTK_Display *)data;
  double scroll_y = display->get_scroll_y ();
  double height = display->h ();
  scroll_y = scroll_y + height / 5;
  display->set_scroll_y (scroll_y);
  display->redraw ();
  Fl_Group *g = (Fl_Group *)w->parent ();
//   g->child (2)-> label (form ("%.0f\n", scroll_y));
  char label[100];
  sprintf (label, "%.0f\n", scroll_y);
  g->child (2)-> label (label);
//
  g->window ()->redraw ();
}

void cb_scroll_left (Fl_Widget *w, void *data) 
  // la fenetre "se deplace vers la gauche" de 20% sa taille horizontale
{
  FLTK_Display *display = (FLTK_Display *)data;
  double scroll_x = display->get_scroll_x ();
  double width = display->w ();
  scroll_x = scroll_x + width / 5;
  display->set_scroll_x (scroll_x);
  display->redraw ();
  Fl_Group *g = (Fl_Group *)w->parent ();
//   g->child (1)-> label (form ("%.0f\n", scroll_x));
  char label[100];
  sprintf (label, "%.0f\n", scroll_x);
  g->child (1)-> label (label);
//
  g->window ()->redraw ();
}

void cb_scroll_right (Fl_Widget *w, void *data) 
  // la fenetre "se deplace vers la droite" de 20% sa taille horizontale
{
  FLTK_Display *display = (FLTK_Display *)data;
  double scroll_x = display->get_scroll_x ();
  double width = display->w ();
  scroll_x = scroll_x - width / 5;
  display->set_scroll_x (scroll_x);
  display->redraw ();
  Fl_Group *g = (Fl_Group *)w->parent ();
//   g->child (1)-> label (form ("%.0f\n", scroll_x));
  char label[100];
  sprintf (label, "%.0f\n", scroll_x);
  g->child (1)-> label (label);
//
  g->window ()->redraw ();
}

void cb_scroll_reset (Fl_Widget *w, void *data) 
  // la fenetre "retrouve" sa position initiale
{
  FLTK_Display *display = (FLTK_Display *)data;
  double scroll_x = display->get_init_scroll_x ();
  double scroll_y = display->get_init_scroll_y ();
  display->set_scroll_x (scroll_x);
  display->set_scroll_y (scroll_y);
  display->redraw ();
  Fl_Group *g = (Fl_Group *)w->parent ();
//   g->child (1)-> label (form ("%.0f\n", scroll_x));
  char label[100];
  sprintf (label, "%.0f\n", scroll_x);
  g->child (1)-> label (label);
//   g->child (2)-> label (form ("%.0f\n", scroll_y));
  sprintf (label, "%.0f\n", scroll_y);
  g->child (2)-> label (label);
//
  g->window ()->redraw ();
}

// constructeur(s)
FLTK_Display_Control::FLTK_Display_Control (double _unit_size,
					    double _scroll_x, double _scroll_y,
					    int _w, int _h, char* _title)
  : Fl_Window (210, 140, _title),
    // quit button
    quit (0, 0, 62, 20, "Close"),
    // clear button
    clear (0, 0, 62, 20, "Clear"),
    // xfig output button
    xfig (0, 0, 62, 20, "Xfig"),
    // zoom management group
    zoom_group (0, 0, 85, 80, ""),
    zoom_title (5, 5, 75, 20, "Unit size"),
    zoom_value (30, 30, 50, 20),
    zoom_reset (30, 55, 50, 20, "Reset"),
    zoom_plus (5, 30, 20, 20, "+"),
    zoom_minus (5, 55, 20, 20, "-"),
    // scroll management group
    scroll_group (0, 0, 110, 105, ""),
    scroll_title (5, 5, 100, 20, "Scrolling"),
    scroll_value_x (30, 30, 50, 20), 
    scroll_value_y (30, 55, 50, 20),
    scroll_reset (5, 80, 100, 20, "Reset"),
    scroll_up (5, 55, 20 , 20, "u"),
    scroll_down (85, 55, 20, 20, "d"),
    scroll_left (5, 30, 20 , 20 , "l"),
    scroll_right (85, 30, 20 , 20 , "r")
{
  // mise a jour des labels de zoom_value, scroll_value_x et scroll_value_y
  char label1[100], label2[100], label3[100];
  sprintf (label1, "%.2f\n", _unit_size);
  sprintf (label2, "%.0f\n", _scroll_x );
  sprintf (label3, "%.0f\n", _scroll_x);
  zoom_value.label (label1);
  scroll_value_x.label (label2);
  scroll_value_y.label (label3);

  // creation du display
  display = new FLTK_Display (_unit_size, _scroll_x, _scroll_y, _w, _h,
			     _title);
  // quit button
  this->add (quit);
  quit.position (143, 5);
  quit.callback (cb_quit, display);
  // clear button
  this->add (clear);
  clear.position (5, 5);
  clear.callback (cb_clear, display);
  // xfig output button
  this->add (xfig);
  xfig.position (74, 5);
  xfig.callback (cb_xfig, display);
  // zoom management group
  zoom_group.begin ();
  zoom_group.add (zoom_title);
  zoom_group.add (zoom_value);
  zoom_group.add (zoom_reset);
  zoom_group.add (zoom_plus);
  zoom_group.add (zoom_minus);
  zoom_group.end ();
  zoom_group.box (FL_UP_BOX);
  zoom_value.box (FL_DOWN_BOX);
  zoom_value.align (FL_ALIGN_INSIDE | FL_ALIGN_RIGHT);
  zoom_plus.label(FL_SYMBOL_LABEL, "@8->");
  zoom_plus.callback (cb_zoom_plus, display);
  zoom_minus.label(FL_SYMBOL_LABEL, "@2->");
  zoom_minus.callback (cb_zoom_minus, display);
  zoom_reset.callback (cb_zoom_reset, display);
  this->add (zoom_group);
  zoom_group.position (5, 30);
  // scroll management group
  scroll_group.begin ();
  scroll_group.add (scroll_title);
  scroll_group.add (scroll_value_x);
  scroll_group.add (scroll_value_y);
  scroll_group.add (scroll_reset);
  scroll_group.add (scroll_up);
  scroll_group.add (scroll_down);
  scroll_group.add (scroll_left);
  scroll_group.add (scroll_right);
  scroll_group.end ();
  scroll_group.box (FL_UP_BOX);
  scroll_value_x.box (FL_DOWN_BOX);
  scroll_value_y.box (FL_DOWN_BOX);
  scroll_value_x.align (FL_ALIGN_INSIDE | FL_ALIGN_RIGHT);
  scroll_value_y.align (FL_ALIGN_INSIDE | FL_ALIGN_RIGHT);
  scroll_up.label (FL_SYMBOL_LABEL, "@8->");
  scroll_up.callback (cb_scroll_up, display);
  scroll_down.label (FL_SYMBOL_LABEL, "@2->");
  scroll_down.callback (cb_scroll_down, display);
  scroll_left.label (FL_SYMBOL_LABEL, "@4->");
  scroll_left.callback (cb_scroll_left, display);
  scroll_right.label (FL_SYMBOL_LABEL, "@6->");
  scroll_right.callback (cb_scroll_right, display);
  scroll_reset.callback (cb_scroll_reset, display);
  this->add (scroll_group);
  scroll_group.position (95, 30);

  end (); show ();
}

// ajout du callback
void FLTK_Display_Control::add_callback (void _callback (Fl_Widget *, void *))
{ display->callback (_callback); }

// suppression des objets graphiques
void FLTK_Display_Control::clear_objects () { display->clear_objects (); }

// ajout d'un object graphique
void FLTK_Display_Control::add_object (FLTK_Graphic_Object *object)
{ display->add_object (object); }

// mise a jour de l'affichage
void FLTK_Display_Control::redraw ()
{ display->redraw (); }

// conversion repere display -> repere monde 
double worldify_x (int x, FLTK_Display *display) {
  double unit_size = display->get_unit_size ();
  double scroll_x = display->get_scroll_x ();
  return (display_to_world_x (x, unit_size, scroll_x));
}

double worldify_y (int y, FLTK_Display *display) {
  double unit_size = display->get_unit_size ();
  double scroll_y = display->get_scroll_y ();
  return (display_to_world_y (y, unit_size, scroll_y));
}
