#include <LiquidCrystal.h>
#include "LedControl.h"

// Ghita Alexandru - grupa 253 - grupa marti

LedControl lc = LedControl(12, 11, 10, 1);  //Variabila de tip matrice 8x8
LiquidCrystal lcd(13, 8, 5, 4, 3, 2); //Variabila lcd

const short int joyPinX = A0; //Pin Joystick Ox
const short int joyPinY = A1; //Pin Joystick Oy
const short int joyPinClk = 7;  //Pin Joystick Click
const short int lcdVo = 9;  //Pin V0 lcd
const short int buzzerPin = 6; //Pin pentru buzzer
short int valueX = 0; //Valoarea pe Ox
short int valueY = 0; //Valoarea pe Oy
short int joyClk = 0, joyDefaultClk = 1;  //Valoarea Click si valoarea default (pentru a evita continous click)
short int change = 0; //Variabila de setare a jocului activ
short int joyDirection = 0, joyDirectionDefault = 4, menuSpot = 0;  //Valoarea joystickului, valoarea default, si pozitia in meniu
unsigned long previousTime = 0; //Timpul precedent (evitarea delay-ului)
short int loadingPosition = 0;  //Pozitia pentru functia de loading
const String menuPrincipal[4] = {"Choose", "Snake ", "Frogger ", "Space Ship "};  //Meniul principal pentru alegerea jocului
boolean reseter = true; //Variabila ce determina repornirea jocului ca in stagiul initial (cazul pierderii jocului, nefiind nevoie de memorarea unui highscore sau altele)
void *menuFocus = NULL; //Pointerul catre meniul jocului

void loadingGeneral() //Loading pentru matrice in timpul meniului dintre jocuri
{
  lc.clearDisplay(0);
  //Coordonatele pe matrice a loadingului: primele 20 sunt pentru cerc, apoi cate sase pozitiile limbii in cele 8 directii
  short int loadingShowColumn[] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 7, 7, 1, 1, 2, 2, 3, 3, 1, 2, 2, 3, 3, 4, 3, 3, 3, 4, 4, 4, 3, 4, 4, 5, 5, 6, 4, 4, 5, 5, 6, 6, 3, 4, 4, 5, 5, 6, 3, 3, 3, 4, 4, 4, 1, 2, 2, 3, 3, 4};
  short int loadingShowRow[] = {2, 3, 4, 5, 1, 6, 0, 7, 0, 7, 0, 7, 0, 7, 1, 6, 2, 3, 4, 5, 3, 4, 3, 4, 3, 4, 2, 1, 3, 2, 4, 3, 1, 2, 3, 1, 2, 3, 3, 4, 2, 3, 1, 2, 4, 3, 4, 3, 4, 3, 4, 3, 5, 4, 6, 5, 4, 5, 6, 4, 5, 6, 5, 4, 6, 3, 5, 4};
  //Aprinderea loadingului conform coordonatelor
  for (int i = 0; i < 20; i++)
    lc.setLed(0, loadingShowColumn[i], loadingShowRow[i], true);
  for (int i = 0; i < 6; i ++)
    lc.setLed(0, loadingShowColumn[20 + i + 6 * loadingPosition], loadingShowRow[20 + i + 6 * loadingPosition], true);
  loadingPosition++;
  //La depasirea numarului de directii se reseteaza directia limbii ceasului
  if (loadingPosition > 7)
   loadingPosition = 0;
  switch(loadingPosition)
  {
    case 0:
    {
    tone(buzzerPin, 500, 200);
    delay(200);
    noTone(buzzerPin);
      break;
    }
    case 1:
    {
    tone(buzzerPin, 3000, 200);
    delay(200);
    noTone(buzzerPin);
      break;
    }
    case 2:
    {
    tone(buzzerPin, 1000, 200);
    delay(200);
    noTone(buzzerPin);
      break;
    }
    case 3:
    {
    tone(buzzerPin, 3500, 200);
    delay(200);
    noTone(buzzerPin);
      break;
    }
    case 4:
    {
    tone(buzzerPin, 500, 200);
    delay(200);
    noTone(buzzerPin);
      break;
    }
    case 5:
    {
    tone(buzzerPin, 3000, 200);
    delay(200);
    noTone(buzzerPin);
      break;
    }
    case 6:
    {
    tone(buzzerPin, 1000, 200);
    delay(200);
    noTone(buzzerPin);
      break;
    }
    case 7:
    {
    tone(buzzerPin, 3500, 200);
    delay(200);
    noTone(buzzerPin);
      break;
    }
  }
}

