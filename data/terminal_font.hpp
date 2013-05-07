#ifndef __TERMINAL_FONT_HPP
#define __TERMINAL_FONT_HPP

size_t const GLYPH_WIDTH        = 6; /* max width of a glyph */
size_t const GLYPH_HEIGHT       = 8; /* max height of a glyph */
float  const GLYPH_RATIO        = 1.f * GLYPH_WIDTH / GLYPH_HEIGHT;
size_t const GLYPH_SIZE         = GLYPH_WIDTH * GLYPH_HEIGHT; /* glyph size */
size_t const FNT_TBL_START      = 31; /* ASCII table start */
typedef unsigned char const glyph_t[GLYPH_SIZE]; /* glyph type */

glyph_t FNT_musc1 = { 0x10, 0x61, 0x44, 0x31, 0xC6, 0x00 }; /* ( ) */
glyph_t FNT_musc2 = { 0x0C, 0xD2, 0xCD, 0x2D, 0xB6, 0x00 }; /* ( ) */
glyph_t FNT_excl  = { 0x10, 0xE3, 0x84, 0x10, 0x01, 0x00 }; /* (!) */
glyph_t FNT_sharp = { 0x00, 0xA7, 0xCA, 0x29, 0xF2, 0x80 }; /* (#) */
glyph_t FNT_comma = { 0x00, 0x00, 0x00, 0x00, 0xC2, 0x08 }; /* (,) */
glyph_t FNT_dash  = { 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00 }; /* (-) */
glyph_t FNT_dot   = { 0x00, 0x00, 0x00, 0x00, 0xC3, 0x00 }; /* (.) */
glyph_t FNT_0     = { 0x31, 0x14, 0xD5, 0x65, 0x13, 0x00 }; /* (0) */
glyph_t FNT_1     = { 0x10, 0xC1, 0x04, 0x10, 0x43, 0x80 }; /* (1) */
glyph_t FNT_2     = { 0x39, 0x10, 0x46, 0x21, 0x07, 0xC0 }; /* (2) */
glyph_t FNT_3     = { 0x39, 0x10, 0x4E, 0x05, 0x13, 0x80 }; /* (3) */
glyph_t FNT_5     = { 0x7D, 0x04, 0x1E, 0x05, 0x13, 0x80 }; /* (5) */
glyph_t FNT_9     = { 0x39, 0x14, 0x4F, 0x04, 0x23, 0x00 }; /* (9) */
glyph_t FNT_dbdot = { 0x00, 0x03, 0x0C, 0x00, 0xC3, 0x00 }; /* (:) */
glyph_t FNT_B     = { 0x79, 0x04, 0x5E, 0x45, 0x13, 0x80 }; /* (B) */
glyph_t FNT_E     = { 0x7D, 0x04, 0x1E, 0x41, 0x07, 0xC0 }; /* (E) */
glyph_t FNT_L     = { 0x41, 0x04, 0x10, 0x41, 0x07, 0xC0 }; /* (L) */
glyph_t FNT_M     = { 0x45, 0xB5, 0x51, 0x45, 0x14, 0x40 }; /* (M) */
glyph_t FNT_N     = { 0x45, 0x95, 0x53, 0x44, 0x14, 0x40 }; /* (N) */
glyph_t FNT_O     = { 0x39, 0x14, 0x51, 0x45, 0x13, 0x80 }; /* (O) */
glyph_t FNT_R     = { 0x79, 0x14, 0x5E, 0x49, 0x14, 0x40 }; /* (R) */
glyph_t FNT_S     = { 0x39, 0x14, 0x0E, 0x05, 0x13, 0x80 }; /* (S) */
glyph_t FNT_T     = { 0x7C, 0x41, 0x04, 0x10, 0x41, 0x00 }; /* (T) */
glyph_t FNT_a     = { 0x00, 0x03, 0x81, 0x3D, 0x13, 0xC0 }; /* (a) */
glyph_t FNT_b     = { 0x41, 0x07, 0x91, 0x44, 0x17, 0x80 }; /* (b) */
glyph_t FNT_c     = { 0x00, 0x03, 0x91, 0x41, 0x13, 0x80 }; /* (c) */
glyph_t FNT_d     = { 0x04, 0x13, 0xD1, 0x45, 0x13, 0xC0 }; /* (d) */
glyph_t FNT_e     = { 0x00, 0x03, 0x91, 0x79, 0x03, 0x80 }; /* (e) */
glyph_t FNT_f     = { 0x18, 0x82, 0x1E, 0x20, 0x82, 0x00 }; /* (f) */
glyph_t FNT_g     = { 0x00, 0x03, 0xD1, 0x44, 0xF0, 0x4E }; /* (g) */
glyph_t FNT_h     = { 0x41, 0x07, 0x12, 0x49, 0x24, 0x80 }; /* (h) */
glyph_t FNT_i     = { 0x10, 0x01, 0x04, 0x10, 0x41, 0x80 }; /* (i) */
glyph_t FNT_j     = { 0x04, 0x01, 0x82, 0x08, 0x24, 0x8C }; /* (j) */
glyph_t FNT_k     = { 0x41, 0x04, 0x94, 0x61, 0x44, 0x80 }; /* (k) */
glyph_t FNT_l     = { 0x10, 0x41, 0x04, 0x10, 0x41, 0x80 }; /* (l) */
glyph_t FNT_m     = { 0x00, 0x06, 0x95, 0x55, 0x14, 0x40 }; /* (m) */
glyph_t FNT_n     = { 0x00, 0x07, 0x12, 0x49, 0x24, 0x80 }; /* (n) */
glyph_t FNT_o     = { 0x00, 0x03, 0x91, 0x45, 0x13, 0x80 }; /* (o) */
glyph_t FNT_p     = { 0x00, 0x07, 0x91, 0x45, 0x17, 0x90 }; /* (p) */
glyph_t FNT_q     = { 0x00, 0x03, 0xD1, 0x45, 0x13, 0xC1 }; /* (q) */
glyph_t FNT_r     = { 0x00, 0x05, 0x89, 0x20, 0x87, 0x00 }; /* (r) */
glyph_t FNT_s     = { 0x00, 0x03, 0x90, 0x38, 0x13, 0x80 }; /* (s) */
glyph_t FNT_t     = { 0x00, 0x87, 0x88, 0x22, 0xA1, 0x00 }; /* (t) */
glyph_t FNT_u     = { 0x00, 0x04, 0x92, 0x49, 0x62, 0x80 }; /* (u) */
glyph_t FNT_v     = { 0x00, 0x08, 0x51, 0x44, 0xA1, 0x00 }; /* (v) */
glyph_t FNT_x     = { 0x00, 0x04, 0x92, 0x31, 0x20, 0x89 }; /* (x) */
glyph_t FNT_y     = { 0x00, 0x04, 0x92, 0x48, 0xE1, 0x18 }; /* (y) */
glyph_t FNT_z     = { 0x00, 0x07, 0x82, 0x31, 0x03, 0x80 }; /* (z) */


