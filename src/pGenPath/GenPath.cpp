/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: GenPath.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "GenPath.h"
#include "CompPath.h"
#include <cstdint>
#include<sstream>
#include<unistd.h>
#include"XYPoint.h"
#include"XYSegList.h"

using namespace std;

//---------------------------------------------------------
// Constructor

GenPath::GenPath()
{
m_got_all_points = false;
m_sent_all_points = false;
}

//---------------------------------------------------------
// Destructor

GenPath::~GenPath()
{
}

void GenPath::sendPoints()
{
  double x,y;
  string label,color;

  XYSegList my_seglist;
    my_seglist.set_param("vertex_size", "3");
    // string update_str = "points = ";
      string update_str = "points = ";


  list<CompPath>::iterator l;
  for(l=m_list.begin(); l!=m_list.end(); l++) {
    CompPath &lobj = *l;
    int tmp_id = atoi(lobj.m_id.c_str());

    x = atof(lobj.m_x.c_str());
    y = atof(lobj.m_y.c_str());
    
    XYPoint point(x,y);
    point.set_param("vertex_size", "3");
    point.set_label(lobj.m_id);

    // my_seglist.set_label(lobj.m_id);

    // Notify("ASSIGN","OK");

    if((lobj.m_id=="firstpoint") ||(lobj.m_id=="lastpoint")){

    }

    else {
      // my_seglist.set_color("vertex","yellow");
      
      // my_seglist.add_vertex(point);
      my_seglist.insert_vertex(point.x(),point.y());


      // Notify(m_out_name2,"x="+lobj.m_x+", y="+lobj.m_y+", id="+lobj.m_id);
    }

  }

  update_str       += my_seglist.get_spec();

  Notify("LOITER_UPDATE",update_str);

  m_sent_all_points = true;


  // XYSegList my_seglist;
  // my_seglist.add_vertex(43,99);

  // string update_str = "points = ";
  // update_str       += my_seglist.get_spec();
  // Notify("LOITER_UPDATE",update_str);

}

//---------------------------------------------------------
// Procedure: OnNewMail

bool GenPath::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

  //Every new VISIT_POINT instantiates a CompPath object which is pushed to a list
    string key = msg.GetKey();
    if(key=="VISIT_POINT"){
      string value = msg.GetString();      
      CompPath b(value);
      m_list.push_front(b);
      // Notify("GOT_IT",b.getReport());
    }

    if(key=="NODE_REPORT_LOCAL"){
      string value = msg.GetString();  
      string x_str,y_str,ans; 
      double x,y;

      x_str = tokStringParse(value, "X", ',', '=');
      y_str = tokStringParse(value, "Y", ',', '=');
      x = atof(x_str.c_str());
      y = atof(y_str.c_str());
    // id_int = atof(lobj.m_id.c_str());
      XYPoint point(x,y);

      // ans = "x =" + x +", y ="+y;
      // Notify("GOT_IT",ans);
      string spec = point.get_spec();
      Notify("GOT_IT",spec);
    }





#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

     if(key == "FOO") 
       cout << "great!";

   //   else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
   //     reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool GenPath::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool GenPath::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!



    if(!m_got_all_points) {
      list<CompPath>::iterator p;
      for(p=m_list.begin(); p!=m_list.end(); p++) {
        CompPath &pointobj = *p;

        if((pointobj.m_id=="lastpoint")) {
          m_got_all_points = true;
        }
      }
    }



    if((m_got_all_points) && (!m_sent_all_points)) {
      sendPoints();
    }




  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool GenPath::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "foo") {
      handled = true;
    }
    else if(param == "bar") {
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void GenPath::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("VISIT_POINT", 0);
  Register("LOITER_UPDATE",0);
  Register("NODE_REPORT_LOCAL",0);
  Notify("PAUSE_TIME","false");

}


//------------------------------------------------------------
// Procedure: buildReport()

bool GenPath::buildReport() 
{
  m_msgs << "============================================ \n";
  m_msgs << "File:                                        \n";
  m_msgs << "============================================ \n";

  ACTable actab(4);
  actab << "Alpha | Bravo | Charlie | Delta";
  actab.addHeaderLines();
  actab << "one" << "two" << "three" << "four";
  m_msgs << actab.getFormattedString();

  return(true);
}




