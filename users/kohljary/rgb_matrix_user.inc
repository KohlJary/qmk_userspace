/* // !!! DO NOT ADD #pragma once !!! // */
/* /1* #include <math.h> *1/ */

/* // Step 1. */
/* // Declare custom effects using the RGB_MATRIX_EFFECT macro */
/* // (note the lack of semicolon after the macro!) */
/* RGB_MATRIX_EFFECT(tech_demo_1) */
/* RGB_MATRIX_EFFECT(tech_demo_2) */
/* RGB_MATRIX_EFFECT(tech_demo_3) */
/* RGB_MATRIX_EFFECT(tech_demo_4) */
/* RGB_MATRIX_EFFECT(my_cool_effect2) */

/* // Step 2. */
/* // Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block */
/* #ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS */

/* // Enums */
/* enum LED_GROUP { */
/*   LED_R1 = 0, */
/*   LED_R2, */
/*   LED_R3, */
/*   LED_R4, */
/*   LED_R5, */
/*   LED_NUMR, */
/*   LED_HOME, */
/*   LED_VIM, */
/* }; */

/* enum LED_COLORS { */
/*   LED_COL_R = 0, */
/*   LED_COL_O, */
/*   LED_COL_Y, */
/*   LED_COL_G, */
/*   LED_COL_B, */
/*   LED_COL_V, */
/* }; */

/* // Helper functions */
/* __attribute__ ((weak)) */
/* int rgb_get_key_row(int x) { */
/*   if (x >= 0 && x <= 14) { */
/*     return LED_R1; */
/*   } */
/*   if (x >= 15 && x <= 29) { */
/*     return LED_R2; */
/*   } */
/*   if (x >= 30 && x <= 43) { */
/*     return LED_R3; */
/*   } */
/*   if (x >= 44 && x <= 57) { */
/*     return LED_R4; */
/*   } */
/*   if (x >= 58 && x <= 66) { */
/*     return LED_R5; */
/*   } */
/*   return -1; */
/* } */

/* __attribute__ ((weak)) */
/* bool rgb_is_num_row(int x) { */
/*   if (x >= 1 && x <= 12) { */
/*     return true; */
/*   } */
/*   return false; */
/* } */

/* __attribute__ ((weak)) */
/* bool rgb_is_txt_grp(int x) { */
/*   if(x >= 16 && x <= 27) { */
/*     return true; */
/*   } */
/*   if(x >= 31 && x <= 41) { */
/*     return true; */
/*   } */
/*   if(x >= 45 && x <= 54) { */
/*     return true; */
/*   } */
/*   return false; */
/* } */

/* __attribute__ ((weak)) */
/* bool rgb_is_home(int x) { */
/*   //asdf */
/*   if (x >= 31 && x <= 34) { */
/*     return true; */
/*   } */
/*   //jkl; */
/*   if (x >= 37 && x <= 40) { */
/*     return true; */
/*   } */
/*   return false; */
/* } */

/* __attribute__ ((weak)) */
/* bool rgb_is_vim(int x) { */
/*   //hjkl */
/*   if (x >= 36 && x <= 39) { */
/*     return true; */
/*   } */
/*   return false; */
/* } */

/* static HSV rgb_create_hsv_struct(int h, int s, int v) { */
/*   HSV hsv = {h, s, v}; */
/*   return hsv; */
/* } */

/* static HSV rgb_update_breathe_v(HSV in, effect_params_t* params) { */
/*     HSV      hsv  = rgb_matrix_config.hsv; */
/*     uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8); */
/*     hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v); */
/*     in.v = hsv.v; */
/*     return in; */
/* } */