void launchLoadingGeneral() //Lansarea loadingului din 500 in 500 de milisecunde fara blocarea programului
{
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= 500)
  {
    previousTime = currentTime;
    loadingGeneral();
  }
}

void winOrLose(boolean winLose) //Win or lose afisare pe matricea de 8x8
{
  lc.clearDisplay(0);
  if (winLose == true)
  { //Coordonatele pe matrice a textului "WIN" si aprinderea lor
    short int winColumn[] = {0, 1, 2, 3, 2, 1, 0, 0, 1, 2, 3, 2, 1, 0, 7, 6, 5, 4, 4, 5, 6, 7, 7, 6, 5, 4, 5, 6, 7, 6, 5, 4};
    short int winRow[] = {7, 7, 6, 5, 4, 4, 4, 3, 3, 3, 2, 1, 0, 0, 6, 6, 6, 6, 5, 5, 5, 5, 3, 3, 3, 3, 2, 1, 0, 0, 0, 0};
    for (int i = 0; i < 32; i++)
      lc.setLed(0, winColumn[i], winRow[i], true);
    tone(buzzerPin, 500, 100);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 2000, 100);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 3500, 300);
    delay(300);
    noTone(buzzerPin);
  }
  else
  { //Coordonatele pe matrice a textului "LOSE" si aprinderea lor
    short int loseColumn[] = {0, 1, 2, 2, 2, 0, 0, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5, 6, 7, 7, 7, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7};
    short int loseRow[] = {7, 7, 7, 6, 5, 2, 3, 1, 4, 2, 3, 5, 6, 4, 7, 6, 5, 4, 5, 6, 7, 0, 1, 2, 2, 0, 1, 2, 2, 0, 1, 2};
    for (int i = 0; i < 32; i++)
      lc.setLed(0, loseColumn[i], loseRow[i], true);
    tone(buzzerPin, 3500, 100);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 2000, 100);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 500, 300);
    delay(300);
    noTone(buzzerPin);
  }
}

class snakeBody //Corpul Snake-ului (lista simplu inlantuita)
{
  private:  //Coordonatele bucatii de corp si adresa urmatoarei bucati de corp
    short int bodyColumn, bodyRow;
    snakeBody *nextPart;
  public:
    snakeBody();  //Initializator fara parametri pentru crearea initiala la inceperea jocului
    snakeBody(int, int);  //Alocarea coordonatelor urmatoarului cap al snake-ului si aprinderea ledului respectiv
    int snakeBodyColumn(); //Obtinerea coordonatei de coloana a bucatii respective din corp
    int snakeBodyRow(); //Obtinerea coordonatei de rand a bucatii respective din corp
    snakeBody* newBody(int, int, boolean);  //Crearea noului cap al snake-ului si conectarea lui cu retul corpului
    boolean safeCheck(short int, short int);  //Verifica daca coordonatele respective sunt pe corp sau nu
};

snakeBody::snakeBody() //Initializarea snake-ului (incepand cu 3 bucati de corp)
{
  bodyColumn = 4;
  bodyRow = 3;
  lc.setLed(0, 4, 3, true);
  nextPart = new snakeBody(5, 3);
  nextPart->nextPart = new snakeBody(6, 3);
}

snakeBody::snakeBody(int collumn, int row)  //Initializarea unei bucati de corp cu anumite coordonate, aprinderea pe matrice si conexiune la NULL
{
  bodyColumn = collumn;
  bodyRow = row;
  lc.setLed(0, collumn, row, true);
  nextPart = NULL;
}

int snakeBody::snakeBodyColumn() //Obtinerea coordonatei de coloana a bucatii respective din corp
{
  return bodyColumn;
}

