//
// Created by rostyslav.romanets on 10/20/2024.
//

#include <QRegularExpression>

#include "RustSyntaxHighlighter.h"

void RustSyntaxHighlighter::highlightBlock(const QString& text)
{
    setFormat(0, text.length(), tokenFormats[UNKNOWN]);

    num_literals(text);
    identifiers(text);
    string_literals(text);
    function_identifiers(text);
    punctuators(text);
    operators(text);
    keywords(text);
    macroses(text);
    comments(text);
    doc_comments(text);
}

void RustSyntaxHighlighter::initFormats()
{
    QTextCharFormat orangeText;
    orangeText.setForeground(QColor("orange"));

    QTextCharFormat yellowText;
    yellowText.setForeground(QColor("yellow"));

    QTextCharFormat greenText;
    greenText.setForeground(QColor("green"));

    QTextCharFormat darkGreenText;
    darkGreenText.setForeground(QColor("darkgreen"));

    QTextCharFormat blueText;
    blueText.setForeground(QColor("blue"));

    QTextCharFormat grayText;
    grayText.setForeground(QColor("gray"));

    QTextCharFormat redText;
    redText.setForeground(QColor("red"));

    QTextCharFormat purpleText;
    purpleText.setForeground(QColor("purple"));

    QTextCharFormat cyanColor;
    cyanColor.setForeground(Qt::cyan);

    QTextCharFormat darkMagentaColor;
    darkMagentaColor.setForeground(QColor(250, 100, 200));

    tokenFormats[KEYWORD] = orangeText;
    tokenFormats[IDENTIFIER] = purpleText;
    tokenFormats[FUNCTION_IDENTIFIER] = blueText;

    /*tokenFormats[INTEGER_LITERAL]
    tokenFormats[FLOAT_LITERAL]
    tokenFormats[HEX_LITERAL]*/

    tokenFormats[STRING_LITERAL] = greenText;
    tokenFormats[DOC_COMMENT] = darkGreenText;
    tokenFormats[OPERATOR] = cyanColor;
    tokenFormats[PUNCTUATOR] = darkMagentaColor;
    tokenFormats[MACROS] = yellowText;
    tokenFormats[COMMENT] = grayText;
    tokenFormats[UNKNOWN] = redText;
}

void RustSyntaxHighlighter::setStyle(const QString& text, const QRegularExpression& expression, TokenType type)
{
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[type]);
    }
}

void RustSyntaxHighlighter::keywords(const QString& text)
{
    // TODO: Move to class members and init in ctor
    // But for the sake of readability, it's here :)
    QRegularExpression expression("\\b" + m_keywords.join("\\b|") + "\\b");

    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[KEYWORD]);
    }
}

void RustSyntaxHighlighter::identifiers(const QString& text)
{
    QRegularExpression expression("\\b[a-zA-Z_$][\\w$]*");
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[IDENTIFIER]);
    }
}

void RustSyntaxHighlighter::function_identifiers(const QString& text)
{
    QRegularExpression expression("fn(\\s+)[a-zA-Z_$][\\w$]*");
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart() + 2, match.capturedLength() - 2, tokenFormats[FUNCTION_IDENTIFIER]);
    }
}

void RustSyntaxHighlighter::num_literals(const QString& text)
{
    QRegularExpression floatExpression("[+-]?[0-9]+");
    QRegularExpressionMatchIterator i = floatExpression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[FLOAT_LITERAL]);
    }

    QRegularExpression hexExpression("0[xX][0-9a-fA-F]+");
    i = hexExpression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[HEX_LITERAL]);
    }

    QRegularExpression intExpression("[+-]?([0-9]*[.])?[0-9]+");
    i = intExpression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[INTEGER_LITERAL]);
    }
}

void RustSyntaxHighlighter::string_literals(const QString& text)
{
    QRegularExpression expression("\".*\"");
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[STRING_LITERAL]);
    }
}

void RustSyntaxHighlighter::operators(const QString& text)
{
    QRegularExpression expression(m_operators.join("|"));

    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[OPERATOR]);
    }

    // Additional check for "->" operator
    i = QRegularExpression("->").globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[OPERATOR]);
    }
}

void RustSyntaxHighlighter::punctuators(const QString& text)
{
    QRegularExpression expression("{|}|\\(|\\)|;|<|>");
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[PUNCTUATOR]);
    }
}

void RustSyntaxHighlighter::macroses(const QString& text)
{
    QRegularExpression expression("\\b[a-zA-Z_$][\\w$]*!");
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), tokenFormats[MACROS]);
    }
}

void RustSyntaxHighlighter::doc_comments(const QString& text)
{
    QRegularExpression expression("///");
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), text.length() - match.capturedStart(), tokenFormats[DOC_COMMENT]);
    }
}

void RustSyntaxHighlighter::comments(const QString& text)
{
    QRegularExpression expression("//");
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), text.length() - match.capturedStart(), tokenFormats[COMMENT]);
    }

    QRegularExpression startExpression("/\\*");
    QRegularExpression endExpression("\\*/");

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(startExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch endMatch;
        int endIndex = text.indexOf(endExpression, startIndex, &endMatch);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + endMatch.capturedLength();
        }
        setFormat(startIndex, commentLength, tokenFormats[COMMENT]);
        startIndex = text.indexOf(startExpression,
                                  startIndex + commentLength);
    }
}
