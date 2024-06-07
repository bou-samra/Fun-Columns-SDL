REL
* Fun Columns
* par O.Goguel et FTA

* ToolBox Mag No 4
* Copyright 1990/1991 FTA
* Copyright 1990/1991 Toolbox
* 6 Rue H. Barbusse - 95100 Argenteuil - France

* Création     : 22 Décembre 1990
* Dernière MAJ : 03 Février 1991

* Assemblage sous Merlin 16+ uniquement

* !vP8 !vP16!
* ! 1  !  x ! ...... Version SYS Prodos8 (OA-A)
* ! 0  !  1 ! ...... Version S16 Gs/Os   (OA-6)
* ! 0  !  0 ! ...... Version CDA Gs/Os   (OA-6)

* Language : 0=Francais, 1=English

vP8              =     0
vP16             =     1
Language         =     0

                 LST   OFF

* Le source est peu commenté car la gestion d'un jeu de
* ce genre est relativement simple et ne pose aucun probleme
* de programmation...

* Seul quelques _bidouilles_ en GS/OS et PRODOS sont expliqués...
* sinon, juste les noms des grandes parties sont données...


*------------------------------------------------- Macros

TXT              MAC
                 DO    Language
                 ASC   ]1
                 ELSE
                 ASC   ]2
                 FIN
                 EOM

INK              MAC
                 INC   ]1
                 BNE   Here
                 INC   ]1+1
Here             EOM


_Err             MAC
                 BCC   NoErr
                 BRL   PgmDeath
NoErr            EOM

STL              MAC
                 DO    vP8
                 STA   ]1
                 ELSE
                 STAL  ]1
                 FIN
                 EOM

LDL              MAC
                 DO    vP8
                 LDA   ]1
                 ELSE
                 LDAL  ]1
                 FIN
                 EOM

BEQL             MAC
                 BNE   Here
                 BRL   ]1
Here             EOM

BNEL             MAC
                 BEQ   Here
                 BRL   ]1
Here             EOM

*------------------------------------------------- Constantes & Adresses

Screen           =     $E12000
ZPage            =     $1F00

NbLgn            =     18                                      ; Nb de block par Ligne
NbCol            =     8                                       ; Nb de Block par Colonne
HautCase         =     11                                      ; Taille Blocks
LargCase         =     12                                      ;    "      "
Center           =     $38+$A0



*------------------------------------------------- Entetes


* Entete Prodos8
*----------------
                 DO    vP8
                 ORG   $2000
BeginningOfFile  =     *
                 TYP   $FF                                     ; Fichier SYS
                 XC
                 XC
                 ELSE
BeginningOfFile  =     *

* Entete P16
*-----------
*                 REL
                 DO    vP16
                 DSK   Beyond.SYS16.L
                 ELSE

* Entete CDA
*-----------
                 TYP   CDA
                 DSK   Beyond.CDA.L
                 DO    Language
                 STR   'Fun Columns by FTA'
                 ELSE
                 STR   'Fun Columns par FTA'
                 FIN
                 ADRL  START
                 ADRL  ENDCDA
                 FIN
                 FIN

*------------------------------------------------- Page Zero

                 DUM   $00
CaseList         DS    NbCol*2
Table            DS    NbLgn*NbCol
Pnt              DS    4
Lgn              DS    2
Col              DS    2
ZNbLgn           DS    2
ZNbCol           DS    2
Barre            DS    3
BarreCol         DS    2
BarreLgn         DS    2
BarrePos         DS    2
AleaGen          DS    2
LevelSpeed       DS    2
Compteur         DS    2
Col0             DS    2
Lgn0             DS    2
Flag             DS    2
CaseTest         DS    2
Buf              DS    2
Msk              DS    2
Msk0             DS    2
Score            DS    4
Total            DS    2
Level            DS    2
Level0           DS    2
Inv              DS    2
CycleCount       DS    2
SaveScreen       DS    4
FlagHi           DS    2
Counter          DS    2
PntPath          DS    4
PtrMsk           DS    2
Step             DS    2
PtrPattern       DS    2
PtrPatPos        DS    2
PtrPtrMsk        DS    2
BarreCol0        DS    2
PtrShp           DS    2
BarreNext        DS    3
BlackMode        DS    2
AlreadyNext      DS    2
ColorDeg         DS    2
XColor           DS    2
PatchActif       DS    2
NextMode         DS    2
                 DEND

*------------------------------------------------- Debut

START            DO    vP8
                 ELSE
                 DO    vP16
                 ELSE
                 PHP                                           ; Initialisation
                 PHD                                           ; version CDA uniquement
                 PHB
                 SEI
                 FIN
                 FIN

                 PHK
                 PLB

* Effacement écran text

                 SEP   $30
]lp              LDL   $E1C02E
                 CMP   #$F0
                 BNE   ]lp

                 LDX   #0
                 LDA   #" "
]lp              STL   $000400,X
                 STL   $000480,X
                 STL   $000500,X
                 STL   $000580,X
                 STL   $000600,X
                 STL   $000680,X
                 STL   $000700,X
                 STL   $000780,X
                 STAL  $010400,X
                 STAL  $010480,X
                 STAL  $010500,X
                 STAL  $010580,X
                 STAL  $010600,X
                 STAL  $010680,X
                 STAL  $010700,X
                 STAL  $010780,X

                 INX
                 CPX   #$78
                 BNE   ]lp

* Sauvegarde et mise @ jour du contexte video

                 LDL   $E1C036
                 ORA   #$80
                 STL   $E1C036
                 LDL   $E1C029
                 STA   Save29+1
                 ORA   #$40
                 STL   $E1C029
                 LDL   $E1C035
                 STA   Save35+1
                 LDL   $E1C034
                 STA   Save34+1
                 LDA   #$1E
                 STL   $E1C035

                 DO    vP8

*------------------------------------------------- Initialisation P8

* Recherche du pathname complet sous lequel
* a été lancé BEYOND depuis P8...

* Il n'existe en théorie aucun moyen de savoir le nom de
* l'application en cours sous P8 (contrairement a GS/OS)
* mais on peut facilement _en bidouillant un peu_ le
* recuperer...

* Cette routine utilise des points d'entrées Prodos non
* garanti par Apple, mais marche avec toutes les versions
* de P8 existantes...


* Tout d'abord on prend le prefix courant...

                 JSR   $BF00
                 DFB   $C7                                     ; GetPrefix
                 DA    PrefixParm

* Puis, on va trouver en $D700 banc 0 de la carte langage
* une suite de nom de fichiers au format Prodos qui constitue le pathname
* que l'on cherche... Il suffit donc de les ajouter les uns a la suite des
* autres au prefix initial (s'il existe)

                 LDA   $C068
                 PHA
                 LDA   $C08B
                 LDA   $C08B

                 LDA   PathName
                 BNE   AlreadyPath

                 LDA   #'/'
                 STA   PathName+1
                 LDA   #1
AlreadyPath      INC
                 STA   $02
                 TAX
                 STZ   $00
                 LDA   #$D7
                 STA   $01
]lp2             LDA   ($00)
                 BEQ   EndPath
                 TAY
]lp              INK   $00
                 LDA   ($00)
                 STA   PathName,X
                 INX
                 DEY
                 BNE   ]lp
                 INK   $00
                 LDA   ($00)
                 BEQ   EndPath
                 LDA   #'/'
                 STA   PathName,X
                 INX
                 BRA   ]lp2

EndPath          DEX
                 STX   PathName

* Seule petite difficulté : les noms que l'on vient de trouver contenaient
* peut-etre une partie du prefix courant... Si c'est le cas, il faut
* épurer le pathname que l'on vient de creer...

                 LDX   $02
                 CPX   #2
                 BEQ   NoDoublePath

                 LDY   #2
]lp              LDA   PathName,Y
                 CMP   PathName,X
                 BNE   NoDoublePath
                 INX
                 INY
                 CPY   $02
                 BNE   ]lp

                 LDY   #2
                 LDX   $02
]lp              LDA   PathName,X
                 STA   PathName,Y
                 CPX   PathName
                 BEQ   NewLgth
                 INX
                 INY
                 BRA   ]lp
NewLgth          LDA   PathName
                 SEC
                 SBC   $02
                 INC
                 INC
                 STA   PathName

NoDoublePath     PLA                                           ; On deconnecte
                 STA   $C068
; la carte langage

* On a donc finalement @ l'adresse Pathname le nom complet de l'application
* P8 en cours...

                 CLC
                 XCE
                 REP   $30
                 LDA   #ZPage                                  ; Page zero fixe
                 TCD                                           ; pour P8
                 LDX   #$100-2
]lp              STZ   $00,X
                 DEX
                 DEX
                 BPL   ]lp

                 ELSE

*------------------------------------------------- Initialisation GS/OS et CDA

                 CLC
                 XCE
                 REP   $30
                 PEA   $0000
                 LDX   #$0202                                  ; MMStartup
                 JSL   $E10000
                 _Err
                 PLA
                 STA   MasterId
                 ORA   #$0100
                 STA   UserId                                  ; Recuperation de l'Id
; de l'application

                 PEA   $0000
                 PEA   $0000
                 PEA   $0000
                 PEA   $0100
                 LDA   UserId
                 PHA
                 PEA   $C001
                 PEA   $0000
                 PEA   $0000
                 LDX   #$0902                                  ; New Handle
                 JSL   $E10000
                 _Err
                 PLA
                 PLA
                 TSC
                 SEC
                 SBC   #4
                 TCS
                 INC
                 TCD
                 LDA   [$00]
                 TAX
                 TSC
                 CLC
                 ADC   #4
                 TCS
                 TXA
                 TCD                                           ; Recuperation d'une
; page zero grace a NewHandle

                 LDX   #$100-2
]lp              STZ   $00,X
                 DEX
                 DEX
                 BPL   ]lp


* Attention !!!
* -------------

* Dans toute la suite du programme, on va _comme d'habitude_ tout
* gérer par nous meme...(affichage, erreurs fichiers...)

* Malheureusement, on va etre légerement géné par GS/OS qui a la
* possibilité d'afficher des fenetres de dialogues (textes ou graphiques)
* pour nous avertir l'apparition d'erreurs eventuelles...

* Theoriquement, l'appel SetSysPref permet de dire a GS/OS de ne pas
* s'occuper de la gestion des erreurs...

                 JSL   $E100A8
                 DA    $200F                                   ; GetSysPref
                 ADRL  SysDefaultParms

                 JSL   $E100A8
                 DA    $200C                                   ; SetSysPref
                 ADRL  SysParms

* Malheureusement, dans certains cas, GS/OS va -malgré les préférences
* demandées- afficher certaines fenetres d'erreurs ce qui va etre fatal
* @ notre application et au systeme qui ne sont pas prévus pour cohabiter
* hors des limites qui ont été définies par votre serviteur...

* On va donc patcher GS/OS, puisque l'on ne recule devant rien, et
* qu'aucun appel homologué ne permet de le faire...
* On ne va tout de meme pas se laisser dominer par un systeme d'exploitation
* quelconque...

* Pour cela, j'ai "examiné" une partie de GS/OS pour remonter jusqu'@
* la routine qui m'interesse et qui se trouve point{ par un vecteur _dont
* son adresse, bien que non déclarée me parait inamovible..._ en $01FC98

* Si on suit ce qui est pointé par ce vecteur, on trouve un bout de routine
* qui commence par :
*
*              LSR
*              BCS  AfficherFenetre
*              LDAL $00B9F6            ; Test des préférences
*              BMI  AfficherFenetre    ; (Bit15=Affichage)
*              ...
*              RTL
* Aff_Fenetre  ...

* Et on voit donc bien le BCS qui peut forcer l'affichage d'une fenetre
* malgré l'état du flag Préference...

* On va donc détourner le vecteur en $01FC98 vers une routine qui remet
* l'accumulateur @ 00 pour que le BCS ne soit jamais pris, et ainsi
* on n'aura jamais de fenetres indésirable @ l'écran...

* A noter que l'on envelera notre patch au moment de quitter, bien entendu...
* et que notre application gere quand meme les erreurs meme si GS/OS n'affiche
* pas de message... (en particulier, le message Inserez le disk XXX)


                 SEP   $20
                 LDAL  $E1C068
                 PHA
                 LDAL  $E1C08B
                 LDAL  $E1C08B

                 REP   $30

                 LDAL  $01FC98                                 ; On verifie que c'est
                 AND   #$00FF                                  ; bien un vecteur...
                 CMP   #$5C
                 BNE   NoPatch

                 LDAL  $01FC99                                 ; Sauvegarde de
                 STA   SaveVect+1                              ; la valeur du vecteur
                 LDAL  $01FC9A
                 STA   SaveVect+2

                 LDA   NewVect+1                               ; et detournement
                 STAL  $01FC99                                 ; vers notre routine
                 LDA   NewVect+2
                 STAL  $01FC9A

NoPatch          SEP   $20
                 PLA
                 STAL  $E1C068
                 REP   $30

                 BRA   Continue_Init

*-------------------------------------------------

SysDefaultParms  DA    1                                       ; Sauvegardes des
                 DA    0                                       ; preferences

SysParms         DA    1
                 DA    0                                       ; don't draw dialog box


NewVect          JML   NewFC98                                 ; nouvelle valeur FC98

NewFC98          LDA   #0
SaveVect         JML   $000000                                 ; Ancienne valeur FC98


*------------------------------------------------- Initialisation CDA

Continue_Init    DO    vP16
                 ELSE

* Demande de 32ko pour sauvegarder la page graphique en cours...

                 PHA
                 PHA
                 PEA   $0
                 PEA   $8000                                   ; 32Ko
                 LDA   UserId
                 PHA
                 PEA   $C000
                 PEA   $0
                 PEA   $0
                 LDX   #$0902                                  ; NewHandle
                 JSL   $E10000
                 _Err
                 PLA
                 STA   SaveScreen
                 PLA
                 STA   SaveScreen+2

                 LDY   #2
                 LDA   [SaveScreen],Y
                 TAX
                 LDA   [SaveScreen]
                 STA   SaveScreen
                 STX   SaveScreen+2

* Copie de la page graphique actuelle dans le buffer récupéré...

                 LDX   #0
]lp              TXY
                 LDAL  $E12000,X
                 STA   [SaveScreen],Y
                 INX
                 INX
                 BPL   ]lp

                 FIN
                 FIN

