// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di creazione ed elaborazione delle immagini intermedie


#ifndef PTGEN_IMAGES_H
#define PTGEN_IMAGES_H

class invalid_param { };

// Classe astratta image.
//
// Rappresenta un algoritmo di generazione o manipolazione di un'immagine.

class image : public ptgen_object
  {
    vector <image *> prev;
    int num_next;

    void one_successor_computed()
      {
        if (--num_next == 0)
          {
	    delete[] image_data;
	    image_data = NULL;
	  }
      }

  protected:
    typedef unsigned char pixel;

    pixel *image_data;

    void add_pred (image *img)
      {
        prev.push_back (img);
        img->num_next++;
      }

  public:
    image() : prev(), num_next(0), image_data(NULL) { };
    ~image()
      {
	if (image_data)
	  delete[] image_data;
      };

    virtual void build_graph (void) { };
    virtual void compute (void) = 0;
    pixel *get_image_data ();
    bool write(ostream &os, enum image_file_format fmt);

    enum param { OPERATION, OPACITY, X_DISPLACEMENT, Y_DISPLACEMENT,
		 OUT_RED, OUT_GREEN, OUT_BLUE, CONVOLUTION_MATRIX, SCALE, BIAS,
		 SRC_IMAGE, SRC_IMAGE_2 };

    enum blit_op { BLEND, ADD, SUBTRACT, DIFFERENCE, MULTIPLY, SCREEN,
		   OVERLAY, COLOR, HUE, VALUE, SATURATION, LIGHTEN, DARKEN,
		   DISSOLVE };

    virtual void set_param (enum param id, image *img) { throw invalid_param(); };
    virtual void set_param (enum param id, enum blit_op op) { throw invalid_param(); };
    virtual void set_param (enum param id, ptgen_function *fun) { throw invalid_param(); };
    virtual void set_param (enum param id, float real) { throw invalid_param(); };
    virtual void set_param (enum param id, numeric_matrix *matr) { throw invalid_param(); };
    virtual void set_param (enum param id, numeric_vector *vec) { throw invalid_param(); };

    static void set_size (int w, int h) { width = w; height = h; };
    static int width, height;
  };

// Classe astratta unary_command.
//
// Rappresenta i comandi che hanno un solo operando di tipo immagine

class unary_command : public image
  {
  protected:
    image *src_img;

  public:
    unary_command () : image (), src_img (NULL) { };

    void build_graph (void);
    void set_param (enum param id, image *img);
  };

// Classe convolve_command.
//
// Implementa la convoluzione con una matrice arbitraria.  Si puo'
// applicare una scalatura e/o sommare un valore costante ai risultati
// (ovvero una componente continua).

class convolve_command : public unary_command
  {
    numeric_matrix *conv_matrix;
    float scale, bias;

  public:
    convolve_command () : unary_command (), conv_matrix (NULL), scale(1.0), bias(0.0) { };
    ~convolve_command ()
      {
        if (conv_matrix && !conv_matrix->declared)
	  delete conv_matrix;
      }

    void compute (void);
    void set_param (enum param id, numeric_matrix *matr);
    void set_param (enum param id, float real);
  };

// Classe apply_command.
//
// Implementa una trasformazione dello spazio di coordinate di un'immagine.

class apply_command : public unary_command
  {
    ptgen_function *x_func, *y_func;

  public:
    apply_command () : unary_command (), x_func (NULL), y_func (NULL) { };

    void compute (void);
    void set_param (enum param id, ptgen_function *func);
  };

// Classe apply_colormap_command.
//
// Implementa una trasformazione dello spazio RGB

class apply_colormap_command : public unary_command
  {
    ptgen_function *red_func, *green_func, *blue_func;

  public:
    apply_colormap_command () : unary_command (), red_func (NULL), green_func (NULL), blue_func (NULL) { };

    void compute (void);
    void set_param (enum param id, ptgen_function *func);
  };

// Classe greyscale_command.
//
// Tiene la sola componente di luminanza dell'immagine

class greyscale_command : public unary_command
  {
  public:
    greyscale_command () : unary_command () { };

    void compute (void);
  };

// Classe apply_op_command.
//
// E' un operatore binario che fonde due immagini con un operatore scelto
// tra quelli di GIMP.

class apply_op_command : public image
  {
    image *src1_img, *src2_img;
    enum blit_op operation;
    float opacity;

    void blend ();
    void dissolve ();
    void darken ();
    void lighten ();
    void hsv ();
    void color ();
    void multiply ();
    void screen ();
    void overlay ();
    void add ();
    void subtract ();
    void difference ();
  public:
    apply_op_command () : image (), src1_img (NULL), src2_img (NULL), operation (BLEND), opacity (1.0) { };

    void build_graph (void);
    void compute (void);
    void set_param (enum param id, image *img);
    void set_param (enum param id, enum blit_op op);
    void set_param (enum param id, float real);
  };

// Classe create_from_formula_command.
//
// Prende una formula per ciascun canale, oppure una sola per tutti
// e tre i canali, e la applica una volta per pixel.

class create_from_formula_command : public image
  {
    ptgen_function *red_func, *green_func, *blue_func;

  public:
    create_from_formula_command () : image (), red_func (NULL), green_func (NULL), blue_func (NULL) { };

    void compute (void);
    void set_param (enum param id, ptgen_function *func);
  };

// Classe create_from_channels_command.
//
// Prende un'immagine per ciascun canale.

class create_from_channels_command : public image
  {
    image *red_src, *green_src, *blue_src;

  public:
    create_from_channels_command () : image (), red_src (NULL), green_src (NULL), blue_src (NULL) { };

    void build_graph (void);
    void compute (void);
    void set_param (enum param id, image *src);
  };

// Classe noise_command.
//
// Crea un rumore bianco monocromatico, opzionalmente facendo passare
// il rumore per una funzione che rimappa i tre canali.

class noise_command : public image
  {
  protected:
    ptgen_function *red_func, *green_func, *blue_func;

  public:
    noise_command () : image (), red_func (NULL), green_func (NULL), blue_func (NULL) { };

    void compute (void);
    void set_param (enum param id, ptgen_function *func);
  };

// Classe perlin_noise_command.
//
// Crea un rumore frattale monocromatico, opzionalmente facendo passare
// il rumore per una funzione che rimappa i tre canali.

class perlin_noise_command : public noise_command
  {
    float scale;

  public:
    perlin_noise_command () : noise_command (), scale (1) { };

    void compute (void);
    void set_param (enum param id, float real);
  };

void push_image (image *img);
image *pop_image ();
image *top_image ();
void set_seed (unsigned long seed1, unsigned long seed2);

#endif
