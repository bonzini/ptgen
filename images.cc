// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di creazione ed elaborazione delle immagini intermedie

#include "ptgen.h"

#include <stack>
#include <cstdlib>

using std::stack;

rng randf;

int image::width = 0;
int image::height = 0;

// Gli oggetti image di cui il parser sta inizializzando i parametri.
static stack <image *> img_stack;

// Funzioni di conversione tra gli spazi di colore RGB/HSV/HLS
static void rgb_to_hsv (int *r, int *g, int *b);
static void hsv_to_rgb (int *r, int *g, int *b);
static void rgb_to_hls (int *r, int *g, int *b);
static void hls_to_rgb (int *r, int *g, int *b);

// Se non e' NULL, valuta la funzione FUNC per tutti i valori
// compresi tra 0 ed N-1, altrimenti copia i primi N valori di DEF.
static int *prepare_range(int n, ptgen_function *func, int *def);

void
rgb_to_hsv (int *r,
	    int *g,
	    int *b)
{
  int red, green, blue;
  float h, s, v;
  int min, max;
  int delta;

  red = *r;
  green = *g;
  blue = *b;

  if (red > green)
    {
      if (red > blue)
	max = red;
      else
	max = blue;

      if (green < blue)
	min = green;
      else
	min = blue;
    }
  else
    {
      if (green > blue)
	max = green;
      else
	max = blue;

      if (red < blue)
	min = red;
      else
	min = blue;
    }

  v = max;

  if (max != 0)
    s = ((max - min) * 255) / (float) max;
  else
    s = 0;

  if (s == 0)
    h = 0;
  else
    {
      delta = max - min;
      if (red == max)
	h = (green - blue) / (float) delta;
      else if (green == max)
	h = 2 + (blue - red) / (float) delta;
      else /* if (blue == max) */
	h = 4 + (red - green) / (float) delta;
      h *= 42.5;

      if (h < 0)
	h += 255;
      if (h > 255)
	h -= 255;
    }

  *r = (int) h;
  *g = (int) s;
  *b = (int) v;
}


void
hsv_to_rgb (int *h,
	    int *s,
	    int *v)
{
  float hue, saturation, value;
  float f, p, q, t;

  if (*s == 0)
    {
      *h = *v;
      *s = *v;
      // *v = *v;
    }
  else
    {
      hue = *h * 6.0 / 255.0;
      saturation = *s / 255.0;
      value = *v / 255.0;

      f = hue - (int) hue;
      p = value * (1.0 - saturation);
      q = value * (1.0 - (saturation * f));
      t = value * (1.0 - (saturation * (1.0 - f)));

      switch ((int) hue)
	{
	case 0:
	  *h = (int) (value * 255);
	  *s = (int) (t * 255);
	  *v = (int) (p * 255);
	  break;
	case 1:
	  *h = (int) (q * 255);
	  *s = (int) (value * 255);
	  *v = (int) (p * 255);
	  break;
	case 2:
	  *h = (int) (p * 255);
	  *s = (int) (value * 255);
	  *v = (int) (t * 255);
	  break;
	case 3:
	  *h = (int) (p * 255);
	  *s = (int) (q * 255);
	  *v = (int) (value * 255);
	  break;
	case 4:
	  *h = (int) (t * 255);
	  *s = (int) (p * 255);
	  *v = (int) (value * 255);
	  break;
	case 5:
	  *h = (int) (value * 255);
	  *s = (int) (p * 255);
	  *v = (int) (q * 255);
	  break;
	}
    }
}


