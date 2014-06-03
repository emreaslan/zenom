#include "inogenerator.h"
#include "cppparser.h"
#include <QTextStream>

#define GENERATE_INO_PARAMETER (std::string("--generateino"))

#define INDENTATION_TEXT ("    ")

InoGenerator::InoGenerator()
{
}

void InoGenerator::printUsage()
{
    printf ("usage: znm-target-project project_name --generateino  : Generates .ino file from Arduino project.\n");
}

bool InoGenerator::checkParameters(int argc, char *argv[])
{
    if ( argc != 3 || (std::string(argv[1]) != GENERATE_INO_PARAMETER && std::string(argv[2]) != GENERATE_INO_PARAMETER) )
    {
        return false;
    }
    return true;
}

bool InoGenerator::processParameters(int argc, char *argv[])
{
    if (std::string(argv[1]) == GENERATE_INO_PARAMETER )
    {
        return generateIno(QString(argv[2]) );
    }
    else
    {
        return generateIno(QString(argv[1]) );
    }
}

bool InoGenerator::generateIno(QString pFileName)
{
    if (!pFileName.endsWith(".cpp"))
    {
        printf("Invalid ControlBaseArduino file!\n");
        return false;
    }

    if( !mCppParser.parseFile(pFileName) )
    {
        printf("ControlBaseArduino file cannot be opened!\n");
        return false;
    }

    QString inoFileName = mCppParser.projectName() + ".ino";

    QFile inoFile(QString("./src/") + inoFileName);
    if ( !inoFile.open(QFile::WriteOnly | QFile::Text) )
    {
        fprintf(stderr, "The ino file cannot be created because the file '%s' could not be opened.\n", inoFileName.toAscii().data());
        return false;  /* exit status of the program : non-zero for errors */
    }

    fillInoFile(inoFile);

    inoFile.close();

    return true;
}

void InoGenerator::fillInoFile(QFile &pInoFile)
{
    QTextStream out( &pInoFile );
    out << "#include \"zenomarduinomanager.h\"" << "\n";
    out << "\n";
    out << "ZenomArduinoManager zenomManager;" << "\n";
    out << "\n";

    // Log Variables declaration
    out << "// Log Variables" << "\n";
    for (int i = 0; i < mCppParser.logVariables().size(); ++i)
    {
        out << "double "<< mCppParser.logVariables()[i] << ";" << "\n";
    }

    // Control Variables deckaration
    out << "\n";
    out << "// Control Variables" << "\n";
    for (int i = 0; i < mCppParser.controlVariables().size(); ++i)
    {
        out << "double "<< mCppParser.controlVariables()[i] << ";" << "\n";
    }

    out << "\n";

    out << "void setup()" << "\n";
    out << "{" << "\n";

    // Log Variables Register
    out << INDENTATION_TEXT << "// Log Variable Register" << "\n";
    for (int i = 0; i < mCppParser.logVariables().size(); ++i)
    {
        out << INDENTATION_TEXT << "zenomManager.registerLogVariable(&"<< mCppParser.logVariables()[i] << ", \"" << mCppParser.logVariables()[i] << "\");"  << "\n";
    }

    // Control Variables Register
    out << INDENTATION_TEXT << "\n";
    out << INDENTATION_TEXT << "// Control Variable Register" << "\n";
    for (int i = 0; i < mCppParser.controlVariables().size(); ++i)
    {
        out << INDENTATION_TEXT <<"zenomManager.registerControlVariable(&"<< mCppParser.controlVariables()[i] << ", \"" << mCppParser.controlVariables()[i] << "\");"  << "\n";
    }

    out << "\n";
    out << INDENTATION_TEXT << "Serial.begin (9600);" << "\n";
    out << INDENTATION_TEXT << "\n";
    out << INDENTATION_TEXT << "// User Code" << "\n";
    out << INDENTATION_TEXT << "\n";
    out << "}" << "\n";
    out << "\n" ;
    out << "void loop()" << "\n";
    out << "{" << "\n";
    out << INDENTATION_TEXT << "zenomManager.loopPreProcess();" << "\n";
    out << INDENTATION_TEXT << "\n";
    out << INDENTATION_TEXT << "// User Code Begin" << "\n";
    out << INDENTATION_TEXT << "\n";
    out << INDENTATION_TEXT << "\n";
    out << INDENTATION_TEXT << "\n";
    out << INDENTATION_TEXT << "// User Code End" << "\n";
    out << INDENTATION_TEXT << "\n";
    out << INDENTATION_TEXT << "zenomManager.loopPostProcess();" << "\n";
    out << INDENTATION_TEXT << "delay(500); // delay time editable" << "\n";
    out << "}" << "\n";
}


