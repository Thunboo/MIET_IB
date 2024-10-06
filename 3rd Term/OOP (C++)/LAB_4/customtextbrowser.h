#ifndef CUSTOMTEXTBROWSER_H
#define CUSTOMTEXTBROWSER_H

#include <QTextBrowser>

class CustomTextBrowser : public QTextBrowser {
    Q_OBJECT
public:
    CustomTextBrowser(QWidget* parent = nullptr);
};

#endif // CUSTOMTEXTBROWSER_H