void
rgb_to_hls (int *r,
	    int *g,
	    int *b)
{
  int red = *r;
  int green = *g;
  int blue = *b;

  int min, max;
  if (red > green)
    {
      max = (red > blue) ? red : blue;
      min = (green < blue) ? green : blue;
    }
  else
    {
      max = (green > blue) ? green : blue;
      min = (red < blue) ? red : blue;
    }

  float l = (max + min) / 2.0;

  float h,s;
  if (max == min)
    {
      s = 0.0;
      h = 0.0;
    }
  else
    {
      int delta = (max - min);

      if (l < 128)
	s = 255 * (float) delta / (float) (max + min);
      else
	s = 255 * (float) delta / (float) (511 - max - min);

      if (red == max)
	h = (green - blue) / (float) delta;
      else if (green == max)
	h = 2 + (blue - red) / (float) delta;
      else
	h = 4 + (red - green) / (float) delta;

      h = h * 42.5;

      if (h < 0)
	h += 255;
      if (h > 255)
	h -= 255;
    }

  *r = (int) h;
  *g = (int) l;
  *b = (int) s;
}


static int
hls_value (float n1,
	   float n2,
	   float hue)
{
  float value;

  if (hue > 255)
    hue -= 255;
  else if (hue < 0)
    hue += 255;
  if (hue < 42.5)
    value = n1 + (n2 - n1) * (hue / 42.5);
  else if (hue < 127.5)
    value = n2;
  else if (hue < 170)
    value = n1 + (n2 - n1) * ((170 - hue) / 42.5);
  else
    value = n1;

  return (int) (value * 255);
}


void
hls_to_rgb (int *h,
	    int *l,
	    int *s)
{
  if (*s == 0)
    {
      /*  achromatic case  */
      *h = *l;
      *s = *l;
      // *l = *l;
    }
  else
    {
      float hue = *h;
      float lightness = *l;
      float saturation = *s;

      float m2;
      if (lightness < 128)
	m2 = (lightness * (255 + saturation)) / 65025.0;
      else
	m2 = (lightness + saturation - (lightness * saturation)/255.0) / 255.0;

      float m1 = (lightness / 127.5) - m2;

      /*  chromatic case  */
      *h = hls_value (m1, m2, hue + 85);
      *l = hls_value (m1, m2, hue);
      *s = hls_value (m1, m2, hue - 85);
    }
}


int *prepare_range(int n, ptgen_function *func, int *def)
{
  int *dest = new int[n];
  int *p = dest;
  int max = n - 1;

  if (!func)
    if (def)
      for (int i = 0; i < n; i++)
        *p++ = *def++;
    else
      for (int i = 0; i < n; i++)
        *p++ = i;
  else
    for (int i = 0; i < n; i++)
      *p++ = int (max * func->apply (float(i) / max));

  return dest;
}

// Classe astratta image.
//
// Rappresenta un algoritmo di generazione o manipolazione di un'immagine.

// Questo metodo ritorna l'immagine calcolata con l'algoritmo
// corrispondente all'oggetto image; dopo aver fatto il calcolo
// i predecessori nel grafo vengono informati in modo che
// la memoria che occupano possa essere liberata.
image::pixel *image::get_image_data ()
{
  if (image_data)
    return image_data;

  image_data = new pixel[3 * width * height];
  compute ();

  vector <image *>::iterator it;
  for (it = prev.begin(); it < prev.end(); it++)
    (*it)->one_successor_computed();

  return image_data;
}

// Scrive l'immagine nel formato identificato da FMT, attualmente
// PNG o PPM binario.
bool image::write (ostream &os, enum image_file_format fmt)
{
  bool error = false;
  char *data = reinterpret_cast <char *> (get_image_data());

  if (fmt == OUT_PNG)
    error |= !write_png (os, data, width, height);
  else
    {
      os << "P6" << endl << "# Generated by " PACKAGE_STRING << endl
         << width << ' ' << height << endl
         << 255 << endl;

      os.write (data, 3 * width * height);
    }

  error |= !os;

  if (error)
    cerr << "File output error." << endl;

  return error;
}

// Classe astratta unary_command.
//
// Rappresenta i comandi che hanno un solo operando di tipo immagine

// Il metodo build_graph aggiunge un arco da ciascuno degli operandi
// di tipo immagine verso l'oggetto
void unary_command::build_graph(void)
{
  add_pred (src_img);
}

