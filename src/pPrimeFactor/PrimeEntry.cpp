#include "PrimeEntry.h"
#include "PrimeFactor.h"
#include "MBUtils.h"
#include <cstdint>
#include<sstream>
#include<unistd.h>

int Registered = 0;
int Calculated = 0;


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

PrimeEntry::~PrimeEntry()
{
}


void PrimeEntry::factor(void)
{
  uint64_t number = m_current;

  uint64_t divisor = m_divisor;
  for(int i = 0;(i<10) && (!m_done);i++) {
  // for(int i = 0;(!m_done);i++) {
    if (number == 1) {
      //      m_factors.push_back(1);// Technically 1 is not a prime number
      m_done = 1;
    }
    else {
      int count = 0;
      while ((number % divisor) && (number > divisor) && (count < 1000000)) {
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
