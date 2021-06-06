
#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------

  USE p1508726
  
#------------------------------------------------------------
# Table: morpion
#------------------------------------------------------------

CREATE TABLE morpion(
        IDMo  int (11) Auto_increment  NOT NULL ,
        name  Char (25) NOT NULL ,
        icone Varchar (25) NOT NULL ,
        IDCr  Int ,
        PRIMARY KEY (IDMo )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: party
#------------------------------------------------------------

CREATE TABLE party(
        winer     Char (25) ,
        IDPa      int (11) Auto_increment  NOT NULL ,
        IDDa      Int ,
        IDDi      Int ,
        IDEq      Int ,
        IDEq_team Int ,
        PRIMARY KEY (IDPa )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: archery
#------------------------------------------------------------

CREATE TABLE archery(
        IDAr   Int ,
        life   Int ,
        attack Int ,
        mana   Int ,
        IDMo   Int NOT NULL ,
        PRIMARY KEY (IDMo )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: knight
#------------------------------------------------------------

CREATE TABLE knight(
        IDKn   Int ,
        life   Int NOT NULL ,
        mana   Int NOT NULL ,
        attack Int NOT NULL ,
        proba  Int ,
        IDMo   Int NOT NULL ,
        PRIMARY KEY (IDMo )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: sorcerer
#------------------------------------------------------------

CREATE TABLE sorcerer(
        IDSo   Int NOT NULL ,
        life   Int NOT NULL ,
        attack Int NOT NULL ,
        mana   Int NOT NULL ,
        IDMo   Int NOT NULL ,
        PRIMARY KEY (IDMo )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: team
#------------------------------------------------------------

CREATE TABLE team(
        IDEq  int (11) Auto_increment  NOT NULL ,
        name  Char (25) NOT NULL ,
        color Char (25) ,
        IDDa  Int ,
        PRIMARY KEY (IDEq )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: date
#------------------------------------------------------------

CREATE TABLE date(
        IDDa  int (11) Auto_increment  NOT NULL ,
        dates Date ,
        PRIMARY KEY (IDDa )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: dimension
#------------------------------------------------------------

CREATE TABLE dimension(
        X1   Int ,
        Y1   Int ,
        IDDi Int NOT NULL ,
        PRIMARY KEY (IDDi )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: action
#------------------------------------------------------------

CREATE TABLE action(
        IDAc       int (11) Auto_increment  NOT NULL ,
        numeroAc   Int ,
        typeaction Char (25) ,
        IDPa       Int NOT NULL ,
        IDCr       Int ,
        PRIMARY KEY (IDAc )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: coordonnee
#------------------------------------------------------------

CREATE TABLE coordonnee(
        X    Int ,
        Y    Char (25) ,
        IDCr Int NOT NULL ,
        PRIMARY KEY (IDCr )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: jeu
#------------------------------------------------------------

CREATE TABLE jeu(
        verifeq Int NOT NULL ,
        verifjo Int ,
        verifac Int ,
        party   Int NOT NULL ,
        PRIMARY KEY (verifeq )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: matrice
#------------------------------------------------------------

CREATE TABLE matrice(
        IDpos  Int NOT NULL ,
        IDMo   Int ,
        icone  Char (25) ,
        life   Int NOT NULL ,
        attack Int NOT NULL ,
        mana   Int NOT NULL ,
        proba  Int NOT NULL ,
        IDEq   Int NOT NULL ,
        PRIMARY KEY (IDpos )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: sort
#------------------------------------------------------------

CREATE TABLE sort(
        IDSt  int (11) Auto_increment  NOT NULL ,
        cost  Int ,
        name  Char (25) ,
        power Int ,
        PRIMARY KEY (IDSt )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: sauvegarde
#------------------------------------------------------------

CREATE TABLE sauvegarde(
        idsauvegarde Int NOT NULL ,
        IDMo         Int ,
        IDEq         Int ,
        life         Int NOT NULL ,
        mana         Int NOT NULL ,
        attack       Int NOT NULL ,
        proba        Int ,
        PRIMARY KEY (idsauvegarde )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: lance
#------------------------------------------------------------

CREATE TABLE lance(
        IDMo Int NOT NULL ,
        IDSt Int NOT NULL ,
        PRIMARY KEY (IDMo ,IDSt )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: appartienta
#------------------------------------------------------------

CREATE TABLE appartienta(
        IDMo Int NOT NULL ,
        IDEq Int NOT NULL ,
        PRIMARY KEY (IDMo ,IDEq )
)ENGINE=InnoDB;

ALTER TABLE morpion ADD CONSTRAINT FK_morpion_IDCr FOREIGN KEY (IDCr) REFERENCES coordonnee(IDCr);
ALTER TABLE party ADD CONSTRAINT FK_party_IDDa FOREIGN KEY (IDDa) REFERENCES date(IDDa);
ALTER TABLE party ADD CONSTRAINT FK_party_IDDi FOREIGN KEY (IDDi) REFERENCES dimension(IDDi);
ALTER TABLE party ADD CONSTRAINT FK_party_IDEq FOREIGN KEY (IDEq) REFERENCES team(IDEq);
ALTER TABLE party ADD CONSTRAINT FK_party_IDEq_team FOREIGN KEY (IDEq_team) REFERENCES team(IDEq);
ALTER TABLE archery ADD CONSTRAINT FK_archery_IDMo FOREIGN KEY (IDMo) REFERENCES morpion(IDMo);
ALTER TABLE knight ADD CONSTRAINT FK_knight_IDMo FOREIGN KEY (IDMo) REFERENCES morpion(IDMo);
ALTER TABLE sorcerer ADD CONSTRAINT FK_sorcerer_IDMo FOREIGN KEY (IDMo) REFERENCES morpion(IDMo);
ALTER TABLE team ADD CONSTRAINT FK_team_IDDa FOREIGN KEY (IDDa) REFERENCES date(IDDa);
ALTER TABLE action ADD CONSTRAINT FK_action_IDPa FOREIGN KEY (IDPa) REFERENCES party(IDPa);
ALTER TABLE action ADD CONSTRAINT FK_action_IDCr FOREIGN KEY (IDCr) REFERENCES coordonnee(IDCr);
ALTER TABLE lance ADD CONSTRAINT FK_lance_IDMo FOREIGN KEY (IDMo) REFERENCES morpion(IDMo);
ALTER TABLE lance ADD CONSTRAINT FK_lance_IDSt FOREIGN KEY (IDSt) REFERENCES sort(IDSt);
ALTER TABLE appartienta ADD CONSTRAINT FK_appartienta_IDMo FOREIGN KEY (IDMo) REFERENCES morpion(IDMo);
ALTER TABLE appartienta ADD CONSTRAINT FK_appartienta_IDEq FOREIGN KEY (IDEq) REFERENCES team(IDEq);

INSERT INTO coordonnee(X,Y,IDCr) VALUES(0,0,0);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(1,1,1);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(1,2,2);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(1,3,3);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(2,1,4);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(2,2,5);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(2,3,6);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(3,1,7);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(3,2,8);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(3,3,9);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(1,4,10);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(2,4,11);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(3,4,12);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(4,1,13);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(4,2,14);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(4,3,15);
INSERT INTO coordonnee(X,Y,IDCr) VALUES(4,4,16);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (1,"archer","./img/pap_ar.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (2,"archer1","./img/pap_ar.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (3,"archer2","./img/pap_ar.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (4,"archer3","./img/pap_ar.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (5,"archer4","./img/pap_ar.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (6,"sorcier5","./img/pap_sor.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (7,"sorcier6","./img/pap_sor.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (8,"sorcier7","./img/pap_sor.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (9,"sorcier8","./img/pap_sor.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (10,"sorcier9","./img/pap_sor.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (11,"guerrier10","./img/pap_kn.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (12,"guerrier11","./img/pap_kn.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (13,"guerrier12","./img/pap_kn.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (14,"guerrier13","./img/pap_kn.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (15,"guerrier14","./img/pap_kn.jpg",0);
INSERT INTO `morpion`(`IDMo`, `name`, `icone`, `IDCr`) VALUES (16,"guerrier15","./img/pap_kn.jpg",0);
INSERT INTO `archery`( IDAr, `life`, `attack`, `mana`, `IDMo`) VALUES (1,5,5,0,1);
INSERT INTO `archery`( IDAr, `life`, `attack`, `mana`, `IDMo`) VALUES (2,4,6,0,2);
INSERT INTO `archery`( IDAr, `life`, `attack`, `mana`, `IDMo`) VALUES (3,6,4,0,3);
INSERT INTO `archery`( IDAr, `life`, `attack`, `mana`, `IDMo`) VALUES (4,3,7,0,4);
INSERT INTO `archery`( IDAr, `life`, `attack`, `mana`, `IDMo`) VALUES (5,2,8,0,5);
INSERT INTO `sorcerer`( IDSo, `life`, `attack`, `mana`, `IDMo`) VALUES (1,5,1,4,6);
INSERT INTO `sorcerer`( IDSo, `life`, `attack`, `mana`, `IDMo`) VALUES (2,1,1,8,7);
INSERT INTO `sorcerer`( IDSo, `life`, `attack`, `mana`, `IDMo`) VALUES (3,2,3,5,8);
INSERT INTO `sorcerer`( IDSo, `life`, `attack`, `mana`, `IDMo`) VALUES (4,3,1,6,9);
INSERT INTO `sorcerer`( IDSo, `life`, `attack`, `mana`, `IDMo`) VALUES (5,2,2,6,10);
INSERT INTO `knight`( IDKn, `life`, `attack`, `mana`, proba , `IDMo`) VALUES (1,5,5,0,5,11);
INSERT INTO `knight`( IDKn, `life`, `attack`, `mana`, proba , `IDMo`) VALUES (2,4,6,0,5,12);
INSERT INTO `knight`( IDKn, `life`, `attack`, `mana`, proba , `IDMo`) VALUES (3,6,4,0,5,13);
INSERT INTO `knight`( IDKn, `life`, `attack`, `mana`, proba , `IDMo`) VALUES (4,3,7,0,5,14);
INSERT INTO `knight`( IDKn, `life`, `attack`, `mana`, proba , `IDMo`) VALUES (5,2,8,0,5,15);
INSERT INTO `knight`( IDKn, `life`, `attack`, `mana`, proba , `IDMo`) VALUES (6,3,7,0,5,16);
INSERT INTO `jeu`(`verifeq`, `verifjo`, `verifac`,party) VALUES (0,0,3,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (1,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (2,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (3,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (4,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (5,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (6,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (7,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (8,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (9,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (10,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (11,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (12,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (13,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (14,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (15,0,'icone',0,0,0,0,0);
INSERT INTO `matrice`(`IDpos`, `IDMo`, `icone`, `life`, `attack`, `mana`, `proba`, `IDEq`) VALUES (16,0,'icone',0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (1,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (2,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (3,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (4,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (5,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (6,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (7,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (8,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (9,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (10,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (11,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (12,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (13,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (14,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (15,0,0,0,0,0,0);
INSERT INTO `sauvegarde`(`idsauvegarde`, `IDMo`, `IDEq`, `life`, `mana`, `attack`, `proba`) VALUES (16,0,0,0,0,0,0);
INSERT INTO `dimension`(`X1`, `Y1`, `IDDi`) VALUES (3,3,1);
INSERT INTO `dimension`(`X1`, `Y1`, `IDDi`) VALUES (4,4,2);
INSERT INTO `sort`(`IDSt`, `cost`, `name`, `power`) VALUES (1,2,'boule de feu',4);
INSERT INTO `sort`(`IDSt`, `cost`, `name`, `power`) VALUES (2,1,'soin',3);
INSERT INTO `sort`(`IDSt`, `cost`, `name`, `power`) VALUES (3,5,'armageddon',0);
