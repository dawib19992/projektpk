#define iclk 2      //wejscie 2 to przebieg A (zegar / impulsator)
#define idir 3      //wejsccie 3 to przebieg B (sygnal kierunku obrotu)
#define ireset 4    //wejscie 4 po przyciśnięciu to 0 dla np. resetowania kata 


//enkoder generuje 20 okresów na 360 stopni, czyli 40 zbocz na 360 stopni
const float st_na_imp=360/40; 

bool oldclk,clk,dir,reset;
int impuls_lewo = 0; 
int impuls_prawo = 0;
float kat = 0;
int czas;
float katPrawo =0;
float karLewo =0;
int st_na_impulsy = 18;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(iclk, INPUT);
  pinMode(idir, INPUT);
  pinMode(ireset, INPUT);

  oldclk=digitalRead(iclk);
}

void loop() {
  // put your main code here, to run repeatedly:

  float katPrawo = impuls_prawo * st_na_impulsy;
  float katLewo = impuls_lewo * st_na_impulsy;
  unsigned long total_impulsy = impuls_prawo + impuls_lewo;
  float czaswsek = millis() / 1000.0;
  float predkosckatowa = total_impulsy * st_na_impulsy / czaswsek;
  
  clk=digitalRead(iclk);
  dir=digitalRead(idir);
  reset=digitalRead(ireset);
  
  if (clk != oldclk)
{
  if(clk == HIGH)
  {
   if(dir == HIGH) 
   {
    impuls_prawo++;
    Serial.println("ZGODNY Z KIERUNKIEM ZEGARA");
    Serial.println("Liczba obrotow w prawo: ");
  Serial.println(impuls_prawo);
  Serial.println("Kat obrotu w prawo: ");
  Serial.println(katPrawo);
  Serial.println("Predkosc katowa: ");
  Serial.println(predkosckatowa);
  Serial.println(" ");
   }
   else
   {
    impuls_lewo++;
    Serial.println("NIEZGODNY Z KIERUNKIEM ZEGARA");
    Serial.println("Liczba obortow w lewo: ");
    Serial.println(impuls_lewo);
    Serial.println("Kat obrotu w lewo: ");
    Serial.println(katLewo);
    Serial.println("Predkosc katowa: ");
    Serial.println(predkosckatowa);
    Serial.println(" ");
   }
  }
  else
  {
    if(dir == HIGH)
    {
      impuls_lewo++;
   Serial.println("NIEZGODNY Z KIERUNKIEM ZEGARA");
   Serial.println("Liczba obortow w lewo: ");
  Serial.println(impuls_lewo);
    Serial.println("Kat obrotu w lewo: ");
  Serial.println(katLewo);
  Serial.println("Predkosc katowa: ");
  Serial.println(predkosckatowa);
  Serial.println(" ");
   }
   else
   {
    impuls_prawo++;
    Serial.println("ZGODNY Z KIERUNKIEM ZEGARA");
    Serial.println("Liczba obrotow w prawo: ");
  Serial.println(impuls_prawo);
  Serial.println("Kat obrotu w prawo: ");
  Serial.println(katPrawo);
  Serial.println("Predkosc katowa: ");
  Serial.println(predkosckatowa);
 Serial.println(" ");
    }
  }
  oldclk=clk;
}
   
  if(reset == LOW)
  {
    Serial.println("Reset enkodera");
    impuls_prawo = 0;
    impuls_lewo = 0;
  }
 

 
}

