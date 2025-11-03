#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // Palabras clave estructurales (azul)
    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bINICIAR\\b"), QStringLiteral("\\bFINALIZAR\\b"),
        QStringLiteral("\\bLOTE\\b"), QStringLiteral("\\bCULTIVO\\b"),
        QStringLiteral("\\bVAR\\b"), QStringLiteral("\\bCONST\\b"),  // AÑADIDO CONST
        QStringLiteral("\\bDISPOSITIVO\\b"),
        QStringLiteral("\\bCONDICION\\b"), QStringLiteral("\\bFIN_CONDICION\\b"),
        QStringLiteral("\\bALERTA\\b"), QStringLiteral("\\bFIN_ALERTA\\b"),
        QStringLiteral("\\bSI\\b"), QStringLiteral("\\bENTONCES\\b"),
        QStringLiteral("\\bSINO\\b"), QStringLiteral("\\bSINO_SI\\b"),  // AÑADIDO SINO y SINO_SI
        QStringLiteral("\\bEN\\b"), QStringLiteral("\\bA\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Comandos/acciones (magenta oscuro)
    commandFormat.setForeground(QColor(139, 0, 139));
    commandFormat.setFontWeight(QFont::Bold);
    const QString commandPatterns[] = {
        QStringLiteral("\\bSENSOR\\b"), QStringLiteral("\\bACTUADOR\\b"),
        QStringLiteral("\\bUBICAR_SENSOR\\b"), QStringLiteral("\\bUBICAR_ACTUADOR\\b"),
        QStringLiteral("\\bUBICAR_DISPOSITIVO\\b"), QStringLiteral("\\bVINCULAR\\b"),
        QStringLiteral("\\bIP\\b"), QStringLiteral("\\bPUERTO\\b"), 
        QStringLiteral("\\bSERIAL\\b"),
        QStringLiteral("\\bRIEGO\\b"), QStringLiteral("\\bRIEGO_AVANZADO\\b"), 
        QStringLiteral("\\bACTIVAR\\b"), QStringLiteral("\\bCALCULAR\\b"),
        QStringLiteral("\\bDURACION\\b"), QStringLiteral("\\bCAUDAL\\b"), 
        QStringLiteral("\\bFERTILIZACION\\b"),
        QStringLiteral("\\bTIPO\\b"), QStringLiteral("\\bCANTIDAD\\b"),
        QStringLiteral("\\bMONITOREAR\\b"), QStringLiteral("\\bCADA\\b"),
        QStringLiteral("\\bHORAS\\b"), QStringLiteral("\\bTAREA\\b"),
        QStringLiteral("\\bEJECUTAR\\b"), QStringLiteral("\\bREPORTE\\b"),
        QStringLiteral("\\bENVIAR_ALERTA\\b"),
        QStringLiteral("\\bASIGNAR\\b")  // AÑADIDO ASIGNAR
    };
    for (const QString &pattern : commandPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = commandFormat;
        highlightingRules.append(rule);
    }

    // Operadores lógicos (naranja oscuro con negrita)
    QTextCharFormat logicalOperatorFormat;
    logicalOperatorFormat.setForeground(QColor(255, 100, 0));
    logicalOperatorFormat.setFontWeight(QFont::Bold);
    const QString logicalPatterns[] = {
        QStringLiteral("\\bY\\b"), 
        QStringLiteral("\\bO\\b"),
        QStringLiteral("\\bNO\\b")
    };
    for (const QString &pattern : logicalPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = logicalOperatorFormat;
        highlightingRules.append(rule);
    }

    // Identificadores especiales - tipos minúsculas (verde oscuro) - DEPRECADO pero compatible
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(QColor(0, 128, 0));
    const QString classPatterns[] = {
        QStringLiteral("\\bhumedad\\b"), QStringLiteral("\\btemperatura\\b"),
        QStringLiteral("\\briego\\b"), QStringLiteral("\\bph\\b"),
        QStringLiteral("\\bluz\\b"), QStringLiteral("\\bco2\\b"),
        QStringLiteral("\\bnumero\\b"), QStringLiteral("\\bpresion\\b"),
        QStringLiteral("\\bviento\\b"), QStringLiteral("\\bvalvula\\b"),
        QStringLiteral("\\bventilador\\b"), QStringLiteral("\\blampara\\b")
    };
    for (const QString &pattern : classPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = classFormat;
        highlightingRules.append(rule);
    }
    
    // Tipos de datos PascalCase (azul cyan - color distintivo para tipos)
    QTextCharFormat typeFormat;
    typeFormat.setForeground(QColor(0, 128, 200));  // Azul cyan
    typeFormat.setFontWeight(QFont::Bold);
    const QString typePatterns[] = {
        QStringLiteral("\\bHumedad\\b"), QStringLiteral("\\bTemperatura\\b"),
        QStringLiteral("\\bPh\\b"), QStringLiteral("\\bLuz\\b"),
        QStringLiteral("\\bCo2\\b"), QStringLiteral("\\bPresion\\b"),
        QStringLiteral("\\bViento\\b"), QStringLiteral("\\bNumero\\b")
    };
    for (const QString &pattern : typePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = typeFormat;
        highlightingRules.append(rule);
    }
    
    // Identificadores de variables (verde claro - después de palabras clave)
    // Formato: palabra_con_guiones_bajos
    QTextCharFormat identifierFormat;
    identifierFormat.setForeground(QColor(50, 180, 100));
    rule.pattern = QRegularExpression(QStringLiteral("\\b[a-z][a-z0-9_]*\\b"));
    rule.format = identifierFormat;
    highlightingRules.append(rule);
    
    // Identificadores de constantes (mayúsculas con guiones bajos) - morado
    QTextCharFormat constantFormat;
    constantFormat.setForeground(QColor(128, 0, 128));
    constantFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Z][A-Z0-9_]*\\b"));
    rule.format = constantFormat;
    highlightingRules.append(rule);

    // Strings entre comillas (rojo) - PRIMERO para proteger contenido
    quotationFormat.setForeground(QColor(163, 21, 21));
    rule.pattern = QRegularExpression(QStringLiteral("\"[^\"]*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // Números (cian oscuro)
    numberFormat.setForeground(QColor(0, 139, 139));
    rule.pattern = QRegularExpression(QStringLiteral("\\b-?[0-9]+(\\.[0-9]+)?\\b"));
    rule.format = numberFormat;
    highlightingRules.append(rule);

    // Operadores de comparación (naranja)
    operatorFormat.setForeground(QColor(255, 140, 0));
    operatorFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("<=|>=|==|<|>|="));
    rule.format = operatorFormat;
    highlightingRules.append(rule);
    
    // Operadores matemáticos (naranja oscuro)
    QTextCharFormat mathOperatorFormat;
    mathOperatorFormat.setForeground(QColor(200, 100, 0));
    mathOperatorFormat.setFontWeight(QFont::Bold);
    const QString mathOperators[] = {
        QStringLiteral("\\+"), QStringLiteral("-"),
        QStringLiteral("\\*"), QStringLiteral("/"),
        QStringLiteral("%")
    };
    for (const QString &pattern : mathOperators) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = mathOperatorFormat;
        highlightingRules.append(rule);
    }
    
    // Paréntesis (gris oscuro)
    QTextCharFormat parenFormat;
    parenFormat.setForeground(QColor(64, 64, 64));
    parenFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("[\\(\\)]"));
    rule.format = parenFormat;
    highlightingRules.append(rule);
    
    // Dos puntos (gris)
    QTextCharFormat colonFormat;
    colonFormat.setForeground(QColor(100, 100, 100));
    rule.pattern = QRegularExpression(QStringLiteral(":"));
    rule.format = colonFormat;
    highlightingRules.append(rule);

    // Comentarios de una línea estilo Java (gris)
    singleLineCommentFormat.setForeground(Qt::gray);
    singleLineCommentFormat.setFontItalic(true);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
    
    // Comentarios multi-línea estilo Java
    multiLineCommentFormat.setForeground(Qt::gray);
    multiLineCommentFormat.setFontItalic(true);
    
    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void Highlighter::highlightBlock(const QString &text)
{
    // PRIMERO: Aplicar strings para proteger su contenido
    QRegularExpressionMatchIterator stringIterator = QRegularExpression(QStringLiteral("\"[^\"]*\"")).globalMatch(text);
    QVector<QPair<int, int>> stringRanges;
    while (stringIterator.hasNext()) {
        QRegularExpressionMatch match = stringIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), quotationFormat);
        stringRanges.append(qMakePair(match.capturedStart(), match.capturedStart() + match.capturedLength()));
    }
    
    // SEGUNDO: Aplicar comentarios de una línea
    QRegularExpressionMatch commentMatch = QRegularExpression(QStringLiteral("//[^\n]*")).match(text);
    int commentStart = -1;
    if (commentMatch.hasMatch()) {
        commentStart = commentMatch.capturedStart();
        setFormat(commentStart, commentMatch.capturedLength(), singleLineCommentFormat);
    }
    
    // TERCERO: Aplicar el resto de reglas, pero SOLO fuera de strings y comentarios
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        // Saltar la regla de comentarios porque ya la procesamos
        if (rule.format.fontItalic() && rule.format.foreground().color() == Qt::gray) {
            continue;
        }
        
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            int start = match.capturedStart();
            int end = start + match.capturedLength();
            
            // Verificar si este match está dentro de un string
            bool insideString = false;
            for (const auto &range : stringRanges) {
                if (start >= range.first && end <= range.second) {
                    insideString = true;
                    break;
                }
            }
            
            // Verificar si está dentro de un comentario
            bool insideComment = (commentStart != -1 && start >= commentStart);
            
            // Solo aplicar formato si NO está dentro de un string o comentario
            if (!insideString && !insideComment) {
                setFormat(start, match.capturedLength(), rule.format);
            }
        }
    }
    
    // CUARTO: Manejo de comentarios multi-línea (también respeta strings)
    setCurrentBlockState(0);
    
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);
    
    while (startIndex >= 0) {
        // Verificar si el inicio del comentario está dentro de un string
        bool insideString = false;
        for (const auto &range : stringRanges) {
            if (startIndex >= range.first && startIndex < range.second) {
                insideString = true;
                break;
            }
        }
        
        if (!insideString) {
            QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
            int endIndex = match.capturedStart();
            int commentLength = 0;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex + match.capturedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
        }
        
        startIndex = text.indexOf(commentStartExpression, startIndex + 1);
    }
}