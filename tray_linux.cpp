#include "QtTrayMenu.h"
#include <QApplication>
#include <QShortcut>
#include <QKeySequence>

#include "tray.h"

#include <iostream>

static QtTrayMenu *trayMenuInstance = nullptr;
static struct tray *currentTrayStruct = nullptr;
hotkey_handler hk_handler = NULL;

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
    hk_handler = handle;
}

char tray_register_hotkey(const char* hotkey)
{
    if(!trayMenuInstance)
        return -1;

    trayMenuInstance->registerShortcut(QString::fromUtf8(hotkey));
    return 0;
}

void tray_unregister_hotkey(const char* hotkey)
{
    trayMenuInstance->unregisterShortcut(QString::fromUtf8(hotkey));
}

} // extern "C"
