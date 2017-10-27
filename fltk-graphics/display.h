// *** File: display.h
// *** Author(s): Th. Fraichard
// *** Last modified on 9 Jul 2008

/**
 * \page FLTK_Display Widget d'affichage graphique 2D
 * \section introduction Introduction
 *
 * Widget d'affichage graphique qui comporte deux fenêtres: une fenêtre de
 * contrôle (objet de classe FLTK_Display_Control) et une fenêtre
 * d'affichage 2D (objet de classe FLTK_Display).  Est associée à ce widget
 * une liste d'objets graphiques (objets de classe FLTK_Graphic_Object) qui
 * sont representés dans la fenêtre d'affichage.  La fenêtre de controle
 * permet de gérer les paramètres de visualisation (échelle, point de vue),
 * de réinitialiser la liste d'objets graphiques et de demander une sortie
 * au format Xfig dans un fichier <nom du widget>-output.fig.
 */

/**
 * \defgroup FLTK_Display FLTK_Display, FLTK_Display_Control et FLTK_Graphic_Object
 */

#ifndef DISPLAY_H
#define DISPLAY_H

class FLTK_Graphic_Object;

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include <utilities.h>
#include <graphic-objects.h>

// ############################################################################
/**
 * \ingroup FLTK_Display
 * \brief Fenêtre d'affichage d'un widget d'affichage graphique 2D.
 *
 * Widget d'affichage graphique qui comporte deux fenêtres: une fenêtre de
 * contrôle (objet de classe FLTK_Display_Control) et une fenêtre
 * d'affichage 2D (objet de classe FLTK_Display).  Est associée à ce widget
 * une liste d'objets graphiques (objets de classe FLTK_Graphic_Object) qui
 * sont representés dans la fenêtre d'affichage.  La fenêtre de controle
 * permet de gérer les paramètres de visualisation (échelle, point de vue),
 * de réinitialiser la liste d'objets graphiques et de demander une sortie
 * au format Xfig dans un fichier <nom du widget>-output.fig.
 */
class FLTK_Display : public Fl_Double_Window {
public:
  // taille initiale de l'unite du repere "monde" (en pixel).
  double init_unit_size;
  // taille courante de l'unite du repere "monde" (en pixel).
  double unit_size;
  // position initiale du repere "monde" par rapport au repere "display"
  // (coin superieur gauche de la fenetre).
  double init_scroll_x, init_scroll_y;
  // position courante du repere "monde" par rapport au repere "display"
  // (coin superieur gauche de la fenetre).
  double scroll_x, scroll_y;
  // liste des objets graphiques a afficher
  vector<FLTK_Graphic_Object *> list_objects;
  // affichage graphique des objets de list_objects
  void draw ();
  // gestion des evenements
  int handle (int e);
  // constructeur(s)
  FLTK_Display (const double _unit_size,
        const double _scroll_x, const double _scroll_y,
        const int _w, const int _h, const char* _title);
  // destructeur
  ~FLTK_Display ();
  // lecture des attributs
  double get_init_unit_size () const;
  double get_init_scroll_x () const;
  double get_init_scroll_y () const;
  double get_unit_size () const;
  double get_scroll_x () const;
  double get_scroll_y () const;
  vector<FLTK_Graphic_Object *> get_list_objects () const;
  // ecriture  des attributs
  void set_unit_size (const double _unit_size);
  void set_scroll_x (const double _scroll_x);
  void set_scroll_y (const double _scroll_y);
  // reinitialisation de list_objects
  void clear_objects ();
  // ajout d'un objet graphique dans list_objects
  void add_object (FLTK_Graphic_Object *object);
  // fonctions amies
  friend void cb_xfig (Fl_Widget *, void *data);
};

