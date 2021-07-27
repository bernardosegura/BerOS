#include <kernel.h>

char* version = "Rxj-0.19";
unsigned char lockUpdateClock = 0;

window wnd;

char displayFont = 0;
char showRelojPanel = 1;
char displayColor = 4;

void kernel()
{
    //window wnd;
    init(version);
    barraSuperior(version);
    lockUpdateClock = 1;
    wnd = CreateWnd(1, 12, 78, 12,"Ayuda");
    setXYWnd(&wnd,0,0);
    print("   Fuente Reloj              Color                    Extras\n");
    print("Ctrl + N = Normal      Ctrl + 1 = Azul            Power = Apagar\n");
    print("Ctrl + A = Alien       Ctrl + 2 = Verde        Ctrl + Q = Reiniciar\n");
    print("Ctrl + D = Digital     Ctrl + 3 = Azul Cielo   Ctrl + R = Reloj en Panel\n");
    print("                       Ctrl + 4 = Rojo\n");
    print("                       Ctrl + 5 = Morado\n");
    print("                       Ctrl + 6 = Naranja\n");
    print("                       Ctrl + 7 = Blanco\n");

    /*for (int i = 0; i < 16; ++i)
      {
          change_color(i,i);
          putc(' ');
      }*/
    //setXY(0,0); 
    lockUpdateClock = 0;
}

void init(char* version)
{
    //splash_BerOS(35,10,10,5,6);
    splash_BerOS(0,0,80,25,version);
    print(" ");

    change_kbmap(&kbdmap_lat);
    print(" ");
     
    init_gdt();
    print("  ");

    init_idt();
    print("  ");

    init_pic();
    print(" ");

    asm(" movw $0x38, %ax; ltr %ax");
    enable_interrupt();
    print("  "); 
}

void barraSuperior(char* version)
{
  //change_color(Black,Black);  
  //clear_vga();
  change_color(LightGrey,LightGrey);

  for (int i = 0; i < 80; ++i)
     {
       setXY(i,0);
       print(" ");
     }
  
  setXY(1,0);
  change_color(Green,LightGrey);
  print("Ber");
  change_color(Yellow,LightGrey);
  print("OS"); 
  change_color(Black,LightGrey);
  print(" v%s",version);
  
  //setXY(74,0);
  //print("Reloj");
  
  updateClock();
  //change_color(Magenta,Magenta);
  //setXY(0,0);
}

void isr_schedule_int()
{
    static int tic = 0;
    static int sec = 0;
        tic++;
        if (tic % 100 == 0) {
        sec++;
        tic = 0;        
    }
    if(lockUpdateClock == 0)
    {
       updateClock();
    }
    //schedule();
    outb(0x20,0x20);
    outb(0xA0,0x20);
}

void updateClock()
{
    updateDate();

    char ds[2],dm[2],dh[2];
    //char nS0[10][8], nS1[10][8];
    time reloj = {0};
    reloj = getTime();

    if(reloj.Hour > 12)reloj.Hour -= 12; 
    
    itoa(dh,reloj.Hour,10);
    if(strlen(dh) > 1)
    {
        setHora(dh[0], dh[1]);
    }
    else
    {
        setHora('0', dh[0]);
    }

    dosPuntos();
    
    itoa(dm,reloj.Minute,10);
    if(strlen(dm) > 1)
    {
        setMinutos(dm[0], dm[1]);
    }
    else
    {
        setMinutos('0', dm[0]);
    }

    unPunto();
    
    itoa(ds,reloj.Second,10);
    if(strlen(ds) > 1)
    {
        setSegundos(ds[0], ds[1]);
    }
    else
    {
        setSegundos('0', ds[0]);
    }
    

    if (showRelojPanel == 1)
    {
        change_color(Black,LightGrey);
    }
    else
    {
        change_color(LightGrey,LightGrey);

    }    
        //setXY(((80-10)/2),5);
        //setXY(((80-10)/2),15);
        setXY(64,0);
        print("%d:%d.%d %s   ",reloj.Hour,reloj.Minute,reloj.Second,reloj.ap);

    
    setXY(0,24);
    //setXYWnd(&wnd,0,0);
}



