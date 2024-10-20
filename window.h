//
// Created by rostyslav.romanets on 10/19/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class RustSyntaxHighlighter;
QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow {
Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;

private:
    Ui::Window *ui;

    RustSyntaxHighlighter *highlighter_;
};


#endif //WINDOW_H
