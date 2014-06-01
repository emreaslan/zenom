#ifndef ARDUINOPROJECTBASE_H
#define ARDUINOPROJECTBASE_H


class TargetProjectBase
{
public:
    virtual void printUsage() = 0;
    virtual bool checkParameters(int argc, char *argv[]) = 0;
    virtual bool processParameters(int argc, char *argv[]) = 0;
};

#endif // ARDUINOPROJECTBASE_H
