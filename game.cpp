#include "game.h"
#include "utilities.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() : player(nullptr), monsterIndex(0) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Game::start() {
    std::string playerName;
    int jobChoice;
    std::cout << "ƒvƒŒƒCƒ„[–¼‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ";
    std::cin >> playerName;
    std::cout << "E‹Æ‚ğ‘I‚ñ‚Å‚­‚¾‚³‚¢:\n";
    std::cout << "1. —EÒ (‘Ì—Í: 40, UŒ‚—Í: 5-8, ‰ñ”ğ—¦: 20%)\n";
    std::cout << "2. ím (‘Ì—Í: 50, UŒ‚—Í: 3-10, ‰ñ”ğ—¦: 5%)\n";
    std::cout << "3. •“¬‰Æ (‘Ì—Í: 30, UŒ‚—Í: 4-8, ‰ñ”ğ—¦: 30%)\n";
    std::cin >> jobChoice;
    std::cout << std::endl;
    switch (jobChoice) {
    case 1:
        player = new Player(playerName, "—EÒ");
        std::cout << "—EÒ‚ª‘I‘ğ‚³‚ê‚Ü‚µ‚½!–`Œ¯‚Ìn‚Ü‚è‚Å‚·!" << std::endl;
        break;
    case 2:
        player = new Player(playerName, "ím");
        std::cout << "ím‚ª‘I‘ğ‚³‚ê‚Ü‚µ‚½!–`Œ¯‚Ìn‚Ü‚è‚Å‚·!" << std::endl;
        break;
    case 3:
        player = new Player(playerName, "•“¬‰Æ");
        std::cout << "•“¬‰Æ‚ª‘I‘ğ‚³‚ê‚Ü‚µ‚½!–`Œ¯‚Ìn‚Ü‚è‚Å‚·!" << std::endl;
        break;
    default:
        std::cout << "–³Œø‚È‘I‘ğ‚Ì‚½‚ß—EÒ‚Éİ’è‚³‚ê‚Ü‚µ‚½B–`Œ¯‚Ìn‚Ü‚è‚Å‚·!\n";
        player = new Player(playerName, "—EÒ");
        break;
    }

    while (player->isAlive() && monsterIndex < 5) {
        Monster monster = createNextMonster(monsterIndex);
        battle(monster);
        if (player->isAlive()) {
            monsterIndex++;
        }
    }

    if (player->isAlive()) {
        std::cout << "ƒQ[ƒ€ƒNƒŠƒAI‚¨‚ß‚Å‚Æ‚¤I" << std::endl;
    }
    else {
        std::cout << "ƒQ[ƒ€ƒI[ƒo[!" << std::endl;
    }

    delete player;
}


Monster Game::createNextMonster(int index) {
    switch (index) {
    case 0:
        return Monster("ƒXƒ‰ƒCƒ€", 20, 3, 5, 0.05, "‚½‚¢‚ ‚½‚è");    //("“G–¼",‘Ì—Í,Å¬EÅ‘åUŒ‚—Í,‰ñ”ğ—¦,"‹Z–¼")
    case 1:
        return Monster("ƒSƒuƒŠƒ“", 30, 5, 7, 0.10, "ƒSƒuƒŠƒ“ƒpƒ“ƒ`");
    case 2:
        return Monster("ƒS[ƒŒƒ€", 60, 7, 10, 0.00, "ŠâÎ‚¨‚Æ‚µ");
    case 3:
        return Monster("‚ ‚­‚Ü‚Ì‚«‚µ", 50, 7, 10, 0.30, "‚È‚¬‚Í‚ç‚¢");
    case 4:
        return Monster("‚Ü‚¨‚¤", 100, 10, 15, 0.30, "‚ ‚­‚Ì‚Í‚Ç‚¤");
    default:
        return Monster("Unknown", 0, 0, 0, 0.0, "Unknown");
    }
}