*------------------------------------------------- Creation de l'image de jeu

                 LDX   #0
                 TXA
]lp              STAL  Screen,X
                 INX
                 INX
                 BPL   ]lp

                 LDX   #$20-2
]lp              LDA   Palette,X
]A               =     0
                 LUP   16
                 STAL  ]A+Screen+$7E00,X
]A               =     ]A+$20
                 --^
                 DEX
                 DEX
                 BPL   ]lp

                 JSR   Degrade
                 BRA   ContDeg

ListDegrade      DA    $00C,0-$001
                 DA    $0C0,0-$010
                 DA    $C00,0-$100
                 DA    $CC0,0-$110
                 DA    $C0C,0-$101
                 DA    $0CC,0-$011
                 DA    $CCC,0-$111
                 DA    $001,$001
                 DA    $010,$010
                 DA    $100,$100
                 DA    $110,$110
                 DA    $101,$101
                 DA    $011,$011
                 DA    $111,$111

Degrade          LDA   ColorDeg                                ; Dégradé pour le décor
                 CLC
                 ADC   XColor
                 ASL
                 ASL
                 TAX
                 LDA   ListDegrade+2,X
                 STA   Step
                 LDA   ListDegrade,X
                 LDX   #0
]lp              STAL  Screen+$7E02,X
                 PHA
                 TXA
                 CLC
                 ADC   #$20
                 TAX
                 PLA
                 CLC
                 ADC   Step
                 CPX   #$20*10
                 BNE   ]lp
                 RTS

ContDeg          SEP   $30

                 LDX   #0
                 LDA   #0
]lp2             LDY   #20
]lp              STAL  Screen+$7D00,X
                 INX
                 DEY
                 BNE   ]lp
                 INC
                 CMP   #10
                 BNE   ]lp2

                 REP   $30

* Decor
                 LDA   #$00A0
                 STA   Buf

                 LDX   #0
]mainloop        PHX
                 LDY   #0
]lp              LDA   ZTop,Y
                 STAL  Screen,X
                 LDA   ZTop0,Y
                 STAL  Screen+$A0,X
                 LDA   ZBottom0,Y
                 STAL  $A0*18+Screen,X
                 LDA   ZBottom,Y
                 STAL  $A0*19+Screen,X
                 INX
                 INX
                 INY
                 INY
                 CPY   #$0A
                 BNE   ]lp

                 LDY   #0
]lp2             PHY
                 TXA
                 CLC
                 ADC   #$A0-$0A
                 TAX
                 LDY   #0
]lp              LDA   ZMiddle,Y
                 STAL  Screen+$A0,X
                 INX
                 INX
                 INY
                 INY
                 CPY   #$0A
                 BNE   ]lp
                 PLY
                 INY
                 CPY   #16
                 BNE   ]lp2
                 PLA
                 CLC
                 ADC   #$0A
                 TAX
                 CMP   Buf
                 BNE   ]mainloop
                 LDA   Buf
                 CLC
                 ADC   #20*$A0
                 STA   Buf
                 CMP   #$7D00
                 BCS   Endraw
                 TXA
                 CLC
                 ADC   #20*$A0-$A0
                 TAX
                 BRA   ]mainloop

Endraw           SEP   $20

                 LDX   #1
                 LDA   #$FF
]lp              STAL  Screen+Center-1-$A0,X
                 STAL  NbLgn*$A0*HautCase+Center-1+Screen,X
                 INX
                 CPX   #NbCol*LargCase/2+1
                 BNE   ]lp

                 LDX   #0
]lp              LDA   #$0F
                 STAL  Screen+Center-1-$A0,X
                 LDA   #$F0
                 STAL  NbCol*LargCase/2+Screen+Center-$A0,X
                 REP   $20
                 TXA
                 CLC
                 ADC   #$A0
                 TAX
                 SEP   $20
                 CPX   #NbLgn*HautCase+2*$A0
                 BNE   ]lp

                 REP   $30

                 LDA   #BeyondLogo+4
                 STA   Pnt

                 LDX   #$88*$A0+$73

]lp2             PHX

                 LDY   #$28/2
]lp              LDA   (Pnt)
                 INC   Pnt
                 INC   Pnt
                 STAL  $E12000,X
                 INX
                 INX
                 DEY
                 BNE   ]lp
                 PLA
                 CLC
                 ADC   #$A0
                 TAX
                 CPX   #$88+$38*$A0+$73
                 BNE   ]lp2

                 STZ   BlackMode
                 STA   Inv

                 LDA   #6
                 STA   Lgn
                 LDA   #115
                 STA   Col
                 LDA   #67
                 STA   ZNbLgn
                 LDA   #38
                 STA   ZNbCol
                 JSR   Window

                 LDX   #11*$A0+120
                 JSR   Print
                 HEX   0CFF                                    ; Couleur noir
                 ASC   "SCORE:",00
                 LDX   #11+20*$A0+120
                 JSR   Print
                 TXT   "LEVEL:",00;"TABLEAU:",00
                 LDX   #11+40*$A0+120
                 JSR   Print
                 ASC   "TOTAL:",00

                 LDA   #6
                 STA   Lgn
                 LDA   #6
                 STA   Col
                 LDA   #187
                 STA   ZNbLgn
                 LDA   #38
                 STA   ZNbCol
                 JSR   Window

                 LDX   #11*$A0+11
                 JSR   Print
                 TXT   "HIGH";"LES"
                 HEX   8D
                 TXT   "SCORES:";"BALAISES"
                 HEX   00

                 STZ   Score
                 STZ   Score+2
                 LDA   #$0001
                 STA   Level
                 STZ   Total

                 LDA   PatternList
                 STA   PtrPattern
                 LDA   MskList
                 STA   PtrPtrMsk

                 LDA   #2
                 STA   PtrPatPos

                 JSR   PrintHiScore
                 JSR   PrintScore
                 JSR   PrintTotal
                 JSR   PrintLevel

*------------------------------------------------- Fin de l'initialisation

]RestartGame     JSR   ClearAera

                 SEP   $30
                 LDL   $E1C02F
                 STA   AleaGen

]lp              LDL   $E1C02E
                 CMP   #$F0
                 BNE   ]lp

                 LDA   #0
                 STL   $E1C034
                 LDA   #$C1
                 STL   $E1C029

                 REP   $30

* Affichage du menu...

                 STZ   Inv
                 LDX   #52*$A0+$37+4
                 JSR   Print
                 HEX   0C99
                 TXT   "CHOOSE :";"CHOISIR:"
                 HEX   8D8D
                 ASC   "1",0CFF,"-"
                 TXT   "VERY EASY";"ENFANTIN"
                 HEX   8D0C99
                 ASC   "2",0CFF,"-"
                 TXT   "EASY";"FACILE"
                 HEX   8D0C99
                 ASC   "3",0CFF,"-"
                 TXT   "MEDIUM";"MOYEN"
                 HEX   8D0C99
                 ASC   "4",0CFF,"-"
                 TXT   "HARD";"DIFFICILE"
                 HEX   8D0C99
                 ASC   "5",0CFF,"-"
                 TXT   "VERY HARD";"AIE !"
                 HEX   8D0C99
                 ASC   "6",0CFF,"-"
                 TXT   "JEDI";"MODE JYB"
                 HEX   8D8D0C99
                 ASC   "A",0CFF,"-"
                 TXT   "ABOUT";"A PROPOS"
                 HEX   8D0C99
                 ASC   "I",0CFF,"-INFO",8D0C99
                 ASC   "Q",0CFF,"-"
                 TXT   "QUIT";"QUITTER"
                 HEX   0CFF00

                 LDA   #$FFFF
                 STA   Inv

* Saisie du choix au clavier...

WaitKeyPress     SEP   $30
                 STL   $E1C010
]lp              LDL   $E1C000
                 BPL   ]lp
                 STL   $E1C010
                 REP   $30
                 AND   #$00FF
                 CMP   #"Z"+1
                 BCC   NoMin
                 SEC
                 SBC   #$20
NoMin            CMP   #"Q"
                 BNEL  NoQuit

* Si on appuie sur Q, on va sauver les high-scores s'ils ont étés
* améliorés (FlagHi)

                 LDA   FlagHi
                 BEQ   NoSaveHi

                 JSR   PrintSaving

* Les meilleurs scores sont sauvés directement dans le programme !

*------------------------------------------------- Routine sauvegarde P8

NoSaveHi         DO    vP8                                     ; *D0

                 PEA   $0
                 PLD
                 SEC
                 XCE
                 SEP   $30

                 LDA   FlagHi+ZPage
                 BEQ   NoSaveHiP8

                 STZ   FlagClean

]lp              JSR   $BF00
                 DFB   $C8                                     ; Open
                 DA    OpenParm
                 BCC   NoErrOpening
                 CMP   #$45                                    ; Volume Not Found
                 BNE   ErrFatal
                 JSR   InsertDisk
                 BCC   ]lp
                 BRA   NoSaveHiP8

NoErrOpening     LDA   FlagClean
                 BEQ   NoRedraw0

                 JSR   PrintSaving

NoRedraw0        LDA   Ref
                 STA   RefRead
                 STA   RefWrite
                 STA   RefMark
                 JSR   $BF00
                 DFB   $CE                                     ; SetMark
                 DA    MarkParm
                 BCC   NoErrMark
                 BRA   ErrFatal
ErrFatal0        LDA   #$FF                                    ; Bad Signature
ErrFatal         JSR   FatalError
                 BRA   NoSaveHiP8
NoErrMark        JSR   $BF00
                 DFB   $CA                                     ; Read
                 DA    ReadParm
                 BCS   ErrFatal
                 LDX   #7
]lp              LDA   Signature,X
                 CMP   SignatureTest,X
                 BNE   ErrFatal0
                 DEX
                 BPL   ]lp
GoodTest         JSR   $BF00
                 DFB   $CB
                 DA    WriteParm
                 BCC   NoSaveHiP8
                 CMP   #$2F
                 BEQ   DiskSwap
                 CMP   #$2B
                 BNE   ErrFatal
                 JSR   WriteProtect
                 BCC   GoodTest
                 BRA   NoSaveHiP8
DiskSwap         JSR   InsertDisk
                 BCC   GoodTest
NoSaveHiP8       JSR   $BF00
                 DFB   $CC
                 DA    CloseParm

Save35           LDA   #0
                 STL   $E1C035
Save29           LDA   #$41
                 STL   $E1C029
Save34           LDA   #0
                 STL   $E1C034

                 JSR   $BF00
                 DFB   $65
                 DA    QuitParm

PrintSaving      CLC
                 XCE
                 PHP
                 PHD
                 REP   $30
                 LDA   #ZPage
                 TCD
                 JSR   ClearAera
                 STZ   Inv
                 LDX   #91*$A0+$37+4
                 JSR   Print
                 HEX   0C99
                 TXT   "  SAVING";"SAUVEGARDE"
                 HEX   8D
                 TXT   "HIGH SCORES";"DES SCORES."
                 HEX   00
                 PLD
                 PLP
                 XCE
                 RTS

                 MX    %11
WriteProtect     CLC
                 XCE
                 REP   $30
                 LDA   #ZPage
                 TCD
                 JSR   ClearAera
                 LDX   #67*$A0+$36+4
                 JSR   Print
                 HEX   0CFF
                 TXT   "DISK WRITE";"DISQUETTE"
                 HEX   8D
                 TXT   "PROTECTED.";"PROTEGEE."
                 HEX   0CAA00

                 BRA   ContErr

                 MX    %11
InsertDisk       LDX   #0
]lp              LDA   PathName+2,X
                 ORA   #$80
                 CMP   #"/"
                 BEQ   EndPath0
                 STA   Name+1,X
                 INX
                 CPX   #11
                 BNE   ]lp
EndPath0         CPX   #11
                 BEQ   NoBlank
                 LDA   #" "
                 STA   Name+1,X
                 INX
                 BRA   EndPath0

NoBlank          CLC
                 XCE
                 REP   $30
                 LDA   #ZPage
                 TCD
                 JSR   ClearAera
                 LDX   #67*$A0+$36+2
                 JSR   Print
                 HEX   0CFF
                 TXT   "INSERT DISK:";"INSEREZ:"
                 HEX   8D
Name             ASC   "/           ",0CAA00

ContErr          DO    Language
                 LDX   #8*3+67*$A0+$36+2
                 JSR   Print
                 ASC   "PRESS RETURN",8D
                 ASC   "   TO RETRY ",8E
                 ASC   "     OR",8E
                 ASC   "PRESS ESC",8D
                 ASC   "   TO ABORT",00
                 ELSE
                 LDX   #8*3+67*$A0+$36+5
                 JSR   Print
                 ASC   "TAPEZ ENVOI",8D
                 ASC   "   POUR    ",8D
                 ASC   "RE-ESSAYER.",8E
                 ASC   "    OU",8E
                 ASC   " TAPEZ ESC",8D
                 ASC   "   POUR",8D
                 ASC   "ABANDONNER."
                 HEX   00
                 FIN

                 SEP   $30
]lp              LDL   $E1C025
                 BIT   #%0000_1000
                 BNE   ]lp
]lp2             STL   $E1C010
]lp              LDL   $E1C000
                 BPL   ]lp
                 STL   $E1C010
                 CMP   #"M"&$9F
                 BEQ   GoRetry
                 CMP   #$9B
                 BNE   ]lp2
                 SEC
                 XCE
                 PEA   $0
                 PLD
                 SEC
                 RTS
GoRetry          INC   FlagClean
                 SEC
                 XCE
                 PEA   $0
                 PLD
                 CLC
                 RTS

FlagClean        DS    2

FatalError       PHA
                 AND   #$F0
                 LSR
                 LSR
                 LSR
                 LSR
                 JSR   Translate
                 STA   ErrCode
                 PLA
                 AND   #$0F
                 JSR   Translate
                 STA   ErrCode+1
                 CLC
                 XCE
                 REP   $30
                 LDA   #ZPage
                 TCD
                 JSR   ClearAera
                 LDX   #91*$A0+$37+4
                 JSR   Print
                 HEX   0C99
                 TXT   "CAN'T SAVE";"SAUVEGARDE"
                 HEX   8D
                 TXT   "HI-SCORES :";"IMPOSSIBLE"
                 HEX   8D8D
                 TXT   " ERROR $";"ERREUR $"
