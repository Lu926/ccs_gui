// *** File: graphic-objects.cc
// *** Author(s): Th. Fraichard
// *** Last modified on 04 Aug 2008

// Description: 

#include <graphic-objects.h>

// ############################################################################
// fonction utilitaire pour xfigicize: determination de la couleur, du
// style et de l'epaisseur dans le codage xfig.
void xfig_parametres (Fl_Color color, int style, int width,
		      int *out_color, int *out_style, int *out_width) {
  switch ( color ) {
  case FL_RED: *out_color = 4; break;
  case FL_GREEN: *out_color = 2; break;
  case FL_YELLOW: *out_color = 6; break;
  case FL_BLUE: *out_color = 1; break;
  case FL_MAGENTA: *out_color = 5; break;
  case FL_CYAN: *out_color = 3; break;
  case FL_WHITE: *out_color = 7; break;
  case FL_DARK3: *out_color = 32; break;
  case FL_DARK2: *out_color = 33; break;
  case FL_DARK1: *out_color = 33; break;
  case FL_GRAY: case FL_GRAY0: *out_color = 35; break;
  case FL_LIGHT1: *out_color = 36; break;
  case FL_LIGHT2: *out_color = 37; break;
  case FL_LIGHT3: *out_color = 38; break;
  default: *out_color = 0; break; // defaults to black
  }
  switch ( style ) {
  case FL_DASH : *out_style = 1; break;
  case FL_DOT: *out_style = 2; break;
  case FL_DASHDOT: *out_style = 3; break;
  case FL_DASHDOTDOT: *out_style = 4; break;
  default: *out_style = 0; break; // defaults to solid
  }
  if ( width == 0 ) { *out_width = 1; } // system default
  else { *out_width = width; } }

// fonction utilitaire pour xfigicize: calcul des coordonnees xfig. le
// repere xfig est indirect, il est au coin superieur gauche.  la
// resolution par defaut est de 1200 ppi
int xfig_x (double x) { return (int) (1200 * x); }
int xfig_y (double y) { return (int) (-1200 * y); }


// ############################################################################
// Class FLTK_Graphic_Object 
// ############################################################################
// constructeur(s)
FLTK_Graphic_Object::FLTK_Graphic_Object (Fl_Color _color,
					  int _style, int _width)
{ color = _color; style = _style; width = _width; }


// ############################################################################
// Class FLTK_Point
// ############################################################################
// constructeur(s)
FLTK_Point::FLTK_Point (double _x, double _y, Fl_Color _color, int _width) 
  : FLTK_Graphic_Object (_color, FL_SOLID, _width)
{ x = _x; y = _y; }

// affichage graphique de l'objet
void FLTK_Point::draw (FLTK_Display *display)
{
  double unit_size = display->get_unit_size ();
  double scroll_x = display->get_scroll_x ();
  double scroll_y = display->get_scroll_y ();
  double _x = world_to_display_x (x, unit_size, scroll_x);
  double _y = world_to_display_y (y, unit_size, scroll_y);
  Fl_Color old_color = fl_color ();
  fl_color (color);
  fl_line_style (style, width);
  fl_point ((int)_x, (int)_y);
  fl_line_style (0);
  fl_color (old_color); }

// affichage alphanumerique des attributs de l'objet
void FLTK_Point::print ()
{ cout << "Point: " << x << ", " << y << endl; }

// conversion de l'objet en objets xfig
void FLTK_Point::xfigicize (ofstream &output) {
  int out_color, out_style, out_width;
  xfig_parametres (color, style, width, &out_color, &out_style, &out_width);
  int _x = xfig_x (x);
  int _y = xfig_y (y);
  output << "# point: " << x << ", " << y << endl; 
  output << "2 1 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 0 0 -1 0 0 1" << endl;
  output << "     " << _x << " " << _y << endl; }


// ############################################################################
// Class FLTK_Cross
// ############################################################################
// constructeur(s)
FLTK_Cross::FLTK_Cross (double _x, double _y, double _size, 
			Fl_Color _color, int _style, int _width) 
  : FLTK_Graphic_Object (_color, _style, _width)
{ x = _x; y = _y; size = _size; }

