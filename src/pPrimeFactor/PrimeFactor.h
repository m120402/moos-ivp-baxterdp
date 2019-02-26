/************************************************************/
/*    NAME: David Baxter                                              */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactor.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef PrimeFactor_HEADER
#define PrimeFactor_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include <list>
#include "PrimeEntry.h"

using namespace std;

class PrimeFactor : public CMOOSApp
{
 public:
   PrimeFactor();
   ~PrimeFactor();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
  void RegisterVariables();
//  int registered() {return m_counter_registered;};
 // bool m_is_even;
  //double m_value;
 // list<uint64_t> m_list;
  list<PrimeEntry> m_list2;
  //  int m_counter_registered;
  //  int m_counter_calculated;

 private: // Configuration variables

 private: // State variables
};

#endif 