ErrCode          ASC   "??",00

                 SEC
                 XCE
                 SEP   $30
                 PEA   $0
                 PLD
]lp              LDL   $E1C025
                 BIT   #%0000_1000
                 BNE   ]lp
                 STL   $E1C010
]lp              LDL   $E1C000
                 BPL   ]lp
                 STL   $E1C010
                 CLC
                 RTS


QuitParm         HEX   04
                 HEX   00
                 HEX   0000
                 HEX   00
                 HEX   0000

CloseParm        HEX   01
                 HEX   00

WriteParm        HEX   04
RefWrite         HEX   00
                 DA    HiScoreList
                 DA    12*8
                 DA    0

ReadParm         HEX   04
RefRead          HEX   00
                 DA    SignatureTest
                 DA    8
                 DA    0

MarkParm         HEX   02
RefMark          HEX   00
                 ADRL  Signature-BeginningOfFile

PrefixParm       HEX   01
                 DA    PathName

OpenParm         HEX   03
                 DA    PathName
                 DA    BufIO
Ref              HEX   00

                 MX    %00


*------------------------------------------------- Routine sauvegarde GS/OS et CDA

                 ELSE                                          ;*E0

                 LDA   FlagHi
                 BEQL  NoSaveHiSYS16

                 PEA   $0
                 PEA   $0
                 LDA   MasterId
                 PHA
                 PEA   $0000
                 LDX   #$1111                                  ; LGetPathName
                 JSL   $E10000
                 _Err
                 PLA
                 PLX
                 DEC
                 STA   PntPath
                 STX   PntPath+2

                 LDA   PntPath
                 LDX   PntPath+2

                 STA   PathNameAdr
                 STX   PathNameAdr+2

                 STZ   FlagClean

]lp              LDA   [PntPath]                               ; Conversion chaine
                 PHA                                           ; de type pascal en
                 XBA                                           ; GS/OS...
                 AND   #$00FF
                 STA   [PntPath]
                 JSL   $E100A8
                 DA    $2010
                 ADRL  Open_Parms
                 TAX                                           ; et vice-versa...
                 PLA                                           ; (Il faut un outil
                 STA   [PntPath]                               ;  pour faire ca???)
                 TXA
                 CMP   #1
                 BCC   NoErrOp

                 CMP   #$45
                 BNE   ErrFatalBis
                 JSR   InsertDisk
                 BCC   ]lp
                 BRA   There0
ErrFatalBis      JSR   FatalError
There0           BRL   NoSaveHiSYS16

ErrFatal0        LDA   #$FF
ErrFatal         JSR   FatalError
                 BRL   EndSave

NoErrOp          LDA   Ref
                 STA   MarkRef
                 STA   ReadRef
                 STA   WriteRef
                 STA   CloseRef
                 STA   FlushRef

                 LDA   FlagClean
                 BEQ   NoR2

                 JSR   PrintSaving

NoR2             =     *

                 JSL   $E100A8
                 DA    $2016                                   ; SetMark
                 ADRL  Ref_Parms
                 BCS   ErrFatal

                 JSL   $E100A8
                 DA    $2012                                   ; Read
                 ADRL  Read_Parms
                 BCS   ErrFatal

                 LDX   #8-2
]lp              LDA   Signature,X
                 CMP   SignatureTest,X
                 BNE   ErrFatal0
                 DEX
                 DEX
                 BPL   ]lp

]lp              JSL   $E100A8
                 DA    $2013
                 ADRL  Write_Parms
                 BCC   EndSave0

                 CMP   #$45
                 BNE   NoBadVolume0
                 JSR   InsertDisk0
                 BRA   ]lp
NoBadVolume0     CMP   #$2B
                 BNE   ErrFatal1
                 JSR   WriteProtect
                 BRA   ]lp

ErrFatal1        BRL   ErrFatal

EndSave0         JSL   $E100A8
                 DA    $2015
                 ADRL  Flush_Parms
                 BCC   EndSave

                 CMP   #$45
                 BNE   NoBadVolume
                 JSR   InsertDisk0
                 BRA   EndSave0
NoBadVolume      CMP   #$2B
                 BNE   ErrFatal1
                 JSR   WriteProtect
                 BRA   EndSave0

EndSave          JSL   $E100A8
                 DA    $2014                                   ; Close
                 ADRL  Close_Parms

NoSaveHiSYS16    SEP   $20
                 LDAL  $E1C068
                 PHA
                 LDAL  $E1C08B
                 LDAL  $E1C08B

                 REP   $30

                 LDAL  $01FC98
                 AND   #$00FF
                 CMP   #$5C
                 BNE   NoPatch0

                 LDA   SaveVect+1                              ; avant de quitter, on
                 STAL  $01FC99                                 ; enleve notre patch
                 LDA   SaveVect+2
                 STAL  $01FC9A

NoPatch0         SEP   $20
                 PLA
                 STAL  $E1C068
                 REP   $20

                 JSL   $E100A8
                 DA    $200C                                   ; SetSysPref
                 ADRL  SysDefaultParms

                 BRL   NormalQuit

Open_Parms       DA    15
Ref              DA    0
PathNameAdr      ADRL  0
                 DA    %0000_0000_0000_0011                    ; R/W
                 DS    50

Ref_Parms        DA    3
MarkRef          DA    0
                 DA    0
                 ADRL  Signature-BeginningOfFile+$45

Read_Parms       DA    5
ReadRef          DA    0
                 ADRL  SignatureTest
                 ADRL  8
                 ADRL  0
                 DA    0                                       ; NoCache

Write_Parms      DA    4
WriteRef         DA    0
                 ADRL  HiScoreList
                 ADRL  12*8
                 ADRL  0
                 DA    0

Close_Parms      DA    1
CloseRef         DA    0

Flush_Parms      DA    1
FlushRef         DA    0

PrintSaving      =     *
                 JSR   ClearAera
                 STZ   Inv
                 LDX   #91*$A0+$37+4
                 JSR   Print
                 HEX   0C99
                 TXT   "  SAVING";"SAUVEGARDE"
                 HEX   8D
                 TXT   "HIGH SCORES";"DES SCORES."
                 HEX   00
                 RTS

FlagClean        DS    2

WriteProtect     JSR   ClearAera
                 LDX   #67*$A0+$36+4
                 JSR   Print
                 HEX   0CFF
                 TXT   "DISK WRITE";"DISQUETTE"
                 HEX   8D
                 TXT   "PROTECTED.";"PROTEGEE."
                 HEX   0CAA00

WriteReturn0     DO    Language
                 LDX   #8*3+67*$A0+$36+2
                 JSR   Print
                 ASC   "PRESS RETURN",8D
                 ASC   "   TO RETRY ",00
                 ELSE
                 LDX   #8*3+67*$A0+$36+5
                 JSR   Print
                 ASC   "TAPEZ ENVOI",8D
                 ASC   "   POUR    ",8D
                 ASC   "RE-ESSAYER.",00
                 FIN

                 BRL   ContErr0

FlagCont         DS    2

InsertDisk0      LDA   #$FFFF
                 BRA   C0
InsertDisk       LDA   #0
C0               STA   FlagCont
                 SEP   $30
                 LDX   #0
                 LDY   #2+1
]lp              LDA   [PntPath],Y
                 ORA   #$80
                 CMP   #"/"
                 BEQ   EndPath0
                 STA   Name+1,X
                 INY
                 INX
                 CPX   #11
                 BNE   ]lp

EndPath0         CPX   #11
                 BEQ   NoBlank
                 LDA   #" "
                 STA   Name+1,X
                 INX
                 BRA   EndPath0

NoBlank          REP   $30
                 LDX   #67*$A0+$36+2
                 JSR   Print
                 HEX   0CFF
                 TXT   "INSERT DISK:";"INSEREZ:"
                 HEX   8D
Name             ASC   "/           ",0CAA00

                 LDA   FlagCont
                 BEQ   NormalCont
                 BRL   WriteReturn0

NormalCont       DO    Language
                 LDX   #8*3+67*$A0+$36+2
                 JSR   Print
                 ASC   "PRESS RETURN",8D
                 ASC   "   TO RETRY ",8E
                 ASC   "     OR",8E
                 ASC   "PRESS ESC",8D
                 ASC   "   TO ABORT",00
                 ELSE
                 LDX   #8*3+67*$A0+$36+5
                 JSR   Print
                 ASC   "TAPEZ ENVOI",8D
                 ASC   "   POUR    ",8D
                 ASC   "RE-ESSAYER.",8E
                 ASC   "    OU",8E
                 ASC   " TAPEZ ESC",8D
                 ASC   "   POUR",8D
                 ASC   "ABANDONNER."
                 HEX   00
                 FIN

ContErr0         SEP   $30
]lp              LDL   $E1C025
                 BIT   #%0000_1000
                 BNE   ]lp
]lp2             STL   $E1C010
]lp              LDL   $E1C000
                 BPL   ]lp
                 STL   $E1C010
                 CMP   #"M"&$9F
                 BEQ   GoRetry
                 CMP   #$9B
                 BNE   ]lp2
                 REP   $30
                 SEC
                 RTS
GoRetry          INC   FlagClean
                 REP   $30
                 CLC
                 RTS

FatalError       SEP   $30
                 PHA
                 AND   #$F0
                 LSR
                 LSR
                 LSR
                 LSR
                 JSR   Translate
                 STA   ErrCode
                 PLA
                 AND   #$0F
                 JSR   Translate
                 STA   ErrCode+1
                 REP   $30
                 JSR   ClearAera
                 LDX   #91*$A0+$37+4
                 JSR   Print
                 HEX   0C99
                 TXT   "CAN'T SAVE";"SAUVEGARDE"
                 HEX   8D
                 TXT   "HI-SCORES :";"IMPOSSIBLE"
                 HEX   8D8D
                 TXT   " ERROR $";"ERREUR $"
ErrCode          ASC   "??",00
                 SEP   $30
]lp              LDL   $E1C025
                 BIT   #%0000_1000
                 BNE   ]lp
                 STL   $E1C010
]lp              LDL   $E1C000
                 BPL   ]lp
                 STL   $E1C010
                 REP   $30
                 RTS

NormalQuit       DO    vP16                                    ; Routine pour quitter
                 ELSE                                          ;
                 SEP   $20
Save35           LDA   #0
                 STL   $E1C035
Save29           LDA   #$41
                 STL   $E1C029
Save34           LDA   #0
                 STL   $E1C034
                 REP   $20

                 LDX   #0                                      ; Remets l'écran tel
]lp              TXY                                           ; qu'il etait pour
                 LDA   [SaveScreen],Y                          ; la version CDA
                 STAL  $E12000,X
                 INX
                 INX
                 BPL   ]lp
                 FIN                                           ;*F

                 LDA   UserId
                 PHA
                 LDX   #$1102                                  ; Dispose All
                 JSL   $E10000
                 _Err

                 LDA   MasterId
                 PHA
                 LDX   #$0302
                 JSL   $E10000
                 _Err

                 DO    vP16                                    ;*D

                 SEP   $20
Save35           LDA   #0
                 STL   $E1C035
Save29           LDA   #$41
                 STL   $E1C029
Save34           LDA   #0
                 STL   $E1C034
                 REP   $20

                 JSL   $E100A8
                 DA    $29
                 ADRL  QuitRecGS
QuitRecGS        DA    0
                 ADRL  0
                 DA    0
                 ELSE                                          ;*E
                 PLB
                 PLD
                 PLP
ENDCDA           RTL
                 FIN                                           ;*F

                 FIN                                           ;*F0


                 MX    %11
Translate        CLC
                 ADC   #"0"
                 CMP   #"9"+1
                 BCC   Chiffre0
                 ADC   #"A"-"9"-2
Chiffre0         RTS

LevelList        DA    01,30                                   ; Numero du level / Vitesse
                 DA    05,25
                 DA    10,20
                 DA    15,15
                 DA    20,10
                 DA    25,05

Progression      LUP   5
                 DA    50                                      ; Nombre de piece pour passer au level
                 --^
                 LUP   5
                 DA    60
                 --^
                 LUP   5
                 DA    70
                 --^
                 LUP   5
                 DA    80
                 --^
                 DA    080
                 DA    090
                 DA    100
                 DA    110
                 DA    120

                 MX    %00

*-------------------------------------------------

* Apres avoir test{ la touche Q, on va tester les autres options
* qui s'offrent @ nous...

NoQuit           =     *

* Touche I = Info

                 CMP   #"I"
                 BNEL  NoInfo

                 JSR   ClearAera
                 STZ   Inv
                 LDX   #50*$A0+$37-1+2+2
                 JSR   Print
                 HEX   0C99
                 TXT   "COLUMNS",8D;"REGLES",8D
                 TXT   "RULES.",8D8D0CFF;"DU JEU.",8D8D8D0CFF
                 TXT   "  <:LEFT",8D;"  <:GAUCHE",8D
                 TXT   "  >:RIGHT",8D;"  >:DROITE",8D
                 TXT   "  R:ROTATE",8D;"  R:PERMUTE",8D
                 TXT   "SPC:FALL",8D;"ESP:DEPOSE",8D
                 TXT   " ^R:RESTART",8D;" ^R:REJOUER",8D
                 TXT   " ^S:NEW PAT",8D;" ^S:FORMES",8D
                 TXT   "  N:NEXT",8D;"  N:SUIVANT",8D
                 ASC   "  P:PAUSE",8D8D
                 DO    Language
                 ASC   " HAVE FUN !",00
                 ELSE
                 HEX   8D
                 ASC   "JOIE",8D
                 ASC   "DANS LES",8D
                 ASC   "CHAUMIERES!",00
                 FIN

EndAbout         SEP   $20
                 STL   $E1C010
]lp              LDL   $E1C000
                 BPL   ]lp
                 REP   $20
                 BRL   ]RestartGame

* Touche A = About