int snakeBody::snakeBodyRow() //Obtinerea coordonatei de rand a bucatii respective din corp
{
  return bodyRow;
}

snakeBody* snakeBody::newBody(int collumn, int row, boolean biggerSnake)  //Crearea noului cap al snake-ului si conectarea lui cu retul corpului
{
  snakeBody *aux = new snakeBody(collumn, row); //Crearea unei variabile care reprezinta noul cap
  snakeBody *returner = aux;  //Crearea unei copii care reprezinta noul cap
  aux -> nextPart = this; //Conexiunea intre noul cap si vechiul cap
  if (biggerSnake == false) //Conditia daca nu a mancat un gold si stergem coada
  {
    while (aux->nextPart->nextPart != NULL)
      aux = aux->nextPart;
    snakeBody *deleter = aux->nextPart;
    aux->nextPart = NULL;
    lc.setLed(0, deleter->bodyColumn, deleter->bodyRow, false);
    delete deleter;
  }
  return returner;  //noul cap este returnat pentru a modifica in variabila de tip snake (see line 257, 268)
}

boolean snakeBody::safeCheck(short int nextColumn, short int nextRow)  //Verifica daca coordonatele respective sunt pe corp sau nu
{
  snakeBody *aux = this;
  while (aux != NULL)
  {
    if (nextColumn == aux->bodyColumn && nextRow == aux->bodyRow)
      return false; //Daca coordonatele corespund oricarei bucati din corp atunci returnam fals
    aux = aux->nextPart;
  }
  return true;
}

class snake //Clasa snake care contine meniu, gameplay si un pointer catre capul corpului
{
  private:
    int gold, difficulty, goldColumn, goldRow, snakeSize;  //Numarul de gold mancat, dificultatea, coordonatele goldului, dimensiunea snake-ului
    snakeBody *body;  //Pointer catre capul corpului
    short int defaultDirection; //Directia antecedenta a corpului
    boolean wall, inGame; //Daca exista coliziune cu ziduri sau nu si daca este in joc sau in meniul jocului
    String menu[6]; //Meniul jocului
  public:
    snake();  //Initializarea jocului
    void movement(int directionSnake);  //Miscarea corpului
    void menuShow();  //Afisarea meniului si apelarea functilor de joc necesare pentru jocul propriu-zis
};

snake::snake()  //Initializarea jocului
{
  lc.clearDisplay(0);
  gold = 0;
  goldColumn = -1;
  goldRow = -1;
  snakeSize = 3;
  difficulty = 1;
  defaultDirection = 2;
  inGame = false;
  wall = false;
  menu[0] = "Snake";
  menu[1] = "New Game";
  menu[2] = "Difficulty ";
  menu[3] = "Wall ";
  menu[4] = "Exit ";
  menu[5] = "Score: ";
  body = new snakeBody;
}