void setHora(char n0, char n1)
{
    int j;
    char *p_0[10];
    char **digito_0;
    char *p_1[10];
    char **digito_1;

    switch(n0)
    {
        case '0':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cero[j]:((displayFont == 1))?ceroA[j]:ceroD[j]);
             }
          break;
        case '1':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?uno[j]:((displayFont == 1))?unoA[j]:unoD[j]);
             }
          break;
        case '2':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?dos[j]:((displayFont == 1))?dosA[j]:dosD[j]);
             }
          break;
        case '3':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?tres[j]:((displayFont == 1))?tresA[j]:tresD[j]);
             }
          break;
        case '4':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cuatro[j]:((displayFont == 1))?cuatroA[j]:cuatroD[j]);
             }
          break;
        case '5':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cinco[j]:((displayFont == 1))?cincoA[j]:cincoD[j]);
             }
          break;
        case '6':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?seis[j]:((displayFont == 1))?seisA[j]:seisD[j]);
             }
          break;
        case '7':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?siete[j]:((displayFont == 1))?sieteA[j]:sieteD[j]);
             }
          break;
        case '8':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?ocho[j]:((displayFont == 1))?ochoA[j]:ochoD[j]);
             }
          break;
        case '9':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?nueve[j]:((displayFont == 1))?nueveA[j]:nueveD[j]);
             }
          break;          
    }

    digito_0 = p_0;
    
    switch(n1)
    {
        case '0':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cero[j]:((displayFont == 1))?ceroA[j]:ceroD[j]);
             }
          break;
        case '1':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?uno[j]:((displayFont == 1))?unoA[j]:unoD[j]);
             }
          break;
        case '2':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?dos[j]:((displayFont == 1))?dosA[j]:dosD[j]);
             }
          break;
        case '3':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?tres[j]:((displayFont == 1))?tresA[j]:tresD[j]);
             }
          break;
        case '4':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cuatro[j]:((displayFont == 1))?cuatroA[j]:cuatroD[j]);
             }
          break;
        case '5':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cinco[j]:((displayFont == 1))?cincoA[j]:cincoD[j]);
             }
          break;
        case '6':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?seis[j]:((displayFont == 1))?seisA[j]:seisD[j]);
             }
          break;
        case '7':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?siete[j]:((displayFont == 1))?sieteA[j]:sieteD[j]);
             }
          break;
        case '8':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?ocho[j]:((displayFont == 1))?ochoA[j]:ochoD[j]);
             }
          break;
        case '9':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?nueve[j]:((displayFont == 1))?nueveA[j]:nueveD[j]);
             }
          break;          
    }

    digito_1 = p_1;

    hora(digito_0,digito_1);
}

void setMinutos(char n0, char n1)
{
    int j;
    char *p_0[10];
    char **digito_0;
    char *p_1[10];
    char **digito_1;

    switch(n0)
    {
        case '0':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cero[j]:((displayFont == 1))?ceroA[j]:ceroD[j]);
             }
          break;
        case '1':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?uno[j]:((displayFont == 1))?unoA[j]:unoD[j]);
             }
          break;
        case '2':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?dos[j]:((displayFont == 1))?dosA[j]:dosD[j]);
             }
          break;
        case '3':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?tres[j]:((displayFont == 1))?tresA[j]:tresD[j]);
             }
          break;
        case '4':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cuatro[j]:((displayFont == 1))?cuatroA[j]:cuatroD[j]);
             }
          break;
        case '5':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cinco[j]:((displayFont == 1))?cincoA[j]:cincoD[j]);
             }
          break;
        case '6':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?seis[j]:((displayFont == 1))?seisA[j]:seisD[j]);
             }
          break;
        case '7':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?siete[j]:((displayFont == 1))?sieteA[j]:sieteD[j]);
             }
          break;
        case '8':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?ocho[j]:((displayFont == 1))?ochoA[j]:ochoD[j]);
             }
          break;
        case '9':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?nueve[j]:((displayFont == 1))?nueveA[j]:nueveD[j]);
             }
          break;          
    }

    digito_0 = p_0;
    
    switch(n1)
    {
        case '0':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cero[j]:((displayFont == 1))?ceroA[j]:ceroD[j]);
             }
          break;
        case '1':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?uno[j]:((displayFont == 1))?unoA[j]:unoD[j]);
             }
          break;
        case '2':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?dos[j]:((displayFont == 1))?dosA[j]:dosD[j]);
             }
          break;
        case '3':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?tres[j]:((displayFont == 1))?tresA[j]:tresD[j]);
             }
          break;
        case '4':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cuatro[j]:((displayFont == 1))?cuatroA[j]:cuatroD[j]);
             }
          break;
        case '5':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cinco[j]:((displayFont == 1))?cincoA[j]:cincoD[j]);
             }
          break;
        case '6':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?seis[j]:((displayFont == 1))?seisA[j]:seisD[j]);
             }
          break;
        case '7':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?siete[j]:((displayFont == 1))?sieteA[j]:sieteD[j]);
             }
          break;
        case '8':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?ocho[j]:((displayFont == 1))?ochoA[j]:ochoD[j]);
             }
          break;
        case '9':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?nueve[j]:((displayFont == 1))?nueveA[j]:nueveD[j]);
             }
          break;          
    }

    digito_1 = p_1;

    minutos(digito_0,digito_1);
}

