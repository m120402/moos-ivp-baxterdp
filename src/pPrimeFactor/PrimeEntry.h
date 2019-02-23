// File: PrimeEntry.h

#include <string> 
#include <vector> 
#include <cstdint>

 #ifndef PRIME_ENTRY_HEADER
 #define PRIME_ENTRY_HEADER

using namespace std;

 class PrimeEntry
 {

 public:

   PrimeEntry(uint64_t v);
   ~PrimeEntry();

   void setOriginalVal(unsigned long int v) {m_orig=v;};
   void setReceivedIndex(unsigned int v)    {m_received_index=v;};
   void setCalculatedIndex(unsigned int v)  {m_calculated_index=v;};
   void setDone(bool v)                     {m_done=v;};
   void factor(void);

   bool   done() {return(m_done);};

   //   bool   factor(unsigned long int max_steps);

   string  getReport();

 protected:
   //   uint64_t      m_start_index;
   uint64_t      m_orig;
   uint64_t      m_current;
   uint64_t      m_divisor;
   double        m_start;
   double        m_time;
   bool          m_done;
   unsigned int  m_received_index;
   unsigned int  m_calculated_index;

   vector<uint64_t> m_factors;
 };
 #endif 