void Game::battle(Monster& monster) {
    std::cout << monster.getName() << "‚ª‚ ‚ç‚í‚ê‚½!" << std::endl;

    while (player->isAlive() && monster.isAlive()) {
        std::cout << "ƒvƒŒƒCƒ„[c‚è‘Ì—Í: " << player->getHealth() << "/" << player->getMaxHealth() << " | ";
        std::cout << monster.getName() << " c‚è‘Ì—Í: " << monster.getHealth() << std::endl;

        std::cout << "s“®‚ğ‘I‚ñ‚Å‰º‚³‚¢: 1. UŒ‚  2. ƒJƒEƒ“ƒ^[(“G‚ªæ‚És“®‚·‚é‚Æ¬Œ÷)" << std::endl;
        int choice;
        std::cin >> choice;

        bool playerGoesFirst = rand() % 2 == 0;

        //1.UŒ‚
        if (choice == 1) {
            if (playerGoesFirst) {
                int damage = player->attack();
                if (!monster.dodge()) {
                    monster.takeDamage(damage);
                    std::cout << player->getName() << "‚Í" << monster.getName() << "‚ÉUŒ‚‚µA" << damage << "ƒ_ƒ[ƒW‚ğ—^‚¦‚½!" << std::endl;
                }
                else {
                    std::cout << player->getName() << monster.getSkillName() << "‚ÌUŒ‚!" << std::endl;
                    std::cout << monster.getName() << "‚ÍUŒ‚‚ğ‰ñ”ğ‚µ‚½!" << std::endl;
                }

                if (!monster.isAlive()) {
                    std::cout << monster.getName() << "‚ğ“|‚µ‚½!" << std::endl;
                    player->healToFull();
                    player->gainExperience(100); //100XP‚ğŠl“¾
                    break;
                }

                damage = monster.attack();
                if (!player->dodge()) {
                    player->takeDamage(damage);
                    std::cout << monster.getName() << "‚Í" << player->getName() << "‚ÉUŒ‚‚µA" << damage << "ƒ_ƒ[ƒW‚ğ—^‚¦‚½!" << std::endl;
                }
                else {
                    std::cout << monster.getName() << "‚ÌUŒ‚!" << std::endl;
                    std::cout << player->getName() << "‚ÍUŒ‚‚ğ‰ñ”ğ‚µ‚½!" << std::endl;
                }
            }
            else {
                int damage = monster.attack();
                if (!player->dodge()) {
                    player->takeDamage(damage);
                    std::cout << monster.getName() << "‚Í" << player->getName() << "‚ÉUŒ‚‚µA" << damage << "ƒ_ƒ[ƒW‚ğ—^‚¦‚½!" << std::endl;
                }

                if (!player->isAlive()) {
                    std::cout << player->getName() << "‚Í“|‚ê‚½!" << std::endl;
                    break;
                }

                else {
                    std::cout << monster.getName() << "‚ÌUŒ‚!" << std::endl;
                    std::cout << player->getName() << "‚ÍUŒ‚‚ğ‰ñ”ğ‚µ‚½!" << std::endl;
                }

                if (!player->isAlive()) {
                    std::cout << player->getName() << "‚Í“|‚ê‚½!" << std::endl;
                    break;
                }

                damage = player->attack();
                if (!monster.dodge()) {
                    monster.takeDamage(damage);
                    std::cout << player->getName() << "‚Í" << monster.getName() << "‚ÉUŒ‚‚µA" << damage << "ƒ_ƒ[ƒW‚ğ—^‚¦‚½!" << std::endl;
                }
                else {
                    std::cout << player->getName() << "‚ÌUŒ‚!" << std::endl;
                    std::cout << monster.getName() << "‚ÍUŒ‚‚ğ‰ñ”ğ‚µ‚½!" << std::endl;
                }

                if (!monster.isAlive()) {
                    std::cout << monster.getName() << "‚ğ“|‚µ‚½!" << std::endl;
                    player->healToFull();
                    player->gainExperience(100);
                    break;
                }
            }
        }

        //2.ƒJƒEƒ“ƒ^[
        else if (choice == 2) {
            if (playerGoesFirst) {  //ƒvƒŒƒCƒ„[‚ªæ‚És“®‚µ‚Ä‚µ‚Ü‚¤‚Æ¸”s‚µUŒ‚‚ğó‚¯‚é
                std::cout << player->getName() << "‚ÍƒJƒEƒ“ƒ^[‚ğ‘_‚Á‚½‚ªA¸”s‚µ‚½!" << std::endl;

                int damage = monster.attack();
                player->takeDamage(monster.attack());
                std::cout << player->getName() << "‚Íƒ_ƒ[ƒW‚ğó‚¯‚½!" << std::endl;
            }

            if (!player->isAlive()) {
                std::cout << player->getName() << "‚Í“|‚ê‚½!" << std::endl;
                break;
            }

            else {  //“G‚ªæ‚És“®‚·‚é‚ÆƒJƒEƒ“ƒ^[¬Œ÷
                int damage = monster.attack();
                std::cout << monster.getName() << "‚ÌUŒ‚!" << std::endl;
                std::cout << "ƒJƒEƒ“ƒ^[¬Œ÷! " << monster.getName() << "‚É" << damage << "ƒ_ƒ[ƒW‚ğ—^‚¦‚½!" << std::endl;
                monster.takeDamage(damage);

            }
            if (!monster.isAlive()) {
                std::cout << monster.getName() << "‚ğ“|‚µ‚½!" << std::endl;
                player->healToFull();
                player->gainExperience(100);
                break;
            }
        }
    }
}