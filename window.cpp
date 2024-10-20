//
// Created by rostyslav.romanets on 10/19/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Window.h" resolved

#include "window.h"

#include "RustSyntaxHighlighter.h"
#include "ui_Window.h"


Window::Window(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Window) {
    ui->setupUi(this);

    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, QColor(30, 30, 30)); // BG
    p.setColor(QPalette::Text, Qt::white); // (plain) TEXT
    ui->textEdit->setPalette(p);

    highlighter_ = new RustSyntaxHighlighter(ui->textEdit->document());
}

Window::~Window() {
    delete ui;
}