void unary_command::set_param(enum image::param id, image *img)
{
  if (id == SRC_IMAGE)
    src_img = img;
  else
    image::set_param (id, img);
}

// Classe convolve_command.
//
// Implementa la convoluzione con una matrice arbitraria.  Si puo'
// applicare una scalatura e/o sommare un valore costante ai risultati
// (ovvero una componente continua).

void convolve_command::set_param(enum image::param id, numeric_matrix *matr)
{
  if (id == CONVOLUTION_MATRIX)
    conv_matrix = matr;
  else
    image::set_param (id, matr);
}

void convolve_command::set_param(enum image::param id, float real)
{
  if (id == SCALE)
    scale = real;
  else if (id == BIAS)
    bias = real * 256;
  else
    image::set_param (id, real);
}

void
convolve_command::compute ()
{
  int rows = conv_matrix->size();
  int columns = conv_matrix->row_size();

  // Controlla se l'immagine di destinazione e' troppo piccola
  if (width < (columns - 1) || height < (rows - 1))
    {
      memcpy (get_image_data (), src_img->get_image_data(), 3*width*height);
      return;
    }

  // Memorizza i coefficienti della matrice in un'array.
  float *matrix = new float[rows * columns], *m = matrix;
  for (numeric_matrix::iterator m_it = conv_matrix->begin();
       m_it < conv_matrix->end(); m_it++)
    for (numeric_vector::iterator v_it = (*m_it)->begin();
         v_it < (*m_it)->end(); v_it++)
      *m++ = *v_it;

  // Inizializza alcuni valori
  int stride = 3 * width;
  int y_margin = rows / 2;
  int x_margin = columns / 2;

  int src_width = x_margin * 2 + width;
  int src_height = y_margin * 2 + height;
  int src_stride = 3 * src_width;
  int wraparound = src_stride - columns * 3;
  pixel *src_base = new pixel[src_stride * src_height];

  // Copia le prime Y_MARGIN righe, riflesse
  pixel *src = src_base + x_margin * 3;
  pixel *src2 = src_img->get_image_data();
  for (int i = y_margin; i--; )
    {
      memcpy (src, src2 + stride * (i + 1), stride);
      src += src_stride;
    }

  // Copia l'immagine
  for (int i = height; i--; )
    {
      memcpy (src, src2, stride);
      src += src_stride;
      src2 += stride;
    }

  // Copia le ultime Y_MARGIN righe, riflesse
  src2 -= stride;
  for (int i = y_margin; i--; )
    {
      src2 -= stride;
      memcpy (src, src2, stride);
      src += src_stride;
    }

  // Riflette i margini.
  src = src_base;
  for (int i = src_height; i--; src += src_stride)
    for (int j = x_margin * 3, k = 6; j; k += 6)
      {
 	j -= 3;
	src[j] = src[j + k];
	src[j+1] = src[j+1 + k];
	src[j+2] = src[j+2 + k];
	src[src_stride - x_margin*3 + j] = src[src_stride - x_margin*3 - j-6];
	src[src_stride - x_margin*3 + j+1] = src[src_stride - x_margin*3 - j-5];
	src[src_stride - x_margin*3 + j+2] = src[src_stride - x_margin*3 - j-4];
      }

  // Ora esegue la convoluzione vera e propria
  pixel *dest = get_image_data ();
  for (int y = 0; y < height; y++)
    {
      pixel *src = src_base + src_stride * y;
      pixel *d = dest + stride * y;

      for (int x = width; x--; )
	{
	  float total_r = 0, total_g = 0, total_b = 0;
	  pixel *s = src;

	  // Moltiplica i pixel per i coefficienti
	  m = matrix;
	  for (int i = rows; i--; s += wraparound)
	    for (int j = columns; j--; m++)
	      {
		float coeff = *m;
	        total_r += coeff * *s++;
		total_g += coeff * *s++;
		total_b += coeff * *s++;
	     }

	  // Applica scalatura e componente continua
	  int tot_r = (int) (total_r / scale + bias);
	  int tot_g = (int) (total_g / scale + bias);
	  int tot_b = (int) (total_b / scale + bias);

	  // Ora applica il clamping per i valori fuori dal range 0...255
	  *d++ = tot_r < 0 ? 0 : tot_r > 255 ? 255 : tot_r;
	  *d++ = tot_g < 0 ? 0 : tot_g > 255 ? 255 : tot_g;
	  *d++ = tot_b < 0 ? 0 : tot_b > 255 ? 255 : tot_b;
	  src += 3;
	}
    }

  delete[] src_base;
}