/* // e.g: A simple effect, self-contained within a single method */
/* static bool tech_demo_1(effect_params_t* params) { */
/*   bool apply_breathe = true; */
/*   RGB_MATRIX_USE_LIMITS(led_min, led_max); */
/*   /1* int hsv_arr[3] = {HSV_WHITE}; *1/ */
/*   HSV key_hsv = {HSV_WHITE}; */
/*   for (uint8_t i = led_min; i < led_max; i++) { */
/*     apply_breathe = true; */
/*     //Assign colors by row */
/*     switch (rgb_get_key_row(i)) { */
/*       case LED_R1: */
/*         key_hsv = rgb_create_hsv_struct(HSV_RED); */
/*         break; */
/*       case LED_R2: */
/*         key_hsv = rgb_create_hsv_struct(HSV_ORANGE); */
/*         break; */
/*       case LED_R3: */
/*         key_hsv = rgb_create_hsv_struct(HSV_YELLOW); */
/*         break; */
/*       case LED_R4: */
/*         key_hsv = rgb_create_hsv_struct(HSV_GREEN); */
/*         break; */
/*       case LED_R5: */
/*         key_hsv = rgb_create_hsv_struct(HSV_BLUE); */
/*         break; */
/*     } */
/*     //Special groups */
/*     if (rgb_is_num_row(i)) { */
/*       if(i % 2 == 0) { */
/*         key_hsv = rgb_create_hsv_struct(HSV_PURPLE); */
/*       } */
/*       else { */
/*         key_hsv = rgb_create_hsv_struct(HSV_CYAN); */
/*       } */
/*       apply_breathe = false; */
/*     } */
/*     if (rgb_is_home(i)) { */
/*       /1* key_hsv = rgb_create_hsv_struct(HSV_CYAN); *1/ */
/*     } */
/*     if (rgb_is_vim(i)) { */
/*       /1* key_hsv = rgb_create_hsv_struct(HSV_BLUE); *1/ */
/*     } */
/*     //breathing effect */
/*     if(apply_breathe) { */
/*       key_hsv = rgb_update_breathe_v(key_hsv, params); */
/*     } */
/*     RGB key_rgb = rgb_matrix_hsv_to_rgb(key_hsv); */
/*     rgb_matrix_set_color(i, key_rgb.r, key_rgb.g, key_rgb.b); */
/*   } */
/*   return rgb_matrix_check_finished_leds(led_max); */
/* } */

/* static bool tech_demo_2(effect_params_t* params) { */
/*   RGB_MATRIX_USE_LIMITS(led_min, led_max); */
/*   HSV key_hsv = {HSV_WHITE}; */
/*   int rainbow_index = 0; */
/*   for (uint8_t i = led_min; i < led_max; i++) { */
/*     /1* switch (rainbow_index % 6) { *1/ */
/*     switch (i % 6) { */
/*       case LED_COL_R: */
/*         key_hsv = rgb_create_hsv_struct(HSV_RED); */
/*         break; */
/*       case LED_COL_O: */
/*         key_hsv = rgb_create_hsv_struct(HSV_ORANGE); */
/*         break; */
/*       case LED_COL_Y: */
/*         key_hsv = rgb_create_hsv_struct(HSV_YELLOW); */
/*         break; */
/*       case LED_COL_G: */
/*         key_hsv = rgb_create_hsv_struct(HSV_GREEN); */
/*         break; */
/*       case LED_COL_B: */
/*         key_hsv = rgb_create_hsv_struct(HSV_BLUE); */
/*         break; */
/*       case LED_COL_V: */
/*         key_hsv = rgb_create_hsv_struct(HSV_PURPLE); */
/*         break; */
/*     } */
/*     rainbow_index++; */
/*     if(rainbow_index > LED_COL_V) { */
/*       rainbow_index = 0; */
/*     } */
/*     key_hsv = rgb_update_breathe_v(key_hsv, params); */
/*     RGB key_rgb = rgb_matrix_hsv_to_rgb(key_hsv); */
/*     rgb_matrix_set_color(i, key_rgb.r, key_rgb.g, key_rgb.b); */
/*   } */
/*   return rgb_matrix_check_finished_leds(led_max); */
/* } */