void setSegundos(char n0, char n1)
{
    int j;
    char *p_0[10];
    char **digito_0;
    char *p_1[10];
    char **digito_1;

    switch(n0)
    {
        case '0':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cero[j]:((displayFont == 1))?ceroA[j]:ceroD[j]);
             }
          break;
        case '1':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?uno[j]:((displayFont == 1))?unoA[j]:unoD[j]);
             }
          break;
        case '2':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?dos[j]:((displayFont == 1))?dosA[j]:dosD[j]);
             }
          break;
        case '3':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?tres[j]:((displayFont == 1))?tresA[j]:tresD[j]);
             }
          break;
        case '4':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cuatro[j]:((displayFont == 1))?cuatroA[j]:cuatroD[j]);
             }
          break;
        case '5':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?cinco[j]:((displayFont == 1))?cincoA[j]:cincoD[j]);
             }
          break;
        case '6':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?seis[j]:((displayFont == 1))?seisA[j]:seisD[j]);
             }
          break;
        case '7':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?siete[j]:((displayFont == 1))?sieteA[j]:sieteD[j]);
             }
          break;
        case '8':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?ocho[j]:((displayFont == 1))?ochoA[j]:ochoD[j]);
             }
          break;
        case '9':
            for(j = 0; j < 10; j++)
             {
               p_0[j] = ((displayFont == 0)?nueve[j]:((displayFont == 1))?nueveA[j]:nueveD[j]);
             }
          break;          
    }

    digito_0 = p_0;
    
    switch(n1)
    {
        case '0':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cero[j]:((displayFont == 1))?ceroA[j]:ceroD[j]);
             }
          break;
        case '1':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?uno[j]:((displayFont == 1))?unoA[j]:unoD[j]);
             }
          break;
        case '2':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?dos[j]:((displayFont == 1))?dosA[j]:dosD[j]);
             }
          break;
        case '3':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?tres[j]:((displayFont == 1))?tresA[j]:tresD[j]);
             }
          break;
        case '4':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cuatro[j]:((displayFont == 1))?cuatroA[j]:cuatroD[j]);
             }
          break;
        case '5':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?cinco[j]:((displayFont == 1))?cincoA[j]:cincoD[j]);
             }
          break;
        case '6':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?seis[j]:((displayFont == 1))?seisA[j]:seisD[j]);
             }
          break;
        case '7':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?siete[j]:((displayFont == 1))?sieteA[j]:sieteD[j]);
             }
          break;
        case '8':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?ocho[j]:((displayFont == 1))?ochoA[j]:ochoD[j]);
             }
          break;
        case '9':
            for(j = 0; j < 10; j++)
             {
               p_1[j] = ((displayFont == 0)?nueve[j]:((displayFont == 1))?nueveA[j]:nueveD[j]);
             }
          break;          
    }

    digito_1 = p_1;

    segundos(digito_0,digito_1);
}