// affichage graphique de l'objet
void FLTK_Cross::draw (FLTK_Display *display)
{
  double unit_size = display->get_unit_size ();
  double scroll_x = display->get_scroll_x ();
  double scroll_y = display->get_scroll_y ();
  double x1 = world_to_display_x (x - size, unit_size, scroll_x);
  double x2 = world_to_display_x (x + size, unit_size, scroll_x);
  double y1 = world_to_display_y (y - size, unit_size, scroll_y);
  double y2 = world_to_display_y (y + size, unit_size, scroll_y);
  Fl_Color old_color = fl_color ();
  fl_color (color);
  fl_line_style (style, width);
  fl_line (x1, y1, x2, y2);
  fl_line (x1, y2, x2, y1);
  fl_line_style (0);
  fl_color (old_color); }

// affichage alphanumerique des attributs de l'objet
void FLTK_Cross::print () {
  cout << "Cross: " << x << ", " << y << ", " << size << endl; }

// conversion de l'objet en objets xfig
void FLTK_Cross::xfigicize (ofstream &output) {
  int out_color, out_style, out_width;
  xfig_parametres (color, style, width, &out_color, &out_style, &out_width);
  int x1 = xfig_x (x - size);
  int x2 = xfig_x (x + size);
  int y1 = xfig_y (y - size);
  int y2 = xfig_y (y + size);
  output << "# cross: " << x << ", " << y << ", " << size << endl; 
  // premiere branche de la croix
  output << "2 1 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 0 0 -1 0 0 2" << endl;
  output << "     " << x1 << " " << y1  << " " << x2  << " " << y2 << endl;
  // deuxieme branche de la croix
  output << "2 1 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 0 0 -1 0 0 2" << endl;
  output << "     " << x1 << " " << y2  << " " << x2  << " " << y1 << endl; }


// ############################################################################
// Class FLTK_Plus
// ############################################################################
// constructeur(s)
FLTK_Plus::FLTK_Plus (double _x, double _y, double _size, 
		      Fl_Color _color, int _style, int _width) 
  : FLTK_Graphic_Object (_color, _style, _width)
{ x = _x; y = _y; size = _size; }

// affichage graphique de l'objet
void FLTK_Plus::draw (FLTK_Display *display)
{
  double unit_size = display->get_unit_size ();
  double scroll_x = display->get_scroll_x ();
  double scroll_y = display->get_scroll_y ();
  double x0 = world_to_display_x (x, unit_size, scroll_x);
  double x1 = world_to_display_x (x - size, unit_size, scroll_x);
  double x2 = world_to_display_x (x + size, unit_size, scroll_x);
  double y0 = world_to_display_y (y, unit_size, scroll_y);
  double y1 = world_to_display_y (y - size, unit_size, scroll_y);
  double y2 = world_to_display_y (y + size, unit_size, scroll_y);
  Fl_Color old_color = fl_color ();
  fl_color (color);
  fl_line_style (style, width);
  fl_line (x1, y0, x2, y0);
  fl_line (x0, y1, x0, y2);
  fl_line_style (0);
  fl_color (old_color); }

// affichage alphanumerique des attributs de l'objet
void FLTK_Plus::print ()
{ cout << "Plus: " << x << ", " << y << ", " << size << endl; }

// conversion de l'objet en objets xfig
void FLTK_Plus::xfigicize (ofstream &output) {
  int out_color, out_style, out_width;
  xfig_parametres (color, style, width, &out_color, &out_style, &out_width);
  int x0 = xfig_x (x);
  int x1 = xfig_x (x - size);
  int x2 = xfig_x (x + size);
  int y0 = xfig_y (y);
  int y1 = xfig_y (y - size);
  int y2 = xfig_y (y + size);
  output << "# plus: " << x << ", " << y << ", " << size << endl; 
  // premiere branche du plus
  output << "2 1 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 0 0 -1 0 0 2" << endl;
  output << "     " << x1 << " " << y0  << " " << x2  << " " << y0 << endl;
  // deuxieme branche du plus
  output << "2 1 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 0 0 -1 0 0 2" << endl;
  output << "     " << x0 << " " << y1  << " " << x0  << " " << y2 << endl; }


