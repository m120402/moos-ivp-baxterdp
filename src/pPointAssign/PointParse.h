// File: PointParse.h

#include <string> 
#include <vector> 
#include <cstdint>

 #ifndef POINT_PARSE_HEADER
 #define POINT_PARSE_HEADER

using namespace std;

 class PointParse
 {

 public:

   friend class PointAssign;
   // PointParse(uint64_t v);
   PointParse(string v);

   ~PointParse();

 protected:
//Functions
   string  getReport();
   // struct Comparator();



//Data
   string      m_point;
   string      m_x;
   string      m_y;
   string      m_id;
 };
 #endif 
