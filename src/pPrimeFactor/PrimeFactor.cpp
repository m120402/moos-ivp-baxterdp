/************************************************************/
/*    NAME: David Baxter                                              */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactor.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "PrimeFactor.h"
#include "PrimeEntry.h"
#include <cstdint>
#include<sstream>
#include<unistd.h>

using namespace std;


int Registered = 0;
int Calculated = 0;

//---------------------------------------------------------
// Constructor

PrimeFactor::PrimeFactor() {

  //Initialize Variables                                                                  
 // m_is_even = 0;
 // m_value = 0;
  //  m_counter_registered = 0;
  //  m_counter_calculated = 0;
}

//---------------------------------------------------------
// Destructor

PrimeFactor::~PrimeFactor() {
}


//---------------------------------------------------------                                            
// Constructor                                                                                         

PrimeEntry::PrimeEntry(uint64_t v) {

  //Initialize Variables
  m_orig = v;
  m_divisor = 2;
  m_current = v;
  m_start = MOOSTime(); 
  Registered +=1; //Index Global count of registered primes prior to assigning to obj
  m_received_index = Registered;
  m_done = 0;
}

//---------------------------------------------------------
// Destructor

PrimeEntry::~PrimeEntry()
{
}

//---------------------------------------------------------

void PrimeEntry::factor(void)
{
  uint64_t number = m_current;

  uint64_t divisor = m_divisor;
  for(int i = 0;(i<1) && (!m_done);i++) {
  // for(int i = 0;(!m_done);i++) {
    if (number == 1) {
      //      m_factors.push_back(1);// Technically 1 is not a prime number
      m_done = 1;
    }
    else {
      int count = 0;
      while ((number % divisor) && (number > divisor)) {
        divisor++;
        count++;      
      }
      m_factors.push_back(divisor);
    }

    number = (number / divisor);
  }

  m_divisor = divisor;
  m_current = number;
}

string PrimeEntry::getReport() {

  Calculated +=1;
  m_calculated_index = Calculated;
  m_time = MOOSTime() - m_start;

  stringstream ss;
  ss << m_orig;
  string orig = ss.str();

  stringstream ss2;
  ss2 << m_received_index;
  string received_index = ss2.str();

  stringstream ss3;
  ss3 << m_calculated_index;
  string calculated_index = ss3.str();

  stringstream ss4;
  ss4 << m_time;
  string time = ss4.str();
  
  stringstream ss5;
  string factors;
  for (vector<uint64_t>::iterator it = m_factors.begin() ; it != m_factors.end(); ++it) {
    ss5 << *it;
    ss5 << ":";  
    
  }
  factors += ss5.str();
  factors.pop_back(); //All  but last iteration
  string str = "\n orig=" + orig + ", recived=" + received_index + ",calculated =" + calculated_index + ",solve_time=" + time + ",primes=" + factors + ",username=david\n";
  return str;
}

//---------------------------------------------------------       // Factor

/*void factors(int number)
{
  int divisor = 2;
  if (number == 1) { cout << "1" << endl; return; }
  while ((number % divisor) && (number > divisor)) divisor++;
  cout << divisor << ", ";
  factors(number / divisor);
}
*/


//---------------------------------------------------------
// Procedure: OnNewMail

bool PrimeFactor::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    string key = msg.GetKey();
    
    if(key=="NUM_VALUE"){
      string value = msg.GetString();      
      uint64_t a = strtoul(value.c_str(),NULL,0);
      //      m_list.push_front(a);
      PrimeEntry b(a);
      m_list2.push_front(b);
    }


#if 0 // Keep these around just for template
    string key   = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
   }
  
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PrimeFactor::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);
  
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PrimeFactor::Iterate()
{
  list<PrimeEntry>::iterator p;
  for(p=m_list2.begin(); p!=m_list2.end(); p++) {
    PrimeEntry &primeobj = *p;

    primeobj.factor();

    if(primeobj.done()) {
      // sleep(2);
      Notify("PRIME_RESULT",primeobj.getReport());
      p = m_list2.erase(p);
    }

    // Notify("TEST_OBJ",primeobj.m_divisor);
  }

  //  sleep(2);

  // Notify("IS_EVEN",m_is_even);

  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PrimeFactor::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string line  = *p;
      string param = tolower(biteStringX(line, '='));
      string value = line;
      
      if(param == "foo") {
        //handled
      }
      else if(param == "bar") {
        //handled
      }
    }
  }
  
  RegisterVariables();  
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void PrimeFactor::RegisterVariables()
{

  Register("NUM_VALUE", 0);
}




/*
  //Publish Odometry                                                                    
  while(!m_list.empty()){
    int a = m_list.front();
      if(a%2==0){
  m_is_even = 1;
  cout << "EVEN" << endl;
  //  factors(a);
  m_list.pop_front();
      }
      else{
  m_is_even = 0;
  cout << "ODD" << endl;
  //  factors(a);
  m_list.pop_front();   
   }

  Notify("IS_EVEN",m_is_even);

*/
