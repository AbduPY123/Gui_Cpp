#include "languagevisitor.h"

void LanguageVisitor::fun(){}

LanguageRussianVisitor::LanguageRussianVisitor()
{
    translator.load(":/language/QtLanguage_ru.qm");
    qApp->installTranslator(&translator);
}

void LanguageRussianVisitor::fun(){}

LanguageEnglishVisitor::LanguageEnglishVisitor()
{
    translator.load(":/language/QtLanguage_en.qm");
    qApp->installTranslator(&translator);
}

void LanguageEnglishVisitor::fun(){}

void LanguageVisitor::retranslate(MainWindow* mainWindow)
{
    if(mainWindow == nullptr) return;
    mainWindow->retranslate();
}

