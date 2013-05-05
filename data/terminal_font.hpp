#ifndef __TERMINAL_FONT_HPP
#define __TERMINAL_FONT_HPP

size_t const GLYPH_HEIGHT       = 6; /* max height of a glyph */
size_t const GLYPH_SIZE         = GLYPH_HEIGHT * sizeof(char); /* glyph size */
typedef unsigned char const glyph_t[GLYPH_SIZE]; /* glyph type */

glyph_t FNT_excl  = { 0x84, 0xE3, 0x10, 0x04, 0x40, 0x00 }; /* (!) */
glyph_t FNT_sharp = { 0x80, 0xF2, 0x29, 0xCA, 0xA7, 0x00 }; /* (#) */
glyph_t FNT_comma = { 0x00, 0x00, 0x00, 0x00, 0xC3, 0x20 }; /* (,) */
glyph_t FNT_dash  = { 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00 }; /* (-) */
glyph_t FNT_dot   = { 0x00, 0x00, 0x00, 0x00, 0xC3, 0x00 }; /* (.) */
glyph_t FNT_0     = { 0x4c, 0x34, 0x55, 0x59, 0xE4, 0x00 }; /* (0) */
glyph_t FNT_1     = { 0x04, 0x43, 0x10, 0x04, 0xE1, 0x00 }; /* (1) */
glyph_t FNT_2     = { 0x4E, 0x14, 0x18, 0x08, 0xF4, 0x01 }; /* (2) */
glyph_t FNT_3     = { 0x4E, 0x14, 0x38, 0x41, 0xE4, 0x00 }; /* (3) */
glyph_t FNT_5     = { 0x1F, 0x04, 0x79, 0x41, 0xE4, 0x00 }; /* (5) */
glyph_t FNT_9     = { 0x4E, 0x14, 0x3D, 0x81, 0xC0, 0x00 }; /* (9) */
glyph_t FNT_dbdot = { 0x00, 0xC0, 0x30, 0x00, 0xC3, 0x00 }; /* (:) */
glyph_t FNT_B     = { 0x1E, 0x14, 0x79, 0x51, 0xE4, 0x00 }; /* (B) */
glyph_t FNT_E     = { 0x1F, 0x04, 0x79, 0x10, 0xF4, 0x01 }; /* (E) */
glyph_t FNT_L     = { 0x10, 0x04, 0x41, 0x10, 0xF4, 0x01 }; /* (L) */
glyph_t FNT_M     = { 0xD1, 0x56, 0x45, 0x51, 0x14, 0x01 }; /* (M) */
glyph_t FNT_N     = { 0x51, 0x56, 0x4D, 0x51, 0x10, 0x01 }; /* (N) */
glyph_t FNT_O     = { 0x4E, 0x14, 0x45, 0x51, 0xE4, 0x00 }; /* (O) */
glyph_t FNT_R     = { 0x5E, 0x14, 0x79, 0x52, 0x14, 0x01 }; /* (R) */
glyph_t FNT_S     = { 0x4E, 0x04, 0x39, 0x41, 0xE4, 0x00 }; /* (S) */
glyph_t FNT_T     = { 0x1F, 0x41, 0x10, 0x04, 0x41, 0x00 }; /* (T) */
glyph_t FNT_a     = { 0x00, 0xE0, 0x04, 0x4F, 0xF4, 0x00 }; /* (a) */
glyph_t FNT_b     = { 0x10, 0xE4, 0x45, 0x51, 0xE0, 0x01 }; /* (b) */
glyph_t FNT_c     = {
glyph_t FNT_d
glyph_t FNT_e     = { 0x00, 0xE0, 0x44, 0x1E, 0xE4, 0x00 }; /* e */
glyph_t FNT_f
glyph_t FNT_g
glyph_t FNT_h
glyph_t FNT_i     = { 0x04, 0x40, 0x10, 0x04, 0x61, 0x00 }; /* i */
glyph_t FNT_j
glyph_t FNT_k     = { 0x10, 0x24, 0x51, 0x18, 0x25, 0x01 }; /* k */
glyph_t FNT_l
glyph_t FNT_m
glyph_t FNT_n
glyph_t FNT_o     = { 0x00, 0xE0, 0x44, 0x51, 0xE4, 0x00 }; /* o */
glyph_t FNT_p     = { 0x00, 0xE0, 0x45, 0x51, 0xE4, 0x41 }; /* p */
glyph_t FNT_q
glyph_t FNT_r     = { 0x00, 0x60, 0x25, 0x08, 0xC2, 0x01 }; /* r */
glyph_t FNT_s     = { 0x00, 0xE0, 0x40, 0x4E, 0xE0, 0x00 }; /* s */
glyph_t FNT_t
glyph_t FNT_u     = { 0x00, 0x20, 0x49, 0x92, 0xA5, 0x00 }; /* u */
glyph_t FNT_v     = { 0x00, 0x10, 0x46, 0x91, 0x42, 0x00 }; /* v */
glyph_t FNT_x
glyph_t FNT_y     = { 0x00, 0x20, 0x49, 0x92, 0x43, 0x60 }; /* y */
glyph_t FNT_z


glyph_t *FNT_glyphs[] = {
    /* ASCII start at 33, (!) */
    &FNT_excl  /* (!) */
  , nullptr    /* (") */
  , &FNT_sharp /* (#) */
  , nullptr    /* ($) */
  , nullptr    /* (%) */
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
  , &FNT_x     /* (x) */
  , &FNT_y     /* (y) */
  , &FNT_z     /* (z) */
};
     
#endif /* guard */