time getTime()
{
    time tiempo = {0};

    unsigned int DataHour, DataMinute, DataSecond;

    outb(0x70, 0x95);

    outb(0x70, 4);
    DataHour = inb(0x71);
    tiempo.Hour = DataHour - ((unsigned int) DataHour/16) * 6;

    outb(0x70, 2);
    DataMinute = inb(0x71);
    tiempo.Minute = DataMinute - ((unsigned int) DataMinute/16) * 6;  
    
    outb(0x70, 0);
    DataSecond = inb(0x71);
    tiempo.Second = DataSecond - ((unsigned int) DataSecond/16) * 6;

    if(tiempo.Hour < 12)
    {
        tiempo.ap = "am";
        if(displayFont == 0)
            ampm(A, M);
        if(displayFont == 1)
            ampm(AA, MA);
        else    
            ampm(AD, MD);        
    }
    else
    {
        tiempo.ap = "pm";
        if(displayFont == 0)
            ampm(P, M);
        if(displayFont == 1)
            ampm(PA, MA);
        else 
            ampm(PD, MD);
    }

    return tiempo;
}

date getDate()
{
    date fecha = {0};
    unsigned int DataYear, DataMonth, DataDay, DataWeekday;

    outb(0x70, 0x95);

    outb(0x70, 9);
    DataYear = inb(0x71);
    fecha.Year = (DataYear - ((unsigned int) DataYear/16) * 6) + 2000;

    outb(0x70, 8);
    DataMonth = inb(0x71);
    fecha.Month = DataMonth - ((unsigned int) DataMonth/16) * 6;

    switch(fecha.Month)
    {
        case 1:
            fecha.Mth = "Enero";
            break;
        case 2:
            fecha.Mth = "Febrero";
            break;
        case 3:
            fecha.Mth = "Marzo";
            break;
        case 4:
            fecha.Mth = "Abril";
            break;
        case 5:
            fecha.Mth = "Mayo";
            break;
        case 6:
            fecha.Mth = "Junio";
            break;
        case 7:
            fecha.Mth = "Julio";
            break;
        case 8:
            fecha.Mth = "Agosto";
            break;
        case 9:
            fecha.Mth = "Septiembre";
            break;
        case 10:
            fecha.Mth = "Octubre";
            break;
        case 11:
            fecha.Mth = "Noviembre";
            break;
        case 12:
            fecha.Mth = "Diciembre";
            break;      
    };

    outb(0x70, 7);
    DataDay = inb(0x71);
    fecha.Day = DataDay - ((unsigned int) DataDay/16) * 6;

    outb(0x70, 6);
    DataWeekday = inb(0x71);
    /*if(DataWeekday<6)*/ fecha.Weekday = DataWeekday;// + 2;
    //else fecha.Weekday = DataWeekday - 5;
    switch(fecha.Weekday)
    {
        case 1:
            fecha.Wday = "Lunes";
            break;
        case 2:
            fecha.Wday = "Martes";
            break;
        case 3:
            fecha.Wday = "Miercoles";
            break;
        case 4:
            fecha.Wday = "Jueves";
            break;
        case 5:
            fecha.Wday = "Viernes";
            break;
        case 6:
            fecha.Wday = "Sabado";
            break;                       
        case 7:
            fecha.Wday = "Domingo";
            break;
    };

    return fecha;
}

void updateDate()
{
    date fecha = getDate();

    change_color(Black,LightGrey);
    setXY(/*((80-10)/2)*/20,0);
    print("%s %d de %s del %d",fecha.Wday,fecha.Day, fecha.Mth, fecha.Year);
    //setXY(0,0);

}

void hora(char **digito_0, char **digito_1)
{
  for(int h = 2; h < 11; h++)
  {
    for(int v = 0; v < 8; v++)
    {
      setXY(v,h);
      if(digito_0[h-2][v] == 4)
        change_color(displayColor,displayColor);
      else
        change_color(digito_0[h-2][v],digito_0[h-2][v]);  
      putc(' ');
    }
  } 

  for(int h = 2; h < 11; h++)
  {
    for(int v = 9; v < 17; v++)
    {
      setXY(v,h);
      if(digito_1[h-2][v-9] == 4)
        change_color(displayColor,displayColor);
      else
        change_color(digito_1[h-2][v-9],digito_1[h-2][v-9]);  
      putc(' ');
    }
  } 

}

