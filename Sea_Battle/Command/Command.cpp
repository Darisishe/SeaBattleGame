#include "Command.h"
#include "IO.h"

void DestroyCommand::execute(const InterfaceIO& IO) const {
    IO.destroyMessage();
}
bool DestroyCommand::isMiss() const {
    return false;
}

void HitCommand::execute(const InterfaceIO& IO) const {
    IO.hitMessage();
}
bool HitCommand::isMiss() const {
    return false;
}

void MissCommand::execute(const InterfaceIO& IO) const {
    IO.missMessage();
}
bool MissCommand::isMiss() const {
    return true;
}