// Classe apply_command.
//
// Implementa una trasformazione dello spazio di coordinate di un'immagine.

void apply_command::set_param(enum image::param id, ptgen_function *func)
{
  if (id == X_DISPLACEMENT)
    x_func = func;
  else if (id == Y_DISPLACEMENT)
    y_func = func;
  else
    image::set_param (id, func);
}

void apply_command::compute (void)
{
  int y_max = height-1, x_max = width-1;
  int stride = width*3;
  pixel *p = image_data, *srcp = src_img->get_image_data();

  float y_step = 1.0 / y_max;
  float x_step = 1.0 / x_max;
  float x, y;
  int xx, yy;
  for (yy = height, y = 0; yy--; y += y_step)
    for (xx = width, x = 0; xx--; x += x_step)
      {
        int old_x = int(x_max * x_func->apply(x, y));
        int old_y = int(y_max * y_func->apply(x, y));

	pixel *q = srcp + (3*old_x + stride*old_y);
	*p++ = *q++;
	*p++ = *q++;
	*p++ = *q;
      }
}

// Classe greyscale_command.
//
// Tiene la sola componente di luminanza dell'immagine

void greyscale_command::compute (void)
{
  static int *out_red, *out_green, *out_blue;

  if (!out_red)
    {
      out_red = new int[256];
      out_green = new int[256];
      out_blue = new int[256];
      for (int i = 0; i < 256; i++)
        out_red[i] = int(i * 0.3), out_green[i] = int(i * 0.59),
	out_blue[i] = int(i * 0.11);
    }

  for (pixel *p = image_data, *srcp = src_img->get_image_data(),
       *end = image_data + 3*width*height; p < end; )
    {
      pixel c = out_red[*srcp++];
      c += out_green[*srcp++];
      c += out_blue[*srcp++];
      *p++ = c;
      *p++ = c;
      *p++ = c;
    }
}

// Classe apply_colormap_command.
//
// Implementa una trasformazione dello spazio RGB

void apply_colormap_command::set_param(enum image::param id, ptgen_function *func)
{
  if (id == OUT_RED)
    red_func = func;
  else if (id == OUT_GREEN)
    green_func = func;
  else if (id == OUT_BLUE)
    blue_func = func;
  else
    image::set_param (id, func);
}

void apply_colormap_command::compute (void)
{
  // Ci sono due possibilita': se green_func==blue_func==NULL, usa una sola
  // funzione, altrimenti tutti e tre.  Inoltre se le funzioni sono a un
  // solo argomento viene passata una componente per volta (vedi gli ultimi
  // tre parametri della funzione apply), altrimenti vengono passate tutte
  // e tre le componenti.

  if (green_func)
    for (pixel *p = image_data, *srcp = src_img->get_image_data(),
         *end = image_data + 3*width*height; p < end; )
      {
        float r = *srcp++ / 255.0;
        float g = *srcp++ / 255.0;
        float b = *srcp++ / 255.0;
        *p++ = static_cast<pixel> (255 * red_func->apply(r, g, b, 1, 0, 0));
        *p++ = static_cast<pixel> (255 * green_func->apply(r, g, b, 0, 1, 0));
        *p++ = static_cast<pixel> (255 * blue_func->apply(r, g, b, 0, 0, 1));
      }
  else
    for (pixel *p = image_data, *srcp = src_img->get_image_data(),
         *end = image_data + 3*width*height; p < end; )
      {
        float r = *srcp++ / 255.0;
        float g = *srcp++ / 255.0;
        float b = *srcp++ / 255.0;
        *p++ = static_cast<pixel> (255 * red_func->apply(r, g, b, 1, 0, 0));
        *p++ = static_cast<pixel> (255 * red_func->apply(r, g, b, 0, 1, 0));
        *p++ = static_cast<pixel> (255 * red_func->apply(r, g, b, 0, 0, 1));
      }
}