// ############################################################################
// Class FLTK_Line
// ############################################################################
// constructeur(s)
FLTK_Line::FLTK_Line (double _x1, double _y1, double _x2, double _y2, 
		      Fl_Color _color, int _style, int _width)
  : FLTK_Graphic_Object (_color, _style, _width)
{ x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2; }

// affichage graphique de l'objet
void FLTK_Line::draw (FLTK_Display *display)
{
  double unit_size = display->get_unit_size ();
  double scroll_x = display->get_scroll_x ();
  double scroll_y = display->get_scroll_y ();
  double _x1 = world_to_display_x (x1, unit_size, scroll_x);
  double _y1 = world_to_display_y (y1, unit_size, scroll_y);
  double _x2 = world_to_display_x (x2, unit_size, scroll_x);
  double _y2 = world_to_display_y (y2, unit_size, scroll_y);
  Fl_Color old_color = fl_color ();
  fl_color (color);
  fl_line_style (style, width);
  fl_line (_x1, _y1, _x2, _y2);
  fl_line_style (0);
  fl_color (old_color); }

// affichage alphanumerique des attributs de l'objet
void FLTK_Line::print ()
{ cout << "Line: " << x1 << ", " << y1 << " -> " << x2 << ", " << y2 << endl; }

// conversion de l'objet en objets xfig
void FLTK_Line::xfigicize (ofstream &output) {
  int out_color, out_style, out_width;
  xfig_parametres (color, style, width, &out_color, &out_style, &out_width);
  int _x1 = xfig_x (x1);
  int _x2 = xfig_x (x2);
  int _y1 = xfig_y (y1);
  int _y2 = xfig_y (y2);
  output << "# line: " << x1 << ", " << y1 << " -> " 
	 << x2 << ", " << y2 << endl; 
  output << "2 1 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 0 0 -1 0 0 2" << endl;
  output << "     " << _x1 << " " << _y1  << " " 
	 << _x2  << " " << _y2 << endl; }

// ############################################################################
// Class FLTK_Arc
// ############################################################################
// constructeur(s)
FLTK_Arc::FLTK_Arc (double _x1, double _y1, double _x2, double _y2, 
		    double _xc, double _yc, double _radius, bool _ccw,
		    Fl_Color _color, int _style, int _width)
  : FLTK_Graphic_Object (_color, _style, _width)
{
  x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2;  xc = _xc; yc = _yc;
  radius = _radius; ccw = _ccw;
  alpha1 = twopify (atan2 ((y1 - yc), (x1 - xc)));
  alpha2 = twopify (atan2 ((y2 - yc), (x2 - xc)));
  if (alpha1 < alpha2)
    if ( ccw )
      { length = (alpha2 - alpha1) * radius; }
    else
      { length = (2* Pi - alpha2 + alpha1) * radius; }
  else
    if ( ccw )
      { length = (2* Pi + alpha2 - alpha1) * radius; }
    else
      { length = (alpha1 - alpha2) * radius; }
}
 
// affichage de l'objet dans le widget graphique display
void FLTK_Arc::draw (FLTK_Display *display)
{ 
  double _xc = world_to_display_x (xc, display->get_unit_size (),
				   display->get_scroll_x ());
  double _yc = world_to_display_y (yc, display->get_unit_size (),
				   display->get_scroll_y ());
  double box_width = world_to_display_x (radius, display->get_unit_size (), 0);
  double _alpha1 = degrees (alpha1);
  double _alpha2 = degrees (alpha2);

  Fl_Color old_color = fl_color ();
  fl_color (color);
  fl_line_style (style, width);
  if (_alpha1 < _alpha2)
    if ( ccw )
      { fl_arc ((_xc - box_width), (_yc - box_width), 
		2 * box_width, 2 * box_width,
		_alpha1, _alpha2); }
    else
      { fl_arc ((_xc - box_width), (_yc - box_width), 
		2 * box_width, 2 * box_width,
		_alpha2, _alpha1 + 360); }
  else
    if ( ccw )
      { fl_arc ((_xc - box_width), (_yc - box_width), 
		2 * box_width, 2 * box_width,
		_alpha1, _alpha2 + 360); }
    else
      { fl_arc ((_xc - box_width), (_yc - box_width), 
		2 * box_width, 2 * box_width,
		_alpha1, _alpha2); }
  fl_line_style (0);
  fl_color (old_color);
}