NoInfo           CMP   #"A"
                 BNEL  NoAbout

                 JSR   ClearAera
                 STZ   Inv
                 LDX   #35*$A0+$37+4
                 JSR   Print
                 DFB   $0C,$EE,"F"
                 DFB   $0C,$CC,"U"
                 DFB   $0C,$AA,"N"
                 DFB   $0C,$22
                 ASC   " COLUMNS",8D8D
                 DFB   $0C,$FF
                 TXT   " BY ";"PAR "
                 DFB   $0C,$DD
                 ASC   "FTA",8D8D
                 DFB   $0C,$FF
                 ASC   "CODING:",8E
                 ASC   "O. GOGUEL",8D8E
                 ASC   "DESIGN:",8E
                 ASC   "O. BAILLY",8D
                 ASC   "   MAITRE",8D8D8D8D
                 ASC   "VERSION 1.1",8E
                 ASC   "TOOLBOX-MAG",8E
                 TXT   " ISSUE: 04";" NUMERO 04"
                 DFB   $8E
                 TXT   " 03-FEB-91";" 03-FEV-91"
                 DFB   $8E,$8D
                 ASC   " COPYRIGHT",8E
                 ASC   "FTA/TOOLBOX"
                 HEX   0CFF00
                 BRL   EndAbout

* Sinon, il reste les levels...

NoAbout          CMP   #"1"
                 BCC   NoLevel
                 CMP   #"6"+1
                 BCS   NoLevel
                 SEC
                 SBC   #"1"
                 ASL
                 ASL
                 TAX
                 LDA   LevelList,X
                 STA   Level0
                 TAY
                 SED
                 LDA   #0
                 CLC
]lp              ADC   #1
                 DEY
                 BNE   ]lp
                 CLD
                 STA   Level
                 LDA   LevelList+2,X
                 STA   LevelSpeed

                 BRL   StartGame

NoLevel          BRL   WaitKeyPress


*------------------------------------------------- Debut d'une nouvelle partie

StartGame        STZ   Score
                 STZ   Score+2
                 STZ   Total

                 STZ   ColorDeg
                 JSR   Degrade

                 JSR   GetBarre                                ; initialise GetBarre
; pour pouvoir afficher
; eventuellement le
; suivant...

                 LDA   Level0
                 DEC
                 ASL
                 TAX
                 LDA   Progression,X
                 STA   Counter

                 LDX   #0
]lp              STZ   Table,X
                 INX
                 INX
                 CPX   #NbLgn*NbCol
                 BCC   ]lp

                 REP   $30

                 JSR   WaitSync
                 JSR   DrawScreen
                 JSR   PrintScore
                 JSR   PrintLevel
                 JSR   PrintTotal
                 JSR   WaitSync
                 JSR   WaitSync
                 JSR   WaitSync

]newbar          =     *

                 JSR   GetBarre
                 JSR   PrintNext
                 BRL   ContGame

GetBarre         =     *
                 SEP   $30
                 LDX   #0
]loop            LDA   BarreNext,X
                 STA   Barre,X
                 JSR   GetAlea
]lp              AND   #$7F
                 CMP   #6
                 BCC   OkCouleur
                 SEC
                 SBC   #6
                 BRA   ]lp
OkCouleur        INC
                 STA   BarreNext,X
                 INX
                 CPX   #3
                 BNE   ]loop
                 REP   $30
                 RTS
*

NoNext           LDX   #0
]lp2             PHX
                 LDY   #6
]lp              LDAL  85*$A0+Screen-20+128,X
                 STAL  85*$A0+Screen+128,X
                 INX
                 INX
                 DEY
                 BNE   ]lp
                 PLA
                 CLC
                 ADC   #$A0
                 TAX
                 CPX   #41*$A0
                 BNE   ]lp2
                 STZ   AlreadyNext
                 RTS

* Affichage de l'element suivant ou non selon le flag NextMode


PrintNext        BIT   NextMode
                 BPL   NoNext
                 BIT   AlreadyNext
                 BMI   Already_La
                 LDA   #$FFFF
                 STA   BlackMode
                 LDA   #85
                 STA   Lgn
                 LDA   #128
                 STA   Col
                 LDA   #38
                 STA   ZNbLgn
                 LDA   #9
                 STA   ZNbCol
                 JSR   Window

Already_La       STZ   BlackMode
                 LDA   #$FFFF
                 STA   AlreadyNext

                 LDA   #88*$A0+130-Center
                 STA   Buf

                 LDX   #0
]lp              PHX
                 LDA   BarreNext,X
                 AND   #$00FF
                 ASL
                 TAY
                 STZ   Msk0
                 LDX   Buf
                 JSR   PrintOnePat
                 LDA   Buf
                 CLC
                 ADC   #HautCase*$A0
                 STA   Buf
                 PLX
                 INX
                 CPX   #3
                 BNE   ]lp

                 RTS

* C'est dur de suivre quand il y a des sous-routines au milieu de la
* boucle principale, n'est-il pas ?


ContGame         JSR   GetAlea

* On choisit aleatoirement une colonne de départ pour le nouvel élément...

                 AND   #$1F
]lp              CMP   #NbCol
                 BCC   OkCol
                 SEC
                 SBC   #NbCol
                 BRA   ]lp
OkCol            STA   BarreCol
                 STA   BarreCol0

                 STZ   BarreLgn

* On vérifie que l'on peut l'afficher entierement, cad qu'il n'y ait rien
* juste en dessous...

]loop            JSR   GetBarreAdr
                 TAX
                 STX   BarrePos
                 SEP   $20
                 LDA   Table,X
                 AND   #$0F
                 BNE   Over0
                 LDA   Table+NbCol,X
                 AND   #$0F
                 BNE   Over0
                 LDA   Table+NbCol+NbCol,X
                 AND   #$0F
                 BEQ   GoodCol

* Si on ne peut l'afficher, on va essayer avec la colonne voisine...

Over0            INC   BarreCol
                 LDA   BarreCol
                 CMP   #NbCol
                 BNE   NoFin
                 STZ   BarreCol
                 LDA   #0
NoFin            CMP   BarreCol0
                 BNE   ]loop


* Si on n'a trouvé aucune colonne de libre, alors ...

                 BRL   GameOver

GoodCol          =     *

*------------------------------------------------- Boucle principale

]mainloop        REP   $30
                 STZ   Msk
                 JSR   StoreBarre
                 JSR   DrawScreen
                 LDA   LevelSpeed
                 STA   CycleCount
]lp              JSR   TestKey
                 BCC   Nothing
                 JSR   ClearBarre
                 JSR   StoreBarre
                 JSR   DrawScreen
Nothing          JSR   WaitSync
                 DEC   CycleCount
                 BNE   ]lp
                 JSR   TestDown
                 BNEL  Down
                 JSR   ClearBarre
                 INC   BarreLgn
                 JSR   StoreBarre
                 BRL   ]mainloop

*------------------------------------------------- Fin du jeu...

GameOver         REP   $30

                 LDA   #$FFFF
                 STA   Inv

                 LDA   #92
                 STA   Lgn
                 LDA   #$3B
                 STA   Col
                 LDA   #14
                 STA   ZNbLgn
                 LDA   #$29
                 STA   ZNbCol
                 JSR   Window

                 LDX   #96+1*$A0+$3E
                 JSR   Print
                 HEX   0C11
                 ASC   "GAME OVER",00

                 JSR   CheckHighScore
                 BCS   NoHigh

                 BRL   ]RestartGame

NoHigh           SEP   $20
                 STL   $E1C010
]lp              LDL   $E1C025
                 BIT   #%0000_1000
                 BNE   ]lp
                 STL   $E1C010
]lp              LDL   $E1C000
                 BPL   ]lp
                 STL   $E1C010
                 REP   $20

                 BRL   ]RestartGame

*-------------------------------------------------

NextPos          INC   Col0
                 LDA   Col0
                 CMP   #NbCol
                 BNE   MoreTest
                 STZ   Col0
                 INC   Lgn0
                 LDA   Lgn0
                 CMP   #NbLgn
                 BNE   MoreTest

                 LDA   Flag
                 BEQ   PoorPlayer

                 JSR   SecondAction

                 BRA   Down

PoorPlayer       BRL   ]newbar

*------------------------------------------------- Routine de recherche
*                                                  pour l'elimination des
*                                                  briques...

Down             STZ   Lgn0
                 STZ   Col0
                 STZ   Flag

                 SED
                 LDA   Score
                 CLC
                 ADC   #5
                 STA   Score
                 LDA   Score+2
                 ADC   #0
                 STA   Score+2
                 CLD

                 JSR   PrintScore

MoreTest         LDA   Lgn0
                 ASL
                 TAX
                 LDA   MulLgn,X
                 CLC
                 ADC   Col0
                 TAX
                 LDA   Table,X
                 AND   #$1F
                 BEQ   NextPos
                 BIT   #$10
                 BNE   NextPos
                 STA   CaseTest

                 STZ   Buf                                     ; 4 grandes direction

]looping         STZ   Compteur

]loop            LDA   Lgn0
                 STA   Lgn
                 LDA   Col0
                 STA   Col

]lp              LDX   Buf
                 JSR   (GetList,X)
                 CMP   #$FFFF
                 BEQ   NextDirection
                 LDA   Lgn
                 ASL
                 TAX
                 LDA   MulLgn,X
                 CLC
                 ADC   Col
                 TAX
                 LDA   Table,X
                 AND   #$0F
                 CMP   CaseTest
                 BNE   NextDirection

                 TXA
                 LDX   Compteur
                 STA   CaseList,X
                 INX
                 INX
                 STX   Compteur
                 BRA   ]lp

NextDirection    LDA   Buf
                 INC
                 INC
                 STA   Buf
                 AND   #%0000_0010
                 BNE   ]loop

                 LDA   Compteur
                 CMP   #2*2
                 BCC   No3Barre

                 LDX   Compteur
]lp              DEX
                 DEX
                 BMI   EndKill
                 PHX
                 LDA   CaseList,X
                 TAX
                 LDA   Table,X
                 ORA   #$0010
                 AND   #$FF7F
                 STA   Table,X
                 INC   Flag
                 PLX
                 BRA   ]lp

EndKill          LDA   Lgn0
                 ASL
                 TAX
                 LDA   MulLgn,X
                 CLC
                 ADC   Col0
                 TAX
                 LDA   Table,X
                 ORA   #$0010
                 AND   #$FF7F
                 STA   Table,X

No3Barre         LDA   Buf
                 CMP   #16
                 BNE   ]looping

                 BRL   NextPos

SecondAction     =     *
                 STZ   Msk
]lp              JSR   DrawScreen
                 JSR   WaitSync
                 JSR   WaitSync
                 LDA   Msk
                 INC
                 INC
                 STA   Msk
                 CMP   #7*2
                 BNE   ]lp

                 REP   $30

                 LDA   PtrPatPos
                 CMP   #4*2
                 BEQ   NoBlanc0

                 JSR   StoreBlanc

NoBlanc0         LDA   #2
                 STA   Msk

                 LDA   #6*2
                 STA   Msk

]lp              LDA   Msk
                 DEC
                 DEC
                 STA   Msk
                 BMI   Out

                 JSR   DrawScreen
                 JSR   WaitSync
                 JSR   WaitSync
                 BRA   ]lp

StoreBlanc       SEP   $30
                 LDX   #0
]lp              LDA   Table,X
                 BIT   #%0001_0000
                 BEQ   NoOff0
                 ORA   #%0001_0111
NoOff0           STA   Table,X
                 INX
                 CPX   #NbLgn*NbCol
                 BNE   ]lp
                 REP   $30
                 RTS

Out              =     *

                 LDA   PtrPatPos
                 CMP   #4*2
                 BNE   NoBlanc

                 JSR   StoreBlanc

NoBlanc          LDA   #2
                 STA   Msk

]lp              JSR   DrawScreen
                 JSR   WaitSync
                 JSR   WaitSync
                 LDA   Msk
                 INC
                 INC
                 STA   Msk
                 CMP   #7*2
                 BNE   ]lp

                 STZ   Buf

                 SEP   $30

                 LDX   #0
]lp              LDA   Table,X
                 BIT   #%0001_0000
                 BEQ   NoCl
                 STZ   Table,X
                 INC   Buf
                 LDA   Buf
                 PHA
                 PHX
                 REP   $30
                 DEC   Counter
                 BNE   NoNewLevel
                 INC   ColorDeg
                 LDA   ColorDeg
                 CMP   #7
                 BNE   NoNewColor
                 STZ   ColorDeg
NoNewColor       JSR   Degrade
                 INC   Level0
                 LDA   Level0
                 DEC
                 ASL
                 TAX
                 LDA   Progression,X
                 STA   Counter
                 LDA   LevelSpeed
                 CMP   #1
                 BEQ   NoNewLevel
                 DEC   LevelSpeed
                 SED
                 LDA   Level
                 CLC
                 ADC   #1
                 STA   Level
                 CLD
                 JSR   PrintLevel
NoNewLevel       =     *
                 SED
                 LDA   Total
                 CLC
                 ADC   #1
                 STA   Total
                 SEP   $30
                 CLD
                 PLX
                 PLA
                 STA   Buf
NoCl             INX
                 CPX   #NbCol*NbLgn
                 BNE   ]lp
                 REP   $30

                 LDA   Buf
                 CMP   #3
                 BCC   NoBonus
                 CMP   #12
                 BCC   NoMaxBonus
                 LDA   #11
NoMaxBonus       SEC
                 SBC   #3
                 ASL
                 TAX
                 SED
                 LDA   Score
                 CLC
                 ADC   ScorePerBrick,X
                 STA   Score
                 LDA   Score+2
                 ADC   #0
                 STA   Score+2
                 CLD

NoBonus          JSR   DrawScreen
                 JSR   PrintTotal
                 JSR   PrintScore
                 JSR   WaitSync

                 SEP   $30

                 STZ   Pnt

]newcol          LDX   Pnt
]lp              LDA   Table,X
                 AND   #$0F
                 BNE   FoundTop
                 TXA
                 CLC
                 ADC   #NbCol
                 TAX
                 CMP   #NbLgn-1*NbCol
                 BCC   ]lp

                 BRA   NextCol

FoundTop         STX   Buf

                 LDA   #NbLgn-1*NbCol
                 CLC
                 ADC   Pnt
                 TAX

]lp              CPX   Buf
                 BEQ   NextCol

                 LDA   Table,X
                 AND   #$0F
                 BNE   SomethingUnder

                 PHX
]notop           LDA   Table-NbCol,X
                 AND   #%0000_1111
                 STA   Table,X
                 TXA
                 SEC
                 SBC   #NbCol
                 TAX
                 CPX   Buf
                 BNE   ]notop

                 STZ   Table,X

                 LDA   Buf                                     ; Descend le plafond de 1 ligne
                 CLC
                 ADC   #NbCol
                 STA   Buf
                 PLX
                 BRA   ]lp

