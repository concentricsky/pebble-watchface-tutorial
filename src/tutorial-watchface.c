#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xBD, 0x46, 0x1D, 0x5E, 0xCA, 0x85, 0x40, 0xF3, 0xB3, 0x63, 0x15, 0x99, 0xA1, 0x42, 0x29, 0x8F }
PBL_APP_INFO(MY_UUID,
             "TemplateWatch", "Concentric Sky",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_STANDARD_APP);


Window g_Window;


void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)ctx;
  (void)t;

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
