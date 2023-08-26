#ifndef TRAY_H
#define TRAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#define TRAY_EXPORT 

struct tray {
  const char *icon_filepath;
  char *tooltip;
  void (*cb)(struct tray *); // called on left click, leave null to just open menu
  struct tray_menu_item *menu;
};

struct tray_menu_item {
  const char *text;
  int disabled;
  int checked;
  void (*cb)(struct tray_menu_item *);
  struct tray_menu_item *submenu;
};

TRAY_EXPORT
struct tray * tray_get_instance();

TRAY_EXPORT
int tray_init(struct tray *tray);

TRAY_EXPORT
int tray_loop(int blocking);

TRAY_EXPORT
void tray_update(struct tray *tray);

TRAY_EXPORT
void tray_exit(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* TRAY_H */
