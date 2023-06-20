// TetiSoft: To specify which modules you need,
// insert the following in your source file and uncomment as needed:

/*
//#define FT2_1_3_USE_AUTOHINT       // autohinter
//#define FT2_1_3_USE_RASTER         // monochrome rasterizer
//#define FT2_1_3_USE_SMOOTH         // anti-aliasing rasterizer
//#define FT2_1_3_USE_TT             // truetype font driver
//#define FT2_1_3_USE_T1             // type1 font driver
//#define FT2_1_3_USE_T42            // type42 font driver
//#define FT2_1_3_USE_T1CID          // cid-keyed type1 font driver  // no cmap support
//#define FT2_1_3_USE_CFF            // opentype font driver
//#define FT2_1_3_USE_BDF            // bdf bitmap font driver
//#define FT2_1_3_USE_PCF            // pcf bitmap font driver
//#define FT2_1_3_USE_PFR            // pfr font driver
//#define FT2_1_3_USE_WINFNT         // windows .fnt|.fon bitmap font driver
#include "FT:src/base/ftinit.c"
*/

// TetiSoft: make sure that needed support modules are built in.
// Dependencies can be found by searching for FT2_1_3_Get_Module.

#ifdef FT2_1_3_USE_T42
#define FT2_1_3_USE_TT
#endif

#ifdef FT2_1_3_USE_TT
#define FT2_1_3_USE_SFNT
#endif

#ifdef FT2_1_3_USE_CFF
#define FT2_1_3_USE_SFNT
#define FT2_1_3_USE_PSHINT
#define FT2_1_3_USE_PSNAMES
#endif

#ifdef FT2_1_3_USE_T1
#define FT2_1_3_USE_PSAUX
#define FT2_1_3_USE_PSHINT
#define FT2_1_3_USE_PSNAMES
#endif

#ifdef FT2_1_3_USE_T1CID
#define FT2_1_3_USE_PSAUX
#define FT2_1_3_USE_PSHINT
#define FT2_1_3_USE_PSNAMES
#endif

#ifdef FT2_1_3_USE_PSAUX
#define FT2_1_3_USE_PSNAMES
#endif

#ifdef FT2_1_3_USE_SFNT
#define FT2_1_3_USE_PSNAMES
#endif

// TetiSoft: Now include the modules

#ifdef FT2_1_3_USE_AUTOHINT
FT2_1_3_USE_MODULE(autohint_module_class)
#endif

#ifdef FT2_1_3_USE_PSHINT
FT2_1_3_USE_MODULE(pshinter_module_class)
#endif

#ifdef FT2_1_3_USE_CFF
FT2_1_3_USE_MODULE(cff_driver_class)
#endif

#ifdef FT2_1_3_USE_T1CID
FT2_1_3_USE_MODULE(t1cid_driver_class)
#endif

#ifdef FT2_1_3_USE_BDF
FT2_1_3_USE_MODULE(bdf_driver_class)
#endif

#ifdef FT2_1_3_USE_PCF
FT2_1_3_USE_MODULE(pcf_driver_class)
#endif

#ifdef FT2_1_3_USE_PFR
FT2_1_3_USE_MODULE(pfr_driver_class)
#endif

#ifdef FT2_1_3_USE_PSAUX
FT2_1_3_USE_MODULE(psaux_module_class)
#endif

#ifdef FT2_1_3_USE_PSNAMES
FT2_1_3_USE_MODULE(psnames_module_class)
#endif

#ifdef FT2_1_3_USE_RASTER
FT2_1_3_USE_MODULE(ft_raster1_renderer_class)
#endif

#ifdef FT2_1_3_USE_SFNT
FT2_1_3_USE_MODULE(sfnt_module_class)
#endif

#ifdef FT2_1_3_USE_SMOOTH
FT2_1_3_USE_MODULE(ft_smooth_renderer_class)
FT2_1_3_USE_MODULE(ft_smooth_lcd_renderer_class)
FT2_1_3_USE_MODULE(ft_smooth_lcdv_renderer_class)
#endif

#ifdef FT2_1_3_USE_TT
FT2_1_3_USE_MODULE(tt_driver_class)
#endif

#ifdef FT2_1_3_USE_T1
FT2_1_3_USE_MODULE(t1_driver_class)
#endif

#ifdef FT2_1_3_USE_T42
FT2_1_3_USE_MODULE(t42_driver_class)
#endif

#ifdef FT2_1_3_USE_WINFNT
FT2_1_3_USE_MODULE(winfnt_driver_class)
#endif