/* static bool tech_demo_3(effect_params_t* params) { */
/*   RGB_MATRIX_USE_LIMITS(led_min, led_max); */
/*   HSV key_hsv = {HSV_WHITE}; */
/*   /1* int rainbow_index = 0; *1/ */
/*   for (uint8_t i = led_min; i < led_max; i++) { */
/*     if(!rgb_is_txt_grp(i)) { */
/*       switch (i % 6) { */
/*         case LED_COL_R: */
/*           key_hsv = rgb_create_hsv_struct(HSV_RED); */
/*           break; */
/*         case LED_COL_O: */
/*           key_hsv = rgb_create_hsv_struct(HSV_ORANGE); */
/*           break; */
/*         case LED_COL_Y: */
/*           key_hsv = rgb_create_hsv_struct(HSV_YELLOW); */
/*           break; */
/*         case LED_COL_G: */
/*           key_hsv = rgb_create_hsv_struct(HSV_GREEN); */
/*           break; */
/*         case LED_COL_B: */
/*           key_hsv = rgb_create_hsv_struct(HSV_BLUE); */
/*           break; */
/*         case LED_COL_V: */
/*           key_hsv = rgb_create_hsv_struct(HSV_PURPLE); */
/*           break; */
/*       } */
/*       /1* rainbow_index++; *1/ */
/*       /1* if(rainbow_index > LED_COL_V) { *1/ */
/*       /1*   rainbow_index = 0; *1/ */
/*       /1* } *1/ */
/*       /1* effect_runner_dx_dy_dist_per_key(i, params, &CYCLE_LEFT_RIGHT_math); *1/ */
/*       key_hsv = rgb_update_breathe_v(key_hsv, params); */
/*       RGB key_rgb = rgb_matrix_hsv_to_rgb(key_hsv); */
/*       rgb_matrix_set_color(i, key_rgb.r, key_rgb.g, key_rgb.b); */
/*     } */
/*     else { */
/*       effect_runner_dx_dy_dist_per_key(i, params, &CYCLE_SPIRAL_math); */
/*     } */
/*   } */
/*   return rgb_matrix_check_finished_leds(led_max); */
/* } */

/* static bool tech_demo_4(effect_params_t* params) { */
/*   RGB_MATRIX_USE_LIMITS(led_min, led_max); */
/*   HSV key_hsv = {HSV_WHITE}; */
/*   int rainbow_index = 0; */
/*   for (uint8_t i = led_min; i < led_max; i++) { */
/*     RGB_MATRIX_TEST_LED_FLAGS(); */
/*     if(!rgb_is_txt_grp(i)) { */
/*       switch (i % 6) { */
/*         case LED_COL_R: */
/*           key_hsv = rgb_create_hsv_struct(HSV_RED); */
/*           break; */
/*         case LED_COL_O: */
/*           key_hsv = rgb_create_hsv_struct(HSV_ORANGE); */
/*           break; */
/*         case LED_COL_Y: */
/*           key_hsv = rgb_create_hsv_struct(HSV_YELLOW); */
/*           break; */
/*         case LED_COL_G: */
/*           key_hsv = rgb_create_hsv_struct(HSV_GREEN); */
/*           break; */
/*         case LED_COL_B: */
/*           key_hsv = rgb_create_hsv_struct(HSV_BLUE); */
/*           break; */
/*         case LED_COL_V: */
/*           key_hsv = rgb_create_hsv_struct(HSV_PURPLE); */
/*           break; */
/*       } */
/*       rainbow_index++; */
/*       if(rainbow_index > LED_COL_V) { */
/*         rainbow_index = 0; */
/*       } */
/*       key_hsv = rgb_update_breathe_v(key_hsv, params); */
/*       RGB key_rgb = rgb_matrix_hsv_to_rgb(key_hsv); */
/*       rgb_matrix_set_color(i, key_rgb.r, key_rgb.g, key_rgb.b); */
/*     } */
/*     else { */
/*       effect_runner_dx_dy_dist_per_key(i, params, &CYCLE_OUT_IN_math); */
/*     } */
/*   } */
/*   return rgb_matrix_check_finished_leds(led_max); */
/* } */

/* // e.g: A more complex effect, relying on external methods and state, with */
/* // dedicated init and run methods */
/* static uint8_t some_global_state; */
/* static void my_cool_effect2_complex_init(effect_params_t* params) { */
/*   some_global_state = 1; */
/* } */
/* static bool my_cool_effect2_complex_run(effect_params_t* params) { */
/*   RGB_MATRIX_USE_LIMITS(led_min, led_max); */
/*   for (uint8_t i = led_min; i < led_max; i++) { */
/*     if (rgb_is_num_row(i)) { */
/*       rgb_matrix_set_color(i, RGB_MAGENTA); */
/*     } */
/*     else { */
/*       rgb_matrix_set_color(i, 0xff, some_global_state++, 0xff); */
/*     } */
/*   } */
/*   return rgb_matrix_check_finished_leds(led_max); */
/* } */
/* static bool my_cool_effect2(effect_params_t* params) { */
/*   if (params->init) my_cool_effect2_complex_init(params); */
/*   return my_cool_effect2_complex_run(params); */
/* } */

/* #endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS */
