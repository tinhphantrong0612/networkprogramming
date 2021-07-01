networkprogramming
GUI client using Qt C++ framework

After tested, there are bugs remain:

1. handleAttackCastle: when answer right without take over the castle, send incorrect 'team' index 
   Cause by: informCastleAttack: 'team' got from using request player's team index