#include "utilities.h"


Monster createNextMonster(int index) {
    switch (index) {
    case 0:
        return Monster("ƒXƒ‰ƒCƒ€", 20, 3, 5, 0.05, "‚½‚¢‚ ‚½‚è");//("“G–¼",‘Ì—Í,Å¬EÅ‘åUŒ‚—Í,‰ñ”ğ—¦,"‹Z–¼")
    case 1:
        return Monster("ƒSƒuƒŠƒ“", 30, 5, 7, 0.10, "ƒSƒuƒŠƒ“ƒpƒ“ƒ`");
    case 2:
        return Monster("ƒS[ƒŒƒ€", 60, 7, 10, 0.00, "ŠâÎ‚¨‚Æ‚µ");
    case 3:
        return Monster("‚ ‚­‚Ü‚Ì‚«‚µ", 50, 7, 10, 0.30, "‚È‚¬‚Í‚ç‚¢");
    case 4:
        return Monster("–‚‰¤", 100, 10, 15, 0.30, "‚ ‚­‚Ì‚Í‚Ç‚¤");
    default:
        return Monster("Unknown", 0, 0, 0, 0.0, "Unknown");
    }
}

