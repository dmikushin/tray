#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QObject>

#include "tray.h"

class UGlobalHotkeys;

class QtTrayMenu : public QObject
        {
            Q_OBJECT

            public:
                QtTrayMenu();
                ~QtTrayMenu();
                virtual bool eventFilter(QObject *watched, QEvent *event) override;
                int init(struct tray *tray);
                void update(struct tray *tray);
                int loop(int blocking);
                void exit();

                void registerShortcut(const QString &shortcut);
                void unregisterShortcut(const QString &shortcut);

            private:
                void createMenu(struct tray_menu_item *items, QMenu *menu);
                void onTrayActivated(QSystemTrayIcon::ActivationReason reason);
                void onMenuItemTriggered();
                QApplication *app;
                QSystemTrayIcon *trayIcon;
                struct tray *trayStruct;
                UGlobalHotkeys *hotkeys;

                bool continueRunning;
                struct tray_menu_item *getTrayMenuItem(QAction *action);
                QHash<int, QString> shortcuts;

            signals:
                void exitRequested();

            public slots:
                void onShortcutPressed(int id);

            private slots:
                void onExitRequested();
};


#endif // TRAYMENU_H