void snake::movement(int directionSnake)  //Miscarea corpului
{
  short int nextRow, nextColumn; //Coordonatele urmatoarei pozitii a capului snake-ului
  if (snakeSize == 51)  //Decizia de castig (80% din spatiul de joc)
  {
    winOrLose(true);
    joyClk = 1;
    delay(300);
    while (joyClk == 1)
      joyClk = digitalRead(joyPinClk);
    inGame = false;
    reseter = true;
    joyDirectionDefault = 3;
  }
  switch (directionSnake) //Calcularea urmatoarelor coordonate ale capului snake-ului in functie de directie
  {
    case 1:
      {
        nextRow = body->snakeBodyRow() - 1;
        nextColumn = body->snakeBodyColumn();
        break;
      }
    case -1:
      {
        nextRow = body->snakeBodyRow() + 1;
        nextColumn = body->snakeBodyColumn();
        break;
      }
    case 2:
      {
        nextRow = body->snakeBodyRow();
        nextColumn = body->snakeBodyColumn() - 1;
        break;
      }
    case -2:
      {
        nextRow = body->snakeBodyRow();
        nextColumn = body->snakeBodyColumn() + 1;
        break;
      }
  }
  if (goldColumn == -1 && goldRow == -1) //Daca nu avem gold pe matrice ne atribuim random unul pe matrice verificand sa nu il punem pe snake si il aprindem
  {
    goldColumn = body->snakeBodyColumn();
    goldRow = body->snakeBodyRow();
    while (body->safeCheck(goldColumn, goldRow) == false)
    {
      goldColumn = random(7);
      goldRow = random(7);
    }
    lc.setLed(0, goldColumn, goldRow, true);
  }

  if (wall == true) //Daca snake-ul intersecteaza zidul si coliziunea este activa pierde
  {
    if (nextRow == 8 || nextRow == -1 || nextColumn == 8 || nextColumn == -1)
    {
      winOrLose(false);
      joyClk = 1;
      delay(300);
      while (joyClk == 1)
        joyClk = digitalRead(joyPinClk);
      inGame = false;
      reseter = true;
      joyDirectionDefault = 3;
    }
  }
  else
  { //Daca intersecteaza un zid si zidul este dezactivat atunci parcurge pe partea cealalta a matricii
    if (nextRow == 8)
      nextRow = 0;
    else if (nextRow == -1)
      nextRow = 7;
    else if (nextColumn == 8)
      nextColumn = 0;
    if (nextColumn == -1)
      nextColumn = 7;
  }

  if (body->safeCheck(nextColumn, nextRow) == true)  //Daca este in siguranta locul urmator
  {
    if (goldColumn == nextColumn && goldRow == nextRow) //Daca este gold locul urmator creeam noul cap peste gold si resetam coordonatele goldului
    {
      body = body->newBody(nextColumn, nextRow, true);
      goldColumn = -1;
      goldRow = -1;
      gold++;
      snakeSize++;
      tone(buzzerPin, 3500, 50);
      delay(50);
      noTone(buzzerPin);
    }
    else
      body = body->newBody(nextColumn, nextRow, false);  //Doar creeam noul cap eliminand coada
  }
  else
  { //Nu este in siguranta noua locatie (se intersecteaza cu propriul corp) si player-ul pierde
    winOrLose(false);
    joyClk = 1;
    delay(300);
    while (joyClk == 1)
      joyClk = digitalRead(joyPinClk);
    inGame = false;
    reseter = true;
    joyDirectionDefault = 3;
  }
}