void minutos(char **digito_0, char **digito_1)
{
  for(int h = 2; h < 11; h++)
  {
    for(int v = 21; v < 29; v++)
    {
      setXY(v,h);
      if(digito_0[h-2][v-21] == 4)
        change_color(displayColor,displayColor);
      else
        change_color(digito_0[h-2][v-21],digito_0[h-2][v-21]);  
      putc(' ');
    }
  } 

  for(int h = 2; h < 11; h++)
  {
    for(int v = 30; v < 38; v++)
    {
      setXY(v,h);
      if(digito_1[h-2][v-30] == 4)
        change_color(displayColor,displayColor);
      else
        change_color(digito_1[h-2][v-30],digito_1[h-2][v-30]);  
      putc(' ');
    }
  } 

}

void segundos(char **digito_0, char **digito_1)
{
  for(int h = 2; h < 11; h++)
  {
    for(int v = 43; v < 51; v++)
    {
      setXY(v,h);
      if(digito_0[h-2][v-43] == 4)
        change_color(displayColor,displayColor);
      else
        change_color(digito_0[h-2][v-43],digito_0[h-2][v-43]);  
      putc(' ');
    }
  } 

  for(int h = 2; h < 11; h++)
  {
    for(int v = 52; v < 60; v++)
    {
      setXY(v,h);
      if(digito_1[h-2][v-52] == 4)
        change_color(displayColor,displayColor);
      else
        change_color(digito_1[h-2][v-52],digito_1[h-2][v-52]);  
      putc(' ');
    }
  } 

}

void ampm(char digito_0[10][8], char digito_1[10][8])
{
  for(int h = 2; h < 11; h++)
  {
    for(int v = 61; v < 69; v++)
    {
      setXY(v,h);
      if(digito_0[h-2][v-61] == 4)
        change_color(displayColor,displayColor);
      else
        change_color(digito_0[h-2][v-61],digito_0[h-2][v-61]);  
      putc(' ');
    }
  } 

  for(int h = 2; h < 11; h++)
  {
    for(int v = 70; v < 78; v++)
    {
      setXY(v,h);
      if(digito_1[h-2][v-70] == 4)
        change_color(displayColor,displayColor);
      else
        change_color(digito_1[h-2][v-70],digito_1[h-2][v-70]);  
      putc(' ');
    }
  } 

}

void dosPuntos()
{  
  for(int h = 2; h < 11; h++)
  {
    for(int v = 18; v < 21; v++)
    {
      setXY(v,h);
      if(displayFont == 0)
      {
        if(puntos[h-2][v-18] == 4)
            change_color(displayColor,displayColor);
        else
            change_color(puntos[h-2][v-18],puntos[h-2][v-18]);
      }
      if(displayFont == 1)
      {
        if(puntosA[h-2][v-18] == 4)
            change_color(displayColor,displayColor);
        else
            change_color(puntosA[h-2][v-18],puntosA[h-2][v-18]);
      }
      else
      {
        if(puntosD[h-2][v-18] == 4)
            change_color(displayColor,displayColor);
        else
            change_color(puntosD[h-2][v-18],puntosD[h-2][v-18]);
      }
      putc(' ');
    }
  } 

}

void unPunto()
{  
  for(int h = 1; h < 11; h++)
  {
    for(int v = 39; v < 42; v++)
    {
      setXY(v,h);
      if(displayFont == 0)
      {
        if(punto[h-1][v-39] == 4)
            change_color(displayColor,displayColor); 
        else
            change_color(punto[h-1][v-39],punto[h-1][v-39]); 
      } 
      if(displayFont == 1)
      {
        if(puntoA[h-1][v-39] == 4)
            change_color(displayColor,displayColor); 
        else
            change_color(puntoA[h-1][v-39],puntoA[h-1][v-39]);
      }
      else
      {
        if(puntoD[h-1][v-39] == 4)
            change_color(displayColor,displayColor); 
        else
            change_color(puntoD[h-1][v-39],puntoD[h-1][v-39]); 
      } 
      putc(' ');
    }
  } 

}

void setDisplayFot(char fnt)
{
    displayFont = fnt;
}

void setShowRelojPanel()
{
    if(showRelojPanel == 1)
        showRelojPanel = 0;
    else
        showRelojPanel = 1;
}

void changeColorDisplay(char color)
{
    displayColor = color;
}