// Classe apply_op_command.
//
// E' un operatore binario che fonde due immagini con un operatore scelto
// tra quelli di GIMP.

void apply_op_command::build_graph(void)
{
  add_pred (src1_img);
  add_pred (src2_img);
}

void apply_op_command::set_param(enum image::param id, enum image::blit_op op)
{
  if (id == OPERATION)
    operation = op;
  else
    image::set_param (id, op);
}

void apply_op_command::set_param(enum image::param id, image *img)
{
  if (id == SRC_IMAGE)
    src1_img = img;
  else if (id == SRC_IMAGE_2)
    src2_img = img;
  else
    image::set_param (id, img);
}

void apply_op_command::set_param(enum image::param id, float real)
{
  if (id == OPACITY)
    opacity = real;
  else
    image::set_param (id, real);
}

void apply_op_command::compute (void)
{
  switch (operation)
    {
    case BLEND: blend(); break;
    case DISSOLVE: dissolve(); break;
    case ADD: add(); break;
    case SUBTRACT: subtract(); break;
    case DIFFERENCE: difference(); break;
    case MULTIPLY: multiply(); break;
    case SCREEN: screen(); break;
    case OVERLAY: overlay(); break;
    case COLOR: color(); break;
    case HUE:
    case SATURATION:
    case VALUE: hsv(); break;
    case LIGHTEN: lighten(); break;
    case DARKEN: darken(); break;
    }
}

// blend e' il valore di default e miscela le due immagini
// secondo il fattore specificato senza applicare alcuna operazione
// aritmetica.
void
apply_op_command::blend ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  length *= 3;
  while (length--)
    *dest++ = (*src1++ * blend2 + *src2++ * blend) / 256;
}

// dissolve sceglie un pixel da una delle due immagini casualmente
// secondo il valore di opacita' specificato.
void
apply_op_command::dissolve ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  while (length--)
    {
      if (randf() * 255 < blend2)
	{
	  *dest++ = *src1++;
	  *dest++ = *src1++;
	  *dest++ = *src1++;
	  src2 += 3;
	}
      else
	{
	  *dest++ = *src2++;
	  *dest++ = *src2++;
	  *dest++ = *src2++;
	  src1 += 3;
	}
    }
}


// darken sceglie il pixel piu' scuro tra le due immagini.
void
apply_op_command::darken ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  while (length--)
    {
      int r1 = *src1++, g1 = *src1++, b1 = *src1++;
      int r2 = *src2++, g2 = *src2++, b2 = *src2++;

      // These coefficients are 32 64 8 instead of the correct 30 59 11,
      // but the results are practically the same
      int l1 = (r1 << 2) + (g1 << 3) + b1;
      int l2 = (r2 << 2) + (g2 << 3) + b2;

      int result_r = (l1 < l2) ? r1 : r2;
      int result_g = (l1 < l2) ? g1 : g2;
      int result_b = (l1 < l2) ? b1 : b2;

      *dest++ = (r1 * blend2 + result_r * blend) / 256;
      *dest++ = (g1 * blend2 + result_g * blend) / 256;
      *dest++ = (b1 * blend2 + result_b * blend) / 256;
    }
}


