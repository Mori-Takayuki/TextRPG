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
    std::cout << "プレイヤー名を入力してください: ";
    std::cin >> playerName;
    std::cout << "職業を選んでください:\n";
    std::cout << "1. 勇者 (体力: 40, 攻撃力: 5-8, 回避率: 20%)\n";
    std::cout << "2. 戦士 (体力: 50, 攻撃力: 3-10, 回避率: 5%)\n";
    std::cout << "3. 武闘家 (体力: 30, 攻撃力: 4-8, 回避率: 30%)\n";
    std::cin >> jobChoice;
    std::cout << std::endl;
    switch (jobChoice) {
    case 1:
        player = new Player(playerName, "勇者");
        std::cout << "勇者が選択されました!冒険の始まりです!" << std::endl;
        break;
    case 2:
        player = new Player(playerName, "戦士");
        std::cout << "戦士が選択されました!冒険の始まりです!" << std::endl;
        break;
    case 3:
        player = new Player(playerName, "武闘家");
        std::cout << "武闘家が選択されました!冒険の始まりです!" << std::endl;
        break;
    default:
        std::cout << "無効な選択のため勇者に設定されました。冒険の始まりです!\n";
        player = new Player(playerName, "勇者");
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
        std::cout << "ゲームクリア！おめでとう！" << std::endl;
    }
    else {
        std::cout << "ゲームオーバー!" << std::endl;
    }

    delete player;
}


Monster Game::createNextMonster(int index) {
    switch (index) {
    case 0:
        return Monster("スライム", 20, 3, 5, 0.05, "たいあたり");    //("敵名",体力,最小・最大攻撃力,回避率,"技名")
    case 1:
        return Monster("ゴブリン", 30, 5, 7, 0.10, "ゴブリンパンチ");
    case 2:
        return Monster("ゴーレム", 60, 7, 10, 0.00, "岩石おとし");
    case 3:
        return Monster("あくまのきし", 50, 7, 10, 0.30, "なぎはらい");
    case 4:
        return Monster("まおう", 100, 10, 15, 0.30, "あくのはどう");
    default:
        return Monster("Unknown", 0, 0, 0, 0.0, "Unknown");
    }
}

void Game::battle(Monster& monster) {
    std::cout << monster.getName() << "があらわれた!" << std::endl;

    while (player->isAlive() && monster.isAlive()) {
        std::cout << "プレイヤー残り体力: " << player->getHealth() << "/" << player->getMaxHealth() << " | ";
        std::cout << monster.getName() << " 残り体力: " << monster.getHealth() << std::endl;

        std::cout << "行動を選んで下さい: 1. 攻撃  2. カウンター(敵が先に行動すると成功)" << std::endl;
        int choice;
        std::cin >> choice;

        bool playerGoesFirst = rand() % 2 == 0;

        //1.攻撃
        if (choice == 1) {
            if (playerGoesFirst) {
                int damage = player->attack();
                if (!monster.dodge()) {
                    monster.takeDamage(damage);
                    std::cout << player->getName() << "は" << monster.getName() << "に攻撃し、" << damage << "ダメージを与えた!" << std::endl;
                }
                else {
                    std::cout << player->getName() << monster.getSkillName() << "の攻撃!" << std::endl;
                    std::cout << monster.getName() << "は攻撃を回避した!" << std::endl;
                }

                if (!monster.isAlive()) {
                    std::cout << monster.getName() << "を倒した!" << std::endl;
                    player->healToFull();
                    player->gainExperience(100); //100XPを獲得
                    break;
                }

                damage = monster.attack();
                if (!player->dodge()) {
                    player->takeDamage(damage);
                    std::cout << monster.getName() << "は" << player->getName() << "に攻撃し、" << damage << "ダメージを与えた!" << std::endl;
                }
                else {
                    std::cout << monster.getName() << "の攻撃!" << std::endl;
                    std::cout << player->getName() << "は攻撃を回避した!" << std::endl;
                }
            }
            else {
                int damage = monster.attack();
                if (!player->dodge()) {
                    player->takeDamage(damage);
                    std::cout << monster.getName() << "は" << player->getName() << "に攻撃し、" << damage << "ダメージを与えた!" << std::endl;
                }

                if (!player->isAlive()) {
                    std::cout << player->getName() << "は倒れた!" << std::endl;
                    break;
                }

                else {
                    std::cout << monster.getName() << "の攻撃!" << std::endl;
                    std::cout << player->getName() << "は攻撃を回避した!" << std::endl;
                }

                if (!player->isAlive()) {
                    std::cout << player->getName() << "は倒れた!" << std::endl;
                    break;
                }

                damage = player->attack();
                if (!monster.dodge()) {
                    monster.takeDamage(damage);
                    std::cout << player->getName() << "は" << monster.getName() << "に攻撃し、" << damage << "ダメージを与えた!" << std::endl;
                }
                else {
                    std::cout << player->getName() << "の攻撃!" << std::endl;
                    std::cout << monster.getName() << "は攻撃を回避した!" << std::endl;
                }

                if (!monster.isAlive()) {
                    std::cout << monster.getName() << "を倒した!" << std::endl;
                    player->healToFull();
                    player->gainExperience(100);
                    break;
                }
            }
        }

        //2.カウンター
        else if (choice == 2) {
            if (playerGoesFirst) {  //プレイヤーが先に行動してしまうと失敗し攻撃を受ける
                std::cout << player->getName() << "はカウンターを狙ったが、失敗した!" << std::endl;

                int damage = monster.attack();
                player->takeDamage(monster.attack());
                std::cout << player->getName() << "はダメージを受けた!" << std::endl;
            }

            if (!player->isAlive()) {
                std::cout << player->getName() << "は倒れた!" << std::endl;
                break;
            }

            else {  //敵が先に行動するとカウンター成功
                int damage = monster.attack();
                std::cout << monster.getName() << "の攻撃!" << std::endl;
                std::cout << "カウンター成功! " << monster.getName() << "に" << damage << "ダメージを与えた!" << std::endl;
                monster.takeDamage(damage);

            }
            if (!monster.isAlive()) {
                std::cout << monster.getName() << "を倒した!" << std::endl;
                player->healToFull();
                player->gainExperience(100);
                break;
            }
        }
    }
}