// ############################################################################
/**
 * \ingroup FLTK_Display
 * \brief Fenêtre de contrôle d'un widget d'affichage graphique 2D.
 *
 * Widget d'affichage graphique qui comporte deux fenêtres: une fenêtre de
 * contrôle (objet de classe FLTK_Display_Control) et une fenêtre
 * d'affichage 2D (objet de classe FLTK_Display).  Est associée à ce widget
 * une liste d'objets graphiques (objets de classe FLTK_Graphic_Object) qui
 * sont representés dans la fenêtre d'affichage.  La fenêtre de controle
 * permet de gérer les paramètres de visualisation (échelle, point de vue),
 * de réinitialiser la liste d'objets graphiques et de demander une sortie
 * au format Xfig dans un fichier <nom du widget>-output.fig.
 */
class FLTK_Display_Control : public Fl_Window {
public:
  // quit button
  Fl_Button quit;
  // clear button
  Fl_Button clear;
  // xfig output button
  Fl_Button xfig;
  // zoom management group
  Fl_Group zoom_group;
  Fl_Box zoom_title, zoom_value;
  Fl_Button zoom_reset, zoom_plus, zoom_minus;
  // scroll management group
  Fl_Group scroll_group;
  Fl_Box scroll_title, scroll_value_x, scroll_value_y;
  Fl_Button scroll_reset, scroll_up, scroll_down, scroll_left, scroll_right;
  // display
  FLTK_Display *display;
  /** Constructeur.
   * Crée la fenêtre de contrôle et la fenêtre d'affichage associée.
   *
   * \param _unit_size taille (en pixels) de l'unité du repère "monde"
   * \param _scroll_x abcisse (en pixels) du repère "monde" par rapport au
   * repère "fenêtre" (coin supérieur gauche de la fenêtre).
   * \param _scroll_y ordonnée (en pixels) du repère "monde" par rapport au
   * repère "fenêtre" (coin supérieur gauche de la fenêtre).
   * \param _w largeur en pixels de la fenêtre.
   * \param _h hauteur en pixels de la fenêtre.
   * \param _title nom des fenêtres.
   */
  FLTK_Display_Control (double _unit_size,
            double _scroll_x, double _scroll_y,
            int _w, int _h, char* _title);
  /** Ajout du callback associé a la fenêtre d'affichage,
   *
   * Le callback est appelé lorsque que le curseur se trouve dans la
   * fenêtre d'affichage et que l'un des boutons de la souris ou que l'une
   * des touches du clavier est enfoncé.
   *
   * Le callback est une fonction de type "void <callback> (Fl_Widget
   * *display, void *data) {...}".  Dans le callback, on peut déterminer
   * quelle touche a été enfoncée à l'aide de la fonction "int
   * *Fl::event_key ();", ou quel bouton de la souris a été enfoncé à l'aide
   * de la fonction "int Fl::event_button ();".
   *
   * On peut récupérer la position en \a x de la souris (repère "monde")
   * par "worldify_x (Fl::event_x (), (FLTK_Display *)display);" (idem pour
   * la position en \a y: "worldify_y (Fl::event_y (), (FLTK_Display
   * *)display);").
   */
  void add_callback (void _callback (Fl_Widget *, void *));
  /** Réinitialisation de la liste des objets graphiques.
   *
   * Attention, les objets graphiques (dont les pointeurs ont été passé à
   * la fonction add_object) sont désalloués.
   */
  void clear_objects ();
  /** Ajout d'un objet graphique.
   *
   * \param object pointeur sur l'objet FLTK_Graphic_Object à ajouter.
   */
  void add_object (FLTK_Graphic_Object *object);
  /** Rafraîchissement de l'affichage.
   */
  void redraw ();
};

/**
 * Fonction de conversion (abcisse) repère "fenêtre" -> repère "monde".
 */
double worldify_x (int x, FLTK_Display *display);
/**
 * Fonction de conversion (ordonnée) repère "fenêtre" -> repère "monde".
 */
double worldify_y (int y, FLTK_Display *display);

#endif