// lighten sceglie il pixel piu' scuro tra le due immagini.
void
apply_op_command::lighten ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  while (length--)
    {
      int r1 = *src1++, g1 = *src1++, b1 = *src1++;
      int r2 = *src2++, g2 = *src2++, b2 = *src2++;

      // Questi coefficienti sono 32 64 8 invece di quelli piu' comuni
      // 30 59 11, ma va piu' veloce senza grandi differenze.
      int l1 = (r1 << 2) + (g1 << 3) + b1;
      int l2 = (r2 << 2) + (g2 << 3) + b2;

      int result_r = (l1 > l2) ? r1 : r2;
      int result_g = (l1 > l2) ? g1 : g2;
      int result_b = (l1 > l2) ? b1 : b2;

      *dest++ = (r1 * blend2 + result_r * blend) / 256;
      *dest++ = (g1 * blend2 + result_g * blend) / 256;
      *dest++ = (b1 * blend2 + result_b * blend) / 256;
    }
}


// hsv sostituisce una delle componenti nello spazio HSV
// con quella dell'immagine "sovrapposta".
void
apply_op_command::hsv ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  int r1, g1, b1;
  int r2, g2, b2;

  int *dest_r, *dest_g, *dest_b;
  dest_r = &r1;
  dest_g = &g1;
  dest_b = &b1;
  switch (operation)
    {
    case HUE:
      dest_r = &r2;
      break;
    case SATURATION:
      dest_g = &g2;
      break;
    case VALUE:
      dest_b = &b2;
      break;
    default:
      abort();
    }

  while (length--)
    {
      r1 = *src1++; g1 = *src1++; b1 = *src1++;
      r2 = *src2++; g2 = *src2++; b2 = *src2++;

      int src_r = r1;
      int src_g = g1;
      int src_b = b1;

      rgb_to_hsv (&r1, &g1, &b1);
      rgb_to_hsv (&r2, &g2, &b2);

      /*  set the destination  */
      int result_r = *dest_r;
      int result_g = *dest_g;
      int result_b = *dest_b;
      hsv_to_rgb (&result_r, &result_g, &result_b);

      *dest++ = (src_r * blend2 + result_r * blend) / 256;
      *dest++ = (src_g * blend2 + result_g * blend) / 256;
      *dest++ = (src_b * blend2 + result_b * blend) / 256;
    }
}

// color sostituisce le componenti H ed S nello spazio HLS
// con quella dell'immagine "sovrapposta".
void
apply_op_command::color ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  int r1, g1, b1;
  int r2, g2, b2;

  while (length--)
    {
      r1 = *src1++; g1 = *src1++; b1 = *src1++;
      r2 = *src2++; g2 = *src2++; b2 = *src2++;

      pixel src_r = r1;
      pixel src_g = g1;
      pixel src_b = b1;

      rgb_to_hls (&r1, &g1, &b1);
      rgb_to_hls (&r2, &g2, &b2);

      // Trasferisce tinta e saturazione dall'immagine "sovrapposta"
      // e tiene la luminosita' dell'immagine originale.
      int result_r = r2;
      int result_g = g1;
      int result_b = b2;
      hls_to_rgb (&result_r, &result_g, &result_b);

      *dest++ = (src_r * blend2 + result_r * blend) / 256;
      *dest++ = (src_g * blend2 + result_g * blend) / 256;
      *dest++ = (src_b * blend2 + result_b * blend) / 256;
    }
}


// multiply moltiplica i pixel delle due immagini.
void
apply_op_command::multiply ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  length *= 3;
  while (length --)
    {
      int s1 = *src1++;
      int s2 = *src2++;
      int result = s1 * s2 / 256;
      *dest++ = (s1 * blend2 + result * blend) / 256;
    }
}


// screen calcola il negativo della moltiplicazione dei negativi.
void
apply_op_command::screen ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  length *= 3;
  while (length--)
    {
      int s1 = *src1++;
      int s2 = *src2++;
      int result = 255 - (255 - s1) * (255 - s2) / 256;
      *dest++ = (s1 * blend2 + result * blend) / 256;
    }
}


