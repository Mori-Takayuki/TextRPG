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
    std::cout << "�v���C���[������͂��Ă�������: ";
    std::cin >> playerName;
    std::cout << "�E�Ƃ�I��ł�������:\n";
    std::cout << "1. �E�� (�̗�: 40, �U����: 5-8, ���: 20%)\n";
    std::cout << "2. ��m (�̗�: 50, �U����: 3-10, ���: 5%)\n";
    std::cout << "3. ������ (�̗�: 30, �U����: 4-8, ���: 30%)\n";
    std::cin >> jobChoice;
    std::cout << std::endl;
    switch (jobChoice) {
    case 1:
        player = new Player(playerName, "�E��");
        std::cout << "�E�҂��I������܂���!�`���̎n�܂�ł�!" << std::endl;
        break;
    case 2:
        player = new Player(playerName, "��m");
        std::cout << "��m���I������܂���!�`���̎n�܂�ł�!" << std::endl;
        break;
    case 3:
        player = new Player(playerName, "������");
        std::cout << "�����Ƃ��I������܂���!�`���̎n�܂�ł�!" << std::endl;
        break;
    default:
        std::cout << "�����ȑI���̂��ߗE�҂ɐݒ肳��܂����B�`���̎n�܂�ł�!\n";
        player = new Player(playerName, "�E��");
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
        std::cout << "�Q�[���N���A�I���߂łƂ��I" << std::endl;
    }
    else {
        std::cout << "�Q�[���I�[�o�[!" << std::endl;
    }

    delete player;
}


Monster Game::createNextMonster(int index) {
    switch (index) {
    case 0:
        return Monster("�X���C��", 20, 3, 5, 0.05, "����������");    //("�G��",�̗�,�ŏ��E�ő�U����,���,"�Z��")
    case 1:
        return Monster("�S�u����", 30, 5, 7, 0.10, "�S�u�����p���`");
    case 2:
        return Monster("�S�[����", 60, 7, 10, 0.00, "��΂��Ƃ�");
    case 3:
        return Monster("�����܂̂���", 50, 7, 10, 0.30, "�Ȃ��͂炢");
    case 4:
        return Monster("�܂���", 100, 10, 15, 0.30, "�����̂͂ǂ�");
    default:
        return Monster("Unknown", 0, 0, 0, 0.0, "Unknown");
    }
}

void Game::battle(Monster& monster) {
    std::cout << monster.getName() << "�������ꂽ!" << std::endl;

    while (player->isAlive() && monster.isAlive()) {
        std::cout << "�v���C���[�c��̗�: " << player->getHealth() << "/" << player->getMaxHealth() << " | ";
        std::cout << monster.getName() << " �c��̗�: " << monster.getHealth() << std::endl;

        std::cout << "�s����I��ŉ�����: 1. �U��  2. �J�E���^�[(�G����ɍs������Ɛ���)" << std::endl;
        int choice;
        std::cin >> choice;

        bool playerGoesFirst = rand() % 2 == 0;

        //1.�U��
        if (choice == 1) {
            if (playerGoesFirst) {
                int damage = player->attack();
                if (!monster.dodge()) {
                    monster.takeDamage(damage);
                    std::cout << player->getName() << "��" << monster.getName() << "�ɍU�����A" << damage << "�_���[�W��^����!" << std::endl;
                }
                else {
                    std::cout << player->getName() << monster.getSkillName() << "�̍U��!" << std::endl;
                    std::cout << monster.getName() << "�͍U�����������!" << std::endl;
                }

                if (!monster.isAlive()) {
                    std::cout << monster.getName() << "��|����!" << std::endl;
                    player->healToFull();
                    player->gainExperience(100); //100XP���l��
                    break;
                }

                damage = monster.attack();
                if (!player->dodge()) {
                    player->takeDamage(damage);
                    std::cout << monster.getName() << "��" << player->getName() << "�ɍU�����A" << damage << "�_���[�W��^����!" << std::endl;
                }
                else {
                    std::cout << monster.getName() << "�̍U��!" << std::endl;
                    std::cout << player->getName() << "�͍U�����������!" << std::endl;
                }
            }
            else {
                int damage = monster.attack();
                if (!player->dodge()) {
                    player->takeDamage(damage);
                    std::cout << monster.getName() << "��" << player->getName() << "�ɍU�����A" << damage << "�_���[�W��^����!" << std::endl;
                }

                if (!player->isAlive()) {
                    std::cout << player->getName() << "�͓|�ꂽ!" << std::endl;
                    break;
                }

                else {
                    std::cout << monster.getName() << "�̍U��!" << std::endl;
                    std::cout << player->getName() << "�͍U�����������!" << std::endl;
                }

                if (!player->isAlive()) {
                    std::cout << player->getName() << "�͓|�ꂽ!" << std::endl;
                    break;
                }

                damage = player->attack();
                if (!monster.dodge()) {
                    monster.takeDamage(damage);
                    std::cout << player->getName() << "��" << monster.getName() << "�ɍU�����A" << damage << "�_���[�W��^����!" << std::endl;
                }
                else {
                    std::cout << player->getName() << "�̍U��!" << std::endl;
                    std::cout << monster.getName() << "�͍U�����������!" << std::endl;
                }

                if (!monster.isAlive()) {
                    std::cout << monster.getName() << "��|����!" << std::endl;
                    player->healToFull();
                    player->gainExperience(100);
                    break;
                }
            }
        }

        //2.�J�E���^�[
        else if (choice == 2) {
            if (playerGoesFirst) {  //�v���C���[����ɍs�����Ă��܂��Ǝ��s���U�����󂯂�
                std::cout << player->getName() << "�̓J�E���^�[��_�������A���s����!" << std::endl;

                int damage = monster.attack();
                player->takeDamage(monster.attack());
                std::cout << player->getName() << "�̓_���[�W���󂯂�!" << std::endl;
            }

            if (!player->isAlive()) {
                std::cout << player->getName() << "�͓|�ꂽ!" << std::endl;
                break;
            }

            else {  //�G����ɍs������ƃJ�E���^�[����
                int damage = monster.attack();
                std::cout << monster.getName() << "�̍U��!" << std::endl;
                std::cout << "�J�E���^�[����! " << monster.getName() << "��" << damage << "�_���[�W��^����!" << std::endl;
                monster.takeDamage(damage);

            }
            if (!monster.isAlive()) {
                std::cout << monster.getName() << "��|����!" << std::endl;
                player->healToFull();
                player->gainExperience(100);
                break;
            }
        }
    }
}