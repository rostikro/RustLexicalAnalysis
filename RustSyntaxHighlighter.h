//
// Created by rostyslav.romanets on 10/20/2024.
//

#ifndef RUSTSYNTAXHIGHLIGHTER_H
#define RUSTSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include "Parser.h"


class RustSyntaxHighlighter: QSyntaxHighlighter {
public:
    explicit RustSyntaxHighlighter(QObject* parent)
        : QSyntaxHighlighter(parent)
    {
        initFormats();
    }

    explicit RustSyntaxHighlighter(QTextDocument* textDocument)
        : QSyntaxHighlighter(textDocument)
    {
        initFormats();
    }
private:
    void highlightBlock(const QString& text) override;

    void initFormats();

    // Helpers
    void setStyle(const QString& text, const QRegularExpression& expression, TokenType type);

    // Syntax analyzer functions
    void keywords(const QString& text);

    void identifiers(const QString& text);

    void function_identifiers(const QString& text);

    void num_literals(const QString& text);

    void string_literals(const QString& text);

    void operators(const QString& text);

    void punctuators(const QString& text);

    void macroses(const QString& text);

    void doc_comments(const QString& text);

    void comments(const QString& text);

private:
    std::unordered_map<TokenType, QTextCharFormat> tokenFormats;

    // Consts
    const QVector<QString> m_keywords = {"fn", "for", "if", "else", "let", "struct", "const", "static", "use"};
    const QVector<QString> m_operators = {"\\+", "-", "\\*", "\\/", "=", "\\+=", "-=", "\\*=", "\\/=", "::"};
};

#endif //RUSTSYNTAXHIGHLIGHTER_H