// overlay passa dallo stesso effetto di multiply se l'immagine di
// partenza e' scura, allo stesso effetto di screen se l'immagine di
// partenza e' chiara.
void
apply_op_command::overlay ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  length *= 3;
  while (length--)
    {
      int s1 = *src1++;
      int s2 = *src2++;

      // int screen = 255 - ((255 - s1) * (255 - s2)) / 256;
      // int mult = (s1 * s2) / 256;
      // int result = (screen * s1 + mult * (255 - s1)) / 256;

      // La formula si puo' semplificare cosi':
      //
      // result = (1-a)ab  + a (1-(1-a)(1-b))
      //        = a (b-ab) + a (1-(1-a-b+ab))
      //        = a (b-ab) + a (a+b-ab)
      //        = a (a + 2b (1-a))
      int result = s1 * (128 * s1 + s2 * (255 - s1)) / 32768;

      *dest++ = (s1 * blend2 + result * blend) / 256;
    }
}


// add somma le immagini con saturazione a 255.
void
apply_op_command::add ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  length *= 3;
  while (length --)
    {
      int s1 = *src1++;
      int s2 = *src2++;
      int sum = s1 + s2;
      int result = (s1 * blend2 + sum * blend) / 256;
      *dest++ = (result > 255) ? 255 : result;
    }
}


// subtract sottrae un'immagine dall'altra con saturazione a 0.
void
apply_op_command::subtract ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  length *= 3;
  while (length --)
    {
      int s1 = *src1++;
      int s2 = *src2++;
      int diff = s1 - s2;
      int result = (s1 * blend2 + diff * blend) / 256;
      *dest++ = (result < 0) ? 0 : result;
    }
}


// difference sottrae un'immagine dall'altra e prende il valore assoluto.
void
apply_op_command::difference ()
{
  pixel *src1 = src1_img->get_image_data();
  pixel *src2 = src2_img->get_image_data();
  pixel *dest = get_image_data();
  int blend = (int) (opacity * 256);
  int blend2 = 256 - blend;
  int length = width * height;

  length *= 3;
  while (length --)
    {
      int s1 = *src1++;
      int s2 = *src2++;
      int diff = s1 - s2;
      int result = (diff < 0) ? -diff : diff;
      *dest++ = (s1 * blend2 + result * blend) / 256;
    }
}


// Classe create_from_formula_command.
//
// Prende una formula per ciascun canale, oppure una sola per tutti
// e tre i canali, e la applica una volta per pixel.

void create_from_formula_command::set_param(enum image::param id, ptgen_function *func)
{
  if (id == OUT_RED)
    red_func = func;
  else if (id == OUT_GREEN)
    green_func = func;
  else if (id == OUT_BLUE)
    blue_func = func;
  else
    image::set_param (id, func);
}

void create_from_formula_command::compute (void)
{
  int y_max = height-1, x_max = width-1;
  pixel *p = image_data;

  float y_step = 1.0 / y_max;
  float x_step = 1.0 / x_max;
  float x, y;
  int xx, yy;
  if (green_func)
    for (yy = height, y = 0; yy--; y += y_step)
      for (xx = width, x = 0; xx--; x += x_step)
        {
          *p++ = static_cast<pixel> (255 * red_func->apply(x, y));
          *p++ = static_cast<pixel> (255 * green_func->apply(x, y));
          *p++ = static_cast<pixel> (255 * blue_func->apply(x, y));
        }
  else
    for (yy = height, y = 0; yy--; y += y_step)
      for (xx = width, x = 0; xx--; x += x_step)
        {
          pixel c =
	    static_cast<pixel> (255 * red_func->apply(x, y));
          *p++ = c;
          *p++ = c;
          *p++ = c;
        }
}

// Classe create_from_channels_command.
//
// Prende un'immagine per ciascun canale.

void create_from_channels_command::build_graph(void)
{
  add_pred (red_src);
  add_pred (green_src);
  add_pred (blue_src);
}

void create_from_channels_command::set_param(enum image::param id, image *img)
{
  if (id == OUT_RED)
    red_src = img;
  else if (id == OUT_GREEN)
    green_src = img;
  else if (id == OUT_BLUE)
    blue_src = img;
  else
    image::set_param (id, img);
}