void snake::menuShow()  //Afisarea meniului si apelarea functilor de joc necesare pentru jocul propriu-zis
{
  if (inGame == true) //Daca player-ul se afla in joc si nu in meniu
  { //Afisam scorul calculat live
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(menu[5]);
    lcd.setCursor(0, 1);
    lcd.print((int)(10 * gold * difficulty * ((wall == false) ? 1 : 1.5)));
    if (joyDirection != joyDirectionDefault)  //Daca player-ul ii da un input diferit de cel anterior
    {
      joyDirectionDefault = joyDirection;
      if (joyDirection + defaultDirection == 0 || joyDirection == 0)  //Se proceseaza input-ul si se apeleaza daca directia este valida
      {
        this->movement(defaultDirection);
      }
      else
      {
        this->movement(joyDirection);
        defaultDirection = joyDirection;
      }
      delay(100 * (4 - difficulty));  //timer-ul de repaus pentru o miscare vizibila (folosim delay pentru ca nu trebuie sa se intample altceva in timpul respectiv)
    } else  //Daca nu primeste input diferit de anterior sau 0, jocul va continua pe ultima directie valida
    {
      this->movement(defaultDirection);
      delay(100 * (4 - difficulty));  //timer-ul de repaus pentru o miscare vizibila (folosim delay pentru ca nu trebuie sa se intample altceva in timpul respectiv)
    }
  }
  else
  { //Daca player-ul nu se afla in jocul propriu-zis, ci se afla in meniu
    if (joyDirection != joyDirectionDefault)
    { //Daca player-ul executa un input de directie (se deplaseaza in meniu), reafisam meniul in mod corespunzator noii locatii (cu verificarea sa nu iasa din meniu)
      joyDirectionDefault = joyDirection;
      if (joyDirection == 2 || joyDirection == -2)
        menuSpot -= joyDirection / 2;
      if (menuSpot < 0)
        menuSpot = 0;
      if (menuSpot > 3)
        menuSpot = 3;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(menu[menuSpot]);
      if (menuSpot == 2)
        lcd.print(difficulty);
      if (menuSpot == 3)
        lcd.print(wall == false ? "OFF" : "ON");
      lcd.setCursor(0, 1);
      lcd.print(menu[menuSpot + 1]);
      if (menuSpot == 1)
        lcd.print(difficulty);
      if (menuSpot == 2)
        lcd.print(wall == false ? "OFF" : "ON");
      lcd.print(" <");
    }
    if (joyClk != joyDefaultClk)
    { //Daca player-ul da click actionam in mod corespunzator
      joyDefaultClk = joyClk;
      if (joyClk == 0)
      {
        switch (menuSpot)
        {
          case 0:
            { // Intram in jocul propriu-zis
              inGame = true;
              break;
            }
          case 1:
            { //Modificam dificultatea
              difficulty++;
              if (difficulty > 3)
                difficulty = 1;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(menu[menuSpot]);
              if (menuSpot == 2)
                lcd.print(difficulty);
              if (menuSpot == 3)
                lcd.print(wall == false ? "OFF" : "ON");
              lcd.setCursor(0, 1);
              lcd.print(menu[menuSpot + 1]);
              if (menuSpot == 1)
                lcd.print(difficulty);
              if (menuSpot == 2)
                lcd.print(wall == false ? "OFF" : "ON");
              lcd.print(" <");
              break;
            }
          case 2:
            { //Modifica activarea sau dezactivarea zidului
              wall = (wall == false) ? true : false;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(menu[menuSpot]);
              if (menuSpot == 2)
                lcd.print(difficulty);
              if (menuSpot == 3)
                lcd.print(wall == false ? "OFF" : "ON");
              lcd.setCursor(0, 1);
              lcd.print(menu[menuSpot + 1]);
              if (menuSpot == 1)
                lcd.print(difficulty);
              if (menuSpot == 2)
                lcd.print(wall == false ? "OFF" : "ON");
              lcd.print(" <");
              break;
            }
          case 3:
            { //Iese din meniul jocului si se intoarce la meniul principal
              change = 0;
              menuSpot = 0;
              delete menuFocus;
              menuFocus = NULL;
              joyDirectionDefault = 3;
            }
        }
        delay(300);
      }
    }
  }
}

class frogger //Clasa frogger care contine meniu si gameplay
{
  private:
    unsigned long travelingBodiesTimes[7]; //Timp previous pentru fiecare linie
    short int travelingBodies[6][8]; //Pozitionarea corpurilor care trebuiesc depasite
    short int froggerBodyColumn, froggerBodyRow; //Coordonatele coloana si rand pentru player
    short int difficulty, level, defaultLevel, defaultLives, lives, levelFinish;  //Dificultate, level si vieti si defaulturile lor, conditionarea de terminare a level-ului
    String menu[6]; //Meniu
    boolean inGame; //Daca este in joc sau nu
  public:
    frogger();  //Initializator joc
    void menuShow();  //Afiseaza meniului si actioneaza gameplay-ul necesar
    void game();  //Miscarea corpurilor
    void froggerMovement(); //Miscarea player-ului
    boolean safeCheck();  //Coliziunea intre player si corpurile ce traverseaza
};

