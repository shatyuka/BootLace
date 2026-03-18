#include <lvgl/lvgl.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

volatile bool exit = false;

static void normal_system_event_cb(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    exit = true;
  }
}

void log_print(lv_log_level_t level, const char* buf) { Print(L"%a\n", buf); }

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable) {
  lv_uefi_init(ImageHandle, SystemTable);
  lv_init();

  if (!lv_is_initialized())
    return EFI_NOT_READY;

  lv_log_register_print_cb(log_print);

  EFI_HANDLE displayHandle = lv_uefi_display_get_active();
  if (!displayHandle)
    displayHandle = lv_uefi_display_get_any();
  if (!displayHandle) {
    lv_deinit();
    return EFI_UNSUPPORTED;
  }

  lv_display_t* display = lv_uefi_display_create(displayHandle);
  lv_display_set_default(display);

  lv_group_t* group = lv_group_create();
  lv_group_set_default(group);

  lv_obj_t* cursor = lv_image_create(lv_layer_top());
  LV_IMAGE_DECLARE(image_cursor);
  lv_image_set_src(cursor, &image_cursor);

  lv_indev_t* indev_simple_text_input = lv_uefi_simple_text_input_indev_create();
  lv_indev_set_group(indev_simple_text_input, group);
  lv_uefi_simple_text_input_indev_add_all(indev_simple_text_input);

  lv_indev_t* indev_simple_pointer = lv_uefi_simple_pointer_indev_create(NULL);
  lv_uefi_simple_pointer_indev_add_all(indev_simple_pointer);
  lv_indev_set_cursor(indev_simple_pointer, cursor);

  lv_indev_t* indev_absolute_pointer = lv_uefi_absolute_pointer_indev_create(NULL);
  lv_uefi_absolute_pointer_indev_add_all(indev_absolute_pointer);

  lv_obj_t* screen = lv_screen_active();
  lv_obj_set_size(screen, LV_PCT(100), LV_PCT(100));
  lv_obj_set_layout(screen, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(screen, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  lv_obj_set_style_pad_top(screen, 200, 0);
  lv_obj_set_style_pad_bottom(screen, 200, 0);
  lv_obj_set_style_pad_left(screen, 200, 0);
  lv_obj_set_style_pad_right(screen, 200, 0);
  lv_obj_set_style_pad_gap(screen, 100, 0);
  {
    lv_obj_t* label = lv_label_create(screen);
    lv_obj_set_size(label, 800, 200);
    lv_label_set_text_static(label, "BootLace");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  }
  {
    lv_obj_t* button = lv_button_create(screen);
    lv_obj_set_size(button, 800, 200);
    lv_obj_set_style_bg_color(button, lv_color_make(0, 0, 0), 0);
    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text_static(label, "KernelSU");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
    lv_obj_center(label);
  }
  {
    lv_obj_t* button = lv_button_create(screen);
    lv_obj_set_size(button, 800, 200);
    lv_obj_set_style_bg_color(button, lv_color_make(80, 220, 80), 0);
    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text_static(label, "Normal System");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
    lv_obj_center(label);
    lv_obj_add_event_cb(button, normal_system_event_cb, LV_EVENT_CLICKED, NULL);
  }
  {
    lv_obj_t* button = lv_button_create(screen);
    lv_obj_set_size(button, 800, 200);
    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text_static(label, "Recovery");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
    lv_obj_center(label);
  }
  {
    lv_obj_t* button = lv_button_create(screen);
    lv_obj_set_size(button, 800, 200);
    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text_static(label, "Fastboot");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
    lv_obj_center(label);
  }
  {
    lv_obj_t* button = lv_button_create(screen);
    lv_obj_set_size(button, 800, 200);
    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text_static(label, "EDL");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
    lv_obj_center(label);
  }
  {
    lv_obj_t* button = lv_button_create(screen);
    lv_obj_set_size(button, 800, 200);
    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text_static(label, "Reboot");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
    lv_obj_center(label);
  }
  {
    lv_obj_t* button = lv_button_create(screen);
    lv_obj_set_size(button, 800, 200);
    lv_obj_set_style_bg_color(button, lv_color_make(220, 70, 70), 0);
    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text_static(label, "Power Off");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
    lv_obj_center(label);
  }

  while (!exit) {
    lv_tick_inc(1);
    lv_timer_handler();
    gBS->Stall(1000);
  }

  return EFI_SUCCESS;
}