SomethingUnder   TXA
                 SEC
                 SBC   #NbCol
                 TAX
                 BRA   ]lp

NextCol          INC   Pnt
                 LDA   Pnt
                 CMP   #NbCol
                 BNE   ]newcol

EndDisap         REP   $30

                 JSR   DrawScreen

                 JSR   WaitSync
                 JSR   WaitSync
                 RTS


* Test dans chacune des directions...

GetList          DA    Get1
                 DA    Get9
                 DA    Get2
                 DA    Get8
                 DA    Get3
                 DA    Get7
                 DA    Get4
                 DA    Get6

Get1             LDA   Lgn
                 BEQ   OutCadre
                 LDA   Col
                 BEQ   OutCadre
                 DEC   Lgn
                 DEC   Col
                 RTS
Get2             LDA   Lgn
                 BEQ   OutCadre
                 DEC   Lgn
                 RTS
Get3             LDA   Lgn
                 BEQ   OutCadre
                 LDA   Col
                 CMP   #NbCol-1
                 BEQ   OutCadre
                 DEC   Lgn
                 INC   Col
                 RTS
Get4             LDA   Col
                 BEQ   OutCadre
                 DEC   Col
                 RTS
OutCadre         LDA   #$FFFF
                 RTS
Get6             LDA   Col
                 CMP   #NbCol-1
                 BEQ   OutCadre
                 INC   Col
                 RTS
Get7             LDA   Col
                 BEQ   OutCadre
                 LDA   Lgn
                 CMP   #NbLgn-1
                 BEQ   OutCadre
                 INC   Lgn
                 DEC   Col
                 RTS
Get8             LDA   Lgn
                 CMP   #NbLgn-1
                 BEQ   OutCadre
                 INC   Lgn
                 RTS
Get9             LDA   Lgn
                 CMP   #NbLgn-1
                 BEQ   OutCadre
                 LDA   Col
                 CMP   #NbCol-1
                 BEQ   OutCadre
                 INC   Lgn
                 INC   Col
                 RTS


TestKey          SEP   $20
                 LDL   $E1C000
                 STL   $E1C010
                 REP   $20
                 AND   #$00FF
                 CMP   #$0080
                 BCS   SomeKey0
                 BRL   NoKey

SomeKey0         CMP   #"R"&$9F
                 BNE   NoAbandon
                 PLA
                 STZ   Score
                 STZ   Score+2
                 BRL   GameOver

NoAbandon        =     *
                 CMP   #"S"&$9F
                 BNE   NoSwitchPat

]lp              LDX   PtrPatPos
                 LDA   PatternList,X
                 BNE   SameList
                 STZ   PtrPatPos
                 BRA   ]lp
SameList         STA   PtrPattern
                 LDA   MskList,X
                 STA   PtrPtrMsk
                 INC   PtrPatPos
                 INC   PtrPatPos

DrawGame         SEP   $30
                 LDX   #0
]lp              LDA   Table,X
                 AND   #%0111_1111
                 STA   Table,X
                 INX
                 CPX   #NbCol*NbLgn
                 BNE   ]lp
                 REP   $30

                 JSR   PrintNext

                 SEC
                 RTS

NoSwitchPat      CMP   #"4"
                 BEQ   GLeft
                 CMP   #"J"
                 BEQ   GLeft
                 CMP   #"H"&$9F
                 BNE   NoLeft

GLeft            LDA   BarreCol
                 BEQ   NoKey0

                 JSR   GetBarreAdr
                 DEC
                 JSR   TestLR
                 BNE   NoKey0

                 DEC   BarreCol
                 SEC
                 RTS

NoKey0           CLC
                 RTS

NoLeft           CMP   #"L"
                 BEQ   GRight
                 CMP   #"6"
                 BEQ   GRight
                 CMP   #"U"&$9F
                 BNE   NoRight

GRight           LDA   BarreCol
                 CMP   #NbCol-1
                 BEQ   NoKey0

                 JSR   GetBarreAdr
                 INC
                 JSR   TestLR
                 BNE   NoKey0

                 INC   BarreCol
                 SEC
                 RTS

NoRight          CMP   #"R"
                 BNE   NoRotate
GRotate          SEP   $20
                 LDA   Barre
                 PHA
                 LDA   Barre+1
                 STA   Barre
                 LDA   Barre+2
                 STA   Barre+1
                 PLA
                 STA   Barre+2
                 REP   $20
                 SEC
                 RTS

NoRotate         CMP   #"K"
                 BEQ   GFall
                 CMP   #"5"
                 BEQ   GFall
                 CMP   #" "
                 BNE   NoSpace

GFall            =     *
]lp              JSR   TestDown
                 BNE   FoundDown
                 INC   BarreLgn
                 BRA   ]lp
FoundDown        LDA   #1
                 STA   CycleCount
                 SEC
                 RTS

NoSpace          =     *
                 CMP   #"N"
                 BNE   NoN
                 LDA   NextMode
                 EOR   #$FFFF
                 STA   NextMode
                 JSR   PrintNext
                 CLC
                 RTS

NoN              CMP   #"P"
                 BNE   NoPause

                 LDX   #0
]lp2             PHX
                 LDY   #NbCol*LargCase/4
                 LDA   #0
]lp              STAL  Screen+Center,X
                 INX
                 INX
                 DEY
                 BNE   ]lp
                 PLA
                 CLC
                 ADC   #$A0
                 TAX
                 CPX   #NbLgn*HautCase*$A0
                 BNE   ]lp2

                 LDA   #$FFFF
                 STA   Inv

                 LDA   #92
                 STA   Lgn
                 LDA   #$3B
                 STA   Col
                 LDA   #14
                 STA   ZNbLgn
                 LDA   #$29
                 STA   ZNbCol
                 JSR   Window

                 LDX   #96+1*$A0+$3E
                 JSR   Print
                 HEX   0C11
                 ASC   "> PAUSE <",0CFF00

                 SEP   $20
]lp              LDL   $E1C025
                 BIT   #%0000_1000
                 BNE   ]lp
]lp2             STL   $E1C010
]lp              LDL   $E1C000
                 BPL   ]lp
                 STL   $E1C010
                 REP   $20

                 BRL   DrawGame

NoPause          CMP   #"X"&$9F
                 BNE   No_XCol
                 LDA   XColor
                 EOR   #7
                 STA   XColor
                 JSR   Degrade
                 CLC
                 RTS

No_XCol          CMP   #"C"&$9F
                 BNE   NoDegCol
                 INC   ColorDeg
                 LDA   ColorDeg
                 CMP   #7
                 BNE   NoNewDeg0
                 STZ   ColorDeg
NoNewDeg0        JSR   Degrade
                 CLC
                 RTS
NoDegCol
NoKey            =     *
                 CLC
                 RTS

TestDown         LDA   BarreLgn
                 CMP   #NbLgn-3
                 BEQ   Down0
                 JSR   GetBarreAdr
                 TAX
                 LDA   Table+NbCol+NbCol+NbCol,X
                 AND   #$000F
                 RTS
Down0            LDA   #$FFFF
                 RTS

WaitSync         PHP
                 SEP   $20
]lp              LDL   $E1C02E
                 CMP   #$F0
                 BCC   ]lp
]lp              LDL   $E1C02E
                 CMP   #$F0
                 BCS   ]lp
                 PLP
                 RTS

TestLR           TAX
                 SEP   $20
                 LDA   Table,X
                 ORA   NbCol+Table,X
                 ORA   NbCol+NbCol+Table,X
                 REP   $20
                 AND   #$000F
                 RTS

GetAlea          PHP
                 SEP   $20
                 LDL   $E1C02E
                 EOR   AleaGen
                 ADC   AleaGen
                 INC   AleaGen
                 DO    vP8
                 SBC   $C02F
                 ELSE
                 SBCL  $E1C02F
                 FIN
                 ROR
                 ROR
                 ROR   AleaGen
                 ROR
                 DO    vP8
                 EOR   $C02E
                 ADC   $C02F
                 ELSE
                 EORL  $E1C02E
                 ADCL  $E1C02F
                 FIN
                 PLP
                 RTS

                 MX    %00

GetBarreAdr      LDA   BarreLgn
                 ASL
                 TAX
                 LDA   MulLgn,X
                 CLC
                 ADC   BarreCol
                 RTS

StoreBarre       JSR   GetBarreAdr
                 TAX
                 STX   BarrePos
                 SEP   $20
                 LDA   Table,X
                 AND   #$0F
                 BNE   Over
                 LDA   Barre
                 STA   Table,X
                 LDA   Table+NbCol,X
                 AND   #$0F
                 BNE   Over
                 LDA   Barre+1
                 STA   Table+NbCol,X
                 LDA   Table+NbCol+NbCol,X
                 AND   #$0F
                 BNE   Over
                 LDA   Barre+2
                 STA   Table+NbCol+NbCol,X
                 REP   $20
                 CLC
                 RTS
Over             REP   $20
                 SEC
                 RTS

ClearBarre       LDX   BarrePos
                 SEP   $20
                 STZ   Table,X
                 STZ   Table+NbCol,X
                 STZ   Table+NbCol+NbCol,X
                 REP   $20
                 RTS


CaseAdr          =     *
]A               =     0
                 LUP   NbLgn
                 DA    0*LargCase/2+]A
                 DA    1*LargCase/2+]A
                 DA    2*LargCase/2+]A
                 DA    3*LargCase/2+]A
                 DA    4*LargCase/2+]A
                 DA    5*LargCase/2+]A
                 DA    6*LargCase/2+]A
                 DA    7*LargCase/2+]A
]A               =     HautCase*$A0+]A
                 --^

MulLgn           =     *
]A               =     0
                 LUP   NbLgn
                 DA    ]A
]A               =     ]A+NbCol
                 --^


ClearAera        LDX   #0
]lp              STZ   Table,X
                 INX
                 INX
                 CPX   #NbLgn*NbCol
                 BCC   ]lp
                 JSR   DrawScreen
                 RTS


*------------------------------------------------- Routine d'affichage
*                                                  "intelligente"

DrawScreen       STZ   Pnt
                 BRA   ContDraw

PlotNothing      INC   Pnt
                 LDA   Pnt
                 CMP   #NbLgn*NbCol
                 BNE   ContDraw
                 RTS

ContDraw         LDX   Pnt
                 LDA   Table,X
                 BIT   #%0000_0000_0001_0000
                 BNE   SpecialPlot
                 BIT   #%0000_0000_1000_0000
                 BNE   PlotNothing
                 ORA   #%0000_0000_1000_0000
                 STA   Table,X
                 LDX   #0
                 AND   #%0000_0000_0001_1111
                 BRA   NoSpecial
SpecialPlot      LDX   Msk
                 AND   #%0000_0000_0000_1111
NoSpecial        STX   Msk0
                 ASL
                 TAY
                 LDA   Pnt
                 ASL
                 TAX
                 LDA   CaseAdr,X
                 TAX
                 JSR   PrintOnePat
                 BRA   PlotNothing

PrintOnePat      LDA   (PtrPattern),Y
                 STA   PtrShp
                 LDY   Msk0
                 LDA   (PtrPtrMsk),Y
                 STA   PtrMsk
                 LDA   #0
                 TAY
]lp              PHA
                 LDA   (PtrShp),Y
                 AND   (PtrMsk),Y
                 STAL  Screen+Center,X
                 INY
                 INY
                 LDA   (PtrShp),Y
                 AND   (PtrMsk),Y
                 STAL  Screen+Center+2,X
                 INY
                 INY
                 LDA   (PtrShp),Y
                 AND   (PtrMsk),Y
                 STAL  Screen+Center+4,X
                 INY
                 INY
                 TXA
                 CLC
                 ADC   #$A0
                 TAX
                 PLA
                 INC
                 CMP   #HautCase
                 BNE   ]lp
                 RTS

*------------------------------------------------- Routine de window...

ColorIn          =     $FF
ColorOut         =     $00

Window           PHP
                 LDA   Lgn
                 ASL
                 ASL
                 ASL
                 ASL
                 ASL
                 PHA
                 ASL
                 ASL
                 CLC
                 ADC   $01,S
                 PLY
                 CLC
                 ADC   #$2000
                 STA   Pnt
                 LDA   #$E1
                 STA   Pnt+2

                 SEP   $30

                 LDX   ZNbCol
                 LDY   Col
                 LDA   #ColorOut
                 EOR   BlackMode
]lp              STA   [Pnt],Y
                 INY
                 DEX
                 BPL   ]lp

                 JSR   AUG_LGN

                 DEC   ZNbLgn

                 STZ   Buf

]loop            LDX   ZNbCol
                 LDY   Col
                 LDA   #ColorOut&$F0+ColorIn&$0F
                 EOR   BlackMode
                 STA   [Pnt],Y
]lp              INY
                 DEX
                 BEQ   END_W2
                 LDA   #ColorIn
                 EOR   BlackMode
                 STA   [Pnt],Y
                 BRA   ]lp

END_W2           LDA   #ColorOut&$0F+ColorIn&$F0
                 EOR   BlackMode
                 STA   [Pnt],Y

                 LDA   Buf
                 CMP   #$03
                 BCC   NADA2

                 INY
                 LDA   #ColorOut
                 STA   [Pnt],Y

NADA2            JSR   AUG_LGN

                 INC   Buf
                 DEC   ZNbLgn
                 BNE   ]loop

                 LDY   Col
                 LDX   ZNbCol
                 LDA   #ColorOut
                 EOR   BlackMode
]loop            STA   [Pnt],Y
                 INY
                 DEX
                 BPL   ]loop
                 LDA   #ColorOut
                 STA   [Pnt],Y

                 LDX   #$02
]loop2           PHX

                 JSR   AUG_LGN

                 LDX   ZNbCol
                 LDY   Col
                 INY
                 INY
                 DEX
                 LDA   #ColorOut
]loop            STA   [Pnt],Y
                 INY
                 DEX
                 CPX   #$FF
                 BNE   ]loop

                 PLX
                 DEX
                 BNE   ]loop2
                 PLP
                 RTS

AUG_LGN          REP   $30
                 LDA   Pnt
                 CLC
                 ADC   #$00A0
                 STA   Pnt
                 SEP   $30
                 RTS

                 MX    %00

*------------------------------------------------- Routine d'affichage texte

Print            PLA
                 STA   Msg
                 JSR   Print0
                 LDA   Msg
                 PHA
                 RTS

Print_Rout       =     *
                 DEC
                 STA   Msg
