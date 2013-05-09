#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xBD, 0x46, 0x1D, 0x5E, 0xCA, 0x85, 0x40, 0xF3, 0xB3, 0x63, 0x15, 0x99, 0xA1, 0x42, 0x29, 0x8F }
PBL_APP_INFO(MY_UUID,
             "TemplateWatch", "Concentric Sky",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_STANDARD_APP);


Window g_Window;          // our window
PblTm g_Now;              // the current time--updated by handle_second_tick
TextLayer g_DateLayer;    // a text layer to print the date string

// we need a static buffer for string_format_time
#define _DATE_BUF_LEN 25
static char _DATE_BUFFER[_DATE_BUF_LEN];
#define DATE_FORMAT "%a %B %e %T"        // see the strftime(3) man page for options.


void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)ctx;
  (void)t;

  // update our current time
  get_time(&g_Now);

  // formant and render the date string on the date layer
  string_format_time(_DATE_BUFFER, _DATE_BUF_LEN, DATE_FORMAT, &g_Now);
  text_layer_set_text(&g_DateLayer, _DATE_BUFFER);
}


void handle_init(AppContextRef ctx) {
  (void)ctx;

  /*
   * initialize the window
   */
  window_init(&g_Window, "TemplateWatch");
  window_stack_push(&g_Window, true /* Animated */);
  window_set_background_color(&g_Window, GColorBlack);
  resource_init_current_app(&APP_RESOURCES);


  /* 
   * initialize the date layer
   */
  // our layer occupies the bottom 16px across the entire screen
  text_layer_init(&g_DateLayer, GRect(1, 168-16, 144, 16));
  text_layer_set_text_color(&g_DateLayer, GColorWhite);
  text_layer_set_background_color(&g_DateLayer, GColorClear);
  text_layer_set_text_alignment(&g_DateLayer, GTextAlignmentCenter);
  text_layer_set_font(&g_DateLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  layer_add_child(&g_Window.layer, &g_DateLayer.layer);


  // trigger a second tick manually, to paint our initial frame.
  handle_second_tick(ctx,NULL);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_second_tick,
      .tick_units = SECOND_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
