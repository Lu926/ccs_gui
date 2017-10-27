// *** File: graphic-objects.h
// *** Author(s): Th. Fraichard
// *** Last modified on 04 Aug 2008

// Description:

#ifndef GRAPHIC_OBJECTS_H
#define GRAPHIC_OBJECTS_H

class FLTK_Display;

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <math.h>

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>

#include <utilities.h>
#include <display.h>

// ############################################################################
// fonction utilitaire pour xfigicize: calcul des coordonnees xfig. le
// repere xfig est indirect, il est au coin superieur gauche.  la
// resolution par defaut est de 1200 ppi
int xfig_x (double x);
int xfig_y (double y);

// ############################################################################
/**
 * \ingroup FLTK_Display
 * \brief Objet graphique g�n�rique destin� � �tre affich� dans un widget
 * d'affichage graphique 2D.
 *
 * Tout objet graphique poss�de les attributs graphiques suivants:
 * -# Couleur: FL_BLACK, FL_RED, FL_GREEN, FL_YELLOW, FL_BLUE, FL_MAGENTA,
 * FL_CYAN, FL_WHITE, FL_GRAY0, FL_DARK3, FL_DARK2, FL_DARK1,
 * FL_GRAY, FL_LIGHT1, FL_LIGHT2, FL_LIGHT3.
 * -# Style du trac�: FL_SOLID, FL_DASH, FL_DOT, FL_DASHDOT, FL_DASHDOTDOT.
 * -# Epaisseur du trac�: en nombre de pixels (0 = d�faut syst�me).
 */
class FLTK_Graphic_Object
{
public:
  // standard colors: FL_BLACK = 0, FL_RED = 1, FL_GREEN = 2,
  // FL_YELLOW = 3, FL_BLUE = 4, FL_MAGENTA = 5, FL_CYAN = 6, FL_WHITE = 7
  // greys: FL_GRAY0 = 32, FL_DARK3 = 39, FL_DARK2 = 45, FL_DARK1 = 47,
  // FL_GRAY = 49, FL_LIGHT1 = 50, FL_LIGHT2 = 52, FL_LIGHT3 = 54,
  Fl_Color color;
  // drawing style: FL_SOLID = 0, FL_DASH = 1, FL_DOT = 2, FL_DASHDOT = 3,
  // FL_DASHDOTDOT = 4.
  int style;
  // pixel thickness of a line (0 = system-defined default)
  int width;

  // constructeur(s)
  FLTK_Graphic_Object (Fl_Color _color = FL_BLACK,
               int _style = FL_SOLID, int _width = 0);
  // methode pure d'affichage de l'objet dans le widget graphique display
  // on suppose que display est le widget "courant" au sens fltk
  virtual void draw (FLTK_Display *display) = 0;
  // methode pure d'affichage alphanumerique des attributs de l'objet
  // on suppose que la methode se termine par un retour a la ligne
  virtual void print () = 0;

  // methode pure de conversion de l'objet en objets xfig
  virtual void xfigicize (ofstream &output) = 0;
};

// ############################################################################
/** Classe FLTK_Point: objet graphique de type point destin� � �tre affich�
 * dans un widget FLTK_Display_control.
 */
class FLTK_Point : public FLTK_Graphic_Object {
public:
  // (repere "monde") coordonnees du point
  double x, y;

  /** Constructeur.
   *
   * \param _x abcisse du point (rep�re "monde").
   * \param _y ordonn�e du point (rep�re "monde").
   * \param _color couleur du point.
   * \param _width taille du point.
   */
  FLTK_Point (double _x = 0.0, double _y = 0.0,
         Fl_Color _color = FL_BLACK, int _width = 0);
  // affichage de l'objet dans le widget graphique display
  void draw (FLTK_Display *display);
  // affichage alphanumerique des attributs de l'objet
  void print ();
  // conversion de l'objet en objets xfig
  void xfigicize (ofstream &output);
};

// ############################################################################
/** Classe FLTK_Cross: objet graphique de type croix destin� � �tre affich�
 * dans un widget FLTK_Display_control.
 */
class FLTK_Cross : public FLTK_Graphic_Object {
public:
  // (repere "monde") coordonnees du point, longueur d'une demi-branche du x
  double x, y, size;

  /** Constructeur.
   *
   * \param _x abcisse du centre de la croix (rep�re "monde").
   * \param _y ordonn�e du centre de la croix (rep�re "monde").
   * \param _size longueur d'une demi-branche de la croix (rep�re "monde").
   * \param _color couleur du point.
   * \param _style style du trac�.
   * \param _width �paisseur du trac�.
   */
  FLTK_Cross (double _x = 0.0, double _y = 0.0, double _size = 0.0,
         Fl_Color _color = FL_BLACK,
         int _style = FL_SOLID, int _width = 0);
  // affichage de l'objet dans le widget graphique display
  void draw (FLTK_Display *display);
  // affichage alphanumerique des attributs de l'objet
  void print ();
  // conversion de l'objet en objets xfig
  void xfigicize (ofstream &output);
};

// ############################################################################
/** Classe FLTK_Plus: objet graphique de type plus destin� � �tre affich�
 * dans un widget FLTK_Display_control.
 */
class FLTK_Plus : public FLTK_Graphic_Object {
public:
  // (repere "monde") coordonnees du point, longueur d'une demi-branche du +
  double x, y, size;

  /** Constructeur.
   *
   * \param _x abcisse du centre du plus (rep�re "monde").
   * \param _y ordonn�e du centre du plus (rep�re "monde").
   * \param _size longueur d'une demi-branche du plus (rep�re "monde").
   * \param _color couleur du point.
   * \param _style style du point.
   * \param _width �paisseur du trait.
   */
  FLTK_Plus (double _x = 0.0, double _y = 0.0, double _size = 0.0,
        Fl_Color _color = FL_BLACK,
        int _style = FL_SOLID, int _width = 0);
  // affichage de l'objet dans le widget graphique display
  void draw (FLTK_Display *display);
  // affichage alphanumerique des attributs de l'objet
  void print ();
  // conversion de l'objet en objets xfig
  void xfigicize (ofstream &output);
};

// ############################################################################
/** Classe FLTK_Line: objet graphique de type ligne destin� � �tre affich�
 * dans un widget FLTK_Display_control.
 */
class FLTK_Line : public FLTK_Graphic_Object {
public:
  // (repere "monde") coordonnees des extremites
  double x1, y1, x2, y2;

  /** Constructeur.
   *
   * \param _x1 abcisse de l'extremit� 1 (rep�re "monde").
   * \param _y1 ordonn�e de l'extremit� 1 (rep�re "monde").
   * \param _x2 abcisse de l'extremit� 2 (rep�re "monde").
   * \param _y2 ordonn�e de l'extremit� 2 (rep�re "monde").
   * \param _color couleur du point.
   * \param _style style du point.
   * \param _width �paisseur du trait.
   */
  FLTK_Line (double _x1 = 0.0, double _y1 = 0.0,
        double _x2 = 0.0, double _y2 = 0.0,
        Fl_Color _color = FL_BLACK,
        int _style = FL_SOLID, int _width = 0);
  // affichage de l'objet dans le widget graphique display
  void draw (FLTK_Display *display);
  // affichage alphanumerique des attributs de l'objet
  void print ();
  // conversion de l'objet en objets xfig
  void xfigicize (ofstream &output);
};

// ############################################################################
/** Classe FLTK_Arc: objet graphique de type arc destin� � �tre affich�
 * dans un widget FLTK_Display_control.
 */
class FLTK_Arc : public FLTK_Graphic_Object {
public:
  // (repere "monde") coordonnees des extremites (debut, fin), du centre du
  // cercle et de son rayon
  double x1, y1, x2, y2, xc, yc, radius;
  // direction de l'arc de cercle (counterclockwise)
  bool ccw;
  // angles des extremites (en radians, de 0 a 2*Pi, mesure
  // counterclockwise a partir de 3h00)
  double alpha1, alpha2;
  // longueur de l'arc de cercle
  double length;

  /** Constructeur.
   *
   * \param _x1 abcisse de l'extremit� 1 (rep�re "monde").
   * \param _y1 ordonn�e de l'extremit� 1 (rep�re "monde").
   * \param _x2 abcisse de l'extremit� 2 (rep�re "monde").
   * \param _y2 ordonn�e de l'extremit� 2 (rep�re "monde").
   * \param _xc abcisse du centre (rep�re "monde").
   * \param _yc ordonn�e du centre (rep�re "monde").
   * \param _radius rayon de l'arc (rep�re "monde").
   * \param _ccw bool�en, direction de l'arc de cercle (counterclockwise)
   * \param _color couleur du point.
   * \param _style style du point.
   * \param _width �paisseur du trait.
   */
  FLTK_Arc (double _x1 = 0.0, double _y1 = 0.0,
       double _x2 = 0.0, double _y2 = 0.0,
       double _xc = 0.0, double _yc = 0.0,
       double _radius = 0.0, bool _ccw = true,
       Fl_Color _color = FL_BLACK,
       int _style = FL_SOLID, int _width = 0);
  // affichage de l'objet dans le widget graphique display
  void draw (FLTK_Display *display);
  // affichage alphanumerique des attributs de l'objet
  void print ();
  // conversion de l'objet en objets xfig
  void xfigicize (ofstream &output);
};

// ############################################################################
/** Classe FLTK_Circle: objet graphique de type cercle destin� � �tre affich�
 * dans un widget FLTK_Display_control.
 */
class FLTK_Circle : public FLTK_Graphic_Object {
public:
  // (repere "monde") coordonnees du centre du cercle et de son rayon
  double xc, yc, radius;

  /** Constructeur.
   *
   * \param _xc abcisse du centre (rep�re "monde").
   * \param _yc ordonn�e du centre (rep�re "monde").
   * \param _radius rayon du cercle (rep�re "monde").
   * \param _color couleur du point.
   * \param _style style du point.
   * \param _width �paisseur du trait.
   */
  FLTK_Circle (double _xc = 0.0, double _yc = 0.0, double _radius = 0.0,
          Fl_Color _color = FL_BLACK,
          int _style = FL_SOLID, int _width = 0);
  // affichage de l'objet dans le widget graphique display
  void draw (FLTK_Display *display);
  // affichage alphanumerique des attributs de l'objet
  void print ();
  // conversion de l'objet en objets xfig
  void xfigicize (ofstream &output);
};

// ############################################################################
/** Classe FLTK_Clothoid: objet graphique de type arc de cloto�de destin�
 *    � �tre affich� dans un widget FLTK_Display_control.
*/
class FLTK_Clothoid : public FLTK_Graphic_Object {
public:
  // (repere "monde") coordonnees des extremites (debut, fin) avec
  // orientation et courbure associees
  double x1, y1, theta1, kappa1, x2, y2, theta2, kappa2;
  // "sharpness" de la clotoide (signee)
  double sigma;
  // marche avant / arriere a partir de (x1, y1, theta1) ?
  bool forward;
  // longueur de l'arc de clotoide (positive)
  double length;
  // pas de discretisation pour l'affichage graphique (repere "monde")
  double step;

  /** Constructeur.
   *
   * \param _x1 abcisse de l'extremit� 1 (rep�re "monde").
   * \param _y1 ordonn�e de l'extremit� 1 (rep�re "monde").
   * \param _theta1 orientation de l'extremit� 1.
   * \param _kappa1 courbure � l'extremit� 1.
   * \param _x2 abcisse de l'extremit� 2 (rep�re "monde").
   * \param _y2 ordonn�e de l'extremit� 2 (rep�re "monde").
   * \param _theta2 orientation de l'extremit� 2.
   * \param _kappa2 courbure � l'extremit� 2.
   * \param _sigma "sharpness" (sign�e) de la cloto�de
   * \param _forward bool�en, marche avant ou marche arri�re a partir de
   * l'extremit� 1.
   * \param _length longueur (positive) de l'arc de clotoide  (rep�re "monde").
   * \param _step pas de discr�tisation pour l'affichage graphique (rep�re
   * "monde").
   * \param _color couleur du point.
   * \param _style style du point.
   * \param _width �paisseur du trait.
   */
  FLTK_Clothoid (double _x1 = 0.0, double _y1 = 0.0,
        double _theta1 = 0.0, double _kappa1 = 0.0,
        double _x2 = 0.0, double _y2 = 0.0,
        double _theta2 = 0.0, double _kappa2 = 0.0,
        double _sigma = 0.0,
        bool _forward = true,
        double _length = 0.0,
        double _step = 0.0,
        Fl_Color _color = FL_BLACK,
        int _style = FL_SOLID, int _width = 0);
  // affichage de l'objet dans le widget graphique display
  void draw (FLTK_Display *display);
  // affichage alphanumerique des attributs de l'objet
  void print ();
  // conversion de l'objet en objets xfig
  void xfigicize (ofstream &output);
};

#endif
