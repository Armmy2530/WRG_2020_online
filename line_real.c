int baseSpeed = 80;
int maxSpeed = 100;
int motorSpeed;
int leftSpeed, rightSpeed;
int line = 0 ;
int Kp = 35;
int Kd = 0;
float Ki = 0;
int ref1 = 600;
int error = 0;
int pre_error;
int sum_error;
int inputvar1;
int inputvar2;
int inputvar3;
int inputvar4;
int inputvar5;
int numbertocheck=12;
int x=0;
int lap=1;
int []lineneedtoleack = new int[6]{2,3,7,8,16,17};
bool W(int n)
{ if (n >= ref1) {
    return true;
  }
  else {
    return false;
  }
}
bool B(int n)
{ if (n < ref1) {
    return true;
  }
  else {
    return false;
  }
}
bool getleack = false;
void setup()
{
  sw1_press();
  do
  {
     lcd("line=%d",line);
     sensorcheck();
     pid_run();
      if(line>=0&&line<6){
      if ( B(inputvar2) && B(inputvar3) && B(inputvar4) ){
        do{
          sensorcheck();
          fd(60);
        }while (B(inputvar2)&& B(inputvar4));
        sleep(300);
        line++;
        cheackgetleack();
        if(getleack == true){
            if(line==7){
                getleackL(); 
                do{
                sl(40);
                sensorcheck();
                }while(inputvar2>500);
            }
            else{getleackL();}
            x++;
        }
      }
      }
      else if(line>=6&&line<8){
      if ( B(inputvar2) && B(inputvar3) && B(inputvar4) ){
        do{
          sensorcheck();
          fd(60);
        }while (B(inputvar2)&& B(inputvar4));
        sleep(300);
        line++;
        cheackgetleack();
        if(getleack == true){
            if(line==7||line==8){
                getleackR(); 
                do{
                sr(40);
                sensorcheck();
                }while(inputvar2>500);
            }
            else{getleackR();}
            x++;
        }
      }
      }
      else if(line>=8&&line<=12){
          sensorcheck();
          if (B(inputvar1)&&B(inputvar2))
          {
            line++;
            if (line==10)
            {
              fd(80);
              sleep(500);
              ao();
              do
              {
                sr(40);
                sensorcheck();
             }while(inputvar3>500);
              do
              {
               sr(40);
               sensorcheck();
              }while(inputvar3<500);
              sleep(100);
            }
            else
            {
              fd(80);
              sleep(500);
              ao();
              sl90();
            }
          }
          else if (B(inputvar5)&&B(inputvar4))
          {
            line++;
            if (line==9)
            {
              fd(80);
              sleep(100);
              ao();
              getleackR();
            }
            else if (line==12)
            {
              fd(80);
              sleep(500);
              ao();
              sl90();
            }
            else if (line==13)
            {
              fd(80);
              sleep(500);
              ao();
              sr90();
            }
            
          }
          else{}
        }
        else if (line>=13&&line<=14)
        {
          if (B(inputvar1)&&B(inputvar2))
          {
            line++;
            if(line==15)
            {
              fd(80);
              sleep(500);
              ao();
              do
              {
                sr(40);
                sensorcheck();
             }while(inputvar3>500);
              do
              {
               sr(40);
               sensorcheck();
              }while(inputvar3<500);
              sleep(100);
            }
          }
          else if (B(inputvar4)&&B(inputvar5))
          {
            line++;
            if(line==14)
            {
            fd(80);
            sleep(100);
            ao();
            getleackR();
            }
          }
        } 
        else if (line>=15&&line<=16)
        {
          if ( B(inputvar2) && B(inputvar3) && B(inputvar4) ){
            do{
              sensorcheck();
              fd(60);
            }while (B(inputvar2)&& B(inputvar4));
            sleep(300);
            line++;
            cheackgetleack();
            if(getleack == true){
              getleackL();
            }
            x++;
          }
        }
        else if (line>=17&&line<=18)
        {
          if (B(inputvar1)&&B(inputvar2))
          {
            line++;
            if(line==19)
            {
              fd(80);
              sleep(500);
              ao();
              do
              {
                sr(40);
                sensorcheck();
              }while(inputvar3>500);
              do
              {
               sr(40);
               sensorcheck();
              }while(inputvar3<500);
              sleep(100);
              line++;
            }
          }
          else if (B(inputvar4)&&B(inputvar5))
          {
            line++;
            if(line==18)
            {
            fd(80);
            sleep(100);
            ao();
            getleackR();
            }
          }
          else{}
        }
        else if (lap==1&&line==20)
        {
          line=0;
          lap=2;
        }
        else if (lap==2&&line==20)
        {
          fd(80);
          sleep(200);
          ao();
          break;
        }
        else{
        }
        
  }while (true);
  lcd("Finshed");
}