frogger::frogger()  //Initializator joc
{
  lc.clearDisplay(0);
  froggerBodyColumn = 7;
  froggerBodyRow = 3;
  level = 1;
  lives = 3;
  defaultLevel = -1;
  defaultLives = -1;
  levelFinish = 0;
  difficulty = 1;
  menu[0] = "Frogger ";
  menu[1] = "New Game ";
  menu[2] = "Difficulty ";
  menu[3] = "Exit ";
  menu[4] = "Level: ";
  menu[5] = "Lives: ";
  //Modelele de corpuri si timpurile lor de start
  {
    travelingBodies[5][0] = travelingBodies[5][1] = travelingBodies[5][5] = travelingBodies[5][6] = 1;
    travelingBodies[5][2] = travelingBodies[5][3] = travelingBodies[5][4] = travelingBodies[5][7] = 0;
    travelingBodiesTimes[5] = 0;

    travelingBodies[3][0] = travelingBodies[3][1] = travelingBodies[3][4] = travelingBodies[3][5] = 1;
    travelingBodies[3][2] = travelingBodies[3][3] = travelingBodies[3][6] = travelingBodies[3][7] = 0;
    travelingBodiesTimes[3] = 0;

    travelingBodies[0][0] = travelingBodies[0][1] = travelingBodies[0][4] = travelingBodies[0][5] = travelingBodies[0][6] = travelingBodies[0][7] = 1;
    travelingBodies[0][2] = travelingBodies[0][3] =  0;
    travelingBodiesTimes[0] = 0;

    travelingBodies[2][0] = travelingBodies[2][1] = travelingBodies[2][2] = 1;
    travelingBodies[2][3] = travelingBodies[2][4] = travelingBodies[2][5] = travelingBodies[2][6] = travelingBodies[2][7] = 0;
    travelingBodiesTimes[2] = 0;

    travelingBodies[1][0] = travelingBodies[1][2] = travelingBodies[1][4] = travelingBodies[1][6] = 1;
    travelingBodies[1][1] = travelingBodies[1][3] = travelingBodies[1][5] = travelingBodies[1][7] = 0;
    travelingBodiesTimes[1] = 0;

    travelingBodies[4][0] = travelingBodies[4][1] = travelingBodies[4][4] = travelingBodies[4][5] = 1;
    travelingBodies[4][2] = travelingBodies[4][3] = travelingBodies[4][6] = travelingBodies[4][7] = 0;
    travelingBodiesTimes[4] = 0;
  }
  travelingBodiesTimes[6] = 0;
  inGame = false;
  lc.setLed(0, 7, 3, true);
}

void frogger::menuShow()  //Afiseaza meniului si actioneaza gameplay-ul necesar
{
  if (inGame == true) //In jocul propriu-zis
  {
    if (defaultLives != lives || defaultLevel != level) //Se rescriu pe lcd vietile si level-ul doar la schimbarea uneia din cele 2 mentionate
    {
      defaultLives = lives;
      defaultLevel = level;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(menu[4]);
      lcd.print(level);
      lcd.setCursor(0, 1);
      lcd.print(menu[5]);
      for (int i = 0; i < 3; i++)
        lcd.print(i < lives ? "1 " : "0 ");
    }
    if (joyDirection != joyDirectionDefault)  //Miscarea player-ului
    {
      joyDirectionDefault = joyDirection;
      froggerMovement();
    }
    game(); //Miscarea corpurilor
    if (safeCheck() == false && lives > 0) //Verificarea coliziunii intre player si corpuri si scaderea de vieti in cazul in care mai are
    {
      lives--;
      levelFinish = 0;
      froggerBodyColumn = 7;
      froggerBodyRow = 3;
      lc.setLed(0, froggerBodyColumn, froggerBodyRow, true);
      tone(buzzerPin,3500,200);
      delay(200);
      noTone(buzzerPin);
    }
    if (lives == 0) //Pierderea jocului si resetarea jocului dupa input de la player
    {
      winOrLose(false);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(menu[4]);
      lcd.print(level);
      lcd.setCursor(0, 1);
      lcd.print(menu[5]);
      for (int i = 0; i < 3; i++)
        lcd.print(i < lives ? "1 " : "0 ");
      while (joyClk == 1)
      {
        joyClk = digitalRead(joyPinClk);
      }
      inGame = false;
      reseter = true;
      joyDirectionDefault = 3;
    }
  }
  else
  { //Afisarea meniului de la joc (analog meniu snake)
    if (joyDirection != joyDirectionDefault)
    {
      joyDirectionDefault = joyDirection;
      if (joyDirection == 2 || joyDirection == -2)
        menuSpot -= joyDirection / 2;
      if (menuSpot < 0)
        menuSpot = 0;
      if (menuSpot > 2)
        menuSpot = 2;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(menu[menuSpot]);
      if (menuSpot == 2)
        lcd.print(difficulty);
      lcd.setCursor(0, 1);
      lcd.print(menu[menuSpot + 1]);
      if (menuSpot == 1)
        lcd.print(difficulty);
      lcd.print(" <");
    }
    if (joyClk != joyDefaultClk)
    {
      joyDefaultClk = joyClk;
      if (joyClk == 0)
      {
        switch (menuSpot)
        {
          case 0:
            {
              inGame = true;
              break;
            }
          case 1:
            {
              difficulty++;
              if (difficulty > 3)
                difficulty = 1;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(menu[menuSpot]);
              lcd.setCursor(0, 1);
              lcd.print(menu[menuSpot + 1]);
              lcd.print(difficulty);
              lcd.print(" <");
              break;
            }
          case 2:
            {
              change = 0;
              menuSpot = 0;
              delete menuFocus;
              menuFocus = NULL;
              joyDirectionDefault = 3;
            }
        }
        delay(300);
      }
    }
  }
}

