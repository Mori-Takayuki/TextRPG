#include "utilities.h"


Monster createNextMonster(int index) {
    switch (index) {
    case 0:
        return Monster("�X���C��", 20, 3, 5, 0.05, "����������");//("�G��",�̗�,�ŏ��E�ő�U����,���,"�Z��")
    case 1:
        return Monster("�S�u����", 30, 5, 7, 0.10, "�S�u�����p���`");
    case 2:
        return Monster("�S�[����", 60, 7, 10, 0.00, "��΂��Ƃ�");
    case 3:
        return Monster("�����܂̂���", 50, 7, 10, 0.30, "�Ȃ��͂炢");
    case 4:
        return Monster("����", 100, 10, 15, 0.30, "�����̂͂ǂ�");
    default:
        return Monster("Unknown", 0, 0, 0, 0.0, "Unknown");
    }
}

