//Header
// File: Data.h

#include <string> 
#include <vector> 
#include <cstdint>

 #ifndef DATA_HEADER
 #define DATA_HEADER

using namespace std;

 class Data
 {

 public:
   friend class CommunicationAngle_baxterdp;
   Data();
   ~Data();

 protected:
//Functions
   // bool   done() {return(m_done);};
   // void factor(void);
   // string  getReport();

   bool   set_x0(double v) {m_x0 = v; return(true);};
   bool   set_y0(double v) {m_y0 = v; return(true);};
   bool   set_depth0(double v) {m_depth0 = v; return(true);};
   bool   set_deptha(double v) {m_deptha = v; return(true);};
   bool   set_xa(double v) {m_xa = v; return(true);};
   bool   set_ya(double v) {m_ya = v; return(true);};
   bool   set_c0(double v) {m_c0 = v; return(true);};
   bool   set_g(double v) {m_g = v; return(true);};
   bool   set_depthw(double v) {m_depthw = v; return(true);};


//Data
   double      	 m_x0; //Transmitter
   double        m_y0;
   double        m_xa; //UAV
   double        m_ya;
   double        m_depth0;
   double        m_deptha;
   double        m_c0;
   double        m_g;
   double        m_depthw;
   // bool          m_evens;
   // unsigned int  m_received_index;
   // unsigned int  m_calculated_index;
   // vector<uint64_t> m_factors;
 };
 #endif 