// affichage alphanumerique des attributs de l'objet
void FLTK_Arc::print () { 
  cout << "Arc: " << x1 << ", " << y1 << " -> " << x2 << ", " << y2 
       << ", centre " << xc << ", " << yc << ", rayon " << radius 
       << ",  ccw " << ccw << ", angles (radians) " 
       << alpha1 << ", " << alpha2 << ", angles (degres) "
       << degrees (alpha1) << ", " << degrees (alpha2) << endl; }

// conversion de l'objet en objets xfig
void FLTK_Arc::xfigicize (ofstream &output) {
  int out_color, out_style, out_width;
  xfig_parametres (color, style, width, &out_color, &out_style, &out_width);
  float _xc = 1200 * xc;	// xfig demande un float dans ce cas
  float _yc = -1200 * yc;
  int _x1 = xfig_x (x1);
  int _x2 = xfig_x (x2);
  int _y1 = xfig_y (y1);
  int _y2 = xfig_y (y2);
  int _ccw;
  if ( ccw ) { _ccw = 1; } else { _ccw = 0; }
  // calcul d'un point intermediaire
  double delta, xi, yi;
  if (alpha1 < alpha2)
    if ( ccw )
      { delta = (alpha1 + alpha2) /2; }
    else
      { delta = (alpha1 + alpha2) /2 + Pi; }
  else
    if ( ccw )
      { delta = (alpha1 + alpha2) /2 + Pi; }
    else
      { delta = (alpha1 + alpha2) /2; }
  xi = xc + radius * cos (delta);
  yi = yc + radius * sin (delta);
  int _xi = xfig_x (xi);
  int _yi = xfig_y (yi);
  output << "# arc: " << x1 << ", " << y1 << " -> " << x2 << ", " << y2 
	 << ", centre " << xc << ", " << yc << ", rayon " << radius 
	 << ",  ccw " << ccw << ", angles (radians) " 
	 << alpha1 << ", " << alpha2 << ", angles (degres) "
	 << degrees (alpha1) << ", " << degrees (alpha2) << endl;  
  output << "5 1 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 0 " << _ccw << " 0 0 " 
	 << _xc << " " << _yc << " " 
	 << _x1 << " " << _y1 << " " 
	 << _xi << " " << _yi << " " 
	 << _x2 << " " << _y2 << endl; }


// ############################################################################
// Class FLTK_Circle
// ############################################################################
// constructeur(s)
FLTK_Circle::FLTK_Circle (double _xc, double _yc, double _radius,
			  Fl_Color _color, int _style, int _width) 
  : FLTK_Graphic_Object (_color, _style, _width)
{
  xc = _xc; yc = _yc; radius = _radius;  
}

// affichage de l'objet dans le widget graphique display
void FLTK_Circle::draw (FLTK_Display *display) {
  double _xc = world_to_display_x (xc, display->get_unit_size (),
				   display->get_scroll_x ());
  double _yc = world_to_display_y (yc, display->get_unit_size (),
				   display->get_scroll_y ());
  double box_width = world_to_display_x (radius, display->get_unit_size (), 0);

  Fl_Color old_color = fl_color ();
  fl_color (color);
  fl_line_style (style, width);
  fl_arc ((_xc - box_width), (_yc - box_width), 
	  2 * box_width, 2 * box_width, 0, 360);
  fl_line_style (0);
  fl_color (old_color); 
}

// affichage alphanumerique des attributs de l'objet
void FLTK_Circle::print () {
  cout << "Circle: (" << xc << ", " << yc << "), rayon " << radius << endl; }

// conversion de l'objet en objets xfig
void FLTK_Circle::xfigicize (ofstream &output) {
  int out_color, out_style, out_width;
  xfig_parametres (color, style, width, &out_color, &out_style, &out_width);
  int _xc = xfig_x (xc);
  int _yc = xfig_y (yc);
  int _radius = xfig_x (radius);
  int _x = xfig_x (xc + radius);
  int _y = xfig_y (yc);
  output << "# circle: (" << xc << ", " << yc << "), rayon " << radius << endl;
  output << "1 3 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 1 0.0 " << _xc << " " << _yc << " "
	 << _radius << " " << _radius << " " << _xc << " " << _yc << " "
	 << _x << " " << _y << endl;
}