Print0           =     *
]lp2             STX   XValue
]lp              INC   Msg
                 LDA   !$0000
Msg              =     *-2
                 TAY
                 AND   #$00FF
                 BEQ   EndPrint
                 CMP   #$0C
                 BEQ   Change_Color
                 CMP   #$8D
                 BEQ   NewLine
                 CMP   #$8E
                 BEQ   HalfLine
                 JSR   Print_Char
                 BRA   ]lp
Change_Color     TYA
                 XBA
                 SEP   $20
                 STA   ColorF+1
                 REP   $20
                 INC   Msg
                 BRA   ]lp
HalfLine         LDA   XValue
                 CLC
                 ADC   #9*$A0
                 TAX
                 BRA   ]lp2
NewLine          LDA   #0
XValue           =     *-2
                 CLC
                 ADC   #7*$A0
                 TAX
                 BRA   ]lp2
EndPrint         LDA   XValue
                 CLC
                 ADC   #8*$A0
                 TAX
                 RTS

Special          DFB   " ",".",":","-","$","#","<",">","!","^","/","'"

Print_Char       SEP   $20
                 LDY   #11
]lp              CMP   Special,Y
                 BEQ   GoSpecial
                 DEY
                 BPL   ]lp
                 BRA   GoNormal
GoSpecial        TYA
                 PHA
                 PHA
                 ASL
                 ASL
                 CLC
                 ADC   $01,S
                 PLY
                 TAY
                 REP   $20
                 AND   #$00FF
                 CLC
                 ADC   #Font
                 BRA   EndGetC

GoNormal         REP   $20
                 CMP   #"A"
                 BCC   GetChiffre
                 SEC
                 SBC   #"A"
                 LDY   #Lettre
                 BRA   ContGetC
GetChiffre       SEC
                 SBC   #"0"
                 LDY   #Chiffre
ContGetC         STY   PatchDeb+1
                 PHA
                 ASL
                 ASL
                 CLC
                 ADC   $01,S
PatchDeb         ADC   #0
                 PLY

EndGetC          STA   Font_Adr
                 LDA   #5
]lp2             PHA
                 PHX
                 LDA   !$0000
Font_Adr         =     *-2
                 INC   Font_Adr
                 LDY   #4
]lp              PHY
                 PHA
                 LDY   #0
                 BIT   #%0100_0000
                 BEQ   No_Left
                 LDY   #$0F
No_Left          BIT   #%1000_0000
                 BEQ   No_Right
                 TYA
                 ORA   #$F0
                 TAY
No_Right         TYA
                 SEP   $20
ColorF           AND   #$FF
NoI0             LDY   Inv
                 BEQ   noinv
                 LDY   ColorF
                 CPY   #$FF29
                 BNE   noinv0
                 EOR   #$FF
                 BRA   noinv
noinv0           TAY
                 AND   #$0F
                 BNE   ok0
                 TYA
                 ORA   #$0F
                 TAY
ok0              TYA
                 AND   #$F0
                 BNE   ok1
                 TYA
                 ORA   #$F0
                 TAY
ok1              TYA
noinv            STAL  $E12000,x
                 REP   $20
                 INX
                 PLA
                 ASL
                 ASL
                 PLY
                 DEY
                 BNE   ]lp
                 PLA
                 CLC
                 ADC   #$A0
                 TAX
                 PLA
                 DEC
                 BNE   ]lp2
                 TXA
                 SEC
                 SBC   #5*$A0-4
                 TAX
                 RTS

*------------------------------------------------- Police

Font             DFB   %00000000
                 DFB   %00000000
                 DFB   %00000000
                 DFB   %00000000
                 DFB   %00000000

                 DFB   %00000000
                 DFB   %00000000
                 DFB   %00000000
                 DFB   %00011000
                 DFB   %00011000

                 DFB   %00000000
                 DFB   %00011000
                 DFB   %00000000
                 DFB   %00011000
                 DFB   %00000000

                 DFB   %00000000
                 DFB   %00000000
                 DFB   %01111100
                 DFB   %00000000
                 DFB   %00000000

                 DFB   %01111110
                 DFB   %11010000
                 DFB   %01111100
                 DFB   %00010110
                 DFB   %11111100

                 DFB   %11111110
                 DFB   %11111110
                 DFB   %11111110
                 DFB   %11111110
                 DFB   %11111110

                 DFB   %00011000
                 DFB   %00110000
                 DFB   %01111110
                 DFB   %00110000
                 DFB   %00011000

                 DFB   %00011000
                 DFB   %00001100
                 DFB   %01111110
                 DFB   %00001100
                 DFB   %00011000

                 DFB   %00011000
                 DFB   %00011000
                 DFB   %00011000
                 DFB   %00000000
                 DFB   %00011000

                 DFB   %00011000
                 DFB   %00111100
                 DFB   %01100110
                 DFB   %00000000
                 DFB   %00000000

                 DFB   %00000110
                 DFB   %00001100
                 DFB   %00011000
                 DFB   %00110000
                 DFB   %01100000

                 DFB   %00011000
                 DFB   %00011000
                 DFB   %00000000
                 DFB   %00000000
                 DFB   %00000000


Chiffre          DFB   %01111110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11111100

                 DFB   %01111000
                 DFB   %00011000
                 DFB   %00011000
                 DFB   %00011000
                 DFB   %01111100

                 DFB   %11111100
                 DFB   %00000110
                 DFB   %01111100
                 DFB   %11000000
                 DFB   %01111110

                 DFB   %11111100
                 DFB   %00000110
                 DFB   %00011100
                 DFB   %00000110
                 DFB   %11111100

                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11111110
                 DFB   %00000110
                 DFB   %00000110

                 DFB   %11111110
                 DFB   %11000000
                 DFB   %11111100
                 DFB   %00000110
                 DFB   %11111100

                 DFB   %01111110
                 DFB   %11000000
                 DFB   %11111100
                 DFB   %11000110
                 DFB   %01111100

                 DFB   %11111110
                 DFB   %00001100
                 DFB   %00011000
                 DFB   %00011000
                 DFB   %00011000

                 DFB   %01111100
                 DFB   %11000110
                 DFB   %01111100
                 DFB   %11000110
                 DFB   %01111100

                 DFB   %01111100
                 DFB   %11000110
                 DFB   %01111110
                 DFB   %00000110
                 DFB   %00000110

Lettre           DFB   %01111100
                 DFB   %11000110
                 DFB   %11111110
                 DFB   %11000110
                 DFB   %11000110

                 DFB   %11111100
                 DFB   %11000110
                 DFB   %11111100
                 DFB   %11000110
                 DFB   %11111100

                 DFB   %01111110
                 DFB   %11000000
                 DFB   %11000000
                 DFB   %11000000
                 DFB   %01111110

                 DFB   %11111100
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11111100

                 DFB   %11111110
                 DFB   %11000000
                 DFB   %11110000
                 DFB   %11000000
                 DFB   %11111110

                 DFB   %11111110
                 DFB   %11000000
                 DFB   %11110000
                 DFB   %11000000
                 DFB   %11000000

                 DFB   %01111110
                 DFB   %11000000
                 DFB   %11001110
                 DFB   %11000110
                 DFB   %01111110

                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11111110
                 DFB   %11000110
                 DFB   %11000110

                 DFB   %11111100
                 DFB   %00110000
                 DFB   %00110000
                 DFB   %00110000
                 DFB   %11111100

                 DFB   %00000110
                 DFB   %00000110
                 DFB   %00000110
                 DFB   %11000110
                 DFB   %01111100

                 DFB   %11000110
                 DFB   %11001100
                 DFB   %11111000
                 DFB   %11001100
                 DFB   %11000110

                 DFB   %11000000
                 DFB   %11000000
                 DFB   %11000000
                 DFB   %11000000
                 DFB   %11111110

                 DFB   %11000110
                 DFB   %11111110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11000110

                 DFB   %11000110
                 DFB   %11110110
                 DFB   %11011110
                 DFB   %11000110
                 DFB   %11000110

                 DFB   %01111100
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %01111100

                 DFB   %11111100
                 DFB   %11000110
                 DFB   %11111100
                 DFB   %11000000
                 DFB   %11000000

                 DFB   %01111100
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11011110
                 DFB   %01111110

                 DFB   %11111100
                 DFB   %11000110
                 DFB   %11111100
                 DFB   %11000110
                 DFB   %11000110

                 DFB   %01111110
                 DFB   %11000000
                 DFB   %01111100
                 DFB   %00000110
                 DFB   %11111100

                 DFB   %11111110
                 DFB   %00110000
                 DFB   %00110000
                 DFB   %00110000
                 DFB   %00110000

                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %01111100

                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %01111100
                 DFB   %00111000

                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11000110
                 DFB   %11111110
                 DFB   %11000110

                 DFB   %11000110
                 DFB   %01101100
                 DFB   %00111000
                 DFB   %01101100
                 DFB   %11000110

                 DFB   %11000110
                 DFB   %01101100
                 DFB   %00111000
                 DFB   %00110000
                 DFB   %01100000

                 DFB   %11111110
                 DFB   %00001100
                 DFB   %00011000
                 DFB   %01100000
                 DFB   %11111110

*------------------------------------------------- Affichage divers...

PrintScore       STZ   Buf
                 LDY   #11+9*$A0+124
                 LDX   #2
]lp              PHX
                 LDA   Score,X
                 AND   #$00FF
                 TYX
                 JSR   Print_2Digits
                 TXY
                 PLX
                 DEX
                 BNE   NoF
                 INC   Buf
NoF              BPL   ]lp
                 RTS

PrintTotal       STZ   Buf
                 LDY   #11+49*$A0+132
                 LDX   #1
]lp              PHX
                 LDA   Total,X
                 AND   #$00FF
                 TYX
                 JSR   Print_2Digits
                 TXY
                 PLX
                 DEX
                 BNE   NoF0
                 INC   Buf
NoF0             BPL   ]lp
                 RTS

PrintLevel       LDA   #1
                 STA   Buf
                 LDX   #11+29*$A0+140
                 LDA   Level
                 JSR   Print_2Digits
                 SEP   $30
                 LDA   LevelSpeed
                 PHA
                 AND   #$F0
                 LSR
                 LSR
                 LSR
                 LSR
                 JSR   Translate
                 STA   SP
                 PLA
                 AND   #$0F
                 JSR   Translate
                 STA   SP+1
                 REP   $30
                 LDX   #11+29*$A0+120
                 JSR   Print
SP               ASC   "??",00
                 RTS

Print_2Digits    PHA
                 AND   #$F0
                 BEQ   MaybeZero
                 INC   Buf
                 INC   Buf
                 LSR
                 LSR
                 LSR
                 LSR
                 CLC
                 ADC   #"0"
                 BRA   DrawR
MaybeZero        LDA   #"0"
                 LDY   Buf
                 CPY   #2
                 BCS   DrawR
PatchS0          LDA   #" "
DrawR            JSR   Print_Char
                 PLA
                 AND   #$0F
                 BEQ   MaybeZero0
                 INC   Buf
                 INC   Buf
                 CLC
                 ADC   #"0"
                 BRA   DrawL
MaybeZero0       LDA   #"0"
                 LDY   Buf
                 CPY   #1
                 BCS   DrawL
PatchS1          LDA   #" "
DrawL            JMP   Print_Char

ScorePerBrick    DA    $50                                     ; Bonus
                 DA    $100
                 DA    $150
                 DA    $200
                 DA    $250
                 DA    $300
                 DA    $350
                 DA    $500
                 DA    $500

Palette          HEX   0000F00099099900DD00630C960FA10B
                 HEX   E50F5E088F0BA401F9062A0D7C0FFF0F

ZTop             HEX   F2222222222222222220
ZTop0
ZMiddle
ZBottom0         HEX   21111111111111111110
ZBottom          HEX   00000000000000000000

PrintHiScore     LDX   #11+23*$A0+11
                 STZ   Pnt
]loop            PHX
                 LDA   Pnt
                 CLC
                 ADC   #HiScoreList
                 JSR   Print_Rout
                 LDA   #"."
                 STA   PatchS0+1
                 STA   PatchS1+1
                 JSR   Print_Char
                 STZ   Buf
                 LDA   Pnt
                 CLC
                 ADC   #HiScoreList+8
                 STA   Pnt+2
                 LDY   #2
]lp              PHY
                 LDA   (Pnt+2),Y
                 AND   #$00FF
                 JSR   Print_2Digits
                 PLY
                 DEY
                 BNE   NoF2
                 INC   Buf
NoF2             BPL   ]lp

                 PLA
                 CLC
                 ADC   #20*$A0
                 TAX
                 LDA   Pnt
                 CLC
                 ADC   #12
                 STA   Pnt
                 CMP   #8*12
                 BCC   ]loop
                 LDA   #" "
                 STA   PatchS0+1
                 STA   PatchS1+1
                 RTS

*------------------------------------------------- Routine de gestion
*                                                  des high-scores...

CheckHighScore   LDX   #12*7
]lp              LDA   Score+2
                 CMP   HiScoreList+10,X
                 BEQ   MoreCompare
                 BCS   FindNext
                 BRA   FoundLow
MoreCompare      LDA   Score
                 CMP   HiScoreList+8,X
                 BEQ   FoundLow
                 BCS   FindNext
FoundLow         CPX   #12*7
                 BNE   SomeHigh
                 SEC
                 RTS                                           ; NoHigh
FindNext         TXA
                 SEC
                 SBC   #12
                 TAX
                 BCS   ]lp
SomeHigh         TXA
                 CLC
                 ADC   #12
                 STA   Buf

                 LDX   #12*7
]lp2             CPX   Buf
                 BEQ   EndMove
                 PHX
                 LDY   #6
]lp              LDA   HiScoreList-12,X
                 STA   HiScoreList,X
                 INX
                 INX
                 DEY
                 BNE   ]lp
                 PLA
                 SEC
                 SBC   #12
                 TAX
                 BCS   ]lp2