void create_from_channels_command::compute (void)
{
  pixel *red = red_src->get_image_data();
  pixel *green = green_src->get_image_data() + 1;
  pixel *blue = blue_src->get_image_data() + 2;

  for (pixel *p = image_data, *end = image_data + 3*width*height;
       p < end; red += 3, green += 3, blue += 3)
    {
      *p++ = *red;
      *p++ = *green;
      *p++ = *blue;
    }
}

// Classe noise_command.
//
// Crea un rumore bianco monocromatico, opzionalmente facendo passare
// il rumore per una funzione che rimappa i tre canali.

void noise_command::set_param(enum image::param id, ptgen_function *func)
{
  if (id == OUT_RED)
    red_func = func;
  else if (id == OUT_GREEN)
    green_func = func;
  else if (id == OUT_BLUE)
    blue_func = func;
  else
    image::set_param (id, func);
}

void noise_command::compute (void)
{
  int *out_red = prepare_range(256, red_func, NULL);
  int *out_green = prepare_range(256, green_func, out_red);
  int *out_blue = prepare_range(256, blue_func, out_red);

  for (pixel *p = image_data, *end = image_data + 3*width*height;
       p < end; )
    {
      pixel c = static_cast <pixel> (randf() * 255);
      *p++ = out_red[c];
      *p++ = out_green[c];
      *p++ = out_blue[c];
    }

  delete[] out_red;
  delete[] out_green;
  delete[] out_blue;
}

// Classe perlin_noise_command.
//
// Crea un rumore frattale monocromatico, opzionalmente facendo passare
// il rumore per una funzione che rimappa i tre canali.

void perlin_noise_command::compute (void)
{
  int *out_red = prepare_range(256, red_func, NULL);
  int *out_green = prepare_range(256, green_func, out_red);
  int *out_blue = prepare_range(256, blue_func, out_red);

  scale = width / 2 / scale;

  pixel *noise = new pixel[width*height];
  for (pixel *p = noise, *end = noise + width*height; p < end; )
    *p++ = static_cast <pixel> (randf() * 255);

  pixel *p = image_data;
  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
      {
	float value = 0.0, weight = 0.0;

	// Compute several linear interpolations in the noise array
        for (float octave = scale; octave >= 1; octave /= 2)
	  {
	    float nx, ny;              //xy into texture array
	    int ix, iy, ixd, iyd;      //floor & ceil of xy into texture array
	    float rx, ry;              //fractional part of xy

	    nx = (float)x / octave;
	    ny = (float)y / octave;

	    ix = (int) nx;
	    iy = (int) ny;
	    rx = nx - (float) ix;
	    ry = ny - (float) iy;
	    ixd = (ix - 1) & (width - 1);
	    iyd = (iy - 1) & (height - 1);
	    ix = ix & (width - 1);
	    iy = iy & (height - 1);

	    float accum = rx * ry * noise[iy * height + ix];
	    accum += (1 - rx) * ry * noise[iy * height + ixd];
	    accum += rx * (1 - ry) * noise[iyd * height + ix];
	    accum += (1 - rx) * (1 - ry) * noise[iyd * height + ixd];
	    value += accum * octave;
	    weight += octave;
	  }

	pixel c = static_cast <pixel> (value / weight);
        *p++ = out_red[c];
        *p++ = out_green[c];
        *p++ = out_blue[c];
      }

  delete[] noise;
  delete[] out_red;
  delete[] out_green;
  delete[] out_blue;
}

void perlin_noise_command::set_param(enum image::param id, float real)
{
  if (id == SCALE)
    scale = real;
  else
    image::set_param (id, real);
}

void push_image (image *img)
{
  img_stack.push (img);
}

image *pop_image ()
{
  image *img = img_stack.top();
  img_stack.pop ();
  return img;
}

image *top_image ()
{
  return img_stack.top();
}

