#include "QtTrayMenu.h"
#include <QApplication>
#include "tray.h"

static QtTrayMenu *trayMenuInstance = nullptr;
static struct tray *currentTrayStruct = nullptr;

extern "C"
{

TRAY_EXPORT struct tray *tray_get_instance()
{
    return currentTrayStruct;
}

TRAY_EXPORT int tray_init(struct tray *tray)
{
    currentTrayStruct = tray;

    if (!trayMenuInstance)
    {
        trayMenuInstance = new QtTrayMenu();
    }

    return trayMenuInstance->init(tray);
}

TRAY_EXPORT int tray_loop(int blocking) {
    return trayMenuInstance ? trayMenuInstance->loop(blocking) : -1;
}

TRAY_EXPORT void tray_update(struct tray *tray)
{
    currentTrayStruct = tray;
    if (trayMenuInstance)
    {
        trayMenuInstance->update(tray);
    }
}

TRAY_EXPORT void tray_exit(void)
{
    if (trayMenuInstance)
    {
        trayMenuInstance->exit();
    }
}

void set_hotkey_handler(hotkey_handler handle)
{

}

char tray_register_hotkey(const char* hotkey)
{
    return 0;
}

void tray_unregister_hotkey(const char* hotkey)
{

}

void set_hotkey_handler(hotkey_handler handle)
{

}

char tray_register_hotkey(const char* hotkey)
{
    return 0;
}

void tray_unregister_hotkey(const char* hotkey)
{

}

} // extern "C"