void frogger::game()  //Miscarea corpurilor in conformitate cu anumiti timpi
{
  unsigned long currentTime = millis();
  if (level == 1)
  {
    if (currentTime - travelingBodiesTimes[0] > 750 - difficulty * 50)
    {
      travelingBodiesTimes[0] = currentTime;
      short int aux = travelingBodies[0][0];
      for (int i = 0; i < 8; i++)
        lc.setLed(0, 1, i, false);
      for (int i = 0; i < 7; i++)
        travelingBodies[0][i] = travelingBodies[0][i + 1];
      travelingBodies[0][7] = aux;
      for (int i = 0; i < 8; i++)
        lc.setLed(0, 1, i, travelingBodies[0][i] == 1 ? true : false);
      if (froggerBodyColumn == 1)
        lc.setLed(0, froggerBodyColumn, froggerBodyRow, true);
    }
    if (currentTime - travelingBodiesTimes[2] > 250 - difficulty * 50)
    {
      travelingBodiesTimes[2] = currentTime;
      short int aux = travelingBodies[2][0];
      for (int i = 0; i < 8; i++)
        lc.setLed(0, 3, i, false);
      for (int i = 0; i < 7; i++)
        travelingBodies[2][i] = travelingBodies[2][i + 1];
      travelingBodies[2][7] = aux;
      for (int i = 0; i < 8; i++)
        lc.setLed(0, 3, i, travelingBodies[2][i] == 1 ? true : false);
      if (froggerBodyColumn == 3)
        lc.setLed(0, froggerBodyColumn, froggerBodyRow, true);
    }
    if (currentTime - travelingBodiesTimes[4] > 500 - difficulty * 50)
    {
      travelingBodiesTimes[4] = currentTime;
      short int aux = travelingBodies[4][7];
      for (int i = 0; i < 8; i++)
        lc.setLed(0, 5, i, false);
      for (int i = 7; i > 0; i--)
        travelingBodies[4][i] = travelingBodies[4][i - 1];
      travelingBodies[4][0] = aux;
      for (int i = 0; i < 8; i++)
        lc.setLed(0, 5, i, travelingBodies[4][i] == 1 ? true : false);
      if (froggerBodyColumn == 5)
        lc.setLed(0, froggerBodyColumn, froggerBodyRow, true);
    }
  }
}

void frogger::froggerMovement() //Miscarea player-ului
{
  unsigned long currentTime = millis();
  if (levelFinish == 1 && froggerBodyColumn == 7)
  {
    winOrLose(true);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Buy Full Version");
    lcd.setCursor(0, 1);
    lcd.print("At Ghita Alex");
    joyClk = 1;
    delay(300);
    while (joyClk == 1)
      joyClk = digitalRead(joyPinClk);
    inGame = false;
    reseter = true;
    joyDirectionDefault = 3;
  }
  if (levelFinish == 0 && froggerBodyColumn == 0) //Daca ajunge in capatul de sus notam 1
    levelFinish = 1;
  if (currentTime - travelingBodiesTimes[6] > 50) //Pentru a nu continua intr-o directie pana in capat printr-un singur input scurt
  {
    travelingBodiesTimes[6] = currentTime;
    lc.setLed(0, froggerBodyColumn, froggerBodyRow, false);
    switch (joyDirection)
    {
      case 2:
        {
          if (froggerBodyColumn > 0)
            froggerBodyColumn--;
          break;
        }
      case 1:
        {
          if (froggerBodyRow > 0)
            froggerBodyRow--;
          break;
        }
      case -2:
        {
          if (froggerBodyColumn < 7)
            froggerBodyColumn++;
          break;
        }
      case -1:
        {
          if (froggerBodyRow < 7)
            froggerBodyRow++;
          break;
        }
    }
    lc.setLed(0, froggerBodyColumn, froggerBodyRow, true);
  }
}