EndMove          LDX   Buf
                 LDA   Score
                 STA   HiScoreList+8,X
                 LDA   Score+2
                 STA   HiScoreList+10,X

                 LDA   Buf
                 PHA

                 LDA   #130
                 STA   Lgn
                 LDA   #$36+3
                 STA   Col
                 LDA   #30
                 STA   ZNbLgn
                 LDA   #$2B+2
                 STA   ZNbCol
                 JSR   Window

                 LDX   #138*$A0+$38+4
                 JSR   Print
                 HEX   0CFF
                 TXT   "ENTER NAME",00;"VOTRE NOM:",00

                 SEP   $30
                 STL   $E1C010

                 LDX   #0
                 LDA   #" "
]lp              STA   NameAdr,X
                 INX
                 CPX   #7
                 BNE   ]lp
                 JSR   PrintName

                 STZ   Pnt

]reloop          STL   $E1C010

]loop            LDX   Pnt
                 LDA   #"#"
                 STA   NameAdr,X
                 JSR   PrintName

                 LDX   #12
]lp              LDL   $E1C000
                 BMI   KeyPress
                 JSR   WaitSync
                 DEX
                 BNE   ]lp

                 LDX   Pnt
                 LDA   #" "
                 STA   NameAdr,X
                 JSR   PrintName

                 LDX   #12
]lp              LDL   $E1C000
                 BMI   KeyPress
                 JSR   WaitSync
                 DEX
                 BNE   ]lp

                 BRA   ]loop

KeyPress         LDY   Pnt
                 CMP   #"M"&$9F
                 BEQ   NoName
                 CMP   #$9B
                 BEQ   NoName
                 CMP   #$FF
                 BEQ   Delete
                 CMP   #"H"&$9F
                 BEQ   Delete
NoDel            CPY   #7
                 BEQ   ]reloop
                 CMP   #" "
                 BCC   ]reloop
                 CMP   #"Z"+1
                 BCC   OkCar
                 SEC
                 SBC   #$20
OkCar            STA   NameAdr,Y
                 INC   Pnt
                 BRA   ]reloop

Delete           CPY   #0
                 BEQ   ]reloop
                 LDA   #" "
                 STA   NameAdr,Y
                 DEC   Pnt
                 BRA   ]reloop

NoName           LDY   Pnt
                 LDA   #" "
                 STA   NameAdr,Y

                 PLX
                 PLA                                           ; Empile sur 16bits

                 LDY   #0
]lp              LDA   NameAdr,Y
                 STA   HiScoreList,X
                 INY
                 INX
                 CPY   #7
                 BNE   ]lp

                 REP   $30
                 LDA   #$FFFF
                 STA   FlagHi
                 JSR   PrintHiScore
                 CLC
                 RTS

PrintName        PHP
                 REP   $30
                 LDX   #138+8*$A0+$38+4
                 JSR   Print
                 ASC   "<"
NameAdr          ASC   "#       "
                 ASC   ">",00
                 PLP
                 RTS

                 DO    vP8
                 ELSE
UserId           DS    2
MasterId         DS    2
                 FIN

*------------------------------------------------- Patterns et masques...

PatternList      DA    PatternList1
                 DA    PatternList2
                 DA    PatternList3
                 DA    PatternList4
                 DA    PatternList5
                 DA    0

MskList          DA    MskCarre
                 DA    MskRond
                 DA    MskCarre
                 DA    MskRondB
                 DA    MskCarre

MskCarre         DA    MskList0
                 DA    MskList1
                 DA    MskList2
                 DA    MskList3
                 DA    MskList4
                 DA    MskList5
                 DA    PatBlank

MskRond          DA    MskList0
                 DA    MskRond1
                 DA    MskRond2
                 DA    MskRond3
                 DA    MskRond4
                 DA    MskRond5
                 DA    PatBlank

MskRondB         DA    MskList0
                 DA    MskRondB1
                 DA    MskRondB2
                 DA    MskRondB3
                 DA    MskRondB4
                 DA    MskRondB5
                 DA    PatBlank


PatternList1     DA    PatBlank
                 DA    Pat0
                 DA    Pat1
                 DA    Pat2
                 DA    Pat3
                 DA    Pat4
                 DA    Pat5
                 DA    Blanc0

PatternList2     DA    PatBlank
                 DA    Ball0
                 DA    Ball1
                 DA    Ball2
                 DA    Ball3
                 DA    Ball4
                 DA    Ball5
                 DA    Blanc1

PatternList3     DA    PatBlank
                 DA    En0
                 DA    En1
                 DA    En2
                 DA    En3
                 DA    En4
                 DA    En5
                 DA    Blanc0

PatternList4     DA    PatBlank
                 DA    Tr0
                 DA    Tr1
                 DA    Tr2
                 DA    Tr3
                 DA    Tr4
                 DA    Tr5
                 DA    Blanc1


PatternList5     DA    PatBlank
                 DA    Le0
                 DA    Le1
                 DA    Le2
                 DA    Le3
                 DA    Le4
                 DA    Le5
                 DA    Blanc0

En0              HEX   DEEEEEEEEEED
                 HEX   0DDEEEEEEDD0
                 HEX   E0DDEEEEDD0E
                 HEX   EE0DDEEDD0ED
                 HEX   EEE0DDDD0EDD
                 HEX   EEDD0ED0DEDD
                 HEX   EDD0EEEE0DDD
                 HEX   ED0EEEEEE0DD
                 HEX   D0EEEEEEEE0D
                 HEX   0EEDDDDDDDE0
                 HEX   EDDDDDDDDDDD

En1              HEX   BCCCCCCCCCCB
                 HEX   0BBCCCCCCBB0
                 HEX   C0BBCCCCBB0C
                 HEX   CC0BBCCBB0CB
                 HEX   CCC0BBBB0CBB
                 HEX   CCBB0CB0BCBB
                 HEX   CBB0CCCC0BBB
                 HEX   CB0CCCCCC0BB
                 HEX   B0CCCCCCCC0B
                 HEX   0CCBBBBBBBC0
                 HEX   CBBBBBBBBBBB

En2              HEX   9AAAAAAAAAA9
                 HEX   099AAAAAA990
                 HEX   A099AAAA990A
                 HEX   AA099AA990A9
                 HEX   AAA099990A99
                 HEX   AA990A909A99
                 HEX   A990AAAA0999
                 HEX   A90AAAAAA099
                 HEX   90AAAAAAAA09
                 HEX   0AA9999999A0
                 HEX   A99999999999

En3              HEX   788888888887
                 HEX   077888888770
                 HEX   807788887708
                 HEX   880778877087
                 HEX   888077770877
                 HEX   887708707877
                 HEX   877088880777
                 HEX   870888888077
                 HEX   708888888807
                 HEX   088777777780
                 HEX   877777777777

En4              HEX   566666666665
                 HEX   055666666550
                 HEX   605566665506
                 HEX   660556655065
                 HEX   666055550655
                 HEX   665506505655
                 HEX   655066660555
                 HEX   650666666055
                 HEX   506666666605
                 HEX   066555555560
                 HEX   655555555555

En5              HEX   344444444443
                 HEX   033444444330
                 HEX   403344443304
                 HEX   440334433043
                 HEX   444033330433
                 HEX   443304303433
                 HEX   433044440333
                 HEX   430444444033
                 HEX   304444444403
                 HEX   044333333340
                 HEX   433333333333

Ball0            HEX   000DEEEED000
                 HEX   00EEFEEEEE00
                 HEX   0EEFFFEEDEE0
                 HEX   DEEEFEEEEDED
                 HEX   EEEEEEEEEDDE
                 HEX   EEEEEEEEEDDE
                 HEX   EDEEEEEEDDDE
                 HEX   DEDEEEEDDDED
                 HEX   0EDDDDDDDDE0
                 HEX   00EEDDDDEE00
                 HEX   000DEEEED000

Ball1            HEX   000BCCCCB000
                 HEX   00CCFCCCCC00
                 HEX   0CCFFFCCBCC0
                 HEX   BCCCFCCCCBCB
                 HEX   CCCCCCCCCBBC
                 HEX   CCCCCCCCCBBC
                 HEX   CBCCCCCCBBBC
                 HEX   BCBCCCCBBBCB
                 HEX   0CBBBBBBBBC0
                 HEX   00CCBBBBCC00
                 HEX   000BCCCCB000

Ball2            HEX   0009AAAA9000
                 HEX   00AAFAAAAA00
                 HEX   0AAFFFAA9AA0
                 HEX   9AAAFAAAA9A9
                 HEX   AAAAAAAAA99A
                 HEX   AAAAAAAAA99A
                 HEX   A9AAAAAA999A
                 HEX   9A9AAAA999A9
                 HEX   0A99999999A0
                 HEX   00AA9999AA00
                 HEX   0009AAAA9000

Ball3            HEX   000788887000
                 HEX   0088F8888800
                 HEX   088FFF887880
                 HEX   7888F8888787
                 HEX   888888888778
                 HEX   888888888778
                 HEX   878888887778
                 HEX   787888877787
                 HEX   087777777780
                 HEX   008877778800
                 HEX   000788887000

Blanc1           HEX   000FFFFFF000
                 HEX   00FFFFFFFF00
                 HEX   0FFFFFFFFFF0
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   0FFFFFFFFFF0
                 HEX   00FFFFFFFF00
                 HEX   000FFFFFF000

Ball4            HEX   000566665000
                 HEX   0066F6666600
                 HEX   066FFF665660
                 HEX   5666F6666565
                 HEX   666666666556
                 HEX   666666666556
                 HEX   656666665556
                 HEX   565666655565
                 HEX   065555555560
                 HEX   006655556600
                 HEX   000566665000

Ball5            HEX   000344443000
                 HEX   0044F4444400
                 HEX   044FFF443440
                 HEX   3444F4444343
                 HEX   444444444334
                 HEX   444444444334
                 HEX   434444443334
                 HEX   343444433343
                 HEX   043333333340
                 HEX   004433334400
                 HEX   000344443000

PatBlank         HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000

Pat0             HEX   EEEEEEEEEEEE
                 HEX   EEEEEEEEEEED
                 HEX   EEEEEEEEEEDD
                 HEX   EEEEEEEEEEDD
                 HEX   EEEEEEEEEEDD
                 HEX   EEEEEEEEEEDD
                 HEX   EEEEEEEEEEDD
                 HEX   EEEEEEEEEEDD
                 HEX   EEEEEEEEEEDD
                 HEX   EEDDDDDDDDED
                 HEX   EDDDDDDDDDDD

Pat1             HEX   CCCCCCCCCCCC
                 HEX   CCCCCCCCCCCB
                 HEX   CCCCCCCCCCBB
                 HEX   CCCCCCCCCCBB
                 HEX   CCCCCCCCCCBB
                 HEX   CCCCCCCCCCBB
                 HEX   CCCCCCCCCCBB
                 HEX   CCCCCCCCCCBB
                 HEX   CCCCCCCCCCBB
                 HEX   CCBBBBBBBBCB
                 HEX   CBBBBBBBBBBB

Pat2             HEX   AAAAAAAAAAAA
                 HEX   AAAAAAAAAAA9
                 HEX   AAAAAAAAAA99
                 HEX   AAAAAAAAAA99
                 HEX   AAAAAAAAAA99
                 HEX   AAAAAAAAAA99
                 HEX   AAAAAAAAAA99
                 HEX   AAAAAAAAAA99
                 HEX   AAAAAAAAAA99
                 HEX   AA99999999A9
                 HEX   A99999999999

Pat3             HEX   888888888888
                 HEX   888888888887
                 HEX   888888888877
                 HEX   888888888877
                 HEX   888888888877
                 HEX   888888888877
                 HEX   888888888877
                 HEX   888888888877
                 HEX   888888888877
                 HEX   887777777787
                 HEX   877777777777

Pat4             HEX   666666666666
                 HEX   666666666665
                 HEX   666666666655
                 HEX   666666666655
                 HEX   666666666655
                 HEX   666666666655
                 HEX   666666666655
                 HEX   666666666655
                 HEX   666666666655
                 HEX   665555555565
                 HEX   655555555555

Pat5             HEX   444444444444
                 HEX   444444444443
                 HEX   444444444433
                 HEX   444444444433
                 HEX   444444444433
                 HEX   444444444433
                 HEX   444444444433
                 HEX   444444444433
                 HEX   444444444433
                 HEX   443333333343
                 HEX   433333333333

Blanc0
MskList0         HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF

MskList1         HEX   000000000000
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   000000000000

MskList2         HEX   000000000000
                 HEX   000000000000
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   000000000000
                 HEX   000000000000

MskList3         HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000FFFFFF000
                 HEX   000FFFFFF000
                 HEX   000FFFFFF000
                 HEX   000FFFFFF000
                 HEX   000FFFFFF000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000

MskList4         HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   0000FFFF0000
                 HEX   0000FFFF0000
                 HEX   0000FFFF0000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000

MskList5         HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   00000FF00000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000

MskRond1         HEX   000000000000
                 HEX   0000FFFF0000
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   0FFFFFFFFFF0
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   0000FFFF0000
                 HEX   000000000000

MskRond2         HEX   000000000000
                 HEX   000000000000
                 HEX   0000FFFF0000
                 HEX   000FFFFFF000
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   00FFFFFFFF00
                 HEX   000FFFFFF000
                 HEX   0000FFFF0000
                 HEX   000000000000
                 HEX   000000000000

MskRond3         HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   0000FFFF0000
                 HEX   000FFFFFF000
                 HEX   000FFFFFF000
                 HEX   000FFFFFF000
                 HEX   0000FFFF0000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000

MskRond4         HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   00000FF00000
                 HEX   0000FFFF0000
                 HEX   00000FF00000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000

MskRond5         HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   00000FF00000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000


MskRondB1        HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFF00FFFFF
                 HEX   FFFF0000FFFF
                 HEX   FFFFF00FFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF

MskRondB2        HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFF00FFFFF
                 HEX   FFF000000FFF
                 HEX   FFF000000FFF
                 HEX   FFF000000FFF
                 HEX   FFFFF00FFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF

MskRondB3        HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFF00FFFFF
                 HEX   FFF000000FFF
                 HEX   FF00000000FF
                 HEX   FF00000000FF
                 HEX   FF00000000FF
                 HEX   FFF000000FFF
                 HEX   FFFF0000FFFF
                 HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFFF

MskRondB4        HEX   FFFFFFFFFFFF
                 HEX   FFFFF00FFFFF
                 HEX   FFF000000FFF
                 HEX   FF00000000FF
                 HEX   FF00000000FF
                 HEX   F0000000000F
                 HEX   FF00000000FF
                 HEX   FF00000000FF
                 HEX   FFF000000FFF
                 HEX   FFFFF00FFFFF
                 HEX   FFFFFFFFFFFF