void loop() {

}

void sensorcheck()
{
    inputvar1 = analog(0);
    inputvar2 = analog(1);
    inputvar3 = analog(2);
    inputvar4 = analog(3);
    inputvar5 = analog(4);
}    

void getleackR()
{
    do
    {
        sr(40);
        sensorcheck();
    }while(inputvar2>=500);
    do
    {
        sr(40);
        sensorcheck();
    }while(inputvar2<=500);
    sleep(100);
}
 
void getleackL()
{
    do
    {
        sl(40);
        sensorcheck();
    }while(inputvar2>500);
    do
    {
        sl(40);
        sensorcheck();
    }while(inputvar2<500);
    sleep(100);
}
 
void cheackgetleack()
{
        if(line==lineneedtoleack[x]){getleack=true;}
        else{getleack=false;}
        sleep(50);
}

void pid_run()
{
  if ( W(inputvar1) && W(inputvar2) && W(inputvar3) && W(inputvar4) && B(inputvar5) ) {
        error = 4; // w w w w b
      }
      else if ( W(inputvar1) && W(inputvar2) && W(inputvar3) && B(inputvar4) && B(inputvar5) ) {
        error = 3; // w w w b b
      }
      else if ( W(inputvar1) && W(inputvar2) && W(inputvar3) && B(inputvar4) && W(inputvar5) ) {
        error = 2; // w w w b w
      }
      else if ( W(inputvar1) && W(inputvar2) && B(inputvar3) && B(inputvar4) && W(inputvar5) ) {
        error = 1; // w w b b w
      }
      else if ( W(inputvar1) && W(inputvar2) && B(inputvar3) && W(inputvar4) && W(inputvar5) ) {
        error = 0; // w w b w w
      }
      else if ( W(inputvar1) && B(inputvar2) && B(inputvar3) && W(inputvar4) && W(inputvar5) ) {
        error = -1; // w b b w w
      }
      else if ( W(inputvar1) && B(inputvar2) && W(inputvar3) && W(inputvar4) && W(inputvar5) ) {
        error = -2; // w b w w w
      }
      else if ( B(inputvar1) && B(inputvar2) && W(inputvar3) && W(inputvar4) && W(inputvar5) ) {
        error = -3; // b b w w w
      }
      else if ( B(inputvar1) && W(inputvar2) && W(inputvar3) && W(inputvar4) && W(inputvar5) ) {
        error = -4; // b w w w w
      }
      else if ( W(inputvar1) && W(inputvar2) && W(inputvar3) && W(inputvar4) && W(inputvar5) ) {
        error = pre_error; // w w w w w
      }

      motorSpeed = (int)(Kp * error + Kd * (error - pre_error) + Ki * (sum_error));
      leftSpeed = baseSpeed + motorSpeed;
      rightSpeed = baseSpeed - motorSpeed;

      if (leftSpeed > maxSpeed) leftSpeed = maxSpeed;
      if (rightSpeed > maxSpeed) rightSpeed = maxSpeed;

      if (leftSpeed < -maxSpeed) leftSpeed = -maxSpeed;
      if (rightSpeed < -maxSpeed) rightSpeed = -maxSpeed;

      motor(1, leftSpeed);
      motor(2, rightSpeed);
      sleep(10);

      pre_error = error;
      sum_error += error;
}

void sr90()
{
  sr(80);
  sleep(850);
  ao();
}


void sl90()
{
  sl(80);
  sleep(850);
  ao();
}