boolean frogger::safeCheck()  //Coliziunea dintre player si corpuri
{
  if (froggerBodyColumn == 1 && travelingBodies[0][froggerBodyRow] == 1)
    return false;
  if (froggerBodyColumn == 3 && travelingBodies[2][froggerBodyRow] == 1)
    return false;
  if (froggerBodyColumn == 5 && travelingBodies[4][froggerBodyRow] == 1)
    return false;
  return true;
}

void setup()
{
  lcd.begin(16, 2);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  Serial.begin(9600);
  pinMode(joyPinX, INPUT);
  pinMode(joyPinY, INPUT);
  pinMode(joyPinClk, INPUT);
  digitalWrite(joyPinClk, HIGH);
  pinMode(lcdVo, OUTPUT);
  analogWrite(lcdVo, 102);  //In loc de potentiometru scriu 2 volti pe V0
  randomSeed(analogRead(4));  //Pentru crearea de random adevarat (dupa noise)
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  {
    valueX = analogRead(joyPinY);
    valueY = analogRead(joyPinX);
    joyClk = digitalRead(joyPinClk);
    //Citirea de joystick cu contitia: sus = 2, jos = -2, dreapta = 1, stanga = -1, rest = 0
    joyDirection = 0;
    if (valueX > 868 && valueY > 248 && valueY < 868)
      joyDirection = -1;
    if (valueX < 268 && valueY > 248 && valueY < 868)
      joyDirection = 1;
    if (valueY > 868 && valueX > 248 && valueX < 868)
      joyDirection = -2;
    if (valueY < 268 && valueX > 248 && valueX < 868)
      joyDirection = 2;
  }
  switch (change)
  {
    case 0:
      { //Meniul principal
        launchLoadingGeneral();
        if (joyDirection != joyDirectionDefault)
        {
          joyDirectionDefault = joyDirection;
          if (joyDirection == 2 || joyDirection == -2)
            menuSpot -= joyDirection / 2;
          if (menuSpot < 0)
            menuSpot = 0;
          if (menuSpot > 2)
            menuSpot = 2;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(menuPrincipal[menuSpot]);
          lcd.setCursor(0, 1);
          lcd.print(menuPrincipal[menuSpot + 1]);
          lcd.print("<");
        }
        if (joyClk != joyDefaultClk)
        {
          joyDefaultClk = joyClk;
          if (joyClk == 0)
          {
            change = menuSpot + 1;
            joyDirectionDefault = 2;
            menuSpot = 0;
            lcd.clear();
          }
          delay(300);
        }
        break;
      }
    case 1:
      { //Snake
        if (menuFocus != NULL && reseter == true)
        {
          delete (snake*)menuFocus;
          menuFocus = NULL;
        }
        if (menuFocus == NULL)
        {
          menuFocus = new snake;
          reseter = false;
        }
        ((snake*)menuFocus)->menuShow();
        break;
      }
    case 2:
      { //Frogger
        if (menuFocus != NULL && reseter == true)
        {
          delete (frogger*)menuFocus;
          menuFocus = NULL;
        }
        if (menuFocus == NULL)
        {
          menuFocus = new frogger;
          reseter = false;
        }
        ((frogger*)menuFocus)->menuShow();
        break;
      }
    case 3:
      { //Space Ship
        winOrLose(false);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Buy Full Version");
        lcd.setCursor(0, 1);
        lcd.print("At Ghita Alex");
        delay(5000);
        change = 0;
        break;
      }
  }
}