MskRondB5        HEX   FFFF0000FFFF
                 HEX   FF00000000FF
                 HEX   F0000000000F
                 HEX   F0000000000F
                 HEX   000000000000
                 HEX   000000000000
                 HEX   000000000000
                 HEX   F0000000000F
                 HEX   F0000000000F
                 HEX   FF00000000FF
                 HEX   FFFF0000FFFF

Tr0              HEX   000DEEEED000
                 HEX   00EEEDDDEE00
                 HEX   0EFFEDDDDEE0
                 HEX   DEFEDDDDDEED
                 HEX   EEEDDDDDDEFE
                 HEX   EDDDDDDDDEFE
                 HEX   EDDDDDDDEFFE
                 HEX   DEDDDDDEFFED
                 HEX   0EDDEEFFFFE0
                 HEX   00EEFFFFEE00
                 HEX   000DEEEED000

Tr1              HEX   000BCCCCB000
                 HEX   00CCCBBBCC00
                 HEX   0CFFCBBBBCC0
                 HEX   BCFCBBBBBCCB
                 HEX   CCCBBBBBBCFC
                 HEX   CBBBBBBBBCFC
                 HEX   CBBBBBBBCFFC
                 HEX   BCBBBBBCFFCB
                 HEX   0CBBCCFFFFC0
                 HEX   00CCFFFFCC00
                 HEX   000BCCCCB000

Tr2              HEX   0009AAAA9000
                 HEX   00AAA999AA00
                 HEX   0AFFA9999AA0
                 HEX   9AFA99999AA9
                 HEX   AAA999999AFA
                 HEX   A99999999AFA
                 HEX   A9999999AFFA
                 HEX   9A99999AFFA9
                 HEX   0A99AAFFFFA0
                 HEX   00AAFFFFAA00
                 HEX   0009AAAA9000

Tr3              HEX   000788887000
                 HEX   008887778800
                 HEX   08FF87777880
                 HEX   78F877777887
                 HEX   8887777778F8
                 HEX   8777777778F8
                 HEX   877777778FF8
                 HEX   78777778FF87
                 HEX   087788FFFF80
                 HEX   0088FFFF8800
                 HEX   000788887000

Tr4              HEX   000566665000
                 HEX   006665556600
                 HEX   06FF65555660
                 HEX   56F655555665
                 HEX   6665555556F6
                 HEX   6555555556F6
                 HEX   655555556FF6
                 HEX   56555556FF65
                 HEX   065566FFFF60
                 HEX   0066FFFF6600
                 HEX   000566665000

Tr5              HEX   000344443000
                 HEX   004443334400
                 HEX   04FF43333440
                 HEX   34F433333443
                 HEX   4443333334F4
                 HEX   4333333334F4
                 HEX   433333334FF4
                 HEX   34333334FF43
                 HEX   043344FFFF40
                 HEX   0044FFFF4400
                 HEX   000344443000

Le0              HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFF2
                 HEX   FFFFFFFFFF22
                 HEX   FFFF2002FF22
                 HEX   FFF200002F22
                 HEX   FFF00FF00F22
                 HEX   FFF000000F22
                 HEX   FFF00FF00F22
                 HEX   FFFFFFFFFF22
                 HEX   FF22222222F2
                 HEX   F22222222222

Le1              HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFF2
                 HEX   FFFFFFFFFF22
                 HEX   FFF00000FF22
                 HEX   FFF002F20F22
                 HEX   FFF000002F22
                 HEX   FFF002F20F22
                 HEX   FFF00000FF22
                 HEX   FFFFFFFFFF22
                 HEX   FF22222222F2
                 HEX   F22222222222

Le2              HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFF2
                 HEX   FFFFFFFFFF22
                 HEX   FFF200002F22
                 HEX   FFF002FF0F22
                 HEX   FFF002FFFF22
                 HEX   FFF002FF0F22
                 HEX   FFF200002F22
                 HEX   FFFFFFFFFF22
                 HEX   FF22222222F2
                 HEX   F22222222222

Le3              HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFF2
                 HEX   FFFFFFFFFF22
                 HEX   FFF000002F22
                 HEX   FFF002F20F22
                 HEX   FFF002FF0F22
                 HEX   FFF002F20F22
                 HEX   FFF000002F22
                 HEX   FFFFFFFFFF22
                 HEX   FF22222222F2
                 HEX   F22222222222

Le4              HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFF2
                 HEX   FFFFFFFFFF22
                 HEX   FFF000000F22
                 HEX   FFF002FFFF22
                 HEX   FFF0000FFF22
                 HEX   FFF002FFFF22
                 HEX   FFF000000F22
                 HEX   FFFFFFFFFF22
                 HEX   FF22222222F2
                 HEX   F22222222222

Le5              HEX   FFFFFFFFFFFF
                 HEX   FFFFFFFFFFF2
                 HEX   FFFFFFFFFF22
                 HEX   FFF000000F22
                 HEX   FFF002FFFF22
                 HEX   FFF0000FFF22
                 HEX   FFF002FFFF22
                 HEX   FFF002FFFF22
                 HEX   FFFFFFFFFF22
                 HEX   FF22222222F2
                 HEX   F22222222222


*------------------------------------------------- Logo Beyond

BeyondLogo       HEX   87733828000000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   0000000000000000000000110FFFFFFF
                 HEX   FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                 HEX   FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                 HEX   FFFFF0110F0000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000F0110F000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   0000F0110F000EEEEEEEEEEEEEEEEEE0
                 HEX   CCCCCCCCCCCCC0E00C00EEEEEEEEEEEE
                 HEX   EEEEEEEE00A00EEEE000F0000F000EEE
                 HEX   EEEEEEEEEEEEEEE0CCCCCCCCCCCCC000
                 HEX   CCC00EEEEEEEEEEEEEEEEEE00AAA00EE
                 HEX   E000F0000F000EEEEEEEEEEEEEEEEEE0
                 HEX   CCCCCCCCCCCCC00CCCCC00EEEEEEEEEE
                 HEX   EEEEEE00AAAAA00EE000F0000F000EEE
                 HEX   EEEEEEEEEEEEEEE0CCCCCCCCCCCC00CC
                 HEX   CCCCC00EEEEEEEEEEEEEE00AAAAAAA00
                 HEX   E000F0000F000EEEEEEEEEEEEEEEEEE0
                 HEX   CCCCCCCCCCC00CCCCCCCCC00EEEEEEEE
                 HEX   EEEE00AAAAAAAAA00000F0000F000EEE
                 HEX   EEEEEEEEEEEEEEE0CCCCCCCCCC00CCCC
                 HEX   CCCCCCC00EEEEEEEEEE00AAAAAAAAAAA
                 HEX   0000F0000F000EEEEEEEEEEEEEEEEEE0
                 HEX   CCCCCCCCC00CCCCCCCCCCCCC00EEEEEE
                 HEX   EE00AAAAAAAAAAAAA000F0000F000EEE
                 HEX   EEEEEEEEEEEEEEE0CCCCCCCC000000CC
                 HEX   CCCCC000000EEEEEE000000AAAAAAA00
                 HEX   0000F0000F000EEEEEEEEEEEEEEEEEE0
                 HEX   CCCCCCCCCCCCC0CCCCCCC0EEEE00EEEE
                 HEX   EEEEEE0AAAAAAA0EE000F0000F000EEE
                 HEX   EEEEEEE000000000CCCCCCCCCCCCC0CC
                 HEX   CCCCC000000000000000000AAAAAAA00
                 HEX   0000F0000F000EEEEEEEEEE000000000
                 HEX   CCCCCCCCCCCCC0CCCCCCC0AAAA0E00AA
                 HEX   AAAAAA0AAAAAAA000000F0000F000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000EE00AAAAAAA0AAAAAAA00
                 HEX   0000F0000F000EEEEEEEEEEEEEEEEEEE
                 HEX   EEEEEEEEEEEEEEEEEEEEEEEEEEEEEE00
                 HEX   AAAAAA0AAAAAAA000000F0000F000EEE
                 HEX   EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
                 HEX   EEEEEEEEEEEEEEE00AAAAA0AAAAAAA00
                 HEX   0000F0000F000EEEEEEEEEEEEEEEEEEE
                 HEX   EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
                 HEX   00AAAA0AAAAAAA000000F0000F000EEE
                 HEX   EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
                 HEX   EEEEEEEEEEEEEEEEE00AAA0AAAAAAA00
                 HEX   0000F0000F000EEEEEEEEEEEEEEEEEEE
                 HEX   EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
                 HEX   0000AA0AAAAAAA000000F0000F000EEE
                 HEX   EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
                 HEX   EEEEEEEEEEEEEEE000000A0AAAAAAA0A
                 HEX   0000F0000F000EEEEEEEEEEEEEEEEEEE
                 HEX   EEEEEEEEEEEEEEEEEEEEEEEEEEEEEE00
                 HEX   0000000AAAAAAA0AA000F0000F000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000EE0000000000AAAAAAA0A
                 HEX   A000F0000F000EEEEEEEEEE000000000
                 HEX   CCCCCCCCCCCCC0CCCCCCC0AAAA0E00A0
                 HEX   0000000AAAAAAA0AA000F0000F000EEE
                 HEX   EEEEEEE000000000CCCCCCCCCCCCC0CC
                 HEX   CCCCC0AAAA000AA00000000AAAAAAA0A
                 HEX   A000F0000F000EEEEEEEEEE000000000
                 HEX   CCCCCCCCCCCCC0CCCCCCC0AAAA00AAA0
                 HEX   0000000AAAAAAA0AA000F0000F000EEE
                 HEX   EEEEEEE000000000CCCCCCCCCCCCC0CC
                 HEX   CCCCC0AAAA0AAAA00000000AAAAAAAAA
                 HEX   A000F0000F000EEEEEEEEEE000000000
                 HEX   CCCCCCCCCCCC000CCCCCC0AAAAAAAAA0
                 HEX   0000000AAAAAAAAAA000F0000F000EEE
                 HEX   EEEEEEE000000000CCCCCCCCCCCCCCCC
                 HEX   CCCCC0AAAAAAAAA00000000AAAAAAAAA
                 HEX   A000F0000F000EEEEEEEEEE000000000
                 HEX   CCCCCCCCCCCCCCCCCCCCC0AAAAAAAAA0
                 HEX   0000000AAAAAAAAAA000F0000F000EEE
                 HEX   EEEEEEE000000000BCCCCCCCCCCCCCCC
                 HEX   CCCCB0AAAAAAAAA00000000AAAAAAAAA
                 HEX   A000F0000F000EEEEEEEEEE000000000
                 HEX   0CCCCCCCCCCCCCCCCCCC09AAAAAAAAA0
                 HEX   0000000AAAAAAAAA9000F0000F000EEE
                 HEX   EEEEEEE00000000000CCCCCCCCCCCCCC
                 HEX   CCC09AAAAAAAAAA00000000AAAAAAAAA
                 HEX   0000F0000F000EEEEEEEEEE000000000
                 HEX   000BCCCCCCCCCCCCCB09AAAAAAAAAAA0
                 HEX   0000000AAAAAAAA00000F0000F000EEE
                 HEX   EEEEEEE00000000000000BCCCCCCCCCB
                 HEX   09AAAAAAAAAAAAA00000000AAAAAA900
                 HEX   0000F0000F0000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000F0000F000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   0000F0000F000F2222222220F2222222
                 HEX   0F22200000F2220F220F222000F220F2
                 HEX   220F220F222222222000F0000F000200
                 HEX   00000020200000020200200000200202
                 HEX   02020002020020200022020200000000
                 HEX   2000F0000F0002222222222022222202
                 HEX   02002000002222020202222020202022
                 HEX   22020202222222222000F0000F000000
                 HEX   00000000000002020200200000000002
                 HEX   02000002022020000020020000000000
                 HEX   0000F0000F000F2222200000F2220202
                 HEX   0200200000F22202020F2220202020F2
                 HEX   2202020F222222222000F0000F000200
                 HEX   00200000200202020200200000200202
                 HEX   02020020002020200202020200000000
                 HEX   2000F0000F0002000020000020020202
                 HEX   02002000002002020202002000202020
                 HEX   02020202222220002000F0000F000200
                 HEX   00200000200202020200200000200202
                 HEX   02020020002020200202020000002000
                 HEX   2000F0000F0002000022222020022F02
                 HEX   020022222020022F0202002000202020
                 HEX   0202020F2222F0002000F0000F000200
                 HEX   00000020200000020200000020200000
                 HEX   02020020002020200202020200000000
                 HEX   2000F0000F0002000000002020000002
                 HEX   02000000202000000202002000202020
                 HEX   02020202000000002000F0000F000222
                 HEX   22222220222222220222222220222222
                 HEX   22022220002220222202220222222222
                 HEX   2000F0000F0000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000F0000F000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   0000F0000FFFFFFFFFFFFFFFFFFFFFFF
                 HEX   FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                 HEX   FFFFFFFFFFFFFFFFFFFFF00000000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000111100000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000000011110000
                 HEX   00000000000000000000000000000000
                 HEX   00000000000000000000000000000000
                 HEX   00000000

*------------------------------------------------- Scores...

SignatureTest    DS    8
Signature        ASC   "BeyondGS"

HiScoreList      TXT   "HULK   ",00;"OLIVIER",00
                 ADRL  $00010000
                 TXT   "EARTH  ",00;"J-YVES ",00
                 ADRL  $00009000
                 TXT   "BUSH   ",00;"BERNARD",00
                 ADRL  $00008000
                 TXT   "AXE    ",00;"ERIC   ",00
                 ADRL  $00007000
                 TXT   "PERFECT",00;"HUBERT ",00
                 ADRL  $00006000
                 TXT   "POWERS ",00;"J-LUC  ",00
                 ADRL  $00005000
                 TXT   "TUGBOAT",00;"YVAN   ",00
                 ADRL  $00004000
                 TXT   "DINO   ",00;"EMILE  ",00
                 ADRL  $00000001


                 DO    vP8
                 ELSE
                 MX    %00
PgmDeath         PHA
                 PEA   ^DeathMsg
                 PEA   DeathMsg
                 LDX   #$1503
                 JSL   $E10000

DeathMsg         STR   'Beyond Colums Fatal Error :$'
                 FIN

                 DS    \

                 DO    vP8
BufIO            =     *
PathName         =     *+$400
                 FIN