// ############################################################################
// Class FLTK_Clothoid
// ############################################################################
// constructeur(s)
FLTK_Clothoid::FLTK_Clothoid (double _x1, double _y1, 
			      double _theta1, double _kappa1, 
			      double _x2, double _y2, 
			      double _theta2, double _kappa2,
			      double _sigma, bool _forward,
			      double _length,double _step,
			      Fl_Color _color, int _style, int _width)
  : FLTK_Graphic_Object (_color, _style, _width) {
  x1 = _x1; y1 = _y1; theta1 = twopify (_theta1); kappa1 = _kappa1;
  x2 = _x2; y2 = _y2; theta2 = twopify (_theta2); kappa2 = _kappa2; 
  sigma = _sigma; forward = _forward; length = _length; step = _step; }

// affichage de l'objet dans le widget graphique display
void FLTK_Clothoid::draw (FLTK_Display *display)
{
  double nb_steps = floor (length / step);
  double x_f, y_f, theta_f, kappa_f;

  Fl_Color old_color = fl_color ();
  fl_color (color);
  fl_line_style (style, width);
  fl_begin_line ();
  fl_vertex (world_to_display_x (x1, display->get_unit_size (),
				 display->get_scroll_x ()), 
	     world_to_display_y (y1, display->get_unit_size (),
				 display->get_scroll_y ()));
  for (int i = 1; i <= nb_steps; i++)
    {
      end_of_clothoid (x1, y1, theta1, kappa1, sigma, forward, i * step,
		       &x_f, &y_f, &theta_f, &kappa_f);
      fl_vertex (world_to_display_x (x_f, display->get_unit_size (),
				     display->get_scroll_x ()), 
		 world_to_display_y (y_f, display->get_unit_size (),
				     display->get_scroll_y ()));
    }
  fl_vertex (world_to_display_x (x2, display->get_unit_size (),
				 display->get_scroll_x ()), 
	     world_to_display_y (y2, display->get_unit_size (),
				 display->get_scroll_y ()));
  fl_end_line ();
  fl_line_style (0);
  fl_color (old_color); }

// affichage alphanumerique des attributs de l'objet
void FLTK_Clothoid::print () {
  cout << "Clotoide: " << x1 << ", " << y1 << ", " 
       << degrees (theta1) << ", " << kappa1 << " -> " 
       << x2 << ", " << y2 << ", " 
       << degrees (theta2) << ", " << kappa2 << ", sigma " << sigma;
  if ( forward ) { cout << ", forward"; } else { cout << ", backward"; } 
  cout << ", longueur " << length << ", step " << step << endl; }

// conversion de l'objet en objets xfig
void FLTK_Clothoid::xfigicize (ofstream &output) {
  int out_color, out_style, out_width;
  xfig_parametres (color, style, width, &out_color, &out_style, &out_width);
  double nb_steps = floor (length / step);
  double _x, _y, _theta, _kappa;

  output << "# clotoide: " << x1 << ", " << y1 << ", " 
	 << degrees (theta1) << ", " << kappa1 << " -> " 
	 << x2 << ", " << y2 << ", " 
	 << degrees (theta2) << ", " << kappa2 << ", sigma " << sigma;
  if ( forward ) { output << ", forward"; } else { output << ", backward"; } 
  output << ", longueur " << length << ", step " << step << endl; 
  output << "2 1 " << out_style << " " << out_width << " " << out_color
	 << " -1 100 0 -1 0.0 0 0 -1 0 0 " << nb_steps + 2 << endl;

  _x = xfig_x (x1); _y = xfig_y (y1);
  output << "     " << _x << " " << _y;
  for (int i = 1; i <= nb_steps; i++)
    {
      end_of_clothoid (x1, y1, theta1, kappa1, sigma, forward, i * step,
		       &_x, &_y, &_theta, &_kappa);
      
      _x = xfig_x (_x); _y = xfig_y (_y);
      output  << " " << _x << " " << _y;
    }
  _x = xfig_x (x2); _y = xfig_y (y2);
  output << " " << _x << " " << _y << endl;;
}
