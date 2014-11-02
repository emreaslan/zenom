template<typename Data>
class Vector
{
   public:
     Vector() : d_size(0), d_capacity(0), d_data(0) {resize(10);} // Default constructor
     Vector(Vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); }; // Copy constuctor
     ~Vector() { free(d_data); }; // Destructor
     Vector &operator=(Vector const &other) { free(d_data); d_size = other.d_size; d_capacity = other.d_capacity; d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); return *this; }; // Needed for memory management
     void push_back(Data const &x) { if (d_capacity == d_size) resize(); d_data[d_size++] = x; }; // Adds new value. If needed, allocates more space
     size_t size() const { return d_size; }; // Size getter
     Data const &operator[](size_t idx) const { return d_data[idx]; }; // Const getter
     Data &operator[](size_t idx) { return d_data[idx]; }; // Changeable getter
   private:
     void resize() { d_capacity = d_capacity ? d_capacity*2 : 1; Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(newdata, d_data, d_size * sizeof(Data)); free(d_data); d_data = newdata; };// Allocates double the old space
     void resize(size_t pSize) { d_capacity = pSize; Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(newdata, d_data, d_size * sizeof(Data)); free(d_data); d_data = newdata; };// Allocates double the old space

     size_t d_size; // Stores no. of actually stored objects
     size_t d_capacity; // Stores allocated capacity
     Data *d_data; // Stores data
};


struct ZenomVariableData
{
  ZenomVariableData(char pName, double* pValue) : mName(pName), mValue(pValue) {}
  ZenomVariableData() : mName(0), mValue(NULL) {}
  
  char mName;
  double* mValue;
};

class ZenomArduinoManager
{
  public:
    ZenomArduinoManager(){reset();}
    void reset(){mLogVariableCurrentName = 'A'; mControlVariableCurrentName = 'a'; }
    void registerLogVariable(double* pVal, String pName){ mLogVariableVec.push_back( ZenomVariableData(mLogVariableCurrentName, pVal) ); mLogVariableCurrentName++; }
    void registerControlVariable(double* pVal, String pName){ mControlVariableVec.push_back( ZenomVariableData(mControlVariableCurrentName, pVal) ); mControlVariableCurrentName++; }
    void loopPreProcess()
    {
      char incomingByte;
      while (Serial.available() > 0)
      {
        // read the incoming byte:
        incomingByte = Serial.read();
        mBuffer += incomingByte;
      }
      
      if ( mBuffer.length() )
      {
        Serial.println(mBuffer);
      }
      processBuffer();
      
    }
    void loopPostProcess()
    {
      for (int i = 0; i < mLogVariableVec.size(); ++i)
      {
        printVariable(mLogVariableVec[i].mName, *(mLogVariableVec[i].mValue) );
      }
    }
   private:
     void processBuffer()
     {
       int bracketOpenIndex = -1;
       int lastBracketCloseIndex = -1;
       for (int i = 0; i < mBuffer.length(); ++i)
       {
         if ( mBuffer[i] == '<')
         {
           bracketOpenIndex = i;
         }
         else if (mBuffer[i] == '>' && bracketOpenIndex != -1)
         {
           processVariable(bracketOpenIndex, i);
           bracketOpenIndex = -1;
           lastBracketCloseIndex = i;
         }
       }
       
       if (lastBracketCloseIndex == -1 )
       {
         return;
       }
       
       String tempBuffer;
       for (int i = lastBracketCloseIndex+1; i < mBuffer.length(); ++i)
       {
         tempBuffer += mBuffer[i];
       } 
       mBuffer = tempBuffer;
       return;            
     }
     
     void processVariable(int pBeginIndex, int pEndIndex )
     {
       char varName;
       String varValue;
       bool isDividerFound = false;
       for (int i = pBeginIndex+1; i < pEndIndex ; ++i)
       {
         if (mBuffer[i] == ':')
         {
           isDividerFound = true;
           continue;           
         }
         
         if (mBuffer[i] == ' ')
         {
           continue;           
         }
         
         if (isDividerFound)
         {
           varValue += mBuffer[i];
         }
         else
         {
           varName = mBuffer[i];
         }         
       }
       setControlVariable(varName, varValue);
     }
     
     void setControlVariable(const char pName, String& pValue)
     {
       Serial.print("pName : ");
       Serial.println(pName);
       
       Serial.print("pValue : ");
       Serial.println(pValue);
       
       int variableIndex = -1;
       for (int i = 0; i < mControlVariableVec.size(); ++i)
       {
         if ( mControlVariableVec[i].mName == pName)
         {
            variableIndex = i;
            break;
         }
       }

       if (variableIndex != -1)
       {
         char* valueStr = (char*)malloc(pValue.length() + 1 * sizeof(char) );
         pValue.toCharArray(valueStr, pValue.length() );
         *(mControlVariableVec[variableIndex].mValue) = atof(valueStr);
         free(valueStr);
       }       
     }
     
   
     void printVariable(const char pVariableName, double pValue)
     {
      Serial.print("<");
      Serial.print(pVariableName);
      Serial.print(" : ");
      Serial.print(pValue);
      Serial.println(">"); 
     }
      
     
     
     Vector<ZenomVariableData> mLogVariableVec;
     Vector<ZenomVariableData> mControlVariableVec;
     String mBuffer;
     char mLogVariableCurrentName;
     char mControlVariableCurrentName;
};


// Arduino Motor Control 
#ifdef USE_MOTOR

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

/*  VNH2SP30 pin definitions
 xxx[0] controls '1' outputs
 xxx[1] controls '2' outputs */
int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)
int statpin = 13;

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND
 
 pwm: should be a value between ? and 1023, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}

void initMotor()
{
 // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
}



#endif 

