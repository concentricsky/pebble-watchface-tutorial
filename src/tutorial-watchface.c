#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xBD, 0x46, 0x1D, 0x5E, 0xCA, 0x85, 0x40, 0xF3, 0xB3, 0x63, 0x15, 0x99, 0xA1, 0x42, 0x29, 0x8F }
PBL_APP_INFO(MY_UUID,
             "Template App", "Your Company",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;


void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
