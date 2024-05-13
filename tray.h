#ifndef TRAY_H
#define TRAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _WIN32
#ifdef TRAY_EXPORTS
#define TRAY_EXPORT __declspec(dllexport)
#else
#define TRAY_EXPORT __declspec(dllimport)
#endif
#else
#if __GNUC__ >= 4 || defined(__clang__)
#define TRAY_EXPORT extern __attribute__((visibility("default")))
#else
#define TRAY_EXPORT extern
#endif
#endif

struct tray {
  const char *icon_filepath;
  const char *tooltip;
  void (*cb)(struct tray *); // called on left click, leave null to just open menu
  struct tray_menu_item *menu;
};

struct tray_menu_item {
  const char *text;
  int disabled;
  int checked;
  int checkbox;
  
  void *context;
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

typedef void(*hotkey_handler)(const char*);

TRAY_EXPORT
void set_hotkey_handler(hotkey_handler handle);
TRAY_EXPORT
char tray_register_hotkey(const char* hotkey);
TRAY_EXPORT
void tray_unregister_hotkey(const char* hotkey);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* TRAY_H */