glyph_t * const FNT_glyphs[] = {
    /* ASCII start at 33 (!), but we use 31 and 32 for the music signs (respectively US and Space) */
    &FNT_musc1 /* ( ) */
  , &FNT_musc2 /* ( ) */
  , &FNT_excl  /* (!) */
  , nullptr    /* (") */
  , &FNT_sharp /* (#) */
  , nullptr    /* ($) */
  , nullptr    /* (%) */
  , nullptr    /* (&) */
  , nullptr    /* (() */
  , nullptr    /* ()) */
  , nullptr    /* (*) */
  , nullptr    /* (+) */
  , &FNT_comma /* (,) */
  , &FNT_dash  /* (-) */
  , &FNT_dot   /* (.) */
  , nullptr    /* (/) */
  , &FNT_0     /* (0) */
  , &FNT_1     /* (1) */
  , &FNT_2     /* (2) */
  , &FNT_3     /* (3) */
  , nullptr    /* (4) */
  , &FNT_5     /* (5) */
  , nullptr    /* (6) */
  , nullptr    /* (7) */
  , nullptr    /* (8) */
  , &FNT_9     /* (9) */
  , &FNT_dbdot /* (:) */
  , nullptr    /* (;) */
  , nullptr    /* (<) */
  , nullptr    /* (=) */
  , nullptr    /* (>) */
  , nullptr    /* (?) */
  , nullptr    /* (@) */
  , nullptr    /* (A) */
  , &FNT_B     /* (B) */
  , nullptr    /* (C) */
  , nullptr    /* (D) */
  , &FNT_E     /* (E) */
  , nullptr    /* (F) */
  , nullptr    /* (G) */
  , nullptr    /* (H) */
  , nullptr    /* (I) */
  , nullptr    /* (J) */
  , nullptr    /* (K) */
  , &FNT_L     /* (L) */
  , &FNT_M     /* (M) */
  , &FNT_N     /* (N) */
  , &FNT_O     /* (O) */
  , nullptr    /* (P) */
  , nullptr    /* (Q) */
  , &FNT_R     /* (R) */
  , &FNT_S     /* (S) */
  , &FNT_T     /* (T) */
  , nullptr    /* (U) */
  , nullptr    /* (V) */
  , nullptr    /* (W) */
  , nullptr    /* (X) */
  , nullptr    /* (Y) */
  , nullptr    /* (Z) */
  , nullptr    /* ([) */
  , nullptr    /* (\) */
  , nullptr    /* (]) */
  , nullptr    /* (^) */
  , nullptr    /* (_) */
  , nullptr    /* (`) */
  , &FNT_a     /* (a) */
  , &FNT_b     /* (b) */
  , &FNT_c     /* (c) */
  , &FNT_d     /* (d) */
  , &FNT_e     /* (e) */
  , &FNT_f     /* (f) */
  , &FNT_g     /* (g) */
  , &FNT_h     /* (g) */
  , &FNT_i     /* (i) */
  , &FNT_j     /* (j) */
  , &FNT_k     /* (k) */
  , &FNT_l     /* (l) */
  , &FNT_m     /* (m) */
  , &FNT_n     /* (n) */
  , &FNT_o     /* (o) */
  , &FNT_p     /* (p) */
  , &FNT_q     /* (q) */
  , &FNT_r     /* (r) */
  , &FNT_s     /* (s) */
  , &FNT_t     /* (t) */
  , &FNT_u     /* (u) */
  , &FNT_v     /* (v) */
  , nullptr    /* (w) */
  , &FNT_x     /* (x) */
  , &FNT_y     /* (y) */
  , &FNT_z     /* (z) */
};
     
size_t const GLYPH_NB = sizeof(FNT_glyphs) / sizeof(glyph_t*);

#endif /* guard */

