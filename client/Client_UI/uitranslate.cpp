#include "uitranslate.h"

QString getWallName(int wall_id){
    switch (wall_id) {
        case 1:
            return "Fence";
        case 2:
            return "Wood wall";
        case 3:
            return "Stone wall";
        case 4:
            return "Legend wall";
        default:
            return "No wall";
    }
}

QString getWeaponName(int weapon_id){
    switch (weapon_id) {
        case 1:
            return "Ballista";
        case 2:
            return "Catapult";
        case 3:
            return "Cannon!";
        default:
            return "Bare hand";
    }
}

QString getOccupiedText(int occupied_by){
    if ( occupied_by >= 0 && occupied_by < 4 ){
        return "Team " + QString::number(occupied_by+1) + " owned";
    } else {
        return "Unoccupied";
    }
}

QString getMineResourceText(Mine mine){
    return QString::number(mine.wood) + "W " + QString::number(mine.stone) + "S " + QString::number(mine.iron) + "I";
}

QPixmap getWeaponPixMap(int weapon_id){
    QPixmap imageBallista(":/image/ballista.png");
    QPixmap imageCatapult(":/image/catapult.png");
    QPixmap imageCannon(":/image/cannon.png");
    QPixmap imageNothing(":/image/nothing.png");
    switch (weapon_id){
        case 1:
            return imageBallista;
        case 2:
            return imageCatapult;
        case 3:
            return imageCannon;
        default:
            return imageNothing;
    }
}
