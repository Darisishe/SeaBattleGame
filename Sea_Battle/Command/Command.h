#ifndef COMMAND_H
#define COMMAND_H
class InterfaceIO;
class Command {
public:
    virtual void execute(const InterfaceIO& IO) const = 0;
    virtual bool isMiss() const = 0;
};

class DestroyCommand: public Command {
public:
    void execute(const InterfaceIO& IO) const override;
    bool isMiss() const override;
};
class HitCommand: public Command {
public:
    void execute(const InterfaceIO& IO) const override;
    bool isMiss() const override;
};
class MissCommand: public Command {
public:
    void execute(const InterfaceIO& IO) const override;
    bool isMiss() const override;
};


#endif